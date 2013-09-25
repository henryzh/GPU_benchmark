#include "common.h"
#ifdef LOCKFREE
__device__ inline void __syncblocks_lockfree(int goalVal, uint tx, uint bx, uint numBlocks, volatile int *arrayIn, volatile int *arrayOut) {
	if(tx == 0) {
		arrayIn[bx] = goalVal;
	}
	if(bx == 1) {
		if(tx < numBlocks) {
			while (arrayIn[tx] != goalVal) {}
		}
		__syncthreads();
		if(tx < numBlocks) {
			arrayOut[tx] = goalVal;
		}
	}
	if(tx == 0) {
		while(arrayOut[bx] != goalVal) {}
	}
	__syncthreads();
}
#endif

#ifdef ATOMIC
__device__ volatile int mutex = 0;
__device__ inline void __syncblocks_atomic(int goal, uint tx) {
	if (tx == 0) {
		atomicAdd((int *)&mutex, 1);
		while(mutex != goal) {}
	}
	__syncthreads();
}
#endif
