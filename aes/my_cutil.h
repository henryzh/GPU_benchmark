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

#endif // #ifndef _MY_CUTIL_H_
