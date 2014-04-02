#ifndef COMMON_H
#define COMMON_H

//#define tx threadIdx.x
//#define bx blockIdx.x
//#define bs blockDim.x

#define CUDA_SAFE_CALL_NO_SYNC(call) {                                       \
    cudaError err = call;                                                    \
    if( cudaSuccess != err) {                                                \
        fprintf(stderr, "Cuda error in file '%s' in line %i : %s.\n",        \
                __FILE__, __LINE__, cudaGetErrorString( err) );              \
        exit(EXIT_FAILURE);                                                  \
    } }

#define CUDA_SAFE_CALL(call) CUDA_SAFE_CALL_NO_SYNC(call);
#define cutilSafeCall(call) CUDA_SAFE_CALL(call)
#define CUT_CHECK_ERROR(errorMessage) {                                      \
    cudaError_t err = cudaGetLastError();                                    \
    if( cudaSuccess != err) {                                                \
        fprintf(stderr, "Cuda error: %s in file '%s' in line %i : %s.\n",    \
                errorMessage, __FILE__, __LINE__, cudaGetErrorString( err) );\
        exit(EXIT_FAILURE);                                                  \
    }                                                                        \
  }
#define cutilCheckMsg(errorMessage) CUT_CHECK_ERROR(errorMessage)
#endif
