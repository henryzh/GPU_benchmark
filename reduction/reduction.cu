#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "common.h"
#include "barrier.cu"
#define BLOCK_SIZE 256
#define GRID_SIZE 64
//__device__ unsigned count = 0;
//__shared__ bool isLastBlockDone;

__device__ float calculatePartialSum(const float* input, unsigned N) {
    unsigned tx = threadIdx.x;
    unsigned bs = blockDim.x;
    unsigned shift = bs*blockIdx.x;
    unsigned tid = shift+tx;
    if (tid>=N) return 0;
    __shared__ float partialSum[2*BLOCK_SIZE];
    unsigned start = 2*shift;

    // each thread loads two array elements
    partialSum[tx] = input[start + tx];
    partialSum[bs + tx] = input[start + bs + tx];

    // calculate partial sum
    for (unsigned stride = bs; stride >=1; stride >>=1) {
        __syncthreads();
        if (tx < stride) partialSum[tx] += partialSum[tx + stride];
    }
    return partialSum[0];
}

__device__ float calculateTotalSum(float* input) {
    unsigned tx = threadIdx.x;
    unsigned bs = GRID_SIZE;
    if (tx>=GRID_SIZE/2) return 0;
    __shared__ float partialSum[GRID_SIZE];
    partialSum[tx] = input[tx];
    partialSum[bs/2 + tx] = input[bs/2 + tx];
    for (unsigned stride = bs/2; stride >=1; stride >>=1) {
        __syncthreads();
        if (tx < stride) partialSum[tx] += partialSum[tx + stride];
    }
    return partialSum[0];
}

#ifdef LOCKFREE
__global__ void sum(const float* array, unsigned N, float* result, volatile int* arrayIn, volatile int* arrayOut) {
#else
__global__ void sum(const float* array, unsigned N, float* result) {
#endif
///*
    // Each block sums a subset of the input array
    float partialSum = calculatePartialSum(array, N);
    if (threadIdx.x == 0) {
//        printf("partialSum[%d] = %f\n", blockIdx.x, partialSum);
        // Thread 0 of each block stores the partial sum
        // to global memory
        result[blockIdx.x] = partialSum;

        // Thread 0 makes sure that the threads of the
        // last block will read its correct partial sum
        __threadfence();

        // Thread 0 of each block signals that it is done
//        unsigned value = atomicInc(&count, gridDim.x);

        // Thread 0 of each block determines if its block is
        // the last block to be done
//        isLastBlockDone = (value == (gridDim.x - 1));
    }
    // Synchronize to make sure that each thread reads
    // the correct value of isLastBlockDone
//    __syncthreads();

#ifdef LOCKFREE
    __syncblocks_lockfree(1, arrayIn, arrayOut);
#endif
#ifdef ATOMIC
    __syncblocks_atomic(gridDim.x);
#endif
#ifdef HW_BARRIER
    __threadfence();
#endif

//    if (isLastBlockDone) {
    if (blockIdx.x == 0) {
        // The last block sums the partial sums
        // stored in result[0 .. gridDim.x-1]
        float totalSum = calculateTotalSum(result);
        if (threadIdx.x == 0) {
            // Thread 0 of last block stores total sum
            // to global memory and resets count so that
            // next kernel call works properly
            result[0] = totalSum;
//            printf("totalSum = %f\n", result[0]);
//            count = 0;
        }
    }
//*/
//    if (threadIdx.x == 0)  result[blockIdx.x] = blockIdx.x;
}

int main(int argc, char* argv[]) {
    unsigned n = 2 * BLOCK_SIZE * GRID_SIZE;
    if(argc>1)
        n = atoi(argv[1]);
    if(GRID_SIZE > BLOCK_SIZE) {
        printf("ERROR: GRID_SIZE > BLOCK_SIZE not allowed\n");
        exit(0);
    }
    printf("[BENCH] CUDA Sum, n = %d\n", n);
    printf("[BENCH] Xuhao Chen <cxh@illinois.edu>\n");
    printf("[BENCH] Block Size: %d\n", BLOCK_SIZE);
    printf("[BENCH] Number of Blocks: %d\n", GRID_SIZE);
#ifdef LOCKFREE
    printf("[BENCH] Lock Free Barrier\n");
#endif
#ifdef ATOMIC
    printf("[BENCH] Atomic Barrier\n");
#endif
#ifdef HW_BARRIER
    printf("[BENCH] Hardware Barrier\n");
#endif
    float *h_input;
    float *h_result;
    h_input = (float*)malloc(n*sizeof(float));
    h_result = (float*)calloc(GRID_SIZE, sizeof(float));
    int i;
    for(i = 0; i < n; i++) {
        h_input[i] = ((float) rand() / (RAND_MAX));
//        h_input[i] = 1.0f;
    }
    float *d_input;
    float *d_result;
    CUDA_SAFE_CALL(cudaMalloc(&d_input, n*sizeof(float)));
    CUDA_SAFE_CALL(cudaMalloc(&d_result, GRID_SIZE*sizeof(float)));
    CUDA_SAFE_CALL(cudaMemcpy(d_input, h_input, n*sizeof(float), cudaMemcpyHostToDevice));
    CUDA_SAFE_CALL(cudaMemset(d_result, 0, GRID_SIZE*sizeof(float)));

#ifdef LOCKFREE
   int* d_arrayIn;
   int* d_arrayOut;
   CUDA_SAFE_CALL(cudaMalloc((void**) &d_arrayIn, sizeof(int)*GRID_SIZE));
   CUDA_SAFE_CALL(cudaMalloc((void**) &d_arrayOut, sizeof(int)*GRID_SIZE));
   CUDA_SAFE_CALL(cudaMemset((void*) d_arrayIn, 0, sizeof(int)*GRID_SIZE));
   CUDA_SAFE_CALL(cudaMemset((void*) d_arrayOut, 0, sizeof(int)*GRID_SIZE));
#endif

    int blockSize = BLOCK_SIZE;
    int gridSize = GRID_SIZE;

    cudaDeviceSynchronize();
#ifdef LOCKFREE
    sum<<<gridSize, blockSize>>>(d_input, n, d_result, d_arrayIn, d_arrayOut);
#else
    sum<<<gridSize, blockSize>>>(d_input, n, d_result);
#endif
    cudaDeviceSynchronize();
    CUT_CHECK_ERROR("Kernel Launch Failed!")

    CUDA_SAFE_CALL(cudaMemcpy(h_result, d_result, GRID_SIZE*sizeof(float), cudaMemcpyDeviceToHost));
    printf("[BENCH] Final Result: %f\n", h_result[0]);
/*
    for(i = 0; i < GRID_SIZE; i++) {
        printf("h_result[%d] = %f\n", i, h_result[i]);
    }
*/
    float ref_result = 0.0f;
    for(i = 0; i < n; i++) {
        ref_result += h_input[i];
    }
    float error = abs(ref_result - h_result[0]);
    if(error < 0.1)
        printf("[BENCH] Result Correct, error = %f\n", error);
    else
        printf("[BENCH] ERROR (Ref Result = %f)!\n", ref_result);
    CUDA_SAFE_CALL(cudaFree(d_input));
    CUDA_SAFE_CALL(cudaFree(d_result));
    free(h_input);
    return 0;
}
