// Parallel bitonic sort using CUDA
// Xuhao Chen, IMPACT group, UIUC
 
#include <stdlib.h>
#include <stdio.h>
#include "parboil.h"
#include "common.h"
#include "barrier.cu"

//#define TEST
//#define DEBUG
//#define PRINT
#define TIMING
//#define SHM
#define SHARED_SIZE_LIMIT 1024

#ifdef TEST
#define THREADS 8
#define BLOCKS 4
#else
#define THREADS 512
#define BLOCKS 32
#endif
#define NUM_VALS 2*THREADS*BLOCKS
struct pb_TimerSet timers;

#define CUERR { cudaError_t err; \
  if ((err = cudaGetLastError()) != cudaSuccess) { \
  printf("CUDA error: %s, line %d\n", cudaGetErrorString(err), __LINE__); \
  exit(0); }}

void choose_best_device() {
  int num_devices, device;
  cudaGetDeviceCount(&num_devices);
  if (num_devices > 1) {
    int max_sm = 0, max_id = 0;
    for (device = 0; device < num_devices; device++) {
      cudaDeviceProp properties;
      cudaGetDeviceProperties(&properties, device);
      if (max_sm < properties.multiProcessorCount) {
        max_sm = properties.multiProcessorCount;
        max_id = device;
      }
    }
    cudaSetDevice(max_id);
  }
}

void choose_device() {
  int num_devices, device;
  cudaGetDeviceCount(&num_devices);
  if (num_devices > 1) {
    int min_sm = 0, min_id = 0;
    for (device = 0; device < num_devices; device++) {
      cudaDeviceProp properties;
      cudaGetDeviceProperties(&properties, device);
      if (min_sm < properties.multiProcessorCount) {
        min_sm = properties.multiProcessorCount;
        min_id = device;
      }
    }
    cudaSetDevice(min_id);
  }
}

int compare (const void * a, const void * b) {
  return ( *(float*)a > *(float*)b );
}

void print_elapsed(clock_t start, clock_t stop) {
  double elapsed = ((double) (stop - start)) / CLOCKS_PER_SEC;
  printf("Elapsed time: %.3fs\n", elapsed);
}

float random_float() {
  return (float)rand()/(float)RAND_MAX;
}

void array_print(float *arr, int length)  {
  int i;
  for (i = 0; i < length; ++i) {
    printf("%1.3f ",  arr[i]);
  }
  printf("\n");
}

void array_fill(float *arr, int length) {
  srand(time(NULL));
  int i;
  for (i = 0; i < length; ++i) {
    arr[i] = length-i;//random_float();
  }
}

void array_copy(float *dst, float *src, int length) {
  int i;
  for (i=0; i<length; ++i) {
    dst[i] = src[i];
  }
}

bool array_compare(float *ref, float *res, int length) {
  int i;
  for (i=0; i<length; ++i) {
    if(ref[i]!=res[i])
      return false;
  }
  return true;
}

#ifdef DEBUG
__device__ void gpu_array_print(float *arr, int length)  {
  int i;
  for (i = 0; i < length; ++i) {
    printf("%1.3f ",  arr[i]);
  }
  printf("\n");
}
#endif
/*
__device__ void comparator_volatile(volatile float &A, volatile float &B, uint dir) {
    float t;
    if ((A > B) == dir) {
        t = A;
        A = B;
        B = t;
    }
}
//*/
__device__ inline void comparator(float &A, float &B, uint dir) {
    float t;
    if ((A > B) == dir) {
        t = A;
        A = B;
        B = t;
    }
}

#ifdef NAIVE
__global__ void bitonicSortNaive(float *src, int stride, int size) {
  uint tid = threadIdx.x + blockDim.x * blockIdx.x;
  uint dir = (tid & (size / 2)) == 0;
  uint pos = 2*tid - (tid & (stride - 1));
  comparator(src[pos], src[pos+stride], dir);
}
#endif

#ifdef LOCK_FREE
__global__ void bitonicSortLockfree(float *src, int length, int *in, int *out) {
  int goalVal = 0;
//  uint barrier_count = 0;

  uint tid = threadIdx.x + blockDim.x * blockIdx.x;
  for(uint size=2; size<=length; size<<=1) {
    for(uint stride=size>>1; stride>0; stride=stride>>1) {
      uint dir = (tid & (size / 2)) == 0;
      uint pos = 2*tid - (tid & (stride - 1));
      comparator(src[pos], src[pos+stride], dir);
      if(stride>THREADS || (stride==1 && size>=THREADS)) {
//        barrier_count ++;
        __threadfence();
        goalVal ++;
        __syncblocks_lockfree(goalVal, in, out);
      }
      else {
//        comparator_volatile(src[pos], src[pos+stride], dir);
        __syncthreads();
      }
    } // end for stride
  } // end for size
//  if(tid==0)printf("barrier_count=%d\n", barrier_count);
}
#endif

#ifdef ATOMIC
__global__ void bitonicSortAtomic(float *src, int length) {
#ifndef HW_BARRIER
  uint numBlocks = gridDim.x * gridDim.y * gridDim.z;
  uint goalVal = 0;
#endif
//  uint barrier_count = 0;

  uint tid = threadIdx.x + blockDim.x * blockIdx.x;
  for(uint size=2; size<=length; size<<=1) {
    for(uint stride=size>>1; stride>0; stride=stride>>1) {
      uint dir = (tid & (size / 2)) == 0;
      uint pos = 2*tid - (tid & (stride - 1));
//      comparator_volatile(src[pos], src[pos+stride], dir);
      comparator(src[pos], src[pos+stride], dir);
      if(stride>THREADS || (stride==1 && size>=THREADS)) {
//        barrier_count ++;
        __threadfence();
#ifndef HW_BARRIER
        goalVal += numBlocks;
        __syncblocks_atomic(goalVal);
#endif
      }
      else
        __syncthreads();
    } // end for stride
  } // end for size
//  if(tid==0)printf("barrier_count=%d\n", barrier_count);
}
#endif

__global__ void bitonicSortSmall(float *src, int length, uint dir) {
//    gpu_array_print(src, length);
    int tx = threadIdx.x;
//    int bx = blockIdx.x;
    __shared__ float src_shared[SHARED_SIZE_LIMIT];
    src_shared[tx] = src[tx];
    src_shared[tx + (length / 2)] = src[tx + (length / 2)];

    for (uint size = 2; size < length; size <<= 1) {
        uint ddd = dir ^ ((tx & (size / 2)) != 0);//direction: ascending or descending
        for (uint stride = size/2; stride > 0; stride >>= 1) {
            __syncthreads();
            uint pos = 2 * tx - (tx & (stride - 1));
            comparator(src_shared[pos], src_shared[pos + stride], ddd);
        }
    }
    {
        for (uint stride = length/2; stride > 0; stride >>= 1) {
            __syncthreads();
            uint pos = 2 * tx - (tx & (stride - 1));
            comparator(src_shared[pos + 0], src_shared[pos + stride], dir);
        }
    }
    __syncthreads();
    src[tx] = src_shared[tx];
    src[tx + (length/2)] = src_shared[tx + (length/2)];
}

#ifdef SHM
__global__ void bitonicSortShared(float *src) {
    int tx = threadIdx.x;
    int bx = blockIdx.x;
    int index = blockIdx.x * SHARED_SIZE_LIMIT + threadIdx.x;
    __shared__ float src_shared[SHARED_SIZE_LIMIT];
    src_shared[tx] = src[index];
    src_shared[tx + (SHARED_SIZE_LIMIT/2)] = src[index + (SHARED_SIZE_LIMIT/2)];

    for (uint size = 2; size < SHARED_SIZE_LIMIT; size <<= 1) {
        uint ddd = (tx & (size / 2)) == 1;//direction: ascending or descending
        for (uint stride = size/2; stride > 0; stride >>= 1) {
            __syncthreads();
            uint pos = 2 * tx - (tx & (stride - 1));
            comparator(src_shared[pos], src_shared[pos + stride], ddd);
        }
    }
    uint ddd = (bx&1);
//    uint ddd = ((bx&1)==0);
    {
        for (uint stride = SHARED_SIZE_LIMIT/2; stride > 0; stride >>= 1) {
            __syncthreads();
            uint pos = 2 * tx - (tx & (stride - 1));
            comparator(src_shared[pos + 0], src_shared[pos + stride], ddd);
        }
    }
    __syncthreads();
    src[index] = src_shared[tx];
    src[index+(SHARED_SIZE_LIMIT/2)] = src_shared[tx+(SHARED_SIZE_LIMIT/2)];
}

__global__ void bitonicMergeGlobal(float *src, int length, int size, int stride, uint dir) {
  uint tid = threadIdx.x + blockDim.x * blockIdx.x;
  uint comparatorI = tid & (length/2 - 1);
  uint ddd = dir ^ ((comparatorI & (size / 2)) != 0);
  unsigned int pos = 2*tid - (tid & (stride - 1));
//  printf("bx=%d, tx=%d, tid=%d, stride=%d, pos=%d, ddd=%d, size=%d\n", blockIdx.x, threadIdx.x, tid, stride, pos, ddd, size);
  comparator(src[pos], src[pos+stride], ddd);
}
//Map to single instructions on G8x / G9x / G100
#define UMUL(a, b) __umul24((a), (b))
#define UMAD(a, b, c) ( UMUL((a), (b)) + (c) )
__global__ void bitonicMergeShared(float *src, int length, int size, uint dir) {
    __shared__ float src_shm[SHARED_SIZE_LIMIT];
    int index = blockIdx.x * SHARED_SIZE_LIMIT + threadIdx.x;
    src_shm[threadIdx.x] = src[index];
    src_shm[threadIdx.x + (SHARED_SIZE_LIMIT/2)] = src[index+(SHARED_SIZE_LIMIT/2)];

    uint comparatorI = UMAD(blockIdx.x, blockDim.x, threadIdx.x) & ((length / 2) - 1);
    uint ddd = dir ^ ((comparatorI & (size / 2)) != 0);
    for (uint stride = SHARED_SIZE_LIMIT / 2; stride > 0; stride >>= 1) {
        __syncthreads();
        uint pos = 2 * threadIdx.x - (threadIdx.x & (stride - 1));
        comparator(src_shm[pos], src_shm[pos + stride], ddd);
    }
    __syncthreads();
    src[index] = src_shm[threadIdx.x];
    src[index+(SHARED_SIZE_LIMIT / 2)] = src_shm[threadIdx.x + (SHARED_SIZE_LIMIT / 2)];
}
#endif

// Inplace bitonic sort using CUDA
void bitonic_sort(float *values) {
#ifdef DEBUG
  int iteration = 0;
#endif

  float *dev_values;
  size_t size = NUM_VALS * sizeof(float);
  cudaMalloc((void**) &dev_values, size);
  CUERR
  cudaMemcpy(dev_values, values, size, cudaMemcpyHostToDevice);
  CUERR

#ifdef LOCK_FREE
  int *in, *out;
  cudaMalloc(&in, BLOCKS*sizeof(int));
  CUERR
  cudaMalloc(&out, BLOCKS*sizeof(int));
  CUERR
#endif

  dim3 blocks(BLOCKS,1);
  dim3 threads(THREADS,1);
  cudaDeviceSynchronize();

#ifdef TIMING
  pb_SwitchToTimer(&timers, pb_TimerID_KERNEL);
#endif

  if (NUM_VALS <= SHARED_SIZE_LIMIT) {
    uint blockCount = 1;
    uint threadCount = NUM_VALS / 2;
    printf("[BENCH] Small size, only one block\n");
    printf("[BENCH] blockCount=%d, threadCount=%d\n", blockCount, threadCount);
    bitonicSortSmall<<<blockCount, threadCount>>>(dev_values, NUM_VALS, 1);
    cudaMemcpy(values, dev_values, size, cudaMemcpyDeviceToHost);
    CUERR
    cudaFree(dev_values);
    CUERR
    return;
  }
#ifndef SHM
  printf("[BENCH] blockCount=%d, threadCount=%d\n", BLOCKS, THREADS);
#endif

#ifdef NAIVE
  int j, k;
  for (k = 2; k <= NUM_VALS; k <<= 1) {
    for (j=k>>1; j>0; j=j>>1) {
//      printf("k=%d, j=%d\n", k, j);
      bitonicSortNaive<<<blocks, threads>>>(dev_values, j, k);
#ifdef DEBUG
      iteration ++;
#endif
    }
  }
  CUERR
#endif

#ifdef LOCK_FREE
  bitonicSortLockfree<<<blocks, threads>>>(dev_values, NUM_VALS, in, out);
  CUERR
#endif

#ifdef ATOMIC
  bitonicSortAtomic<<<blocks, threads>>>(dev_values, NUM_VALS);
  CUERR
#endif

#ifdef SHM
  uint blockCount = NUM_VALS / SHARED_SIZE_LIMIT;
  uint threadCount = SHARED_SIZE_LIMIT / 2;
  printf("blockCount=%d, threadCount=%d, SHARED_SIZE_LIMIT=%d\n", blockCount, threadCount, SHARED_SIZE_LIMIT);
  bitonicSortShared<<<blockCount, threadCount>>>(dev_values);
//  cudaMemcpy(values, dev_values, size, cudaMemcpyDeviceToHost);
//  printf("Inter1 array:\n");
//  array_print(values, NUM_VALS);
  CUERR
  
  for(uint size = 2 * SHARED_SIZE_LIMIT; size <= NUM_VALS; size <<= 1)
    for(unsigned stride = size / 2; stride > 0; stride >>= 1)
      if(stride >= SHARED_SIZE_LIMIT) {
//        printf("bitonicMergeGlobal, blockCount=%d, threadCount=%d\n", NUM_VALS/threadCount, threadCount/2);
        bitonicMergeGlobal<<<NUM_VALS/threadCount, threadCount/2>>>(dev_values, NUM_VALS, size, stride, 1);
//  cudaMemcpy(values, dev_values, size, cudaMemcpyDeviceToHost);
//  printf("Inter2 array:\n");
//  array_print(values, NUM_VALS);
      }
      else {
        bitonicMergeShared<<<blockCount, threadCount>>>(dev_values, NUM_VALS, size, 1);
        break;
      }
  CUERR
#endif

  cudaDeviceSynchronize();
#ifdef TIMING
  pb_SwitchToTimer(&timers, pb_TimerID_COPY);
#endif

#ifdef DEBUG
  printf("iteration=%d\n", iteration);
#endif

  cudaMemcpy(values, dev_values, size, cudaMemcpyDeviceToHost);
  CUERR
  cudaFree(dev_values);
#ifdef LOCK_FREE
  cudaFree(in);
  CUERR
  cudaFree(out);
  CUERR
#endif
  CUERR
}

////////////////////////////////////
//           MAIN function        //
////////////////////////////////////
int main(void) {
  printf("[BENCH] Bitonic Sort %d elements\n", NUM_VALS);
  printf("[BENCH] Xuhao Chen <cxh@illinois.edu>\n");
#ifdef SHM
  printf("[BENCH] Shared memory version\n");
#endif
#ifdef NAIVE
  printf("[BENCH] Naive version\n");
#endif
#ifdef LOCK_FREE
  printf("[BENCH] Lock-free Barrier\n");
#endif
#ifndef HW_BARRIER
#ifdef ATOMIC
  printf("[BENCH] Atomic Barrier\n");
#endif
#endif
#ifdef HW_BARRIER
  printf("[BENCH] Hardware Barrier\n");
#endif

#ifdef TIMING
  pb_InitializeTimerSet(&timers);
#endif
  float *values = (float*) malloc( NUM_VALS * sizeof(float));
  float *ref = (float*) malloc( NUM_VALS * sizeof(float));
  array_fill(values, NUM_VALS);
  array_copy(ref, values, NUM_VALS);

  qsort(ref, NUM_VALS, sizeof(float), compare);

#ifdef PRINT
  printf("[BENCH] Input array:\n");
  array_print(values, NUM_VALS);
#endif
#ifdef TIMING
  pb_SwitchToTimer(&timers, pb_TimerID_COPY);
#endif

  bitonic_sort(values);

#ifdef TIMING
  pb_SwitchToTimer(&timers, pb_TimerID_NONE);
  pb_PrintTimerSet(&timers);
#endif

  if(array_compare(ref, values, NUM_VALS))
    printf("[BENCH] Pass\n");
  else
    printf("[BENCH] Mismatch\n");

#ifdef PRINT
  printf("[BENCH] Output array:\n");
  array_print(values, NUM_VALS);
//  printf("Referance array3:\n");
//  array_print(ref, NUM_VALS);
#endif
  free(values);
  free(ref);
}
