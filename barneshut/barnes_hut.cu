//CUDA BarnesHut v1.1: Simulation of the gravitational forces
//in a galactic cluster using the Barnes-Hut n-body algorithm
//Copyright (c) 2010 The University of Texas at Austin
//Author: Dr. Martin Burtscher

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <cuda.h>

// thread count
#define THREADS0 512
#define THREADS1 512
#define THREADS2 288
#define THREADS3 256
#define THREADS4 512
#define THREADS5 384
#define THREADS6 512

// block count = factor * SMs
#define FACTOR0 2
#define FACTOR1 1
#define FACTOR2 2
#define FACTOR3 1
#define FACTOR4 1
#define FACTOR5 2
#define FACTOR6 1

#define WARPSIZE 32
#define MAXDEPTH 26

// input generation
#define MULT 1103515245
#define ADD 12345
#define MASK 0x7FFFFFFF
#define TWOTO31 2147483648.0

#define CUDA_SAFE_CALL_NO_SYNC(call) {                                       \
    cudaError err = call;                                                    \
    if( cudaSuccess != err) {                                                \
        fprintf(stderr, "Cuda error in file '%s' in line %i : %s.\n",        \
                __FILE__, __LINE__, cudaGetErrorString( err) );              \
        exit(EXIT_FAILURE);                                                  \
    } }

#define CUDA_SAFE_CALL(call) CUDA_SAFE_CALL_NO_SYNC(call);

#define CUT_CHECK_ERROR(errorMessage) {                                      \
    cudaThreadSynchronize();                                                 \
    cudaError_t err = cudaGetLastError();                                    \
    if( cudaSuccess != err) {                                                \
        fprintf(stderr, "[CUDA ERROR] %s\n", errorMessage);                  \
        fprintf(stderr, "[CUDA ERROR] in file '%s' in line %i : %s.\n",      \
                __FILE__, __LINE__, cudaGetErrorString( err) );              \
        exit(EXIT_FAILURE);                                                  \
    }                                                                        \
  }

/*
static void CudaTest(char *msg) {
  cudaError_t e;
  cudaThreadSynchronize();
  if (cudaSuccess != (e = cudaGetLastError())) {
    fprintf(stderr, "%s: %d\n", msg, e);
    fprintf(stderr, "%s\n", cudaGetErrorString(e));
    exit(-1);
  }
}
//*/

static int A = 1;
static int B = 0;
static int randx = 1;
static int lastrand;

static void drndset(int seed) {
   A = 1;
   B = 0;
   randx = (A * seed + B) & MASK;
   A = (MULT * A) & MASK;
   B = (MULT * B + ADD) & MASK;
}

static double drnd() {
   lastrand = randx;
   randx = (A * randx + B) & MASK;
   return (double)lastrand / TWOTO31;
}

// childd is aliased with velxd, velyd, velzd, accxd, accyd, acczd, and sortd but they never use the same memory locations
__constant__ volatile int nnodesd, nbodiesd;
__constant__ volatile float dtimed, dthfd, epssqd, itolsqd;

//__constant__ volatile int *errd;
__device__ volatile int errd = 0;
/*
__device__ volatile int *sortd, *childd, *countd, *startd;
__device__ volatile float *massd, *posxd, *posyd, *poszd, *velxd, *velyd, *velzd, *accxd, *accyd, *acczd;
__device__ volatile float *maxxd, *maxyd, *maxzd, *minxd, *minyd, *minzd;
*/
__device__ volatile int stepd = -1;
__device__ volatile int bottomd;
__device__ volatile int maxdepthd = 1;
__device__ volatile unsigned int blkcntd = 0;
__device__ volatile float radiusd;

// initialize memory
__global__ void InitializationKernel(volatile float *accxd, volatile float *accyd, volatile float *acczd) {
  int i, inc;
  i = threadIdx.x + blockIdx.x * blockDim.x;
  inc = blockDim.x * gridDim.x;
  if (i == 0) {
    printf("[DEBUG] nbodiesd = %d\n", nbodiesd);
    printf("[DEBUG] nnodesd = %d\n", nnodesd);
    printf("[DEBUG] stepd = %d\n", stepd);
    printf("[DEBUG] maxdepthd = %d\n", maxdepthd);
    printf("[DEBUG] blkcntd = %d\n", blkcntd);
    printf("[DEBUG] errd = %d\n", errd);
  }
  for (; i < nbodiesd; i += inc) {
//    accxd[i] = 0.0f;
//    accyd[i] = 0.0f;
//    acczd[i] = 0.0f;
  }
  if (i == 0) {
    printf("[DEBUG] accxd[0] = %d\n", accxd[0]);
    printf("[DEBUG] accyd[0] = %d\n", accyd[0]);
    printf("[DEBUG] acczd[0] = %d\n", acczd[0]);
  }
}

// compute center and radius
__global__ void BoundingBoxKernel(volatile float *posxd, volatile float *posyd, volatile float *poszd, volatile float *maxxd, volatile float *maxyd, volatile float *maxzd, volatile float *minxd, volatile float *minyd, volatile float *minzd, volatile float *massd, volatile int *startd, volatile int *childd) {
  register int i, j, inc;
  register float tmp;
  __shared__ volatile float minx[THREADS1], miny[THREADS1], minz[THREADS1];
  __shared__ volatile float maxx[THREADS1], maxy[THREADS1], maxz[THREADS1];

  i = threadIdx.x;
  if (i == 0) {
    minx[0] = posxd[0];
    miny[0] = posyd[0];
    minz[0] = poszd[0];
  }
  __syncthreads();

  // initialize with valid data (in case #bodies < #threads)
  minx[i] = maxx[i] = minx[0];
  miny[i] = maxy[i] = miny[0];
  minz[i] = maxz[i] = minz[0];

  inc = blockDim.x * gridDim.x;
  j = i + blockIdx.x * blockDim.x;

  // scan bodies
  while (j < nbodiesd) {
    tmp = posxd[j];
    minx[i] = min(minx[i], tmp);
    maxx[i] = max(maxx[i], tmp);

    tmp = posyd[j];
    miny[i] = min(miny[i], tmp);
    maxy[i] = max(maxy[i], tmp);

    tmp = poszd[j];
    minz[i] = min(minz[i], tmp);
    maxz[i] = max(maxz[i], tmp);

    j += inc;  // move on to next body
  }

  // reduction in shared memory
  j = blockDim.x >> 1;
  while (j > 0) {
    __syncthreads();
    if (i < j) {
      minx[i] = min(minx[i], minx[i+j]);
      miny[i] = min(miny[i], miny[i+j]);
      minz[i] = min(minz[i], minz[i+j]);

      maxx[i] = max(maxx[i], maxx[i+j]);
      maxy[i] = max(maxy[i], maxy[i+j]);
      maxz[i] = max(maxz[i], maxz[i+j]);
    }
    j >>= 1;
  }

  if (i == 0) {
    // write block result to global memory
    j = blockIdx.x;
    minxd[j] = minx[0];
    minyd[j] = miny[0];
    minzd[j] = minz[0];

    maxxd[j] = maxx[0];
    maxyd[j] = maxy[0];
    maxzd[j] = maxz[0];
    __threadfence();

    inc = gridDim.x - 1;
    if (inc == atomicInc((unsigned int *)&blkcntd, inc)) {
      // I'm the last block, so combine all block results
      for (j = 0; j <= inc; j++) {
        minx[0] = min(minx[0], minxd[j]);
        miny[0] = min(miny[0], minyd[j]);
        minz[0] = min(minz[0], minzd[j]);

        maxx[0] = max(maxx[0], maxxd[j]);
        maxy[0] = max(maxy[0], maxyd[j]);
        maxz[0] = max(maxz[0], maxzd[j]);
      }

      // compute radius
      tmp = max(maxx[0] - minx[0], maxy[0] - miny[0]);
      radiusd = max(tmp, maxz[0] - minz[0]) * 0.5f;

      // create root node
      j = nnodesd;
      massd[j] = -1.0f;
      startd[j] = 0;
      posxd[j] = (minx[0] + maxx[0]) * 0.5f;
      posyd[j] = (miny[0] + maxy[0]) * 0.5f;
      poszd[j] = (minz[0] + maxz[0]) * 0.5f;
#pragma unroll 8
      for (i = 0; i < 8; i++) childd[j*8+i] = -1;

      bottomd = j;
      stepd++;
    }
  }
}

// build tree
__global__ void TreeBuildingKernel(volatile float *posxd, volatile float *posyd, volatile float *poszd, volatile float *massd, volatile int *startd, volatile int *childd) {
  register int i, j, k, depth, localmaxdepth, skip, inc;
  register float x, y, z, r;
  register float px, py, pz;
  register int ch, n, cell, locked, patch;
  __shared__ float radius, rootx, rooty, rootz;

  i = threadIdx.x;
  if (i == 0) {
    // cache root data
    radius = radiusd;
    rootx = posxd[nnodesd];
    rooty = posyd[nnodesd];
    rootz = poszd[nnodesd];
  }
  __syncthreads();

  localmaxdepth = 1;
  skip = 1;
  inc = blockDim.x * gridDim.x;
  i += blockIdx.x * blockDim.x;

  // iterate over all bodies assigned to thread
  while (i < nbodiesd) {
    if (skip != 0) {
      // new body, so start traversing at root
      skip = 0;
      px = posxd[i];
      py = posyd[i];
      pz = poszd[i];
      n = nnodesd;
      depth = 1;
      r = radius;
      j = 0;
      // determine which child to follow
      if (rootx < px) j = 1;
      if (rooty < py) j += 2;
      if (rootz < pz) j += 4;
    }

    ch = childd[n*8+j];
    // follow path to leaf cell
    while (ch >= nbodiesd) {
      n = ch;
      depth++;
      r *= 0.5f;
      j = 0;
      // determine which child to follow
      if (posxd[n] < px) j = 1;
      if (posyd[n] < py) j += 2;
      if (poszd[n] < pz) j += 4;
      ch = childd[n*8+j];
    }

    if (ch != -2) {  // skip if child pointer is locked and try again later
      locked = n*8+j;
      if (ch == atomicCAS((int *)&childd[locked], ch, -2)) {  // try to lock
        if (ch == -1) {
          // if null, just insert the new body
          childd[locked] = i;
        } else {  // there already is a body in this position
          patch = -1;
          // create new cell(s) and insert the old and new body
          do {
            depth++;

            cell = atomicSub((int *)&bottomd, 1) - 1;
            if (cell <= nbodiesd) {
              errd = 1;
//              *errd = 1;
              bottomd = nnodesd;
            }
            patch = max(patch, cell);

            x = (j & 1) * r;
            y = ((j >> 1) & 1) * r;
            z = ((j >> 2) & 1) * r;
            r *= 0.5f;

            massd[cell] = -1.0f;
            startd[cell] = -1;
            x = posxd[cell] = posxd[n] - r + x;
            y = posyd[cell] = posyd[n] - r + y;
            z = poszd[cell] = poszd[n] - r + z;
#pragma unroll 8
            for (k = 0; k < 8; k++) childd[cell*8+k] = -1;

            if (patch != cell) { 
              childd[n*8+j] = cell;
            }

            j = 0;
            if (x < posxd[ch]) j = 1;
            if (y < posyd[ch]) j += 2;
            if (z < poszd[ch]) j += 4;
            childd[cell*8+j] = ch;

            n = cell;
            j = 0;
            if (x < px) j = 1;
            if (y < py) j += 2;
            if (z < pz) j += 4;

            ch = childd[n*8+j];
            // repeat until the two bodies are different children
          } while (ch >= 0);// end of do-while

          childd[n*8+j] = i;
          __threadfence();
          childd[locked] = patch;
        }// end else

        localmaxdepth = max(depth, localmaxdepth);
        i += inc;  // move on to next body
        skip = 1;
      } // end if (ch == atomicCAS...)
    } // end if (ch != -2)
    __syncthreads();
  } // end while (i < nbodiesd)
  atomicMax((int *)&maxdepthd, localmaxdepth);
}

// compute center of mass
__global__ void SummarizationKernel(volatile float *posxd, volatile float *posyd, volatile float *poszd, volatile float *massd, volatile int *childd, volatile int *countd) {
  register int i, j, k, ch, inc, missing, cnt;
  register float m, cm, px, py, pz;
  __shared__ volatile int bottom, child[THREADS3 * 8];

  if (0 == threadIdx.x) {
    bottom = bottomd;
  }
  __syncthreads();

  inc = blockDim.x * gridDim.x;
  k = (bottom & (-WARPSIZE)) + threadIdx.x + blockIdx.x * blockDim.x;  // align to warp size
  if (k < bottom) k += inc;

  missing = 0;
  // iterate over all cells assigned to thread
  while (k <= nnodesd) {
    if (missing == 0) {
      // new cell, so initialize
      cm = 0.0f;
      px = 0.0f;
      py = 0.0f;
      pz = 0.0f;
      cnt = 0;
      j = 0;
#pragma unroll 8
      for (i = 0; i < 8; i++) {
        ch = childd[k*8+i];
        if (ch >= 0) {
          if (i != j) {
            // move children to front (needed later for speed)
            childd[k*8+i] = -1;
            childd[k*8+j] = ch;
          }
          child[missing*THREADS3+threadIdx.x] = ch;  // cache missing children
          m = massd[ch];
          missing++;
          if (m >= 0.0f) {
            // child is ready
            missing--;
            if (ch >= nbodiesd) {  // count bodies (needed later)
              cnt += countd[ch] - 1;
            }
            // add child's contribution
            cm += m;
            px += posxd[ch] * m;
            py += posyd[ch] * m;
            pz += poszd[ch] * m;
          }
          j++;
        }
      }
      cnt += j;
    }

    if (missing != 0) {
      do {
        // poll missing child
        ch = child[(missing-1)*THREADS3+threadIdx.x];
        m = massd[ch];
        if (m >= 0.0f) {
          // child is now ready
          missing--;
          if (ch >= nbodiesd) {
            // count bodies (needed later)
            cnt += countd[ch] - 1;
          }
          // add child's contribution
          cm += m;
          px += posxd[ch] * m;
          py += posyd[ch] * m;
          pz += poszd[ch] * m;
        }
        // repeat until we are done or child is not ready
      } while ((m >= 0.0f) && (missing != 0));
    }

    if (missing == 0) {
      // all children are ready, so store computed information
      countd[k] = cnt;
      m = 1.0f / cm;
      posxd[k] = px * m;
      posyd[k] = py * m;
      poszd[k] = pz * m;
      __threadfence();
      massd[k] = cm;
      k += inc;  // move on to next cell
    }
  }
}

// sort bodies
__global__ void SortKernel(volatile int *startd, volatile int *childd, volatile int *countd, volatile int *sortd) {
  register int i, k, ch, dec, start, bottom;
  __shared__ int bottoms;

  if (0 == threadIdx.x) {
    bottoms = bottomd;
  }
  __syncthreads();
  bottom = bottoms;

  dec = blockDim.x * gridDim.x;
  k = nnodesd + 1 - dec + threadIdx.x + blockIdx.x * blockDim.x;

  // iterate over all cells assigned to thread
  while (k >= bottom) {
    start = startd[k];
    if (start >= 0) {
#pragma unroll 8
      for (i = 0; i < 8; i++) {
        ch = childd[k*8+i];
        if (ch >= nbodiesd) {
          // child is a cell
          startd[ch] = start;  // set start ID of child
          start += countd[ch];  // add #bodies in subtree
        } else if (ch >= 0) {
          // child is a body
          sortd[start] = ch;  // record body in sorted array
          start++;
        }
      }
      k -= dec;  // move on to next cell
    }
  }
}

// compute force
__global__ void ForceCalculationKernel(volatile float *posxd, volatile float *posyd, volatile float *poszd, volatile float *accxd, volatile float *accyd, volatile float *acczd, volatile float *velxd, volatile float *velyd, volatile float *velzd, volatile float *massd, volatile int *childd, volatile int *sortd) {
  register int i, j, k, n, depth, base, sbase, diff;
  register float px, py, pz, ax, ay, az, dx, dy, dz, tmp;
  __shared__ int step, maxdepth;
  __shared__ int ch[THREADS5/WARPSIZE];
  __shared__ volatile int pos[MAXDEPTH * THREADS5/WARPSIZE], node[MAXDEPTH * THREADS5/WARPSIZE];
  __shared__ volatile float dq[MAXDEPTH * THREADS5/WARPSIZE];
  __shared__ volatile float nx[THREADS5/WARPSIZE], ny[THREADS5/WARPSIZE], nz[THREADS5/WARPSIZE], nm[THREADS5/WARPSIZE];

  if (0 == threadIdx.x) {
    step = stepd;
    maxdepth = maxdepthd;
    tmp = radiusd;
    // precompute values that depend only on tree level
    dq[0] = tmp * tmp * itolsqd;
    for (i = 1; i < maxdepth; i++) {
      dq[i] = dq[i - 1] * 0.25f;
    }

    if (maxdepth > MAXDEPTH) {
      errd = maxdepth;
//      *errd = maxdepth;
    }
  }
  __syncthreads();

  if (maxdepth <= MAXDEPTH) {
    // figure out first thread in each warp
    base = threadIdx.x / WARPSIZE;
    sbase = base * WARPSIZE;
    j = base * MAXDEPTH;

    diff = threadIdx.x - sbase;
    // make multiple copies to avoid index calculations later
    if (diff < MAXDEPTH) {
      dq[diff+j] = dq[diff];
    }
    __syncthreads();

    // iterate over all bodies assigned to thread
    for (k = threadIdx.x + blockIdx.x * blockDim.x; k < nbodiesd; k += blockDim.x * gridDim.x) {
      i = sortd[k];  // get permuted index
      // cache position info
      px = posxd[i];
      py = posyd[i];
      pz = poszd[i];

      ax = 0.0f;
      ay = 0.0f;
      az = 0.0f;

      // initialize iteration stack, i.e., push root node onto stack
      depth = j;
      if (sbase == threadIdx.x) {
        node[j] = nnodesd;
        pos[j] = 0;
      }
      __threadfence_block();

      while (depth >= j) {
        // stack is not empty
        while (pos[depth] < 8) {
          // node on top of stack has more children to process
          if (sbase == threadIdx.x) {
            // I'm the first thread in the warp
            n = childd[node[depth]*8+pos[depth]];  // load child pointer
            pos[depth]++;
            ch[base] = n;  // cache child pointer
            if (n >= 0) {
              // cache position and mass
              nx[base] = posxd[n];
              ny[base] = posyd[n];
              nz[base] = poszd[n];
              nm[base] = massd[n];
            }
          }
          __threadfence_block();
          // all threads retrieve cached data
          n = ch[base];
          if (n >= 0) {
            dx = nx[base] - px;
            dy = ny[base] - py;
            dz = nz[base] - pz;
            tmp = dx*dx + dy*dy + dz*dz;  // compute distance squared
            if ((n < nbodiesd) || __all(tmp >= dq[depth])) {  // check if all threads agree that cell is far enough away (or is a body)
              if (n != i) {
                tmp = rsqrtf(tmp + epssqd);  // compute distance
                tmp = nm[base] * tmp * tmp * tmp;
                ax += dx * tmp;
                ay += dy * tmp;
                az += dz * tmp;
              }
            } else {
              // push cell onto stack
              depth++;
              if (sbase == threadIdx.x) {
                node[depth] = n;
                pos[depth] = 0;
              }
              __threadfence_block();
            }
          } else {
            depth = max(j, depth - 1);  // early out because all remaining children are also zero
          }
        }
        depth--;  // done with this level
      }

      if (step > 0) {
        velxd[i] += (ax - accxd[i]) * dthfd;
        velyd[i] += (ay - accyd[i]) * dthfd;
        velzd[i] += (az - acczd[i]) * dthfd;
      }

      // save computed acceleration
      accxd[i] = ax;
      accyd[i] = ay;
      acczd[i] = az;
    }
  }
}

// advance bodies
__global__ void IntegrationKernel(volatile float *posxd, volatile float *posyd, volatile float *poszd, volatile float *accxd, volatile float *accyd, volatile float *acczd, volatile float *velxd, volatile float *velyd, volatile float *velzd) {
  register int i, inc;
  register float dvelx, dvely, dvelz;
  register float velhx, velhy, velhz;

  inc = blockDim.x * gridDim.x;
  // iterate over all bodies assigned to thread
  for (i = threadIdx.x + blockIdx.x * blockDim.x; i < nbodiesd; i += inc) {
    // integrate
    dvelx = accxd[i] * dthfd;
    dvely = accyd[i] * dthfd;
    dvelz = acczd[i] * dthfd;

    velhx = velxd[i] + dvelx;
    velhy = velyd[i] + dvely;
    velhz = velzd[i] + dvelz;

    posxd[i] += velhx * dtimed;
    posyd[i] += velhy * dtimed;
    poszd[i] += velhz * dtimed;

    velxd[i] = velhx + dvelx;
    velyd[i] = velhy + dvely;
    velzd[i] = velhz + dvelz;
  }
}

/*
static void debugDump() {
   // host copy for fast debug purpose
   int bottomh, maxdepthh, nnodesh, nbodiesh;
   int *childh; 
   float *posxh, *posyh, *poszh;

   cudaMemcpyFromSymbol(&bottomh, bottomd, sizeof(int));
   cudaMemcpyFromSymbol(&nnodesh, nnodesd, sizeof(int));
   cudaMemcpyFromSymbol(&nbodiesh, nbodiesd, sizeof(int));
   cudaMemcpyFromSymbol(&maxdepthh, maxdepthd, sizeof(int));
   fprintf(stdout, "buttomd = %d\n", bottomh); 
   fprintf(stdout, "nnodesd = %d\n", nnodesh); 
   fprintf(stdout, "nbodiesd = %d\n", nbodiesh); 
   fprintf(stdout, "maxdepthd = %d\n", maxdepthh); 
   childh = (int*) malloc(sizeof(int) * (nnodesh+1) * 8); 
   posxh = (float*) malloc(sizeof(float) * (nnodesh+1)); 
   posyh = (float*) malloc(sizeof(float) * (nnodesh+1)); 
   poszh = (float*) malloc(sizeof(float) * (nnodesh+1)); 
   int *childl;
   int *posxl, *posyl, *poszl; 
   cudaMemcpyFromSymbol(&childl, childd, sizeof(int*));
   CudaTest("DebugDump obtain childd\n"); 
   cudaMemcpyFromSymbol(&posxl, posxd, sizeof(int*));
   cudaMemcpyFromSymbol(&posyl, posyd, sizeof(int*));
   cudaMemcpyFromSymbol(&poszl, poszd, sizeof(int*));
   cudaMemcpy(childh, childl, sizeof(int) * (nnodesh+1) * 8, cudaMemcpyDeviceToHost);
   cudaMemcpy(posxh, posxl, sizeof(float) * (nnodesh+1), cudaMemcpyDeviceToHost);
   cudaMemcpy(posyh, posyl, sizeof(float) * (nnodesh+1), cudaMemcpyDeviceToHost);
   cudaMemcpy(poszh, poszl, sizeof(float) * (nnodesh+1), cudaMemcpyDeviceToHost);
   CudaTest("DebugDump copyback\n"); 
   
   // depth first traversal of tree
   fprintf(stdout, "octree in DFS traversal:\n"); 
   int *stack = (int*) malloc(sizeof(int) * (nnodesh+1) * 8); 
   int *treedepth = (int*) malloc(sizeof(int) * (nnodesh+1) * 8); 
   stack[0] = nnodesh; 
   treedepth[0] = 0; 
   int stack_top = 0; 
   while (stack_top >= 0) {
      int node = stack[stack_top]; 
      int depth = treedepth[stack_top]; 
      stack_top--; 

      int nchild = 0; 
      for (int c = 0; c < 8; c++) {
         int childnode = (childh[8 * node + c]); 
         if (childnode >= 0 && childnode < nbodiesh) {
            // print leaf node 
            fprintf(stdout, "   %d %2d %d \n", childnode, depth + 1, c); 
            // fprintf(stdout, "   %d %2d %d:%d %p\n", childnode, depth + 1, node, c, &(childl[8 * node + c])); 
         } else if (childnode != -1) {
            nchild += 1; 
            stack_top++; 
            stack[stack_top] = childnode; 
            treedepth[stack_top] = depth + 1; 
            // fprintf(stdout, " b %d %2d %d:%d %p\n", childnode, depth + 1, node, c, &(childl[8 * node + c])); 
            // if (depth <= 1) 
            //    fprintf(stdout, "treenode: %d %d [%f %f %f]\n", 
            //            childnode, depth + 1, posxh[childnode] ,posyh[childnode], poszh[childnode]); 
         }
      }
   }
   fprintf(stdout, "\n");
   exit(0);
}
*/

int main(int argc, char *argv[]) {
  register int i, run, blocks;
  register int nnodes, nbodies, step, timesteps;
  int error;
  register float dtime, dthf, epssq, itolsq;
  float *mass;
  float *posx, *posy, *posz;
  float *velx, *vely, *velz;
  int *errl;
  int *sortl, *childl, *countl, *startl;
  float *massl;
  float *posxl, *posyl, *poszl;
  float *velxl, *velyl, *velzl;
  float *accxl, *accyl, *acczl;
  float *maxxl, *maxyl, *maxzl;
  float *minxl, *minyl, *minzl;
  register double rsc, vsc, r, v, x, y, z, sq, scale;

  printf("[BENCH] CUDA BarnesHut\n");
  if (argc != 3) {
    fprintf(stderr, "\n");
    fprintf(stderr, "arguments: number_of_bodies number_of_timesteps\n");
    exit(-1);
  }
/*
  int deviceCount;
  cudaGetDeviceCount(&deviceCount);
  if (deviceCount == 0) {
    fprintf(stderr, "There is no device supporting CUDA\n");
    exit(-1);
  }
*/
  cudaDeviceProp deviceProp;
  cudaGetDeviceProperties(&deviceProp, 0);
/*
  if ((deviceProp.major == 9999) && (deviceProp.minor == 9999)) {
    fprintf(stderr, "There is no CUDA capable device\n");
    exit(-1);
  }
  if ((deviceProp.major < 1) || ((deviceProp.major == 1) && (deviceProp.minor < 2))) {
    fprintf(stderr, "Need at least compute capability 1.2\n");
    exit(-1);
  }
  if (deviceProp.warpSize != WARPSIZE) {
    fprintf(stderr, "Warp size must be %d\n", deviceProp.warpSize);
    exit(-1);
  }
  if (deviceProp.warpSize != WARPSIZE) {
    fprintf(stderr, "Warp size must be %d\n", deviceProp.warpSize);
    exit(-1);
  }
*/
  blocks = deviceProp.multiProcessorCount;
  printf("[BENCH] blocks = %d\n", blocks);
/*
  if ((WARPSIZE <= 0) || (WARPSIZE & (WARPSIZE-1) != 0)) {
    fprintf(stderr, "Warp size must be greater than zero and a power of two\n");
    exit(-1);
  }
  if (WARPSIZE < MAXDEPTH) {
    fprintf(stderr, "Warp size must be greater than or equal to MAXDEPTH\n");
    exit(-1);
  }
  if ((THREADS0 <= 0) || ((THREADS0 & (WARPSIZE-1)) != 0)) {
    fprintf(stderr, "THREADS0 must be greater than zero and an integer multiple of the warp size\n");
    exit(-1);
  }
  if ((THREADS1 <= 0) || ((THREADS1 & (WARPSIZE-1)) != 0) || ((THREADS1 & (THREADS1-1)) != 0)) {
    fprintf(stderr, "THREADS1 must be greater than zero, an integer multiple of the warp size, and a power of two\n");
    exit(-1);
  }
  if ((THREADS2 <= 0) || ((THREADS2 & (WARPSIZE-1)) != 0)) {
    fprintf(stderr, "THREADS2 must be greater than zero and an integer multiple of the warp size\n");
    exit(-1);
  }
  if ((THREADS3 <= 0) || ((THREADS3 & (WARPSIZE-1)) != 0)) {
    fprintf(stderr, "THREADS3 must be greater than zero and an integer multiple of the warp size\n");
    exit(-1);
  }
  if ((THREADS4 <= 0) || ((THREADS4 & (WARPSIZE-1)) != 0)) {
    fprintf(stderr, "THREADS4 must be greater than zero and an integer multiple of the warp size\n");
    exit(-1);
  }
  if ((THREADS5 <= 0) || ((THREADS5 & (WARPSIZE-1)) != 0)) {
    fprintf(stderr, "THREADS5 must be greater than zero and an integer multiple of the warp size\n");
    exit(-1);
  }
  if ((THREADS6 <= 0) || ((THREADS6 & (WARPSIZE-1)) != 0)) {
    fprintf(stderr, "THREADS6 must be greater than zero and an integer multiple of the warp size\n");
    exit(-1);
  }
*/

  cudaGetLastError();  // reset error value
  for (run = 0; run < 1; run++) {
//    for (i = 0; i < 7; i++) timing[i] = 0.0f;
    nbodies = atoi(argv[1]);
    if (nbodies < 1) {
      fprintf(stderr, "nbodies is too small: %d\n", nbodies);
      exit(-1);
    }
    if (nbodies > (1 << 30)) {
      fprintf(stderr, "nbodies is too large: %d\n", nbodies);
      exit(-1);
    }
    nnodes = nbodies * 2;
    if (nnodes < 1024*blocks) nnodes = 1024*blocks;
    while ((nnodes & (WARPSIZE-1)) != 0) nnodes++;
    nnodes--;
    timesteps = atoi(argv[2]);
    dtime = 0.025;
    dthf = dtime * 0.5f;
    epssq = 0.05 * 0.05;
    itolsq = 1.0f / (0.5 * 0.5);

    // allocate memory
    if (run == 0) {
      fprintf(stderr, "[BENCH] nodes = %d\n", nnodes+1);
      fprintf(stderr, "[BENCH] configuration: %d bodies, %d time steps\n", nbodies, timesteps);

      mass = (float *)malloc(sizeof(float) * nbodies);
      if (mass == NULL) {fprintf(stderr, "cannot allocate mass\n");  exit(-1);}
      posx = (float *)malloc(sizeof(float) * nbodies);
      if (posx == NULL) {fprintf(stderr, "cannot allocate posx\n");  exit(-1);}
      posy = (float *)malloc(sizeof(float) * nbodies);
      if (posy == NULL) {fprintf(stderr, "cannot allocate posy\n");  exit(-1);}
      posz = (float *)malloc(sizeof(float) * nbodies);
      if (posz == NULL) {fprintf(stderr, "cannot allocate posz\n");  exit(-1);}
      velx = (float *)malloc(sizeof(float) * nbodies);
      if (velx == NULL) {fprintf(stderr, "cannot allocate velx\n");  exit(-1);}
      vely = (float *)malloc(sizeof(float) * nbodies);
      if (vely == NULL) {fprintf(stderr, "cannot allocate vely\n");  exit(-1);}
      velz = (float *)malloc(sizeof(float) * nbodies);
      if (velz == NULL) {fprintf(stderr, "cannot allocate velz\n");  exit(-1);}

      int int_size = (nnodes+1)*sizeof(int);
      int flt_size = (nnodes+1)*sizeof(float);
      CUDA_SAFE_CALL(cudaMalloc((void **)&errl, sizeof(int)));
      CUDA_SAFE_CALL(cudaMalloc((void **)&childl, 8*int_size));
      CUDA_SAFE_CALL(cudaMalloc((void **)&massl, flt_size));
      CUDA_SAFE_CALL(cudaMalloc((void **)&posxl, flt_size));
      CUDA_SAFE_CALL(cudaMalloc((void **)&posyl, flt_size));
      CUDA_SAFE_CALL(cudaMalloc((void **)&poszl, flt_size));
      CUDA_SAFE_CALL(cudaMalloc((void **)&countl, int_size));
      CUDA_SAFE_CALL(cudaMalloc((void **)&startl, int_size));

      cudaMemset(childl, 0, 8*int_size);

      // alias arrays
      int inc = (nbodies + WARPSIZE - 1) & (-WARPSIZE);
      velxl = (float *)&childl[0*inc];
      velyl = (float *)&childl[1*inc];
      velzl = (float *)&childl[2*inc];
      accxl = (float *)&childl[3*inc];
      accyl = (float *)&childl[4*inc];
      acczl = (float *)&childl[5*inc];
      sortl = (int *)&childl[6*inc];

      CUDA_SAFE_CALL(cudaMalloc((void **)&maxxl, sizeof(float) * blocks));
      CUDA_SAFE_CALL(cudaMalloc((void **)&maxyl, sizeof(float) * blocks));
      CUDA_SAFE_CALL(cudaMalloc((void **)&maxzl, sizeof(float) * blocks));
      CUDA_SAFE_CALL(cudaMalloc((void **)&minxl, sizeof(float) * blocks));
      CUDA_SAFE_CALL(cudaMalloc((void **)&minyl, sizeof(float) * blocks));
      CUDA_SAFE_CALL(cudaMalloc((void **)&minzl, sizeof(float) * blocks));

      CUDA_SAFE_CALL(cudaMemcpyToSymbol(nnodesd, &nnodes, sizeof(int)));
      CUDA_SAFE_CALL(cudaMemcpyToSymbol(nbodiesd, &nbodies, sizeof(int)));
      CUDA_SAFE_CALL(cudaMemcpyToSymbol(dtimed, &dtime, sizeof(float)));
      CUDA_SAFE_CALL(cudaMemcpyToSymbol(dthfd, &dthf, sizeof(float)));
      CUDA_SAFE_CALL(cudaMemcpyToSymbol(epssqd, &epssq, sizeof(float)));
      CUDA_SAFE_CALL(cudaMemcpyToSymbol(itolsqd, &itolsq, sizeof(float)));
//      CUDA_SAFE_CALL(cudaMemcpyToSymbol(errd, &errl, sizeof(int)));
/*
      CUDA_SAFE_CALL(cudaMemcpyToSymbol(sortd, &sortl, sizeof(int)));
      CUDA_SAFE_CALL(cudaMemcpyToSymbol(countd, &countl, sizeof(int)));
      CUDA_SAFE_CALL(cudaMemcpyToSymbol(startd, &startl, sizeof(int)));
      CUDA_SAFE_CALL(cudaMemcpyToSymbol(childd, &childl, sizeof(int)));
      CUDA_SAFE_CALL(cudaMemcpyToSymbol(massd, &massl, sizeof(int)));
      CUDA_SAFE_CALL(cudaMemcpyToSymbol(posxd, &posxl, sizeof(int)));
      CUDA_SAFE_CALL(cudaMemcpyToSymbol(posyd, &posyl, sizeof(int)));
      CUDA_SAFE_CALL(cudaMemcpyToSymbol(poszd, &poszl, sizeof(int)));
      CUDA_SAFE_CALL(cudaMemcpyToSymbol(velxd, &velxl, sizeof(int)));
      CUDA_SAFE_CALL(cudaMemcpyToSymbol(velyd, &velyl, sizeof(int)));
      CUDA_SAFE_CALL(cudaMemcpyToSymbol(velzd, &velzl, sizeof(int)));
      CUDA_SAFE_CALL(cudaMemcpyToSymbol(accxd, &accxl, sizeof(int)));
      CUDA_SAFE_CALL(cudaMemcpyToSymbol(accyd, &accyl, sizeof(int)));
      CUDA_SAFE_CALL(cudaMemcpyToSymbol(acczd, &acczl, sizeof(int)));
      CUDA_SAFE_CALL(cudaMemcpyToSymbol(maxxd, &maxxl, sizeof(int)));
      CUDA_SAFE_CALL(cudaMemcpyToSymbol(maxyd, &maxyl, sizeof(int)));
      CUDA_SAFE_CALL(cudaMemcpyToSymbol(maxzd, &maxzl, sizeof(int)));
      CUDA_SAFE_CALL(cudaMemcpyToSymbol(minxd, &minxl, sizeof(int)));
      CUDA_SAFE_CALL(cudaMemcpyToSymbol(minyd, &minyl, sizeof(int)));
      CUDA_SAFE_CALL(cudaMemcpyToSymbol(minzd, &minzl, sizeof(int)));
*/
    }
    // generate input
    drndset(7);
    rsc = (3 * M_PI) / 16;
    vsc = sqrt(1.0 / rsc);
    for (i = 0; i < nbodies; i++) {
      mass[i] = 1.0 / nbodies;
      r = 1.0 / sqrt(pow(drnd()*0.999, -2.0/3.0) - 1);
      do {
        x = drnd()*2.0 - 1.0;
        y = drnd()*2.0 - 1.0;
        z = drnd()*2.0 - 1.0;
        sq = x*x + y*y + z*z;
      } while (sq > 1.0);
      scale = rsc * r / sqrt(sq);
      posx[i] = x * scale;
      posy[i] = y * scale;
      posz[i] = z * scale;

      do {
        x = drnd();
        y = drnd() * 0.1;
      } while (y > x*x * pow(1 - x*x, 3.5));
      v = x * sqrt(2.0 / sqrt(1 + r*r));
      do {
        x = drnd()*2.0 - 1.0;
        y = drnd()*2.0 - 1.0;
        z = drnd()*2.0 - 1.0;
        sq = x*x + y*y + z*z;
      } while (sq > 1.0);
      scale = vsc * v / sqrt(sq);
      velx[i] = x * scale;
      vely[i] = y * scale;
      velz[i] = z * scale;
    }

    CUDA_SAFE_CALL(cudaMemcpy(massl, mass, sizeof(float) * nbodies, cudaMemcpyHostToDevice));
    CUDA_SAFE_CALL(cudaMemcpy(posxl, posx, sizeof(float) * nbodies, cudaMemcpyHostToDevice));
    CUDA_SAFE_CALL(cudaMemcpy(posyl, posy, sizeof(float) * nbodies, cudaMemcpyHostToDevice));
    CUDA_SAFE_CALL(cudaMemcpy(poszl, posz, sizeof(float) * nbodies, cudaMemcpyHostToDevice));
    CUDA_SAFE_CALL(cudaMemcpy(velxl, velx, sizeof(float) * nbodies, cudaMemcpyHostToDevice));
    CUDA_SAFE_CALL(cudaMemcpy(velyl, vely, sizeof(float) * nbodies, cudaMemcpyHostToDevice));
    CUDA_SAFE_CALL(cudaMemcpy(velzl, velz, sizeof(float) * nbodies, cudaMemcpyHostToDevice));

    printf("[BENCH] lauch GPU kernels\n");
//    InitializationKernel<<<blocks*FACTOR0, THREADS0>>>();
    CUT_CHECK_ERROR("InitializationKernel execution failed")
//    CudaTest("InitializationKernel ERROR");
    for (step = 0; step < timesteps; step++) {
      BoundingBoxKernel<<<blocks*FACTOR1, THREADS1>>>(posxl, posyl, poszl, maxxl, maxyl, maxzl, minxl, minyl, minzl, massl, startl, childl);
      CUT_CHECK_ERROR("BoundingBoxKernel execution failed")
      TreeBuildingKernel<<<blocks*FACTOR2, THREADS2>>>(posxl, posyl, poszl, massl, startl, childl);
      CUT_CHECK_ERROR("TreeBuildingKernel execution failed")
      SummarizationKernel<<<blocks*FACTOR3, THREADS3>>>(posxl, posyl, poszl, massl, childl, countl);
      CUT_CHECK_ERROR("SummarizationKernel execution failed")
      SortKernel<<<blocks*FACTOR4, 512>>>(startl, childl, countl, sortl);
      CUT_CHECK_ERROR("SortKernel execution failed")
      ForceCalculationKernel<<<blocks*FACTOR5, THREADS5>>>(posxl, posyl, poszl, accxl, accyl, acczl, velxl, velyl, velzl, massl, childl, sortl);
      CUT_CHECK_ERROR("ForceCalculationKernel execution failed")
      IntegrationKernel<<<blocks*FACTOR6, THREADS6>>>(posxl, posyl, poszl, accxl, accyl, acczl, velxl, velyl, velzl);
      CUT_CHECK_ERROR("IntegrationKernel execution failed")
    }
    printf("[BENCH] GPU kernels finished\n");

    // transfer result back to CPU
    CUDA_SAFE_CALL(cudaMemcpy(&error, errl, sizeof(int), cudaMemcpyDeviceToHost));
    CUDA_SAFE_CALL(cudaMemcpy(posx, posxl, sizeof(float) * nbodies, cudaMemcpyDeviceToHost));
    CUDA_SAFE_CALL(cudaMemcpy(posy, posyl, sizeof(float) * nbodies, cudaMemcpyDeviceToHost));
    CUDA_SAFE_CALL(cudaMemcpy(posz, poszl, sizeof(float) * nbodies, cudaMemcpyDeviceToHost));
    CUDA_SAFE_CALL(cudaMemcpy(velx, velxl, sizeof(float) * nbodies, cudaMemcpyDeviceToHost));
    CUDA_SAFE_CALL(cudaMemcpy(vely, velyl, sizeof(float) * nbodies, cudaMemcpyDeviceToHost));
    CUDA_SAFE_CALL(cudaMemcpy(velz, velzl, sizeof(float) * nbodies, cudaMemcpyDeviceToHost));
  }

  // print output
  FILE * fp = fopen("out.txt", "w");
  for (i = 0; i < nbodies; i++) {
    fprintf(fp, "%.2e %.2e %.2e\n", posx[i], posy[i], posz[i]);
  }
  fclose(fp);
  return 0;
}
