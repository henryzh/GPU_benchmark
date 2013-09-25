__device__ void __ib_sync_lockfree(int goalVal, volatile int *Arrayin, volatile int *Arrayout) {
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

__device__ volatile int g_mutex;
__device__ void __ib_sync(int goal) {
//	__syncthreads();
	int tx = threadIdx.x;// * blockDim.y + threadIdx.y;
	if (tx == 0) {
		atomicAdd((int *)&g_mutex, 1);
		while(g_mutex != goal) {}
	}
	__syncthreads();
}
