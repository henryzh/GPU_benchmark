#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "common.h"
#include "barrier.cu"
//#define DEBUG

#define PI 3.14159
#define IDX(x,y,z) ((z)*LATT_DIM_X*LATT_DIM_Y + (y)*LATT_DIM_X + (x))

#define LATT_DIM_X 48
#define LATT_DIM_Y 48
#define LATT_DIM_Z 48
#define LATT_SIZE (LATT_DIM_X*LATT_DIM_Y*LATT_DIM_Z)

#define CUDA_SAFE_CALL_NO_SYNC(call) {                                    \
    cudaError err = call;                                                    \
    if( cudaSuccess != err) {                                                \
        fprintf(stderr, "Cuda error in file '%s' in line %i : %s.\n",        \
                __FILE__, __LINE__, cudaGetErrorString( err) );              \
        exit(EXIT_FAILURE);                                                  \
    } }

#define CUDA_SAFE_CALL(call) CUDA_SAFE_CALL_NO_SYNC(call);
#define cutilSafeCall(call) CUDA_SAFE_CALL(call); 

#define CUT_CHECK_ERROR(errorMessage) {                                    \
    cudaError_t err = cudaGetLastError();                                    \
    if( cudaSuccess != err) {                                                \
        fprintf(stderr, "Cuda error: %s in file '%s' in line %i : %s.\n",    \
                errorMessage, __FILE__, __LINE__, cudaGetErrorString( err) );\
        exit(EXIT_FAILURE);                                                  \
    }                                                                        \
  }

void wave_gold(float* input_t0, float* input_t1, float vsq, float coeff[5], int iterations, float* result) {
    float* input = (float*) malloc( sizeof(float)*(LATT_SIZE) );
    float* output = (float*) malloc( sizeof(float)*(LATT_SIZE) );
    memcpy(input, input_t1, sizeof(float)*(LATT_SIZE));
    memcpy(output, input_t0, sizeof(float)*(LATT_SIZE));    // output initially contains t-2

    for(int i=0 ;i<iterations; i++) {
        for(int z=4; z<LATT_DIM_Z-4; z++) {
            for(int y=4; y<LATT_DIM_Y-4; y++) {
                for(int x=4; x<LATT_DIM_X-4; x++) {
                    float current = input[IDX(x,y,z)];
                    float prev = output[IDX(x,y,z)];
                    float temp = 2.0f*current - prev;
                    float div = coeff[0] * current;
                    div += coeff[1]*( input[IDX(x+1,y,z)] + input[IDX(x-1,y,z)] +
                                      input[IDX(x,y+1,z)] + input[IDX(x,y-1,z)] +
                                      input[IDX(x,y,z+1)] + input[IDX(x,y,z-1)] );
                    div += coeff[2]*( input[IDX(x+2,y,z)] + input[IDX(x-2,y,z)] +
                                      input[IDX(x,y+2,z)] + input[IDX(x,y-2,z)] +
                                      input[IDX(x,y,z+2)] + input[IDX(x,y,z-2)] );
                    div += coeff[3]*( input[IDX(x+3,y,z)] + input[IDX(x-3,y,z)] +
                                      input[IDX(x,y+3,z)] + input[IDX(x,y-3,z)] +
                                      input[IDX(x,y,z+3)] + input[IDX(x,y,z-3)] );
                    div += coeff[4]*( input[IDX(x+4,y,z)] + input[IDX(x-4,y,z)] +
                                      input[IDX(x,y+4,z)] + input[IDX(x,y-4,z)] +
                                      input[IDX(x,y,z+4)] + input[IDX(x,y,z-4)] );
                    output[IDX(x,y,z)] = temp + div*vsq;
                }
            }
        }

        // Switch buffers
        float* temp_buff = input;
        input = output;
        output = temp_buff;
    }

    // Copy result
    memcpy(result, input, sizeof(float)*(LATT_SIZE));
    free( input );
    free( output );
}

void print_error(float* real_result, float* gold_result) {
    float error_sum = 0.0f;
    for(int z=4; z<LATT_DIM_Z-4; z++) {
        for(int y=4; y<LATT_DIM_Y-4; y++) {
            for(int x=4; x<LATT_DIM_X-4; x++) {
                error_sum += abs(real_result[IDX(x,y,z)] - gold_result[IDX(x,y,z)]);
            }
        }
    }
    printf("[BENCH] Total error = %f\n", error_sum);
    printf("[BENCH] Average error = %f\n", error_sum/((LATT_DIM_Z-4)*(LATT_DIM_Y-4)*(LATT_DIM_X-4)));
}

void generateInputLattice(float* input_t0, float* input_t1, float vsq) {
    for(int z=0; z<LATT_DIM_Z; z++) {
        for(int y=0; y<LATT_DIM_Y; y++) {
            for(int x=0; x<LATT_DIM_X; x++) {
                int index = IDX(x,y,z);

                // Fit N periods of a sinusoid in each dimension
                const float maxAmp = 5.0f;
                const float N = 2;
                float fx, fy, fz;
                fx = (float) x / (float)LATT_DIM_X * 2.0f * PI * N;
                fy = (float) y / (float)LATT_DIM_Y * 2.0f * PI * N;
                fz = (float) z / (float)LATT_DIM_Z * 2.0f * PI * N;
                float val_t0, val_t1;
                val_t0 = maxAmp*sin( sqrt(fx*fx + fy*fy + fz*fz));
                if(x>=4 and x<(LATT_DIM_X-4) and y>=4 and y<(LATT_DIM_Y-4) and z>=4 and z<(LATT_DIM_Z-4))
                    val_t1 = maxAmp*sin( sqrt(fx*fx + fy*fy + fz*fz) + sqrt(vsq));
                else
                    val_t1 = val_t0;

                input_t0[index] = val_t0;
                input_t1[index] = val_t1;
            }
        }
    }
}

void debugPrintDimension(float* input, int dimToPrint) {
    int xStart, yStart, zStart;
    int xEnd, yEnd, zEnd;
    xStart = (dimToPrint==0) ? 0 : 4;
    yStart = (dimToPrint==1) ? 0 : 4;
    zStart = (dimToPrint==2) ? 0 : 4;
    xEnd = (dimToPrint==0) ? LATT_DIM_X : xStart+1;
    yEnd = (dimToPrint==1) ? LATT_DIM_Y : yStart+1;
    zEnd = (dimToPrint==2) ? LATT_DIM_Z : zStart+1;

    for(int z=zStart; z<zEnd; z++) {
        for(int y=yStart; y<yEnd; y++) {
            for(int x=xStart; x<xEnd; x++) {
                int index = IDX(x,y,z);
                float val = input[index];
                printf("%f\t", val);
            }
        }
    }
    printf("\n");
}

// Kernel to solve finite difference wave equation - output stores t-2 step, input stores t-1 step
#ifdef LOCKFREE
__global__ void wave_kernel(float* output_buffer, float* input_buffer, float vsq, float* coeff, int iterations,
                   volatile int* arrayIn, volatile int* arrayOut) {
#else
__global__ void wave_kernel(float* output_buffer, float* input_buffer, float vsq, float* coeff, int iterations) {
#endif
    const int bid_start = blockIdx.x;
    const int num_conc_blocks = gridDim.x;
    const int num_blocks_x = ((LATT_DIM_X-8)/blockDim.x) + (((LATT_DIM_X-8)%blockDim.x)?1:0);
    const int num_blocks_y = ((LATT_DIM_Y-8)/blockDim.y) + (((LATT_DIM_Y-8)%blockDim.y)?1:0);
    const int num_blocks_z = ((LATT_DIM_Z-8)/blockDim.z) + (((LATT_DIM_Z-8)%blockDim.z)?1:0);
    const int num_blocks = num_blocks_x*num_blocks_y*num_blocks_z;
    float* input = input_buffer;
    float* output = output_buffer;
    for(int i=0; i<iterations; i++) {
        for(int bid=bid_start; bid<num_blocks; bid+=num_conc_blocks) {
            // Get bid x,y,z from bid
            const int bidz = bid / (num_blocks_x*num_blocks_y);
            const int bidy = (bid % (num_blocks_x*num_blocks_y)) / num_blocks_x;
            const int bidx = bid % num_blocks_x;

            // Get tid x,y,z with offset of 4 included
            const int x = bidx*blockDim.x + threadIdx.x + 4;
            const int y = bidy*blockDim.y + threadIdx.y + 4;
            const int z = bidz*blockDim.z + threadIdx.z + 4;

            if(x<(LATT_DIM_X-4) and y<(LATT_DIM_Y-4) and z<(LATT_DIM_Z-4)) {
                // Do the computation
                float current = input[IDX(x,y,z)];
                float prev = output[IDX(x,y,z)];
                float temp = 2.0f*current - prev;
                float div = coeff[0] * current;
                div += coeff[1]*( input[IDX(x+1,y,z)] + input[IDX(x-1,y,z)] +
                                  input[IDX(x,y+1,z)] + input[IDX(x,y-1,z)] +
                                  input[IDX(x,y,z+1)] + input[IDX(x,y,z-1)] );
                div += coeff[2]*( input[IDX(x+2,y,z)] + input[IDX(x-2,y,z)] +
                                  input[IDX(x,y+2,z)] + input[IDX(x,y-2,z)] +
                                  input[IDX(x,y,z+2)] + input[IDX(x,y,z-2)] );
                div += coeff[3]*( input[IDX(x+3,y,z)] + input[IDX(x-3,y,z)] +
                                  input[IDX(x,y+3,z)] + input[IDX(x,y-3,z)] +
                                  input[IDX(x,y,z+3)] + input[IDX(x,y,z-3)] );
                div += coeff[4]*( input[IDX(x+4,y,z)] + input[IDX(x-4,y,z)] +
                                  input[IDX(x,y+4,z)] + input[IDX(x,y-4,z)] +
                                  input[IDX(x,y,z+4)] + input[IDX(x,y,z-4)] );
                output[IDX(x,y,z)] = temp + div*vsq;
            }
        }   // next block

        __threadfence();
//        __gpu_sync(i+1, arrayIn, arrayOut);
#ifdef LOCKFREE
        __syncblocks_lockfree(i+1, arrayIn, arrayOut);
#endif
#ifdef ATOMIC
        __syncblocks_atomic((i+1)*num_conc_blocks);
#endif
#ifdef HW_BARRIER
        __syncthreads();
#endif

        // Swap the buffers
        float* temp_buffer = input;
        input = output;
        output = temp_buffer;
    } // next iteration
}
/*
__device__ void __gpu_sync(int goalVal, volatile int* arrayIn, volatile int* arrayOut) {
    const int tid_in_block = threadIdx.z*(blockDim.x*blockDim.y) + threadIdx.y*(blockDim.x) + threadIdx.x;
    const int bid = blockIdx.x;
    const int num_conc_blocks = gridDim.x;

    // Notify that current block has reached sync
    if(tid_in_block == 0) {
        arrayIn[bid] = goalVal;
    }

    if(bid == 0) {
        if(tid_in_block < num_conc_blocks) {
            while(arrayIn[tid_in_block] != goalVal){
                // Wait for block to reach sync
            }
        }
        __syncthreads();

        // Notify all blocks of sync completion
        if(tid_in_block < num_conc_blocks) {
            arrayOut[tid_in_block] = goalVal;
        }
    }

    if(tid_in_block == 0) {
        while(arrayOut[bid] != goalVal) {
            // Wait for global sync notification
        }
    }
    __syncthreads();
}
*/

int main( int argc, const char** argv) {
	printf("[BENCH] Stencil-Wave <cxh@illinois.edu>\n");
#ifdef LOCKFREE
	printf("[BENCH] Lock Free Barrier\n");
#endif
#ifdef ATOMIC
	printf("[BENCH] Atomic Barrier\n");
#endif
#ifdef HW_BARRIER
	printf("[BENCH] Hardware Barrier\n");
#endif
   int thd_per_block_x = 8;
   int thd_per_block_y = 8;
   int thd_per_block_z = 8;

   // Get command line arguments if any
//   cutGetCmdLineArgumenti(argc, argv, "thdx", &thd_per_block_x);
//   cutGetCmdLineArgumenti(argc, argv, "thdy", &thd_per_block_y);
//   cutGetCmdLineArgumenti(argc, argv, "thdz", &thd_per_block_z);

   const int threads_per_block = thd_per_block_x*thd_per_block_y*thd_per_block_z;
   cudaDeviceProp prop;
   cudaGetDeviceProperties(&prop, 0);
   int num_blocks = prop.multiProcessorCount*2;
   printf("[BENCH] Block Size: %d (%d,%d,%d) \n", threads_per_block,
                   thd_per_block_x, thd_per_block_y, thd_per_block_z);
   printf("[BENCH] Number of Blocks: %d\n", num_blocks);

   // allocate host memory
   float* h_input_lattice_t0 = (float*) malloc( sizeof(float)*LATT_SIZE );
   float* h_input_lattice_t1 = (float*) malloc( sizeof(float)*LATT_SIZE );
   float vsq = 0.5f;
   float h_coeff[5] = {0.05f, -0.03f, 0.02f, -0.1f, 0.005f};
   const int iterations = 10;

   // Initialize input lattice on host side
   srand(2012);      // set seed for rand()
   generateInputLattice(h_input_lattice_t0, h_input_lattice_t1, vsq);

   // allocate and initialize device memory
   float* d_input_lattice_t0;
   float* d_input_lattice_t1;
   cutilSafeCall( cudaMalloc( (void**) &d_input_lattice_t0, sizeof(float)*LATT_SIZE));
   cutilSafeCall( cudaMalloc( (void**) &d_input_lattice_t1, sizeof(float)*LATT_SIZE));
   cutilSafeCall( cudaMemcpy( d_input_lattice_t0, h_input_lattice_t0, sizeof(float)*LATT_SIZE, cudaMemcpyHostToDevice) );
   cutilSafeCall( cudaMemcpy( d_input_lattice_t1, h_input_lattice_t1, sizeof(float)*LATT_SIZE, cudaMemcpyHostToDevice) );

   float* d_coeff;
   cutilSafeCall( cudaMalloc( (void**) &d_coeff, sizeof(float)*5));
   cutilSafeCall( cudaMemcpy( d_coeff, h_coeff, sizeof(float)*5, cudaMemcpyHostToDevice) );

   // Device memory for synchronization buffers
#ifdef LOCKFREE
   int* d_arrayIn;
   int* d_arrayOut;
   cutilSafeCall( cudaMalloc( (void**) &d_arrayIn, sizeof(int)*num_blocks));
   cutilSafeCall( cudaMalloc( (void**) &d_arrayOut, sizeof(int)*num_blocks));
   cutilSafeCall( cudaMemset( (void*) d_arrayIn, 0, sizeof(int)*num_blocks));
   cutilSafeCall( cudaMemset( (void*) d_arrayOut, 0, sizeof(int)*num_blocks));
#endif

   // setup execution parameters
   dim3 grid( num_blocks, 1, 1 );
   dim3 threads( thd_per_block_x, thd_per_block_y, thd_per_block_z );

   // execute the kernel
#ifdef LOCKFREE
   wave_kernel<<<grid,threads>>>(d_input_lattice_t0, d_input_lattice_t1, vsq, d_coeff, iterations, d_arrayIn, d_arrayOut);
#else
   wave_kernel<<<grid,threads>>>(d_input_lattice_t0, d_input_lattice_t1, vsq, d_coeff, iterations);
#endif
   CUT_CHECK_ERROR("Kernel execution failed")

   // allocate memory for the result on host side
   float* h_output_lattice = (float*) malloc( sizeof(float)*LATT_SIZE );
   float* d_output_lattice = (iterations%2)? d_input_lattice_t0 : d_input_lattice_t1;   // select correct output buffer
   // copy result from device to host
   cutilSafeCall( cudaMemcpy( h_output_lattice, d_output_lattice, sizeof(float)*LATT_SIZE, cudaMemcpyDeviceToHost) );
   // allocate memory for gold result
   float* h_result_lattice = (float*) malloc( sizeof(float)*LATT_SIZE );
   // Run gold version on CPU
   wave_gold(h_input_lattice_t0, h_input_lattice_t1, vsq, h_coeff, iterations, h_result_lattice);
   // Print error
   print_error(h_output_lattice, h_result_lattice);
   // cleanup memory
   free( h_input_lattice_t0 );
   free( h_input_lattice_t1 );
   free( h_output_lattice );
   cutilSafeCall(cudaFree(d_input_lattice_t0));
   cutilSafeCall(cudaFree(d_input_lattice_t1));
   cutilSafeCall(cudaFree(d_coeff));
   cudaThreadExit();
}

