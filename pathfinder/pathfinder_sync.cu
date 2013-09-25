#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "common.h"
#include "barrier.cu"

#define BLOCK_SIZE 256
#define STR_SIZE 256
#define DEVICE 0
#define HALO 1 // halo width along one direction when advancing to the next iteration

//#define BENCH_PRINT
void run(int argc, char** argv);

int rows, cols;
int* data;
int** wall;
int* result;
#define M_SEED 9
int pyramid_height;

//#define BENCH_PRINT
void init(int argc, char** argv) {
	if(argc==4) {
		cols = atoi(argv[1]);
		rows = atoi(argv[2]);
                pyramid_height=atoi(argv[3]);
	} else {
                printf("Usage: dynproc row_len col_len pyramid_height\n");
                exit(0);
        }
	data = new int[rows*cols];
	wall = new int*[rows];
	for(int n=0; n<rows; n++)
		wall[n]=data+cols*n;
	result = new int[cols];
	int seed = M_SEED;
	srand(seed);
	for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            wall[i][j] = rand() % 10;
        }
    }

#ifdef BENCH_PRINT
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ",wall[i][j]) ;
        }
        printf("\n") ;
    }
#endif
}

void fatal(char *s) {
	fprintf(stderr, "error: %s\n", s);
}

#define IN_RANGE(x, min, max)   ((x)>=(min) && (x)<=(max))
#define CLAMP_RANGE(x, min, max) x = (x<(min)) ? min : ((x>(max)) ? max : x )
#define MIN(a, b) ((a)<=(b) ? (a) : (b))

#ifdef LOCKFREE
__global__ void dynproc_kernel(const int num_steps, const int pyramid_height, int *gpuWall, int *gpuSrc, int *gpuResults, const int cols, const int rows, const int border, int *in, int *out) {
#else
__global__ void dynproc_kernel(const int num_steps, const int pyramid_height, int *gpuWall, int *gpuSrc, int *gpuResults, const int cols, const int rows, const int border) {
#endif

  uint num_blocks = gridDim.x;
  uint bx = blockIdx.x;
  uint tx = threadIdx.x;
//  if(tx==0 && bx==0) printf("num_steps=%d\n", num_steps);
  __shared__ int prev[BLOCK_SIZE];
  __shared__ int result[BLOCK_SIZE];
  int iteration = pyramid_height;
  int small_block_cols = BLOCK_SIZE-iteration*HALO*2;
  int blkX = small_block_cols*bx-border;
  int blkXmax = blkX+BLOCK_SIZE-1;
  int xidx = blkX+tx;
  int validXmin = (blkX < 0) ? -blkX : 0;
  int validXmax = (blkXmax > cols-1) ? BLOCK_SIZE-1-(blkXmax-cols+1) : BLOCK_SIZE-1;
  int W = tx-1;
  int E = tx+1;
  W = (W < validXmin) ? validXmin : W;
  E = (E > validXmax) ? validXmax : E;
  bool isValid = IN_RANGE(tx, validXmin, validXmax);
  for (int step=0; step<num_steps; step++) {
//    if(tx==0 && bx ==0) printf("num_steps=%d, iteration[%d]=%d\n", num_steps, step, iteration);

    if(step==(num_steps-1) && (rows-1)%pyramid_height!=0) {
      iteration = (rows-1)%pyramid_height;
      small_block_cols = BLOCK_SIZE-iteration*HALO*2;
      blkX = small_block_cols*bx-border;
      blkXmax = blkX+BLOCK_SIZE-1;
      xidx = blkX+tx;
      validXmin = (blkX < 0) ? -blkX : 0;
      validXmax = (blkXmax > cols-1) ? BLOCK_SIZE-1-(blkXmax-cols+1) : BLOCK_SIZE-1;
      W = tx-1;
      E = tx+1;
      W = (W < validXmin) ? validXmin : W;
      E = (E > validXmax) ? validXmax : E;
      isValid = IN_RANGE(tx, validXmin, validXmax);
    }

    if(IN_RANGE(xidx, 0, cols-1)) {
      prev[tx] = gpuSrc[xidx];
    }
    __syncthreads();
    bool computed;
    for(int i=0; i<iteration; i++) { 
      computed = false;
      if(IN_RANGE(tx, i+1, BLOCK_SIZE-i-2) && isValid) {
        computed = true;
        int left = prev[W];
        int up = prev[tx];
        int right = prev[E];
        int shortest = MIN(left, up);
        shortest = MIN(shortest, right);
        int index = cols*(step*pyramid_height+i) + xidx;
        result[tx] = shortest + gpuWall[index];
      }
      __syncthreads();
      if(i == iteration-1)
        break;
      if(computed)
        prev[tx] = result[tx];
      __syncthreads();
    }// end for i
    if (computed) {
      gpuResults[xidx] = result[tx];		
    }
//    if(tx==0 && bx ==0) printf("iteration ended, arrive barrier, num_blocks=%d\n", num_blocks);
    __threadfence();
#ifdef ATOMIC
    __syncblocks_atomic((step+1)*num_blocks, tx);
#endif
#ifdef LOCKFREE
//    __syncblocks_lockfree(step+1, tx, bx, num_blocks, in, out);
#endif
    int* temp = gpuSrc;
    gpuSrc = gpuResults;
    gpuResults = temp;
  }// end for t
}

// compute N time steps
int calc_path(int *gpuWall, int *gpuResult[2], int rows, int cols, int pyramid_height, int blockCols, int borderCols) {
#ifdef LOCKFREE
   int* d_arrayIn;
   int* d_arrayOut;
   CUDA_SAFE_CALL( cudaMalloc( (void**) &d_arrayIn, sizeof(int)*blockCols));
   CUDA_SAFE_CALL( cudaMalloc( (void**) &d_arrayOut, sizeof(int)*blockCols));
   CUDA_SAFE_CALL( cudaMemset( (void*) d_arrayIn, 0, sizeof(int)*blockCols));
   CUDA_SAFE_CALL( cudaMemset( (void*) d_arrayOut, 0, sizeof(int)*blockCols));
#endif
    dim3 dimBlock(BLOCK_SIZE);
    dim3 dimGrid(blockCols);
    int num_steps = (rows-1+pyramid_height-1)/pyramid_height;
#ifdef LOCKFREE
    dynproc_kernel<<<dimGrid, dimBlock>>>(num_steps, pyramid_height, gpuWall, gpuResult[0], gpuResult[1], cols, rows, borderCols, d_arrayIn, d_arrayOut);
#else
    dynproc_kernel<<<dimGrid, dimBlock>>>(num_steps, pyramid_height, gpuWall, gpuResult[0], gpuResult[1], cols, rows, borderCols);
#endif
    int dst = 1;
    if(num_steps%2==0) dst = 0;
    return dst;
}

int main(int argc, char** argv) {
    int num_devices;
    cudaGetDeviceCount(&num_devices);
    if (num_devices > 1) cudaSetDevice(DEVICE);
    run(argc,argv);
    return EXIT_SUCCESS;
}

void run(int argc, char** argv) {
    init(argc, argv);
    int borderCols = (pyramid_height)*HALO;
    int smallBlockCol = BLOCK_SIZE-(pyramid_height)*HALO*2;
    int blockCols = cols/smallBlockCol+((cols%smallBlockCol==0)?0:1);
    printf("[BENCH] pyramidHeight=%d, rows=%d, cols=%d, border=%d\n", pyramid_height, rows, cols, borderCols);
    printf("[BENCH] blockSize=%d, gridSize=%d, targetBlock=%d\n", BLOCK_SIZE, blockCols, smallBlockCol);
#ifdef LOCKFREE
    printf("[BENCH] Lock Free Barrier\n");
#endif
#ifdef ATOMIC
    printf("[BENCH] Atomic Barrier\n");
#endif
    int *gpuWall, *gpuResult[2];
    int size = rows*cols;

    CUDA_SAFE_CALL(cudaMalloc((void**)&gpuResult[0], sizeof(int)*cols));
    CUDA_SAFE_CALL(cudaMalloc((void**)&gpuResult[1], sizeof(int)*cols));
    CUDA_SAFE_CALL(cudaMemcpy(gpuResult[0], data, sizeof(int)*cols, cudaMemcpyHostToDevice));
    CUDA_SAFE_CALL(cudaMalloc((void**)&gpuWall, sizeof(int)*(size-cols)));
    CUDA_SAFE_CALL(cudaMemcpy(gpuWall, data+cols, sizeof(int)*(size-cols), cudaMemcpyHostToDevice));

    printf("[BENCH] Launch kernel\n");
    cudaDeviceSynchronize();
    int final_ret = calc_path(gpuWall, gpuResult, rows, cols, pyramid_height, blockCols, borderCols);
    cudaDeviceSynchronize();
    CUT_CHECK_ERROR("Kernel launch failed")
    printf("[BENCH] kernel complete\n");

    cudaMemcpy(result, gpuResult[final_ret], sizeof(int)*cols, cudaMemcpyDeviceToHost);

    FILE * fp = fopen("result.txt", "w");
    for (int i = 0; i < cols; i++)
        fprintf(fp, "%d ", data[i]);
    fprintf(fp, "\n");
    for (int i = 0; i < cols; i++)
        fprintf(fp, "%d ", result[i]);
    fprintf(fp, "\n");

    CUDA_SAFE_CALL(cudaFree(gpuWall));
    CUDA_SAFE_CALL(cudaFree(gpuResult[0]));
    CUDA_SAFE_CALL(cudaFree(gpuResult[1]));
    delete [] data;
    delete [] wall;
    delete [] result;
}

