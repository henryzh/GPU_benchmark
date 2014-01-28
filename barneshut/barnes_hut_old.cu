/*
CUDA BarnesHut v1.1: Simulation of the gravitational forces
in a galactic cluster using the Barnes-Hut n-body algorithm
Copyright (c) 2010 The University of Texas at Austin
Author: Dr. Martin Burtscher
*/


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


/************************************************************************************/

// input generation

#define MULT 1103515245
#define ADD 12345
#define MASK 0x7FFFFFFF
#define TWOTO31 2147483648.0

static int A = 1;
static int B = 0;
static int randx = 1;
static int lastrand;


static void drndset(int seed)
{
   A = 1;
   B = 0;
   randx = (A * seed + B) & MASK;
   A = (MULT * A) & MASK;
   B = (MULT * B + ADD) & MASK;
}


static double drnd()
{
   lastrand = randx;
   randx = (A * randx + B) & MASK;
   return (double)lastrand / TWOTO31;
}


/************************************************************************************/

// childd is aliased with velxd, velyd, velzd, accxd, accyd, acczd, and sortd but they never use the same memory locations
__constant__ volatile int nnodesd, nbodiesd, *errd, *sortd, *childd, *countd, *startd;
__constant__ volatile float dtimed, dthfd, epssqd, itolsqd;
__constant__ volatile float *massd, *posxd, *posyd, *poszd, *velxd, *velyd, *velzd, *accxd, *accyd, *acczd;
__constant__ volatile float *maxxd, *maxyd, *maxzd, *minxd, *minyd, *minzd;

__device__ volatile int stepd, bottomd, maxdepthd;
__device__ volatile unsigned int blkcntd;
__device__ volatile float radiusd;


/************************************************************************************/
/*** initialize memory **************************************************************/
/************************************************************************************/

__global__ void InitializationKernel() {
  int i, inc;
  i = threadIdx.x + blockIdx.x * blockDim.x;
  if (i == 0) {
    *errd = 0;
    stepd = -1;
    maxdepthd = 1;
    blkcntd = 0;
  }
  inc = blockDim.x * gridDim.x;
  for (; i < nbodiesd; i += inc) {
    accxd[i] = 0.0f;
    accyd[i] = 0.0f;
    acczd[i] = 0.0f;
  }
}


/******************************************************************************/
/*** compute center and radius ************************************************/
/******************************************************************************/
__global__ void BoundingBoxKernel() {
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


/******************************************************************************/
/*** build tree ***************************************************************/
/******************************************************************************/
__global__ void TreeBuildingKernel() {
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
              *errd = 1;
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
          } while (ch >= 0);
          childd[n*8+j] = i;
          __threadfence();
          childd[locked] = patch;
        }

        localmaxdepth = max(depth, localmaxdepth);
        i += inc;  // move on to next body
        skip = 1;
      }
    }
    __syncthreads();
  }
  atomicMax((int *)&maxdepthd, localmaxdepth);
}


/******************************************************************************/
/*** compute center of mass ***************************************************/
/******************************************************************************/
__global__ void SummarizationKernel() {
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


/******************************************************************************/
/*** sort bodies **************************************************************/
/******************************************************************************/
__global__ void SortKernel() {
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


/******************************************************************************/
/*** compute force ************************************************************/
/******************************************************************************/
__global__ void ForceCalculationKernel() {
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
      *errd = maxdepth;
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


/******************************************************************************/
/*** advance bodies ***********************************************************/
/******************************************************************************/
__global__ void IntegrationKernel() {
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


/******************************************************************************/
static void CudaTest(char *msg) {
  cudaError_t e;
  cudaThreadSynchronize();
  if (cudaSuccess != (e = cudaGetLastError())) {
    fprintf(stderr, "%s: %d\n", msg, e);
    fprintf(stderr, "%s\n", cudaGetErrorString(e));
    exit(-1);
  }
}

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

/******************************************************************************/
int main(int argc, char *argv[]) {
  register int i, run, blocks;
  register int nnodes, nbodies, step, timesteps;
  //register int runtime, mintime;
  int error;
  register float dtime, dthf, epssq, itolsq;
  //float time, timing[7];
  //clock_t starttime, endtime;
  //cudaEvent_t start, stop;
  float *mass, *posx, *posy, *posz, *velx, *vely, *velz;
  int *errl, *sortl, *childl, *countl, *startl;
  float *massl;
  float *posxl, *posyl, *poszl;
  float *velxl, *velyl, *velzl;
  float *accxl, *accyl, *acczl;
  float *maxxl, *maxyl, *maxzl;
  float *minxl, *minyl, *minzl;
  register double rsc, vsc, r, v, x, y, z, sq, scale;

  // perform some checks
  printf("[BENCH] CUDA BarnesHut\n");
  if (argc != 3) {
    fprintf(stderr, "\n");
    fprintf(stderr, "arguments: number_of_bodies number_of_timesteps\n");
    exit(-1);
  }

  int deviceCount;
  cudaGetDeviceCount(&deviceCount);
  if (deviceCount == 0) {
    fprintf(stderr, "There is no device supporting CUDA\n");
    exit(-1);
  }
  cudaDeviceProp deviceProp;
  cudaGetDeviceProperties(&deviceProp, 0);
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

  blocks = deviceProp.multiProcessorCount;
  printf("numBlocks = %d\n", blocks);

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
  if ((THREADS5 <= 0) || ((THREADS5 & (WARPSIZE-1)) != 0)) {  /* must be a multiple of the warp size */
    fprintf(stderr, "THREADS5 must be greater than zero and an integer multiple of the warp size\n");
    exit(-1);
  }
  if ((THREADS6 <= 0) || ((THREADS6 & (WARPSIZE-1)) != 0)) {
    fprintf(stderr, "THREADS6 must be greater than zero and an integer multiple of the warp size\n");
    exit(-1);
  }

  cudaGetLastError();  // reset error value
  for (run = 0; run < 1; run++) {
    //for (i = 0; i < 7; i++) timing[i] = 0.0f;

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
    dtime = 0.025;  dthf = dtime * 0.5f;
    epssq = 0.05 * 0.05;
    itolsq = 1.0f / (0.5 * 0.5);

    // allocate memory
    if (run == 0) {
      fprintf(stderr, "nodes = %d\n", nnodes+1);
      fprintf(stderr, "configuration: %d bodies, %d time steps\n", nbodies, timesteps);

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

      if (cudaSuccess != cudaMalloc((void **)&errl, sizeof(int))) fprintf(stderr, "could not allocate errd\n");  CudaTest("couldn't allocate errd");
      if (cudaSuccess != cudaMalloc((void **)&childl, sizeof(int) * (nnodes+1) * 8)) fprintf(stderr, "could not allocate childd\n");  CudaTest("couldn't allocate childd");
      if (cudaSuccess != cudaMalloc((void **)&massl, sizeof(float) * (nnodes+1))) fprintf(stderr, "could not allocate massd\n");  CudaTest("couldn't allocate massd");
      if (cudaSuccess != cudaMalloc((void **)&posxl, sizeof(float) * (nnodes+1))) fprintf(stderr, "could not allocate posxd\n");  CudaTest("couldn't allocate posxd");
      if (cudaSuccess != cudaMalloc((void **)&posyl, sizeof(float) * (nnodes+1))) fprintf(stderr, "could not allocate posyd\n");  CudaTest("couldn't allocate posyd");
      if (cudaSuccess != cudaMalloc((void **)&poszl, sizeof(float) * (nnodes+1))) fprintf(stderr, "could not allocate poszd\n");  CudaTest("couldn't allocate poszd");
      if (cudaSuccess != cudaMalloc((void **)&countl, sizeof(int) * (nnodes+1))) fprintf(stderr, "could not allocate countd\n");  CudaTest("couldn't allocate countd");
      if (cudaSuccess != cudaMalloc((void **)&startl, sizeof(int) * (nnodes+1))) fprintf(stderr, "could not allocate startd\n");  CudaTest("couldn't allocate startd");

      // alias arrays
      int inc = (nbodies + WARPSIZE - 1) & (-WARPSIZE);
      velxl = (float *)&childl[0*inc];
      velyl = (float *)&childl[1*inc];
      velzl = (float *)&childl[2*inc];
      accxl = (float *)&childl[3*inc];
      accyl = (float *)&childl[4*inc];
      acczl = (float *)&childl[5*inc];
      sortl = (int *)&childl[6*inc];

      if (cudaSuccess != cudaMalloc((void **)&maxxl, sizeof(float) * blocks)) fprintf(stderr, "could not allocate maxxd\n");  CudaTest("couldn't allocate maxxd");
      if (cudaSuccess != cudaMalloc((void **)&maxyl, sizeof(float) * blocks)) fprintf(stderr, "could not allocate maxyd\n");  CudaTest("couldn't allocate maxyd");
      if (cudaSuccess != cudaMalloc((void **)&maxzl, sizeof(float) * blocks)) fprintf(stderr, "could not allocate maxzd\n");  CudaTest("couldn't allocate maxzd");
      if (cudaSuccess != cudaMalloc((void **)&minxl, sizeof(float) * blocks)) fprintf(stderr, "could not allocate minxd\n");  CudaTest("couldn't allocate minxd");
      if (cudaSuccess != cudaMalloc((void **)&minyl, sizeof(float) * blocks)) fprintf(stderr, "could not allocate minyd\n");  CudaTest("couldn't allocate minyd");
      if (cudaSuccess != cudaMalloc((void **)&minzl, sizeof(float) * blocks)) fprintf(stderr, "could not allocate minzd\n");  CudaTest("couldn't allocate minzd");

      if (cudaSuccess != cudaMemcpyToSymbol(nnodesd, &nnodes, sizeof(int))) fprintf(stderr, "copying of nnodes to device failed\n");  CudaTest("nnode copy to device failed");
      if (cudaSuccess != cudaMemcpyToSymbol(nbodiesd, &nbodies, sizeof(int))) fprintf(stderr, "copying of nbodies to device failed\n");  CudaTest("nbody copy to device failed");
      if (cudaSuccess != cudaMemcpyToSymbol(errd, &errl, sizeof(int))) fprintf(stderr, "copying of err to device failed\n");  CudaTest("err copy to device failed");
      if (cudaSuccess != cudaMemcpyToSymbol(dtimed, &dtime, sizeof(float))) fprintf(stderr, "copying of dtime to device failed\n");  CudaTest("dtime copy to device failed");
      if (cudaSuccess != cudaMemcpyToSymbol(dthfd, &dthf, sizeof(float))) fprintf(stderr, "copying of dthf to device failed\n");  CudaTest("dthf copy to device failed");
      if (cudaSuccess != cudaMemcpyToSymbol(epssqd, &epssq, sizeof(float))) fprintf(stderr, "copying of epssq to device failed\n");  CudaTest("epssq copy to device failed");
      if (cudaSuccess != cudaMemcpyToSymbol(itolsqd, &itolsq, sizeof(float))) fprintf(stderr, "copying of itolsq to device failed\n");  CudaTest("itolsq copy to device failed");
      if (cudaSuccess != cudaMemcpyToSymbol(sortd, &sortl, sizeof(int))) fprintf(stderr, "copying of sortl to device failed\n");  CudaTest("sortl copy to device failed");
      if (cudaSuccess != cudaMemcpyToSymbol(countd, &countl, sizeof(int))) fprintf(stderr, "copying of countl to device failed\n");  CudaTest("countl copy to device failed");
      if (cudaSuccess != cudaMemcpyToSymbol(startd, &startl, sizeof(int))) fprintf(stderr, "copying of startl to device failed\n");  CudaTest("startl copy to device failed");
      if (cudaSuccess != cudaMemcpyToSymbol(childd, &childl, sizeof(int))) fprintf(stderr, "copying of childl to device failed\n");  CudaTest("childl copy to device failed");
      if (cudaSuccess != cudaMemcpyToSymbol(massd, &massl, sizeof(int))) fprintf(stderr, "copying of massl to device failed\n");  CudaTest("massl copy to device failed");
      if (cudaSuccess != cudaMemcpyToSymbol(posxd, &posxl, sizeof(int))) fprintf(stderr, "copying of posxl to device failed\n");  CudaTest("posxl copy to device failed");
      if (cudaSuccess != cudaMemcpyToSymbol(posyd, &posyl, sizeof(int))) fprintf(stderr, "copying of posyl to device failed\n");  CudaTest("posyl copy to device failed");
      if (cudaSuccess != cudaMemcpyToSymbol(poszd, &poszl, sizeof(int))) fprintf(stderr, "copying of poszl to device failed\n");  CudaTest("poszl copy to device failed");
      if (cudaSuccess != cudaMemcpyToSymbol(velxd, &velxl, sizeof(int))) fprintf(stderr, "copying of velxl to device failed\n");  CudaTest("velxl copy to device failed");
      if (cudaSuccess != cudaMemcpyToSymbol(velyd, &velyl, sizeof(int))) fprintf(stderr, "copying of velyl to device failed\n");  CudaTest("velyl copy to device failed");
      if (cudaSuccess != cudaMemcpyToSymbol(velzd, &velzl, sizeof(int))) fprintf(stderr, "copying of velzl to device failed\n");  CudaTest("velzl copy to device failed");
      if (cudaSuccess != cudaMemcpyToSymbol(accxd, &accxl, sizeof(int))) fprintf(stderr, "copying of accxl to device failed\n");  CudaTest("accxl copy to device failed");
      if (cudaSuccess != cudaMemcpyToSymbol(accyd, &accyl, sizeof(int))) fprintf(stderr, "copying of accyl to device failed\n");  CudaTest("accyl copy to device failed");
      if (cudaSuccess != cudaMemcpyToSymbol(acczd, &acczl, sizeof(int))) fprintf(stderr, "copying of acczl to device failed\n");  CudaTest("acczl copy to device failed");
      if (cudaSuccess != cudaMemcpyToSymbol(maxxd, &maxxl, sizeof(int))) fprintf(stderr, "copying of maxxl to device failed\n");  CudaTest("maxxl copy to device failed");
      if (cudaSuccess != cudaMemcpyToSymbol(maxyd, &maxyl, sizeof(int))) fprintf(stderr, "copying of maxyl to device failed\n");  CudaTest("maxyl copy to device failed");
      if (cudaSuccess != cudaMemcpyToSymbol(maxzd, &maxzl, sizeof(int))) fprintf(stderr, "copying of maxzl to device failed\n");  CudaTest("maxzl copy to device failed");
      if (cudaSuccess != cudaMemcpyToSymbol(minxd, &minxl, sizeof(int))) fprintf(stderr, "copying of minxl to device failed\n");  CudaTest("minxl copy to device failed");
      if (cudaSuccess != cudaMemcpyToSymbol(minyd, &minyl, sizeof(int))) fprintf(stderr, "copying of minyl to device failed\n");  CudaTest("minyl copy to device failed");
      if (cudaSuccess != cudaMemcpyToSymbol(minzd, &minzl, sizeof(int))) fprintf(stderr, "copying of minzl to device failed\n");  CudaTest("minzl copy to device failed");
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

    if (cudaSuccess != cudaMemcpy(massl, mass, sizeof(float) * nbodies, cudaMemcpyHostToDevice)) fprintf(stderr, "copying of mass to device failed\n");  CudaTest("mass copy to device failed");
    if (cudaSuccess != cudaMemcpy(posxl, posx, sizeof(float) * nbodies, cudaMemcpyHostToDevice)) fprintf(stderr, "copying of posx to device failed\n");  CudaTest("posx copy to device failed");
    if (cudaSuccess != cudaMemcpy(posyl, posy, sizeof(float) * nbodies, cudaMemcpyHostToDevice)) fprintf(stderr, "copying of posy to device failed\n");  CudaTest("posy copy to device failed");
    if (cudaSuccess != cudaMemcpy(poszl, posz, sizeof(float) * nbodies, cudaMemcpyHostToDevice)) fprintf(stderr, "copying of posz to device failed\n");  CudaTest("posz copy to device failed");
    if (cudaSuccess != cudaMemcpy(velxl, velx, sizeof(float) * nbodies, cudaMemcpyHostToDevice)) fprintf(stderr, "copying of velx to device failed\n");  CudaTest("velx copy to device failed");
    if (cudaSuccess != cudaMemcpy(velyl, vely, sizeof(float) * nbodies, cudaMemcpyHostToDevice)) fprintf(stderr, "copying of vely to device failed\n");  CudaTest("vely copy to device failed");
    if (cudaSuccess != cudaMemcpy(velzl, velz, sizeof(float) * nbodies, cudaMemcpyHostToDevice)) fprintf(stderr, "copying of velz to device failed\n");  CudaTest("velz copy to device failed");

    CudaTest("[ERROR] Before kernel launch");
    printf("[BENCH] Lauch GPU kernels\n");

    //cudaEventCreate(&start);  cudaEventCreate(&stop);  
    //starttime = clock();
    //cudaEventRecord(start, 0);
    InitializationKernel<<<blocks*FACTOR0, THREADS0>>>();
    CudaTest("[ERROR] Kernel <Initialization> launch failed");
    //cudaEventRecord(stop, 0);  cudaEventSynchronize(stop);  cudaEventElapsedTime(&time, start, stop);
    //timing[0] += time;
    for (step = 0; step < timesteps; step++) {
      //cudaEventRecord(start, 0);
      BoundingBoxKernel<<<blocks*FACTOR1, THREADS1>>>();
      CudaTest("[ERROR] Kernel <BoundingBox> launch failed");
      //cudaEventRecord(stop, 0);  cudaEventSynchronize(stop);  cudaEventElapsedTime(&time, start, stop);
      //timing[1] += time;
      //CudaTest("kernel 1 launch failed");
      //cudaEventRecord(start, 0);
      TreeBuildingKernel<<<blocks*FACTOR2, THREADS2>>>();
      CudaTest("[ERROR] Kernel <TreeBuilding> launch failed");
      //cudaEventRecord(stop, 0);  cudaEventSynchronize(stop);  cudaEventElapsedTime(&time, start, stop);
      //timing[2] += time;
      //debugDump(); 
      //CudaTest("kernel 2 launch failed");
      //cudaEventRecord(start, 0);
      SummarizationKernel<<<blocks*FACTOR3, THREADS3>>>();
      CudaTest("[ERROR] Kernel <Summarization> launch failed");
      //cudaEventRecord(stop, 0);  cudaEventSynchronize(stop);  cudaEventElapsedTime(&time, start, stop);
      //timing[3] += time;
      //CudaTest("kernel 3 launch failed");
      //cudaEventRecord(start, 0);
      SortKernel<<<blocks*FACTOR4, 512>>>();
      CudaTest("[ERROR] Kernel <Sort> launch failed");
      //cudaEventRecord(stop, 0);  cudaEventSynchronize(stop);  cudaEventElapsedTime(&time, start, stop);
      //timing[4] += time;
      //CudaTest("kernel 4 launch failed");
      //cudaEventRecord(start, 0);
      ForceCalculationKernel<<<blocks*FACTOR5, THREADS5>>>();
      CudaTest("[ERROR] Kernel <ForceCalculation> launch failed");
      //cudaEventRecord(stop, 0);  cudaEventSynchronize(stop);  cudaEventElapsedTime(&time, start, stop);
      //timing[5] += time;
      //CudaTest("kernel 5 launch failed");
      //cudaEventRecord(start, 0);
      IntegrationKernel<<<blocks*FACTOR6, THREADS6>>>();
      CudaTest("[ERROR] Kernel <Intergration> launch failed");
      //cudaEventRecord(stop, 0);  cudaEventSynchronize(stop);  cudaEventElapsedTime(&time, start, stop);
      //timing[6] += time;
      //CudaTest("kernel 6 launch failed");
    }
    //endtime = clock();
    CudaTest("[ERROR] Kernel launch failed");
    //cudaEventDestroy(start);  cudaEventDestroy(stop);

    // transfer result back to CPU
    if (cudaSuccess != cudaMemcpy(&error, errl, sizeof(int), cudaMemcpyDeviceToHost)) fprintf(stderr, "copying of err from device failed\n");  CudaTest("err copy from device failed");
    if (cudaSuccess != cudaMemcpy(posx, posxl, sizeof(float) * nbodies, cudaMemcpyDeviceToHost)) fprintf(stderr, "copying of posx from device failed\n");  CudaTest("posx copy from device failed");
    if (cudaSuccess != cudaMemcpy(posy, posyl, sizeof(float) * nbodies, cudaMemcpyDeviceToHost)) fprintf(stderr, "copying of posy from device failed\n");  CudaTest("posy copy from device failed");
    if (cudaSuccess != cudaMemcpy(posz, poszl, sizeof(float) * nbodies, cudaMemcpyDeviceToHost)) fprintf(stderr, "copying of posz from device failed\n");  CudaTest("posz copy from device failed");
    if (cudaSuccess != cudaMemcpy(velx, velxl, sizeof(float) * nbodies, cudaMemcpyDeviceToHost)) fprintf(stderr, "copying of velx from device failed\n");  CudaTest("velx copy from device failed");
    if (cudaSuccess != cudaMemcpy(vely, velyl, sizeof(float) * nbodies, cudaMemcpyDeviceToHost)) fprintf(stderr, "copying of vely from device failed\n");  CudaTest("vely copy from device failed");
    if (cudaSuccess != cudaMemcpy(velz, velzl, sizeof(float) * nbodies, cudaMemcpyDeviceToHost)) fprintf(stderr, "copying of velz from device failed\n");  CudaTest("velz copy from device failed");

/*
    runtime = (int) (1000.0f * (endtime - starttime) / CLOCKS_PER_SEC);
    fprintf(stderr, "runtime: %d ms  (", runtime);
    time = 0;
    for (i = 1; i < 7; i++) {
      fprintf(stderr, " %.1f ", timing[i]);
      time += timing[i];
    }
    if (error == 0) {
      fprintf(stderr, ") = %.1f\n", time);
    } else {
      fprintf(stderr, ") = %.1f FAILED %d\n", time, error);
    }

    if ((run == 0) || (mintime > runtime)) mintime = runtime;
*/
  }

//  fprintf(stderr, "mintime: %d ms\n", mintime);

  // print output
  for (i = 0; i < nbodies; i++) {
    printf("%.2e %.2e %.2e\n", posx[i], posy[i], posz[i]);
  }
  return 0;
}
