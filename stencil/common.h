#ifndef COMMON_H
#define COMMON_H

#define Index3D(_nx,_ny,_i,_j,_k) ((_i)+_nx*((_j)+_ny*(_k)))
#define PI 3.1415926
//#define tx threadIdx.x
//#define bx blockIdx.x
//#define bs blockDim.x
#define BSX 32
#define BSY 4
#define BSZ 4
#define ATOMIC
//#define LOCKFREE
//#define HW_BARRIER

//#define TIMING
//#define NAIVE
//#define TILE_2D
//#define TILE_2D_OLD
#define TILE_3D
#define TILE_3D_NEW

#define CUDA_SAFE_CALL_NO_SYNC(call) {                                       \
    cudaError err = call;                                                    \
    if( cudaSuccess != err) {                                                \
        fprintf(stderr, "Cuda error in file '%s' in line %i : %s.\n",        \
                __FILE__, __LINE__, cudaGetErrorString( err) );              \
        exit(EXIT_FAILURE);                                                  \
    } }

#define CUDA_SAFE_CALL(call) CUDA_SAFE_CALL_NO_SYNC(call);

#define CUT_CHECK_ERROR(errorMessage) {                                      \
    cudaError_t err = cudaGetLastError();                                    \
    if( cudaSuccess != err) {                                                \
        fprintf(stderr, "Cuda error: %s in file '%s' in line %i : %s.\n",    \
                errorMessage, __FILE__, __LINE__, cudaGetErrorString( err) );\
        exit(EXIT_FAILURE);                                                  \
    }                                                                        \
  }

#endif
