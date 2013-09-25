// Scan, IMPACT UIUC
#include <stdio.h>
#include <cuda_runtime.h>
#include "common.h"
#include "barrier.cu"

#define BLOCK_SIZE 256
#define NUM_ELEMENTS 1024*128*32;

#ifdef NAIVE
#ifndef HW_BARRIER
__device__ inline void __wait_for_blocks(volatile uint *flags, uint bid, uint tx) {
	if(tx==0) {
		while(flags[bid] != 1) {}// waiting for dependency
	}
//	__threadfence();
	__syncthreads();
}

__device__ inline void __block_check_in(volatile uint *flags, uint bx, uint tx) {
	if(tx==0) {
		flags[bx] = 1;// this block checks in
	}
//	__syncthreads();
}
#endif
#endif

__global__ void scan_kernel(int *data, unsigned *counter, int *partial_sums) {
	uint tx = threadIdx.x;
	uint bx = blockIdx.x;
	uint bs = blockDim.x;
	// Step 1: Load
	extern __shared__ int sums[];
	const unsigned id = bx*bs + tx;
	sums[tx] = data[id];
	__syncthreads();

	// Step 2: Computation
	for (int i=1; i<=bs/2; i*=2) {
		if(tx<bs/2/i) {
			sums[2*i*tx+2*i-1]+=sums[2*i*tx+i-1];
		}
		__syncthreads();
	}

	// Step 3: Synchronization
	// block[i+1] depends on block[i]
#ifdef LOCKFREE
//	__ib_sync_lockfree(counter, partial_sums, sums);
	lockfree_barrier(counter, partial_sums, sums+bs, sums[bs-1], bx, tx);
#endif
#ifdef ATOMIC
	atomic_barrier(counter, partial_sums, sums+bs, sums[bs-1], bx, tx);
#endif
#ifdef FREE
	free_barrier(partial_sums, sums+bs, sums[bs-1], bx, tx);
#endif
#ifdef UNSAFE
	unsafe_barrier(partial_sums, sums+bs, sums[bs-1], bx, tx);
#endif
#ifdef FORWARD
	forward_barrier(partial_sums, sums+bs, sums[bs-1], bx, tx);
#endif
#ifdef FORWARD_ATOMIC
	forward_atomic_barrier(partial_sums, sums+bs, sums[bs-1], bx, tx);
#endif

#ifdef NAIVE
	if(tx==0)partial_sums[bx+1] = sums[bs-1];
	if(bx>0) {
#ifdef HW_BARRIER
//		__syncthreads();
		__threadfence();
#else
		__wait_for_blocks(counter, bx-1, tx);
#endif
	}
	if(tx==0) {
		sums[bs] = partial_sums[bx];
//		partial_sums[bx+1] = sums[bs] + sums[bs-1];
		partial_sums[bx+1] += sums[bs];
	}
	__threadfence();
#ifndef HW_BARRIER
	__block_check_in(counter, bx, tx);
#endif
#endif //end ifdef NAIVE

	// Step 4: Computation
	for (int i=bs/4; i>=1; i/=2) {
		if(tx<bs/2/i-1) {
			sums[3*i+2*i*tx-1]+=sums[2*i+2*i*tx-1];
		}
		__syncthreads();
	}

	// Step 5: Store
	data[id] = sums[tx] + sums[bs];
}

void check_scan_all_one(int *x, int n) {
	for(int i=0;i<n;i++) {
		if(x[i]!=(i+1)) {
			printf("[ERROR] out[%d]=%d, ref=%d\n", i, x[i], i+1);
			printf("[ERROR] out[%d]=%d, ref=%d\n", i+1, x[i+1], i+2);
			return;
		}
	}
	printf("[BENCH] Result correct\n");
}

int main() {
	int n_elements = NUM_ELEMENTS;
	int blockSize = BLOCK_SIZE;
	int *h_data, *h_partial_sums, *h_result;
	int *d_data, *d_partial_sums;
//	unsigned *d_zero;
	unsigned *d_counter;
	int sz = sizeof(int) *n_elements;
	cudaMallocHost((void **)&h_data, sizeof(int)*n_elements);
	cudaMallocHost((void **)&h_result, sizeof(int)*n_elements);
	for (int i=0; i<n_elements; i++) {
		h_data[i] = 1;
	}
	int gridSize = n_elements/blockSize;
	int shmem_sz = blockSize * sizeof(int)+2;
	int n_partialSums = n_elements/blockSize;
	int partial_sz = n_partialSums*sizeof(int);

	printf("[BENCH] Scan with %d elements, %d partial sums\n", n_elements, n_partialSums);
	printf("[BENCH] gridSize=%d, blockSize=%d, shmem_sz=%d\n", gridSize, blockSize, shmem_sz);
#ifdef LOCKFREE
	printf("[BENCH] Lock Free Barrier\n");
#endif
#ifdef ATOMIC
	printf("[BENCH] Atomic Barrier\n");
#endif
#ifdef FREE
	printf("[BENCH] Free Barrier, result is supposed to be incorrect\n");
#endif
#ifdef UNSAFE
	printf("[BENCH] Unsafe Barrier\n");
#endif
#ifdef FORWARD
	printf("[BENCH] Forward Barrier\n");
#endif
#ifdef FORWARD_ATOMIC
	printf("[BENCH] Forward Atomic Barrier\n");
#endif
#ifdef HW_BARRIER
	printf("[BENCH] Hardware Barrier\n");
#endif
	cudaMalloc((void **)&d_data, sz);
	cudaMalloc((void **)&d_partial_sums, partial_sz);
	cudaMemset(d_partial_sums, 0, partial_sz);
	cudaMallocHost((void **)&h_partial_sums, partial_sz);
	cudaMemcpy(d_data, h_data, sz, cudaMemcpyHostToDevice);

//	cudaMalloc((void **)&d_zero, sizeof(unsigned));
	cudaMalloc((void **)&d_counter, n_partialSums*sizeof(unsigned));
//	cudaMemset(d_zero, 0, sizeof(unsigned));
	cudaMemset(d_counter, 0, n_partialSums*sizeof(unsigned));

	cudaDeviceSynchronize();
	scan_kernel<<< gridSize, blockSize, shmem_sz >>>(d_data, d_counter, d_partial_sums);
	cudaDeviceSynchronize();

	cudaMemcpy(h_result, d_data, sz, cudaMemcpyDeviceToHost);
	cudaMemcpy(h_partial_sums, d_partial_sums, partial_sz, cudaMemcpyDeviceToHost);
//	printf("Test Sum: %d\n", h_partial_sums[n_partialSums-1]);
	check_scan_all_one(h_result,n_elements);
	cudaFreeHost(h_data);
	cudaFreeHost(h_result);
	cudaFreeHost(h_partial_sums);
	cudaFree(d_data);
	cudaFree(d_partial_sums);
	cudaDeviceReset();
	return 0;
}

