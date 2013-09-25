#include "common.h"
#ifdef LOCKFREE
__device__ inline void __syncblocks_lockfree(int goalVal, volatile int *arrayIn, volatile int *arrayOut) {
//	int tx = threadIdx.x;
	int tx = threadIdx.z*(blockDim.x*blockDim.y) + threadIdx.y*(blockDim.x) + threadIdx.x;
	int numBlocks = gridDim.x;// * gridDim.y;
	int bid = blockIdx.x;// * gridDim.y + blockIdx.y;
	if(tx == 0) {
		arrayIn[bid] = goalVal;
	}
	if(bid == 1) {
		if(tx < numBlocks) {
			while (arrayIn[tx] != goalVal) {}
		}
		__syncthreads();
		if(tx < numBlocks) {
			arrayOut[tx] = goalVal;
		}
	}
	if(tx == 0) {
		while(arrayOut[bid] != goalVal) {}
	}
	__syncthreads();
}
#endif

#ifdef ATOMIC
__device__ volatile int mutex = 0;
__device__ inline void __syncblocks_atomic(int goal) {
	int tx = threadIdx.z*(blockDim.x*blockDim.y) + threadIdx.y*(blockDim.x) + threadIdx.x;
	if (tx == 0) {
		atomicAdd((int *)&mutex, 1);
		while(mutex != goal) {}
	}
	__syncthreads();
}
#endif
