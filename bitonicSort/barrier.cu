#include "common.h"
#ifdef LOCK_FREE
__device__ inline void __syncblocks_lockfree(int goalVal, volatile int *Arrayin, volatile int *Arrayout) {
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
__device__ volatile int g_mutex = 0;
__device__ inline void __syncblocks_atomic(int goal) {
	__syncthreads();
//	__threadfence();
//	int bx = blockIdx.x;
	int tx = threadIdx.x;// * blockDim.y + threadIdx.y;
	if (tx == 0) {
		atomicAdd((int *)&g_mutex, 1);
		while(g_mutex != goal) {}
	}
	__syncthreads();
}
#endif
