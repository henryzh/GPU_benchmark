// Scan, IMPACT UIUC
#include <stdio.h>
#include <cuda_runtime.h>

__global__ void scan_local(int *data, int *partial_sums) {
	uint tx = threadIdx.x;
	uint bx = blockIdx.x;
	uint bs = blockDim.x;
	extern __shared__ int sums[];
	const unsigned id = bx*bs + tx;
	sums[tx] = data[id];
	__syncthreads();
	for (int i=1; i<=bs/2; i*=2) {
		if(tx<bs/2/i) {
			sums[2*i*tx+2*i-1]+=sums[2*i*tx+i-1];
		}
		__syncthreads();
	}
	if(tx==0)partial_sums[bx+1] = sums[bs-1];
	data[id] = sums[tx];
}

__global__ void scan_partial(int *partial_sums) {
	uint tx = threadIdx.x;
	uint bx = blockIdx.x;
	uint bs = blockDim.x;
	extern __shared__ int sums[];
	const unsigned id = bx*bs + tx;
	sums[tx] = partial_sums[id];
	__syncthreads();
	for (int i=1; i<=bs/2; i*=2) {
		if(tx<bs/2/i) {
			sums[2*i*tx+2*i-1]+=sums[2*i*tx+i-1];
		}
		__syncthreads();
	}
	partial_sums[id] = sums[tx];
}

__global__ void scan_global(int *data, int *partial_sums) {
	uint tx = threadIdx.x;
	uint bx = blockIdx.x;
	uint bs = blockDim.x;
	extern __shared__ int sums[];
	const unsigned id = bx*bs + tx;
	sums[tx] = data[id];
	if(tx==0) sums[bs] = partial_sums[bx];
	__syncthreads();

	for (int i=bs/4; i>=1; i/=2) {
		if(tx<bs/2/i-1) {
			sums[3*i+2*i*tx-1]+=sums[2*i+2*i*tx-1];
		}
		__syncthreads();
	}
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
	cudaMalloc((void **)&d_data, sz);
	cudaMalloc((void **)&d_partial_sums, partial_sz);
	cudaMemset(d_partial_sums, 0, partial_sz);
	cudaMallocHost((void **)&h_partial_sums, partial_sz);
	cudaMemcpy(d_data, h_data, sz, cudaMemcpyHostToDevice);
	cudaMalloc((void **)&d_counter, n_partialSums*sizeof(unsigned));
	cudaMemset(d_counter, 0, n_partialSums*sizeof(unsigned));

	cudaDeviceSynchronize();
	scan_local<<< gridSize, blockSize, shmem_sz >>>(d_data, d_partial_sums);
	scan_partial<<< gridSize, blockSize, shmem_sz >>>(d_data, d_partial_sums);
	scan_global<<< gridSize, blockSize, shmem_sz >>>(d_data, d_partial_sums);
	cudaDeviceSynchronize();

	cudaMemcpy(h_result, d_data, sz, cudaMemcpyDeviceToHost);
	cudaMemcpy(h_partial_sums, d_partial_sums, partial_sz, cudaMemcpyDeviceToHost);
	check_scan_all_one(h_result,n_elements);
	cudaFreeHost(h_data);
	cudaFreeHost(h_result);
	cudaFreeHost(h_partial_sums);
	cudaFree(d_data);
	cudaFree(d_partial_sums);
	cudaDeviceReset();
	return 0;
}

