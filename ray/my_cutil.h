#ifndef _MY_CUTIL_H_
#define _MY_CUTIL_H_

    #if __DEVICE_EMULATION__
        // Interface for bank conflict checker
    #define CUT_BANK_CHECKER( array, index)                                      \
        (cutCheckBankAccess( threadIdx.x, threadIdx.y, threadIdx.z, blockDim.x,  \
        blockDim.y, blockDim.z,                                                  \
        __FILE__, __LINE__, #array, index ),                                     \
        array[index])
    #else
    #define CUT_BANK_CHECKER( array, index)  array[index]
    #endif

#define CUDA_SAFE_CALL_NO_SYNC(call) {                                    \
    cudaError err = call;                                                    \
    if( cudaSuccess != err) {                                                \
        fprintf(stderr, "Cuda error in file '%s' in line %i : %s.\n",        \
                __FILE__, __LINE__, cudaGetErrorString( err) );              \
        exit(EXIT_FAILURE);                                                  \
    } }

#define CUDA_SAFE_CALL(call) CUDA_SAFE_CALL_NO_SYNC(call);

#endif // #ifndef _MY_CUTIL_H_
