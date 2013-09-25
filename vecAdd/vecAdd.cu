#include <stdio.h>
#include <stdlib.h>
#include <math.h>

__global__ void vecAdd_kernel(float *a, float *b, float *c, int n) {
    int id = blockIdx.x*blockDim.x+threadIdx.x;
    if (id < n)
        c[id] = a[id] + b[id];
}

void vecAdd(float *h_a, float *h_b, float *h_c, int n) {
    float *d_a;
    float *d_b;
    float *d_c;
    size_t bytes = n*sizeof(float);
    cudaMalloc(&d_a, bytes);
    cudaMalloc(&d_b, bytes);
    cudaMalloc(&d_c, bytes);
    cudaMemcpy(d_a, h_a, bytes, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, h_b, bytes, cudaMemcpyHostToDevice);
    int blockSize, gridSize;
    blockSize = 256;
    gridSize = (int)ceil((float)n/blockSize);
    vecAdd_kernel<<<gridSize, blockSize>>>(d_a, d_b, d_c, n);
    cudaMemcpy(h_c, d_c, bytes, cudaMemcpyDeviceToHost );
    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);
}

int main(int argc, char* argv[]) {
    int n = 1024;
/*
    if(argc<2) {
      printf("Usage: ./vecAdd num_elements\n");
      return 0;
    }
*/
    if(argc>1)
      n = atoi(argv[1]);
    printf("[BENCH] CUDA Vector Addition, n = %d\n", n);
    printf("[BENCH] Xuhao Chen <cxh@illinois.edu>\n");
    float *h_a;
    float *h_b;
    float *h_c;
    size_t bytes = n*sizeof(float);
    h_a = (float*)malloc(bytes);
    h_b = (float*)malloc(bytes);
    h_c = (float*)malloc(bytes);
    int i;
    for( i = 0; i < n; i++ ) {
        h_a[i] = ((float) rand() / (RAND_MAX));
        h_b[i] = ((float) rand() / (RAND_MAX));
    }

    vecAdd(h_a, h_b, h_c, n);

    float sum = 0;
    for(i=0; i<n; i++)
        sum += h_c[i];
    printf("[BENCH] Final result: %f\n", sum/n);
    free(h_a);
    free(h_b);
    free(h_c);
    return 0;
}
