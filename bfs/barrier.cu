#include "config.h"
#ifdef LOCKFREE
__device__ inline void __barrier_lockfree(int goalVal, volatile int *Arrayin, volatile int *Arrayout) {
	int tx = threadIdx.x;// * blockDim.y + threadIdx.y;
	int numBlocks = gridDim.x;// * gridDim.y;
	int bid = blockIdx.x;// * gridDim.y + blockIdx.y;
	if(tx == 0) {
		Arrayin[bid] = goalVal;
	}
	if(bid == 1) {
		if(tx < numBlocks) {
			while (Arrayin[tx] != goalVal) {}
		}
		__syncthreads();
		if(tx < numBlocks) {
			Arrayout[tx] = goalVal;
		}
	}
	if(tx == 0) {
		while(Arrayout[bid] != goalVal) {}
	}
	__syncthreads();
}
#endif

#ifdef ATOMIC
__device__ volatile int mutex = 0;
__device__ inline void __barrier_atomic(int goal) {
	__syncthreads();
//	int bx = blockIdx.x;
	uint tx = threadIdx.x;// * blockDim.y + threadIdx.y;
	if (tx == 0) {
		atomicAdd((int *)&mutex, 1);
		while(mutex != goal) {}
	}
	__syncthreads();
}
#endif
