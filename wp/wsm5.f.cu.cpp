# 1 "/tmp/tmpxft_00003075_00000000-4_wsm5.f.compute_10.cudafe1.cpp"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "/tmp/tmpxft_00003075_00000000-4_wsm5.f.compute_10.cudafe1.cpp"
# 1 "wsm5.f.cu"
# 60 "/home/hangzhang/local/cuda/4.0/bin/../include/device_types.h"
# 149 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/include/stddef.h" 3
typedef long ptrdiff_t;
# 211 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/include/stddef.h" 3
typedef unsigned long size_t;
# 1 "/home/hangzhang/local/cuda/4.0/bin/../include/crt/host_runtime.h" 1 3
# 69 "/home/hangzhang/local/cuda/4.0/bin/../include/crt/host_runtime.h" 3
# 1 "/home/hangzhang/local/cuda/4.0/bin/../include/builtin_types.h" 1 3
# 56 "/home/hangzhang/local/cuda/4.0/bin/../include/builtin_types.h" 3
# 1 "/home/hangzhang/local/cuda/4.0/bin/../include/device_types.h" 1 3
# 60 "/home/hangzhang/local/cuda/4.0/bin/../include/device_types.h" 3
enum cudaRoundMode
{
  cudaRoundNearest,
  cudaRoundZero,
  cudaRoundPosInf,
  cudaRoundMinInf
};
# 57 "/home/hangzhang/local/cuda/4.0/bin/../include/builtin_types.h" 2 3
# 1 "/home/hangzhang/local/cuda/4.0/bin/../include/driver_types.h" 1 3
# 118 "/home/hangzhang/local/cuda/4.0/bin/../include/driver_types.h" 3
enum cudaError
{





  cudaSuccess = 0,





  cudaErrorMissingConfiguration = 1,





  cudaErrorMemoryAllocation = 2,





  cudaErrorInitializationError = 3,
# 153 "/home/hangzhang/local/cuda/4.0/bin/../include/driver_types.h" 3
  cudaErrorLaunchFailure = 4,
# 162 "/home/hangzhang/local/cuda/4.0/bin/../include/driver_types.h" 3
  cudaErrorPriorLaunchFailure = 5,
# 172 "/home/hangzhang/local/cuda/4.0/bin/../include/driver_types.h" 3
  cudaErrorLaunchTimeout = 6,
# 181 "/home/hangzhang/local/cuda/4.0/bin/../include/driver_types.h" 3
  cudaErrorLaunchOutOfResources = 7,





  cudaErrorInvalidDeviceFunction = 8,
# 196 "/home/hangzhang/local/cuda/4.0/bin/../include/driver_types.h" 3
  cudaErrorInvalidConfiguration = 9,





  cudaErrorInvalidDevice = 10,





  cudaErrorInvalidValue = 11,





  cudaErrorInvalidPitchValue = 12,





  cudaErrorInvalidSymbol = 13,




  cudaErrorMapBufferObjectFailed = 14,




  cudaErrorUnmapBufferObjectFailed = 15,





  cudaErrorInvalidHostPointer = 16,





  cudaErrorInvalidDevicePointer = 17,





  cudaErrorInvalidTexture = 18,





  cudaErrorInvalidTextureBinding = 19,






  cudaErrorInvalidChannelDescriptor = 20,





  cudaErrorInvalidMemcpyDirection = 21,
# 277 "/home/hangzhang/local/cuda/4.0/bin/../include/driver_types.h" 3
  cudaErrorAddressOfConstant = 22,
# 286 "/home/hangzhang/local/cuda/4.0/bin/../include/driver_types.h" 3
  cudaErrorTextureFetchFailed = 23,
# 295 "/home/hangzhang/local/cuda/4.0/bin/../include/driver_types.h" 3
  cudaErrorTextureNotBound = 24,
# 304 "/home/hangzhang/local/cuda/4.0/bin/../include/driver_types.h" 3
  cudaErrorSynchronizationError = 25,





  cudaErrorInvalidFilterSetting = 26,





  cudaErrorInvalidNormSetting = 27,







  cudaErrorMixedDeviceExecution = 28,







  cudaErrorCudartUnloading = 29,




  cudaErrorUnknown = 30,





  cudaErrorNotYetImplemented = 31,
# 352 "/home/hangzhang/local/cuda/4.0/bin/../include/driver_types.h" 3
  cudaErrorMemoryValueTooLarge = 32,






  cudaErrorInvalidResourceHandle = 33,







  cudaErrorNotReady = 34,






  cudaErrorInsufficientDriver = 35,
# 387 "/home/hangzhang/local/cuda/4.0/bin/../include/driver_types.h" 3
  cudaErrorSetOnActiveProcess = 36,





  cudaErrorInvalidSurface = 37,





  cudaErrorNoDevice = 38,





  cudaErrorECCUncorrectable = 39,




  cudaErrorSharedObjectSymbolNotFound = 40,




  cudaErrorSharedObjectInitFailed = 41,





  cudaErrorUnsupportedLimit = 42,





  cudaErrorDuplicateVariableName = 43,





  cudaErrorDuplicateTextureName = 44,





  cudaErrorDuplicateSurfaceName = 45,
# 449 "/home/hangzhang/local/cuda/4.0/bin/../include/driver_types.h" 3
  cudaErrorDevicesUnavailable = 46,




  cudaErrorInvalidKernelImage = 47,







  cudaErrorNoKernelImageForDevice = 48,
# 475 "/home/hangzhang/local/cuda/4.0/bin/../include/driver_types.h" 3
  cudaErrorIncompatibleDriverContext = 49,






  cudaErrorPeerAccessAlreadyEnabled = 50,






  cudaErrorPeerAccessNotEnabled = 51,





  cudaErrorDeviceAlreadyInUse = 54,







  cudaErrorProfilerDisabled = 55,






  cudaErrorProfilerNotInitialized = 56,






  cudaErrorProfilerAlreadyStarted = 57,





   cudaErrorProfilerAlreadyStopped = 58,




  cudaErrorStartupFailure = 0x7f,





  cudaErrorApiFailureBase = 10000
};





enum cudaChannelFormatKind
{
  cudaChannelFormatKindSigned = 0,
  cudaChannelFormatKindUnsigned = 1,
  cudaChannelFormatKindFloat = 2,
  cudaChannelFormatKindNone = 3
};





struct cudaChannelFormatDesc
{
  int x;
  int y;
  int z;
  int w;
  enum cudaChannelFormatKind f;
};





struct cudaArray;





enum cudaMemoryType
{
  cudaMemoryTypeHost = 1,
  cudaMemoryTypeDevice = 2
};





enum cudaMemcpyKind
{
  cudaMemcpyHostToHost = 0,
  cudaMemcpyHostToDevice = 1,
  cudaMemcpyDeviceToHost = 2,
  cudaMemcpyDeviceToDevice = 3,
  cudaMemcpyDefault = 4
};






struct cudaPitchedPtr
{
  void *ptr;
  size_t pitch;
  size_t xsize;
  size_t ysize;
};






struct cudaExtent
{
  size_t width;
  size_t height;
  size_t depth;
};






struct cudaPos
{
  size_t x;
  size_t y;
  size_t z;
};





struct cudaMemcpy3DParms
{
  struct cudaArray *srcArray;
  struct cudaPos srcPos;
  struct cudaPitchedPtr srcPtr;

  struct cudaArray *dstArray;
  struct cudaPos dstPos;
  struct cudaPitchedPtr dstPtr;

  struct cudaExtent extent;
  enum cudaMemcpyKind kind;
};





struct cudaMemcpy3DPeerParms
{
  struct cudaArray *srcArray;
  struct cudaPos srcPos;
  struct cudaPitchedPtr srcPtr;
  int srcDevice;

  struct cudaArray *dstArray;
  struct cudaPos dstPos;
  struct cudaPitchedPtr dstPtr;
  int dstDevice;

  struct cudaExtent extent;
};





struct cudaGraphicsResource;





enum cudaGraphicsRegisterFlags
{
  cudaGraphicsRegisterFlagsNone = 0,
  cudaGraphicsRegisterFlagsReadOnly = 1,
  cudaGraphicsRegisterFlagsWriteDiscard = 2,
  cudaGraphicsRegisterFlagsSurfaceLoadStore = 4
};





enum cudaGraphicsMapFlags
{
  cudaGraphicsMapFlagsNone = 0,
  cudaGraphicsMapFlagsReadOnly = 1,
  cudaGraphicsMapFlagsWriteDiscard = 2
};





enum cudaGraphicsCubeFace {
  cudaGraphicsCubeFacePositiveX = 0x00,
  cudaGraphicsCubeFaceNegativeX = 0x01,
  cudaGraphicsCubeFacePositiveY = 0x02,
  cudaGraphicsCubeFaceNegativeY = 0x03,
  cudaGraphicsCubeFacePositiveZ = 0x04,
  cudaGraphicsCubeFaceNegativeZ = 0x05
};





struct cudaPointerAttributes
{




    enum cudaMemoryType memoryType;
# 728 "/home/hangzhang/local/cuda/4.0/bin/../include/driver_types.h" 3
    int device;





    void *devicePointer;





    void *hostPointer;
};





struct cudaFuncAttributes
{





   size_t sharedSizeBytes;





   size_t constSizeBytes;




   size_t localSizeBytes;






   int maxThreadsPerBlock;




   int numRegs;






   int ptxVersion;






   int binaryVersion;
};





enum cudaFuncCache
{
  cudaFuncCachePreferNone = 0,
  cudaFuncCachePreferShared = 1,
  cudaFuncCachePreferL1 = 2
};





enum cudaComputeMode
{
  cudaComputeModeDefault = 0,
  cudaComputeModeExclusive = 1,
  cudaComputeModeProhibited = 2,
  cudaComputeModeExclusiveProcess = 3
};





enum cudaLimit
{
    cudaLimitStackSize = 0x00,
    cudaLimitPrintfFifoSize = 0x01,
    cudaLimitMallocHeapSize = 0x02
};





enum cudaOutputMode
{
    cudaKeyValuePair = 0x00,
    cudaCSV = 0x01
};





struct cudaDeviceProp
{
  char name[256];
  size_t totalGlobalMem;
  size_t sharedMemPerBlock;
  int regsPerBlock;
  int warpSize;
  size_t memPitch;
  int maxThreadsPerBlock;
  int maxThreadsDim[3];
  int maxGridSize[3];
  int clockRate;
  size_t totalConstMem;
  int major;
  int minor;
  size_t textureAlignment;
  int deviceOverlap;
  int multiProcessorCount;
  int kernelExecTimeoutEnabled;
  int integrated;
  int canMapHostMemory;
  int computeMode;
  int maxTexture1D;
  int maxTexture2D[2];
  int maxTexture3D[3];
  int maxTexture1DLayered[2];
  int maxTexture2DLayered[3];
  size_t surfaceAlignment;
  int concurrentKernels;
  int ECCEnabled;
  int pciBusID;
  int pciDeviceID;
  int pciDomainID;
  int tccDriver;
  int asyncEngineCount;
  int unifiedAddressing;
  int memoryClockRate;
  int memoryBusWidth;
  int l2CacheSize;
  int maxThreadsPerMultiProcessor;
};
# 936 "/home/hangzhang/local/cuda/4.0/bin/../include/driver_types.h" 3
typedef enum cudaError cudaError_t;





typedef struct CUstream_st *cudaStream_t;





typedef struct CUevent_st *cudaEvent_t;





typedef struct cudaGraphicsResource *cudaGraphicsResource_t;





typedef struct CUuuid_st cudaUUID_t;





typedef enum cudaOutputMode cudaOutputMode_t;
# 58 "/home/hangzhang/local/cuda/4.0/bin/../include/builtin_types.h" 2 3
# 1 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_types.h" 1 3
# 77 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_types.h" 3
enum cudaSurfaceBoundaryMode
{
  cudaBoundaryModeZero = 0,
  cudaBoundaryModeClamp = 1,
  cudaBoundaryModeTrap = 2
};





enum cudaSurfaceFormatMode
{
  cudaFormatModeForced = 0,
  cudaFormatModeAuto = 1
};





struct surfaceReference
{



  struct cudaChannelFormatDesc channelDesc;
};
# 59 "/home/hangzhang/local/cuda/4.0/bin/../include/builtin_types.h" 2 3
# 1 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_types.h" 1 3
# 83 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_types.h" 3
enum cudaTextureAddressMode
{
  cudaAddressModeWrap = 0,
  cudaAddressModeClamp = 1,
  cudaAddressModeMirror = 2,
  cudaAddressModeBorder = 3
};





enum cudaTextureFilterMode
{
  cudaFilterModePoint = 0,
  cudaFilterModeLinear = 1
};





enum cudaTextureReadMode
{
  cudaReadModeElementType = 0,
  cudaReadModeNormalizedFloat = 1
};





struct textureReference
{



  int normalized;



  enum cudaTextureFilterMode filterMode;



  enum cudaTextureAddressMode addressMode[3];



  struct cudaChannelFormatDesc channelDesc;



  int sRGB;
  int __cudaReserved[15];
};
# 60 "/home/hangzhang/local/cuda/4.0/bin/../include/builtin_types.h" 2 3
# 1 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h" 1 3
# 59 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h" 3
# 1 "/home/hangzhang/local/cuda/4.0/bin/../include/builtin_types.h" 1 3
# 60 "/home/hangzhang/local/cuda/4.0/bin/../include/builtin_types.h" 3
# 1 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h" 1 3
# 60 "/home/hangzhang/local/cuda/4.0/bin/../include/builtin_types.h" 2 3
# 60 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h" 2 3
# 1 "/home/hangzhang/local/cuda/4.0/bin/../include/host_defines.h" 1 3
# 61 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h" 2 3
# 92 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h" 3
struct char1
{
  signed char x;
};


struct uchar1
{
  unsigned char x;
};


struct __attribute__((aligned(2))) char2
{
  signed char x, y;
};


struct __attribute__((aligned(2))) uchar2
{
  unsigned char x, y;
};


struct char3
{
  signed char x, y, z;
};


struct uchar3
{
  unsigned char x, y, z;
};


struct __attribute__((aligned(4))) char4
{
  signed char x, y, z, w;
};


struct __attribute__((aligned(4))) uchar4
{
  unsigned char x, y, z, w;
};


struct short1
{
  short x;
};


struct ushort1
{
  unsigned short x;
};


struct __attribute__((aligned(4))) short2
{
  short x, y;
};


struct __attribute__((aligned(4))) ushort2
{
  unsigned short x, y;
};


struct short3
{
  short x, y, z;
};


struct ushort3
{
  unsigned short x, y, z;
};


struct __attribute__((aligned(8))) short4 { short x; short y; short z; short w; };


struct __attribute__((aligned(8))) ushort4 { unsigned short x; unsigned short y; unsigned short z; unsigned short w; };


struct int1
{
  int x;
};


struct uint1
{
  unsigned int x;
};


struct __attribute__((aligned(8))) int2 { int x; int y; };


struct __attribute__((aligned(8))) uint2 { unsigned int x; unsigned int y; };


struct int3
{
  int x, y, z;
};


struct uint3
{
  unsigned int x, y, z;
};


struct __attribute__((aligned(16))) int4
{
  int x, y, z, w;
};


struct __attribute__((aligned(16))) uint4
{
  unsigned int x, y, z, w;
};


struct long1
{
  long int x;
};


struct ulong1
{
  unsigned long x;
};
# 246 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h" 3
struct __attribute__((aligned(2*sizeof(long int)))) long2
{
  long int x, y;
};


struct __attribute__((aligned(2*sizeof(unsigned long int)))) ulong2
{
  unsigned long int x, y;
};




struct long3
{
  long int x, y, z;
};


struct ulong3
{
  unsigned long int x, y, z;
};


struct __attribute__((aligned(16))) long4
{
  long int x, y, z, w;
};


struct __attribute__((aligned(16))) ulong4
{
  unsigned long int x, y, z, w;
};


struct float1
{
  float x;
};


struct __attribute__((aligned(8))) float2 { float x; float y; };


struct float3
{
  float x, y, z;
};


struct __attribute__((aligned(16))) float4
{
  float x, y, z, w;
};


struct longlong1
{
  long long int x;
};


struct ulonglong1
{
  unsigned long long int x;
};


struct __attribute__((aligned(16))) longlong2
{
  long long int x, y;
};


struct __attribute__((aligned(16))) ulonglong2
{
  unsigned long long int x, y;
};


struct longlong3
{
  long long int x, y, z;
};


struct ulonglong3
{
  unsigned long long int x, y, z;
};


struct __attribute__((aligned(16))) longlong4
{
  long long int x, y, z ,w;
};


struct __attribute__((aligned(16))) ulonglong4
{
  unsigned long long int x, y, z, w;
};


struct double1
{
  double x;
};


struct __attribute__((aligned(16))) double2
{
  double x, y;
};


struct double3
{
  double x, y, z;
};


struct __attribute__((aligned(16))) double4
{
  double x, y, z, w;
};
# 390 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h" 3
typedef struct char1 char1;

typedef struct uchar1 uchar1;

typedef struct char2 char2;

typedef struct uchar2 uchar2;

typedef struct char3 char3;

typedef struct uchar3 uchar3;

typedef struct char4 char4;

typedef struct uchar4 uchar4;

typedef struct short1 short1;

typedef struct ushort1 ushort1;

typedef struct short2 short2;

typedef struct ushort2 ushort2;

typedef struct short3 short3;

typedef struct ushort3 ushort3;

typedef struct short4 short4;

typedef struct ushort4 ushort4;

typedef struct int1 int1;

typedef struct uint1 uint1;

typedef struct int2 int2;

typedef struct uint2 uint2;

typedef struct int3 int3;

typedef struct uint3 uint3;

typedef struct int4 int4;

typedef struct uint4 uint4;

typedef struct long1 long1;

typedef struct ulong1 ulong1;

typedef struct long2 long2;

typedef struct ulong2 ulong2;

typedef struct long3 long3;

typedef struct ulong3 ulong3;

typedef struct long4 long4;

typedef struct ulong4 ulong4;

typedef struct float1 float1;

typedef struct float2 float2;

typedef struct float3 float3;

typedef struct float4 float4;

typedef struct longlong1 longlong1;

typedef struct ulonglong1 ulonglong1;

typedef struct longlong2 longlong2;

typedef struct ulonglong2 ulonglong2;

typedef struct longlong3 longlong3;

typedef struct ulonglong3 ulonglong3;

typedef struct longlong4 longlong4;

typedef struct ulonglong4 ulonglong4;

typedef struct double1 double1;

typedef struct double2 double2;

typedef struct double3 double3;

typedef struct double4 double4;
# 493 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h" 3
struct dim3
{
    unsigned int x, y, z;

    dim3(unsigned int vx = 1, unsigned int vy = 1, unsigned int vz = 1) : x(vx), y(vy), z(vz) {}
    dim3(uint3 v) : x(v.x), y(v.y), z(v.z) {}
    operator uint3(void) { uint3 t; t.x = x; t.y = y; t.z = z; return t; }

};


typedef struct dim3 dim3;
# 60 "/home/hangzhang/local/cuda/4.0/bin/../include/builtin_types.h" 2 3
# 70 "/home/hangzhang/local/cuda/4.0/bin/../include/crt/host_runtime.h" 2 3
# 1 "/home/hangzhang/local/cuda/4.0/bin/../include/crt/storage_class.h" 1 3
# 71 "/home/hangzhang/local/cuda/4.0/bin/../include/crt/host_runtime.h" 2 3
# 213 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/include/stddef.h" 2 3
# 118 "/home/hangzhang/local/cuda/4.0/bin/../include/driver_types.h"
# 541 "/home/hangzhang/local/cuda/4.0/bin/../include/driver_types.h"
# 553 "/home/hangzhang/local/cuda/4.0/bin/../include/driver_types.h"
# 566 "/home/hangzhang/local/cuda/4.0/bin/../include/driver_types.h"
# 572 "/home/hangzhang/local/cuda/4.0/bin/../include/driver_types.h"
# 582 "/home/hangzhang/local/cuda/4.0/bin/../include/driver_types.h"
# 596 "/home/hangzhang/local/cuda/4.0/bin/../include/driver_types.h"
# 609 "/home/hangzhang/local/cuda/4.0/bin/../include/driver_types.h"
# 621 "/home/hangzhang/local/cuda/4.0/bin/../include/driver_types.h"
# 632 "/home/hangzhang/local/cuda/4.0/bin/../include/driver_types.h"
# 650 "/home/hangzhang/local/cuda/4.0/bin/../include/driver_types.h"
# 669 "/home/hangzhang/local/cuda/4.0/bin/../include/driver_types.h"
# 675 "/home/hangzhang/local/cuda/4.0/bin/../include/driver_types.h"
# 687 "/home/hangzhang/local/cuda/4.0/bin/../include/driver_types.h"
# 698 "/home/hangzhang/local/cuda/4.0/bin/../include/driver_types.h"
# 711 "/home/hangzhang/local/cuda/4.0/bin/../include/driver_types.h"
# 747 "/home/hangzhang/local/cuda/4.0/bin/../include/driver_types.h"
# 798 "/home/hangzhang/local/cuda/4.0/bin/../include/driver_types.h"
# 809 "/home/hangzhang/local/cuda/4.0/bin/../include/driver_types.h"
# 821 "/home/hangzhang/local/cuda/4.0/bin/../include/driver_types.h"
# 832 "/home/hangzhang/local/cuda/4.0/bin/../include/driver_types.h"
# 842 "/home/hangzhang/local/cuda/4.0/bin/../include/driver_types.h"
# 936 "/home/hangzhang/local/cuda/4.0/bin/../include/driver_types.h"
# 942 "/home/hangzhang/local/cuda/4.0/bin/../include/driver_types.h"
# 948 "/home/hangzhang/local/cuda/4.0/bin/../include/driver_types.h"
# 954 "/home/hangzhang/local/cuda/4.0/bin/../include/driver_types.h"
# 960 "/home/hangzhang/local/cuda/4.0/bin/../include/driver_types.h"
# 966 "/home/hangzhang/local/cuda/4.0/bin/../include/driver_types.h"
# 77 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_types.h"
# 88 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_types.h"
# 98 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_types.h"
# 83 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_types.h"
# 95 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_types.h"
# 105 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_types.h"
# 115 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_types.h"
# 92 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 98 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 104 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 110 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 116 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 122 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 128 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 134 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 140 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 146 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 152 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 158 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 164 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 170 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 176 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 179 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 182 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 188 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 194 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 197 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 200 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 206 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 212 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 218 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 224 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 230 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 246 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 252 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 260 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 266 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 272 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 278 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 284 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 290 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 293 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 299 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 305 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 311 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 317 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 323 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 329 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 335 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 341 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 347 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 353 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 359 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 365 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 371 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 390 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 392 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 394 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 396 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 398 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 400 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 402 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 404 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 406 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 408 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 410 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 412 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 414 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 416 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 418 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 420 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 422 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 424 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 426 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 428 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 430 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 432 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 434 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 436 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 438 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 440 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 442 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 444 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 446 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 448 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 450 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 452 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 454 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 456 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 458 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 460 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 462 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 464 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 466 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 468 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 470 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 472 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 474 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 476 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 478 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 480 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 482 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 484 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 493 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 504 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_types.h"
# 134 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaDeviceReset();
# 151 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaDeviceSynchronize();
# 203 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaDeviceSetLimit(cudaLimit , size_t );
# 227 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaDeviceGetLimit(size_t * , cudaLimit );
# 257 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaDeviceGetCacheConfig(cudaFuncCache * );
# 298 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaDeviceSetCacheConfig(cudaFuncCache );
# 332 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaThreadExit();
# 356 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaThreadSynchronize();
# 415 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaThreadSetLimit(cudaLimit , size_t );
# 446 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaThreadGetLimit(size_t * , cudaLimit );
# 481 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaThreadGetCacheConfig(cudaFuncCache * );
# 527 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaThreadSetCacheConfig(cudaFuncCache );
# 581 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaGetLastError();
# 624 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaPeekAtLastError();
# 638 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" const char *cudaGetErrorString(cudaError_t );
# 668 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaGetDeviceCount(int * );
# 829 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaGetDeviceProperties(cudaDeviceProp * , int );
# 848 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaChooseDevice(int * , const cudaDeviceProp * );
# 881 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaSetDevice(int );
# 898 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaGetDevice(int * );
# 927 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaSetValidDevices(int * , int );
# 987 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaSetDeviceFlags(unsigned );
# 1013 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaStreamCreate(cudaStream_t * );
# 1034 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaStreamDestroy(cudaStream_t );
# 1070 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaStreamWaitEvent(cudaStream_t , cudaEvent_t , unsigned );
# 1089 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaStreamSynchronize(cudaStream_t );
# 1107 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaStreamQuery(cudaStream_t );
# 1139 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaEventCreate(cudaEvent_t * );
# 1170 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaEventCreateWithFlags(cudaEvent_t * , unsigned );
# 1203 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaEventRecord(cudaEvent_t , cudaStream_t = 0);
# 1232 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaEventQuery(cudaEvent_t );
# 1264 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaEventSynchronize(cudaEvent_t );
# 1289 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaEventDestroy(cudaEvent_t );
# 1330 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaEventElapsedTime(float * , cudaEvent_t , cudaEvent_t );
# 1369 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaConfigureCall(dim3 , dim3 , size_t = (0), cudaStream_t = 0);
# 1396 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaSetupArgument(const void * , size_t , size_t );
# 1442 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaFuncSetCacheConfig(const char * , cudaFuncCache );
# 1477 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaLaunch(const char * );
# 1510 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaFuncGetAttributes(cudaFuncAttributes * , const char * );
# 1532 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaSetDoubleForDevice(double * );
# 1554 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaSetDoubleForHost(double * );
# 1586 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaMalloc(void ** , size_t );
# 1615 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaMallocHost(void ** , size_t );
# 1654 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaMallocPitch(void ** , size_t * , size_t , size_t );
# 1693 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaMallocArray(cudaArray ** , const cudaChannelFormatDesc * , size_t , size_t = (0), unsigned = (0));
# 1717 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaFree(void * );
# 1737 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaFreeHost(void * );
# 1759 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaFreeArray(cudaArray * );
# 1818 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaHostAlloc(void ** , size_t , unsigned );
# 1874 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaHostRegister(void * , size_t , unsigned );
# 1893 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaHostUnregister(void * );
# 1920 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaHostGetDevicePointer(void ** , void * , unsigned );
# 1939 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaHostGetFlags(unsigned * , void * );
# 1974 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaMalloc3D(cudaPitchedPtr * , cudaExtent );
# 2035 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaMalloc3DArray(cudaArray ** , const cudaChannelFormatDesc * , cudaExtent , unsigned = (0));
# 2132 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaMemcpy3D(const cudaMemcpy3DParms * );
# 2159 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaMemcpy3DPeer(const cudaMemcpy3DPeerParms * );
# 2264 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaMemcpy3DAsync(const cudaMemcpy3DParms * , cudaStream_t = 0);
# 2285 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaMemcpy3DPeerAsync(const cudaMemcpy3DPeerParms * , cudaStream_t = 0);
# 2304 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaMemGetInfo(size_t * , size_t * );
# 2337 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaMemcpy(void * , const void * , size_t , cudaMemcpyKind );
# 2368 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaMemcpyPeer(void * , int , const void * , int , size_t );
# 2401 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaMemcpyToArray(cudaArray * , size_t , size_t , const void * , size_t , cudaMemcpyKind );
# 2434 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaMemcpyFromArray(void * , const cudaArray * , size_t , size_t , size_t , cudaMemcpyKind );
# 2469 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaMemcpyArrayToArray(cudaArray * , size_t , size_t , const cudaArray * , size_t , size_t , size_t , cudaMemcpyKind = cudaMemcpyDeviceToDevice);
# 2511 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaMemcpy2D(void * , size_t , const void * , size_t , size_t , size_t , cudaMemcpyKind );
# 2552 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaMemcpy2DToArray(cudaArray * , size_t , size_t , const void * , size_t , size_t , size_t , cudaMemcpyKind );
# 2593 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaMemcpy2DFromArray(void * , size_t , const cudaArray * , size_t , size_t , size_t , size_t , cudaMemcpyKind );
# 2632 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaMemcpy2DArrayToArray(cudaArray * , size_t , size_t , const cudaArray * , size_t , size_t , size_t , size_t , cudaMemcpyKind = cudaMemcpyDeviceToDevice);
# 2667 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaMemcpyToSymbol(const char * , const void * , size_t , size_t = (0), cudaMemcpyKind = cudaMemcpyHostToDevice);
# 2701 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaMemcpyFromSymbol(void * , const char * , size_t , size_t = (0), cudaMemcpyKind = cudaMemcpyDeviceToHost);
# 2744 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaMemcpyAsync(void * , const void * , size_t , cudaMemcpyKind , cudaStream_t = 0);
# 2774 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaMemcpyPeerAsync(void * , int , const void * , int , size_t , cudaStream_t = 0);
# 2816 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaMemcpyToArrayAsync(cudaArray * , size_t , size_t , const void * , size_t , cudaMemcpyKind , cudaStream_t = 0);
# 2858 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaMemcpyFromArrayAsync(void * , const cudaArray * , size_t , size_t , size_t , cudaMemcpyKind , cudaStream_t = 0);
# 2909 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaMemcpy2DAsync(void * , size_t , const void * , size_t , size_t , size_t , cudaMemcpyKind , cudaStream_t = 0);
# 2959 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaMemcpy2DToArrayAsync(cudaArray * , size_t , size_t , const void * , size_t , size_t , size_t , cudaMemcpyKind , cudaStream_t = 0);
# 3009 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaMemcpy2DFromArrayAsync(void * , size_t , const cudaArray * , size_t , size_t , size_t , size_t , cudaMemcpyKind , cudaStream_t = 0);
# 3053 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaMemcpyToSymbolAsync(const char * , const void * , size_t , size_t , cudaMemcpyKind , cudaStream_t = 0);
# 3096 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaMemcpyFromSymbolAsync(void * , const char * , size_t , size_t , cudaMemcpyKind , cudaStream_t = 0);
# 3118 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaMemset(void * , int , size_t );
# 3144 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaMemset2D(void * , size_t , int , size_t , size_t );
# 3183 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaMemset3D(cudaPitchedPtr , int , cudaExtent );
# 3210 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaMemsetAsync(void * , int , size_t , cudaStream_t = 0);
# 3242 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaMemset2DAsync(void * , size_t , int , size_t , size_t , cudaStream_t = 0);
# 3287 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaMemset3DAsync(cudaPitchedPtr , int , cudaExtent , cudaStream_t = 0);
# 3314 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaGetSymbolAddress(void ** , const char * );
# 3337 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaGetSymbolSize(size_t * , const char * );
# 3482 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaPointerGetAttributes(cudaPointerAttributes * , void * );
# 3516 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaDeviceCanAccessPeer(int * , int , int );
# 3557 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaDeviceEnablePeerAccess(int , unsigned );
# 3582 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaDeviceDisablePeerAccess(int );
# 3628 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaGraphicsUnregisterResource(cudaGraphicsResource_t );
# 3660 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaGraphicsResourceSetMapFlags(cudaGraphicsResource_t , unsigned );
# 3695 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaGraphicsMapResources(int , cudaGraphicsResource_t * , cudaStream_t = 0);
# 3726 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaGraphicsUnmapResources(int , cudaGraphicsResource_t * , cudaStream_t = 0);
# 3755 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaGraphicsResourceGetMappedPointer(void ** , size_t * , cudaGraphicsResource_t );
# 3789 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaGraphicsSubResourceGetMappedArray(cudaArray ** , cudaGraphicsResource_t , unsigned , unsigned );
# 3822 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaGetChannelDesc(cudaChannelFormatDesc * , const cudaArray * );
# 3857 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaChannelFormatDesc cudaCreateChannelDesc(int , int , int , int , cudaChannelFormatKind );
# 3899 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaBindTexture(size_t * , const textureReference * , const void * , const cudaChannelFormatDesc * , size_t = (((2147483647) * 2U) + 1U));
# 3942 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaBindTexture2D(size_t * , const textureReference * , const void * , const cudaChannelFormatDesc * , size_t , size_t , size_t );
# 3970 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaBindTextureToArray(const textureReference * , const cudaArray * , const cudaChannelFormatDesc * );
# 3991 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaUnbindTexture(const textureReference * );
# 4016 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaGetTextureAlignmentOffset(size_t * , const textureReference * );
# 4040 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaGetTextureReference(const textureReference ** , const char * );
# 4073 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaBindSurfaceToArray(const surfaceReference * , const cudaArray * , const cudaChannelFormatDesc * );
# 4091 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaGetSurfaceReference(const surfaceReference ** , const char * );
# 4118 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaDriverGetVersion(int * );
# 4135 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaRuntimeGetVersion(int * );
# 4140 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime_api.h"
extern "C" cudaError_t cudaGetExportTable(const void ** , const cudaUUID_t * );
# 107 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
template< class T> inline cudaChannelFormatDesc cudaCreateChannelDesc()
# 108 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
{
# 109 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
return cudaCreateChannelDesc(0, 0, 0, 0, cudaChannelFormatKindNone);
# 110 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
}
# 112 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
static inline cudaChannelFormatDesc cudaCreateChannelDescHalf()
# 113 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
{
# 114 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
int e = (((int)sizeof(unsigned short)) * 8);
# 116 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
return cudaCreateChannelDesc(e, 0, 0, 0, cudaChannelFormatKindFloat);
# 117 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
}
# 119 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
static inline cudaChannelFormatDesc cudaCreateChannelDescHalf1()
# 120 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
{
# 121 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
int e = (((int)sizeof(unsigned short)) * 8);
# 123 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
return cudaCreateChannelDesc(e, 0, 0, 0, cudaChannelFormatKindFloat);
# 124 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
}
# 126 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
static inline cudaChannelFormatDesc cudaCreateChannelDescHalf2()
# 127 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
{
# 128 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
int e = (((int)sizeof(unsigned short)) * 8);
# 130 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
return cudaCreateChannelDesc(e, e, 0, 0, cudaChannelFormatKindFloat);
# 131 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
}
# 133 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
static inline cudaChannelFormatDesc cudaCreateChannelDescHalf4()
# 134 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
{
# 135 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
int e = (((int)sizeof(unsigned short)) * 8);
# 137 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
return cudaCreateChannelDesc(e, e, e, e, cudaChannelFormatKindFloat);
# 138 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
}
# 140 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
template<> inline cudaChannelFormatDesc cudaCreateChannelDesc< char> ()
# 141 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
{
# 142 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
int e = (((int)sizeof(char)) * 8);
# 147 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
return cudaCreateChannelDesc(e, 0, 0, 0, cudaChannelFormatKindSigned);
# 149 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
}
# 151 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
template<> inline cudaChannelFormatDesc cudaCreateChannelDesc< signed char> ()
# 152 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
{
# 153 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
int e = (((int)sizeof(signed char)) * 8);
# 155 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
return cudaCreateChannelDesc(e, 0, 0, 0, cudaChannelFormatKindSigned);
# 156 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
}
# 158 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
template<> inline cudaChannelFormatDesc cudaCreateChannelDesc< unsigned char> ()
# 159 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
{
# 160 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
int e = (((int)sizeof(unsigned char)) * 8);
# 162 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
return cudaCreateChannelDesc(e, 0, 0, 0, cudaChannelFormatKindUnsigned);
# 163 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
}
# 165 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
template<> inline cudaChannelFormatDesc cudaCreateChannelDesc< char1> ()
# 166 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
{
# 167 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
int e = (((int)sizeof(signed char)) * 8);
# 169 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
return cudaCreateChannelDesc(e, 0, 0, 0, cudaChannelFormatKindSigned);
# 170 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
}
# 172 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
template<> inline cudaChannelFormatDesc cudaCreateChannelDesc< uchar1> ()
# 173 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
{
# 174 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
int e = (((int)sizeof(unsigned char)) * 8);
# 176 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
return cudaCreateChannelDesc(e, 0, 0, 0, cudaChannelFormatKindUnsigned);
# 177 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
}
# 179 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
template<> inline cudaChannelFormatDesc cudaCreateChannelDesc< char2> ()
# 180 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
{
# 181 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
int e = (((int)sizeof(signed char)) * 8);
# 183 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
return cudaCreateChannelDesc(e, e, 0, 0, cudaChannelFormatKindSigned);
# 184 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
}
# 186 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
template<> inline cudaChannelFormatDesc cudaCreateChannelDesc< uchar2> ()
# 187 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
{
# 188 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
int e = (((int)sizeof(unsigned char)) * 8);
# 190 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
return cudaCreateChannelDesc(e, e, 0, 0, cudaChannelFormatKindUnsigned);
# 191 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
}
# 193 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
template<> inline cudaChannelFormatDesc cudaCreateChannelDesc< char4> ()
# 194 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
{
# 195 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
int e = (((int)sizeof(signed char)) * 8);
# 197 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
return cudaCreateChannelDesc(e, e, e, e, cudaChannelFormatKindSigned);
# 198 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
}
# 200 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
template<> inline cudaChannelFormatDesc cudaCreateChannelDesc< uchar4> ()
# 201 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
{
# 202 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
int e = (((int)sizeof(unsigned char)) * 8);
# 204 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
return cudaCreateChannelDesc(e, e, e, e, cudaChannelFormatKindUnsigned);
# 205 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
}
# 207 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
template<> inline cudaChannelFormatDesc cudaCreateChannelDesc< short> ()
# 208 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
{
# 209 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
int e = (((int)sizeof(short)) * 8);
# 211 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
return cudaCreateChannelDesc(e, 0, 0, 0, cudaChannelFormatKindSigned);
# 212 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
}
# 214 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
template<> inline cudaChannelFormatDesc cudaCreateChannelDesc< unsigned short> ()
# 215 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
{
# 216 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
int e = (((int)sizeof(unsigned short)) * 8);
# 218 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
return cudaCreateChannelDesc(e, 0, 0, 0, cudaChannelFormatKindUnsigned);
# 219 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
}
# 221 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
template<> inline cudaChannelFormatDesc cudaCreateChannelDesc< short1> ()
# 222 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
{
# 223 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
int e = (((int)sizeof(short)) * 8);
# 225 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
return cudaCreateChannelDesc(e, 0, 0, 0, cudaChannelFormatKindSigned);
# 226 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
}
# 228 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
template<> inline cudaChannelFormatDesc cudaCreateChannelDesc< ushort1> ()
# 229 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
{
# 230 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
int e = (((int)sizeof(unsigned short)) * 8);
# 232 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
return cudaCreateChannelDesc(e, 0, 0, 0, cudaChannelFormatKindUnsigned);
# 233 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
}
# 235 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
template<> inline cudaChannelFormatDesc cudaCreateChannelDesc< short2> ()
# 236 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
{
# 237 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
int e = (((int)sizeof(short)) * 8);
# 239 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
return cudaCreateChannelDesc(e, e, 0, 0, cudaChannelFormatKindSigned);
# 240 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
}
# 242 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
template<> inline cudaChannelFormatDesc cudaCreateChannelDesc< ushort2> ()
# 243 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
{
# 244 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
int e = (((int)sizeof(unsigned short)) * 8);
# 246 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
return cudaCreateChannelDesc(e, e, 0, 0, cudaChannelFormatKindUnsigned);
# 247 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
}
# 249 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
template<> inline cudaChannelFormatDesc cudaCreateChannelDesc< short4> ()
# 250 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
{
# 251 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
int e = (((int)sizeof(short)) * 8);
# 253 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
return cudaCreateChannelDesc(e, e, e, e, cudaChannelFormatKindSigned);
# 254 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
}
# 256 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
template<> inline cudaChannelFormatDesc cudaCreateChannelDesc< ushort4> ()
# 257 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
{
# 258 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
int e = (((int)sizeof(unsigned short)) * 8);
# 260 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
return cudaCreateChannelDesc(e, e, e, e, cudaChannelFormatKindUnsigned);
# 261 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
}
# 263 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
template<> inline cudaChannelFormatDesc cudaCreateChannelDesc< int> ()
# 264 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
{
# 265 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
int e = (((int)sizeof(int)) * 8);
# 267 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
return cudaCreateChannelDesc(e, 0, 0, 0, cudaChannelFormatKindSigned);
# 268 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
}
# 270 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
template<> inline cudaChannelFormatDesc cudaCreateChannelDesc< unsigned> ()
# 271 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
{
# 272 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
int e = (((int)sizeof(unsigned)) * 8);
# 274 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
return cudaCreateChannelDesc(e, 0, 0, 0, cudaChannelFormatKindUnsigned);
# 275 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
}
# 277 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
template<> inline cudaChannelFormatDesc cudaCreateChannelDesc< int1> ()
# 278 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
{
# 279 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
int e = (((int)sizeof(int)) * 8);
# 281 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
return cudaCreateChannelDesc(e, 0, 0, 0, cudaChannelFormatKindSigned);
# 282 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
}
# 284 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
template<> inline cudaChannelFormatDesc cudaCreateChannelDesc< uint1> ()
# 285 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
{
# 286 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
int e = (((int)sizeof(unsigned)) * 8);
# 288 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
return cudaCreateChannelDesc(e, 0, 0, 0, cudaChannelFormatKindUnsigned);
# 289 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
}
# 291 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
template<> inline cudaChannelFormatDesc cudaCreateChannelDesc< int2> ()
# 292 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
{
# 293 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
int e = (((int)sizeof(int)) * 8);
# 295 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
return cudaCreateChannelDesc(e, e, 0, 0, cudaChannelFormatKindSigned);
# 296 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
}
# 298 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
template<> inline cudaChannelFormatDesc cudaCreateChannelDesc< uint2> ()
# 299 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
{
# 300 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
int e = (((int)sizeof(unsigned)) * 8);
# 302 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
return cudaCreateChannelDesc(e, e, 0, 0, cudaChannelFormatKindUnsigned);
# 303 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
}
# 305 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
template<> inline cudaChannelFormatDesc cudaCreateChannelDesc< int4> ()
# 306 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
{
# 307 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
int e = (((int)sizeof(int)) * 8);
# 309 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
return cudaCreateChannelDesc(e, e, e, e, cudaChannelFormatKindSigned);
# 310 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
}
# 312 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
template<> inline cudaChannelFormatDesc cudaCreateChannelDesc< uint4> ()
# 313 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
{
# 314 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
int e = (((int)sizeof(unsigned)) * 8);
# 316 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
return cudaCreateChannelDesc(e, e, e, e, cudaChannelFormatKindUnsigned);
# 317 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
}
# 379 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
template<> inline cudaChannelFormatDesc cudaCreateChannelDesc< float> ()
# 380 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
{
# 381 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
int e = (((int)sizeof(float)) * 8);
# 383 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
return cudaCreateChannelDesc(e, 0, 0, 0, cudaChannelFormatKindFloat);
# 384 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
}
# 386 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
template<> inline cudaChannelFormatDesc cudaCreateChannelDesc< float1> ()
# 387 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
{
# 388 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
int e = (((int)sizeof(float)) * 8);
# 390 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
return cudaCreateChannelDesc(e, 0, 0, 0, cudaChannelFormatKindFloat);
# 391 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
}
# 393 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
template<> inline cudaChannelFormatDesc cudaCreateChannelDesc< float2> ()
# 394 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
{
# 395 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
int e = (((int)sizeof(float)) * 8);
# 397 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
return cudaCreateChannelDesc(e, e, 0, 0, cudaChannelFormatKindFloat);
# 398 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
}
# 400 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
template<> inline cudaChannelFormatDesc cudaCreateChannelDesc< float4> ()
# 401 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
{
# 402 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
int e = (((int)sizeof(float)) * 8);
# 404 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
return cudaCreateChannelDesc(e, e, e, e, cudaChannelFormatKindFloat);
# 405 "/home/hangzhang/local/cuda/4.0/bin/../include/channel_descriptor.h"
}
# 79 "/home/hangzhang/local/cuda/4.0/bin/../include/driver_functions.h"
static inline cudaPitchedPtr make_cudaPitchedPtr(void *d, size_t p, size_t xsz, size_t ysz)
# 80 "/home/hangzhang/local/cuda/4.0/bin/../include/driver_functions.h"
{
# 81 "/home/hangzhang/local/cuda/4.0/bin/../include/driver_functions.h"
cudaPitchedPtr s;
# 83 "/home/hangzhang/local/cuda/4.0/bin/../include/driver_functions.h"
(s.ptr) = d;
# 84 "/home/hangzhang/local/cuda/4.0/bin/../include/driver_functions.h"
(s.pitch) = p;
# 85 "/home/hangzhang/local/cuda/4.0/bin/../include/driver_functions.h"
(s.xsize) = xsz;
# 86 "/home/hangzhang/local/cuda/4.0/bin/../include/driver_functions.h"
(s.ysize) = ysz;
# 88 "/home/hangzhang/local/cuda/4.0/bin/../include/driver_functions.h"
return s;
# 89 "/home/hangzhang/local/cuda/4.0/bin/../include/driver_functions.h"
}
# 106 "/home/hangzhang/local/cuda/4.0/bin/../include/driver_functions.h"
static inline cudaPos make_cudaPos(size_t x, size_t y, size_t z)
# 107 "/home/hangzhang/local/cuda/4.0/bin/../include/driver_functions.h"
{
# 108 "/home/hangzhang/local/cuda/4.0/bin/../include/driver_functions.h"
cudaPos p;
# 110 "/home/hangzhang/local/cuda/4.0/bin/../include/driver_functions.h"
(p.x) = x;
# 111 "/home/hangzhang/local/cuda/4.0/bin/../include/driver_functions.h"
(p.y) = y;
# 112 "/home/hangzhang/local/cuda/4.0/bin/../include/driver_functions.h"
(p.z) = z;
# 114 "/home/hangzhang/local/cuda/4.0/bin/../include/driver_functions.h"
return p;
# 115 "/home/hangzhang/local/cuda/4.0/bin/../include/driver_functions.h"
}
# 132 "/home/hangzhang/local/cuda/4.0/bin/../include/driver_functions.h"
static inline cudaExtent make_cudaExtent(size_t w, size_t h, size_t d)
# 133 "/home/hangzhang/local/cuda/4.0/bin/../include/driver_functions.h"
{
# 134 "/home/hangzhang/local/cuda/4.0/bin/../include/driver_functions.h"
cudaExtent e;
# 136 "/home/hangzhang/local/cuda/4.0/bin/../include/driver_functions.h"
(e.width) = w;
# 137 "/home/hangzhang/local/cuda/4.0/bin/../include/driver_functions.h"
(e.height) = h;
# 138 "/home/hangzhang/local/cuda/4.0/bin/../include/driver_functions.h"
(e.depth) = d;
# 140 "/home/hangzhang/local/cuda/4.0/bin/../include/driver_functions.h"
return e;
# 141 "/home/hangzhang/local/cuda/4.0/bin/../include/driver_functions.h"
}
# 69 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
static inline char1 make_char1(signed char x)
# 70 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
{
# 71 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
char1 t; (t.x) = x; return t;
# 72 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
}
# 74 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
static inline uchar1 make_uchar1(unsigned char x)
# 75 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
{
# 76 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
uchar1 t; (t.x) = x; return t;
# 77 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
}
# 79 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
static inline char2 make_char2(signed char x, signed char y)
# 80 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
{
# 81 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
char2 t; (t.x) = x; (t.y) = y; return t;
# 82 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
}
# 84 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
static inline uchar2 make_uchar2(unsigned char x, unsigned char y)
# 85 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
{
# 86 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
uchar2 t; (t.x) = x; (t.y) = y; return t;
# 87 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
}
# 89 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
static inline char3 make_char3(signed char x, signed char y, signed char z)
# 90 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
{
# 91 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
char3 t; (t.x) = x; (t.y) = y; (t.z) = z; return t;
# 92 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
}
# 94 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
static inline uchar3 make_uchar3(unsigned char x, unsigned char y, unsigned char z)
# 95 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
{
# 96 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
uchar3 t; (t.x) = x; (t.y) = y; (t.z) = z; return t;
# 97 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
}
# 99 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
static inline char4 make_char4(signed char x, signed char y, signed char z, signed char w)
# 100 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
{
# 101 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
char4 t; (t.x) = x; (t.y) = y; (t.z) = z; (t.w) = w; return t;
# 102 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
}
# 104 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
static inline uchar4 make_uchar4(unsigned char x, unsigned char y, unsigned char z, unsigned char w)
# 105 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
{
# 106 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
uchar4 t; (t.x) = x; (t.y) = y; (t.z) = z; (t.w) = w; return t;
# 107 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
}
# 109 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
static inline short1 make_short1(short x)
# 110 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
{
# 111 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
short1 t; (t.x) = x; return t;
# 112 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
}
# 114 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
static inline ushort1 make_ushort1(unsigned short x)
# 115 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
{
# 116 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
ushort1 t; (t.x) = x; return t;
# 117 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
}
# 119 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
static inline short2 make_short2(short x, short y)
# 120 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
{
# 121 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
short2 t; (t.x) = x; (t.y) = y; return t;
# 122 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
}
# 124 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
static inline ushort2 make_ushort2(unsigned short x, unsigned short y)
# 125 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
{
# 126 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
ushort2 t; (t.x) = x; (t.y) = y; return t;
# 127 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
}
# 129 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
static inline short3 make_short3(short x, short y, short z)
# 130 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
{
# 131 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
short3 t; (t.x) = x; (t.y) = y; (t.z) = z; return t;
# 132 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
}
# 134 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
static inline ushort3 make_ushort3(unsigned short x, unsigned short y, unsigned short z)
# 135 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
{
# 136 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
ushort3 t; (t.x) = x; (t.y) = y; (t.z) = z; return t;
# 137 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
}
# 139 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
static inline short4 make_short4(short x, short y, short z, short w)
# 140 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
{
# 141 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
short4 t; (t.x) = x; (t.y) = y; (t.z) = z; (t.w) = w; return t;
# 142 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
}
# 144 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
static inline ushort4 make_ushort4(unsigned short x, unsigned short y, unsigned short z, unsigned short w)
# 145 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
{
# 146 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
ushort4 t; (t.x) = x; (t.y) = y; (t.z) = z; (t.w) = w; return t;
# 147 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
}
# 149 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
static inline int1 make_int1(int x)
# 150 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
{
# 151 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
int1 t; (t.x) = x; return t;
# 152 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
}
# 154 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
static inline uint1 make_uint1(unsigned x)
# 155 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
{
# 156 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
uint1 t; (t.x) = x; return t;
# 157 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
}
# 159 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
static inline int2 make_int2(int x, int y)
# 160 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
{
# 161 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
int2 t; (t.x) = x; (t.y) = y; return t;
# 162 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
}
# 164 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
static inline uint2 make_uint2(unsigned x, unsigned y)
# 165 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
{
# 166 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
uint2 t; (t.x) = x; (t.y) = y; return t;
# 167 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
}
# 169 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
static inline int3 make_int3(int x, int y, int z)
# 170 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
{
# 171 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
int3 t; (t.x) = x; (t.y) = y; (t.z) = z; return t;
# 172 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
}
# 174 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
static inline uint3 make_uint3(unsigned x, unsigned y, unsigned z)
# 175 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
{
# 176 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
uint3 t; (t.x) = x; (t.y) = y; (t.z) = z; return t;
# 177 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
}
# 179 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
static inline int4 make_int4(int x, int y, int z, int w)
# 180 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
{
# 181 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
int4 t; (t.x) = x; (t.y) = y; (t.z) = z; (t.w) = w; return t;
# 182 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
}
# 184 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
static inline uint4 make_uint4(unsigned x, unsigned y, unsigned z, unsigned w)
# 185 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
{
# 186 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
uint4 t; (t.x) = x; (t.y) = y; (t.z) = z; (t.w) = w; return t;
# 187 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
}
# 189 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
static inline long1 make_long1(long x)
# 190 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
{
# 191 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
long1 t; (t.x) = x; return t;
# 192 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
}
# 194 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
static inline ulong1 make_ulong1(unsigned long x)
# 195 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
{
# 196 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
ulong1 t; (t.x) = x; return t;
# 197 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
}
# 199 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
static inline long2 make_long2(long x, long y)
# 200 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
{
# 201 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
long2 t; (t.x) = x; (t.y) = y; return t;
# 202 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
}
# 204 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
static inline ulong2 make_ulong2(unsigned long x, unsigned long y)
# 205 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
{
# 206 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
ulong2 t; (t.x) = x; (t.y) = y; return t;
# 207 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
}
# 209 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
static inline long3 make_long3(long x, long y, long z)
# 210 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
{
# 211 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
long3 t; (t.x) = x; (t.y) = y; (t.z) = z; return t;
# 212 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
}
# 214 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
static inline ulong3 make_ulong3(unsigned long x, unsigned long y, unsigned long z)
# 215 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
{
# 216 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
ulong3 t; (t.x) = x; (t.y) = y; (t.z) = z; return t;
# 217 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
}
# 219 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
static inline long4 make_long4(long x, long y, long z, long w)
# 220 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
{
# 221 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
long4 t; (t.x) = x; (t.y) = y; (t.z) = z; (t.w) = w; return t;
# 222 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
}
# 224 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
static inline ulong4 make_ulong4(unsigned long x, unsigned long y, unsigned long z, unsigned long w)
# 225 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
{
# 226 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
ulong4 t; (t.x) = x; (t.y) = y; (t.z) = z; (t.w) = w; return t;
# 227 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
}
# 229 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
static inline float1 make_float1(float x)
# 230 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
{
# 231 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
float1 t; (t.x) = x; return t;
# 232 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
}
# 234 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
static inline float2 make_float2(float x, float y)
# 235 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
{
# 236 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
float2 t; (t.x) = x; (t.y) = y; return t;
# 237 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
}
# 239 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
static inline float3 make_float3(float x, float y, float z)
# 240 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
{
# 241 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
float3 t; (t.x) = x; (t.y) = y; (t.z) = z; return t;
# 242 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
}
# 244 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
static inline float4 make_float4(float x, float y, float z, float w)
# 245 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
{
# 246 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
float4 t; (t.x) = x; (t.y) = y; (t.z) = z; (t.w) = w; return t;
# 247 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
}
# 249 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
static inline longlong1 make_longlong1(long long x)
# 250 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
{
# 251 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
longlong1 t; (t.x) = x; return t;
# 252 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
}
# 254 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
static inline ulonglong1 make_ulonglong1(unsigned long long x)
# 255 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
{
# 256 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
ulonglong1 t; (t.x) = x; return t;
# 257 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
}
# 259 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
static inline longlong2 make_longlong2(long long x, long long y)
# 260 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
{
# 261 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
longlong2 t; (t.x) = x; (t.y) = y; return t;
# 262 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
}
# 264 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
static inline ulonglong2 make_ulonglong2(unsigned long long x, unsigned long long y)
# 265 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
{
# 266 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
ulonglong2 t; (t.x) = x; (t.y) = y; return t;
# 267 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
}
# 269 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
static inline longlong3 make_longlong3(long long x, long long y, long long z)
# 270 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
{
# 271 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
longlong3 t; (t.x) = x; (t.y) = y; (t.z) = z; return t;
# 272 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
}
# 274 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
static inline ulonglong3 make_ulonglong3(unsigned long long x, unsigned long long y, unsigned long long z)
# 275 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
{
# 276 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
ulonglong3 t; (t.x) = x; (t.y) = y; (t.z) = z; return t;
# 277 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
}
# 279 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
static inline longlong4 make_longlong4(long long x, long long y, long long z, long long w)
# 280 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
{
# 281 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
longlong4 t; (t.x) = x; (t.y) = y; (t.z) = z; (t.w) = w; return t;
# 282 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
}
# 284 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
static inline ulonglong4 make_ulonglong4(unsigned long long x, unsigned long long y, unsigned long long z, unsigned long long w)
# 285 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
{
# 286 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
ulonglong4 t; (t.x) = x; (t.y) = y; (t.z) = z; (t.w) = w; return t;
# 287 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
}
# 289 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
static inline double1 make_double1(double x)
# 290 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
{
# 291 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
double1 t; (t.x) = x; return t;
# 292 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
}
# 294 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
static inline double2 make_double2(double x, double y)
# 295 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
{
# 296 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
double2 t; (t.x) = x; (t.y) = y; return t;
# 297 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
}
# 299 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
static inline double3 make_double3(double x, double y, double z)
# 300 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
{
# 301 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
double3 t; (t.x) = x; (t.y) = y; (t.z) = z; return t;
# 302 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
}
# 304 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
static inline double4 make_double4(double x, double y, double z, double w)
# 305 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
{
# 306 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
double4 t; (t.x) = x; (t.y) = y; (t.z) = z; (t.w) = w; return t;
# 307 "/home/hangzhang/local/cuda/4.0/bin/../include/vector_functions.h"
}
# 44 "/usr/include/string.h" 3
extern "C" void *memcpy(void *__restrict__ , const void *__restrict__ , size_t ) throw()
# 46 "/usr/include/string.h" 3
 __attribute((__nonnull__(1, 2)));
# 49 "/usr/include/string.h" 3
extern "C" void *memmove(void * , const void * , size_t ) throw()
# 50 "/usr/include/string.h" 3
 __attribute((__nonnull__(1, 2)));
# 57 "/usr/include/string.h" 3
extern "C" void *memccpy(void *__restrict__ , const void *__restrict__ , int , size_t ) throw()
# 59 "/usr/include/string.h" 3
 __attribute((__nonnull__(1, 2)));
# 65 "/usr/include/string.h" 3
extern "C" void *memset(void * , int , size_t ) throw() __attribute((__nonnull__(1)));
# 68 "/usr/include/string.h" 3
extern "C" int memcmp(const void * , const void * , size_t ) throw()
# 69 "/usr/include/string.h" 3
 __attribute((__pure__)) __attribute((__nonnull__(1, 2)));
# 75 "/usr/include/string.h" 3
extern void *memchr(void * , int , size_t ) throw() __asm__("memchr")
# 76 "/usr/include/string.h" 3
 __attribute((__pure__)) __attribute((__nonnull__(1)));
# 77 "/usr/include/string.h" 3
extern const void *memchr(const void * , int , size_t ) throw() __asm__("memchr")
# 78 "/usr/include/string.h" 3
 __attribute((__pure__)) __attribute((__nonnull__(1)));
# 104 "/usr/include/string.h" 3
void *rawmemchr(void * , int ) throw() __asm__("rawmemchr")
# 105 "/usr/include/string.h" 3
 __attribute((__pure__)) __attribute((__nonnull__(1)));
# 106 "/usr/include/string.h" 3
const void *rawmemchr(const void * , int ) throw() __asm__("rawmemchr")
# 107 "/usr/include/string.h" 3
 __attribute((__pure__)) __attribute((__nonnull__(1)));
# 115 "/usr/include/string.h" 3
void *memrchr(void * , int , size_t ) throw() __asm__("memrchr")
# 116 "/usr/include/string.h" 3
 __attribute((__pure__)) __attribute((__nonnull__(1)));
# 117 "/usr/include/string.h" 3
const void *memrchr(const void * , int , size_t ) throw() __asm__("memrchr")
# 118 "/usr/include/string.h" 3
 __attribute((__pure__)) __attribute((__nonnull__(1)));
# 128 "/usr/include/string.h" 3
extern "C" char *strcpy(char *__restrict__ , const char *__restrict__ ) throw()
# 129 "/usr/include/string.h" 3
 __attribute((__nonnull__(1, 2)));
# 131 "/usr/include/string.h" 3
extern "C" char *strncpy(char *__restrict__ , const char *__restrict__ , size_t ) throw()
# 133 "/usr/include/string.h" 3
 __attribute((__nonnull__(1, 2)));
# 136 "/usr/include/string.h" 3
extern "C" char *strcat(char *__restrict__ , const char *__restrict__ ) throw()
# 137 "/usr/include/string.h" 3
 __attribute((__nonnull__(1, 2)));
# 139 "/usr/include/string.h" 3
extern "C" char *strncat(char *__restrict__ , const char *__restrict__ , size_t ) throw()
# 140 "/usr/include/string.h" 3
 __attribute((__nonnull__(1, 2)));
# 143 "/usr/include/string.h" 3
extern "C" int strcmp(const char * , const char * ) throw()
# 144 "/usr/include/string.h" 3
 __attribute((__pure__)) __attribute((__nonnull__(1, 2)));
# 146 "/usr/include/string.h" 3
extern "C" int strncmp(const char * , const char * , size_t ) throw()
# 147 "/usr/include/string.h" 3
 __attribute((__pure__)) __attribute((__nonnull__(1, 2)));
# 150 "/usr/include/string.h" 3
extern "C" int strcoll(const char * , const char * ) throw()
# 151 "/usr/include/string.h" 3
 __attribute((__pure__)) __attribute((__nonnull__(1, 2)));
# 153 "/usr/include/string.h" 3
extern "C" size_t strxfrm(char *__restrict__ , const char *__restrict__ , size_t ) throw()
# 155 "/usr/include/string.h" 3
 __attribute((__nonnull__(2)));
# 40 "/usr/include/xlocale.h" 3
extern "C" { typedef
# 28 "/usr/include/xlocale.h" 3
struct __locale_struct {
# 31 "/usr/include/xlocale.h" 3
struct __locale_data *__locales[13];
# 34 "/usr/include/xlocale.h" 3
const unsigned short *__ctype_b;
# 35 "/usr/include/xlocale.h" 3
const int *__ctype_tolower;
# 36 "/usr/include/xlocale.h" 3
const int *__ctype_toupper;
# 39 "/usr/include/xlocale.h" 3
const char *__names[13];
# 40 "/usr/include/xlocale.h" 3
} *__locale_t; }
# 43 "/usr/include/xlocale.h" 3
extern "C" { typedef __locale_t locale_t; }
# 165 "/usr/include/string.h" 3
extern "C" int strcoll_l(const char * , const char * , __locale_t ) throw()
# 166 "/usr/include/string.h" 3
 __attribute((__pure__)) __attribute((__nonnull__(1, 2, 3)));
# 168 "/usr/include/string.h" 3
extern "C" size_t strxfrm_l(char * , const char * , size_t , __locale_t ) throw()
# 169 "/usr/include/string.h" 3
 __attribute((__nonnull__(2, 4)));
# 175 "/usr/include/string.h" 3
extern "C" char *strdup(const char * ) throw()
# 176 "/usr/include/string.h" 3
 __attribute((__malloc__)) __attribute((__nonnull__(1)));
# 183 "/usr/include/string.h" 3
extern "C" char *strndup(const char * , size_t ) throw()
# 184 "/usr/include/string.h" 3
 __attribute((__malloc__)) __attribute((__nonnull__(1)));
# 215 "/usr/include/string.h" 3
extern char *strchr(char * , int ) throw() __asm__("strchr")
# 216 "/usr/include/string.h" 3
 __attribute((__pure__)) __attribute((__nonnull__(1)));
# 217 "/usr/include/string.h" 3
extern const char *strchr(const char * , int ) throw() __asm__("strchr")
# 218 "/usr/include/string.h" 3
 __attribute((__pure__)) __attribute((__nonnull__(1)));
# 242 "/usr/include/string.h" 3
extern char *strrchr(char * , int ) throw() __asm__("strrchr")
# 243 "/usr/include/string.h" 3
 __attribute((__pure__)) __attribute((__nonnull__(1)));
# 244 "/usr/include/string.h" 3
extern const char *strrchr(const char * , int ) throw() __asm__("strrchr")
# 245 "/usr/include/string.h" 3
 __attribute((__pure__)) __attribute((__nonnull__(1)));
# 271 "/usr/include/string.h" 3
char *strchrnul(char * , int ) throw() __asm__("strchrnul")
# 272 "/usr/include/string.h" 3
 __attribute((__pure__)) __attribute((__nonnull__(1)));
# 273 "/usr/include/string.h" 3
const char *strchrnul(const char * , int ) throw() __asm__("strchrnul")
# 274 "/usr/include/string.h" 3
 __attribute((__pure__)) __attribute((__nonnull__(1)));
# 284 "/usr/include/string.h" 3
extern "C" size_t strcspn(const char * , const char * ) throw()
# 285 "/usr/include/string.h" 3
 __attribute((__pure__)) __attribute((__nonnull__(1, 2)));
# 288 "/usr/include/string.h" 3
extern "C" size_t strspn(const char * , const char * ) throw()
# 289 "/usr/include/string.h" 3
 __attribute((__pure__)) __attribute((__nonnull__(1, 2)));
# 294 "/usr/include/string.h" 3
extern char *strpbrk(char * , const char * ) throw() __asm__("strpbrk")
# 295 "/usr/include/string.h" 3
 __attribute((__pure__)) __attribute((__nonnull__(1, 2)));
# 296 "/usr/include/string.h" 3
extern const char *strpbrk(const char * , const char * ) throw() __asm__("strpbrk")
# 297 "/usr/include/string.h" 3
 __attribute((__pure__)) __attribute((__nonnull__(1, 2)));
# 321 "/usr/include/string.h" 3
extern char *strstr(char * , const char * ) throw() __asm__("strstr")
# 322 "/usr/include/string.h" 3
 __attribute((__pure__)) __attribute((__nonnull__(1, 2)));
# 323 "/usr/include/string.h" 3
extern const char *strstr(const char * , const char * ) throw() __asm__("strstr")
# 325 "/usr/include/string.h" 3
 __attribute((__pure__)) __attribute((__nonnull__(1, 2)));
# 348 "/usr/include/string.h" 3
extern "C" char *strtok(char *__restrict__ , const char *__restrict__ ) throw()
# 349 "/usr/include/string.h" 3
 __attribute((__nonnull__(2)));
# 354 "/usr/include/string.h" 3
extern "C" char *__strtok_r(char *__restrict__ , const char *__restrict__ , char **__restrict__ ) throw()
# 357 "/usr/include/string.h" 3
 __attribute((__nonnull__(2, 3)));
# 359 "/usr/include/string.h" 3
extern "C" char *strtok_r(char *__restrict__ , const char *__restrict__ , char **__restrict__ ) throw()
# 361 "/usr/include/string.h" 3
 __attribute((__nonnull__(2, 3)));
# 367 "/usr/include/string.h" 3
char *strcasestr(char * , const char * ) throw() __asm__("strcasestr")
# 368 "/usr/include/string.h" 3
 __attribute((__pure__)) __attribute((__nonnull__(1, 2)));
# 369 "/usr/include/string.h" 3
const char *strcasestr(const char * , const char * ) throw() __asm__("strcasestr")
# 371 "/usr/include/string.h" 3
 __attribute((__pure__)) __attribute((__nonnull__(1, 2)));
# 382 "/usr/include/string.h" 3
extern "C" void *memmem(const void * , size_t , const void * , size_t ) throw()
# 384 "/usr/include/string.h" 3
 __attribute((__pure__)) __attribute((__nonnull__(1, 3)));
# 388 "/usr/include/string.h" 3
extern "C" void *__mempcpy(void *__restrict__ , const void *__restrict__ , size_t ) throw()
# 390 "/usr/include/string.h" 3
 __attribute((__nonnull__(1, 2)));
# 391 "/usr/include/string.h" 3
extern "C" void *mempcpy(void *__restrict__ , const void *__restrict__ , size_t ) throw()
# 393 "/usr/include/string.h" 3
 __attribute((__nonnull__(1, 2)));
# 399 "/usr/include/string.h" 3
extern "C" size_t strlen(const char * ) throw()
# 400 "/usr/include/string.h" 3
 __attribute((__pure__)) __attribute((__nonnull__(1)));
# 406 "/usr/include/string.h" 3
extern "C" size_t strnlen(const char * , size_t ) throw()
# 407 "/usr/include/string.h" 3
 __attribute((__pure__)) __attribute((__nonnull__(1)));
# 413 "/usr/include/string.h" 3
extern "C" char *strerror(int ) throw();
# 438 "/usr/include/string.h" 3
extern "C" char *strerror_r(int , char * , size_t ) throw()
# 439 "/usr/include/string.h" 3
 __attribute((__nonnull__(2)));
# 445 "/usr/include/string.h" 3
extern "C" char *strerror_l(int , __locale_t ) throw();
# 451 "/usr/include/string.h" 3
extern "C" void __bzero(void * , size_t ) throw() __attribute((__nonnull__(1)));
# 455 "/usr/include/string.h" 3
extern "C" void bcopy(const void * , void * , size_t ) throw()
# 456 "/usr/include/string.h" 3
 __attribute((__nonnull__(1, 2)));
# 459 "/usr/include/string.h" 3
extern "C" void bzero(void * , size_t ) throw() __attribute((__nonnull__(1)));
# 462 "/usr/include/string.h" 3
extern "C" int bcmp(const void * , const void * , size_t ) throw()
# 463 "/usr/include/string.h" 3
 __attribute((__pure__)) __attribute((__nonnull__(1, 2)));
# 469 "/usr/include/string.h" 3
extern char *index(char * , int ) throw() __asm__("index")
# 470 "/usr/include/string.h" 3
 __attribute((__pure__)) __attribute((__nonnull__(1)));
# 471 "/usr/include/string.h" 3
extern const char *index(const char * , int ) throw() __asm__("index")
# 472 "/usr/include/string.h" 3
 __attribute((__pure__)) __attribute((__nonnull__(1)));
# 497 "/usr/include/string.h" 3
extern char *rindex(char * , int ) throw() __asm__("rindex")
# 498 "/usr/include/string.h" 3
 __attribute((__pure__)) __attribute((__nonnull__(1)));
# 499 "/usr/include/string.h" 3
extern const char *rindex(const char * , int ) throw() __asm__("rindex")
# 500 "/usr/include/string.h" 3
 __attribute((__pure__)) __attribute((__nonnull__(1)));
# 523 "/usr/include/string.h" 3
extern "C" int ffs(int ) throw() __attribute((const));
# 528 "/usr/include/string.h" 3
extern "C" int ffsl(long ) throw() __attribute((const));
# 530 "/usr/include/string.h" 3
extern "C" int ffsll(long long ) throw()
# 531 "/usr/include/string.h" 3
 __attribute((const));
# 536 "/usr/include/string.h" 3
extern "C" int strcasecmp(const char * , const char * ) throw()
# 537 "/usr/include/string.h" 3
 __attribute((__pure__)) __attribute((__nonnull__(1, 2)));
# 540 "/usr/include/string.h" 3
extern "C" int strncasecmp(const char * , const char * , size_t ) throw()
# 541 "/usr/include/string.h" 3
 __attribute((__pure__)) __attribute((__nonnull__(1, 2)));
# 547 "/usr/include/string.h" 3
extern "C" int strcasecmp_l(const char * , const char * , __locale_t ) throw()
# 549 "/usr/include/string.h" 3
 __attribute((__pure__)) __attribute((__nonnull__(1, 2, 3)));
# 551 "/usr/include/string.h" 3
extern "C" int strncasecmp_l(const char * , const char * , size_t , __locale_t ) throw()
# 553 "/usr/include/string.h" 3
 __attribute((__pure__)) __attribute((__nonnull__(1, 2, 4)));
# 559 "/usr/include/string.h" 3
extern "C" char *strsep(char **__restrict__ , const char *__restrict__ ) throw()
# 561 "/usr/include/string.h" 3
 __attribute((__nonnull__(1, 2)));
# 566 "/usr/include/string.h" 3
extern "C" char *strsignal(int ) throw();
# 569 "/usr/include/string.h" 3
extern "C" char *__stpcpy(char *__restrict__ , const char *__restrict__ ) throw()
# 570 "/usr/include/string.h" 3
 __attribute((__nonnull__(1, 2)));
# 571 "/usr/include/string.h" 3
extern "C" char *stpcpy(char *__restrict__ , const char *__restrict__ ) throw()
# 572 "/usr/include/string.h" 3
 __attribute((__nonnull__(1, 2)));
# 576 "/usr/include/string.h" 3
extern "C" char *__stpncpy(char *__restrict__ , const char *__restrict__ , size_t ) throw()
# 578 "/usr/include/string.h" 3
 __attribute((__nonnull__(1, 2)));
# 579 "/usr/include/string.h" 3
extern "C" char *stpncpy(char *__restrict__ , const char *__restrict__ , size_t ) throw()
# 581 "/usr/include/string.h" 3
 __attribute((__nonnull__(1, 2)));
# 586 "/usr/include/string.h" 3
extern "C" int strverscmp(const char * , const char * ) throw()
# 587 "/usr/include/string.h" 3
 __attribute((__pure__)) __attribute((__nonnull__(1, 2)));
# 590 "/usr/include/string.h" 3
extern "C" char *strfry(char * ) throw() __attribute((__nonnull__(1)));
# 593 "/usr/include/string.h" 3
extern "C" void *memfrob(void * , size_t ) throw() __attribute((__nonnull__(1)));
# 601 "/usr/include/string.h" 3
char *basename(char * ) throw() __asm__("basename")
# 602 "/usr/include/string.h" 3
 __attribute((__nonnull__(1)));
# 603 "/usr/include/string.h" 3
const char *basename(const char * ) throw() __asm__("basename")
# 604 "/usr/include/string.h" 3
 __attribute((__nonnull__(1)));
# 31 "/usr/include/bits/types.h" 3
extern "C" { typedef unsigned char __u_char; }
# 32 "/usr/include/bits/types.h" 3
extern "C" { typedef unsigned short __u_short; }
# 33 "/usr/include/bits/types.h" 3
extern "C" { typedef unsigned __u_int; }
# 34 "/usr/include/bits/types.h" 3
extern "C" { typedef unsigned long __u_long; }
# 37 "/usr/include/bits/types.h" 3
extern "C" { typedef signed char __int8_t; }
# 38 "/usr/include/bits/types.h" 3
extern "C" { typedef unsigned char __uint8_t; }
# 39 "/usr/include/bits/types.h" 3
extern "C" { typedef signed short __int16_t; }
# 40 "/usr/include/bits/types.h" 3
extern "C" { typedef unsigned short __uint16_t; }
# 41 "/usr/include/bits/types.h" 3
extern "C" { typedef signed int __int32_t; }
# 42 "/usr/include/bits/types.h" 3
extern "C" { typedef unsigned __uint32_t; }
# 44 "/usr/include/bits/types.h" 3
extern "C" { typedef signed long __int64_t; }
# 45 "/usr/include/bits/types.h" 3
extern "C" { typedef unsigned long __uint64_t; }
# 53 "/usr/include/bits/types.h" 3
extern "C" { typedef long __quad_t; }
# 54 "/usr/include/bits/types.h" 3
extern "C" { typedef unsigned long __u_quad_t; }
# 134 "/usr/include/bits/types.h" 3
extern "C" { typedef unsigned long __dev_t; }
# 135 "/usr/include/bits/types.h" 3
extern "C" { typedef unsigned __uid_t; }
# 136 "/usr/include/bits/types.h" 3
extern "C" { typedef unsigned __gid_t; }
# 137 "/usr/include/bits/types.h" 3
extern "C" { typedef unsigned long __ino_t; }
# 138 "/usr/include/bits/types.h" 3
extern "C" { typedef unsigned long __ino64_t; }
# 139 "/usr/include/bits/types.h" 3
extern "C" { typedef unsigned __mode_t; }
# 140 "/usr/include/bits/types.h" 3
extern "C" { typedef unsigned long __nlink_t; }
# 141 "/usr/include/bits/types.h" 3
extern "C" { typedef long __off_t; }
# 142 "/usr/include/bits/types.h" 3
extern "C" { typedef long __off64_t; }
# 143 "/usr/include/bits/types.h" 3
extern "C" { typedef int __pid_t; }
# 144 "/usr/include/bits/types.h" 3
extern "C" { typedef struct { int __val[2]; } __fsid_t; }
# 145 "/usr/include/bits/types.h" 3
extern "C" { typedef long __clock_t; }
# 146 "/usr/include/bits/types.h" 3
extern "C" { typedef unsigned long __rlim_t; }
# 147 "/usr/include/bits/types.h" 3
extern "C" { typedef unsigned long __rlim64_t; }
# 148 "/usr/include/bits/types.h" 3
extern "C" { typedef unsigned __id_t; }
# 149 "/usr/include/bits/types.h" 3
extern "C" { typedef long __time_t; }
# 150 "/usr/include/bits/types.h" 3
extern "C" { typedef unsigned __useconds_t; }
# 151 "/usr/include/bits/types.h" 3
extern "C" { typedef long __suseconds_t; }
# 153 "/usr/include/bits/types.h" 3
extern "C" { typedef int __daddr_t; }
# 154 "/usr/include/bits/types.h" 3
extern "C" { typedef long __swblk_t; }
# 155 "/usr/include/bits/types.h" 3
extern "C" { typedef int __key_t; }
# 158 "/usr/include/bits/types.h" 3
extern "C" { typedef int __clockid_t; }
# 161 "/usr/include/bits/types.h" 3
extern "C" { typedef void *__timer_t; }
# 164 "/usr/include/bits/types.h" 3
extern "C" { typedef long __blksize_t; }
# 169 "/usr/include/bits/types.h" 3
extern "C" { typedef long __blkcnt_t; }
# 170 "/usr/include/bits/types.h" 3
extern "C" { typedef long __blkcnt64_t; }
# 173 "/usr/include/bits/types.h" 3
extern "C" { typedef unsigned long __fsblkcnt_t; }
# 174 "/usr/include/bits/types.h" 3
extern "C" { typedef unsigned long __fsblkcnt64_t; }
# 177 "/usr/include/bits/types.h" 3
extern "C" { typedef unsigned long __fsfilcnt_t; }
# 178 "/usr/include/bits/types.h" 3
extern "C" { typedef unsigned long __fsfilcnt64_t; }
# 180 "/usr/include/bits/types.h" 3
extern "C" { typedef long __ssize_t; }
# 184 "/usr/include/bits/types.h" 3
extern "C" { typedef __off64_t __loff_t; }
# 185 "/usr/include/bits/types.h" 3
extern "C" { typedef __quad_t *__qaddr_t; }
# 186 "/usr/include/bits/types.h" 3
extern "C" { typedef char *__caddr_t; }
# 189 "/usr/include/bits/types.h" 3
extern "C" { typedef long __intptr_t; }
# 192 "/usr/include/bits/types.h" 3
extern "C" { typedef unsigned __socklen_t; }
# 60 "/usr/include/time.h" 3
extern "C" { typedef __clock_t clock_t; }
# 76 "/usr/include/time.h" 3
extern "C" { typedef __time_t time_t; }
# 92 "/usr/include/time.h" 3
extern "C" { typedef __clockid_t clockid_t; }
# 104 "/usr/include/time.h" 3
extern "C" { typedef __timer_t timer_t; }
# 120 "/usr/include/time.h" 3
extern "C" { struct timespec {
# 122 "/usr/include/time.h" 3
__time_t tv_sec;
# 123 "/usr/include/time.h" 3
long tv_nsec;
# 124 "/usr/include/time.h" 3
}; }
# 133 "/usr/include/time.h" 3
extern "C" { struct tm {
# 135 "/usr/include/time.h" 3
int tm_sec;
# 136 "/usr/include/time.h" 3
int tm_min;
# 137 "/usr/include/time.h" 3
int tm_hour;
# 138 "/usr/include/time.h" 3
int tm_mday;
# 139 "/usr/include/time.h" 3
int tm_mon;
# 140 "/usr/include/time.h" 3
int tm_year;
# 141 "/usr/include/time.h" 3
int tm_wday;
# 142 "/usr/include/time.h" 3
int tm_yday;
# 143 "/usr/include/time.h" 3
int tm_isdst;
# 146 "/usr/include/time.h" 3
long tm_gmtoff;
# 147 "/usr/include/time.h" 3
const char *tm_zone;
# 152 "/usr/include/time.h" 3
}; }
# 161 "/usr/include/time.h" 3
extern "C" { struct itimerspec {
# 163 "/usr/include/time.h" 3
timespec it_interval;
# 164 "/usr/include/time.h" 3
timespec it_value;
# 165 "/usr/include/time.h" 3
}; }
# 168 "/usr/include/time.h" 3
struct sigevent;
# 174 "/usr/include/time.h" 3
extern "C" { typedef __pid_t pid_t; }
# 183 "/usr/include/time.h" 3
extern "C" clock_t clock() throw();
# 186 "/usr/include/time.h" 3
extern "C" time_t time(time_t * ) throw();
# 189 "/usr/include/time.h" 3
extern "C" double difftime(time_t , time_t ) throw()
# 190 "/usr/include/time.h" 3
 __attribute((const));
# 193 "/usr/include/time.h" 3
extern "C" time_t mktime(tm * ) throw();
# 199 "/usr/include/time.h" 3
extern "C" size_t strftime(char *__restrict__ , size_t , const char *__restrict__ , const tm *__restrict__ ) throw();
# 207 "/usr/include/time.h" 3
extern "C" char *strptime(const char *__restrict__ , const char *__restrict__ , tm * ) throw();
# 217 "/usr/include/time.h" 3
extern "C" size_t strftime_l(char *__restrict__ , size_t , const char *__restrict__ , const tm *__restrict__ , __locale_t ) throw();
# 224 "/usr/include/time.h" 3
extern "C" char *strptime_l(const char *__restrict__ , const char *__restrict__ , tm * , __locale_t ) throw();
# 233 "/usr/include/time.h" 3
extern "C" tm *gmtime(const time_t * ) throw();
# 237 "/usr/include/time.h" 3
extern "C" tm *localtime(const time_t * ) throw();
# 243 "/usr/include/time.h" 3
extern "C" tm *gmtime_r(const time_t *__restrict__ , tm *__restrict__ ) throw();
# 248 "/usr/include/time.h" 3
extern "C" tm *localtime_r(const time_t *__restrict__ , tm *__restrict__ ) throw();
# 255 "/usr/include/time.h" 3
extern "C" char *asctime(const tm * ) throw();
# 258 "/usr/include/time.h" 3
extern "C" char *ctime(const time_t * ) throw();
# 266 "/usr/include/time.h" 3
extern "C" char *asctime_r(const tm *__restrict__ , char *__restrict__ ) throw();
# 270 "/usr/include/time.h" 3
extern "C" char *ctime_r(const time_t *__restrict__ , char *__restrict__ ) throw();
# 276 "/usr/include/time.h" 3
extern "C" { extern char *__tzname[2]; }
# 277 "/usr/include/time.h" 3
extern "C" { extern int __daylight; }
# 278 "/usr/include/time.h" 3
extern "C" { extern long __timezone; }
# 283 "/usr/include/time.h" 3
extern "C" { extern char *tzname[2]; }
# 287 "/usr/include/time.h" 3
extern "C" void tzset() throw();
# 291 "/usr/include/time.h" 3
extern "C" { extern int daylight; }
# 292 "/usr/include/time.h" 3
extern "C" { extern long timezone; }
# 298 "/usr/include/time.h" 3
extern "C" int stime(const time_t * ) throw();
# 313 "/usr/include/time.h" 3
extern "C" time_t timegm(tm * ) throw();
# 316 "/usr/include/time.h" 3
extern "C" time_t timelocal(tm * ) throw();
# 319 "/usr/include/time.h" 3
extern "C" int dysize(int ) throw() __attribute((const));
# 328 "/usr/include/time.h" 3
extern "C" int nanosleep(const timespec * , timespec * );
# 333 "/usr/include/time.h" 3
extern "C" int clock_getres(clockid_t , timespec * ) throw();
# 336 "/usr/include/time.h" 3
extern "C" int clock_gettime(clockid_t , timespec * ) throw();
# 339 "/usr/include/time.h" 3
extern "C" int clock_settime(clockid_t , const timespec * ) throw();
# 347 "/usr/include/time.h" 3
extern "C" int clock_nanosleep(clockid_t , int , const timespec * , timespec * );
# 352 "/usr/include/time.h" 3
extern "C" int clock_getcpuclockid(pid_t , clockid_t * ) throw();
# 357 "/usr/include/time.h" 3
extern "C" int timer_create(clockid_t , sigevent *__restrict__ , timer_t *__restrict__ ) throw();
# 362 "/usr/include/time.h" 3
extern "C" int timer_delete(timer_t ) throw();
# 365 "/usr/include/time.h" 3
extern "C" int timer_settime(timer_t , int , const itimerspec *__restrict__ , itimerspec *__restrict__ ) throw();
# 370 "/usr/include/time.h" 3
extern "C" int timer_gettime(timer_t , itimerspec * ) throw();
# 374 "/usr/include/time.h" 3
extern "C" int timer_getoverrun(timer_t ) throw();
# 390 "/usr/include/time.h" 3
extern "C" { extern int getdate_err; }
# 399 "/usr/include/time.h" 3
extern "C" tm *getdate(const char * );
# 413 "/usr/include/time.h" 3
extern "C" int getdate_r(const char *__restrict__ , tm *__restrict__ );
# 71 "/home/hangzhang/local/cuda/4.0/bin/../include/common_functions.h"
extern "C" clock_t clock() throw();
# 73 "/home/hangzhang/local/cuda/4.0/bin/../include/common_functions.h"
extern "C" void *memset(void *, int, size_t) throw();
# 75 "/home/hangzhang/local/cuda/4.0/bin/../include/common_functions.h"
extern "C" void *memcpy(void *, const void *, size_t) throw();
# 31 "/usr/include/bits/mathdef.h" 3
extern "C" { typedef float float_t; }
# 32 "/usr/include/bits/mathdef.h" 3
extern "C" { typedef double double_t; }
# 55 "/usr/include/bits/mathcalls.h" 3
extern "C" double acos(double ) throw(); extern "C" double __acos(double ) throw();
# 57 "/usr/include/bits/mathcalls.h" 3
extern "C" double asin(double ) throw(); extern "C" double __asin(double ) throw();
# 59 "/usr/include/bits/mathcalls.h" 3
extern "C" double atan(double ) throw(); extern "C" double __atan(double ) throw();
# 61 "/usr/include/bits/mathcalls.h" 3
extern "C" double atan2(double , double ) throw(); extern "C" double __atan2(double , double ) throw();
# 64 "/usr/include/bits/mathcalls.h" 3
extern "C" double cos(double ) throw(); extern "C" double __cos(double ) throw();
# 66 "/usr/include/bits/mathcalls.h" 3
extern "C" double sin(double ) throw(); extern "C" double __sin(double ) throw();
# 68 "/usr/include/bits/mathcalls.h" 3
extern "C" double tan(double ) throw(); extern "C" double __tan(double ) throw();
# 73 "/usr/include/bits/mathcalls.h" 3
extern "C" double cosh(double ) throw(); extern "C" double __cosh(double ) throw();
# 75 "/usr/include/bits/mathcalls.h" 3
extern "C" double sinh(double ) throw(); extern "C" double __sinh(double ) throw();
# 77 "/usr/include/bits/mathcalls.h" 3
extern "C" double tanh(double ) throw(); extern "C" double __tanh(double ) throw();
# 82 "/usr/include/bits/mathcalls.h" 3
extern "C" void sincos(double , double * , double * ) throw(); extern "C" void __sincos(double , double * , double * ) throw();
# 89 "/usr/include/bits/mathcalls.h" 3
extern "C" double acosh(double ) throw(); extern "C" double __acosh(double ) throw();
# 91 "/usr/include/bits/mathcalls.h" 3
extern "C" double asinh(double ) throw(); extern "C" double __asinh(double ) throw();
# 93 "/usr/include/bits/mathcalls.h" 3
extern "C" double atanh(double ) throw(); extern "C" double __atanh(double ) throw();
# 101 "/usr/include/bits/mathcalls.h" 3
extern "C" double exp(double ) throw(); extern "C" double __exp(double ) throw();
# 104 "/usr/include/bits/mathcalls.h" 3
extern "C" double frexp(double , int * ) throw(); extern "C" double __frexp(double , int * ) throw();
# 107 "/usr/include/bits/mathcalls.h" 3
extern "C" double ldexp(double , int ) throw(); extern "C" double __ldexp(double , int ) throw();
# 110 "/usr/include/bits/mathcalls.h" 3
extern "C" double log(double ) throw(); extern "C" double __log(double ) throw();
# 113 "/usr/include/bits/mathcalls.h" 3
extern "C" double log10(double ) throw(); extern "C" double __log10(double ) throw();
# 116 "/usr/include/bits/mathcalls.h" 3
extern "C" double modf(double , double * ) throw(); extern "C" double __modf(double , double * ) throw();
# 121 "/usr/include/bits/mathcalls.h" 3
extern "C" double exp10(double ) throw(); extern "C" double __exp10(double ) throw();
# 123 "/usr/include/bits/mathcalls.h" 3
extern "C" double pow10(double ) throw(); extern "C" double __pow10(double ) throw();
# 129 "/usr/include/bits/mathcalls.h" 3
extern "C" double expm1(double ) throw(); extern "C" double __expm1(double ) throw();
# 132 "/usr/include/bits/mathcalls.h" 3
extern "C" double log1p(double ) throw(); extern "C" double __log1p(double ) throw();
# 135 "/usr/include/bits/mathcalls.h" 3
extern "C" double logb(double ) throw(); extern "C" double __logb(double ) throw();
# 142 "/usr/include/bits/mathcalls.h" 3
extern "C" double exp2(double ) throw(); extern "C" double __exp2(double ) throw();
# 145 "/usr/include/bits/mathcalls.h" 3
extern "C" double log2(double ) throw(); extern "C" double __log2(double ) throw();
# 154 "/usr/include/bits/mathcalls.h" 3
extern "C" double pow(double , double ) throw(); extern "C" double __pow(double , double ) throw();
# 157 "/usr/include/bits/mathcalls.h" 3
extern "C" double sqrt(double ) throw(); extern "C" double __sqrt(double ) throw();
# 163 "/usr/include/bits/mathcalls.h" 3
extern "C" double hypot(double , double ) throw(); extern "C" double __hypot(double , double ) throw();
# 170 "/usr/include/bits/mathcalls.h" 3
extern "C" double cbrt(double ) throw(); extern "C" double __cbrt(double ) throw();
# 179 "/usr/include/bits/mathcalls.h" 3
extern "C" double ceil(double ) throw() __attribute((const)); extern "C" double __ceil(double ) throw() __attribute((const));
# 182 "/usr/include/bits/mathcalls.h" 3
extern "C" double fabs(double ) throw() __attribute((const)); extern "C" double __fabs(double ) throw() __attribute((const));
# 185 "/usr/include/bits/mathcalls.h" 3
extern "C" double floor(double ) throw() __attribute((const)); extern "C" double __floor(double ) throw() __attribute((const));
# 188 "/usr/include/bits/mathcalls.h" 3
extern "C" double fmod(double , double ) throw(); extern "C" double __fmod(double , double ) throw();
# 193 "/usr/include/bits/mathcalls.h" 3
extern "C" int __isinf(double ) throw() __attribute((const));
# 196 "/usr/include/bits/mathcalls.h" 3
extern "C" int __finite(double ) throw() __attribute((const));
# 202 "/usr/include/bits/mathcalls.h" 3
extern "C" int isinf(double ) throw() __attribute((const));
# 205 "/usr/include/bits/mathcalls.h" 3
extern "C" int finite(double ) throw() __attribute((const));
# 208 "/usr/include/bits/mathcalls.h" 3
extern "C" double drem(double , double ) throw(); extern "C" double __drem(double , double ) throw();
# 212 "/usr/include/bits/mathcalls.h" 3
extern "C" double significand(double ) throw(); extern "C" double __significand(double ) throw();
# 218 "/usr/include/bits/mathcalls.h" 3
extern "C" double copysign(double , double ) throw() __attribute((const)); extern "C" double __copysign(double , double ) throw() __attribute((const));
# 225 "/usr/include/bits/mathcalls.h" 3
extern "C" double nan(const char * ) throw() __attribute((const)); extern "C" double __nan(const char * ) throw() __attribute((const));
# 231 "/usr/include/bits/mathcalls.h" 3
extern "C" int __isnan(double ) throw() __attribute((const));
# 235 "/usr/include/bits/mathcalls.h" 3
extern "C" int isnan(double ) throw() __attribute((const));
# 238 "/usr/include/bits/mathcalls.h" 3
extern "C" double j0(double) throw(); extern "C" double __j0(double) throw();
# 239 "/usr/include/bits/mathcalls.h" 3
extern "C" double j1(double) throw(); extern "C" double __j1(double) throw();
# 240 "/usr/include/bits/mathcalls.h" 3
extern "C" double jn(int, double) throw(); extern "C" double __jn(int, double) throw();
# 241 "/usr/include/bits/mathcalls.h" 3
extern "C" double y0(double) throw(); extern "C" double __y0(double) throw();
# 242 "/usr/include/bits/mathcalls.h" 3
extern "C" double y1(double) throw(); extern "C" double __y1(double) throw();
# 243 "/usr/include/bits/mathcalls.h" 3
extern "C" double yn(int, double) throw(); extern "C" double __yn(int, double) throw();
# 250 "/usr/include/bits/mathcalls.h" 3
extern "C" double erf(double) throw(); extern "C" double __erf(double) throw();
# 251 "/usr/include/bits/mathcalls.h" 3
extern "C" double erfc(double) throw(); extern "C" double __erfc(double) throw();
# 252 "/usr/include/bits/mathcalls.h" 3
extern "C" double lgamma(double) throw(); extern "C" double __lgamma(double) throw();
# 259 "/usr/include/bits/mathcalls.h" 3
extern "C" double tgamma(double) throw(); extern "C" double __tgamma(double) throw();
# 265 "/usr/include/bits/mathcalls.h" 3
extern "C" double gamma(double) throw(); extern "C" double __gamma(double) throw();
# 272 "/usr/include/bits/mathcalls.h" 3
extern "C" double lgamma_r(double, int * ) throw(); extern "C" double __lgamma_r(double, int * ) throw();
# 280 "/usr/include/bits/mathcalls.h" 3
extern "C" double rint(double ) throw(); extern "C" double __rint(double ) throw();
# 283 "/usr/include/bits/mathcalls.h" 3
extern "C" double nextafter(double , double ) throw() __attribute((const)); extern "C" double __nextafter(double , double ) throw() __attribute((const));
# 285 "/usr/include/bits/mathcalls.h" 3
extern "C" double nexttoward(double , long double ) throw() __attribute((const)); extern "C" double __nexttoward(double , long double ) throw() __attribute((const));
# 289 "/usr/include/bits/mathcalls.h" 3
extern "C" double remainder(double , double ) throw(); extern "C" double __remainder(double , double ) throw();
# 293 "/usr/include/bits/mathcalls.h" 3
extern "C" double scalbn(double , int ) throw(); extern "C" double __scalbn(double , int ) throw();
# 297 "/usr/include/bits/mathcalls.h" 3
extern "C" int ilogb(double ) throw(); extern "C" int __ilogb(double ) throw();
# 302 "/usr/include/bits/mathcalls.h" 3
extern "C" double scalbln(double , long ) throw(); extern "C" double __scalbln(double , long ) throw();
# 306 "/usr/include/bits/mathcalls.h" 3
extern "C" double nearbyint(double ) throw(); extern "C" double __nearbyint(double ) throw();
# 310 "/usr/include/bits/mathcalls.h" 3
extern "C" double round(double ) throw() __attribute((const)); extern "C" double __round(double ) throw() __attribute((const));
# 314 "/usr/include/bits/mathcalls.h" 3
extern "C" double trunc(double ) throw() __attribute((const)); extern "C" double __trunc(double ) throw() __attribute((const));
# 319 "/usr/include/bits/mathcalls.h" 3
extern "C" double remquo(double , double , int * ) throw(); extern "C" double __remquo(double , double , int * ) throw();
# 326 "/usr/include/bits/mathcalls.h" 3
extern "C" long lrint(double ) throw(); extern "C" long __lrint(double ) throw();
# 327 "/usr/include/bits/mathcalls.h" 3
extern "C" long long llrint(double ) throw(); extern "C" long long __llrint(double ) throw();
# 331 "/usr/include/bits/mathcalls.h" 3
extern "C" long lround(double ) throw(); extern "C" long __lround(double ) throw();
# 332 "/usr/include/bits/mathcalls.h" 3
extern "C" long long llround(double ) throw(); extern "C" long long __llround(double ) throw();
# 336 "/usr/include/bits/mathcalls.h" 3
extern "C" double fdim(double , double ) throw(); extern "C" double __fdim(double , double ) throw();
# 339 "/usr/include/bits/mathcalls.h" 3
extern "C" double fmax(double , double ) throw(); extern "C" double __fmax(double , double ) throw();
# 342 "/usr/include/bits/mathcalls.h" 3
extern "C" double fmin(double , double ) throw(); extern "C" double __fmin(double , double ) throw();
# 346 "/usr/include/bits/mathcalls.h" 3
extern "C" int __fpclassify(double ) throw()
# 347 "/usr/include/bits/mathcalls.h" 3
 __attribute((const));
# 350 "/usr/include/bits/mathcalls.h" 3
extern "C" int __signbit(double ) throw()
# 351 "/usr/include/bits/mathcalls.h" 3
 __attribute((const));
# 355 "/usr/include/bits/mathcalls.h" 3
extern "C" double fma(double , double , double ) throw(); extern "C" double __fma(double , double , double ) throw();
# 364 "/usr/include/bits/mathcalls.h" 3
extern "C" double scalb(double , double ) throw(); extern "C" double __scalb(double , double ) throw();
# 55 "/usr/include/bits/mathcalls.h" 3
extern "C" float acosf(float ) throw(); extern "C" float __acosf(float ) throw();
# 57 "/usr/include/bits/mathcalls.h" 3
extern "C" float asinf(float ) throw(); extern "C" float __asinf(float ) throw();
# 59 "/usr/include/bits/mathcalls.h" 3
extern "C" float atanf(float ) throw(); extern "C" float __atanf(float ) throw();
# 61 "/usr/include/bits/mathcalls.h" 3
extern "C" float atan2f(float , float ) throw(); extern "C" float __atan2f(float , float ) throw();
# 64 "/usr/include/bits/mathcalls.h" 3
extern "C" float cosf(float ) throw();
# 66 "/usr/include/bits/mathcalls.h" 3
extern "C" float sinf(float ) throw();
# 68 "/usr/include/bits/mathcalls.h" 3
extern "C" float tanf(float ) throw();
# 73 "/usr/include/bits/mathcalls.h" 3
extern "C" float coshf(float ) throw(); extern "C" float __coshf(float ) throw();
# 75 "/usr/include/bits/mathcalls.h" 3
extern "C" float sinhf(float ) throw(); extern "C" float __sinhf(float ) throw();
# 77 "/usr/include/bits/mathcalls.h" 3
extern "C" float tanhf(float ) throw(); extern "C" float __tanhf(float ) throw();
# 83 "/usr/include/bits/mathcalls.h" 3
extern "C" void sincosf(float , float * , float * ) throw();
# 89 "/usr/include/bits/mathcalls.h" 3
extern "C" float acoshf(float ) throw(); extern "C" float __acoshf(float ) throw();
# 91 "/usr/include/bits/mathcalls.h" 3
extern "C" float asinhf(float ) throw(); extern "C" float __asinhf(float ) throw();
# 93 "/usr/include/bits/mathcalls.h" 3
extern "C" float atanhf(float ) throw(); extern "C" float __atanhf(float ) throw();
# 101 "/usr/include/bits/mathcalls.h" 3
extern "C" float expf(float ) throw();
# 104 "/usr/include/bits/mathcalls.h" 3
extern "C" float frexpf(float , int * ) throw(); extern "C" float __frexpf(float , int * ) throw();
# 107 "/usr/include/bits/mathcalls.h" 3
extern "C" float ldexpf(float , int ) throw(); extern "C" float __ldexpf(float , int ) throw();
# 110 "/usr/include/bits/mathcalls.h" 3
extern "C" float logf(float ) throw();
# 113 "/usr/include/bits/mathcalls.h" 3
extern "C" float log10f(float ) throw();
# 116 "/usr/include/bits/mathcalls.h" 3
extern "C" float modff(float , float * ) throw(); extern "C" float __modff(float , float * ) throw();
# 121 "/usr/include/bits/mathcalls.h" 3
extern "C" float exp10f(float ) throw();
# 123 "/usr/include/bits/mathcalls.h" 3
extern "C" float pow10f(float ) throw(); extern "C" float __pow10f(float ) throw();
# 129 "/usr/include/bits/mathcalls.h" 3
extern "C" float expm1f(float ) throw(); extern "C" float __expm1f(float ) throw();
# 132 "/usr/include/bits/mathcalls.h" 3
extern "C" float log1pf(float ) throw(); extern "C" float __log1pf(float ) throw();
# 135 "/usr/include/bits/mathcalls.h" 3
extern "C" float logbf(float ) throw(); extern "C" float __logbf(float ) throw();
# 142 "/usr/include/bits/mathcalls.h" 3
extern "C" float exp2f(float ) throw(); extern "C" float __exp2f(float ) throw();
# 145 "/usr/include/bits/mathcalls.h" 3
extern "C" float log2f(float ) throw();
# 154 "/usr/include/bits/mathcalls.h" 3
extern "C" float powf(float , float ) throw();
# 157 "/usr/include/bits/mathcalls.h" 3
extern "C" float sqrtf(float ) throw(); extern "C" float __sqrtf(float ) throw();
# 163 "/usr/include/bits/mathcalls.h" 3
extern "C" float hypotf(float , float ) throw(); extern "C" float __hypotf(float , float ) throw();
# 170 "/usr/include/bits/mathcalls.h" 3
extern "C" float cbrtf(float ) throw(); extern "C" float __cbrtf(float ) throw();
# 179 "/usr/include/bits/mathcalls.h" 3
extern "C" float ceilf(float ) throw() __attribute((const)); extern "C" float __ceilf(float ) throw() __attribute((const));
# 182 "/usr/include/bits/mathcalls.h" 3
extern "C" float fabsf(float ) throw() __attribute((const)); extern "C" float __fabsf(float ) throw() __attribute((const));
# 185 "/usr/include/bits/mathcalls.h" 3
extern "C" float floorf(float ) throw() __attribute((const)); extern "C" float __floorf(float ) throw() __attribute((const));
# 188 "/usr/include/bits/mathcalls.h" 3
extern "C" float fmodf(float , float ) throw(); extern "C" float __fmodf(float , float ) throw();
# 193 "/usr/include/bits/mathcalls.h" 3
extern "C" int __isinff(float ) throw() __attribute((const));
# 196 "/usr/include/bits/mathcalls.h" 3
extern "C" int __finitef(float ) throw() __attribute((const));
# 202 "/usr/include/bits/mathcalls.h" 3
extern "C" int isinff(float ) throw() __attribute((const));
# 205 "/usr/include/bits/mathcalls.h" 3
extern "C" int finitef(float ) throw() __attribute((const));
# 208 "/usr/include/bits/mathcalls.h" 3
extern "C" float dremf(float , float ) throw(); extern "C" float __dremf(float , float ) throw();
# 212 "/usr/include/bits/mathcalls.h" 3
extern "C" float significandf(float ) throw(); extern "C" float __significandf(float ) throw();
# 218 "/usr/include/bits/mathcalls.h" 3
extern "C" float copysignf(float , float ) throw() __attribute((const)); extern "C" float __copysignf(float , float ) throw() __attribute((const));
# 225 "/usr/include/bits/mathcalls.h" 3
extern "C" float nanf(const char * ) throw() __attribute((const)); extern "C" float __nanf(const char * ) throw() __attribute((const));
# 231 "/usr/include/bits/mathcalls.h" 3
extern "C" int __isnanf(float ) throw() __attribute((const));
# 235 "/usr/include/bits/mathcalls.h" 3
extern "C" int isnanf(float ) throw() __attribute((const));
# 238 "/usr/include/bits/mathcalls.h" 3
extern "C" float j0f(float) throw(); extern "C" float __j0f(float) throw();
# 239 "/usr/include/bits/mathcalls.h" 3
extern "C" float j1f(float) throw(); extern "C" float __j1f(float) throw();
# 240 "/usr/include/bits/mathcalls.h" 3
extern "C" float jnf(int, float) throw(); extern "C" float __jnf(int, float) throw();
# 241 "/usr/include/bits/mathcalls.h" 3
extern "C" float y0f(float) throw(); extern "C" float __y0f(float) throw();
# 242 "/usr/include/bits/mathcalls.h" 3
extern "C" float y1f(float) throw(); extern "C" float __y1f(float) throw();
# 243 "/usr/include/bits/mathcalls.h" 3
extern "C" float ynf(int, float) throw(); extern "C" float __ynf(int, float) throw();
# 250 "/usr/include/bits/mathcalls.h" 3
extern "C" float erff(float) throw(); extern "C" float __erff(float) throw();
# 251 "/usr/include/bits/mathcalls.h" 3
extern "C" float erfcf(float) throw(); extern "C" float __erfcf(float) throw();
# 252 "/usr/include/bits/mathcalls.h" 3
extern "C" float lgammaf(float) throw(); extern "C" float __lgammaf(float) throw();
# 259 "/usr/include/bits/mathcalls.h" 3
extern "C" float tgammaf(float) throw(); extern "C" float __tgammaf(float) throw();
# 265 "/usr/include/bits/mathcalls.h" 3
extern "C" float gammaf(float) throw(); extern "C" float __gammaf(float) throw();
# 272 "/usr/include/bits/mathcalls.h" 3
extern "C" float lgammaf_r(float, int * ) throw(); extern "C" float __lgammaf_r(float, int * ) throw();
# 280 "/usr/include/bits/mathcalls.h" 3
extern "C" float rintf(float ) throw(); extern "C" float __rintf(float ) throw();
# 283 "/usr/include/bits/mathcalls.h" 3
extern "C" float nextafterf(float , float ) throw() __attribute((const)); extern "C" float __nextafterf(float , float ) throw() __attribute((const));
# 285 "/usr/include/bits/mathcalls.h" 3
extern "C" float nexttowardf(float , long double ) throw() __attribute((const)); extern "C" float __nexttowardf(float , long double ) throw() __attribute((const));
# 289 "/usr/include/bits/mathcalls.h" 3
extern "C" float remainderf(float , float ) throw(); extern "C" float __remainderf(float , float ) throw();
# 293 "/usr/include/bits/mathcalls.h" 3
extern "C" float scalbnf(float , int ) throw(); extern "C" float __scalbnf(float , int ) throw();
# 297 "/usr/include/bits/mathcalls.h" 3
extern "C" int ilogbf(float ) throw(); extern "C" int __ilogbf(float ) throw();
# 302 "/usr/include/bits/mathcalls.h" 3
extern "C" float scalblnf(float , long ) throw(); extern "C" float __scalblnf(float , long ) throw();
# 306 "/usr/include/bits/mathcalls.h" 3
extern "C" float nearbyintf(float ) throw(); extern "C" float __nearbyintf(float ) throw();
# 310 "/usr/include/bits/mathcalls.h" 3
extern "C" float roundf(float ) throw() __attribute((const)); extern "C" float __roundf(float ) throw() __attribute((const));
# 314 "/usr/include/bits/mathcalls.h" 3
extern "C" float truncf(float ) throw() __attribute((const)); extern "C" float __truncf(float ) throw() __attribute((const));
# 319 "/usr/include/bits/mathcalls.h" 3
extern "C" float remquof(float , float , int * ) throw(); extern "C" float __remquof(float , float , int * ) throw();
# 326 "/usr/include/bits/mathcalls.h" 3
extern "C" long lrintf(float ) throw(); extern "C" long __lrintf(float ) throw();
# 327 "/usr/include/bits/mathcalls.h" 3
extern "C" long long llrintf(float ) throw(); extern "C" long long __llrintf(float ) throw();
# 331 "/usr/include/bits/mathcalls.h" 3
extern "C" long lroundf(float ) throw(); extern "C" long __lroundf(float ) throw();
# 332 "/usr/include/bits/mathcalls.h" 3
extern "C" long long llroundf(float ) throw(); extern "C" long long __llroundf(float ) throw();
# 336 "/usr/include/bits/mathcalls.h" 3
extern "C" float fdimf(float , float ) throw(); extern "C" float __fdimf(float , float ) throw();
# 339 "/usr/include/bits/mathcalls.h" 3
extern "C" float fmaxf(float , float ) throw(); extern "C" float __fmaxf(float , float ) throw();
# 342 "/usr/include/bits/mathcalls.h" 3
extern "C" float fminf(float , float ) throw(); extern "C" float __fminf(float , float ) throw();
# 346 "/usr/include/bits/mathcalls.h" 3
extern "C" int __fpclassifyf(float ) throw()
# 347 "/usr/include/bits/mathcalls.h" 3
 __attribute((const));
# 350 "/usr/include/bits/mathcalls.h" 3
extern "C" int __signbitf(float ) throw()
# 351 "/usr/include/bits/mathcalls.h" 3
 __attribute((const));
# 355 "/usr/include/bits/mathcalls.h" 3
extern "C" float fmaf(float , float , float ) throw(); extern "C" float __fmaf(float , float , float ) throw();
# 364 "/usr/include/bits/mathcalls.h" 3
extern "C" float scalbf(float , float ) throw(); extern "C" float __scalbf(float , float ) throw();
# 55 "/usr/include/bits/mathcalls.h" 3
extern "C" long double acosl(long double ) throw(); extern "C" long double __acosl(long double ) throw();
# 57 "/usr/include/bits/mathcalls.h" 3
extern "C" long double asinl(long double ) throw(); extern "C" long double __asinl(long double ) throw();
# 59 "/usr/include/bits/mathcalls.h" 3
extern "C" long double atanl(long double ) throw(); extern "C" long double __atanl(long double ) throw();
# 61 "/usr/include/bits/mathcalls.h" 3
extern "C" long double atan2l(long double , long double ) throw(); extern "C" long double __atan2l(long double , long double ) throw();
# 64 "/usr/include/bits/mathcalls.h" 3
extern "C" long double cosl(long double ) throw(); extern "C" long double __cosl(long double ) throw();
# 66 "/usr/include/bits/mathcalls.h" 3
extern "C" long double sinl(long double ) throw(); extern "C" long double __sinl(long double ) throw();
# 68 "/usr/include/bits/mathcalls.h" 3
extern "C" long double tanl(long double ) throw(); extern "C" long double __tanl(long double ) throw();
# 73 "/usr/include/bits/mathcalls.h" 3
extern "C" long double coshl(long double ) throw(); extern "C" long double __coshl(long double ) throw();
# 75 "/usr/include/bits/mathcalls.h" 3
extern "C" long double sinhl(long double ) throw(); extern "C" long double __sinhl(long double ) throw();
# 77 "/usr/include/bits/mathcalls.h" 3
extern "C" long double tanhl(long double ) throw(); extern "C" long double __tanhl(long double ) throw();
# 83 "/usr/include/bits/mathcalls.h" 3
extern "C" void sincosl(long double , long double * , long double * ) throw();
# 83 "/usr/include/bits/mathcalls.h" 3
extern "C" void __sincosl(long double , long double * , long double * ) throw();
# 89 "/usr/include/bits/mathcalls.h" 3
extern "C" long double acoshl(long double ) throw(); extern "C" long double __acoshl(long double ) throw();
# 91 "/usr/include/bits/mathcalls.h" 3
extern "C" long double asinhl(long double ) throw(); extern "C" long double __asinhl(long double ) throw();
# 93 "/usr/include/bits/mathcalls.h" 3
extern "C" long double atanhl(long double ) throw(); extern "C" long double __atanhl(long double ) throw();
# 101 "/usr/include/bits/mathcalls.h" 3
extern "C" long double expl(long double ) throw(); extern "C" long double __expl(long double ) throw();
# 104 "/usr/include/bits/mathcalls.h" 3
extern "C" long double frexpl(long double , int * ) throw(); extern "C" long double __frexpl(long double , int * ) throw();
# 107 "/usr/include/bits/mathcalls.h" 3
extern "C" long double ldexpl(long double , int ) throw(); extern "C" long double __ldexpl(long double , int ) throw();
# 110 "/usr/include/bits/mathcalls.h" 3
extern "C" long double logl(long double ) throw(); extern "C" long double __logl(long double ) throw();
# 113 "/usr/include/bits/mathcalls.h" 3
extern "C" long double log10l(long double ) throw(); extern "C" long double __log10l(long double ) throw();
# 116 "/usr/include/bits/mathcalls.h" 3
extern "C" long double modfl(long double , long double * ) throw(); extern "C" long double __modfl(long double , long double * ) throw();
# 121 "/usr/include/bits/mathcalls.h" 3
extern "C" long double exp10l(long double ) throw(); extern "C" long double __exp10l(long double ) throw();
# 123 "/usr/include/bits/mathcalls.h" 3
extern "C" long double pow10l(long double ) throw(); extern "C" long double __pow10l(long double ) throw();
# 129 "/usr/include/bits/mathcalls.h" 3
extern "C" long double expm1l(long double ) throw(); extern "C" long double __expm1l(long double ) throw();
# 132 "/usr/include/bits/mathcalls.h" 3
extern "C" long double log1pl(long double ) throw(); extern "C" long double __log1pl(long double ) throw();
# 135 "/usr/include/bits/mathcalls.h" 3
extern "C" long double logbl(long double ) throw(); extern "C" long double __logbl(long double ) throw();
# 142 "/usr/include/bits/mathcalls.h" 3
extern "C" long double exp2l(long double ) throw(); extern "C" long double __exp2l(long double ) throw();
# 145 "/usr/include/bits/mathcalls.h" 3
extern "C" long double log2l(long double ) throw(); extern "C" long double __log2l(long double ) throw();
# 154 "/usr/include/bits/mathcalls.h" 3
extern "C" long double powl(long double , long double ) throw(); extern "C" long double __powl(long double , long double ) throw();
# 157 "/usr/include/bits/mathcalls.h" 3
extern "C" long double sqrtl(long double ) throw(); extern "C" long double __sqrtl(long double ) throw();
# 163 "/usr/include/bits/mathcalls.h" 3
extern "C" long double hypotl(long double , long double ) throw(); extern "C" long double __hypotl(long double , long double ) throw();
# 170 "/usr/include/bits/mathcalls.h" 3
extern "C" long double cbrtl(long double ) throw(); extern "C" long double __cbrtl(long double ) throw();
# 179 "/usr/include/bits/mathcalls.h" 3
extern "C" long double ceill(long double ) throw() __attribute((const)); extern "C" long double __ceill(long double ) throw() __attribute((const));
# 182 "/usr/include/bits/mathcalls.h" 3
extern "C" long double fabsl(long double ) throw() __attribute((const)); extern "C" long double __fabsl(long double ) throw() __attribute((const));
# 185 "/usr/include/bits/mathcalls.h" 3
extern "C" long double floorl(long double ) throw() __attribute((const)); extern "C" long double __floorl(long double ) throw() __attribute((const));
# 188 "/usr/include/bits/mathcalls.h" 3
extern "C" long double fmodl(long double , long double ) throw(); extern "C" long double __fmodl(long double , long double ) throw();
# 193 "/usr/include/bits/mathcalls.h" 3
extern "C" int __isinfl(long double ) throw() __attribute((const));
# 196 "/usr/include/bits/mathcalls.h" 3
extern "C" int __finitel(long double ) throw() __attribute((const));
# 202 "/usr/include/bits/mathcalls.h" 3
extern "C" int isinfl(long double ) throw() __attribute((const));
# 205 "/usr/include/bits/mathcalls.h" 3
extern "C" int finitel(long double ) throw() __attribute((const));
# 208 "/usr/include/bits/mathcalls.h" 3
extern "C" long double dreml(long double , long double ) throw(); extern "C" long double __dreml(long double , long double ) throw();
# 212 "/usr/include/bits/mathcalls.h" 3
extern "C" long double significandl(long double ) throw(); extern "C" long double __significandl(long double ) throw();
# 218 "/usr/include/bits/mathcalls.h" 3
extern "C" long double copysignl(long double , long double ) throw() __attribute((const)); extern "C" long double __copysignl(long double , long double ) throw() __attribute((const));
# 225 "/usr/include/bits/mathcalls.h" 3
extern "C" long double nanl(const char * ) throw() __attribute((const)); extern "C" long double __nanl(const char * ) throw() __attribute((const));
# 231 "/usr/include/bits/mathcalls.h" 3
extern "C" int __isnanl(long double ) throw() __attribute((const));
# 235 "/usr/include/bits/mathcalls.h" 3
extern "C" int isnanl(long double ) throw() __attribute((const));
# 238 "/usr/include/bits/mathcalls.h" 3
extern "C" long double j0l(long double) throw(); extern "C" long double __j0l(long double) throw();
# 239 "/usr/include/bits/mathcalls.h" 3
extern "C" long double j1l(long double) throw(); extern "C" long double __j1l(long double) throw();
# 240 "/usr/include/bits/mathcalls.h" 3
extern "C" long double jnl(int, long double) throw(); extern "C" long double __jnl(int, long double) throw();
# 241 "/usr/include/bits/mathcalls.h" 3
extern "C" long double y0l(long double) throw(); extern "C" long double __y0l(long double) throw();
# 242 "/usr/include/bits/mathcalls.h" 3
extern "C" long double y1l(long double) throw(); extern "C" long double __y1l(long double) throw();
# 243 "/usr/include/bits/mathcalls.h" 3
extern "C" long double ynl(int, long double) throw(); extern "C" long double __ynl(int, long double) throw();
# 250 "/usr/include/bits/mathcalls.h" 3
extern "C" long double erfl(long double) throw(); extern "C" long double __erfl(long double) throw();
# 251 "/usr/include/bits/mathcalls.h" 3
extern "C" long double erfcl(long double) throw(); extern "C" long double __erfcl(long double) throw();
# 252 "/usr/include/bits/mathcalls.h" 3
extern "C" long double lgammal(long double) throw(); extern "C" long double __lgammal(long double) throw();
# 259 "/usr/include/bits/mathcalls.h" 3
extern "C" long double tgammal(long double) throw(); extern "C" long double __tgammal(long double) throw();
# 265 "/usr/include/bits/mathcalls.h" 3
extern "C" long double gammal(long double) throw(); extern "C" long double __gammal(long double) throw();
# 272 "/usr/include/bits/mathcalls.h" 3
extern "C" long double lgammal_r(long double, int * ) throw(); extern "C" long double __lgammal_r(long double, int * ) throw();
# 280 "/usr/include/bits/mathcalls.h" 3
extern "C" long double rintl(long double ) throw(); extern "C" long double __rintl(long double ) throw();
# 283 "/usr/include/bits/mathcalls.h" 3
extern "C" long double nextafterl(long double , long double ) throw() __attribute((const)); extern "C" long double __nextafterl(long double , long double ) throw() __attribute((const));
# 285 "/usr/include/bits/mathcalls.h" 3
extern "C" long double nexttowardl(long double , long double ) throw() __attribute((const)); extern "C" long double __nexttowardl(long double , long double ) throw() __attribute((const));
# 289 "/usr/include/bits/mathcalls.h" 3
extern "C" long double remainderl(long double , long double ) throw(); extern "C" long double __remainderl(long double , long double ) throw();
# 293 "/usr/include/bits/mathcalls.h" 3
extern "C" long double scalbnl(long double , int ) throw(); extern "C" long double __scalbnl(long double , int ) throw();
# 297 "/usr/include/bits/mathcalls.h" 3
extern "C" int ilogbl(long double ) throw(); extern "C" int __ilogbl(long double ) throw();
# 302 "/usr/include/bits/mathcalls.h" 3
extern "C" long double scalblnl(long double , long ) throw(); extern "C" long double __scalblnl(long double , long ) throw();
# 306 "/usr/include/bits/mathcalls.h" 3
extern "C" long double nearbyintl(long double ) throw(); extern "C" long double __nearbyintl(long double ) throw();
# 310 "/usr/include/bits/mathcalls.h" 3
extern "C" long double roundl(long double ) throw() __attribute((const)); extern "C" long double __roundl(long double ) throw() __attribute((const));
# 314 "/usr/include/bits/mathcalls.h" 3
extern "C" long double truncl(long double ) throw() __attribute((const)); extern "C" long double __truncl(long double ) throw() __attribute((const));
# 319 "/usr/include/bits/mathcalls.h" 3
extern "C" long double remquol(long double , long double , int * ) throw(); extern "C" long double __remquol(long double , long double , int * ) throw();
# 326 "/usr/include/bits/mathcalls.h" 3
extern "C" long lrintl(long double ) throw(); extern "C" long __lrintl(long double ) throw();
# 327 "/usr/include/bits/mathcalls.h" 3
extern "C" long long llrintl(long double ) throw(); extern "C" long long __llrintl(long double ) throw();
# 331 "/usr/include/bits/mathcalls.h" 3
extern "C" long lroundl(long double ) throw(); extern "C" long __lroundl(long double ) throw();
# 332 "/usr/include/bits/mathcalls.h" 3
extern "C" long long llroundl(long double ) throw(); extern "C" long long __llroundl(long double ) throw();
# 336 "/usr/include/bits/mathcalls.h" 3
extern "C" long double fdiml(long double , long double ) throw(); extern "C" long double __fdiml(long double , long double ) throw();
# 339 "/usr/include/bits/mathcalls.h" 3
extern "C" long double fmaxl(long double , long double ) throw(); extern "C" long double __fmaxl(long double , long double ) throw();
# 342 "/usr/include/bits/mathcalls.h" 3
extern "C" long double fminl(long double , long double ) throw(); extern "C" long double __fminl(long double , long double ) throw();
# 346 "/usr/include/bits/mathcalls.h" 3
extern "C" int __fpclassifyl(long double ) throw()
# 347 "/usr/include/bits/mathcalls.h" 3
 __attribute((const));
# 350 "/usr/include/bits/mathcalls.h" 3
extern "C" int __signbitl(long double ) throw()
# 351 "/usr/include/bits/mathcalls.h" 3
 __attribute((const));
# 355 "/usr/include/bits/mathcalls.h" 3
extern "C" long double fmal(long double , long double , long double ) throw(); extern "C" long double __fmal(long double , long double , long double ) throw();
# 364 "/usr/include/bits/mathcalls.h" 3
extern "C" long double scalbl(long double , long double ) throw(); extern "C" long double __scalbl(long double , long double ) throw();
# 157 "/usr/include/math.h" 3
extern "C" { extern int signgam; }
# 199 "/usr/include/math.h" 3
enum {
# 200 "/usr/include/math.h" 3
FP_NAN,
# 202 "/usr/include/math.h" 3
FP_INFINITE,
# 204 "/usr/include/math.h" 3
FP_ZERO,
# 206 "/usr/include/math.h" 3
FP_SUBNORMAL,
# 208 "/usr/include/math.h" 3
FP_NORMAL
# 210 "/usr/include/math.h" 3
};
# 298 "/usr/include/math.h" 3
extern "C" { typedef
# 292 "/usr/include/math.h" 3
enum {
# 293 "/usr/include/math.h" 3
_IEEE_ = (-1),
# 294 "/usr/include/math.h" 3
_SVID_ = 0,
# 295 "/usr/include/math.h" 3
_XOPEN_,
# 296 "/usr/include/math.h" 3
_POSIX_,
# 297 "/usr/include/math.h" 3
_ISOC_
# 298 "/usr/include/math.h" 3
} _LIB_VERSION_TYPE; }
# 303 "/usr/include/math.h" 3
extern "C" { extern _LIB_VERSION_TYPE _LIB_VERSION; }
# 314 "/usr/include/math.h" 3
extern "C" { struct __exception {
# 319 "/usr/include/math.h" 3
int type;
# 320 "/usr/include/math.h" 3
char *name;
# 321 "/usr/include/math.h" 3
double arg1;
# 322 "/usr/include/math.h" 3
double arg2;
# 323 "/usr/include/math.h" 3
double retval;
# 324 "/usr/include/math.h" 3
}; }
# 327 "/usr/include/math.h" 3
extern "C" int matherr(__exception * ) throw();
# 67 "/usr/include/bits/waitstatus.h" 3
extern "C" { union wait {
# 69 "/usr/include/bits/waitstatus.h" 3
int w_status;
# 71 "/usr/include/bits/waitstatus.h" 3
struct {
# 73 "/usr/include/bits/waitstatus.h" 3
unsigned __w_termsig:7;
# 74 "/usr/include/bits/waitstatus.h" 3
unsigned __w_coredump:1;
# 75 "/usr/include/bits/waitstatus.h" 3
unsigned __w_retcode:8;
# 76 "/usr/include/bits/waitstatus.h" 3
unsigned:16;
# 84 "/usr/include/bits/waitstatus.h" 3
} __wait_terminated;
# 86 "/usr/include/bits/waitstatus.h" 3
struct {
# 88 "/usr/include/bits/waitstatus.h" 3
unsigned __w_stopval:8;
# 89 "/usr/include/bits/waitstatus.h" 3
unsigned __w_stopsig:8;
# 90 "/usr/include/bits/waitstatus.h" 3
unsigned:16;
# 97 "/usr/include/bits/waitstatus.h" 3
} __wait_stopped;
# 98 "/usr/include/bits/waitstatus.h" 3
}; }
# 102 "/usr/include/stdlib.h" 3
extern "C" { typedef
# 99 "/usr/include/stdlib.h" 3
struct {
# 100 "/usr/include/stdlib.h" 3
int quot;
# 101 "/usr/include/stdlib.h" 3
int rem;
# 102 "/usr/include/stdlib.h" 3
} div_t; }
# 110 "/usr/include/stdlib.h" 3
extern "C" { typedef
# 107 "/usr/include/stdlib.h" 3
struct {
# 108 "/usr/include/stdlib.h" 3
long quot;
# 109 "/usr/include/stdlib.h" 3
long rem;
# 110 "/usr/include/stdlib.h" 3
} ldiv_t; }
# 122 "/usr/include/stdlib.h" 3
extern "C" { typedef
# 119 "/usr/include/stdlib.h" 3
struct {
# 120 "/usr/include/stdlib.h" 3
long long quot;
# 121 "/usr/include/stdlib.h" 3
long long rem;
# 122 "/usr/include/stdlib.h" 3
} lldiv_t; }
# 140 "/usr/include/stdlib.h" 3
extern "C" size_t __ctype_get_mb_cur_max() throw();
# 145 "/usr/include/stdlib.h" 3
extern "C" double atof(const char * ) throw()
# 146 "/usr/include/stdlib.h" 3
 __attribute((__pure__)) __attribute((__nonnull__(1)));
# 148 "/usr/include/stdlib.h" 3
extern "C" int atoi(const char * ) throw()
# 149 "/usr/include/stdlib.h" 3
 __attribute((__pure__)) __attribute((__nonnull__(1)));
# 151 "/usr/include/stdlib.h" 3
extern "C" long atol(const char * ) throw()
# 152 "/usr/include/stdlib.h" 3
 __attribute((__pure__)) __attribute((__nonnull__(1)));
# 158 "/usr/include/stdlib.h" 3
extern "C" long long atoll(const char * ) throw()
# 159 "/usr/include/stdlib.h" 3
 __attribute((__pure__)) __attribute((__nonnull__(1)));
# 165 "/usr/include/stdlib.h" 3
extern "C" double strtod(const char *__restrict__ , char **__restrict__ ) throw()
# 167 "/usr/include/stdlib.h" 3
 __attribute((__nonnull__(1)));
# 173 "/usr/include/stdlib.h" 3
extern "C" float strtof(const char *__restrict__ , char **__restrict__ ) throw()
# 174 "/usr/include/stdlib.h" 3
 __attribute((__nonnull__(1)));
# 176 "/usr/include/stdlib.h" 3
extern "C" long double strtold(const char *__restrict__ , char **__restrict__ ) throw()
# 178 "/usr/include/stdlib.h" 3
 __attribute((__nonnull__(1)));
# 184 "/usr/include/stdlib.h" 3
extern "C" long strtol(const char *__restrict__ , char **__restrict__ , int ) throw()
# 186 "/usr/include/stdlib.h" 3
 __attribute((__nonnull__(1)));
# 188 "/usr/include/stdlib.h" 3
extern "C" unsigned long strtoul(const char *__restrict__ , char **__restrict__ , int ) throw()
# 190 "/usr/include/stdlib.h" 3
 __attribute((__nonnull__(1)));
# 196 "/usr/include/stdlib.h" 3
extern "C" long long strtoq(const char *__restrict__ , char **__restrict__ , int ) throw()
# 198 "/usr/include/stdlib.h" 3
 __attribute((__nonnull__(1)));
# 201 "/usr/include/stdlib.h" 3
extern "C" unsigned long long strtouq(const char *__restrict__ , char **__restrict__ , int ) throw()
# 203 "/usr/include/stdlib.h" 3
 __attribute((__nonnull__(1)));
# 210 "/usr/include/stdlib.h" 3
extern "C" long long strtoll(const char *__restrict__ , char **__restrict__ , int ) throw()
# 212 "/usr/include/stdlib.h" 3
 __attribute((__nonnull__(1)));
# 215 "/usr/include/stdlib.h" 3
extern "C" unsigned long long strtoull(const char *__restrict__ , char **__restrict__ , int ) throw()
# 217 "/usr/include/stdlib.h" 3
 __attribute((__nonnull__(1)));
# 240 "/usr/include/stdlib.h" 3
extern "C" long strtol_l(const char *__restrict__ , char **__restrict__ , int , __locale_t ) throw()
# 242 "/usr/include/stdlib.h" 3
 __attribute((__nonnull__(1, 4)));
# 244 "/usr/include/stdlib.h" 3
extern "C" unsigned long strtoul_l(const char *__restrict__ , char **__restrict__ , int , __locale_t ) throw()
# 247 "/usr/include/stdlib.h" 3
 __attribute((__nonnull__(1, 4)));
# 250 "/usr/include/stdlib.h" 3
extern "C" long long strtoll_l(const char *__restrict__ , char **__restrict__ , int , __locale_t ) throw()
# 253 "/usr/include/stdlib.h" 3
 __attribute((__nonnull__(1, 4)));
# 256 "/usr/include/stdlib.h" 3
extern "C" unsigned long long strtoull_l(const char *__restrict__ , char **__restrict__ , int , __locale_t ) throw()
# 259 "/usr/include/stdlib.h" 3
 __attribute((__nonnull__(1, 4)));
# 261 "/usr/include/stdlib.h" 3
extern "C" double strtod_l(const char *__restrict__ , char **__restrict__ , __locale_t ) throw()
# 263 "/usr/include/stdlib.h" 3
 __attribute((__nonnull__(1, 3)));
# 265 "/usr/include/stdlib.h" 3
extern "C" float strtof_l(const char *__restrict__ , char **__restrict__ , __locale_t ) throw()
# 267 "/usr/include/stdlib.h" 3
 __attribute((__nonnull__(1, 3)));
# 269 "/usr/include/stdlib.h" 3
extern "C" long double strtold_l(const char *__restrict__ , char **__restrict__ , __locale_t ) throw()
# 272 "/usr/include/stdlib.h" 3
 __attribute((__nonnull__(1, 3)));
# 311 "/usr/include/stdlib.h" 3
extern "C" char *l64a(long ) throw();
# 314 "/usr/include/stdlib.h" 3
extern "C" long a64l(const char * ) throw()
# 315 "/usr/include/stdlib.h" 3
 __attribute((__pure__)) __attribute((__nonnull__(1)));
# 34 "/usr/include/sys/types.h" 3
extern "C" { typedef __u_char u_char; }
# 35 "/usr/include/sys/types.h" 3
extern "C" { typedef __u_short u_short; }
# 36 "/usr/include/sys/types.h" 3
extern "C" { typedef __u_int u_int; }
# 37 "/usr/include/sys/types.h" 3
extern "C" { typedef __u_long u_long; }
# 38 "/usr/include/sys/types.h" 3
extern "C" { typedef __quad_t quad_t; }
# 39 "/usr/include/sys/types.h" 3
extern "C" { typedef __u_quad_t u_quad_t; }
# 40 "/usr/include/sys/types.h" 3
extern "C" { typedef __fsid_t fsid_t; }
# 45 "/usr/include/sys/types.h" 3
extern "C" { typedef __loff_t loff_t; }
# 49 "/usr/include/sys/types.h" 3
extern "C" { typedef __ino_t ino_t; }
# 56 "/usr/include/sys/types.h" 3
extern "C" { typedef __ino64_t ino64_t; }
# 61 "/usr/include/sys/types.h" 3
extern "C" { typedef __dev_t dev_t; }
# 66 "/usr/include/sys/types.h" 3
extern "C" { typedef __gid_t gid_t; }
# 71 "/usr/include/sys/types.h" 3
extern "C" { typedef __mode_t mode_t; }
# 76 "/usr/include/sys/types.h" 3
extern "C" { typedef __nlink_t nlink_t; }
# 81 "/usr/include/sys/types.h" 3
extern "C" { typedef __uid_t uid_t; }
# 87 "/usr/include/sys/types.h" 3
extern "C" { typedef __off_t off_t; }
# 94 "/usr/include/sys/types.h" 3
extern "C" { typedef __off64_t off64_t; }
# 105 "/usr/include/sys/types.h" 3
extern "C" { typedef __id_t id_t; }
# 110 "/usr/include/sys/types.h" 3
extern "C" { typedef __ssize_t ssize_t; }
# 116 "/usr/include/sys/types.h" 3
extern "C" { typedef __daddr_t daddr_t; }
# 117 "/usr/include/sys/types.h" 3
extern "C" { typedef __caddr_t caddr_t; }
# 123 "/usr/include/sys/types.h" 3
extern "C" { typedef __key_t key_t; }
# 137 "/usr/include/sys/types.h" 3
extern "C" { typedef __useconds_t useconds_t; }
# 141 "/usr/include/sys/types.h" 3
extern "C" { typedef __suseconds_t suseconds_t; }
# 151 "/usr/include/sys/types.h" 3
extern "C" { typedef unsigned long ulong; }
# 152 "/usr/include/sys/types.h" 3
extern "C" { typedef unsigned short ushort; }
# 153 "/usr/include/sys/types.h" 3
extern "C" { typedef unsigned uint; }
# 195 "/usr/include/sys/types.h" 3
extern "C" { typedef signed char int8_t __attribute((__mode__(__QI__))); }
# 196 "/usr/include/sys/types.h" 3
extern "C" { typedef short int16_t __attribute((__mode__(__HI__))); }
# 197 "/usr/include/sys/types.h" 3
extern "C" { typedef int int32_t __attribute((__mode__(__SI__))); }
# 198 "/usr/include/sys/types.h" 3
extern "C" { typedef long int64_t __attribute((__mode__(__DI__))); }
# 201 "/usr/include/sys/types.h" 3
extern "C" { typedef unsigned char u_int8_t __attribute((__mode__(__QI__))); }
# 202 "/usr/include/sys/types.h" 3
extern "C" { typedef unsigned short u_int16_t __attribute((__mode__(__HI__))); }
# 203 "/usr/include/sys/types.h" 3
extern "C" { typedef unsigned u_int32_t __attribute((__mode__(__SI__))); }
# 204 "/usr/include/sys/types.h" 3
extern "C" { typedef unsigned long u_int64_t __attribute((__mode__(__DI__))); }
# 206 "/usr/include/sys/types.h" 3
extern "C" { typedef long register_t __attribute((__mode__(__word__))); }
# 24 "/usr/include/bits/sigset.h" 3
extern "C" { typedef int __sig_atomic_t; }
# 32 "/usr/include/bits/sigset.h" 3
extern "C" { typedef
# 30 "/usr/include/bits/sigset.h" 3
struct {
# 31 "/usr/include/bits/sigset.h" 3
unsigned long __val[(1024) / ((8) * sizeof(unsigned long))];
# 32 "/usr/include/bits/sigset.h" 3
} __sigset_t; }
# 38 "/usr/include/sys/select.h" 3
extern "C" { typedef __sigset_t sigset_t; }
# 75 "/usr/include/bits/time.h" 3
extern "C" { struct timeval {
# 77 "/usr/include/bits/time.h" 3
__time_t tv_sec;
# 78 "/usr/include/bits/time.h" 3
__suseconds_t tv_usec;
# 79 "/usr/include/bits/time.h" 3
}; }
# 55 "/usr/include/sys/select.h" 3
extern "C" { typedef long __fd_mask; }
# 78 "/usr/include/sys/select.h" 3
extern "C" { typedef
# 68 "/usr/include/sys/select.h" 3
struct {
# 72 "/usr/include/sys/select.h" 3
__fd_mask fds_bits[1024 / (8 * ((int)sizeof(__fd_mask)))];
# 78 "/usr/include/sys/select.h" 3
} fd_set; }
# 85 "/usr/include/sys/select.h" 3
extern "C" { typedef __fd_mask fd_mask; }
# 109 "/usr/include/sys/select.h" 3
extern "C" int select(int , fd_set *__restrict__ , fd_set *__restrict__ , fd_set *__restrict__ , timeval *__restrict__ );
# 121 "/usr/include/sys/select.h" 3
extern "C" int pselect(int , fd_set *__restrict__ , fd_set *__restrict__ , fd_set *__restrict__ , const timespec *__restrict__ , const __sigset_t *__restrict__ );
# 31 "/usr/include/sys/sysmacros.h" 3
extern "C" unsigned gnu_dev_major(unsigned long long ) throw();
# 34 "/usr/include/sys/sysmacros.h" 3
extern "C" unsigned gnu_dev_minor(unsigned long long ) throw();
# 37 "/usr/include/sys/sysmacros.h" 3
extern "C" unsigned long long gnu_dev_makedev(unsigned , unsigned ) throw();
# 229 "/usr/include/sys/types.h" 3
extern "C" { typedef __blksize_t blksize_t; }
# 236 "/usr/include/sys/types.h" 3
extern "C" { typedef __blkcnt_t blkcnt_t; }
# 240 "/usr/include/sys/types.h" 3
extern "C" { typedef __fsblkcnt_t fsblkcnt_t; }
# 244 "/usr/include/sys/types.h" 3
extern "C" { typedef __fsfilcnt_t fsfilcnt_t; }
# 263 "/usr/include/sys/types.h" 3
extern "C" { typedef __blkcnt64_t blkcnt64_t; }
# 264 "/usr/include/sys/types.h" 3
extern "C" { typedef __fsblkcnt64_t fsblkcnt64_t; }
# 265 "/usr/include/sys/types.h" 3
extern "C" { typedef __fsfilcnt64_t fsfilcnt64_t; }
# 50 "/usr/include/bits/pthreadtypes.h" 3
extern "C" { typedef unsigned long pthread_t; }
# 57 "/usr/include/bits/pthreadtypes.h" 3
extern "C" { typedef
# 54 "/usr/include/bits/pthreadtypes.h" 3
union {
# 55 "/usr/include/bits/pthreadtypes.h" 3
char __size[56];
# 56 "/usr/include/bits/pthreadtypes.h" 3
long __align;
# 57 "/usr/include/bits/pthreadtypes.h" 3
} pthread_attr_t; }
# 65 "/usr/include/bits/pthreadtypes.h" 3
extern "C" { typedef
# 61 "/usr/include/bits/pthreadtypes.h" 3
struct __pthread_internal_list {
# 63 "/usr/include/bits/pthreadtypes.h" 3
__pthread_internal_list *__prev;
# 64 "/usr/include/bits/pthreadtypes.h" 3
__pthread_internal_list *__next;
# 65 "/usr/include/bits/pthreadtypes.h" 3
} __pthread_list_t; }
# 104 "/usr/include/bits/pthreadtypes.h" 3
extern "C" { typedef
# 77 "/usr/include/bits/pthreadtypes.h" 3
union {
# 78 "/usr/include/bits/pthreadtypes.h" 3
struct __pthread_mutex_s {
# 80 "/usr/include/bits/pthreadtypes.h" 3
int __lock;
# 81 "/usr/include/bits/pthreadtypes.h" 3
unsigned __count;
# 82 "/usr/include/bits/pthreadtypes.h" 3
int __owner;
# 84 "/usr/include/bits/pthreadtypes.h" 3
unsigned __nusers;
# 88 "/usr/include/bits/pthreadtypes.h" 3
int __kind;
# 90 "/usr/include/bits/pthreadtypes.h" 3
int __spins;
# 91 "/usr/include/bits/pthreadtypes.h" 3
__pthread_list_t __list;
# 101 "/usr/include/bits/pthreadtypes.h" 3
} __data;
# 102 "/usr/include/bits/pthreadtypes.h" 3
char __size[40];
# 103 "/usr/include/bits/pthreadtypes.h" 3
long __align;
# 104 "/usr/include/bits/pthreadtypes.h" 3
} pthread_mutex_t; }
# 110 "/usr/include/bits/pthreadtypes.h" 3
extern "C" { typedef
# 107 "/usr/include/bits/pthreadtypes.h" 3
union {
# 108 "/usr/include/bits/pthreadtypes.h" 3
char __size[4];
# 109 "/usr/include/bits/pthreadtypes.h" 3
int __align;
# 110 "/usr/include/bits/pthreadtypes.h" 3
} pthread_mutexattr_t; }
# 130 "/usr/include/bits/pthreadtypes.h" 3
extern "C" { typedef
# 116 "/usr/include/bits/pthreadtypes.h" 3
union {
# 118 "/usr/include/bits/pthreadtypes.h" 3
struct {
# 119 "/usr/include/bits/pthreadtypes.h" 3
int __lock;
# 120 "/usr/include/bits/pthreadtypes.h" 3
unsigned __futex;
# 121 "/usr/include/bits/pthreadtypes.h" 3
__extension__ unsigned long long __total_seq;
# 122 "/usr/include/bits/pthreadtypes.h" 3
__extension__ unsigned long long __wakeup_seq;
# 123 "/usr/include/bits/pthreadtypes.h" 3
__extension__ unsigned long long __woken_seq;
# 124 "/usr/include/bits/pthreadtypes.h" 3
void *__mutex;
# 125 "/usr/include/bits/pthreadtypes.h" 3
unsigned __nwaiters;
# 126 "/usr/include/bits/pthreadtypes.h" 3
unsigned __broadcast_seq;
# 127 "/usr/include/bits/pthreadtypes.h" 3
} __data;
# 128 "/usr/include/bits/pthreadtypes.h" 3
char __size[48];
# 129 "/usr/include/bits/pthreadtypes.h" 3
__extension__ long long __align;
# 130 "/usr/include/bits/pthreadtypes.h" 3
} pthread_cond_t; }
# 136 "/usr/include/bits/pthreadtypes.h" 3
extern "C" { typedef
# 133 "/usr/include/bits/pthreadtypes.h" 3
union {
# 134 "/usr/include/bits/pthreadtypes.h" 3
char __size[4];
# 135 "/usr/include/bits/pthreadtypes.h" 3
int __align;
# 136 "/usr/include/bits/pthreadtypes.h" 3
} pthread_condattr_t; }
# 140 "/usr/include/bits/pthreadtypes.h" 3
extern "C" { typedef unsigned pthread_key_t; }
# 144 "/usr/include/bits/pthreadtypes.h" 3
extern "C" { typedef int pthread_once_t; }
# 189 "/usr/include/bits/pthreadtypes.h" 3
extern "C" { typedef
# 151 "/usr/include/bits/pthreadtypes.h" 3
union {
# 154 "/usr/include/bits/pthreadtypes.h" 3
struct {
# 155 "/usr/include/bits/pthreadtypes.h" 3
int __lock;
# 156 "/usr/include/bits/pthreadtypes.h" 3
unsigned __nr_readers;
# 157 "/usr/include/bits/pthreadtypes.h" 3
unsigned __readers_wakeup;
# 158 "/usr/include/bits/pthreadtypes.h" 3
unsigned __writer_wakeup;
# 159 "/usr/include/bits/pthreadtypes.h" 3
unsigned __nr_readers_queued;
# 160 "/usr/include/bits/pthreadtypes.h" 3
unsigned __nr_writers_queued;
# 161 "/usr/include/bits/pthreadtypes.h" 3
int __writer;
# 162 "/usr/include/bits/pthreadtypes.h" 3
int __shared;
# 163 "/usr/include/bits/pthreadtypes.h" 3
unsigned long __pad1;
# 164 "/usr/include/bits/pthreadtypes.h" 3
unsigned long __pad2;
# 167 "/usr/include/bits/pthreadtypes.h" 3
unsigned __flags;
# 168 "/usr/include/bits/pthreadtypes.h" 3
} __data;
# 187 "/usr/include/bits/pthreadtypes.h" 3
char __size[56];
# 188 "/usr/include/bits/pthreadtypes.h" 3
long __align;
# 189 "/usr/include/bits/pthreadtypes.h" 3
} pthread_rwlock_t; }
# 195 "/usr/include/bits/pthreadtypes.h" 3
extern "C" { typedef
# 192 "/usr/include/bits/pthreadtypes.h" 3
union {
# 193 "/usr/include/bits/pthreadtypes.h" 3
char __size[8];
# 194 "/usr/include/bits/pthreadtypes.h" 3
long __align;
# 195 "/usr/include/bits/pthreadtypes.h" 3
} pthread_rwlockattr_t; }
# 201 "/usr/include/bits/pthreadtypes.h" 3
extern "C" { typedef volatile int pthread_spinlock_t; }
# 210 "/usr/include/bits/pthreadtypes.h" 3
extern "C" { typedef
# 207 "/usr/include/bits/pthreadtypes.h" 3
union {
# 208 "/usr/include/bits/pthreadtypes.h" 3
char __size[32];
# 209 "/usr/include/bits/pthreadtypes.h" 3
long __align;
# 210 "/usr/include/bits/pthreadtypes.h" 3
} pthread_barrier_t; }
# 216 "/usr/include/bits/pthreadtypes.h" 3
extern "C" { typedef
# 213 "/usr/include/bits/pthreadtypes.h" 3
union {
# 214 "/usr/include/bits/pthreadtypes.h" 3
char __size[4];
# 215 "/usr/include/bits/pthreadtypes.h" 3
int __align;
# 216 "/usr/include/bits/pthreadtypes.h" 3
} pthread_barrierattr_t; }
# 327 "/usr/include/stdlib.h" 3
extern "C" long random() throw();
# 330 "/usr/include/stdlib.h" 3
extern "C" void srandom(unsigned ) throw();
# 336 "/usr/include/stdlib.h" 3
extern "C" char *initstate(unsigned , char * , size_t ) throw()
# 337 "/usr/include/stdlib.h" 3
 __attribute((__nonnull__(2)));
# 341 "/usr/include/stdlib.h" 3
extern "C" char *setstate(char * ) throw() __attribute((__nonnull__(1)));
# 349 "/usr/include/stdlib.h" 3
extern "C" { struct random_data {
# 351 "/usr/include/stdlib.h" 3
int32_t *fptr;
# 352 "/usr/include/stdlib.h" 3
int32_t *rptr;
# 353 "/usr/include/stdlib.h" 3
int32_t *state;
# 354 "/usr/include/stdlib.h" 3
int rand_type;
# 355 "/usr/include/stdlib.h" 3
int rand_deg;
# 356 "/usr/include/stdlib.h" 3
int rand_sep;
# 357 "/usr/include/stdlib.h" 3
int32_t *end_ptr;
# 358 "/usr/include/stdlib.h" 3
}; }
# 360 "/usr/include/stdlib.h" 3
extern "C" int random_r(random_data *__restrict__ , int32_t *__restrict__ ) throw()
# 361 "/usr/include/stdlib.h" 3
 __attribute((__nonnull__(1, 2)));
# 363 "/usr/include/stdlib.h" 3
extern "C" int srandom_r(unsigned , random_data * ) throw()
# 364 "/usr/include/stdlib.h" 3
 __attribute((__nonnull__(2)));
# 366 "/usr/include/stdlib.h" 3
extern "C" int initstate_r(unsigned , char *__restrict__ , size_t , random_data *__restrict__ ) throw()
# 369 "/usr/include/stdlib.h" 3
 __attribute((__nonnull__(2, 4)));
# 371 "/usr/include/stdlib.h" 3
extern "C" int setstate_r(char *__restrict__ , random_data *__restrict__ ) throw()
# 373 "/usr/include/stdlib.h" 3
 __attribute((__nonnull__(1, 2)));
# 380 "/usr/include/stdlib.h" 3
extern "C" int rand() throw();
# 382 "/usr/include/stdlib.h" 3
extern "C" void srand(unsigned ) throw();
# 387 "/usr/include/stdlib.h" 3
extern "C" int rand_r(unsigned * ) throw();
# 395 "/usr/include/stdlib.h" 3
extern "C" double drand48() throw();
# 396 "/usr/include/stdlib.h" 3
extern "C" double erand48(unsigned short [3]) throw() __attribute((__nonnull__(1)));
# 399 "/usr/include/stdlib.h" 3
extern "C" long lrand48() throw();
# 400 "/usr/include/stdlib.h" 3
extern "C" long nrand48(unsigned short [3]) throw()
# 401 "/usr/include/stdlib.h" 3
 __attribute((__nonnull__(1)));
# 404 "/usr/include/stdlib.h" 3
extern "C" long mrand48() throw();
# 405 "/usr/include/stdlib.h" 3
extern "C" long jrand48(unsigned short [3]) throw()
# 406 "/usr/include/stdlib.h" 3
 __attribute((__nonnull__(1)));
# 409 "/usr/include/stdlib.h" 3
extern "C" void srand48(long ) throw();
# 410 "/usr/include/stdlib.h" 3
extern "C" unsigned short *seed48(unsigned short [3]) throw()
# 411 "/usr/include/stdlib.h" 3
 __attribute((__nonnull__(1)));
# 412 "/usr/include/stdlib.h" 3
extern "C" void lcong48(unsigned short [7]) throw() __attribute((__nonnull__(1)));
# 418 "/usr/include/stdlib.h" 3
extern "C" { struct drand48_data {
# 420 "/usr/include/stdlib.h" 3
unsigned short __x[3];
# 421 "/usr/include/stdlib.h" 3
unsigned short __old_x[3];
# 422 "/usr/include/stdlib.h" 3
unsigned short __c;
# 423 "/usr/include/stdlib.h" 3
unsigned short __init;
# 424 "/usr/include/stdlib.h" 3
unsigned long long __a;
# 425 "/usr/include/stdlib.h" 3
}; }
# 428 "/usr/include/stdlib.h" 3
extern "C" int drand48_r(drand48_data *__restrict__ , double *__restrict__ ) throw()
# 429 "/usr/include/stdlib.h" 3
 __attribute((__nonnull__(1, 2)));
# 430 "/usr/include/stdlib.h" 3
extern "C" int erand48_r(unsigned short [3], drand48_data *__restrict__ , double *__restrict__ ) throw()
# 432 "/usr/include/stdlib.h" 3
 __attribute((__nonnull__(1, 2)));
# 435 "/usr/include/stdlib.h" 3
extern "C" int lrand48_r(drand48_data *__restrict__ , long *__restrict__ ) throw()
# 437 "/usr/include/stdlib.h" 3
 __attribute((__nonnull__(1, 2)));
# 438 "/usr/include/stdlib.h" 3
extern "C" int nrand48_r(unsigned short [3], drand48_data *__restrict__ , long *__restrict__ ) throw()
# 441 "/usr/include/stdlib.h" 3
 __attribute((__nonnull__(1, 2)));
# 444 "/usr/include/stdlib.h" 3
extern "C" int mrand48_r(drand48_data *__restrict__ , long *__restrict__ ) throw()
# 446 "/usr/include/stdlib.h" 3
 __attribute((__nonnull__(1, 2)));
# 447 "/usr/include/stdlib.h" 3
extern "C" int jrand48_r(unsigned short [3], drand48_data *__restrict__ , long *__restrict__ ) throw()
# 450 "/usr/include/stdlib.h" 3
 __attribute((__nonnull__(1, 2)));
# 453 "/usr/include/stdlib.h" 3
extern "C" int srand48_r(long , drand48_data * ) throw()
# 454 "/usr/include/stdlib.h" 3
 __attribute((__nonnull__(2)));
# 456 "/usr/include/stdlib.h" 3
extern "C" int seed48_r(unsigned short [3], drand48_data * ) throw()
# 457 "/usr/include/stdlib.h" 3
 __attribute((__nonnull__(1, 2)));
# 459 "/usr/include/stdlib.h" 3
extern "C" int lcong48_r(unsigned short [7], drand48_data * ) throw()
# 461 "/usr/include/stdlib.h" 3
 __attribute((__nonnull__(1, 2)));
# 471 "/usr/include/stdlib.h" 3
extern "C" void *malloc(size_t ) throw() __attribute((__malloc__));
# 473 "/usr/include/stdlib.h" 3
extern "C" void *calloc(size_t , size_t ) throw()
# 474 "/usr/include/stdlib.h" 3
 __attribute((__malloc__));
# 485 "/usr/include/stdlib.h" 3
extern "C" void *realloc(void * , size_t ) throw()
# 486 "/usr/include/stdlib.h" 3
 __attribute((__warn_unused_result__));
# 488 "/usr/include/stdlib.h" 3
extern "C" void free(void * ) throw();
# 493 "/usr/include/stdlib.h" 3
extern "C" void cfree(void * ) throw();
# 33 "/usr/include/alloca.h" 3
extern "C" void *alloca(size_t ) throw();
# 503 "/usr/include/stdlib.h" 3
extern "C" void *valloc(size_t ) throw() __attribute((__malloc__));
# 508 "/usr/include/stdlib.h" 3
extern "C" int posix_memalign(void ** , size_t , size_t ) throw()
# 509 "/usr/include/stdlib.h" 3
 __attribute((__nonnull__(1)));
# 514 "/usr/include/stdlib.h" 3
extern "C" void abort() throw() __attribute((__noreturn__));
# 518 "/usr/include/stdlib.h" 3
extern "C" int atexit(void (* )(void)) throw() __attribute((__nonnull__(1)));
# 525 "/usr/include/stdlib.h" 3
int at_quick_exit(void (* )(void)) throw() __asm__("at_quick_exit")
# 526 "/usr/include/stdlib.h" 3
 __attribute((__nonnull__(1)));
# 536 "/usr/include/stdlib.h" 3
extern "C" int on_exit(void (* )(int , void * ), void * ) throw()
# 537 "/usr/include/stdlib.h" 3
 __attribute((__nonnull__(1)));
# 544 "/usr/include/stdlib.h" 3
extern "C" void exit(int ) throw() __attribute((__noreturn__));
# 552 "/usr/include/stdlib.h" 3
extern "C" void quick_exit(int ) throw() __attribute((__noreturn__));
# 560 "/usr/include/stdlib.h" 3
extern "C" void _Exit(int ) throw() __attribute((__noreturn__));
# 567 "/usr/include/stdlib.h" 3
extern "C" char *getenv(const char * ) throw() __attribute((__nonnull__(1)));
# 572 "/usr/include/stdlib.h" 3
extern "C" char *__secure_getenv(const char * ) throw()
# 573 "/usr/include/stdlib.h" 3
 __attribute((__nonnull__(1)));
# 579 "/usr/include/stdlib.h" 3
extern "C" int putenv(char * ) throw() __attribute((__nonnull__(1)));
# 585 "/usr/include/stdlib.h" 3
extern "C" int setenv(const char * , const char * , int ) throw()
# 586 "/usr/include/stdlib.h" 3
 __attribute((__nonnull__(2)));
# 589 "/usr/include/stdlib.h" 3
extern "C" int unsetenv(const char * ) throw() __attribute((__nonnull__(1)));
# 596 "/usr/include/stdlib.h" 3
extern "C" int clearenv() throw();
# 606 "/usr/include/stdlib.h" 3
extern "C" char *mktemp(char * ) throw() __attribute((__nonnull__(1)));
# 620 "/usr/include/stdlib.h" 3
extern "C" int mkstemp(char * ) __attribute((__nonnull__(1)));
# 630 "/usr/include/stdlib.h" 3
extern "C" int mkstemp64(char * ) __attribute((__nonnull__(1)));
# 642 "/usr/include/stdlib.h" 3
extern "C" int mkstemps(char * , int ) __attribute((__nonnull__(1)));
# 652 "/usr/include/stdlib.h" 3
extern "C" int mkstemps64(char * , int )
# 653 "/usr/include/stdlib.h" 3
 __attribute((__nonnull__(1)));
# 663 "/usr/include/stdlib.h" 3
extern "C" char *mkdtemp(char * ) throw() __attribute((__nonnull__(1)));
# 674 "/usr/include/stdlib.h" 3
extern "C" int mkostemp(char * , int ) __attribute((__nonnull__(1)));
# 684 "/usr/include/stdlib.h" 3
extern "C" int mkostemp64(char * , int ) __attribute((__nonnull__(1)));
# 694 "/usr/include/stdlib.h" 3
extern "C" int mkostemps(char * , int , int )
# 695 "/usr/include/stdlib.h" 3
 __attribute((__nonnull__(1)));
# 706 "/usr/include/stdlib.h" 3
extern "C" int mkostemps64(char * , int , int )
# 707 "/usr/include/stdlib.h" 3
 __attribute((__nonnull__(1)));
# 717 "/usr/include/stdlib.h" 3
extern "C" int system(const char * );
# 724 "/usr/include/stdlib.h" 3
extern "C" char *canonicalize_file_name(const char * ) throw()
# 725 "/usr/include/stdlib.h" 3
 __attribute((__nonnull__(1)));
# 734 "/usr/include/stdlib.h" 3
extern "C" char *realpath(const char *__restrict__ , char *__restrict__ ) throw();
# 742 "/usr/include/stdlib.h" 3
extern "C" { typedef int (*__compar_fn_t)(const void *, const void *); }
# 745 "/usr/include/stdlib.h" 3
extern "C" { typedef __compar_fn_t comparison_fn_t; }
# 749 "/usr/include/stdlib.h" 3
extern "C" { typedef int (*__compar_d_fn_t)(const void *, const void *, void *); }
# 755 "/usr/include/stdlib.h" 3
extern "C" void *bsearch(const void * , const void * , size_t , size_t , __compar_fn_t )
# 757 "/usr/include/stdlib.h" 3
 __attribute((__nonnull__(1, 2, 5)));
# 761 "/usr/include/stdlib.h" 3
extern "C" void qsort(void * , size_t , size_t , __compar_fn_t )
# 762 "/usr/include/stdlib.h" 3
 __attribute((__nonnull__(1, 4)));
# 764 "/usr/include/stdlib.h" 3
extern "C" void qsort_r(void * , size_t , size_t , __compar_d_fn_t , void * )
# 766 "/usr/include/stdlib.h" 3
 __attribute((__nonnull__(1, 4)));
# 771 "/usr/include/stdlib.h" 3
extern "C" int abs(int ) throw() __attribute((const));
# 772 "/usr/include/stdlib.h" 3
extern "C" long labs(long ) throw() __attribute((const));
# 776 "/usr/include/stdlib.h" 3
extern "C" long long llabs(long long ) throw()
# 777 "/usr/include/stdlib.h" 3
 __attribute((const));
# 785 "/usr/include/stdlib.h" 3
extern "C" div_t div(int , int ) throw()
# 786 "/usr/include/stdlib.h" 3
 __attribute((const));
# 787 "/usr/include/stdlib.h" 3
extern "C" ldiv_t ldiv(long , long ) throw()
# 788 "/usr/include/stdlib.h" 3
 __attribute((const));
# 793 "/usr/include/stdlib.h" 3
extern "C" lldiv_t lldiv(long long , long long ) throw()
# 795 "/usr/include/stdlib.h" 3
 __attribute((const));
# 808 "/usr/include/stdlib.h" 3
extern "C" char *ecvt(double , int , int *__restrict__ , int *__restrict__ ) throw()
# 809 "/usr/include/stdlib.h" 3
 __attribute((__nonnull__(3, 4)));
# 814 "/usr/include/stdlib.h" 3
extern "C" char *fcvt(double , int , int *__restrict__ , int *__restrict__ ) throw()
# 815 "/usr/include/stdlib.h" 3
 __attribute((__nonnull__(3, 4)));
# 820 "/usr/include/stdlib.h" 3
extern "C" char *gcvt(double , int , char * ) throw()
# 821 "/usr/include/stdlib.h" 3
 __attribute((__nonnull__(3)));
# 826 "/usr/include/stdlib.h" 3
extern "C" char *qecvt(long double , int , int *__restrict__ , int *__restrict__ ) throw()
# 828 "/usr/include/stdlib.h" 3
 __attribute((__nonnull__(3, 4)));
# 829 "/usr/include/stdlib.h" 3
extern "C" char *qfcvt(long double , int , int *__restrict__ , int *__restrict__ ) throw()
# 831 "/usr/include/stdlib.h" 3
 __attribute((__nonnull__(3, 4)));
# 832 "/usr/include/stdlib.h" 3
extern "C" char *qgcvt(long double , int , char * ) throw()
# 833 "/usr/include/stdlib.h" 3
 __attribute((__nonnull__(3)));
# 838 "/usr/include/stdlib.h" 3
extern "C" int ecvt_r(double , int , int *__restrict__ , int *__restrict__ , char *__restrict__ , size_t ) throw()
# 840 "/usr/include/stdlib.h" 3
 __attribute((__nonnull__(3, 4, 5)));
# 841 "/usr/include/stdlib.h" 3
extern "C" int fcvt_r(double , int , int *__restrict__ , int *__restrict__ , char *__restrict__ , size_t ) throw()
# 843 "/usr/include/stdlib.h" 3
 __attribute((__nonnull__(3, 4, 5)));
# 845 "/usr/include/stdlib.h" 3
extern "C" int qecvt_r(long double , int , int *__restrict__ , int *__restrict__ , char *__restrict__ , size_t ) throw()
# 848 "/usr/include/stdlib.h" 3
 __attribute((__nonnull__(3, 4, 5)));
# 849 "/usr/include/stdlib.h" 3
extern "C" int qfcvt_r(long double , int , int *__restrict__ , int *__restrict__ , char *__restrict__ , size_t ) throw()
# 852 "/usr/include/stdlib.h" 3
 __attribute((__nonnull__(3, 4, 5)));
# 860 "/usr/include/stdlib.h" 3
extern "C" int mblen(const char * , size_t ) throw();
# 863 "/usr/include/stdlib.h" 3
extern "C" int mbtowc(wchar_t *__restrict__ , const char *__restrict__ , size_t ) throw();
# 867 "/usr/include/stdlib.h" 3
extern "C" int wctomb(char * , wchar_t ) throw();
# 871 "/usr/include/stdlib.h" 3
extern "C" size_t mbstowcs(wchar_t *__restrict__ , const char *__restrict__ , size_t ) throw();
# 874 "/usr/include/stdlib.h" 3
extern "C" size_t wcstombs(char *__restrict__ , const wchar_t *__restrict__ , size_t ) throw();
# 885 "/usr/include/stdlib.h" 3
extern "C" int rpmatch(const char * ) throw() __attribute((__nonnull__(1)));
# 896 "/usr/include/stdlib.h" 3
extern "C" int getsubopt(char **__restrict__ , char *const *__restrict__ , char **__restrict__ ) throw()
# 899 "/usr/include/stdlib.h" 3
 __attribute((__nonnull__(1, 2, 3)));
# 905 "/usr/include/stdlib.h" 3
extern "C" void setkey(const char * ) throw() __attribute((__nonnull__(1)));
# 913 "/usr/include/stdlib.h" 3
extern "C" int posix_openpt(int );
# 921 "/usr/include/stdlib.h" 3
extern "C" int grantpt(int ) throw();
# 925 "/usr/include/stdlib.h" 3
extern "C" int unlockpt(int ) throw();
# 930 "/usr/include/stdlib.h" 3
extern "C" char *ptsname(int ) throw();
# 937 "/usr/include/stdlib.h" 3
extern "C" int ptsname_r(int , char * , size_t ) throw()
# 938 "/usr/include/stdlib.h" 3
 __attribute((__nonnull__(2)));
# 941 "/usr/include/stdlib.h" 3
extern "C" int getpt();
# 948 "/usr/include/stdlib.h" 3
extern "C" int getloadavg(double [], int ) throw()
# 949 "/usr/include/stdlib.h" 3
 __attribute((__nonnull__(1)));
# 69 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
namespace __gnu_cxx __attribute((__visibility__("default"))) {
# 71 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
template< class _Iterator, class _Container> class __normal_iterator;
# 74 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
}
# 76 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
namespace std __attribute((__visibility__("default")))
# 77 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
 __attribute((__visibility__("default")))
# 492 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
 __attribute((__visibility__("default")))
# 35 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cmath.tcc" 3
 __attribute((__visibility__("default")))
# 49 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstddef" 3
 __attribute((__visibility__("default")))
# 100 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstdlib" 3
 __attribute((__visibility__("default")))
# 199 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstdlib" 3
 __attribute((__visibility__("default"))) {
# 78 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
struct __true_type { };
# 79 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
struct __false_type { };
# 81 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
template< bool __T0>
# 82 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
struct __truth_type {
# 83 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
typedef __false_type __type; };
# 86 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
template<> struct __truth_type< true> {
# 87 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
typedef __true_type __type; };
# 91 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
template< class _Sp, class _Tp>
# 92 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
struct __traitor {
# 94 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
enum { __value = (((bool)_Sp::__value) || ((bool)_Tp::__value))};
# 95 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
typedef typename __truth_type< __value> ::__type __type;
# 96 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
};
# 99 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
template< class , class >
# 100 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
struct __are_same {
# 102 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
enum { __value};
# 103 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
typedef __false_type __type;
# 104 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
};
# 106 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
template< class _Tp>
# 107 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
struct __are_same< _Tp, _Tp> {
# 109 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
enum { __value = 1};
# 110 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
typedef __true_type __type;
# 111 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
};
# 114 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
template< class _Tp>
# 115 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
struct __is_void {
# 117 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
enum { __value};
# 118 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
typedef __false_type __type;
# 119 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
};
# 122 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
template<> struct __is_void< void> {
# 124 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
enum { __value = 1};
# 125 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
typedef __true_type __type;
# 126 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
};
# 131 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
template< class _Tp>
# 132 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
struct __is_integer {
# 134 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
enum { __value};
# 135 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
typedef __false_type __type;
# 136 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
};
# 142 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
template<> struct __is_integer< bool> {
# 144 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
enum { __value = 1};
# 145 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
typedef __true_type __type;
# 146 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
};
# 149 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
template<> struct __is_integer< char> {
# 151 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
enum { __value = 1};
# 152 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
typedef __true_type __type;
# 153 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
};
# 156 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
template<> struct __is_integer< signed char> {
# 158 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
enum { __value = 1};
# 159 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
typedef __true_type __type;
# 160 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
};
# 163 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
template<> struct __is_integer< unsigned char> {
# 165 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
enum { __value = 1};
# 166 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
typedef __true_type __type;
# 167 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
};
# 171 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
template<> struct __is_integer< wchar_t> {
# 173 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
enum { __value = 1};
# 174 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
typedef __true_type __type;
# 175 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
};
# 195 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
template<> struct __is_integer< short> {
# 197 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
enum { __value = 1};
# 198 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
typedef __true_type __type;
# 199 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
};
# 202 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
template<> struct __is_integer< unsigned short> {
# 204 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
enum { __value = 1};
# 205 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
typedef __true_type __type;
# 206 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
};
# 209 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
template<> struct __is_integer< int> {
# 211 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
enum { __value = 1};
# 212 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
typedef __true_type __type;
# 213 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
};
# 216 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
template<> struct __is_integer< unsigned> {
# 218 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
enum { __value = 1};
# 219 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
typedef __true_type __type;
# 220 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
};
# 223 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
template<> struct __is_integer< long> {
# 225 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
enum { __value = 1};
# 226 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
typedef __true_type __type;
# 227 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
};
# 230 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
template<> struct __is_integer< unsigned long> {
# 232 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
enum { __value = 1};
# 233 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
typedef __true_type __type;
# 234 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
};
# 237 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
template<> struct __is_integer< long long> {
# 239 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
enum { __value = 1};
# 240 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
typedef __true_type __type;
# 241 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
};
# 244 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
template<> struct __is_integer< unsigned long long> {
# 246 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
enum { __value = 1};
# 247 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
typedef __true_type __type;
# 248 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
};
# 253 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
template< class _Tp>
# 254 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
struct __is_floating {
# 256 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
enum { __value};
# 257 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
typedef __false_type __type;
# 258 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
};
# 262 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
template<> struct __is_floating< float> {
# 264 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
enum { __value = 1};
# 265 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
typedef __true_type __type;
# 266 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
};
# 269 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
template<> struct __is_floating< double> {
# 271 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
enum { __value = 1};
# 272 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
typedef __true_type __type;
# 273 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
};
# 276 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
template<> struct __is_floating< long double> {
# 278 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
enum { __value = 1};
# 279 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
typedef __true_type __type;
# 280 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
};
# 285 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
template< class _Tp>
# 286 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
struct __is_pointer {
# 288 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
enum { __value};
# 289 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
typedef __false_type __type;
# 290 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
};
# 292 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
template< class _Tp>
# 293 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
struct __is_pointer< _Tp *> {
# 295 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
enum { __value = 1};
# 296 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
typedef __true_type __type;
# 297 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
};
# 302 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
template< class _Tp>
# 303 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
struct __is_normal_iterator {
# 305 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
enum { __value};
# 306 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
typedef __false_type __type;
# 307 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
};
# 309 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
template< class _Iterator, class _Container>
# 310 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
struct __is_normal_iterator< __gnu_cxx::__normal_iterator< _Iterator, _Container> > {
# 313 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
enum { __value = 1};
# 314 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
typedef __true_type __type;
# 315 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
};
# 320 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
template< class _Tp>
# 321 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
struct __is_arithmetic : public __traitor< __is_integer< _Tp> , __is_floating< _Tp> > {
# 323 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
};
# 328 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
template< class _Tp>
# 329 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
struct __is_fundamental : public __traitor< __is_void< _Tp> , __is_arithmetic< _Tp> > {
# 331 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
};
# 336 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
template< class _Tp>
# 337 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
struct __is_scalar : public __traitor< __is_arithmetic< _Tp> , __is_pointer< _Tp> > {
# 339 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
};
# 344 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
template< class _Tp>
# 345 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
struct __is_char {
# 347 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
enum { __value};
# 348 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
typedef __false_type __type;
# 349 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
};
# 352 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
template<> struct __is_char< char> {
# 354 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
enum { __value = 1};
# 355 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
typedef __true_type __type;
# 356 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
};
# 360 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
template<> struct __is_char< wchar_t> {
# 362 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
enum { __value = 1};
# 363 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
typedef __true_type __type;
# 364 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
};
# 367 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
template< class _Tp>
# 368 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
struct __is_byte {
# 370 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
enum { __value};
# 371 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
typedef __false_type __type;
# 372 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
};
# 375 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
template<> struct __is_byte< char> {
# 377 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
enum { __value = 1};
# 378 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
typedef __true_type __type;
# 379 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
};
# 382 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
template<> struct __is_byte< signed char> {
# 384 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
enum { __value = 1};
# 385 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
typedef __true_type __type;
# 386 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
};
# 389 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
template<> struct __is_byte< unsigned char> {
# 391 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
enum { __value = 1};
# 392 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
typedef __true_type __type;
# 393 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
};
# 398 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
template< class _Tp>
# 399 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
struct __is_move_iterator {
# 401 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
enum { __value};
# 402 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
typedef __false_type __type;
# 403 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
};
# 417 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cpp_type_traits.h" 3
}
# 37 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
namespace __gnu_cxx __attribute((__visibility__("default")))
# 157 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstdlib" 3
 __attribute((__visibility__("default"))) {
# 40 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
template< bool __T1, class >
# 41 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
struct __enable_if {
# 42 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
};
# 44 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
template< class _Tp>
# 45 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
struct __enable_if< true, _Tp> {
# 46 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
typedef _Tp __type; };
# 50 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
template< bool _Cond, class _Iftrue, class _Iffalse>
# 51 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
struct __conditional_type {
# 52 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
typedef _Iftrue __type; };
# 54 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
template< class _Iftrue, class _Iffalse>
# 55 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
struct __conditional_type< false, _Iftrue, _Iffalse> {
# 56 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
typedef _Iffalse __type; };
# 60 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
template< class _Tp>
# 61 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
struct __add_unsigned {
# 64 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
private: typedef __enable_if< std::__is_integer< _Tp> ::__value, _Tp> __if_type;
# 67 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
public: typedef typename __enable_if< std::__is_integer< _Tp> ::__value, _Tp> ::__type __type;
# 68 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
};
# 71 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
template<> struct __add_unsigned< char> {
# 72 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
typedef unsigned char __type; };
# 75 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
template<> struct __add_unsigned< signed char> {
# 76 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
typedef unsigned char __type; };
# 79 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
template<> struct __add_unsigned< short> {
# 80 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
typedef unsigned short __type; };
# 83 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
template<> struct __add_unsigned< int> {
# 84 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
typedef unsigned __type; };
# 87 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
template<> struct __add_unsigned< long> {
# 88 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
typedef unsigned long __type; };
# 91 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
template<> struct __add_unsigned< long long> {
# 92 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
typedef unsigned long long __type; };
# 96 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
template<> struct __add_unsigned< bool> ;
# 99 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
template<> struct __add_unsigned< wchar_t> ;
# 103 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
template< class _Tp>
# 104 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
struct __remove_unsigned {
# 107 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
private: typedef __enable_if< std::__is_integer< _Tp> ::__value, _Tp> __if_type;
# 110 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
public: typedef typename __enable_if< std::__is_integer< _Tp> ::__value, _Tp> ::__type __type;
# 111 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
};
# 114 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
template<> struct __remove_unsigned< char> {
# 115 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
typedef signed char __type; };
# 118 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
template<> struct __remove_unsigned< unsigned char> {
# 119 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
typedef signed char __type; };
# 122 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
template<> struct __remove_unsigned< unsigned short> {
# 123 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
typedef short __type; };
# 126 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
template<> struct __remove_unsigned< unsigned> {
# 127 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
typedef int __type; };
# 130 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
template<> struct __remove_unsigned< unsigned long> {
# 131 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
typedef long __type; };
# 134 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
template<> struct __remove_unsigned< unsigned long long> {
# 135 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
typedef long long __type; };
# 139 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
template<> struct __remove_unsigned< bool> ;
# 142 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
template<> struct __remove_unsigned< wchar_t> ;
# 146 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
template < typename _Type >
    inline bool
    __is_null_pointer ( _Type * __ptr )
    { return __ptr == 0; }
# 151 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
template < typename _Type >
    inline bool
    __is_null_pointer ( _Type )
    { return false; }
# 158 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
template< class _Tp, bool __T2 = std::__is_integer< _Tp> ::__value>
# 159 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
struct __promote {
# 160 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
typedef double __type; };
# 162 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
template< class _Tp>
# 163 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
struct __promote< _Tp, false> {
# 164 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
typedef _Tp __type; };
# 166 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
template< class _Tp, class _Up>
# 167 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
struct __promote_2 {
# 170 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
private: typedef typename __promote< _Tp, std::__is_integer< _Tp> ::__value> ::__type __type1;
# 171 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
typedef typename __promote< _Up, std::__is_integer< _Up> ::__value> ::__type __type2;
# 174 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
public: typedef __typeof__((__type1() + __type2())) __type;
# 175 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
};
# 177 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
template< class _Tp, class _Up, class _Vp>
# 178 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
struct __promote_3 {
# 181 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
private: typedef typename __promote< _Tp, std::__is_integer< _Tp> ::__value> ::__type __type1;
# 182 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
typedef typename __promote< _Up, std::__is_integer< _Up> ::__value> ::__type __type2;
# 183 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
typedef typename __promote< _Vp, std::__is_integer< _Vp> ::__value> ::__type __type3;
# 186 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
public: typedef __typeof__(((__type1() + __type2()) + __type3())) __type;
# 187 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
};
# 189 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
template< class _Tp, class _Up, class _Vp, class _Wp>
# 190 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
struct __promote_4 {
# 193 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
private: typedef typename __promote< _Tp, std::__is_integer< _Tp> ::__value> ::__type __type1;
# 194 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
typedef typename __promote< _Up, std::__is_integer< _Up> ::__value> ::__type __type2;
# 195 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
typedef typename __promote< _Vp, std::__is_integer< _Vp> ::__value> ::__type __type3;
# 196 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
typedef typename __promote< _Wp, std::__is_integer< _Wp> ::__value> ::__type __type4;
# 199 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
public: typedef __typeof__((((__type1() + __type2()) + __type3()) + __type4())) __type;
# 200 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
};
# 202 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/ext/type_traits.h" 3
}
# 77 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
namespace std __attribute((__visibility__("default")))
# 492 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
 __attribute((__visibility__("default")))
# 35 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cmath.tcc" 3
 __attribute((__visibility__("default")))
# 49 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstddef" 3
 __attribute((__visibility__("default")))
# 100 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstdlib" 3
 __attribute((__visibility__("default")))
# 199 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstdlib" 3
 __attribute((__visibility__("default"))) {
# 81 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
template < typename _Tp >
    _Tp __cmath_power ( _Tp, unsigned int );
# 84 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
template < typename _Tp >
    inline _Tp
    __pow_helper ( _Tp __x, int __n )
    {
      return __n < 0
        ? _Tp ( 1 ) / __cmath_power ( __x, - __n )
        : __cmath_power ( __x, __n );
    }
# 94 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
inline double abs(double __x)
# 95 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
{ return __builtin_fabs(__x); }
# 98 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
inline float abs(float __x)
# 99 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
{ return __builtin_fabsf(__x); }
# 102 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
inline long double abs(long double __x)
# 103 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
{ return __builtin_fabsl(__x); }
# 105 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
using ::acos;
# 108 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
inline float acos(float __x)
# 109 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
{ return __builtin_acosf(__x); }
# 112 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
inline long double acos(long double __x)
# 113 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
{ return __builtin_acosl(__x); }
# 115 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
template < typename _Tp >
    inline typename __gnu_cxx :: __enable_if < __is_integer < _Tp > :: __value,
        double > :: __type
    acos ( _Tp __x )
    { return __builtin_acos ( __x ); }
# 121 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
using ::asin;
# 124 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
inline float asin(float __x)
# 125 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
{ return __builtin_asinf(__x); }
# 128 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
inline long double asin(long double __x)
# 129 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
{ return __builtin_asinl(__x); }
# 131 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
template < typename _Tp >
    inline typename __gnu_cxx :: __enable_if < __is_integer < _Tp > :: __value,
        double > :: __type
    asin ( _Tp __x )
    { return __builtin_asin ( __x ); }
# 137 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
using ::atan;
# 140 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
inline float atan(float __x)
# 141 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
{ return __builtin_atanf(__x); }
# 144 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
inline long double atan(long double __x)
# 145 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
{ return __builtin_atanl(__x); }
# 147 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
template < typename _Tp >
    inline typename __gnu_cxx :: __enable_if < __is_integer < _Tp > :: __value,
        double > :: __type
    atan ( _Tp __x )
    { return __builtin_atan ( __x ); }
# 153 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
using ::atan2;
# 156 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
inline float atan2(float __y, float __x)
# 157 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
{ return __builtin_atan2f(__y, __x); }
# 160 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
inline long double atan2(long double __y, long double __x)
# 161 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
{ return __builtin_atan2l(__y, __x); }
# 163 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
template < typename _Tp, typename _Up >
    inline
    typename __gnu_cxx :: __promote_2 <
    typename __gnu_cxx :: __enable_if < __is_arithmetic < _Tp > :: __value
        && __is_arithmetic < _Up > :: __value,
        _Tp > :: __type, _Up > :: __type
    atan2 ( _Tp __y, _Up __x )
    {
      typedef typename __gnu_cxx :: __promote_2 < _Tp, _Up > :: __type __type;
      return atan2 ( __type ( __y ), __type ( __x ) );
    }
# 175 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
using ::ceil;
# 178 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
inline float ceil(float __x)
# 179 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
{ return __builtin_ceilf(__x); }
# 182 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
inline long double ceil(long double __x)
# 183 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
{ return __builtin_ceill(__x); }
# 185 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
template < typename _Tp >
    inline typename __gnu_cxx :: __enable_if < __is_integer < _Tp > :: __value,
        double > :: __type
    ceil ( _Tp __x )
    { return __builtin_ceil ( __x ); }
# 191 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
using ::cos;
# 194 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
inline float cos(float __x)
# 195 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
{ return __builtin_cosf(__x); }
# 198 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
inline long double cos(long double __x)
# 199 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
{ return __builtin_cosl(__x); }
# 201 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
template < typename _Tp >
    inline typename __gnu_cxx :: __enable_if < __is_integer < _Tp > :: __value,
        double > :: __type
    cos ( _Tp __x )
    { return __builtin_cos ( __x ); }
# 207 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
using ::cosh;
# 210 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
inline float cosh(float __x)
# 211 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
{ return __builtin_coshf(__x); }
# 214 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
inline long double cosh(long double __x)
# 215 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
{ return __builtin_coshl(__x); }
# 217 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
template < typename _Tp >
    inline typename __gnu_cxx :: __enable_if < __is_integer < _Tp > :: __value,
        double > :: __type
    cosh ( _Tp __x )
    { return __builtin_cosh ( __x ); }
# 223 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
using ::exp;
# 226 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
inline float exp(float __x)
# 227 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
{ return __builtin_expf(__x); }
# 230 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
inline long double exp(long double __x)
# 231 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
{ return __builtin_expl(__x); }
# 233 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
template < typename _Tp >
    inline typename __gnu_cxx :: __enable_if < __is_integer < _Tp > :: __value,
        double > :: __type
    exp ( _Tp __x )
    { return __builtin_exp ( __x ); }
# 239 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
using ::fabs;
# 242 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
inline float fabs(float __x)
# 243 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
{ return __builtin_fabsf(__x); }
# 246 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
inline long double fabs(long double __x)
# 247 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
{ return __builtin_fabsl(__x); }
# 249 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
template < typename _Tp >
    inline typename __gnu_cxx :: __enable_if < __is_integer < _Tp > :: __value,
        double > :: __type
    fabs ( _Tp __x )
    { return __builtin_fabs ( __x ); }
# 255 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
using ::floor;
# 258 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
inline float floor(float __x)
# 259 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
{ return __builtin_floorf(__x); }
# 262 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
inline long double floor(long double __x)
# 263 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
{ return __builtin_floorl(__x); }
# 265 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
template < typename _Tp >
    inline typename __gnu_cxx :: __enable_if < __is_integer < _Tp > :: __value,
        double > :: __type
    floor ( _Tp __x )
    { return __builtin_floor ( __x ); }
# 271 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
using ::fmod;
# 274 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
inline float fmod(float __x, float __y)
# 275 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
{ return __builtin_fmodf(__x, __y); }
# 278 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
inline long double fmod(long double __x, long double __y)
# 279 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
{ return __builtin_fmodl(__x, __y); }
# 281 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
using ::frexp;
# 284 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
inline float frexp(float __x, int *__exp)
# 285 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
{ return __builtin_frexpf(__x, __exp); }
# 288 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
inline long double frexp(long double __x, int *__exp)
# 289 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
{ return __builtin_frexpl(__x, __exp); }
# 291 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
template < typename _Tp >
    inline typename __gnu_cxx :: __enable_if < __is_integer < _Tp > :: __value,
        double > :: __type
    frexp ( _Tp __x, int * __exp )
    { return __builtin_frexp ( __x, __exp ); }
# 297 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
using ::ldexp;
# 300 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
inline float ldexp(float __x, int __exp)
# 301 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
{ return __builtin_ldexpf(__x, __exp); }
# 304 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
inline long double ldexp(long double __x, int __exp)
# 305 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
{ return __builtin_ldexpl(__x, __exp); }
# 307 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
template < typename _Tp >
    inline typename __gnu_cxx :: __enable_if < __is_integer < _Tp > :: __value,
        double > :: __type
  ldexp ( _Tp __x, int __exp )
  { return __builtin_ldexp ( __x, __exp ); }
# 313 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
using ::log;
# 316 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
inline float log(float __x)
# 317 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
{ return __builtin_logf(__x); }
# 320 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
inline long double log(long double __x)
# 321 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
{ return __builtin_logl(__x); }
# 323 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
template < typename _Tp >
    inline typename __gnu_cxx :: __enable_if < __is_integer < _Tp > :: __value,
        double > :: __type
    log ( _Tp __x )
    { return __builtin_log ( __x ); }
# 329 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
using ::log10;
# 332 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
inline float log10(float __x)
# 333 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
{ return __builtin_log10f(__x); }
# 336 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
inline long double log10(long double __x)
# 337 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
{ return __builtin_log10l(__x); }
# 339 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
template < typename _Tp >
    inline typename __gnu_cxx :: __enable_if < __is_integer < _Tp > :: __value,
        double > :: __type
    log10 ( _Tp __x )
    { return __builtin_log10 ( __x ); }
# 345 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
using ::modf;
# 348 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
inline float modf(float __x, float *__iptr)
# 349 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
{ return __builtin_modff(__x, __iptr); }
# 352 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
inline long double modf(long double __x, long double *__iptr)
# 353 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
{ return __builtin_modfl(__x, __iptr); }
# 355 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
using ::pow;
# 358 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
inline float pow(float __x, float __y)
# 359 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
{ return __builtin_powf(__x, __y); }
# 362 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
inline long double pow(long double __x, long double __y)
# 363 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
{ return __builtin_powl(__x, __y); }
# 369 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
inline double pow(double __x, int __i)
# 370 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
{ return __builtin_powi(__x, __i); }
# 373 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
inline float pow(float __x, int __n)
# 374 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
{ return __builtin_powif(__x, __n); }
# 377 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
inline long double pow(long double __x, int __n)
# 378 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
{ return __builtin_powil(__x, __n); }
# 381 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
template < typename _Tp, typename _Up >
    inline
    typename __gnu_cxx :: __promote_2 <
    typename __gnu_cxx :: __enable_if < __is_arithmetic < _Tp > :: __value
        && __is_arithmetic < _Up > :: __value,
        _Tp > :: __type, _Up > :: __type
    pow ( _Tp __x, _Up __y )
    {
      typedef typename __gnu_cxx :: __promote_2 < _Tp, _Up > :: __type __type;
      return pow ( __type ( __x ), __type ( __y ) );
    }
# 393 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
using ::sin;
# 396 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
inline float sin(float __x)
# 397 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
{ return __builtin_sinf(__x); }
# 400 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
inline long double sin(long double __x)
# 401 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
{ return __builtin_sinl(__x); }
# 403 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
template < typename _Tp >
    inline typename __gnu_cxx :: __enable_if < __is_integer < _Tp > :: __value,
        double > :: __type
    sin ( _Tp __x )
    { return __builtin_sin ( __x ); }
# 409 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
using ::sinh;
# 412 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
inline float sinh(float __x)
# 413 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
{ return __builtin_sinhf(__x); }
# 416 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
inline long double sinh(long double __x)
# 417 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
{ return __builtin_sinhl(__x); }
# 419 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
template < typename _Tp >
    inline typename __gnu_cxx :: __enable_if < __is_integer < _Tp > :: __value,
        double > :: __type
    sinh ( _Tp __x )
    { return __builtin_sinh ( __x ); }
# 425 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
using ::sqrt;
# 428 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
inline float sqrt(float __x)
# 429 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
{ return __builtin_sqrtf(__x); }
# 432 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
inline long double sqrt(long double __x)
# 433 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
{ return __builtin_sqrtl(__x); }
# 435 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
template < typename _Tp >
    inline typename __gnu_cxx :: __enable_if < __is_integer < _Tp > :: __value,
        double > :: __type
    sqrt ( _Tp __x )
    { return __builtin_sqrt ( __x ); }
# 441 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
using ::tan;
# 444 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
inline float tan(float __x)
# 445 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
{ return __builtin_tanf(__x); }
# 448 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
inline long double tan(long double __x)
# 449 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
{ return __builtin_tanl(__x); }
# 451 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
template < typename _Tp >
    inline typename __gnu_cxx :: __enable_if < __is_integer < _Tp > :: __value,
        double > :: __type
    tan ( _Tp __x )
    { return __builtin_tan ( __x ); }
# 457 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
using ::tanh;
# 460 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
inline float tanh(float __x)
# 461 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
{ return __builtin_tanhf(__x); }
# 464 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
inline long double tanh(long double __x)
# 465 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
{ return __builtin_tanhl(__x); }
# 467 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
template < typename _Tp >
    inline typename __gnu_cxx :: __enable_if < __is_integer < _Tp > :: __value,
        double > :: __type
    tanh ( _Tp __x )
    { return __builtin_tanh ( __x ); }
# 473 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
}
# 492 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
namespace std __attribute((__visibility__("default")))
# 35 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cmath.tcc" 3
 __attribute((__visibility__("default")))
# 49 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstddef" 3
 __attribute((__visibility__("default")))
# 100 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstdlib" 3
 __attribute((__visibility__("default")))
# 199 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstdlib" 3
 __attribute((__visibility__("default"))) {
# 494 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
template < typename _Tp >
    inline typename __gnu_cxx :: __enable_if < __is_arithmetic < _Tp > :: __value,
        int > :: __type
    fpclassify ( _Tp __f )
    {
      typedef typename __gnu_cxx :: __promote < _Tp > :: __type __type;
      return __builtin_fpclassify ( FP_NAN, FP_INFINITE, FP_NORMAL,
      FP_SUBNORMAL, FP_ZERO, __type ( __f ) );
    }
# 504 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
template < typename _Tp >
    inline typename __gnu_cxx :: __enable_if < __is_arithmetic < _Tp > :: __value,
        int > :: __type
    isfinite ( _Tp __f )
    {
      typedef typename __gnu_cxx :: __promote < _Tp > :: __type __type;
      return __builtin_isfinite ( __type ( __f ) );
    }
# 513 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
template < typename _Tp >
    inline typename __gnu_cxx :: __enable_if < __is_arithmetic < _Tp > :: __value,
        int > :: __type
    isinf ( _Tp __f )
    {
      typedef typename __gnu_cxx :: __promote < _Tp > :: __type __type;
      return __builtin_isinf ( __type ( __f ) );
    }
# 522 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
template < typename _Tp >
    inline typename __gnu_cxx :: __enable_if < __is_arithmetic < _Tp > :: __value,
        int > :: __type
    isnan ( _Tp __f )
    {
      typedef typename __gnu_cxx :: __promote < _Tp > :: __type __type;
      return __builtin_isnan ( __type ( __f ) );
    }
# 531 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
template < typename _Tp >
    inline typename __gnu_cxx :: __enable_if < __is_arithmetic < _Tp > :: __value,
        int > :: __type
    isnormal ( _Tp __f )
    {
      typedef typename __gnu_cxx :: __promote < _Tp > :: __type __type;
      return __builtin_isnormal ( __type ( __f ) );
    }
# 540 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
template < typename _Tp >
    inline typename __gnu_cxx :: __enable_if < __is_arithmetic < _Tp > :: __value,
        int > :: __type
    signbit ( _Tp __f )
    {
      typedef typename __gnu_cxx :: __promote < _Tp > :: __type __type;
      return __builtin_signbit ( __type ( __f ) );
    }
# 549 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
template < typename _Tp >
    inline typename __gnu_cxx :: __enable_if < __is_arithmetic < _Tp > :: __value,
        int > :: __type
    isgreater ( _Tp __f1, _Tp __f2 )
    {
      typedef typename __gnu_cxx :: __promote < _Tp > :: __type __type;
      return __builtin_isgreater ( __type ( __f1 ), __type ( __f2 ) );
    }
# 558 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
template < typename _Tp >
    inline typename __gnu_cxx :: __enable_if < __is_arithmetic < _Tp > :: __value,
        int > :: __type
    isgreaterequal ( _Tp __f1, _Tp __f2 )
    {
      typedef typename __gnu_cxx :: __promote < _Tp > :: __type __type;
      return __builtin_isgreaterequal ( __type ( __f1 ), __type ( __f2 ) );
    }
# 567 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
template < typename _Tp >
    inline typename __gnu_cxx :: __enable_if < __is_arithmetic < _Tp > :: __value,
        int > :: __type
    isless ( _Tp __f1, _Tp __f2 )
    {
      typedef typename __gnu_cxx :: __promote < _Tp > :: __type __type;
      return __builtin_isless ( __type ( __f1 ), __type ( __f2 ) );
    }
# 576 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
template < typename _Tp >
    inline typename __gnu_cxx :: __enable_if < __is_arithmetic < _Tp > :: __value,
        int > :: __type
    islessequal ( _Tp __f1, _Tp __f2 )
    {
      typedef typename __gnu_cxx :: __promote < _Tp > :: __type __type;
      return __builtin_islessequal ( __type ( __f1 ), __type ( __f2 ) );
    }
# 585 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
template < typename _Tp >
    inline typename __gnu_cxx :: __enable_if < __is_arithmetic < _Tp > :: __value,
        int > :: __type
    islessgreater ( _Tp __f1, _Tp __f2 )
    {
      typedef typename __gnu_cxx :: __promote < _Tp > :: __type __type;
      return __builtin_islessgreater ( __type ( __f1 ), __type ( __f2 ) );
    }
# 594 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
template < typename _Tp >
    inline typename __gnu_cxx :: __enable_if < __is_arithmetic < _Tp > :: __value,
        int > :: __type
    isunordered ( _Tp __f1, _Tp __f2 )
    {
      typedef typename __gnu_cxx :: __promote < _Tp > :: __type __type;
      return __builtin_isunordered ( __type ( __f1 ), __type ( __f2 ) );
    }
# 603 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cmath" 3
}
# 35 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cmath.tcc" 3
namespace std __attribute((__visibility__("default")))
# 49 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstddef" 3
 __attribute((__visibility__("default")))
# 100 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstdlib" 3
 __attribute((__visibility__("default")))
# 199 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstdlib" 3
 __attribute((__visibility__("default"))) {
# 37 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cmath.tcc" 3
template < typename _Tp >
    inline _Tp
    __cmath_power ( _Tp __x, unsigned int __n )
    {
      _Tp __y = __n % 2 ? __x : _Tp ( 1 );

      while ( __n >>= 1 )
        {
          __x = __x * __x;
          if ( __n % 2 )
            __y = __y * __x;
        }

      return __y;
    }
# 53 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/bits/cmath.tcc" 3
}
# 49 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstddef" 3
namespace std __attribute((__visibility__("default")))
# 100 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstdlib" 3
 __attribute((__visibility__("default")))
# 199 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstdlib" 3
 __attribute((__visibility__("default"))) {
# 51 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstddef" 3
using ::ptrdiff_t;
# 52 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstddef" 3
using ::size_t;
# 54 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstddef" 3
}
# 100 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstdlib" 3
namespace std __attribute((__visibility__("default")))
# 199 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstdlib" 3
 __attribute((__visibility__("default"))) {
# 102 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstdlib" 3
using ::div_t;
# 103 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstdlib" 3
using ::ldiv_t;
# 105 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstdlib" 3
using ::abort;
# 106 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstdlib" 3
using ::abs;
# 107 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstdlib" 3
using ::atexit;
# 108 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstdlib" 3
using ::atof;
# 109 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstdlib" 3
using ::atoi;
# 110 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstdlib" 3
using ::atol;
# 111 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstdlib" 3
using ::bsearch;
# 112 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstdlib" 3
using ::calloc;
# 113 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstdlib" 3
using ::div;
# 114 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstdlib" 3
using ::exit;
# 115 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstdlib" 3
using ::free;
# 116 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstdlib" 3
using ::getenv;
# 117 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstdlib" 3
using ::labs;
# 118 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstdlib" 3
using ::ldiv;
# 119 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstdlib" 3
using ::malloc;
# 121 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstdlib" 3
using ::mblen;
# 122 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstdlib" 3
using ::mbstowcs;
# 123 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstdlib" 3
using ::mbtowc;
# 125 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstdlib" 3
using ::qsort;
# 126 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstdlib" 3
using ::rand;
# 127 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstdlib" 3
using ::realloc;
# 128 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstdlib" 3
using ::srand;
# 129 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstdlib" 3
using ::strtod;
# 130 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstdlib" 3
using ::strtol;
# 131 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstdlib" 3
using ::strtoul;
# 132 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstdlib" 3
using ::system;
# 134 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstdlib" 3
using ::wcstombs;
# 135 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstdlib" 3
using ::wctomb;
# 139 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstdlib" 3
inline long abs(long __i) { return labs(__i); }
# 142 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstdlib" 3
inline ldiv_t div(long __i, long __j) { return ldiv(__i, __j); }
# 144 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstdlib" 3
}
# 157 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstdlib" 3
namespace __gnu_cxx __attribute((__visibility__("default"))) {
# 160 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstdlib" 3
using ::lldiv_t;
# 166 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstdlib" 3
using ::_Exit;
# 170 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstdlib" 3
inline long long abs(long long __x) { return (__x >= (0)) ? __x : (-__x); }
# 173 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstdlib" 3
using ::llabs;
# 176 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstdlib" 3
inline lldiv_t div(long long __n, long long __d)
# 177 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstdlib" 3
{ lldiv_t __q; (__q.quot) = (__n / __d); (__q.rem) = (__n % __d); return __q; }
# 179 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstdlib" 3
using ::lldiv;
# 190 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstdlib" 3
using ::atoll;
# 191 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstdlib" 3
using ::strtoll;
# 192 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstdlib" 3
using ::strtoull;
# 194 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstdlib" 3
using ::strtof;
# 195 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstdlib" 3
using ::strtold;
# 197 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstdlib" 3
}
# 199 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstdlib" 3
namespace std __attribute((__visibility__("default"))) {
# 202 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstdlib" 3
using __gnu_cxx::lldiv_t;
# 204 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstdlib" 3
using __gnu_cxx::_Exit;
# 205 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstdlib" 3
using __gnu_cxx::abs;
# 207 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstdlib" 3
using __gnu_cxx::llabs;
# 208 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstdlib" 3
using __gnu_cxx::div;
# 209 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstdlib" 3
using __gnu_cxx::lldiv;
# 211 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstdlib" 3
using __gnu_cxx::atoll;
# 212 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstdlib" 3
using __gnu_cxx::strtof;
# 213 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstdlib" 3
using __gnu_cxx::strtoll;
# 214 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstdlib" 3
using __gnu_cxx::strtoull;
# 215 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstdlib" 3
using __gnu_cxx::strtold;
# 217 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/../../../../include/c++/4.4.6/cstdlib" 3
}
# 85 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" int abs(int) throw();
# 87 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" long labs(long) throw();
# 89 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" long long llabs(long long) throw();
# 91 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" double fabs(double) throw();
# 93 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" float fabsf(float) throw();
# 96 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" int min(int, int);
# 98 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" unsigned umin(unsigned, unsigned);
# 100 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" long long llmin(long long, long long);
# 102 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" unsigned long long ullmin(unsigned long long, unsigned long long);
# 104 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" float fminf(float, float) throw();
# 106 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" double fmin(double, double) throw();
# 109 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" int max(int, int);
# 111 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" unsigned umax(unsigned, unsigned);
# 113 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" long long llmax(long long, long long);
# 115 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" unsigned long long ullmax(unsigned long long, unsigned long long);
# 117 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" float fmaxf(float, float) throw();
# 119 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" double fmax(double, double) throw();
# 122 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" double sin(double) throw();
# 125 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" double cos(double) throw();
# 128 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" void sincos(double, double *, double *) throw();
# 130 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" void sincosf(float, float *, float *) throw();
# 133 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" double tan(double) throw();
# 136 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" double sqrt(double) throw();
# 139 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" double rsqrt(double);
# 141 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" float rsqrtf(float);
# 144 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" double exp2(double) throw();
# 146 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" float exp2f(float) throw();
# 149 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" double exp10(double) throw();
# 151 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" float exp10f(float) throw();
# 154 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" double expm1(double) throw();
# 156 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" float expm1f(float) throw();
# 159 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" double log2(double) throw();
# 161 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" float log2f(float) throw();
# 164 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" double log10(double) throw();
# 167 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" double log(double) throw();
# 170 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" double log1p(double) throw();
# 172 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" float log1pf(float) throw();
# 175 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" double floor(double) throw();
# 178 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" double exp(double) throw();
# 181 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" double cosh(double) throw();
# 184 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" double sinh(double) throw();
# 187 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" double tanh(double) throw();
# 190 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" double acosh(double) throw();
# 192 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" float acoshf(float) throw();
# 195 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" double asinh(double) throw();
# 197 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" float asinhf(float) throw();
# 200 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" double atanh(double) throw();
# 202 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" float atanhf(float) throw();
# 205 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" double ldexp(double, int) throw();
# 207 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" float ldexpf(float, int) throw();
# 210 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" double logb(double) throw();
# 212 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" float logbf(float) throw();
# 215 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" int ilogb(double) throw();
# 217 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" int ilogbf(float) throw();
# 220 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" double scalbn(double, int) throw();
# 222 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" float scalbnf(float, int) throw();
# 225 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" double scalbln(double, long) throw();
# 227 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" float scalblnf(float, long) throw();
# 230 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" double frexp(double, int *) throw();
# 232 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" float frexpf(float, int *) throw();
# 235 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" double round(double) throw();
# 237 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" float roundf(float) throw();
# 240 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" long lround(double) throw();
# 242 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" long lroundf(float) throw();
# 245 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" long long llround(double) throw();
# 247 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" long long llroundf(float) throw();
# 250 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" double rint(double) throw();
# 252 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" float rintf(float) throw();
# 255 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" long lrint(double) throw();
# 257 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" long lrintf(float) throw();
# 260 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" long long llrint(double) throw();
# 262 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" long long llrintf(float) throw();
# 265 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" double nearbyint(double) throw();
# 267 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" float nearbyintf(float) throw();
# 270 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" double ceil(double) throw();
# 273 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" double trunc(double) throw();
# 275 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" float truncf(float) throw();
# 278 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" double fdim(double, double) throw();
# 280 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" float fdimf(float, float) throw();
# 283 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" double atan2(double, double) throw();
# 286 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" double atan(double) throw();
# 289 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" double asin(double) throw();
# 292 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" double acos(double) throw();
# 296 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" double hypot(double, double) throw();
# 302 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" float hypotf(float, float) throw();
# 305 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" double cbrt(double) throw();
# 307 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" float cbrtf(float) throw();
# 310 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" double rcbrt(double);
# 312 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" float rcbrtf(float);
# 315 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" double sinpi(double);
# 317 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" float sinpif(float);
# 320 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" double cospi(double);
# 322 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" float cospif(float);
# 325 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" double pow(double, double) throw();
# 328 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" double modf(double, double *) throw();
# 331 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" double fmod(double, double) throw();
# 334 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" double remainder(double, double) throw();
# 336 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" float remainderf(float, float) throw();
# 339 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" double remquo(double, double, int *) throw();
# 341 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" float remquof(float, float, int *) throw();
# 344 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" double erf(double) throw();
# 346 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" float erff(float) throw();
# 349 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" double erfinv(double);
# 351 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" float erfinvf(float);
# 354 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" double erfc(double) throw();
# 356 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" float erfcf(float) throw();
# 359 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" double erfcinv(double);
# 361 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" float erfcinvf(float);
# 364 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" double lgamma(double) throw();
# 366 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" float lgammaf(float) throw();
# 369 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" double tgamma(double) throw();
# 371 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" float tgammaf(float) throw();
# 374 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" double copysign(double, double) throw();
# 376 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" float copysignf(float, float) throw();
# 379 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" double nextafter(double, double) throw();
# 381 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" float nextafterf(float, float) throw();
# 384 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" double nan(const char *) throw();
# 386 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" float nanf(const char *) throw();
# 389 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" int __isinf(double) throw();
# 391 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" int __isinff(float) throw();
# 394 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" int __isnan(double) throw();
# 397 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" int __isnanf(float) throw();
# 411 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" int __finite(double) throw();
# 414 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" int __finitef(float) throw();
# 418 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" int __signbit(double) throw();
# 423 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" int __signbitf(float) throw();
# 426 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" double fma(double, double, double) throw();
# 428 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" float fmaf(float, float, float) throw();
# 436 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" int __signbitl(long double) throw();
# 438 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" int __isinfl(long double) throw();
# 440 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" int __isnanl(long double) throw();
# 450 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" int __finitel(long double) throw();
# 516 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" float acosf(float) throw();
# 519 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" float asinf(float) throw();
# 522 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" float atanf(float) throw();
# 525 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" float atan2f(float, float) throw();
# 528 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" float cosf(float) throw();
# 531 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" float sinf(float) throw();
# 534 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" float tanf(float) throw();
# 537 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" float coshf(float) throw();
# 540 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" float sinhf(float) throw();
# 543 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" float tanhf(float) throw();
# 546 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" float expf(float) throw();
# 549 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" float logf(float) throw();
# 552 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" float log10f(float) throw();
# 555 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" float modff(float, float *) throw();
# 558 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" float powf(float, float) throw();
# 561 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" float sqrtf(float) throw();
# 564 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" float ceilf(float) throw();
# 567 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" float floorf(float) throw();
# 570 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern "C" float fmodf(float, float) throw();
# 605 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
namespace __gnu_cxx {
# 607 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern inline long long abs(long long);
# 608 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
}
# 610 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
namespace std {
# 612 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
template< class T> extern inline T __pow_helper(T, int);
# 613 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
template< class T> extern inline T __cmath_power(T, unsigned);
# 614 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
}
# 616 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
using std::abs;
# 617 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
using std::fabs;
# 618 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
using std::ceil;
# 619 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
using std::floor;
# 620 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
using std::sqrt;
# 621 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
using std::pow;
# 622 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
using std::log;
# 623 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
using std::log10;
# 624 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
using std::fmod;
# 625 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
using std::modf;
# 626 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
using std::exp;
# 627 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
using std::frexp;
# 628 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
using std::ldexp;
# 629 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
using std::asin;
# 630 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
using std::sin;
# 631 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
using std::sinh;
# 632 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
using std::acos;
# 633 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
using std::cos;
# 634 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
using std::cosh;
# 635 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
using std::atan;
# 636 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
using std::atan2;
# 637 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
using std::tan;
# 638 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
using std::tanh;
# 695 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
namespace std {
# 698 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern inline long abs(long);
# 699 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern inline float abs(float);
# 700 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern inline double abs(double);
# 701 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern inline float fabs(float);
# 702 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern inline float ceil(float);
# 703 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern inline float floor(float);
# 704 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern inline float sqrt(float);
# 705 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern inline float pow(float, float);
# 706 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern inline float pow(float, int);
# 707 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern inline double pow(double, int);
# 708 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern inline float log(float);
# 709 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern inline float log10(float);
# 710 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern inline float fmod(float, float);
# 711 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern inline float modf(float, float *);
# 712 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern inline float exp(float);
# 713 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern inline float frexp(float, int *);
# 714 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern inline float ldexp(float, int);
# 715 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern inline float asin(float);
# 716 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern inline float sin(float);
# 717 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern inline float sinh(float);
# 718 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern inline float acos(float);
# 719 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern inline float cos(float);
# 720 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern inline float cosh(float);
# 721 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern inline float atan(float);
# 722 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern inline float atan2(float, float);
# 723 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern inline float tan(float);
# 724 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
extern inline float tanh(float);
# 727 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
}
# 730 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
static inline float logb(float a)
# 731 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
{
# 732 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
return logbf(a);
# 733 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
}
# 735 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
static inline int ilogb(float a)
# 736 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
{
# 737 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
return ilogbf(a);
# 738 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
}
# 740 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
static inline float scalbn(float a, int b)
# 741 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
{
# 742 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
return scalbnf(a, b);
# 743 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
}
# 745 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
static inline float scalbln(float a, long b)
# 746 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
{
# 747 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
return scalblnf(a, b);
# 748 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
}
# 750 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
static inline float exp2(float a)
# 751 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
{
# 752 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
return exp2f(a);
# 753 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
}
# 755 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
static inline float exp10(float a)
# 756 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
{
# 757 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
return exp10f(a);
# 758 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
}
# 760 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
static inline float expm1(float a)
# 761 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
{
# 762 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
return expm1f(a);
# 763 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
}
# 765 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
static inline float log2(float a)
# 766 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
{
# 767 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
return log2f(a);
# 768 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
}
# 770 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
static inline float log1p(float a)
# 771 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
{
# 772 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
return log1pf(a);
# 773 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
}
# 775 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
static inline float rsqrt(float a)
# 776 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
{
# 777 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
return rsqrtf(a);
# 778 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
}
# 780 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
static inline float acosh(float a)
# 781 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
{
# 782 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
return acoshf(a);
# 783 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
}
# 785 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
static inline float asinh(float a)
# 786 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
{
# 787 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
return asinhf(a);
# 788 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
}
# 790 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
static inline float atanh(float a)
# 791 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
{
# 792 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
return atanhf(a);
# 793 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
}
# 795 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
static inline float hypot(float a, float b)
# 796 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
{
# 797 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
return hypotf(a, b);
# 798 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
}
# 800 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
static inline float cbrt(float a)
# 801 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
{
# 802 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
return cbrtf(a);
# 803 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
}
# 805 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
static inline float rcbrt(float a)
# 806 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
{
# 807 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
return rcbrtf(a);
# 808 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
}
# 810 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
static inline float sinpi(float a)
# 811 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
{
# 812 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
return sinpif(a);
# 813 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
}
# 815 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
static inline float cospi(float a)
# 816 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
{
# 817 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
return cospif(a);
# 818 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
}
# 820 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
static inline void sincos(float a, float *sptr, float *cptr)
# 821 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
{
# 822 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
sincosf(a, sptr, cptr);
# 823 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
}
# 825 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
static inline float erf(float a)
# 826 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
{
# 827 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
return erff(a);
# 828 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
}
# 830 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
static inline float erfinv(float a)
# 831 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
{
# 832 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
return erfinvf(a);
# 833 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
}
# 835 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
static inline float erfc(float a)
# 836 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
{
# 837 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
return erfcf(a);
# 838 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
}
# 840 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
static inline float erfcinv(float a)
# 841 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
{
# 842 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
return erfcinvf(a);
# 843 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
}
# 845 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
static inline float lgamma(float a)
# 846 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
{
# 847 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
return lgammaf(a);
# 848 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
}
# 850 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
static inline float tgamma(float a)
# 851 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
{
# 852 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
return tgammaf(a);
# 853 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
}
# 855 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
static inline float copysign(float a, float b)
# 856 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
{
# 857 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
return copysignf(a, b);
# 858 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
}
# 860 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
static inline double copysign(double a, float b)
# 861 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
{
# 862 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
return copysign(a, (double)b);
# 863 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
}
# 865 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
static inline float copysign(float a, double b)
# 866 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
{
# 867 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
return copysignf(a, (float)b);
# 868 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
}
# 870 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
static inline float nextafter(float a, float b)
# 871 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
{
# 872 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
return nextafterf(a, b);
# 873 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
}
# 875 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
static inline float remainder(float a, float b)
# 876 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
{
# 877 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
return remainderf(a, b);
# 878 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
}
# 880 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
static inline float remquo(float a, float b, int *quo)
# 881 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
{
# 882 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
return remquof(a, b, quo);
# 883 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
}
# 885 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
static inline float round(float a)
# 886 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
{
# 887 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
return roundf(a);
# 888 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
}
# 890 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
static inline long lround(float a)
# 891 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
{
# 892 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
return lroundf(a);
# 893 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
}
# 895 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
static inline long long llround(float a)
# 896 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
{
# 897 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
return llroundf(a);
# 898 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
}
# 900 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
static inline float trunc(float a)
# 901 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
{
# 902 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
return truncf(a);
# 903 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
}
# 905 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
static inline float rint(float a)
# 906 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
{
# 907 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
return rintf(a);
# 908 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
}
# 910 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
static inline long lrint(float a)
# 911 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
{
# 912 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
return lrintf(a);
# 913 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
}
# 915 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
static inline long long llrint(float a)
# 916 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
{
# 917 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
return llrintf(a);
# 918 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
}
# 920 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
static inline float nearbyint(float a)
# 921 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
{
# 922 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
return nearbyintf(a);
# 923 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
}
# 925 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
static inline float fdim(float a, float b)
# 926 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
{
# 927 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
return fdimf(a, b);
# 928 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
}
# 930 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
static inline float fma(float a, float b, float c)
# 931 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
{
# 932 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
return fmaf(a, b, c);
# 933 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
}
# 935 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
static inline float fmax(float a, float b)
# 936 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
{
# 937 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
return fmaxf(a, b);
# 938 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
}
# 940 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
static inline float fmin(float a, float b)
# 941 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
{
# 942 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
return fminf(a, b);
# 943 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
}
# 945 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
static inline unsigned min(unsigned a, unsigned b)
# 946 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
{
# 947 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
return umin(a, b);
# 948 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
}
# 950 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
static inline unsigned min(int a, unsigned b)
# 951 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
{
# 952 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
return umin((unsigned)a, b);
# 953 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
}
# 955 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
static inline unsigned min(unsigned a, int b)
# 956 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
{
# 957 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
return umin(a, (unsigned)b);
# 958 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
}
# 960 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
static inline long long min(long long a, long long b)
# 961 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
{
# 962 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
return llmin(a, b);
# 963 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
}
# 965 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
static inline unsigned long long min(unsigned long long a, unsigned long long b)
# 966 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
{
# 967 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
return ullmin(a, b);
# 968 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
}
# 970 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
static inline unsigned long long min(long long a, unsigned long long b)
# 971 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
{
# 972 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
return ullmin((unsigned long long)a, b);
# 973 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
}
# 975 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
static inline unsigned long long min(unsigned long long a, long long b)
# 976 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
{
# 977 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
return ullmin(a, (unsigned long long)b);
# 978 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
}
# 980 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
static inline float min(float a, float b)
# 981 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
{
# 982 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
return fminf(a, b);
# 983 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
}
# 985 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
static inline double min(double a, double b)
# 986 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
{
# 987 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
return fmin(a, b);
# 988 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
}
# 990 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
static inline double min(float a, double b)
# 991 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
{
# 992 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
return fmin((double)a, b);
# 993 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
}
# 995 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
static inline double min(double a, float b)
# 996 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
{
# 997 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
return fmin(a, (double)b);
# 998 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
}
# 1000 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
static inline unsigned max(unsigned a, unsigned b)
# 1001 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
{
# 1002 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
return umax(a, b);
# 1003 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
}
# 1005 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
static inline unsigned max(int a, unsigned b)
# 1006 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
{
# 1007 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
return umax((unsigned)a, b);
# 1008 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
}
# 1010 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
static inline unsigned max(unsigned a, int b)
# 1011 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
{
# 1012 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
return umax(a, (unsigned)b);
# 1013 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
}
# 1015 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
static inline long long max(long long a, long long b)
# 1016 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
{
# 1017 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
return llmax(a, b);
# 1018 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
}
# 1020 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
static inline unsigned long long max(unsigned long long a, unsigned long long b)
# 1021 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
{
# 1022 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
return ullmax(a, b);
# 1023 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
}
# 1025 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
static inline unsigned long long max(long long a, unsigned long long b)
# 1026 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
{
# 1027 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
return ullmax((unsigned long long)a, b);
# 1028 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
}
# 1030 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
static inline unsigned long long max(unsigned long long a, long long b)
# 1031 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
{
# 1032 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
return ullmax(a, (unsigned long long)b);
# 1033 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
}
# 1035 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
static inline float max(float a, float b)
# 1036 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
{
# 1037 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
return fmaxf(a, b);
# 1038 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
}
# 1040 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
static inline double max(double a, double b)
# 1041 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
{
# 1042 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
return fmax(a, b);
# 1043 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
}
# 1045 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
static inline double max(float a, double b)
# 1046 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
{
# 1047 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
return fmax((double)a, b);
# 1048 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
}
# 1050 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
static inline double max(double a, float b)
# 1051 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
{
# 1052 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
return fmax(a, (double)b);
# 1053 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h"
}
# 74 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_surface_types.h"
template< class T, int dim = 1>
# 75 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_surface_types.h"
struct surface : public surfaceReference {
# 77 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_surface_types.h"
surface()
# 78 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_surface_types.h"
{
# 79 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_surface_types.h"
(channelDesc) = cudaCreateChannelDesc< T> ();
# 80 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_surface_types.h"
}
# 82 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_surface_types.h"
surface(cudaChannelFormatDesc desc)
# 83 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_surface_types.h"
{
# 84 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_surface_types.h"
(channelDesc) = desc;
# 85 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_surface_types.h"
}
# 86 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_surface_types.h"
};
# 89 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_surface_types.h"
template< int dim>
# 90 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_surface_types.h"
struct surface< void, dim> : public surfaceReference {
# 92 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_surface_types.h"
surface()
# 93 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_surface_types.h"
{
# 94 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_surface_types.h"
(channelDesc) = cudaCreateChannelDesc< void> ();
# 95 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_surface_types.h"
}
# 96 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_surface_types.h"
};
# 74 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_texture_types.h"
template< class T, int texType = 1, cudaTextureReadMode mode = cudaReadModeElementType>
# 75 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_texture_types.h"
struct texture : public textureReference {
# 77 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_texture_types.h"
texture(int norm = 0, cudaTextureFilterMode
# 78 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_texture_types.h"
fMode = cudaFilterModePoint, cudaTextureAddressMode
# 79 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_texture_types.h"
aMode = cudaAddressModeClamp)
# 80 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_texture_types.h"
{
# 81 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_texture_types.h"
(normalized) = norm;
# 82 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_texture_types.h"
(filterMode) = fMode;
# 83 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_texture_types.h"
((addressMode)[0]) = aMode;
# 84 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_texture_types.h"
((addressMode)[1]) = aMode;
# 85 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_texture_types.h"
((addressMode)[2]) = aMode;
# 86 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_texture_types.h"
(channelDesc) = cudaCreateChannelDesc< T> ();
# 87 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_texture_types.h"
(sRGB) = 0;
# 88 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_texture_types.h"
}
# 90 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_texture_types.h"
texture(int norm, cudaTextureFilterMode
# 91 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_texture_types.h"
fMode, cudaTextureAddressMode
# 92 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_texture_types.h"
aMode, cudaChannelFormatDesc
# 93 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_texture_types.h"
desc)
# 94 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_texture_types.h"
{
# 95 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_texture_types.h"
(normalized) = norm;
# 96 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_texture_types.h"
(filterMode) = fMode;
# 97 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_texture_types.h"
((addressMode)[0]) = aMode;
# 98 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_texture_types.h"
((addressMode)[1]) = aMode;
# 99 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_texture_types.h"
((addressMode)[2]) = aMode;
# 100 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_texture_types.h"
(channelDesc) = desc;
# 101 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_texture_types.h"
(sRGB) = 0;
# 102 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_texture_types.h"
}
# 103 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_texture_types.h"
};
# 338 "/home/hangzhang/local/cuda/4.0/bin/../include/device_functions.h"
__attribute__((unused)) static inline int mulhi(int a, int b)
# 339 "/home/hangzhang/local/cuda/4.0/bin/../include/device_functions.h"
{int volatile ___ = 1;(void)a;(void)b;
# 341 "/home/hangzhang/local/cuda/4.0/bin/../include/device_functions.h"
exit(___);}
# 343 "/home/hangzhang/local/cuda/4.0/bin/../include/device_functions.h"
__attribute__((unused)) static inline unsigned mulhi(unsigned a, unsigned b)
# 344 "/home/hangzhang/local/cuda/4.0/bin/../include/device_functions.h"
{int volatile ___ = 1;(void)a;(void)b;
# 346 "/home/hangzhang/local/cuda/4.0/bin/../include/device_functions.h"
exit(___);}
# 348 "/home/hangzhang/local/cuda/4.0/bin/../include/device_functions.h"
__attribute__((unused)) static inline unsigned mulhi(int a, unsigned b)
# 349 "/home/hangzhang/local/cuda/4.0/bin/../include/device_functions.h"
{int volatile ___ = 1;(void)a;(void)b;
# 351 "/home/hangzhang/local/cuda/4.0/bin/../include/device_functions.h"
exit(___);}
# 353 "/home/hangzhang/local/cuda/4.0/bin/../include/device_functions.h"
__attribute__((unused)) static inline unsigned mulhi(unsigned a, int b)
# 354 "/home/hangzhang/local/cuda/4.0/bin/../include/device_functions.h"
{int volatile ___ = 1;(void)a;(void)b;
# 356 "/home/hangzhang/local/cuda/4.0/bin/../include/device_functions.h"
exit(___);}
# 358 "/home/hangzhang/local/cuda/4.0/bin/../include/device_functions.h"
__attribute__((unused)) static inline long long mul64hi(long long a, long long b)
# 359 "/home/hangzhang/local/cuda/4.0/bin/../include/device_functions.h"
{int volatile ___ = 1;(void)a;(void)b;
# 361 "/home/hangzhang/local/cuda/4.0/bin/../include/device_functions.h"
exit(___);}
# 363 "/home/hangzhang/local/cuda/4.0/bin/../include/device_functions.h"
__attribute__((unused)) static inline unsigned long long mul64hi(unsigned long long a, unsigned long long b)
# 364 "/home/hangzhang/local/cuda/4.0/bin/../include/device_functions.h"
{int volatile ___ = 1;(void)a;(void)b;
# 366 "/home/hangzhang/local/cuda/4.0/bin/../include/device_functions.h"
exit(___);}
# 368 "/home/hangzhang/local/cuda/4.0/bin/../include/device_functions.h"
__attribute__((unused)) static inline unsigned long long mul64hi(long long a, unsigned long long b)
# 369 "/home/hangzhang/local/cuda/4.0/bin/../include/device_functions.h"
{int volatile ___ = 1;(void)a;(void)b;
# 371 "/home/hangzhang/local/cuda/4.0/bin/../include/device_functions.h"
exit(___);}
# 373 "/home/hangzhang/local/cuda/4.0/bin/../include/device_functions.h"
__attribute__((unused)) static inline unsigned long long mul64hi(unsigned long long a, long long b)
# 374 "/home/hangzhang/local/cuda/4.0/bin/../include/device_functions.h"
{int volatile ___ = 1;(void)a;(void)b;
# 376 "/home/hangzhang/local/cuda/4.0/bin/../include/device_functions.h"
exit(___);}
# 378 "/home/hangzhang/local/cuda/4.0/bin/../include/device_functions.h"
__attribute__((unused)) static inline int float_as_int(float a)
# 379 "/home/hangzhang/local/cuda/4.0/bin/../include/device_functions.h"
{int volatile ___ = 1;(void)a;
# 381 "/home/hangzhang/local/cuda/4.0/bin/../include/device_functions.h"
exit(___);}
# 383 "/home/hangzhang/local/cuda/4.0/bin/../include/device_functions.h"
__attribute__((unused)) static inline float int_as_float(int a)
# 384 "/home/hangzhang/local/cuda/4.0/bin/../include/device_functions.h"
{int volatile ___ = 1;(void)a;
# 386 "/home/hangzhang/local/cuda/4.0/bin/../include/device_functions.h"
exit(___);}
# 388 "/home/hangzhang/local/cuda/4.0/bin/../include/device_functions.h"
__attribute__((unused)) static inline float saturate(float a)
# 389 "/home/hangzhang/local/cuda/4.0/bin/../include/device_functions.h"
{int volatile ___ = 1;(void)a;
# 391 "/home/hangzhang/local/cuda/4.0/bin/../include/device_functions.h"
exit(___);}
# 393 "/home/hangzhang/local/cuda/4.0/bin/../include/device_functions.h"
__attribute__((unused)) static inline int mul24(int a, int b)
# 394 "/home/hangzhang/local/cuda/4.0/bin/../include/device_functions.h"
{int volatile ___ = 1;(void)a;(void)b;
# 396 "/home/hangzhang/local/cuda/4.0/bin/../include/device_functions.h"
exit(___);}
# 398 "/home/hangzhang/local/cuda/4.0/bin/../include/device_functions.h"
__attribute__((unused)) static inline unsigned umul24(unsigned a, unsigned b)
# 399 "/home/hangzhang/local/cuda/4.0/bin/../include/device_functions.h"
{int volatile ___ = 1;(void)a;(void)b;
# 401 "/home/hangzhang/local/cuda/4.0/bin/../include/device_functions.h"
exit(___);}
# 403 "/home/hangzhang/local/cuda/4.0/bin/../include/device_functions.h"
__attribute__((unused)) static inline void trap()
# 404 "/home/hangzhang/local/cuda/4.0/bin/../include/device_functions.h"
{int volatile ___ = 1;
# 406 "/home/hangzhang/local/cuda/4.0/bin/../include/device_functions.h"
exit(___);}
# 409 "/home/hangzhang/local/cuda/4.0/bin/../include/device_functions.h"
__attribute__((unused)) static inline void brkpt(int c = 0)
# 410 "/home/hangzhang/local/cuda/4.0/bin/../include/device_functions.h"
{int volatile ___ = 1;(void)c;
# 412 "/home/hangzhang/local/cuda/4.0/bin/../include/device_functions.h"
exit(___);}
# 414 "/home/hangzhang/local/cuda/4.0/bin/../include/device_functions.h"
__attribute__((unused)) static inline void syncthreads()
# 415 "/home/hangzhang/local/cuda/4.0/bin/../include/device_functions.h"
{int volatile ___ = 1;
# 417 "/home/hangzhang/local/cuda/4.0/bin/../include/device_functions.h"
exit(___);}
# 419 "/home/hangzhang/local/cuda/4.0/bin/../include/device_functions.h"
__attribute__((unused)) static inline void prof_trigger(int e)
# 420 "/home/hangzhang/local/cuda/4.0/bin/../include/device_functions.h"
{int volatile ___ = 1;(void)e;
# 437 "/home/hangzhang/local/cuda/4.0/bin/../include/device_functions.h"
exit(___);}
# 439 "/home/hangzhang/local/cuda/4.0/bin/../include/device_functions.h"
__attribute__((unused)) static inline void threadfence(bool global = true)
# 440 "/home/hangzhang/local/cuda/4.0/bin/../include/device_functions.h"
{int volatile ___ = 1;(void)global;
# 442 "/home/hangzhang/local/cuda/4.0/bin/../include/device_functions.h"
exit(___);}
# 444 "/home/hangzhang/local/cuda/4.0/bin/../include/device_functions.h"
__attribute__((unused)) static inline int float2int(float a, cudaRoundMode mode = cudaRoundZero)
# 445 "/home/hangzhang/local/cuda/4.0/bin/../include/device_functions.h"
{int volatile ___ = 1;(void)a;(void)mode;
# 450 "/home/hangzhang/local/cuda/4.0/bin/../include/device_functions.h"
exit(___);}
# 452 "/home/hangzhang/local/cuda/4.0/bin/../include/device_functions.h"
__attribute__((unused)) static inline unsigned float2uint(float a, cudaRoundMode mode = cudaRoundZero)
# 453 "/home/hangzhang/local/cuda/4.0/bin/../include/device_functions.h"
{int volatile ___ = 1;(void)a;(void)mode;
# 458 "/home/hangzhang/local/cuda/4.0/bin/../include/device_functions.h"
exit(___);}
# 460 "/home/hangzhang/local/cuda/4.0/bin/../include/device_functions.h"
__attribute__((unused)) static inline float int2float(int a, cudaRoundMode mode = cudaRoundNearest)
# 461 "/home/hangzhang/local/cuda/4.0/bin/../include/device_functions.h"
{int volatile ___ = 1;(void)a;(void)mode;
# 466 "/home/hangzhang/local/cuda/4.0/bin/../include/device_functions.h"
exit(___);}
# 468 "/home/hangzhang/local/cuda/4.0/bin/../include/device_functions.h"
__attribute__((unused)) static inline float uint2float(unsigned a, cudaRoundMode mode = cudaRoundNearest)
# 469 "/home/hangzhang/local/cuda/4.0/bin/../include/device_functions.h"
{int volatile ___ = 1;(void)a;(void)mode;
# 474 "/home/hangzhang/local/cuda/4.0/bin/../include/device_functions.h"
exit(___);}
# 116 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_11_atomic_functions.h"
__attribute__((unused)) static inline int atomicAdd(int *address, int val)
# 117 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_11_atomic_functions.h"
{int volatile ___ = 1;(void)address;(void)val;
# 119 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_11_atomic_functions.h"
exit(___);}
# 121 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_11_atomic_functions.h"
__attribute__((unused)) static inline unsigned atomicAdd(unsigned *address, unsigned val)
# 122 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_11_atomic_functions.h"
{int volatile ___ = 1;(void)address;(void)val;
# 124 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_11_atomic_functions.h"
exit(___);}
# 126 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_11_atomic_functions.h"
__attribute__((unused)) static inline int atomicSub(int *address, int val)
# 127 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_11_atomic_functions.h"
{int volatile ___ = 1;(void)address;(void)val;
# 129 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_11_atomic_functions.h"
exit(___);}
# 131 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_11_atomic_functions.h"
__attribute__((unused)) static inline unsigned atomicSub(unsigned *address, unsigned val)
# 132 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_11_atomic_functions.h"
{int volatile ___ = 1;(void)address;(void)val;
# 134 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_11_atomic_functions.h"
exit(___);}
# 136 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_11_atomic_functions.h"
__attribute__((unused)) static inline int atomicExch(int *address, int val)
# 137 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_11_atomic_functions.h"
{int volatile ___ = 1;(void)address;(void)val;
# 139 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_11_atomic_functions.h"
exit(___);}
# 141 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_11_atomic_functions.h"
__attribute__((unused)) static inline unsigned atomicExch(unsigned *address, unsigned val)
# 142 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_11_atomic_functions.h"
{int volatile ___ = 1;(void)address;(void)val;
# 144 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_11_atomic_functions.h"
exit(___);}
# 146 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_11_atomic_functions.h"
__attribute__((unused)) static inline float atomicExch(float *address, float val)
# 147 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_11_atomic_functions.h"
{int volatile ___ = 1;(void)address;(void)val;
# 149 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_11_atomic_functions.h"
exit(___);}
# 151 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_11_atomic_functions.h"
__attribute__((unused)) static inline int atomicMin(int *address, int val)
# 152 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_11_atomic_functions.h"
{int volatile ___ = 1;(void)address;(void)val;
# 154 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_11_atomic_functions.h"
exit(___);}
# 156 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_11_atomic_functions.h"
__attribute__((unused)) static inline unsigned atomicMin(unsigned *address, unsigned val)
# 157 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_11_atomic_functions.h"
{int volatile ___ = 1;(void)address;(void)val;
# 159 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_11_atomic_functions.h"
exit(___);}
# 161 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_11_atomic_functions.h"
__attribute__((unused)) static inline int atomicMax(int *address, int val)
# 162 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_11_atomic_functions.h"
{int volatile ___ = 1;(void)address;(void)val;
# 164 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_11_atomic_functions.h"
exit(___);}
# 166 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_11_atomic_functions.h"
__attribute__((unused)) static inline unsigned atomicMax(unsigned *address, unsigned val)
# 167 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_11_atomic_functions.h"
{int volatile ___ = 1;(void)address;(void)val;
# 169 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_11_atomic_functions.h"
exit(___);}
# 171 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_11_atomic_functions.h"
__attribute__((unused)) static inline unsigned atomicInc(unsigned *address, unsigned val)
# 172 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_11_atomic_functions.h"
{int volatile ___ = 1;(void)address;(void)val;
# 174 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_11_atomic_functions.h"
exit(___);}
# 176 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_11_atomic_functions.h"
__attribute__((unused)) static inline unsigned atomicDec(unsigned *address, unsigned val)
# 177 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_11_atomic_functions.h"
{int volatile ___ = 1;(void)address;(void)val;
# 179 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_11_atomic_functions.h"
exit(___);}
# 181 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_11_atomic_functions.h"
__attribute__((unused)) static inline int atomicAnd(int *address, int val)
# 182 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_11_atomic_functions.h"
{int volatile ___ = 1;(void)address;(void)val;
# 184 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_11_atomic_functions.h"
exit(___);}
# 186 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_11_atomic_functions.h"
__attribute__((unused)) static inline unsigned atomicAnd(unsigned *address, unsigned val)
# 187 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_11_atomic_functions.h"
{int volatile ___ = 1;(void)address;(void)val;
# 189 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_11_atomic_functions.h"
exit(___);}
# 191 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_11_atomic_functions.h"
__attribute__((unused)) static inline int atomicOr(int *address, int val)
# 192 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_11_atomic_functions.h"
{int volatile ___ = 1;(void)address;(void)val;
# 194 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_11_atomic_functions.h"
exit(___);}
# 196 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_11_atomic_functions.h"
__attribute__((unused)) static inline unsigned atomicOr(unsigned *address, unsigned val)
# 197 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_11_atomic_functions.h"
{int volatile ___ = 1;(void)address;(void)val;
# 199 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_11_atomic_functions.h"
exit(___);}
# 201 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_11_atomic_functions.h"
__attribute__((unused)) static inline int atomicXor(int *address, int val)
# 202 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_11_atomic_functions.h"
{int volatile ___ = 1;(void)address;(void)val;
# 204 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_11_atomic_functions.h"
exit(___);}
# 206 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_11_atomic_functions.h"
__attribute__((unused)) static inline unsigned atomicXor(unsigned *address, unsigned val)
# 207 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_11_atomic_functions.h"
{int volatile ___ = 1;(void)address;(void)val;
# 209 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_11_atomic_functions.h"
exit(___);}
# 211 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_11_atomic_functions.h"
__attribute__((unused)) static inline int atomicCAS(int *address, int compare, int val)
# 212 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_11_atomic_functions.h"
{int volatile ___ = 1;(void)address;(void)compare;(void)val;
# 214 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_11_atomic_functions.h"
exit(___);}
# 216 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_11_atomic_functions.h"
__attribute__((unused)) static inline unsigned atomicCAS(unsigned *address, unsigned compare, unsigned val)
# 217 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_11_atomic_functions.h"
{int volatile ___ = 1;(void)address;(void)compare;(void)val;
# 219 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_11_atomic_functions.h"
exit(___);}
# 89 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_12_atomic_functions.h"
__attribute__((unused)) static inline unsigned long long atomicAdd(unsigned long long *address, unsigned long long val)
# 90 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_12_atomic_functions.h"
{int volatile ___ = 1;(void)address;(void)val;
# 92 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_12_atomic_functions.h"
exit(___);}
# 94 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_12_atomic_functions.h"
__attribute__((unused)) static inline unsigned long long atomicExch(unsigned long long *address, unsigned long long val)
# 95 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_12_atomic_functions.h"
{int volatile ___ = 1;(void)address;(void)val;
# 97 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_12_atomic_functions.h"
exit(___);}
# 99 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_12_atomic_functions.h"
__attribute__((unused)) static inline unsigned long long atomicCAS(unsigned long long *address, unsigned long long compare, unsigned long long val)
# 100 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_12_atomic_functions.h"
{int volatile ___ = 1;(void)address;(void)compare;(void)val;
# 102 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_12_atomic_functions.h"
exit(___);}
# 104 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_12_atomic_functions.h"
__attribute__((unused)) static inline bool any(bool cond)
# 105 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_12_atomic_functions.h"
{int volatile ___ = 1;(void)cond;
# 107 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_12_atomic_functions.h"
exit(___);}
# 109 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_12_atomic_functions.h"
__attribute__((unused)) static inline bool all(bool cond)
# 110 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_12_atomic_functions.h"
{int volatile ___ = 1;(void)cond;
# 112 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_12_atomic_functions.h"
exit(___);}
# 184 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_13_double_functions.h"
__attribute__((unused)) static inline double fma(double a, double b, double c, cudaRoundMode mode)
# 185 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_13_double_functions.h"
{int volatile ___ = 1;(void)a;(void)b;(void)c;(void)mode;
# 190 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_13_double_functions.h"
exit(___);}
# 192 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_13_double_functions.h"
__attribute__((unused)) static inline double dmul(double a, double b, cudaRoundMode mode = cudaRoundNearest)
# 193 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_13_double_functions.h"
{int volatile ___ = 1;(void)a;(void)b;(void)mode;
# 198 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_13_double_functions.h"
exit(___);}
# 200 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_13_double_functions.h"
__attribute__((unused)) static inline double dadd(double a, double b, cudaRoundMode mode = cudaRoundNearest)
# 201 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_13_double_functions.h"
{int volatile ___ = 1;(void)a;(void)b;(void)mode;
# 206 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_13_double_functions.h"
exit(___);}
# 208 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_13_double_functions.h"
__attribute__((unused)) static inline int double2int(double a, cudaRoundMode mode = cudaRoundZero)
# 209 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_13_double_functions.h"
{int volatile ___ = 1;(void)a;(void)mode;
# 214 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_13_double_functions.h"
exit(___);}
# 216 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_13_double_functions.h"
__attribute__((unused)) static inline unsigned double2uint(double a, cudaRoundMode mode = cudaRoundZero)
# 217 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_13_double_functions.h"
{int volatile ___ = 1;(void)a;(void)mode;
# 222 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_13_double_functions.h"
exit(___);}
# 224 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_13_double_functions.h"
__attribute__((unused)) static inline long long double2ll(double a, cudaRoundMode mode = cudaRoundZero)
# 225 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_13_double_functions.h"
{int volatile ___ = 1;(void)a;(void)mode;
# 230 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_13_double_functions.h"
exit(___);}
# 232 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_13_double_functions.h"
__attribute__((unused)) static inline unsigned long long double2ull(double a, cudaRoundMode mode = cudaRoundZero)
# 233 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_13_double_functions.h"
{int volatile ___ = 1;(void)a;(void)mode;
# 238 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_13_double_functions.h"
exit(___);}
# 240 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_13_double_functions.h"
__attribute__((unused)) static inline double ll2double(long long a, cudaRoundMode mode = cudaRoundNearest)
# 241 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_13_double_functions.h"
{int volatile ___ = 1;(void)a;(void)mode;
# 246 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_13_double_functions.h"
exit(___);}
# 248 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_13_double_functions.h"
__attribute__((unused)) static inline double ull2double(unsigned long long a, cudaRoundMode mode = cudaRoundNearest)
# 249 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_13_double_functions.h"
{int volatile ___ = 1;(void)a;(void)mode;
# 254 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_13_double_functions.h"
exit(___);}
# 256 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_13_double_functions.h"
__attribute__((unused)) static inline double int2double(int a, cudaRoundMode mode = cudaRoundNearest)
# 257 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_13_double_functions.h"
{int volatile ___ = 1;(void)a;(void)mode;
# 259 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_13_double_functions.h"
exit(___);}
# 261 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_13_double_functions.h"
__attribute__((unused)) static inline double uint2double(unsigned a, cudaRoundMode mode = cudaRoundNearest)
# 262 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_13_double_functions.h"
{int volatile ___ = 1;(void)a;(void)mode;
# 264 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_13_double_functions.h"
exit(___);}
# 266 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_13_double_functions.h"
__attribute__((unused)) static inline double float2double(float a, cudaRoundMode mode = cudaRoundNearest)
# 267 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_13_double_functions.h"
{int volatile ___ = 1;(void)a;(void)mode;
# 269 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_13_double_functions.h"
exit(___);}
# 80 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_20_atomic_functions.h"
__attribute__((unused)) static inline float atomicAdd(float *address, float val)
# 81 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_20_atomic_functions.h"
{int volatile ___ = 1;(void)address;(void)val;
# 83 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_20_atomic_functions.h"
exit(___);}
# 138 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_20_intrinsics.h"
__attribute__((unused)) static inline unsigned ballot(bool pred)
# 139 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_20_intrinsics.h"
{int volatile ___ = 1;(void)pred;
# 141 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_20_intrinsics.h"
exit(___);}
# 143 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_20_intrinsics.h"
__attribute__((unused)) static inline int syncthreads_count(bool pred)
# 144 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_20_intrinsics.h"
{int volatile ___ = 1;(void)pred;
# 146 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_20_intrinsics.h"
exit(___);}
# 148 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_20_intrinsics.h"
__attribute__((unused)) static inline bool syncthreads_and(bool pred)
# 149 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_20_intrinsics.h"
{int volatile ___ = 1;(void)pred;
# 151 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_20_intrinsics.h"
exit(___);}
# 153 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_20_intrinsics.h"
__attribute__((unused)) static inline bool syncthreads_or(bool pred)
# 154 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_20_intrinsics.h"
{int volatile ___ = 1;(void)pred;
# 156 "/home/hangzhang/local/cuda/4.0/bin/../include/sm_20_intrinsics.h"
exit(___);}
# 111 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
template< class T> __attribute__((unused)) static inline void
# 112 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
surf1Dread(T *res, surface< void, 1> surf, int x, int s, cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap)
# 113 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)res;(void)surf;(void)x;(void)s;(void)mode;
# 120 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 122 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
template< class T> __attribute__((unused)) static inline T
# 123 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
surf1Dread(surface< void, 1> surf, int x, cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap)
# 124 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)surf;(void)x;(void)mode;
# 130 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 132 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
template< class T> __attribute__((unused)) static inline void
# 133 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
surf1Dread(T *res, surface< void, 1> surf, int x, cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap)
# 134 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)res;(void)surf;(void)x;(void)mode;
# 136 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 139 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
template<> __attribute__((unused)) inline char surf1Dread(surface< void, 1> surf, int x, cudaSurfaceBoundaryMode mode)
# 140 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)surf;(void)x;(void)mode;
# 142 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 145 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
template<> __attribute__((unused)) inline signed char surf1Dread(surface< void, 1> surf, int x, cudaSurfaceBoundaryMode mode)
# 146 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)surf;(void)x;(void)mode;
# 148 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 151 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
template<> __attribute__((unused)) inline unsigned char surf1Dread(surface< void, 1> surf, int x, cudaSurfaceBoundaryMode mode)
# 152 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)surf;(void)x;(void)mode;
# 154 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 157 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
template<> __attribute__((unused)) inline char1 surf1Dread(surface< void, 1> surf, int x, cudaSurfaceBoundaryMode mode)
# 158 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)surf;(void)x;(void)mode;
# 160 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 163 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
template<> __attribute__((unused)) inline uchar1 surf1Dread(surface< void, 1> surf, int x, cudaSurfaceBoundaryMode mode)
# 164 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)surf;(void)x;(void)mode;
# 166 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 169 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
template<> __attribute__((unused)) inline char2 surf1Dread(surface< void, 1> surf, int x, cudaSurfaceBoundaryMode mode)
# 170 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)surf;(void)x;(void)mode;
# 174 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 177 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
template<> __attribute__((unused)) inline uchar2 surf1Dread(surface< void, 1> surf, int x, cudaSurfaceBoundaryMode mode)
# 178 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)surf;(void)x;(void)mode;
# 180 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 183 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
template<> __attribute__((unused)) inline char4 surf1Dread(surface< void, 1> surf, int x, cudaSurfaceBoundaryMode mode)
# 184 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)surf;(void)x;(void)mode;
# 188 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 191 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
template<> __attribute__((unused)) inline uchar4 surf1Dread(surface< void, 1> surf, int x, cudaSurfaceBoundaryMode mode)
# 192 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)surf;(void)x;(void)mode;
# 194 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 197 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
template<> __attribute__((unused)) inline short surf1Dread(surface< void, 1> surf, int x, cudaSurfaceBoundaryMode mode)
# 198 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)surf;(void)x;(void)mode;
# 200 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 203 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
template<> __attribute__((unused)) inline unsigned short surf1Dread(surface< void, 1> surf, int x, cudaSurfaceBoundaryMode mode)
# 204 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)surf;(void)x;(void)mode;
# 206 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 209 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
template<> __attribute__((unused)) inline short1 surf1Dread(surface< void, 1> surf, int x, cudaSurfaceBoundaryMode mode)
# 210 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)surf;(void)x;(void)mode;
# 212 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 215 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
template<> __attribute__((unused)) inline ushort1 surf1Dread(surface< void, 1> surf, int x, cudaSurfaceBoundaryMode mode)
# 216 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)surf;(void)x;(void)mode;
# 218 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 221 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
template<> __attribute__((unused)) inline short2 surf1Dread(surface< void, 1> surf, int x, cudaSurfaceBoundaryMode mode)
# 222 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)surf;(void)x;(void)mode;
# 226 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 229 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
template<> __attribute__((unused)) inline ushort2 surf1Dread(surface< void, 1> surf, int x, cudaSurfaceBoundaryMode mode)
# 230 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)surf;(void)x;(void)mode;
# 232 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 235 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
template<> __attribute__((unused)) inline short4 surf1Dread(surface< void, 1> surf, int x, cudaSurfaceBoundaryMode mode)
# 236 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)surf;(void)x;(void)mode;
# 240 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 243 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
template<> __attribute__((unused)) inline ushort4 surf1Dread(surface< void, 1> surf, int x, cudaSurfaceBoundaryMode mode)
# 244 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)surf;(void)x;(void)mode;
# 246 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 249 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
template<> __attribute__((unused)) inline int surf1Dread(surface< void, 1> surf, int x, cudaSurfaceBoundaryMode mode)
# 250 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)surf;(void)x;(void)mode;
# 252 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 255 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
template<> __attribute__((unused)) inline unsigned surf1Dread(surface< void, 1> surf, int x, cudaSurfaceBoundaryMode mode)
# 256 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)surf;(void)x;(void)mode;
# 258 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 261 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
template<> __attribute__((unused)) inline int1 surf1Dread(surface< void, 1> surf, int x, cudaSurfaceBoundaryMode mode)
# 262 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)surf;(void)x;(void)mode;
# 264 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 267 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
template<> __attribute__((unused)) inline uint1 surf1Dread(surface< void, 1> surf, int x, cudaSurfaceBoundaryMode mode)
# 268 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)surf;(void)x;(void)mode;
# 270 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 273 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
template<> __attribute__((unused)) inline int2 surf1Dread(surface< void, 1> surf, int x, cudaSurfaceBoundaryMode mode)
# 274 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)surf;(void)x;(void)mode;
# 278 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 281 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
template<> __attribute__((unused)) inline uint2 surf1Dread(surface< void, 1> surf, int x, cudaSurfaceBoundaryMode mode)
# 282 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)surf;(void)x;(void)mode;
# 284 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 287 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
template<> __attribute__((unused)) inline int4 surf1Dread(surface< void, 1> surf, int x, cudaSurfaceBoundaryMode mode)
# 288 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)surf;(void)x;(void)mode;
# 292 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 295 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
template<> __attribute__((unused)) inline uint4 surf1Dread(surface< void, 1> surf, int x, cudaSurfaceBoundaryMode mode)
# 296 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)surf;(void)x;(void)mode;
# 298 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 301 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
template<> __attribute__((unused)) inline long long surf1Dread(surface< void, 1> surf, int x, cudaSurfaceBoundaryMode mode)
# 302 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)surf;(void)x;(void)mode;
# 304 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 307 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
template<> __attribute__((unused)) inline unsigned long long surf1Dread(surface< void, 1> surf, int x, cudaSurfaceBoundaryMode mode)
# 308 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)surf;(void)x;(void)mode;
# 310 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 313 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
template<> __attribute__((unused)) inline longlong1 surf1Dread(surface< void, 1> surf, int x, cudaSurfaceBoundaryMode mode)
# 314 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)surf;(void)x;(void)mode;
# 316 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 319 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
template<> __attribute__((unused)) inline ulonglong1 surf1Dread(surface< void, 1> surf, int x, cudaSurfaceBoundaryMode mode)
# 320 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)surf;(void)x;(void)mode;
# 322 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 325 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
template<> __attribute__((unused)) inline longlong2 surf1Dread(surface< void, 1> surf, int x, cudaSurfaceBoundaryMode mode)
# 326 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)surf;(void)x;(void)mode;
# 330 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 333 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
template<> __attribute__((unused)) inline ulonglong2 surf1Dread(surface< void, 1> surf, int x, cudaSurfaceBoundaryMode mode)
# 334 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)surf;(void)x;(void)mode;
# 336 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 399 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
template<> __attribute__((unused)) inline float surf1Dread(surface< void, 1> surf, int x, cudaSurfaceBoundaryMode mode)
# 400 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)surf;(void)x;(void)mode;
# 402 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 405 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
template<> __attribute__((unused)) inline float1 surf1Dread(surface< void, 1> surf, int x, cudaSurfaceBoundaryMode mode)
# 406 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)surf;(void)x;(void)mode;
# 408 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 411 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
template<> __attribute__((unused)) inline float2 surf1Dread(surface< void, 1> surf, int x, cudaSurfaceBoundaryMode mode)
# 412 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)surf;(void)x;(void)mode;
# 416 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 419 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
template<> __attribute__((unused)) inline float4 surf1Dread(surface< void, 1> surf, int x, cudaSurfaceBoundaryMode mode)
# 420 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)surf;(void)x;(void)mode;
# 424 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 471 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
template< class T> __attribute__((unused)) static inline void
# 472 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
surf2Dread(T *res, surface< void, 2> surf, int x, int y, int s, cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap)
# 473 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)res;(void)surf;(void)x;(void)y;(void)s;(void)mode;
# 480 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 482 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
template< class T> __attribute__((unused)) static inline T
# 483 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
surf2Dread(surface< void, 2> surf, int x, int y, cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap)
# 484 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)surf;(void)x;(void)y;(void)mode;
# 490 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 492 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
template< class T> __attribute__((unused)) static inline void
# 493 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
surf2Dread(T *res, surface< void, 2> surf, int x, int y, cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap)
# 494 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)res;(void)surf;(void)x;(void)y;(void)mode;
# 496 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 499 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
template<> __attribute__((unused)) inline char surf2Dread(surface< void, 2> surf, int x, int y, cudaSurfaceBoundaryMode mode)
# 500 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)surf;(void)x;(void)y;(void)mode;
# 502 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 505 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
template<> __attribute__((unused)) inline signed char surf2Dread(surface< void, 2> surf, int x, int y, cudaSurfaceBoundaryMode mode)
# 506 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)surf;(void)x;(void)y;(void)mode;
# 508 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 511 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
template<> __attribute__((unused)) inline unsigned char surf2Dread(surface< void, 2> surf, int x, int y, cudaSurfaceBoundaryMode mode)
# 512 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)surf;(void)x;(void)y;(void)mode;
# 514 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 517 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
template<> __attribute__((unused)) inline char1 surf2Dread(surface< void, 2> surf, int x, int y, cudaSurfaceBoundaryMode mode)
# 518 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)surf;(void)x;(void)y;(void)mode;
# 520 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 523 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
template<> __attribute__((unused)) inline uchar1 surf2Dread(surface< void, 2> surf, int x, int y, cudaSurfaceBoundaryMode mode)
# 524 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)surf;(void)x;(void)y;(void)mode;
# 526 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 529 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
template<> __attribute__((unused)) inline char2 surf2Dread(surface< void, 2> surf, int x, int y, cudaSurfaceBoundaryMode mode)
# 530 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)surf;(void)x;(void)y;(void)mode;
# 534 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 537 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
template<> __attribute__((unused)) inline uchar2 surf2Dread(surface< void, 2> surf, int x, int y, cudaSurfaceBoundaryMode mode)
# 538 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)surf;(void)x;(void)y;(void)mode;
# 540 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 543 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
template<> __attribute__((unused)) inline char4 surf2Dread(surface< void, 2> surf, int x, int y, cudaSurfaceBoundaryMode mode)
# 544 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)surf;(void)x;(void)y;(void)mode;
# 548 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 551 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
template<> __attribute__((unused)) inline uchar4 surf2Dread(surface< void, 2> surf, int x, int y, cudaSurfaceBoundaryMode mode)
# 552 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)surf;(void)x;(void)y;(void)mode;
# 554 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 557 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
template<> __attribute__((unused)) inline short surf2Dread(surface< void, 2> surf, int x, int y, cudaSurfaceBoundaryMode mode)
# 558 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)surf;(void)x;(void)y;(void)mode;
# 560 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 563 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
template<> __attribute__((unused)) inline unsigned short surf2Dread(surface< void, 2> surf, int x, int y, cudaSurfaceBoundaryMode mode)
# 564 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)surf;(void)x;(void)y;(void)mode;
# 566 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 569 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
template<> __attribute__((unused)) inline short1 surf2Dread(surface< void, 2> surf, int x, int y, cudaSurfaceBoundaryMode mode)
# 570 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)surf;(void)x;(void)y;(void)mode;
# 572 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 575 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
template<> __attribute__((unused)) inline ushort1 surf2Dread(surface< void, 2> surf, int x, int y, cudaSurfaceBoundaryMode mode)
# 576 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)surf;(void)x;(void)y;(void)mode;
# 578 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 581 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
template<> __attribute__((unused)) inline short2 surf2Dread(surface< void, 2> surf, int x, int y, cudaSurfaceBoundaryMode mode)
# 582 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)surf;(void)x;(void)y;(void)mode;
# 586 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 589 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
template<> __attribute__((unused)) inline ushort2 surf2Dread(surface< void, 2> surf, int x, int y, cudaSurfaceBoundaryMode mode)
# 590 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)surf;(void)x;(void)y;(void)mode;
# 592 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 595 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
template<> __attribute__((unused)) inline short4 surf2Dread(surface< void, 2> surf, int x, int y, cudaSurfaceBoundaryMode mode)
# 596 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)surf;(void)x;(void)y;(void)mode;
# 600 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 603 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
template<> __attribute__((unused)) inline ushort4 surf2Dread(surface< void, 2> surf, int x, int y, cudaSurfaceBoundaryMode mode)
# 604 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)surf;(void)x;(void)y;(void)mode;
# 606 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 609 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
template<> __attribute__((unused)) inline int surf2Dread(surface< void, 2> surf, int x, int y, cudaSurfaceBoundaryMode mode)
# 610 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)surf;(void)x;(void)y;(void)mode;
# 612 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 615 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
template<> __attribute__((unused)) inline unsigned surf2Dread(surface< void, 2> surf, int x, int y, cudaSurfaceBoundaryMode mode)
# 616 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)surf;(void)x;(void)y;(void)mode;
# 618 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 621 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
template<> __attribute__((unused)) inline int1 surf2Dread(surface< void, 2> surf, int x, int y, cudaSurfaceBoundaryMode mode)
# 622 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)surf;(void)x;(void)y;(void)mode;
# 624 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 627 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
template<> __attribute__((unused)) inline uint1 surf2Dread(surface< void, 2> surf, int x, int y, cudaSurfaceBoundaryMode mode)
# 628 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)surf;(void)x;(void)y;(void)mode;
# 630 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 633 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
template<> __attribute__((unused)) inline int2 surf2Dread(surface< void, 2> surf, int x, int y, cudaSurfaceBoundaryMode mode)
# 634 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)surf;(void)x;(void)y;(void)mode;
# 638 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 641 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
template<> __attribute__((unused)) inline uint2 surf2Dread(surface< void, 2> surf, int x, int y, cudaSurfaceBoundaryMode mode)
# 642 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)surf;(void)x;(void)y;(void)mode;
# 644 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 647 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
template<> __attribute__((unused)) inline int4 surf2Dread(surface< void, 2> surf, int x, int y, cudaSurfaceBoundaryMode mode)
# 648 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)surf;(void)x;(void)y;(void)mode;
# 652 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 655 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
template<> __attribute__((unused)) inline uint4 surf2Dread(surface< void, 2> surf, int x, int y, cudaSurfaceBoundaryMode mode)
# 656 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)surf;(void)x;(void)y;(void)mode;
# 658 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 661 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
template<> __attribute__((unused)) inline long long surf2Dread(surface< void, 2> surf, int x, int y, cudaSurfaceBoundaryMode mode)
# 662 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)surf;(void)x;(void)y;(void)mode;
# 664 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 667 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
template<> __attribute__((unused)) inline unsigned long long surf2Dread(surface< void, 2> surf, int x, int y, cudaSurfaceBoundaryMode mode)
# 668 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)surf;(void)x;(void)y;(void)mode;
# 670 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 673 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
template<> __attribute__((unused)) inline longlong1 surf2Dread(surface< void, 2> surf, int x, int y, cudaSurfaceBoundaryMode mode)
# 674 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)surf;(void)x;(void)y;(void)mode;
# 676 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 679 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
template<> __attribute__((unused)) inline ulonglong1 surf2Dread(surface< void, 2> surf, int x, int y, cudaSurfaceBoundaryMode mode)
# 680 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)surf;(void)x;(void)y;(void)mode;
# 682 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 685 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
template<> __attribute__((unused)) inline longlong2 surf2Dread(surface< void, 2> surf, int x, int y, cudaSurfaceBoundaryMode mode)
# 686 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)surf;(void)x;(void)y;(void)mode;
# 690 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 693 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
template<> __attribute__((unused)) inline ulonglong2 surf2Dread(surface< void, 2> surf, int x, int y, cudaSurfaceBoundaryMode mode)
# 694 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)surf;(void)x;(void)y;(void)mode;
# 696 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 759 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
template<> __attribute__((unused)) inline float surf2Dread(surface< void, 2> surf, int x, int y, cudaSurfaceBoundaryMode mode)
# 760 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)surf;(void)x;(void)y;(void)mode;
# 762 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 765 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
template<> __attribute__((unused)) inline float1 surf2Dread(surface< void, 2> surf, int x, int y, cudaSurfaceBoundaryMode mode)
# 766 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)surf;(void)x;(void)y;(void)mode;
# 768 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 771 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
template<> __attribute__((unused)) inline float2 surf2Dread(surface< void, 2> surf, int x, int y, cudaSurfaceBoundaryMode mode)
# 772 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)surf;(void)x;(void)y;(void)mode;
# 776 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 779 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
template<> __attribute__((unused)) inline float4 surf2Dread(surface< void, 2> surf, int x, int y, cudaSurfaceBoundaryMode mode)
# 780 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)surf;(void)x;(void)y;(void)mode;
# 784 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 831 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
template< class T> __attribute__((unused)) static inline void
# 832 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
surf1Dwrite(T val, surface< void, 1> surf, int x, int s, cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap)
# 833 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)val;(void)surf;(void)x;(void)s;(void)mode;
# 851 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 853 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
template< class T> __attribute__((unused)) static inline void
# 854 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
surf1Dwrite(T val, surface< void, 1> surf, int x, cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap)
# 855 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)val;(void)surf;(void)x;(void)mode;
# 857 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 860 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
__attribute__((unused)) static inline void surf1Dwrite(char val, surface< void, 1> surf, int x, cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap)
# 861 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)val;(void)surf;(void)x;(void)mode;
# 863 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 865 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
__attribute__((unused)) static inline void surf1Dwrite(signed char val, surface< void, 1> surf, int x, cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap)
# 866 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)val;(void)surf;(void)x;(void)mode;
# 868 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 870 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
__attribute__((unused)) static inline void surf1Dwrite(unsigned char val, surface< void, 1> surf, int x, cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap)
# 871 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)val;(void)surf;(void)x;(void)mode;
# 873 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 875 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
__attribute__((unused)) static inline void surf1Dwrite(char1 val, surface< void, 1> surf, int x, cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap)
# 876 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)val;(void)surf;(void)x;(void)mode;
# 878 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 880 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
__attribute__((unused)) static inline void surf1Dwrite(uchar1 val, surface< void, 1> surf, int x, cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap)
# 881 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)val;(void)surf;(void)x;(void)mode;
# 883 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 885 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
__attribute__((unused)) static inline void surf1Dwrite(char2 val, surface< void, 1> surf, int x, cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap)
# 886 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)val;(void)surf;(void)x;(void)mode;
# 888 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 890 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
__attribute__((unused)) static inline void surf1Dwrite(uchar2 val, surface< void, 1> surf, int x, cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap)
# 891 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)val;(void)surf;(void)x;(void)mode;
# 893 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 895 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
__attribute__((unused)) static inline void surf1Dwrite(char4 val, surface< void, 1> surf, int x, cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap)
# 896 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)val;(void)surf;(void)x;(void)mode;
# 898 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 900 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
__attribute__((unused)) static inline void surf1Dwrite(uchar4 val, surface< void, 1> surf, int x, cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap)
# 901 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)val;(void)surf;(void)x;(void)mode;
# 903 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 905 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
__attribute__((unused)) static inline void surf1Dwrite(short val, surface< void, 1> surf, int x, cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap)
# 906 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)val;(void)surf;(void)x;(void)mode;
# 908 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 910 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
__attribute__((unused)) static inline void surf1Dwrite(unsigned short val, surface< void, 1> surf, int x, cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap)
# 911 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)val;(void)surf;(void)x;(void)mode;
# 913 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 915 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
__attribute__((unused)) static inline void surf1Dwrite(short1 val, surface< void, 1> surf, int x, cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap)
# 916 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)val;(void)surf;(void)x;(void)mode;
# 918 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 920 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
__attribute__((unused)) static inline void surf1Dwrite(ushort1 val, surface< void, 1> surf, int x, cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap)
# 921 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)val;(void)surf;(void)x;(void)mode;
# 923 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 925 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
__attribute__((unused)) static inline void surf1Dwrite(short2 val, surface< void, 1> surf, int x, cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap)
# 926 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)val;(void)surf;(void)x;(void)mode;
# 928 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 930 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
__attribute__((unused)) static inline void surf1Dwrite(ushort2 val, surface< void, 1> surf, int x, cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap)
# 931 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)val;(void)surf;(void)x;(void)mode;
# 933 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 935 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
__attribute__((unused)) static inline void surf1Dwrite(short4 val, surface< void, 1> surf, int x, cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap)
# 936 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)val;(void)surf;(void)x;(void)mode;
# 938 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 940 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
__attribute__((unused)) static inline void surf1Dwrite(ushort4 val, surface< void, 1> surf, int x, cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap)
# 941 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)val;(void)surf;(void)x;(void)mode;
# 943 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 945 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
__attribute__((unused)) static inline void surf1Dwrite(int val, surface< void, 1> surf, int x, cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap)
# 946 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)val;(void)surf;(void)x;(void)mode;
# 948 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 950 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
__attribute__((unused)) static inline void surf1Dwrite(unsigned val, surface< void, 1> surf, int x, cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap)
# 951 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)val;(void)surf;(void)x;(void)mode;
# 953 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 955 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
__attribute__((unused)) static inline void surf1Dwrite(int1 val, surface< void, 1> surf, int x, cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap)
# 956 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)val;(void)surf;(void)x;(void)mode;
# 958 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 960 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
__attribute__((unused)) static inline void surf1Dwrite(uint1 val, surface< void, 1> surf, int x, cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap)
# 961 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)val;(void)surf;(void)x;(void)mode;
# 963 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 965 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
__attribute__((unused)) static inline void surf1Dwrite(int2 val, surface< void, 1> surf, int x, cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap)
# 966 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)val;(void)surf;(void)x;(void)mode;
# 968 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 970 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
__attribute__((unused)) static inline void surf1Dwrite(uint2 val, surface< void, 1> surf, int x, cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap)
# 971 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)val;(void)surf;(void)x;(void)mode;
# 973 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 975 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
__attribute__((unused)) static inline void surf1Dwrite(int4 val, surface< void, 1> surf, int x, cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap)
# 976 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)val;(void)surf;(void)x;(void)mode;
# 978 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 980 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
__attribute__((unused)) static inline void surf1Dwrite(uint4 val, surface< void, 1> surf, int x, cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap)
# 981 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)val;(void)surf;(void)x;(void)mode;
# 983 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 985 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
__attribute__((unused)) static inline void surf1Dwrite(long long val, surface< void, 1> surf, int x, cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap)
# 986 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)val;(void)surf;(void)x;(void)mode;
# 988 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 990 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
__attribute__((unused)) static inline void surf1Dwrite(unsigned long long val, surface< void, 1> surf, int x, cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap)
# 991 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)val;(void)surf;(void)x;(void)mode;
# 993 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 995 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
__attribute__((unused)) static inline void surf1Dwrite(longlong1 val, surface< void, 1> surf, int x, cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap)
# 996 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)val;(void)surf;(void)x;(void)mode;
# 998 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 1000 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
__attribute__((unused)) static inline void surf1Dwrite(ulonglong1 val, surface< void, 1> surf, int x, cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap)
# 1001 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)val;(void)surf;(void)x;(void)mode;
# 1003 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 1005 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
__attribute__((unused)) static inline void surf1Dwrite(longlong2 val, surface< void, 1> surf, int x, cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap)
# 1006 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)val;(void)surf;(void)x;(void)mode;
# 1008 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 1010 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
__attribute__((unused)) static inline void surf1Dwrite(ulonglong2 val, surface< void, 1> surf, int x, cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap)
# 1011 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)val;(void)surf;(void)x;(void)mode;
# 1013 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 1059 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
__attribute__((unused)) static inline void surf1Dwrite(float val, surface< void, 1> surf, int x, cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap)
# 1060 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)val;(void)surf;(void)x;(void)mode;
# 1062 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 1064 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
__attribute__((unused)) static inline void surf1Dwrite(float1 val, surface< void, 1> surf, int x, cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap)
# 1065 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)val;(void)surf;(void)x;(void)mode;
# 1067 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 1069 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
__attribute__((unused)) static inline void surf1Dwrite(float2 val, surface< void, 1> surf, int x, cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap)
# 1070 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)val;(void)surf;(void)x;(void)mode;
# 1072 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 1074 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
__attribute__((unused)) static inline void surf1Dwrite(float4 val, surface< void, 1> surf, int x, cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap)
# 1075 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)val;(void)surf;(void)x;(void)mode;
# 1077 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 1124 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
template< class T> __attribute__((unused)) static inline void
# 1125 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
surf2Dwrite(T val, surface< void, 2> surf, int x, int y, int s, cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap)
# 1126 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)val;(void)surf;(void)x;(void)y;(void)s;(void)mode;
# 1144 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 1146 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
template< class T> __attribute__((unused)) static inline void
# 1147 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
surf2Dwrite(T val, surface< void, 2> surf, int x, int y, cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap)
# 1148 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)val;(void)surf;(void)x;(void)y;(void)mode;
# 1150 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 1153 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
__attribute__((unused)) static inline void surf2Dwrite(char val, surface< void, 2> surf, int x, int y, cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap)
# 1154 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)val;(void)surf;(void)x;(void)y;(void)mode;
# 1156 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 1158 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
__attribute__((unused)) static inline void surf2Dwrite(signed char val, surface< void, 2> surf, int x, int y, cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap)
# 1159 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)val;(void)surf;(void)x;(void)y;(void)mode;
# 1161 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 1163 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
__attribute__((unused)) static inline void surf2Dwrite(unsigned char val, surface< void, 2> surf, int x, int y, cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap)
# 1164 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)val;(void)surf;(void)x;(void)y;(void)mode;
# 1166 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 1168 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
__attribute__((unused)) static inline void surf2Dwrite(char1 val, surface< void, 2> surf, int x, int y, cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap)
# 1169 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)val;(void)surf;(void)x;(void)y;(void)mode;
# 1171 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 1173 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
__attribute__((unused)) static inline void surf2Dwrite(uchar1 val, surface< void, 2> surf, int x, int y, cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap)
# 1174 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)val;(void)surf;(void)x;(void)y;(void)mode;
# 1176 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 1178 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
__attribute__((unused)) static inline void surf2Dwrite(char2 val, surface< void, 2> surf, int x, int y, cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap)
# 1179 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)val;(void)surf;(void)x;(void)y;(void)mode;
# 1181 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 1183 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
__attribute__((unused)) static inline void surf2Dwrite(uchar2 val, surface< void, 2> surf, int x, int y, cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap)
# 1184 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)val;(void)surf;(void)x;(void)y;(void)mode;
# 1186 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 1188 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
__attribute__((unused)) static inline void surf2Dwrite(char4 val, surface< void, 2> surf, int x, int y, cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap)
# 1189 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)val;(void)surf;(void)x;(void)y;(void)mode;
# 1191 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 1193 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
__attribute__((unused)) static inline void surf2Dwrite(uchar4 val, surface< void, 2> surf, int x, int y, cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap)
# 1194 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)val;(void)surf;(void)x;(void)y;(void)mode;
# 1196 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 1198 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
__attribute__((unused)) static inline void surf2Dwrite(short val, surface< void, 2> surf, int x, int y, cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap)
# 1199 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)val;(void)surf;(void)x;(void)y;(void)mode;
# 1201 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 1203 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
__attribute__((unused)) static inline void surf2Dwrite(unsigned short val, surface< void, 2> surf, int x, int y, cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap)
# 1204 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)val;(void)surf;(void)x;(void)y;(void)mode;
# 1206 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 1208 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
__attribute__((unused)) static inline void surf2Dwrite(short1 val, surface< void, 2> surf, int x, int y, cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap)
# 1209 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)val;(void)surf;(void)x;(void)y;(void)mode;
# 1211 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 1213 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
__attribute__((unused)) static inline void surf2Dwrite(ushort1 val, surface< void, 2> surf, int x, int y, cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap)
# 1214 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)val;(void)surf;(void)x;(void)y;(void)mode;
# 1216 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 1218 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
__attribute__((unused)) static inline void surf2Dwrite(short2 val, surface< void, 2> surf, int x, int y, cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap)
# 1219 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)val;(void)surf;(void)x;(void)y;(void)mode;
# 1221 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 1223 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
__attribute__((unused)) static inline void surf2Dwrite(ushort2 val, surface< void, 2> surf, int x, int y, cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap)
# 1224 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)val;(void)surf;(void)x;(void)y;(void)mode;
# 1226 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 1228 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
__attribute__((unused)) static inline void surf2Dwrite(short4 val, surface< void, 2> surf, int x, int y, cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap)
# 1229 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)val;(void)surf;(void)x;(void)y;(void)mode;
# 1231 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 1233 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
__attribute__((unused)) static inline void surf2Dwrite(ushort4 val, surface< void, 2> surf, int x, int y, cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap)
# 1234 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)val;(void)surf;(void)x;(void)y;(void)mode;
# 1236 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 1238 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
__attribute__((unused)) static inline void surf2Dwrite(int val, surface< void, 2> surf, int x, int y, cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap)
# 1239 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)val;(void)surf;(void)x;(void)y;(void)mode;
# 1241 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 1243 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
__attribute__((unused)) static inline void surf2Dwrite(unsigned val, surface< void, 2> surf, int x, int y, cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap)
# 1244 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)val;(void)surf;(void)x;(void)y;(void)mode;
# 1246 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 1248 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
__attribute__((unused)) static inline void surf2Dwrite(int1 val, surface< void, 2> surf, int x, int y, cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap)
# 1249 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)val;(void)surf;(void)x;(void)y;(void)mode;
# 1251 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 1253 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
__attribute__((unused)) static inline void surf2Dwrite(uint1 val, surface< void, 2> surf, int x, int y, cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap)
# 1254 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)val;(void)surf;(void)x;(void)y;(void)mode;
# 1256 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 1258 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
__attribute__((unused)) static inline void surf2Dwrite(int2 val, surface< void, 2> surf, int x, int y, cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap)
# 1259 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)val;(void)surf;(void)x;(void)y;(void)mode;
# 1261 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 1263 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
__attribute__((unused)) static inline void surf2Dwrite(uint2 val, surface< void, 2> surf, int x, int y, cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap)
# 1264 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)val;(void)surf;(void)x;(void)y;(void)mode;
# 1266 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 1268 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
__attribute__((unused)) static inline void surf2Dwrite(int4 val, surface< void, 2> surf, int x, int y, cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap)
# 1269 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)val;(void)surf;(void)x;(void)y;(void)mode;
# 1271 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 1273 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
__attribute__((unused)) static inline void surf2Dwrite(uint4 val, surface< void, 2> surf, int x, int y, cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap)
# 1274 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)val;(void)surf;(void)x;(void)y;(void)mode;
# 1276 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 1278 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
__attribute__((unused)) static inline void surf2Dwrite(long long val, surface< void, 2> surf, int x, int y, cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap)
# 1279 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)val;(void)surf;(void)x;(void)y;(void)mode;
# 1281 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 1283 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
__attribute__((unused)) static inline void surf2Dwrite(unsigned long long val, surface< void, 2> surf, int x, int y, cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap)
# 1284 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)val;(void)surf;(void)x;(void)y;(void)mode;
# 1286 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 1288 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
__attribute__((unused)) static inline void surf2Dwrite(longlong1 val, surface< void, 2> surf, int x, int y, cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap)
# 1289 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)val;(void)surf;(void)x;(void)y;(void)mode;
# 1291 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 1293 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
__attribute__((unused)) static inline void surf2Dwrite(ulonglong1 val, surface< void, 2> surf, int x, int y, cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap)
# 1294 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)val;(void)surf;(void)x;(void)y;(void)mode;
# 1296 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 1298 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
__attribute__((unused)) static inline void surf2Dwrite(longlong2 val, surface< void, 2> surf, int x, int y, cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap)
# 1299 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)val;(void)surf;(void)x;(void)y;(void)mode;
# 1301 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 1303 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
__attribute__((unused)) static inline void surf2Dwrite(ulonglong2 val, surface< void, 2> surf, int x, int y, cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap)
# 1304 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)val;(void)surf;(void)x;(void)y;(void)mode;
# 1306 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 1352 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
__attribute__((unused)) static inline void surf2Dwrite(float val, surface< void, 2> surf, int x, int y, cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap)
# 1353 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)val;(void)surf;(void)x;(void)y;(void)mode;
# 1355 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 1357 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
__attribute__((unused)) static inline void surf2Dwrite(float1 val, surface< void, 2> surf, int x, int y, cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap)
# 1358 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)val;(void)surf;(void)x;(void)y;(void)mode;
# 1360 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 1362 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
__attribute__((unused)) static inline void surf2Dwrite(float2 val, surface< void, 2> surf, int x, int y, cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap)
# 1363 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)val;(void)surf;(void)x;(void)y;(void)mode;
# 1365 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 1367 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
__attribute__((unused)) static inline void surf2Dwrite(float4 val, surface< void, 2> surf, int x, int y, cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap)
# 1368 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
{int volatile ___ = 1;(void)val;(void)surf;(void)x;(void)y;(void)mode;
# 1370 "/home/hangzhang/local/cuda/4.0/bin/../include/surface_functions.h"
exit(___);}
# 75 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
template< class T, cudaTextureReadMode readMode> __attribute__((unused)) extern uint4 __utexfetchi(texture< T, 1, readMode> , int4 );
# 77 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
template< class T, cudaTextureReadMode readMode> __attribute__((unused)) extern int4 __itexfetchi(texture< T, 1, readMode> , int4 );
# 79 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
template< class T, cudaTextureReadMode readMode> __attribute__((unused)) extern float4 __ftexfetchi(texture< T, 1, readMode> , int4 );
# 82 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
template< class T, int texType, cudaTextureReadMode readMode> __attribute__((unused)) extern uint4 __utexfetch(texture< T, texType, readMode> , float4 , int = texType);
# 84 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
template< class T, int texType, cudaTextureReadMode readMode> __attribute__((unused)) extern int4 __itexfetch(texture< T, texType, readMode> , float4 , int = texType);
# 86 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
template< class T, int texType, cudaTextureReadMode readMode> __attribute__((unused)) extern float4 __ftexfetch(texture< T, texType, readMode> , float4 , int = texType);
# 89 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
template< class T, int texType, cudaTextureReadMode readMode> __attribute__((unused)) extern uint4 __utexfetchl(texture< T, texType, readMode> , float4 , int , int = (texType & 15));
# 91 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
template< class T, int texType, cudaTextureReadMode readMode> __attribute__((unused)) extern int4 __itexfetchl(texture< T, texType, readMode> , float4 , int , int = (texType & 15));
# 93 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
template< class T, int texType, cudaTextureReadMode readMode> __attribute__((unused)) extern float4 __ftexfetchl(texture< T, texType, readMode> , float4 , int , int = (texType & 15));
# 101 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline char tex1Dfetch(texture< char, 1, cudaReadModeElementType> t, int x)
# 102 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 110 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 112 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline signed char tex1Dfetch(texture< signed char, 1, cudaReadModeElementType> t, int x)
# 113 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 117 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 119 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline unsigned char tex1Dfetch(texture< unsigned char, 1, cudaReadModeElementType> t, int x)
# 120 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 124 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 126 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline char1 tex1Dfetch(texture< char1, 1, cudaReadModeElementType> t, int x)
# 127 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 131 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 133 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline uchar1 tex1Dfetch(texture< uchar1, 1, cudaReadModeElementType> t, int x)
# 134 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 138 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 140 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline char2 tex1Dfetch(texture< char2, 1, cudaReadModeElementType> t, int x)
# 141 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 145 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 147 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline uchar2 tex1Dfetch(texture< uchar2, 1, cudaReadModeElementType> t, int x)
# 148 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 152 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 154 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline char4 tex1Dfetch(texture< char4, 1, cudaReadModeElementType> t, int x)
# 155 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 159 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 161 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline uchar4 tex1Dfetch(texture< uchar4, 1, cudaReadModeElementType> t, int x)
# 162 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 166 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 174 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline short tex1Dfetch(texture< short, 1, cudaReadModeElementType> t, int x)
# 175 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 179 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 181 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline unsigned short tex1Dfetch(texture< unsigned short, 1, cudaReadModeElementType> t, int x)
# 182 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 186 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 188 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline short1 tex1Dfetch(texture< short1, 1, cudaReadModeElementType> t, int x)
# 189 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 193 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 195 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline ushort1 tex1Dfetch(texture< ushort1, 1, cudaReadModeElementType> t, int x)
# 196 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 200 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 202 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline short2 tex1Dfetch(texture< short2, 1, cudaReadModeElementType> t, int x)
# 203 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 207 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 209 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline ushort2 tex1Dfetch(texture< ushort2, 1, cudaReadModeElementType> t, int x)
# 210 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 214 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 216 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline short4 tex1Dfetch(texture< short4, 1, cudaReadModeElementType> t, int x)
# 217 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 221 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 223 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline ushort4 tex1Dfetch(texture< ushort4, 1, cudaReadModeElementType> t, int x)
# 224 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 228 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 236 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline int tex1Dfetch(texture< int, 1, cudaReadModeElementType> t, int x)
# 237 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 241 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 243 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline unsigned tex1Dfetch(texture< unsigned, 1, cudaReadModeElementType> t, int x)
# 244 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 248 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 250 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline int1 tex1Dfetch(texture< int1, 1, cudaReadModeElementType> t, int x)
# 251 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 255 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 257 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline uint1 tex1Dfetch(texture< uint1, 1, cudaReadModeElementType> t, int x)
# 258 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 262 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 264 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline int2 tex1Dfetch(texture< int2, 1, cudaReadModeElementType> t, int x)
# 265 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 269 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 271 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline uint2 tex1Dfetch(texture< uint2, 1, cudaReadModeElementType> t, int x)
# 272 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 276 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 278 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline int4 tex1Dfetch(texture< int4, 1, cudaReadModeElementType> t, int x)
# 279 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 283 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 285 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline uint4 tex1Dfetch(texture< uint4, 1, cudaReadModeElementType> t, int x)
# 286 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 290 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 364 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float tex1Dfetch(texture< float, 1, cudaReadModeElementType> t, int x)
# 365 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 369 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 371 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float1 tex1Dfetch(texture< float1, 1, cudaReadModeElementType> t, int x)
# 372 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 376 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 378 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float2 tex1Dfetch(texture< float2, 1, cudaReadModeElementType> t, int x)
# 379 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 383 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 385 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float4 tex1Dfetch(texture< float4, 1, cudaReadModeElementType> t, int x)
# 386 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 390 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 398 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float tex1Dfetch(texture< char, 1, cudaReadModeNormalizedFloat> t, int x)
# 399 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 408 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 410 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float tex1Dfetch(texture< signed char, 1, cudaReadModeNormalizedFloat> t, int x)
# 411 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 416 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 418 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float tex1Dfetch(texture< unsigned char, 1, cudaReadModeNormalizedFloat> t, int x)
# 419 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 424 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 426 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float1 tex1Dfetch(texture< char1, 1, cudaReadModeNormalizedFloat> t, int x)
# 427 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 432 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 434 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float1 tex1Dfetch(texture< uchar1, 1, cudaReadModeNormalizedFloat> t, int x)
# 435 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 440 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 442 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float2 tex1Dfetch(texture< char2, 1, cudaReadModeNormalizedFloat> t, int x)
# 443 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 448 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 450 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float2 tex1Dfetch(texture< uchar2, 1, cudaReadModeNormalizedFloat> t, int x)
# 451 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 456 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 458 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float4 tex1Dfetch(texture< char4, 1, cudaReadModeNormalizedFloat> t, int x)
# 459 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 464 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 466 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float4 tex1Dfetch(texture< uchar4, 1, cudaReadModeNormalizedFloat> t, int x)
# 467 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 472 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 480 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float tex1Dfetch(texture< short, 1, cudaReadModeNormalizedFloat> t, int x)
# 481 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 486 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 488 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float tex1Dfetch(texture< unsigned short, 1, cudaReadModeNormalizedFloat> t, int x)
# 489 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 494 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 496 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float1 tex1Dfetch(texture< short1, 1, cudaReadModeNormalizedFloat> t, int x)
# 497 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 502 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 504 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float1 tex1Dfetch(texture< ushort1, 1, cudaReadModeNormalizedFloat> t, int x)
# 505 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 510 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 512 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float2 tex1Dfetch(texture< short2, 1, cudaReadModeNormalizedFloat> t, int x)
# 513 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 518 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 520 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float2 tex1Dfetch(texture< ushort2, 1, cudaReadModeNormalizedFloat> t, int x)
# 521 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 526 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 528 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float4 tex1Dfetch(texture< short4, 1, cudaReadModeNormalizedFloat> t, int x)
# 529 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 534 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 536 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float4 tex1Dfetch(texture< ushort4, 1, cudaReadModeNormalizedFloat> t, int x)
# 537 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 542 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 550 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline char tex1D(texture< char, 1, cudaReadModeElementType> t, float x)
# 551 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 559 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 561 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline signed char tex1D(texture< signed char, 1, cudaReadModeElementType> t, float x)
# 562 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 566 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 568 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline unsigned char tex1D(texture< unsigned char, 1, cudaReadModeElementType> t, float x)
# 569 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 573 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 575 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline char1 tex1D(texture< char1, 1, cudaReadModeElementType> t, float x)
# 576 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 580 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 582 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline uchar1 tex1D(texture< uchar1, 1, cudaReadModeElementType> t, float x)
# 583 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 587 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 589 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline char2 tex1D(texture< char2, 1, cudaReadModeElementType> t, float x)
# 590 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 594 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 596 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline uchar2 tex1D(texture< uchar2, 1, cudaReadModeElementType> t, float x)
# 597 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 601 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 603 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline char4 tex1D(texture< char4, 1, cudaReadModeElementType> t, float x)
# 604 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 608 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 610 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline uchar4 tex1D(texture< uchar4, 1, cudaReadModeElementType> t, float x)
# 611 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 615 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 623 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline short tex1D(texture< short, 1, cudaReadModeElementType> t, float x)
# 624 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 628 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 630 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline unsigned short tex1D(texture< unsigned short, 1, cudaReadModeElementType> t, float x)
# 631 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 635 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 637 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline short1 tex1D(texture< short1, 1, cudaReadModeElementType> t, float x)
# 638 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 642 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 644 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline ushort1 tex1D(texture< ushort1, 1, cudaReadModeElementType> t, float x)
# 645 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 649 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 651 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline short2 tex1D(texture< short2, 1, cudaReadModeElementType> t, float x)
# 652 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 656 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 658 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline ushort2 tex1D(texture< ushort2, 1, cudaReadModeElementType> t, float x)
# 659 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 663 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 665 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline short4 tex1D(texture< short4, 1, cudaReadModeElementType> t, float x)
# 666 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 670 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 672 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline ushort4 tex1D(texture< ushort4, 1, cudaReadModeElementType> t, float x)
# 673 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 677 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 685 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline int tex1D(texture< int, 1, cudaReadModeElementType> t, float x)
# 686 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 690 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 692 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline unsigned tex1D(texture< unsigned, 1, cudaReadModeElementType> t, float x)
# 693 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 697 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 699 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline int1 tex1D(texture< int1, 1, cudaReadModeElementType> t, float x)
# 700 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 704 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 706 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline uint1 tex1D(texture< uint1, 1, cudaReadModeElementType> t, float x)
# 707 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 711 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 713 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline int2 tex1D(texture< int2, 1, cudaReadModeElementType> t, float x)
# 714 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 718 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 720 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline uint2 tex1D(texture< uint2, 1, cudaReadModeElementType> t, float x)
# 721 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 725 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 727 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline int4 tex1D(texture< int4, 1, cudaReadModeElementType> t, float x)
# 728 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 732 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 734 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline uint4 tex1D(texture< uint4, 1, cudaReadModeElementType> t, float x)
# 735 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 739 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 819 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float tex1D(texture< float, 1, cudaReadModeElementType> t, float x)
# 820 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 824 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 826 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float1 tex1D(texture< float1, 1, cudaReadModeElementType> t, float x)
# 827 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 831 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 833 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float2 tex1D(texture< float2, 1, cudaReadModeElementType> t, float x)
# 834 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 838 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 840 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float4 tex1D(texture< float4, 1, cudaReadModeElementType> t, float x)
# 841 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 845 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 853 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float tex1D(texture< char, 1, cudaReadModeNormalizedFloat> t, float x)
# 854 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 863 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 865 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float tex1D(texture< signed char, 1, cudaReadModeNormalizedFloat> t, float x)
# 866 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 871 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 873 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float tex1D(texture< unsigned char, 1, cudaReadModeNormalizedFloat> t, float x)
# 874 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 879 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 881 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float1 tex1D(texture< char1, 1, cudaReadModeNormalizedFloat> t, float x)
# 882 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 887 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 889 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float1 tex1D(texture< uchar1, 1, cudaReadModeNormalizedFloat> t, float x)
# 890 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 895 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 897 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float2 tex1D(texture< char2, 1, cudaReadModeNormalizedFloat> t, float x)
# 898 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 903 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 905 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float2 tex1D(texture< uchar2, 1, cudaReadModeNormalizedFloat> t, float x)
# 906 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 911 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 913 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float4 tex1D(texture< char4, 1, cudaReadModeNormalizedFloat> t, float x)
# 914 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 919 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 921 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float4 tex1D(texture< uchar4, 1, cudaReadModeNormalizedFloat> t, float x)
# 922 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 927 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 935 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float tex1D(texture< short, 1, cudaReadModeNormalizedFloat> t, float x)
# 936 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 941 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 943 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float tex1D(texture< unsigned short, 1, cudaReadModeNormalizedFloat> t, float x)
# 944 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 949 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 951 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float1 tex1D(texture< short1, 1, cudaReadModeNormalizedFloat> t, float x)
# 952 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 957 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 959 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float1 tex1D(texture< ushort1, 1, cudaReadModeNormalizedFloat> t, float x)
# 960 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 965 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 967 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float2 tex1D(texture< short2, 1, cudaReadModeNormalizedFloat> t, float x)
# 968 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 973 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 975 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float2 tex1D(texture< ushort2, 1, cudaReadModeNormalizedFloat> t, float x)
# 976 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 981 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 983 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float4 tex1D(texture< short4, 1, cudaReadModeNormalizedFloat> t, float x)
# 984 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 989 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 991 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float4 tex1D(texture< ushort4, 1, cudaReadModeNormalizedFloat> t, float x)
# 992 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;
# 997 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1005 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline char tex2D(texture< char, 2, cudaReadModeElementType> t, float x, float y)
# 1006 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;
# 1014 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1016 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline signed char tex2D(texture< signed char, 2, cudaReadModeElementType> t, float x, float y)
# 1017 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;
# 1021 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1023 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline unsigned char tex2D(texture< unsigned char, 2, cudaReadModeElementType> t, float x, float y)
# 1024 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;
# 1028 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1030 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline char1 tex2D(texture< char1, 2, cudaReadModeElementType> t, float x, float y)
# 1031 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;
# 1035 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1037 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline uchar1 tex2D(texture< uchar1, 2, cudaReadModeElementType> t, float x, float y)
# 1038 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;
# 1042 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1044 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline char2 tex2D(texture< char2, 2, cudaReadModeElementType> t, float x, float y)
# 1045 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;
# 1049 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1051 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline uchar2 tex2D(texture< uchar2, 2, cudaReadModeElementType> t, float x, float y)
# 1052 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;
# 1056 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1058 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline char4 tex2D(texture< char4, 2, cudaReadModeElementType> t, float x, float y)
# 1059 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;
# 1063 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1065 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline uchar4 tex2D(texture< uchar4, 2, cudaReadModeElementType> t, float x, float y)
# 1066 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;
# 1070 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1078 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline short tex2D(texture< short, 2, cudaReadModeElementType> t, float x, float y)
# 1079 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;
# 1083 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1085 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline unsigned short tex2D(texture< unsigned short, 2, cudaReadModeElementType> t, float x, float y)
# 1086 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;
# 1090 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1092 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline short1 tex2D(texture< short1, 2, cudaReadModeElementType> t, float x, float y)
# 1093 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;
# 1097 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1099 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline ushort1 tex2D(texture< ushort1, 2, cudaReadModeElementType> t, float x, float y)
# 1100 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;
# 1104 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1106 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline short2 tex2D(texture< short2, 2, cudaReadModeElementType> t, float x, float y)
# 1107 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;
# 1111 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1113 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline ushort2 tex2D(texture< ushort2, 2, cudaReadModeElementType> t, float x, float y)
# 1114 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;
# 1118 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1120 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline short4 tex2D(texture< short4, 2, cudaReadModeElementType> t, float x, float y)
# 1121 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;
# 1125 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1127 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline ushort4 tex2D(texture< ushort4, 2, cudaReadModeElementType> t, float x, float y)
# 1128 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;
# 1132 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1140 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline int tex2D(texture< int, 2, cudaReadModeElementType> t, float x, float y)
# 1141 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;
# 1145 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1147 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline unsigned tex2D(texture< unsigned, 2, cudaReadModeElementType> t, float x, float y)
# 1148 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;
# 1152 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1154 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline int1 tex2D(texture< int1, 2, cudaReadModeElementType> t, float x, float y)
# 1155 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;
# 1159 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1161 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline uint1 tex2D(texture< uint1, 2, cudaReadModeElementType> t, float x, float y)
# 1162 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;
# 1166 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1168 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline int2 tex2D(texture< int2, 2, cudaReadModeElementType> t, float x, float y)
# 1169 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;
# 1173 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1175 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline uint2 tex2D(texture< uint2, 2, cudaReadModeElementType> t, float x, float y)
# 1176 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;
# 1180 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1182 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline int4 tex2D(texture< int4, 2, cudaReadModeElementType> t, float x, float y)
# 1183 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;
# 1187 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1189 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline uint4 tex2D(texture< uint4, 2, cudaReadModeElementType> t, float x, float y)
# 1190 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;
# 1194 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1268 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float tex2D(texture< float, 2, cudaReadModeElementType> t, float x, float y)
# 1269 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;
# 1273 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1275 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float1 tex2D(texture< float1, 2, cudaReadModeElementType> t, float x, float y)
# 1276 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;
# 1280 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1282 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float2 tex2D(texture< float2, 2, cudaReadModeElementType> t, float x, float y)
# 1283 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;
# 1287 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1289 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float4 tex2D(texture< float4, 2, cudaReadModeElementType> t, float x, float y)
# 1290 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;
# 1294 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1302 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float tex2D(texture< char, 2, cudaReadModeNormalizedFloat> t, float x, float y)
# 1303 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;
# 1312 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1314 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float tex2D(texture< signed char, 2, cudaReadModeNormalizedFloat> t, float x, float y)
# 1315 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;
# 1320 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1322 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float tex2D(texture< unsigned char, 2, cudaReadModeNormalizedFloat> t, float x, float y)
# 1323 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;
# 1328 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1330 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float1 tex2D(texture< char1, 2, cudaReadModeNormalizedFloat> t, float x, float y)
# 1331 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;
# 1336 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1338 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float1 tex2D(texture< uchar1, 2, cudaReadModeNormalizedFloat> t, float x, float y)
# 1339 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;
# 1344 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1346 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float2 tex2D(texture< char2, 2, cudaReadModeNormalizedFloat> t, float x, float y)
# 1347 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;
# 1352 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1354 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float2 tex2D(texture< uchar2, 2, cudaReadModeNormalizedFloat> t, float x, float y)
# 1355 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;
# 1360 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1362 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float4 tex2D(texture< char4, 2, cudaReadModeNormalizedFloat> t, float x, float y)
# 1363 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;
# 1368 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1370 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float4 tex2D(texture< uchar4, 2, cudaReadModeNormalizedFloat> t, float x, float y)
# 1371 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;
# 1376 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1384 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float tex2D(texture< short, 2, cudaReadModeNormalizedFloat> t, float x, float y)
# 1385 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;
# 1390 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1392 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float tex2D(texture< unsigned short, 2, cudaReadModeNormalizedFloat> t, float x, float y)
# 1393 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;
# 1398 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1400 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float1 tex2D(texture< short1, 2, cudaReadModeNormalizedFloat> t, float x, float y)
# 1401 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;
# 1406 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1408 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float1 tex2D(texture< ushort1, 2, cudaReadModeNormalizedFloat> t, float x, float y)
# 1409 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;
# 1414 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1416 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float2 tex2D(texture< short2, 2, cudaReadModeNormalizedFloat> t, float x, float y)
# 1417 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;
# 1422 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1424 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float2 tex2D(texture< ushort2, 2, cudaReadModeNormalizedFloat> t, float x, float y)
# 1425 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;
# 1430 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1432 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float4 tex2D(texture< short4, 2, cudaReadModeNormalizedFloat> t, float x, float y)
# 1433 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;
# 1438 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1440 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float4 tex2D(texture< ushort4, 2, cudaReadModeNormalizedFloat> t, float x, float y)
# 1441 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;
# 1446 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1454 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline char tex1DLayered(texture< char, 241, cudaReadModeElementType> t, float x, int layer)
# 1455 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)layer;
# 1463 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1465 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline signed char tex1DLayered(texture< signed char, 241, cudaReadModeElementType> t, float x, int layer)
# 1466 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)layer;
# 1470 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1472 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline unsigned char tex1DLayered(texture< unsigned char, 241, cudaReadModeElementType> t, float x, int layer)
# 1473 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)layer;
# 1477 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1479 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline char1 tex1DLayered(texture< char1, 241, cudaReadModeElementType> t, float x, int layer)
# 1480 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)layer;
# 1484 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1486 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline uchar1 tex1DLayered(texture< uchar1, 241, cudaReadModeElementType> t, float x, int layer)
# 1487 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)layer;
# 1491 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1493 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline char2 tex1DLayered(texture< char2, 241, cudaReadModeElementType> t, float x, int layer)
# 1494 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)layer;
# 1498 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1500 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline uchar2 tex1DLayered(texture< uchar2, 241, cudaReadModeElementType> t, float x, int layer)
# 1501 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)layer;
# 1505 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1507 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline char4 tex1DLayered(texture< char4, 241, cudaReadModeElementType> t, float x, int layer)
# 1508 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)layer;
# 1512 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1514 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline uchar4 tex1DLayered(texture< uchar4, 241, cudaReadModeElementType> t, float x, int layer)
# 1515 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)layer;
# 1519 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1527 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline short tex1DLayered(texture< short, 241, cudaReadModeElementType> t, float x, int layer)
# 1528 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)layer;
# 1532 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1534 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline unsigned short tex1DLayered(texture< unsigned short, 241, cudaReadModeElementType> t, float x, int layer)
# 1535 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)layer;
# 1539 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1541 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline short1 tex1DLayered(texture< short1, 241, cudaReadModeElementType> t, float x, int layer)
# 1542 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)layer;
# 1546 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1548 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline ushort1 tex1DLayered(texture< ushort1, 241, cudaReadModeElementType> t, float x, int layer)
# 1549 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)layer;
# 1553 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1555 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline short2 tex1DLayered(texture< short2, 241, cudaReadModeElementType> t, float x, int layer)
# 1556 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)layer;
# 1560 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1562 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline ushort2 tex1DLayered(texture< ushort2, 241, cudaReadModeElementType> t, float x, int layer)
# 1563 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)layer;
# 1567 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1569 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline short4 tex1DLayered(texture< short4, 241, cudaReadModeElementType> t, float x, int layer)
# 1570 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)layer;
# 1574 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1576 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline ushort4 tex1DLayered(texture< ushort4, 241, cudaReadModeElementType> t, float x, int layer)
# 1577 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)layer;
# 1581 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1589 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline int tex1DLayered(texture< int, 241, cudaReadModeElementType> t, float x, int layer)
# 1590 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)layer;
# 1594 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1596 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline unsigned tex1DLayered(texture< unsigned, 241, cudaReadModeElementType> t, float x, int layer)
# 1597 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)layer;
# 1601 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1603 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline int1 tex1DLayered(texture< int1, 241, cudaReadModeElementType> t, float x, int layer)
# 1604 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)layer;
# 1608 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1610 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline uint1 tex1DLayered(texture< uint1, 241, cudaReadModeElementType> t, float x, int layer)
# 1611 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)layer;
# 1615 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1617 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline int2 tex1DLayered(texture< int2, 241, cudaReadModeElementType> t, float x, int layer)
# 1618 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)layer;
# 1622 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1624 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline uint2 tex1DLayered(texture< uint2, 241, cudaReadModeElementType> t, float x, int layer)
# 1625 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)layer;
# 1629 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1631 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline int4 tex1DLayered(texture< int4, 241, cudaReadModeElementType> t, float x, int layer)
# 1632 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)layer;
# 1636 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1638 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline uint4 tex1DLayered(texture< uint4, 241, cudaReadModeElementType> t, float x, int layer)
# 1639 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)layer;
# 1643 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1717 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float tex1DLayered(texture< float, 241, cudaReadModeElementType> t, float x, int layer)
# 1718 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)layer;
# 1722 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1724 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float1 tex1DLayered(texture< float1, 241, cudaReadModeElementType> t, float x, int layer)
# 1725 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)layer;
# 1729 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1731 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float2 tex1DLayered(texture< float2, 241, cudaReadModeElementType> t, float x, int layer)
# 1732 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)layer;
# 1736 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1738 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float4 tex1DLayered(texture< float4, 241, cudaReadModeElementType> t, float x, int layer)
# 1739 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)layer;
# 1743 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1751 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float tex1DLayered(texture< char, 241, cudaReadModeNormalizedFloat> t, float x, int layer)
# 1752 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)layer;
# 1761 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1763 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float tex1DLayered(texture< signed char, 241, cudaReadModeNormalizedFloat> t, float x, int layer)
# 1764 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)layer;
# 1769 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1771 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float tex1DLayered(texture< unsigned char, 241, cudaReadModeNormalizedFloat> t, float x, int layer)
# 1772 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)layer;
# 1777 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1779 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float1 tex1DLayered(texture< char1, 241, cudaReadModeNormalizedFloat> t, float x, int layer)
# 1780 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)layer;
# 1785 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1787 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float1 tex1DLayered(texture< uchar1, 241, cudaReadModeNormalizedFloat> t, float x, int layer)
# 1788 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)layer;
# 1793 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1795 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float2 tex1DLayered(texture< char2, 241, cudaReadModeNormalizedFloat> t, float x, int layer)
# 1796 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)layer;
# 1801 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1803 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float2 tex1DLayered(texture< uchar2, 241, cudaReadModeNormalizedFloat> t, float x, int layer)
# 1804 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)layer;
# 1809 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1811 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float4 tex1DLayered(texture< char4, 241, cudaReadModeNormalizedFloat> t, float x, int layer)
# 1812 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)layer;
# 1817 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1819 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float4 tex1DLayered(texture< uchar4, 241, cudaReadModeNormalizedFloat> t, float x, int layer)
# 1820 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)layer;
# 1825 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1833 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float tex1DLayered(texture< short, 241, cudaReadModeNormalizedFloat> t, float x, int layer)
# 1834 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)layer;
# 1839 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1841 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float tex1DLayered(texture< unsigned short, 241, cudaReadModeNormalizedFloat> t, float x, int layer)
# 1842 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)layer;
# 1847 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1849 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float1 tex1DLayered(texture< short1, 241, cudaReadModeNormalizedFloat> t, float x, int layer)
# 1850 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)layer;
# 1855 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1857 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float1 tex1DLayered(texture< ushort1, 241, cudaReadModeNormalizedFloat> t, float x, int layer)
# 1858 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)layer;
# 1863 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1865 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float2 tex1DLayered(texture< short2, 241, cudaReadModeNormalizedFloat> t, float x, int layer)
# 1866 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)layer;
# 1871 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1873 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float2 tex1DLayered(texture< ushort2, 241, cudaReadModeNormalizedFloat> t, float x, int layer)
# 1874 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)layer;
# 1879 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1881 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float4 tex1DLayered(texture< short4, 241, cudaReadModeNormalizedFloat> t, float x, int layer)
# 1882 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)layer;
# 1887 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1889 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float4 tex1DLayered(texture< ushort4, 241, cudaReadModeNormalizedFloat> t, float x, int layer)
# 1890 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)layer;
# 1895 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1903 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline char tex2DLayered(texture< char, 242, cudaReadModeElementType> t, float x, float y, int layer)
# 1904 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)layer;
# 1912 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1914 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline signed char tex2DLayered(texture< signed char, 242, cudaReadModeElementType> t, float x, float y, int layer)
# 1915 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)layer;
# 1919 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1921 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline unsigned char tex2DLayered(texture< unsigned char, 242, cudaReadModeElementType> t, float x, float y, int layer)
# 1922 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)layer;
# 1926 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1928 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline char1 tex2DLayered(texture< char1, 242, cudaReadModeElementType> t, float x, float y, int layer)
# 1929 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)layer;
# 1933 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1935 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline uchar1 tex2DLayered(texture< uchar1, 242, cudaReadModeElementType> t, float x, float y, int layer)
# 1936 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)layer;
# 1940 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1942 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline char2 tex2DLayered(texture< char2, 242, cudaReadModeElementType> t, float x, float y, int layer)
# 1943 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)layer;
# 1947 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1949 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline uchar2 tex2DLayered(texture< uchar2, 242, cudaReadModeElementType> t, float x, float y, int layer)
# 1950 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)layer;
# 1954 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1956 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline char4 tex2DLayered(texture< char4, 242, cudaReadModeElementType> t, float x, float y, int layer)
# 1957 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)layer;
# 1961 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1963 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline uchar4 tex2DLayered(texture< uchar4, 242, cudaReadModeElementType> t, float x, float y, int layer)
# 1964 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)layer;
# 1968 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1976 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline short tex2DLayered(texture< short, 242, cudaReadModeElementType> t, float x, float y, int layer)
# 1977 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)layer;
# 1981 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1983 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline unsigned short tex2DLayered(texture< unsigned short, 242, cudaReadModeElementType> t, float x, float y, int layer)
# 1984 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)layer;
# 1988 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1990 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline short1 tex2DLayered(texture< short1, 242, cudaReadModeElementType> t, float x, float y, int layer)
# 1991 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)layer;
# 1995 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 1997 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline ushort1 tex2DLayered(texture< ushort1, 242, cudaReadModeElementType> t, float x, float y, int layer)
# 1998 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)layer;
# 2002 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 2004 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline short2 tex2DLayered(texture< short2, 242, cudaReadModeElementType> t, float x, float y, int layer)
# 2005 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)layer;
# 2009 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 2011 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline ushort2 tex2DLayered(texture< ushort2, 242, cudaReadModeElementType> t, float x, float y, int layer)
# 2012 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)layer;
# 2016 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 2018 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline short4 tex2DLayered(texture< short4, 242, cudaReadModeElementType> t, float x, float y, int layer)
# 2019 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)layer;
# 2023 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 2025 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline ushort4 tex2DLayered(texture< ushort4, 242, cudaReadModeElementType> t, float x, float y, int layer)
# 2026 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)layer;
# 2030 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 2038 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline int tex2DLayered(texture< int, 242, cudaReadModeElementType> t, float x, float y, int layer)
# 2039 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)layer;
# 2043 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 2045 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline unsigned tex2DLayered(texture< unsigned, 242, cudaReadModeElementType> t, float x, float y, int layer)
# 2046 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)layer;
# 2050 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 2052 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline int1 tex2DLayered(texture< int1, 242, cudaReadModeElementType> t, float x, float y, int layer)
# 2053 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)layer;
# 2057 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 2059 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline uint1 tex2DLayered(texture< uint1, 242, cudaReadModeElementType> t, float x, float y, int layer)
# 2060 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)layer;
# 2064 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 2066 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline int2 tex2DLayered(texture< int2, 242, cudaReadModeElementType> t, float x, float y, int layer)
# 2067 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)layer;
# 2071 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 2073 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline uint2 tex2DLayered(texture< uint2, 242, cudaReadModeElementType> t, float x, float y, int layer)
# 2074 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)layer;
# 2078 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 2080 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline int4 tex2DLayered(texture< int4, 242, cudaReadModeElementType> t, float x, float y, int layer)
# 2081 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)layer;
# 2085 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 2087 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline uint4 tex2DLayered(texture< uint4, 242, cudaReadModeElementType> t, float x, float y, int layer)
# 2088 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)layer;
# 2092 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 2166 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float tex2DLayered(texture< float, 242, cudaReadModeElementType> t, float x, float y, int layer)
# 2167 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)layer;
# 2171 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 2173 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float1 tex2DLayered(texture< float1, 242, cudaReadModeElementType> t, float x, float y, int layer)
# 2174 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)layer;
# 2178 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 2180 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float2 tex2DLayered(texture< float2, 242, cudaReadModeElementType> t, float x, float y, int layer)
# 2181 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)layer;
# 2185 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 2187 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float4 tex2DLayered(texture< float4, 242, cudaReadModeElementType> t, float x, float y, int layer)
# 2188 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)layer;
# 2192 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 2200 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float tex2DLayered(texture< char, 242, cudaReadModeNormalizedFloat> t, float x, float y, int layer)
# 2201 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)layer;
# 2210 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 2212 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float tex2DLayered(texture< signed char, 242, cudaReadModeNormalizedFloat> t, float x, float y, int layer)
# 2213 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)layer;
# 2218 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 2220 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float tex2DLayered(texture< unsigned char, 242, cudaReadModeNormalizedFloat> t, float x, float y, int layer)
# 2221 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)layer;
# 2226 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 2228 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float1 tex2DLayered(texture< char1, 242, cudaReadModeNormalizedFloat> t, float x, float y, int layer)
# 2229 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)layer;
# 2234 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 2236 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float1 tex2DLayered(texture< uchar1, 242, cudaReadModeNormalizedFloat> t, float x, float y, int layer)
# 2237 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)layer;
# 2242 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 2244 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float2 tex2DLayered(texture< char2, 242, cudaReadModeNormalizedFloat> t, float x, float y, int layer)
# 2245 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)layer;
# 2250 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 2252 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float2 tex2DLayered(texture< uchar2, 242, cudaReadModeNormalizedFloat> t, float x, float y, int layer)
# 2253 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)layer;
# 2258 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 2260 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float4 tex2DLayered(texture< char4, 242, cudaReadModeNormalizedFloat> t, float x, float y, int layer)
# 2261 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)layer;
# 2266 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 2268 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float4 tex2DLayered(texture< uchar4, 242, cudaReadModeNormalizedFloat> t, float x, float y, int layer)
# 2269 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)layer;
# 2274 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 2282 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float tex2DLayered(texture< short, 242, cudaReadModeNormalizedFloat> t, float x, float y, int layer)
# 2283 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)layer;
# 2288 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 2290 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float tex2DLayered(texture< unsigned short, 242, cudaReadModeNormalizedFloat> t, float x, float y, int layer)
# 2291 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)layer;
# 2296 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 2298 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float1 tex2DLayered(texture< short1, 242, cudaReadModeNormalizedFloat> t, float x, float y, int layer)
# 2299 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)layer;
# 2304 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 2306 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float1 tex2DLayered(texture< ushort1, 242, cudaReadModeNormalizedFloat> t, float x, float y, int layer)
# 2307 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)layer;
# 2312 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 2314 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float2 tex2DLayered(texture< short2, 242, cudaReadModeNormalizedFloat> t, float x, float y, int layer)
# 2315 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)layer;
# 2320 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 2322 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float2 tex2DLayered(texture< ushort2, 242, cudaReadModeNormalizedFloat> t, float x, float y, int layer)
# 2323 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)layer;
# 2328 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 2330 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float4 tex2DLayered(texture< short4, 242, cudaReadModeNormalizedFloat> t, float x, float y, int layer)
# 2331 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)layer;
# 2336 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 2338 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float4 tex2DLayered(texture< ushort4, 242, cudaReadModeNormalizedFloat> t, float x, float y, int layer)
# 2339 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)layer;
# 2344 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 2352 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline char tex3D(texture< char, 3, cudaReadModeElementType> t, float x, float y, float z)
# 2353 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)z;
# 2361 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 2363 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline signed char tex3D(texture< signed char, 3, cudaReadModeElementType> t, float x, float y, float z)
# 2364 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)z;
# 2368 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 2370 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline unsigned char tex3D(texture< unsigned char, 3, cudaReadModeElementType> t, float x, float y, float z)
# 2371 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)z;
# 2375 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 2377 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline char1 tex3D(texture< char1, 3, cudaReadModeElementType> t, float x, float y, float z)
# 2378 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)z;
# 2382 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 2384 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline uchar1 tex3D(texture< uchar1, 3, cudaReadModeElementType> t, float x, float y, float z)
# 2385 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)z;
# 2389 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 2391 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline char2 tex3D(texture< char2, 3, cudaReadModeElementType> t, float x, float y, float z)
# 2392 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)z;
# 2396 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 2398 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline uchar2 tex3D(texture< uchar2, 3, cudaReadModeElementType> t, float x, float y, float z)
# 2399 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)z;
# 2403 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 2405 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline char4 tex3D(texture< char4, 3, cudaReadModeElementType> t, float x, float y, float z)
# 2406 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)z;
# 2410 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 2412 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline uchar4 tex3D(texture< uchar4, 3, cudaReadModeElementType> t, float x, float y, float z)
# 2413 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)z;
# 2417 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 2425 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline short tex3D(texture< short, 3, cudaReadModeElementType> t, float x, float y, float z)
# 2426 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)z;
# 2430 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 2432 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline unsigned short tex3D(texture< unsigned short, 3, cudaReadModeElementType> t, float x, float y, float z)
# 2433 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)z;
# 2437 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 2439 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline short1 tex3D(texture< short1, 3, cudaReadModeElementType> t, float x, float y, float z)
# 2440 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)z;
# 2444 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 2446 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline ushort1 tex3D(texture< ushort1, 3, cudaReadModeElementType> t, float x, float y, float z)
# 2447 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)z;
# 2451 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 2453 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline short2 tex3D(texture< short2, 3, cudaReadModeElementType> t, float x, float y, float z)
# 2454 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)z;
# 2458 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 2460 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline ushort2 tex3D(texture< ushort2, 3, cudaReadModeElementType> t, float x, float y, float z)
# 2461 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)z;
# 2465 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 2467 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline short4 tex3D(texture< short4, 3, cudaReadModeElementType> t, float x, float y, float z)
# 2468 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)z;
# 2472 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 2474 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline ushort4 tex3D(texture< ushort4, 3, cudaReadModeElementType> t, float x, float y, float z)
# 2475 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)z;
# 2479 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 2487 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline int tex3D(texture< int, 3, cudaReadModeElementType> t, float x, float y, float z)
# 2488 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)z;
# 2492 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 2494 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline unsigned tex3D(texture< unsigned, 3, cudaReadModeElementType> t, float x, float y, float z)
# 2495 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)z;
# 2499 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 2501 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline int1 tex3D(texture< int1, 3, cudaReadModeElementType> t, float x, float y, float z)
# 2502 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)z;
# 2506 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 2508 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline uint1 tex3D(texture< uint1, 3, cudaReadModeElementType> t, float x, float y, float z)
# 2509 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)z;
# 2513 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 2515 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline int2 tex3D(texture< int2, 3, cudaReadModeElementType> t, float x, float y, float z)
# 2516 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)z;
# 2520 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 2522 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline uint2 tex3D(texture< uint2, 3, cudaReadModeElementType> t, float x, float y, float z)
# 2523 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)z;
# 2527 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 2529 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline int4 tex3D(texture< int4, 3, cudaReadModeElementType> t, float x, float y, float z)
# 2530 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)z;
# 2534 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 2536 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline uint4 tex3D(texture< uint4, 3, cudaReadModeElementType> t, float x, float y, float z)
# 2537 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)z;
# 2541 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 2615 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float tex3D(texture< float, 3, cudaReadModeElementType> t, float x, float y, float z)
# 2616 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)z;
# 2620 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 2622 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float1 tex3D(texture< float1, 3, cudaReadModeElementType> t, float x, float y, float z)
# 2623 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)z;
# 2627 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 2629 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float2 tex3D(texture< float2, 3, cudaReadModeElementType> t, float x, float y, float z)
# 2630 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)z;
# 2634 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 2636 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float4 tex3D(texture< float4, 3, cudaReadModeElementType> t, float x, float y, float z)
# 2637 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)z;
# 2641 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 2649 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float tex3D(texture< char, 3, cudaReadModeNormalizedFloat> t, float x, float y, float z)
# 2650 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)z;
# 2659 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 2661 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float tex3D(texture< signed char, 3, cudaReadModeNormalizedFloat> t, float x, float y, float z)
# 2662 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)z;
# 2667 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 2669 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float tex3D(texture< unsigned char, 3, cudaReadModeNormalizedFloat> t, float x, float y, float z)
# 2670 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)z;
# 2675 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 2677 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float1 tex3D(texture< char1, 3, cudaReadModeNormalizedFloat> t, float x, float y, float z)
# 2678 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)z;
# 2683 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 2685 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float1 tex3D(texture< uchar1, 3, cudaReadModeNormalizedFloat> t, float x, float y, float z)
# 2686 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)z;
# 2691 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 2693 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float2 tex3D(texture< char2, 3, cudaReadModeNormalizedFloat> t, float x, float y, float z)
# 2694 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)z;
# 2699 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 2701 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float2 tex3D(texture< uchar2, 3, cudaReadModeNormalizedFloat> t, float x, float y, float z)
# 2702 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)z;
# 2707 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 2709 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float4 tex3D(texture< char4, 3, cudaReadModeNormalizedFloat> t, float x, float y, float z)
# 2710 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)z;
# 2715 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 2717 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float4 tex3D(texture< uchar4, 3, cudaReadModeNormalizedFloat> t, float x, float y, float z)
# 2718 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)z;
# 2723 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 2731 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float tex3D(texture< short, 3, cudaReadModeNormalizedFloat> t, float x, float y, float z)
# 2732 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)z;
# 2737 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 2739 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float tex3D(texture< unsigned short, 3, cudaReadModeNormalizedFloat> t, float x, float y, float z)
# 2740 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)z;
# 2745 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 2747 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float1 tex3D(texture< short1, 3, cudaReadModeNormalizedFloat> t, float x, float y, float z)
# 2748 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)z;
# 2753 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 2755 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float1 tex3D(texture< ushort1, 3, cudaReadModeNormalizedFloat> t, float x, float y, float z)
# 2756 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)z;
# 2761 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 2763 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float2 tex3D(texture< short2, 3, cudaReadModeNormalizedFloat> t, float x, float y, float z)
# 2764 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)z;
# 2769 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 2771 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float2 tex3D(texture< ushort2, 3, cudaReadModeNormalizedFloat> t, float x, float y, float z)
# 2772 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)z;
# 2777 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 2779 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float4 tex3D(texture< short4, 3, cudaReadModeNormalizedFloat> t, float x, float y, float z)
# 2780 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)z;
# 2785 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 2787 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
__attribute__((unused)) static inline float4 tex3D(texture< ushort4, 3, cudaReadModeNormalizedFloat> t, float x, float y, float z)
# 2788 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
{int volatile ___ = 1;(void)t;(void)x;(void)y;(void)z;
# 2793 "/home/hangzhang/local/cuda/4.0/bin/../include/texture_fetch_functions.h"
exit(___);}
# 67 "/home/hangzhang/local/cuda/4.0/bin/../include/device_launch_parameters.h"
extern "C" { extern const uint3 threadIdx; }
# 69 "/home/hangzhang/local/cuda/4.0/bin/../include/device_launch_parameters.h"
extern "C" { extern const uint3 blockIdx; }
# 71 "/home/hangzhang/local/cuda/4.0/bin/../include/device_launch_parameters.h"
extern "C" { extern const dim3 blockDim; }
# 73 "/home/hangzhang/local/cuda/4.0/bin/../include/device_launch_parameters.h"
extern "C" { extern const dim3 gridDim; }
# 75 "/home/hangzhang/local/cuda/4.0/bin/../include/device_launch_parameters.h"
extern "C" { extern const int warpSize; }
# 120 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
template< class T> inline cudaError_t
# 121 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
cudaSetupArgument(T
# 122 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
arg, size_t
# 123 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
offset)
# 125 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
{
# 126 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
return cudaSetupArgument((const void *)(&arg), sizeof(T), offset);
# 127 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
}
# 159 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
static inline cudaError_t cudaEventCreate(cudaEvent_t *
# 160 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
event, unsigned
# 161 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
flags)
# 163 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
{
# 164 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
return cudaEventCreateWithFlags(event, flags);
# 165 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
}
# 222 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
static inline cudaError_t cudaMallocHost(void **
# 223 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
ptr, size_t
# 224 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
size, unsigned
# 225 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
flags)
# 227 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
{
# 228 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
return cudaHostAlloc(ptr, size, flags);
# 229 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
}
# 231 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
template< class T> inline cudaError_t
# 232 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
cudaHostAlloc(T **
# 233 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
ptr, size_t
# 234 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
size, unsigned
# 235 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
flags)
# 237 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
{
# 238 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
return cudaHostAlloc((void **)((void *)ptr), size, flags);
# 239 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
}
# 241 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
template< class T> inline cudaError_t
# 242 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
cudaHostGetDevicePointer(T **
# 243 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
pDevice, void *
# 244 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
pHost, unsigned
# 245 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
flags)
# 247 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
{
# 248 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
return cudaHostGetDevicePointer((void **)((void *)pDevice), pHost, flags);
# 249 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
}
# 251 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
template< class T> inline cudaError_t
# 252 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
cudaMalloc(T **
# 253 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
devPtr, size_t
# 254 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
size)
# 256 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
{
# 257 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
return cudaMalloc((void **)((void *)devPtr), size);
# 258 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
}
# 260 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
template< class T> inline cudaError_t
# 261 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
cudaMallocHost(T **
# 262 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
ptr, size_t
# 263 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
size, unsigned
# 264 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
flags = (0))
# 266 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
{
# 267 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
return cudaMallocHost((void **)((void *)ptr), size, flags);
# 268 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
}
# 270 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
template< class T> inline cudaError_t
# 271 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
cudaMallocPitch(T **
# 272 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
devPtr, size_t *
# 273 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
pitch, size_t
# 274 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
width, size_t
# 275 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
height)
# 277 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
{
# 278 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
return cudaMallocPitch((void **)((void *)devPtr), pitch, width, height);
# 279 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
}
# 289 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
static inline cudaError_t cudaMemcpyToSymbol(char *
# 290 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
symbol, const void *
# 291 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
src, size_t
# 292 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
count, size_t
# 293 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
offset = (0), cudaMemcpyKind
# 294 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
kind = cudaMemcpyHostToDevice)
# 296 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
{
# 297 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
return cudaMemcpyToSymbol((const char *)symbol, src, count, offset, kind);
# 298 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
}
# 300 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
template< class T> inline cudaError_t
# 301 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
cudaMemcpyToSymbol(const T &
# 302 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
symbol, const void *
# 303 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
src, size_t
# 304 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
count, size_t
# 305 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
offset = (0), cudaMemcpyKind
# 306 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
kind = cudaMemcpyHostToDevice)
# 308 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
{
# 309 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
return cudaMemcpyToSymbol((const char *)(&symbol), src, count, offset, kind);
# 310 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
}
# 312 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
static inline cudaError_t cudaMemcpyToSymbolAsync(char *
# 313 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
symbol, const void *
# 314 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
src, size_t
# 315 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
count, size_t
# 316 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
offset = (0), cudaMemcpyKind
# 317 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
kind = cudaMemcpyHostToDevice, cudaStream_t
# 318 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
stream = 0)
# 320 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
{
# 321 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
return cudaMemcpyToSymbolAsync((const char *)symbol, src, count, offset, kind, stream);
# 322 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
}
# 324 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
template< class T> inline cudaError_t
# 325 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
cudaMemcpyToSymbolAsync(const T &
# 326 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
symbol, const void *
# 327 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
src, size_t
# 328 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
count, size_t
# 329 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
offset = (0), cudaMemcpyKind
# 330 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
kind = cudaMemcpyHostToDevice, cudaStream_t
# 331 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
stream = 0)
# 333 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
{
# 334 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
return cudaMemcpyToSymbolAsync((const char *)(&symbol), src, count, offset, kind, stream);
# 335 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
}
# 343 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
static inline cudaError_t cudaMemcpyFromSymbol(void *
# 344 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
dst, char *
# 345 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
symbol, size_t
# 346 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
count, size_t
# 347 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
offset = (0), cudaMemcpyKind
# 348 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
kind = cudaMemcpyDeviceToHost)
# 350 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
{
# 351 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
return cudaMemcpyFromSymbol(dst, (const char *)symbol, count, offset, kind);
# 352 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
}
# 354 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
template< class T> inline cudaError_t
# 355 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
cudaMemcpyFromSymbol(void *
# 356 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
dst, const T &
# 357 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
symbol, size_t
# 358 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
count, size_t
# 359 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
offset = (0), cudaMemcpyKind
# 360 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
kind = cudaMemcpyDeviceToHost)
# 362 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
{
# 363 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
return cudaMemcpyFromSymbol(dst, (const char *)(&symbol), count, offset, kind);
# 364 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
}
# 366 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
static inline cudaError_t cudaMemcpyFromSymbolAsync(void *
# 367 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
dst, char *
# 368 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
symbol, size_t
# 369 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
count, size_t
# 370 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
offset = (0), cudaMemcpyKind
# 371 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
kind = cudaMemcpyDeviceToHost, cudaStream_t
# 372 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
stream = 0)
# 374 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
{
# 375 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
return cudaMemcpyFromSymbolAsync(dst, (const char *)symbol, count, offset, kind, stream);
# 376 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
}
# 378 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
template< class T> inline cudaError_t
# 379 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
cudaMemcpyFromSymbolAsync(void *
# 380 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
dst, const T &
# 381 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
symbol, size_t
# 382 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
count, size_t
# 383 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
offset = (0), cudaMemcpyKind
# 384 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
kind = cudaMemcpyDeviceToHost, cudaStream_t
# 385 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
stream = 0)
# 387 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
{
# 388 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
return cudaMemcpyFromSymbolAsync(dst, (const char *)(&symbol), count, offset, kind, stream);
# 389 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
}
# 391 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
static inline cudaError_t cudaGetSymbolAddress(void **
# 392 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
devPtr, char *
# 393 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
symbol)
# 395 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
{
# 396 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
return cudaGetSymbolAddress(devPtr, (const char *)symbol);
# 397 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
}
# 424 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
template< class T> inline cudaError_t
# 425 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
cudaGetSymbolAddress(void **
# 426 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
devPtr, const T &
# 427 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
symbol)
# 429 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
{
# 430 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
return cudaGetSymbolAddress(devPtr, (const char *)(&symbol));
# 431 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
}
# 439 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
static inline cudaError_t cudaGetSymbolSize(size_t *
# 440 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
size, char *
# 441 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
symbol)
# 443 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
{
# 444 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
return cudaGetSymbolSize(size, (const char *)symbol);
# 445 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
}
# 472 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
template< class T> inline cudaError_t
# 473 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
cudaGetSymbolSize(size_t *
# 474 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
size, const T &
# 475 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
symbol)
# 477 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
{
# 478 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
return cudaGetSymbolSize(size, (const char *)(&symbol));
# 479 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
}
# 521 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
template< class T, int dim, cudaTextureReadMode readMode> inline cudaError_t
# 522 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
cudaBindTexture(size_t *
# 523 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
offset, const texture< T, dim, readMode> &
# 524 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
tex, const void *
# 525 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
devPtr, const cudaChannelFormatDesc &
# 526 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
desc, size_t
# 527 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
size = (((2147483647) * 2U) + 1U))
# 529 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
{
# 530 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
return cudaBindTexture(offset, &tex, devPtr, &desc, size);
# 531 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
}
# 566 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
template< class T, int dim, cudaTextureReadMode readMode> inline cudaError_t
# 567 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
cudaBindTexture(size_t *
# 568 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
offset, const texture< T, dim, readMode> &
# 569 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
tex, const void *
# 570 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
devPtr, size_t
# 571 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
size = (((2147483647) * 2U) + 1U))
# 573 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
{
# 574 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
return cudaBindTexture(offset, tex, devPtr, (tex.channelDesc), size);
# 575 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
}
# 622 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
template< class T, int dim, cudaTextureReadMode readMode> inline cudaError_t
# 623 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
cudaBindTexture2D(size_t *
# 624 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
offset, const texture< T, dim, readMode> &
# 625 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
tex, const void *
# 626 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
devPtr, const cudaChannelFormatDesc &
# 627 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
desc, size_t
# 628 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
width, size_t
# 629 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
height, size_t
# 630 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
pitch)
# 632 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
{
# 633 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
return cudaBindTexture2D(offset, &tex, devPtr, &desc, width, height, pitch);
# 634 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
}
# 680 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
template< class T, int dim, cudaTextureReadMode readMode> inline cudaError_t
# 681 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
cudaBindTexture2D(size_t *
# 682 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
offset, const texture< T, dim, readMode> &
# 683 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
tex, const void *
# 684 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
devPtr, size_t
# 685 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
width, size_t
# 686 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
height, size_t
# 687 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
pitch)
# 689 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
{
# 690 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
return cudaBindTexture2D(offset, &tex, devPtr, &(tex.texture< T, dim, readMode> ::channelDesc), width, height, pitch);
# 691 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
}
# 722 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
template< class T, int dim, cudaTextureReadMode readMode> inline cudaError_t
# 723 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
cudaBindTextureToArray(const texture< T, dim, readMode> &
# 724 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
tex, const cudaArray *
# 725 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
array, const cudaChannelFormatDesc &
# 726 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
desc)
# 728 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
{
# 729 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
return cudaBindTextureToArray(&tex, array, &desc);
# 730 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
}
# 760 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
template< class T, int dim, cudaTextureReadMode readMode> inline cudaError_t
# 761 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
cudaBindTextureToArray(const texture< T, dim, readMode> &
# 762 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
tex, const cudaArray *
# 763 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
array)
# 765 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
{
# 766 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
cudaChannelFormatDesc desc;
# 767 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
cudaError_t err = cudaGetChannelDesc(&desc, array);
# 769 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
return (err == (cudaSuccess)) ? cudaBindTextureToArray(tex, array, desc) : err;
# 770 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
}
# 799 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
template< class T, int dim, cudaTextureReadMode readMode> inline cudaError_t
# 800 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
cudaUnbindTexture(const texture< T, dim, readMode> &
# 801 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
tex)
# 803 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
{
# 804 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
return cudaUnbindTexture(&tex);
# 805 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
}
# 839 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
template< class T, int dim, cudaTextureReadMode readMode> inline cudaError_t
# 840 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
cudaGetTextureAlignmentOffset(size_t *
# 841 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
offset, const texture< T, dim, readMode> &
# 842 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
tex)
# 844 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
{
# 845 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
return cudaGetTextureAlignmentOffset(offset, &tex);
# 846 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
}
# 900 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
template< class T> inline cudaError_t
# 901 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
cudaFuncSetCacheConfig(T *
# 902 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
func, cudaFuncCache
# 903 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
cacheConfig)
# 905 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
{
# 906 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
return cudaFuncSetCacheConfig((const char *)func, cacheConfig);
# 907 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
}
# 944 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
template< class T> inline cudaError_t
# 945 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
cudaLaunch(T *
# 946 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
entry)
# 948 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
{
# 949 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
return cudaLaunch((const char *)entry);
# 950 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
}
# 984 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
template< class T> inline cudaError_t
# 985 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
cudaFuncGetAttributes(cudaFuncAttributes *
# 986 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
attr, T *
# 987 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
entry)
# 989 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
{
# 990 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
return cudaFuncGetAttributes(attr, (const char *)entry);
# 991 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
}
# 1013 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
template< class T, int dim> inline cudaError_t
# 1014 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
cudaBindSurfaceToArray(const surface< T, dim> &
# 1015 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
surf, const cudaArray *
# 1016 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
array, const cudaChannelFormatDesc &
# 1017 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
desc)
# 1019 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
{
# 1020 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
return cudaBindSurfaceToArray(&surf, array, &desc);
# 1021 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
}
# 1042 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
template< class T, int dim> inline cudaError_t
# 1043 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
cudaBindSurfaceToArray(const surface< T, dim> &
# 1044 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
surf, const cudaArray *
# 1045 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
array)
# 1047 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
{
# 1048 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
cudaChannelFormatDesc desc;
# 1049 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
cudaError_t err = cudaGetChannelDesc(&desc, array);
# 1051 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
return (err == (cudaSuccess)) ? cudaBindSurfaceToArray(surf, array, desc) : err;
# 1052 "/home/hangzhang/local/cuda/4.0/bin/../include/cuda_runtime.h"
}
# 45 "/usr/include/stdio.h" 3
struct _IO_FILE;
# 49 "/usr/include/stdio.h" 3
extern "C" { typedef _IO_FILE FILE; }
# 65 "/usr/include/stdio.h" 3
extern "C" { typedef _IO_FILE __FILE; }
# 95 "/usr/include/wchar.h" 3
extern "C" { typedef
# 84 "/usr/include/wchar.h" 3
struct {
# 85 "/usr/include/wchar.h" 3
int __count;
# 87 "/usr/include/wchar.h" 3
union {
# 89 "/usr/include/wchar.h" 3
unsigned __wch;
# 93 "/usr/include/wchar.h" 3
char __wchb[4];
# 94 "/usr/include/wchar.h" 3
} __value;
# 95 "/usr/include/wchar.h" 3
} __mbstate_t; }
# 26 "/usr/include/_G_config.h" 3
extern "C" { typedef
# 23 "/usr/include/_G_config.h" 3
struct {
# 24 "/usr/include/_G_config.h" 3
__off_t __pos;
# 25 "/usr/include/_G_config.h" 3
__mbstate_t __state;
# 26 "/usr/include/_G_config.h" 3
} _G_fpos_t; }
# 31 "/usr/include/_G_config.h" 3
extern "C" { typedef
# 28 "/usr/include/_G_config.h" 3
struct {
# 29 "/usr/include/_G_config.h" 3
__off64_t __pos;
# 30 "/usr/include/_G_config.h" 3
__mbstate_t __state;
# 31 "/usr/include/_G_config.h" 3
} _G_fpos64_t; }
# 53 "/usr/include/_G_config.h" 3
extern "C" { typedef short _G_int16_t __attribute((__mode__(__HI__))); }
# 54 "/usr/include/_G_config.h" 3
extern "C" { typedef int _G_int32_t __attribute((__mode__(__SI__))); }
# 55 "/usr/include/_G_config.h" 3
extern "C" { typedef unsigned short _G_uint16_t __attribute((__mode__(__HI__))); }
# 56 "/usr/include/_G_config.h" 3
extern "C" { typedef unsigned _G_uint32_t __attribute((__mode__(__SI__))); }
# 40 "/usr/lib/gcc/x86_64-redhat-linux/4.4.6/include/stdarg.h" 3
extern "C" { typedef __builtin_va_list __gnuc_va_list; }
# 170 "/usr/include/libio.h" 3
struct _IO_jump_t; struct _IO_FILE;
# 180 "/usr/include/libio.h" 3
extern "C" { typedef void _IO_lock_t; }
# 186 "/usr/include/libio.h" 3
extern "C" { struct _IO_marker {
# 187 "/usr/include/libio.h" 3
_IO_marker *_next;
# 188 "/usr/include/libio.h" 3
_IO_FILE *_sbuf;
# 192 "/usr/include/libio.h" 3
int _pos;
# 203 "/usr/include/libio.h" 3
}; }
# 206 "/usr/include/libio.h" 3
enum __codecvt_result {
# 208 "/usr/include/libio.h" 3
__codecvt_ok,
# 209 "/usr/include/libio.h" 3
__codecvt_partial,
# 210 "/usr/include/libio.h" 3
__codecvt_error,
# 211 "/usr/include/libio.h" 3
__codecvt_noconv
# 212 "/usr/include/libio.h" 3
};
# 271 "/usr/include/libio.h" 3
extern "C" { struct _IO_FILE {
# 272 "/usr/include/libio.h" 3
int _flags;
# 277 "/usr/include/libio.h" 3
char *_IO_read_ptr;
# 278 "/usr/include/libio.h" 3
char *_IO_read_end;
# 279 "/usr/include/libio.h" 3
char *_IO_read_base;
# 280 "/usr/include/libio.h" 3
char *_IO_write_base;
# 281 "/usr/include/libio.h" 3
char *_IO_write_ptr;
# 282 "/usr/include/libio.h" 3
char *_IO_write_end;
# 283 "/usr/include/libio.h" 3
char *_IO_buf_base;
# 284 "/usr/include/libio.h" 3
char *_IO_buf_end;
# 286 "/usr/include/libio.h" 3
char *_IO_save_base;
# 287 "/usr/include/libio.h" 3
char *_IO_backup_base;
# 288 "/usr/include/libio.h" 3
char *_IO_save_end;
# 290 "/usr/include/libio.h" 3
_IO_marker *_markers;
# 292 "/usr/include/libio.h" 3
_IO_FILE *_chain;
# 294 "/usr/include/libio.h" 3
int _fileno;
# 298 "/usr/include/libio.h" 3
int _flags2;
# 300 "/usr/include/libio.h" 3
__off_t _old_offset;
# 304 "/usr/include/libio.h" 3
unsigned short _cur_column;
# 305 "/usr/include/libio.h" 3
signed char _vtable_offset;
# 306 "/usr/include/libio.h" 3
char _shortbuf[1];
# 310 "/usr/include/libio.h" 3
_IO_lock_t *_lock;
# 319 "/usr/include/libio.h" 3
__off64_t _offset;
# 328 "/usr/include/libio.h" 3
void *__pad1;
# 329 "/usr/include/libio.h" 3
void *__pad2;
# 330 "/usr/include/libio.h" 3
void *__pad3;
# 331 "/usr/include/libio.h" 3
void *__pad4;
# 332 "/usr/include/libio.h" 3
size_t __pad5;
# 334 "/usr/include/libio.h" 3
int _mode;
# 336 "/usr/include/libio.h" 3
char _unused2[(((15) * sizeof(int)) - ((4) * sizeof(void *))) - sizeof(size_t)];
# 338 "/usr/include/libio.h" 3
}; }
# 344 "/usr/include/libio.h" 3
struct _IO_FILE_plus;
# 346 "/usr/include/libio.h" 3
extern "C" { extern _IO_FILE_plus _IO_2_1_stdin_; }
# 347 "/usr/include/libio.h" 3
extern "C" { extern _IO_FILE_plus _IO_2_1_stdout_; }
# 348 "/usr/include/libio.h" 3
extern "C" { extern _IO_FILE_plus _IO_2_1_stderr_; }
# 364 "/usr/include/libio.h" 3
extern "C" { typedef __ssize_t __io_read_fn(void * , char * , size_t ); }
# 372 "/usr/include/libio.h" 3
extern "C" { typedef __ssize_t __io_write_fn(void * , const char * , size_t ); }
# 381 "/usr/include/libio.h" 3
extern "C" { typedef int __io_seek_fn(void * , __off64_t * , int ); }
# 384 "/usr/include/libio.h" 3
extern "C" { typedef int __io_close_fn(void * ); }
# 389 "/usr/include/libio.h" 3
extern "C" { typedef __io_read_fn cookie_read_function_t; }
# 390 "/usr/include/libio.h" 3
extern "C" { typedef __io_write_fn cookie_write_function_t; }
# 391 "/usr/include/libio.h" 3
extern "C" { typedef __io_seek_fn cookie_seek_function_t; }
# 392 "/usr/include/libio.h" 3
extern "C" { typedef __io_close_fn cookie_close_function_t; }
# 401 "/usr/include/libio.h" 3
extern "C" { typedef
# 396 "/usr/include/libio.h" 3
struct {
# 397 "/usr/include/libio.h" 3
__io_read_fn *read;
# 398 "/usr/include/libio.h" 3
__io_write_fn *write;
# 399 "/usr/include/libio.h" 3
__io_seek_fn *seek;
# 400 "/usr/include/libio.h" 3
__io_close_fn *close;
# 401 "/usr/include/libio.h" 3
} _IO_cookie_io_functions_t; }
# 402 "/usr/include/libio.h" 3
extern "C" { typedef _IO_cookie_io_functions_t cookie_io_functions_t; }
# 404 "/usr/include/libio.h" 3
struct _IO_cookie_file;
# 407 "/usr/include/libio.h" 3
extern "C" void _IO_cookie_init(_IO_cookie_file * , int , void * , _IO_cookie_io_functions_t );
# 416 "/usr/include/libio.h" 3
extern "C" int __underflow(_IO_FILE *);
# 417 "/usr/include/libio.h" 3
extern "C" int __uflow(_IO_FILE *);
# 418 "/usr/include/libio.h" 3
extern "C" int __overflow(_IO_FILE *, int);
# 460 "/usr/include/libio.h" 3
extern "C" int _IO_getc(_IO_FILE * );
# 461 "/usr/include/libio.h" 3
extern "C" int _IO_putc(int , _IO_FILE * );
# 462 "/usr/include/libio.h" 3
extern "C" int _IO_feof(_IO_FILE * ) throw();
# 463 "/usr/include/libio.h" 3
extern "C" int _IO_ferror(_IO_FILE * ) throw();
# 465 "/usr/include/libio.h" 3
extern "C" int _IO_peekc_locked(_IO_FILE * );
# 471 "/usr/include/libio.h" 3
extern "C" void _IO_flockfile(_IO_FILE *) throw();
# 472 "/usr/include/libio.h" 3
extern "C" void _IO_funlockfile(_IO_FILE *) throw();
# 473 "/usr/include/libio.h" 3
extern "C" int _IO_ftrylockfile(_IO_FILE *) throw();
# 490 "/usr/include/libio.h" 3
extern "C" int _IO_vfscanf(_IO_FILE *__restrict__, const char *__restrict__, __gnuc_va_list, int *__restrict__);
# 492 "/usr/include/libio.h" 3
extern "C" int _IO_vfprintf(_IO_FILE *__restrict__, const char *__restrict__, __gnuc_va_list);
# 494 "/usr/include/libio.h" 3
extern "C" __ssize_t _IO_padn(_IO_FILE *, int, __ssize_t);
# 495 "/usr/include/libio.h" 3
extern "C" size_t _IO_sgetn(_IO_FILE *, void *, size_t);
# 497 "/usr/include/libio.h" 3
extern "C" __off64_t _IO_seekoff(_IO_FILE *, __off64_t, int, int);
# 498 "/usr/include/libio.h" 3
extern "C" __off64_t _IO_seekpos(_IO_FILE *, __off64_t, int);
# 500 "/usr/include/libio.h" 3
extern "C" void _IO_free_backup_area(_IO_FILE *) throw();
# 80 "/usr/include/stdio.h" 3
extern "C" { typedef __gnuc_va_list va_list; }
# 111 "/usr/include/stdio.h" 3
extern "C" { typedef _G_fpos_t fpos_t; }
# 117 "/usr/include/stdio.h" 3
extern "C" { typedef _G_fpos64_t fpos64_t; }
# 165 "/usr/include/stdio.h" 3
extern "C" { extern _IO_FILE *stdin; }
# 166 "/usr/include/stdio.h" 3
extern "C" { extern _IO_FILE *stdout; }
# 167 "/usr/include/stdio.h" 3
extern "C" { extern _IO_FILE *stderr; }
# 177 "/usr/include/stdio.h" 3
extern "C" int remove(const char * ) throw();
# 179 "/usr/include/stdio.h" 3
extern "C" int rename(const char * , const char * ) throw();
# 184 "/usr/include/stdio.h" 3
extern "C" int renameat(int , const char * , int , const char * ) throw();
# 194 "/usr/include/stdio.h" 3
extern "C" FILE *tmpfile();
# 204 "/usr/include/stdio.h" 3
extern "C" FILE *tmpfile64();
# 208 "/usr/include/stdio.h" 3
extern "C" char *tmpnam(char * ) throw();
# 214 "/usr/include/stdio.h" 3
extern "C" char *tmpnam_r(char * ) throw();
# 226 "/usr/include/stdio.h" 3
extern "C" char *tempnam(const char * , const char * ) throw()
# 227 "/usr/include/stdio.h" 3
 __attribute((__malloc__));
# 236 "/usr/include/stdio.h" 3
extern "C" int fclose(FILE * );
# 241 "/usr/include/stdio.h" 3
extern "C" int fflush(FILE * );
# 251 "/usr/include/stdio.h" 3
extern "C" int fflush_unlocked(FILE * );
# 261 "/usr/include/stdio.h" 3
extern "C" int fcloseall();
# 271 "/usr/include/stdio.h" 3
extern "C" FILE *fopen(const char *__restrict__ , const char *__restrict__ );
# 277 "/usr/include/stdio.h" 3
extern "C" FILE *freopen(const char *__restrict__ , const char *__restrict__ , FILE *__restrict__ );
# 296 "/usr/include/stdio.h" 3
extern "C" FILE *fopen64(const char *__restrict__ , const char *__restrict__ );
# 298 "/usr/include/stdio.h" 3
extern "C" FILE *freopen64(const char *__restrict__ , const char *__restrict__ , FILE *__restrict__ );
# 305 "/usr/include/stdio.h" 3
extern "C" FILE *fdopen(int , const char * ) throw();
# 311 "/usr/include/stdio.h" 3
extern "C" FILE *fopencookie(void *__restrict__ , const char *__restrict__ , _IO_cookie_io_functions_t ) throw();
# 318 "/usr/include/stdio.h" 3
extern "C" FILE *fmemopen(void * , size_t , const char * ) throw();
# 324 "/usr/include/stdio.h" 3
extern "C" FILE *open_memstream(char ** , size_t * ) throw();
# 331 "/usr/include/stdio.h" 3
extern "C" void setbuf(FILE *__restrict__ , char *__restrict__ ) throw();
# 335 "/usr/include/stdio.h" 3
extern "C" int setvbuf(FILE *__restrict__ , char *__restrict__ , int , size_t ) throw();
# 342 "/usr/include/stdio.h" 3
extern "C" void setbuffer(FILE *__restrict__ , char *__restrict__ , size_t ) throw();
# 346 "/usr/include/stdio.h" 3
extern "C" void setlinebuf(FILE * ) throw();
# 355 "/usr/include/stdio.h" 3
extern "C" int fprintf(FILE *__restrict__ , const char *__restrict__ , ...);
# 361 "/usr/include/stdio.h" 3
extern "C" int printf(const char *__restrict__ , ...);
# 363 "/usr/include/stdio.h" 3
extern "C" int sprintf(char *__restrict__ , const char *__restrict__ , ...) throw();
# 370 "/usr/include/stdio.h" 3
extern "C" int vfprintf(FILE *__restrict__ , const char *__restrict__ , __gnuc_va_list );
# 376 "/usr/include/stdio.h" 3
extern "C" int vprintf(const char *__restrict__ , __gnuc_va_list );
# 378 "/usr/include/stdio.h" 3
extern "C" int vsprintf(char *__restrict__ , const char *__restrict__ , __gnuc_va_list ) throw();
# 385 "/usr/include/stdio.h" 3
extern "C" int snprintf(char *__restrict__ , size_t , const char *__restrict__ , ...) throw()
# 387 "/usr/include/stdio.h" 3
 __attribute((__format__(__printf__, 3, 4)));
# 389 "/usr/include/stdio.h" 3
extern "C" int vsnprintf(char *__restrict__ , size_t , const char *__restrict__ , __gnuc_va_list ) throw()
# 391 "/usr/include/stdio.h" 3
 __attribute((__format__(__printf__, 3, 0)));
# 398 "/usr/include/stdio.h" 3
extern "C" int vasprintf(char **__restrict__ , const char *__restrict__ , __gnuc_va_list ) throw()
# 400 "/usr/include/stdio.h" 3
 __attribute((__format__(__printf__, 2, 0)));
# 401 "/usr/include/stdio.h" 3
extern "C" int __asprintf(char **__restrict__ , const char *__restrict__ , ...) throw()
# 403 "/usr/include/stdio.h" 3
 __attribute((__format__(__printf__, 2, 3)));
# 404 "/usr/include/stdio.h" 3
extern "C" int asprintf(char **__restrict__ , const char *__restrict__ , ...) throw()
# 406 "/usr/include/stdio.h" 3
 __attribute((__format__(__printf__, 2, 3)));
# 416 "/usr/include/stdio.h" 3
extern "C" int vdprintf(int , const char *__restrict__ , __gnuc_va_list )
# 418 "/usr/include/stdio.h" 3
 __attribute((__format__(__printf__, 2, 0)));
# 419 "/usr/include/stdio.h" 3
extern "C" int dprintf(int , const char *__restrict__ , ...)
# 420 "/usr/include/stdio.h" 3
 __attribute((__format__(__printf__, 2, 3)));
# 429 "/usr/include/stdio.h" 3
extern "C" int fscanf(FILE *__restrict__ , const char *__restrict__ , ...);
# 435 "/usr/include/stdio.h" 3
extern "C" int scanf(const char *__restrict__ , ...);
# 437 "/usr/include/stdio.h" 3
extern "C" int sscanf(const char *__restrict__ , const char *__restrict__ , ...) throw();
# 475 "/usr/include/stdio.h" 3
extern "C" int vfscanf(FILE *__restrict__ , const char *__restrict__ , __gnuc_va_list )
# 477 "/usr/include/stdio.h" 3
 __attribute((__format__(__scanf__, 2, 0)));
# 483 "/usr/include/stdio.h" 3
extern "C" int vscanf(const char *__restrict__ , __gnuc_va_list )
# 484 "/usr/include/stdio.h" 3
 __attribute((__format__(__scanf__, 1, 0)));
# 487 "/usr/include/stdio.h" 3
extern "C" int vsscanf(const char *__restrict__ , const char *__restrict__ , __gnuc_va_list ) throw()
# 489 "/usr/include/stdio.h" 3
 __attribute((__format__(__scanf__, 2, 0)));
# 535 "/usr/include/stdio.h" 3
extern "C" int fgetc(FILE * );
# 536 "/usr/include/stdio.h" 3
extern "C" int getc(FILE * );
# 542 "/usr/include/stdio.h" 3
extern "C" int getchar();
# 554 "/usr/include/stdio.h" 3
extern "C" int getc_unlocked(FILE * );
# 555 "/usr/include/stdio.h" 3
extern "C" int getchar_unlocked();
# 565 "/usr/include/stdio.h" 3
extern "C" int fgetc_unlocked(FILE * );
# 577 "/usr/include/stdio.h" 3
extern "C" int fputc(int , FILE * );
# 578 "/usr/include/stdio.h" 3
extern "C" int putc(int , FILE * );
# 584 "/usr/include/stdio.h" 3
extern "C" int putchar(int );
# 598 "/usr/include/stdio.h" 3
extern "C" int fputc_unlocked(int , FILE * );
# 606 "/usr/include/stdio.h" 3
extern "C" int putc_unlocked(int , FILE * );
# 607 "/usr/include/stdio.h" 3
extern "C" int putchar_unlocked(int );
# 614 "/usr/include/stdio.h" 3
extern "C" int getw(FILE * );
# 617 "/usr/include/stdio.h" 3
extern "C" int putw(int , FILE * );
# 626 "/usr/include/stdio.h" 3
extern "C" char *fgets(char *__restrict__ , int , FILE *__restrict__ );
# 634 "/usr/include/stdio.h" 3
extern "C" char *gets(char * );
# 644 "/usr/include/stdio.h" 3
extern "C" char *fgets_unlocked(char *__restrict__ , int , FILE *__restrict__ );
# 660 "/usr/include/stdio.h" 3
extern "C" __ssize_t __getdelim(char **__restrict__ , size_t *__restrict__ , int , FILE *__restrict__ );
# 663 "/usr/include/stdio.h" 3
extern "C" __ssize_t getdelim(char **__restrict__ , size_t *__restrict__ , int , FILE *__restrict__ );
# 673 "/usr/include/stdio.h" 3
extern "C" __ssize_t getline(char **__restrict__ , size_t *__restrict__ , FILE *__restrict__ );
# 684 "/usr/include/stdio.h" 3
extern "C" int fputs(const char *__restrict__ , FILE *__restrict__ );
# 690 "/usr/include/stdio.h" 3
extern "C" int puts(const char * );
# 697 "/usr/include/stdio.h" 3
extern "C" int ungetc(int , FILE * );
# 704 "/usr/include/stdio.h" 3
extern "C" size_t fread(void *__restrict__ , size_t , size_t , FILE *__restrict__ );
# 710 "/usr/include/stdio.h" 3
extern "C" size_t fwrite(const void *__restrict__ , size_t , size_t , FILE *__restrict__ );
# 721 "/usr/include/stdio.h" 3
extern "C" int fputs_unlocked(const char *__restrict__ , FILE *__restrict__ );
# 732 "/usr/include/stdio.h" 3
extern "C" size_t fread_unlocked(void *__restrict__ , size_t , size_t , FILE *__restrict__ );
# 734 "/usr/include/stdio.h" 3
extern "C" size_t fwrite_unlocked(const void *__restrict__ , size_t , size_t , FILE *__restrict__ );
# 744 "/usr/include/stdio.h" 3
extern "C" int fseek(FILE * , long , int );
# 749 "/usr/include/stdio.h" 3
extern "C" long ftell(FILE * );
# 754 "/usr/include/stdio.h" 3
extern "C" void rewind(FILE * );
# 768 "/usr/include/stdio.h" 3
extern "C" int fseeko(FILE * , __off_t , int );
# 773 "/usr/include/stdio.h" 3
extern "C" __off_t ftello(FILE * );
# 793 "/usr/include/stdio.h" 3
extern "C" int fgetpos(FILE *__restrict__ , fpos_t *__restrict__ );
# 798 "/usr/include/stdio.h" 3
extern "C" int fsetpos(FILE * , const fpos_t * );
# 813 "/usr/include/stdio.h" 3
extern "C" int fseeko64(FILE * , __off64_t , int );
# 814 "/usr/include/stdio.h" 3
extern "C" __off64_t ftello64(FILE * );
# 815 "/usr/include/stdio.h" 3
extern "C" int fgetpos64(FILE *__restrict__ , fpos64_t *__restrict__ );
# 816 "/usr/include/stdio.h" 3
extern "C" int fsetpos64(FILE * , const fpos64_t * );
# 821 "/usr/include/stdio.h" 3
extern "C" void clearerr(FILE * ) throw();
# 823 "/usr/include/stdio.h" 3
extern "C" int feof(FILE * ) throw();
# 825 "/usr/include/stdio.h" 3
extern "C" int ferror(FILE * ) throw();
# 830 "/usr/include/stdio.h" 3
extern "C" void clearerr_unlocked(FILE * ) throw();
# 831 "/usr/include/stdio.h" 3
extern "C" int feof_unlocked(FILE * ) throw();
# 832 "/usr/include/stdio.h" 3
extern "C" int ferror_unlocked(FILE * ) throw();
# 841 "/usr/include/stdio.h" 3
extern "C" void perror(const char * );
# 27 "/usr/include/bits/sys_errlist.h" 3
extern "C" { extern int sys_nerr; }
# 28 "/usr/include/bits/sys_errlist.h" 3
extern "C" { extern const char *const sys_errlist[]; }
# 31 "/usr/include/bits/sys_errlist.h" 3
extern "C" { extern int _sys_nerr; }
# 32 "/usr/include/bits/sys_errlist.h" 3
extern "C" { extern const char *const _sys_errlist[]; }
# 853 "/usr/include/stdio.h" 3
extern "C" int fileno(FILE * ) throw();
# 858 "/usr/include/stdio.h" 3
extern "C" int fileno_unlocked(FILE * ) throw();
# 868 "/usr/include/stdio.h" 3
extern "C" FILE *popen(const char * , const char * );
# 874 "/usr/include/stdio.h" 3
extern "C" int pclose(FILE * );
# 880 "/usr/include/stdio.h" 3
extern "C" char *ctermid(char * ) throw();
# 886 "/usr/include/stdio.h" 3
extern "C" char *cuserid(char * );
# 891 "/usr/include/stdio.h" 3
struct obstack;
# 894 "/usr/include/stdio.h" 3
extern "C" int obstack_printf(obstack *__restrict__ , const char *__restrict__ , ...) throw()
# 896 "/usr/include/stdio.h" 3
 __attribute((__format__(__printf__, 2, 3)));
# 897 "/usr/include/stdio.h" 3
extern "C" int obstack_vprintf(obstack *__restrict__ , const char *__restrict__ , __gnuc_va_list ) throw()
# 900 "/usr/include/stdio.h" 3
 __attribute((__format__(__printf__, 2, 0)));
# 908 "/usr/include/stdio.h" 3
extern "C" void flockfile(FILE * ) throw();
# 912 "/usr/include/stdio.h" 3
extern "C" int ftrylockfile(FILE * ) throw();
# 915 "/usr/include/stdio.h" 3
extern "C" void funlockfile(FILE * ) throw();
# 113 "wsm5.f.cu"
extern "C" int rsl_internal_microclock_();
# 115 "wsm5.f.cu"
extern void wsm5_gpu(float * , float * , float * , float * , float * , float * , float * , float * , float * , float * , float * , float * , float * , float * , float * , float , float * , int , int , int , int , int , int , int , int , int , int , int , int , int , int , int , int , int , int );
# 135 "wsm5.f.cu"
extern "C" int gethostname(char * , size_t );
# 136 "wsm5.f.cu"
extern "C" void bzero(void * , size_t );
# 137 "wsm5.f.cu"
extern "C" char *strcpy(char * , const char * );
# 142 "wsm5.f.cu"
extern "C" { int wsm5_gpu_init_(int *myproc, int *nproc, int *mydevice)
# 143 "wsm5.f.cu"
{
# 144 "wsm5.f.cu"
float x, *x_d;
# 145 "wsm5.f.cu"
int s, e;
# 146 "wsm5.f.cu"
int i, dc, m;
# 147 "wsm5.f.cu"
cudaError_t cerr;
# 148 "wsm5.f.cu"
char hostname[64];
# 149 "wsm5.f.cu"
cudaDeviceProp dp;
# 151 "wsm5.f.cu"
cudaGetDeviceCount(&dc);
# 152 "wsm5.f.cu"
if (dc > 4)
# 153 "wsm5.f.cu"
{ fprintf(stderr, "warning: more than %d devices on node (%d)\n", 4, dc); dc = 4; }
# 154 "wsm5.f.cu"
fprintf(stderr, "Number of devices on this node: %d\n", dc);
# 158 "wsm5.f.cu"
i = (*mydevice);
# 159 "wsm5.f.cu"
if (dc > 0)
# 160 "wsm5.f.cu"
{
# 161 "wsm5.f.cu"
if (cerr = cudaSetDevice(i)) {
# 162 "wsm5.f.cu"
fprintf(stderr, "    non-zero cerr %d\n", cerr);
# 163 "wsm5.f.cu"
}
# 164 "wsm5.f.cu"
}
# 165 "wsm5.f.cu"
gethostname(hostname, 64);
# 166 "wsm5.f.cu"
fprintf(stderr, "Setting device %02d for task %03d on host %s\n", i, *myproc, hostname);
# 168 "wsm5.f.cu"
if (cerr = cudaGetDeviceProperties(&dp, i)) {
# 169 "wsm5.f.cu"
fprintf(stderr, "Device %02d: cerr = %d\n", cerr);
# 170 "wsm5.f.cu"
} else {
# 171 "wsm5.f.cu"
fprintf(stderr, "Device %02d: name %s\n", i, dp.name);
# 172 "wsm5.f.cu"
fprintf(stderr, "Device %02d: mem       %d\n", i, dp.totalGlobalMem);
# 173 "wsm5.f.cu"
fprintf(stderr, "Device %02d: smem      %d\n", i, dp.sharedMemPerBlock);
# 174 "wsm5.f.cu"
fprintf(stderr, "Device %02d: nreg      %d\n", i, dp.regsPerBlock);
# 175 "wsm5.f.cu"
fprintf(stderr, "Device %02d: warp      %d\n", i, dp.warpSize);
# 176 "wsm5.f.cu"
fprintf(stderr, "Device %02d: pitch     %d\n", i, dp.memPitch);
# 177 "wsm5.f.cu"
fprintf(stderr, "Device %02d: maxthrds  %d\n", i, dp.maxThreadsPerBlock);
# 178 "wsm5.f.cu"
fprintf(stderr, "Device %02d: maxtdim   %d %d %d\n", i, (dp.maxThreadsDim)[0], (dp.maxThreadsDim)[1], (dp.maxThreadsDim)[2]);
# 181 "wsm5.f.cu"
fprintf(stderr, "Device %02d: maxgdim   %d %d %d\n", i, (dp.maxGridSize)[0], (dp.maxGridSize)[1], (dp.maxGridSize)[2]);
# 184 "wsm5.f.cu"
fprintf(stderr, "Device %02d: clock     %d\n", i, dp.clockRate);
# 185 "wsm5.f.cu"
fprintf(stderr, "Device %02d: talign    %d\n", i, dp.textureAlignment);
# 186 "wsm5.f.cu"
}
# 189 "wsm5.f.cu"
s = rsl_internal_microclock_();
# 190 "wsm5.f.cu"
cudaMalloc((void **)(&x_d), sizeof(float));
# 191 "wsm5.f.cu"
cudaMemcpy(x_d, &x, sizeof(float), cudaMemcpyHostToDevice);
# 192 "wsm5.f.cu"
cudaFree(x_d);
# 193 "wsm5.f.cu"
e = rsl_internal_microclock_();
# 194 "wsm5.f.cu"
fprintf(stderr, "wsm5_init: %d\n", e - s);
# 195 "wsm5.f.cu"
return 0;
# 196 "wsm5.f.cu"
} }
# 199 "wsm5.f.cu"
extern "C" { int wsm5_host_(float *
# 200 "wsm5.f.cu"
th, float *pii, float *
# 201 "wsm5.f.cu"
q, float *
# 202 "wsm5.f.cu"
qc, float *qi, float *qr, float *qs, float *
# 203 "wsm5.f.cu"
den, float *p, float *delz, float *
# 207 "wsm5.f.cu"
delt, float *
# 208 "wsm5.f.cu"
rain, float *rainncv, float *
# 209 "wsm5.f.cu"
sr, float *
# 210 "wsm5.f.cu"
snow, float *snowncv, int *
# 211 "wsm5.f.cu"
ids, int *ide, int *jds, int *jde, int *kds, int *kde, int *
# 212 "wsm5.f.cu"
ims, int *ime, int *jms, int *jme, int *kms, int *kme, int *
# 213 "wsm5.f.cu"
ips, int *ipe, int *jps, int *jpe, int *kps, int *kpe)
# 215 "wsm5.f.cu"
{
# 216 "wsm5.f.cu"
int i, j, k;
# 217 "wsm5.f.cu"
float *bigbuf;
# 218 "wsm5.f.cu"
int s, e, s1, e1, s2, e2;
# 219 "wsm5.f.cu"
int d3 = (((((*ime) - (*ims)) + 1) * (((*jme) - (*jms)) + 1)) * (((*kme) - (*kms)) + 1));
# 220 "wsm5.f.cu"
int d2 = ((((*ime) - (*ims)) + 1) * (((*jme) - (*jms)) + 1));
# 229 "wsm5.f.cu"
int dips = 0; int dipe = (((*ipe) - (*ips)) + 1);
# 231 "wsm5.f.cu"
int djps = 0; int djpe = (((*jpe) - (*jps)) + 1);
# 232 "wsm5.f.cu"
int dkps = 0; int dkpe = (((*kpe) - (*kps)) + 1);
# 234 "wsm5.f.cu"
bigbuf = ((float *)malloc(((dipe * djpe) * dkpe) * sizeof(float)));
# 241 "wsm5.f.cu"
s = rsl_internal_microclock_();
# 242 "wsm5.f.cu"
float *th_d; cudaMalloc((void **)(&th_d), d3 * sizeof(float)); cudaMemcpy(th_d, th, d3 * sizeof(float), cudaMemcpyHostToDevice); ;
# 243 "wsm5.f.cu"
float *pii_d; cudaMalloc((void **)(&pii_d), d3 * sizeof(float)); cudaMemcpy(pii_d, pii, d3 * sizeof(float), cudaMemcpyHostToDevice); ;
# 244 "wsm5.f.cu"
float *q_d; cudaMalloc((void **)(&q_d), d3 * sizeof(float)); cudaMemcpy(q_d, q, d3 * sizeof(float), cudaMemcpyHostToDevice); ;
# 245 "wsm5.f.cu"
float *qc_d; cudaMalloc((void **)(&qc_d), d3 * sizeof(float)); cudaMemcpy(qc_d, qc, d3 * sizeof(float), cudaMemcpyHostToDevice); ;
# 246 "wsm5.f.cu"
float *qi_d; cudaMalloc((void **)(&qi_d), d3 * sizeof(float)); cudaMemcpy(qi_d, qi, d3 * sizeof(float), cudaMemcpyHostToDevice); ;
# 247 "wsm5.f.cu"
float *qr_d; cudaMalloc((void **)(&qr_d), d3 * sizeof(float)); cudaMemcpy(qr_d, qr, d3 * sizeof(float), cudaMemcpyHostToDevice); ;
# 248 "wsm5.f.cu"
float *qs_d; cudaMalloc((void **)(&qs_d), d3 * sizeof(float)); cudaMemcpy(qs_d, qs, d3 * sizeof(float), cudaMemcpyHostToDevice); ;
# 249 "wsm5.f.cu"
float *den_d; cudaMalloc((void **)(&den_d), d3 * sizeof(float)); cudaMemcpy(den_d, den, d3 * sizeof(float), cudaMemcpyHostToDevice); ;
# 250 "wsm5.f.cu"
float *p_d; cudaMalloc((void **)(&p_d), d3 * sizeof(float)); cudaMemcpy(p_d, p, d3 * sizeof(float), cudaMemcpyHostToDevice); ;
# 251 "wsm5.f.cu"
float *delz_d; cudaMalloc((void **)(&delz_d), d3 * sizeof(float)); cudaMemcpy(delz_d, delz, d3 * sizeof(float), cudaMemcpyHostToDevice); ;
# 255 "wsm5.f.cu"
float *rain_d; cudaMalloc((void **)(&rain_d), d2 * sizeof(float)); cudaMemcpy(rain_d, rain, d2 * sizeof(float), cudaMemcpyHostToDevice); ;
# 256 "wsm5.f.cu"
float *rainncv_d; cudaMalloc((void **)(&rainncv_d), d2 * sizeof(float)); cudaMemcpy(rainncv_d, rainncv, d2 * sizeof(float), cudaMemcpyHostToDevice); ;
# 257 "wsm5.f.cu"
float *sr_d; cudaMalloc((void **)(&sr_d), d2 * sizeof(float)); cudaMemcpy(sr_d, sr, d2 * sizeof(float), cudaMemcpyHostToDevice); ;
# 258 "wsm5.f.cu"
float *snow_d; cudaMalloc((void **)(&snow_d), d2 * sizeof(float)); cudaMemcpy(snow_d, snow, d2 * sizeof(float), cudaMemcpyHostToDevice); ;
# 259 "wsm5.f.cu"
float *snowncv_d; cudaMalloc((void **)(&snowncv_d), d2 * sizeof(float)); cudaMemcpy(snowncv_d, snowncv, d2 * sizeof(float), cudaMemcpyHostToDevice); ;
# 260 "wsm5.f.cu"
float retvals[100];
# 261 "wsm5.f.cu"
{ int k;
# 262 "wsm5.f.cu"
for (k = 0; k < (((*kme) - (*kms)) + 1); k++) { ((retvals)[k]) = ((0.0)); }
# 263 "wsm5.f.cu"
}
# 264 "wsm5.f.cu"
float *retvals_d; cudaMalloc((void **)(&retvals_d), (((*kme) - (*kms)) + 1) * sizeof(float)); cudaMemcpy(retvals_d, retvals, (((*kme) - (*kms)) + 1) * sizeof(float), cudaMemcpyHostToDevice); ;
# 266 "wsm5.f.cu"
int remx, remy;
# 268 "wsm5.f.cu"
remx = ((((((*ipe) - (*ips)) + 1) % 8) != 0) ? 1 : 0);
# 269 "wsm5.f.cu"
remy = ((((((*jpe) - (*jps)) + 1) % 8) != 0) ? 1 : 0);
# 271 "wsm5.f.cu"
dim3 dimBlock(8, 8);
# 273 "wsm5.f.cu"
dim3 dimGrid(((((*ipe) - (*ips)) + 1) / 8) + remx, ((((*jpe) - (*jps)) + 1) / 8) + remy);
# 275 "wsm5.f.cu"
fprintf(stderr, "Call to wsm5_gpu: block dims %d %d\n", dimBlock.x, dimBlock.y);
# 276 "wsm5.f.cu"
fprintf(stderr, "Call to wsm5_gpu: grid  dims %d %d\n", dimGrid.x, dimGrid.y);
# 284 "wsm5.f.cu"
s2 = rsl_internal_microclock_();
# 285 "wsm5.f.cu"
cudaConfigureCall(dimGrid, dimBlock) ? ((void)0) : wsm5_gpu(th_d, pii_d, q_d, qc_d, qi_d, qr_d, qs_d, den_d, p_d, delz_d, rain_d, rainncv_d, sr_d, snow_d, snowncv_d, *delt, retvals_d, dips + 1, ((*ipe) - (*ips)) + 1, djps + 1, ((*jpe) - (*jps)) + 1, dkps + 1, ((*kpe) - (*kps)) + 1, dips + 1, dipe, djps + 1, djpe, dkps + 1, dkpe, dips + 1, dipe, djps + 1, djpe, dkps + 1, dkpe);
# 299 "wsm5.f.cu"
cudaThreadSynchronize();
# 300 "wsm5.f.cu"
e2 = rsl_internal_microclock_();
# 301 "wsm5.f.cu"
fprintf(stderr, "Call to wsm5_gpu (not including data xfer): %d microseconds\n", e2 - s2);
# 304 "wsm5.f.cu"
cudaMemcpy(th, th_d, d3 * sizeof(float), cudaMemcpyDeviceToHost); ;
# 305 "wsm5.f.cu"
cudaMemcpy(pii, pii_d, d3 * sizeof(float), cudaMemcpyDeviceToHost); ;
# 306 "wsm5.f.cu"
cudaMemcpy(q, q_d, d3 * sizeof(float), cudaMemcpyDeviceToHost); ;
# 307 "wsm5.f.cu"
cudaMemcpy(qc, qc_d, d3 * sizeof(float), cudaMemcpyDeviceToHost); ;
# 308 "wsm5.f.cu"
cudaMemcpy(qi, qi_d, d3 * sizeof(float), cudaMemcpyDeviceToHost); ;
# 309 "wsm5.f.cu"
cudaMemcpy(qr, qr_d, d3 * sizeof(float), cudaMemcpyDeviceToHost); ;
# 310 "wsm5.f.cu"
cudaMemcpy(qs, qs_d, d3 * sizeof(float), cudaMemcpyDeviceToHost); ;
# 314 "wsm5.f.cu"
cudaMemcpy(rain, rain_d, d2 * sizeof(float), cudaMemcpyDeviceToHost); ;
# 315 "wsm5.f.cu"
cudaMemcpy(rainncv, rainncv_d, d2 * sizeof(float), cudaMemcpyDeviceToHost); ;
# 316 "wsm5.f.cu"
cudaMemcpy(sr, sr_d, d2 * sizeof(float), cudaMemcpyDeviceToHost); ;
# 317 "wsm5.f.cu"
cudaMemcpy(snow, snow_d, d2 * sizeof(float), cudaMemcpyDeviceToHost); ;
# 318 "wsm5.f.cu"
cudaMemcpy(snowncv, snowncv_d, d2 * sizeof(float), cudaMemcpyDeviceToHost); ;
# 319 "wsm5.f.cu"
e = rsl_internal_microclock_();
# 321 "wsm5.f.cu"
cudaMemcpy(retvals, retvals_d, (((*kme) - (*kms)) + 1) * sizeof(float), cudaMemcpyDeviceToHost); ;
# 322 "wsm5.f.cu"
fprintf(stderr, "Call to wsm5_gpu (including data xfer): %d microseconds\n", e - s);
# 324 "wsm5.f.cu"
{ int k;
# 327 "wsm5.f.cu"
}
# 329 "wsm5.f.cu"
cudaFree(th_d);
# 330 "wsm5.f.cu"
cudaFree(pii_d);
# 331 "wsm5.f.cu"
cudaFree(q_d);
# 332 "wsm5.f.cu"
cudaFree(qc_d);
# 333 "wsm5.f.cu"
cudaFree(qi_d);
# 334 "wsm5.f.cu"
cudaFree(qr_d);
# 335 "wsm5.f.cu"
cudaFree(qs_d);
# 336 "wsm5.f.cu"
cudaFree(den_d);
# 337 "wsm5.f.cu"
cudaFree(p_d);
# 338 "wsm5.f.cu"
cudaFree(delz_d);
# 342 "wsm5.f.cu"
cudaFree(rain_d);
# 343 "wsm5.f.cu"
cudaFree(rainncv_d);
# 344 "wsm5.f.cu"
cudaFree(sr_d);
# 345 "wsm5.f.cu"
cudaFree(snow_d);
# 346 "wsm5.f.cu"
cudaFree(snowncv_d);
# 347 "wsm5.f.cu"
cudaFree(retvals_d);
# 349 "wsm5.f.cu"
return 0;
# 350 "wsm5.f.cu"
} }
# 470 "wsm5.f.cu"
extern "C" { int get_wsm5_gpu_levels_(int *retval)
# 471 "wsm5.f.cu"
{
# 472 "wsm5.f.cu"
(*retval) = 28;
# 473 "wsm5.f.cu"
} }
# 1 "/tmp/tmpxft_00003075_00000000-4_wsm5.f.compute_10.cudafe1.stub.c"
# 1 "/tmp/tmpxft_00003075_00000000-4_wsm5.f.compute_10.cudafe1.stub.c" 1
# 1 "/home/hangzhang/local/cuda/4.0/bin/../include/crt/host_runtime.h" 1
# 74 "/home/hangzhang/local/cuda/4.0/bin/../include/crt/host_runtime.h"
template <typename T>
static inline void *__cudaAddressOf(T &val)
{
    return (void *)(&(const_cast<char &>(reinterpret_cast<const volatile char &>(val))));
}
# 103 "/home/hangzhang/local/cuda/4.0/bin/../include/crt/host_runtime.h"
extern "C" {

extern void** __cudaRegisterFatBinary(
  void *fatCubin
);

extern void __cudaUnregisterFatBinary(
  void **fatCubinHandle
);

extern void __cudaRegisterVar(
        void **fatCubinHandle,
        char *hostVar,
        char *deviceAddress,
  const char *deviceName,
        int ext,
        int size,
        int constant,
        int global
);

extern void __cudaRegisterTexture(
        void **fatCubinHandle,
  const struct textureReference *hostVar,
  const void **deviceAddress,
  const char *deviceName,
        int dim,
        int norm,
        int ext
);

extern void __cudaRegisterSurface(
        void **fatCubinHandle,
  const struct surfaceReference *hostVar,
  const void **deviceAddress,
  const char *deviceName,
        int dim,
        int ext
);

extern void __cudaRegisterFunction(
        void **fatCubinHandle,
  const char *hostFun,
        char *deviceFun,
  const char *deviceName,
        int thread_limit,
        uint3 *tid,
        uint3 *bid,
        dim3 *bDim,
        dim3 *gDim,
        int *wSize
);



extern int atexit(void(*)(void)) throw();







}

static void **__cudaFatCubinHandle;

static void __cudaUnregisterBinaryUtil(void)
{
  __cudaUnregisterFatBinary(__cudaFatCubinHandle);
}

# 1 "/home/hangzhang/local/cuda/4.0/bin/../include/common_functions.h" 1
# 147 "/home/hangzhang/local/cuda/4.0/bin/../include/common_functions.h"
# 1 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h" 1 3
# 1064 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h" 3
# 1 "/home/hangzhang/local/cuda/4.0/bin/../include/math_constants.h" 1 3
# 1065 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h" 2 3
# 3135 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h" 3
# 1 "/home/hangzhang/local/cuda/4.0/bin/../include/crt/func_macro.h" 1 3
# 3136 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h" 2 3
# 4849 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h" 3
inline double rsqrt(double a)
{
  return 1.0 / sqrt(a);
}

inline double rcbrt(double a)
{
  double s, t;

  if (__isnan(a)) {
    return a + a;
  }
  if (a == 0.0 || __isinf(a)) {
    return 1.0 / a;
  }
  s = fabs(a);
  t = exp2(-3.3333333333333333e-1 * log2(s));
  t = ((t*t) * (-s*t) + 1.0) * (3.3333333333333333e-1*t) + t;



  if (__signbit(a))

  {
    t = -t;
  }
  return t;
}

inline double sinpi(double a)
{
  int n;

  if (__isnan(a)) {
    return a + a;
  }
  if (a == 0.0 || __isinf(a)) {
    return sin (a);
  }
  if (a == floor(a)) {
    return ((a / 1.0e308) / 1.0e308) / 1.0e308;
  }
  a = remquo (a, 0.5, &n);
  a = a * 3.1415926535897931e+0;
  if (n & 1) {
    a = cos (a);
  } else {
    a = sin (a);
  }
  if (n & 2) {
    a = -a;
  }
  return a;
}

inline double cospi(double a)
{
  int n;

  if (__isnan(a)) {
    return a + a;
  }
  if (__isinf(a)) {
    return cos (a);
  }
  if (fabs(a) > 9.0071992547409920e+015) {
    a = 0.0;
  }
  a = remquo (a, 0.5, &n);
  a = a * 3.1415926535897931e+0;
  n++;
  if (n & 1) {
    a = cos (a);
  } else {
    a = sin (a);
  }
  if (n & 2) {
    a = -a;
  }
  if (a == 0.0) {
    a = fabs(a);
  }
  return a;
}

inline double erfinv(double a)
{
  double p, q, t, fa;
  volatile union {
    double d;
    unsigned long long int l;
  } cvt;

  fa = fabs(a);
  if (fa >= 1.0) {
    cvt.l = 0xfff8000000000000ull;
    t = cvt.d;
    if (fa == 1.0) {
      t = a * exp(1000.0);
    }
  } else if (fa >= 0.9375) {




    t = log1p(-fa);
    t = 1.0 / sqrt(-t);
    p = 2.7834010353747001060e-3;
    p = p * t + 8.6030097526280260580e-1;
    p = p * t + 2.1371214997265515515e+0;
    p = p * t + 3.1598519601132090206e+0;
    p = p * t + 3.5780402569085996758e+0;
    p = p * t + 1.5335297523989890804e+0;
    p = p * t + 3.4839207139657522572e-1;
    p = p * t + 5.3644861147153648366e-2;
    p = p * t + 4.3836709877126095665e-3;
    p = p * t + 1.3858518113496718808e-4;
    p = p * t + 1.1738352509991666680e-6;
    q = t + 2.2859981272422905412e+0;
    q = q * t + 4.3859045256449554654e+0;
    q = q * t + 4.6632960348736635331e+0;
    q = q * t + 3.9846608184671757296e+0;
    q = q * t + 1.6068377709719017609e+0;
    q = q * t + 3.5609087305900265560e-1;
    q = q * t + 5.3963550303200816744e-2;
    q = q * t + 4.3873424022706935023e-3;
    q = q * t + 1.3858762165532246059e-4;
    q = q * t + 1.1738313872397777529e-6;
    t = p / (q * t);
    if (a < 0.0) t = -t;
  } else if (fa >= 0.75) {




    t = a * a - .87890625;
    p = .21489185007307062000e+0;
    p = p * t - .64200071507209448655e+1;
    p = p * t + .29631331505876308123e+2;
    p = p * t - .47644367129787181803e+2;
    p = p * t + .34810057749357500873e+2;
    p = p * t - .12954198980646771502e+2;
    p = p * t + .25349389220714893917e+1;
    p = p * t - .24758242362823355486e+0;
    p = p * t + .94897362808681080020e-2;
    q = t - .12831383833953226499e+2;
    q = q * t + .41409991778428888716e+2;
    q = q * t - .53715373448862143349e+2;
    q = q * t + .33880176779595142685e+2;
    q = q * t - .11315360624238054876e+2;
    q = q * t + .20369295047216351160e+1;
    q = q * t - .18611650627372178511e+0;
    q = q * t + .67544512778850945940e-2;
    p = p / q;
    t = a * p;
  } else {




    t = a * a - .5625;
    p = - .23886240104308755900e+2;
    p = p * t + .45560204272689128170e+3;
    p = p * t - .22977467176607144887e+4;
    p = p * t + .46631433533434331287e+4;
    p = p * t - .43799652308386926161e+4;
    p = p * t + .19007153590528134753e+4;
    p = p * t - .30786872642313695280e+3;
    q = t - .83288327901936570000e+2;
    q = q * t + .92741319160935318800e+3;
    q = q * t - .35088976383877264098e+4;
    q = q * t + .59039348134843665626e+4;
    q = q * t - .48481635430048872102e+4;
    q = q * t + .18997769186453057810e+4;
    q = q * t - .28386514725366621129e+3;
    p = p / q;
    t = a * p;
  }
  return t;
}

inline double erfcinv(double a)
{
  double t;
  volatile union {
    double d;
    unsigned long long int l;
  } cvt;

  if (__isnan(a)) {
    return a + a;
  }
  if (a <= 0.0) {
    cvt.l = 0xfff8000000000000ull;
    t = cvt.d;
    if (a == 0.0) {
        t = (1.0 - a) * exp(1000.0);
    }
  }
  else if (a >= 0.0625) {
    t = erfinv (1.0 - a);
  }
  else if (a >= 1e-100) {




    double p, q;
    t = log(a);
    t = 1.0 / sqrt(-t);
    p = 2.7834010353747001060e-3;
    p = p * t + 8.6030097526280260580e-1;
    p = p * t + 2.1371214997265515515e+0;
    p = p * t + 3.1598519601132090206e+0;
    p = p * t + 3.5780402569085996758e+0;
    p = p * t + 1.5335297523989890804e+0;
    p = p * t + 3.4839207139657522572e-1;
    p = p * t + 5.3644861147153648366e-2;
    p = p * t + 4.3836709877126095665e-3;
    p = p * t + 1.3858518113496718808e-4;
    p = p * t + 1.1738352509991666680e-6;
    q = t + 2.2859981272422905412e+0;
    q = q * t + 4.3859045256449554654e+0;
    q = q * t + 4.6632960348736635331e+0;
    q = q * t + 3.9846608184671757296e+0;
    q = q * t + 1.6068377709719017609e+0;
    q = q * t + 3.5609087305900265560e-1;
    q = q * t + 5.3963550303200816744e-2;
    q = q * t + 4.3873424022706935023e-3;
    q = q * t + 1.3858762165532246059e-4;
    q = q * t + 1.1738313872397777529e-6;
    t = p / (q * t);
  }
  else {




    double p, q;
    t = log(a);
    t = 1.0 / sqrt(-t);
    p = 6.9952990607058154858e-1;
    p = p * t + 1.9507620287580568829e+0;
    p = p * t + 8.2810030904462690216e-1;
    p = p * t + 1.1279046353630280005e-1;
    p = p * t + 6.0537914739162189689e-3;
    p = p * t + 1.3714329569665128933e-4;
    p = p * t + 1.2964481560643197452e-6;
    p = p * t + 4.6156006321345332510e-9;
    p = p * t + 4.5344689563209398450e-12;
    q = t + 1.5771922386662040546e+0;
    q = q * t + 2.1238242087454993542e+0;
    q = q * t + 8.4001814918178042919e-1;
    q = q * t + 1.1311889334355782065e-1;
    q = q * t + 6.0574830550097140404e-3;
    q = q * t + 1.3715891988350205065e-4;
    q = q * t + 1.2964671850944981713e-6;
    q = q * t + 4.6156017600933592558e-9;
    q = q * t + 4.5344687377088206783e-12;
    t = p / (q * t);
  }
  return t;
}

inline float rsqrtf(float a)
{
  return (float)rsqrt((double)a);
}

inline float rcbrtf(float a)
{
  return (float)rcbrt((double)a);
}

inline float sinpif(float a)
{
  return (float)sinpi((double)a);
}

inline float cospif(float a)
{
  return (float)cospi((double)a);
}

inline float erfinvf(float a)
{
  return (float)erfinv((double)a);
}

inline float erfcinvf(float a)
{
  return (float)erfcinv((double)a);
}







inline int min(int a, int b)
{
  return a < b ? a : b;
}

inline unsigned int umin(unsigned int a, unsigned int b)
{
  return a < b ? a : b;
}

inline long long int llmin(long long int a, long long int b)
{
  return a < b ? a : b;
}

inline unsigned long long int ullmin(unsigned long long int a, unsigned long long int b)
{
  return a < b ? a : b;
}

inline int max(int a, int b)
{
  return a > b ? a : b;
}

inline unsigned int umax(unsigned int a, unsigned int b)
{
  return a > b ? a : b;
}

inline long long int llmax(long long int a, long long int b)
{
  return a > b ? a : b;
}

inline unsigned long long int ullmax(unsigned long long int a, unsigned long long int b)
{
  return a > b ? a : b;
}
# 5201 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h" 3
# 1 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions_dbl_ptx1.h" 1 3
# 5202 "/home/hangzhang/local/cuda/4.0/bin/../include/math_functions.h" 2 3
# 148 "/home/hangzhang/local/cuda/4.0/bin/../include/common_functions.h" 2
# 176 "/home/hangzhang/local/cuda/4.0/bin/../include/crt/host_runtime.h" 2







#pragma pack()
# 2 "/tmp/tmpxft_00003075_00000000-4_wsm5.f.compute_10.cudafe1.stub.c" 2
# 1 "/tmp/tmpxft_00003075_00000000-3_wsm5.f.fatbin.c" 1
asm(
".section .rodata\n"
".align 32\n"
"fatbinData:\n"
".quad 0x00100001ba55ed50,0x0000000000001ae6,0x0000004801000002,0x0000000000000278\n"
".quad 0x0000000000000000,0x0000000a00010002,0x0000000900000038,0x0000000000000015\n"
".quad 0x0000000000000000,0x632e662e356d7377,0x0000000000000075,0x33010102464c457f\n"
".quad 0x0000000000000002,0x0000000100be0002,0x0000000000000000,0x0000000000000208\n"
".quad 0x0000000000000040,0x00380040000a010a,0x0001000400400002,0x0000000000000000\n"
".quad 0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000\n"
".quad 0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000300000001\n"
".quad 0x0000000000000000,0x0000000000000000,0x0000000000000140,0x0000000000000036\n"
".quad 0x0000000000000000,0x0000000000000004,0x0000000000000000,0x000000030000000b\n"
".quad 0x0000000000000000,0x0000000000000000,0x0000000000000176,0x0000000000000001\n"
".quad 0x0000000000000000,0x0000000000000001,0x0000000000000000,0x0000000200000013\n"
".quad 0x0000000000000000,0x0000000000000000,0x0000000000000177,0x0000000000000090\n"
".quad 0x0000000600000002,0x0000000000000001,0x0000000000000018,0x7472747368732e00\n"
".quad 0x747274732e006261,0x746d79732e006261,0x672e766e2e006261,0x6e692e6c61626f6c\n"
".quad 0x672e766e2e007469,0x0000006c61626f6c,0x0000000000000000,0x0000000000000000\n"
".quad 0x0000000000000000,0x0000010003000000,0x0000000000000000,0x0000000000000000\n"
".quad 0x0000020003000000,0x0000000000000000,0x0000000000000000,0x0000030003000000\n"
".quad 0x0000000000000000,0x0000000000000000,0x0000000003000000,0x0000000000000000\n"
".quad 0x0000000000000000,0x0000000003000000,0x0000000000000000,0x0000000000000000\n"
".quad 0x0000000500000006,0x0000000000000208,0x0000000000000000,0x0000000000000000\n"
".quad 0x0000000000000070,0x0000000000000070,0x0000000000000004,0x0000000560000000\n"
".quad 0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000207\n"
".quad 0x0000000000000207,0x0000000000000004,0x0000005001000001,0x0000000000000a61\n"
".quad 0x0000003800000000,0x0000000a00010004,0x0000000900000040,0x0000000000000015\n"
".quad 0x0000000000000000,0x0000000000000000,0x632e662e356d7377,0x0000000000000075\n"
".quad 0x6f69737265762e09,0x2e090a342e31206e,0x7320746567726174,0x616d202c30315f6d\n"
".quad 0x6f745f3436665f70,0x2f2f090a3233665f,0x656c69706d6f6320,0x2f20687469772064\n"
".quad 0x6e61682f32737368,0x6c2f676e61687a67,0x6475632f6c61636f,0x706f2f302e342f61\n"
".quad 0x62696c2f34366e65,0x2f2f090a65622f2f,0x636e65706f766e20,0x756220302e342063\n"
".quad 0x32206e6f20746c69,0x312d35302d313130,0x2d2d2f2f090a0a32,0x2d2d2d2d2d2d2d2d\n"
".quad 0x2d2d2d2d2d2d2d2d,0x2d2d2d2d2d2d2d2d,0x2d2d2d2d2d2d2d2d,0x2d2d2d2d2d2d2d2d\n"
".quad 0x2d2d2d2d2d2d2d2d,0x2d2d2d2d2d2d2d2d,0x6f43202f2f090a2d,0x20676e696c69706d\n"
".quad 0x706d742f706d742f,0x303030305f746678,0x3030305f35373033,0x5f392d3030303030\n"
".quad 0x632e662e356d7377,0x315f657475706d6f,0x692e337070632e30,0x632f706d742f2820\n"
".quad 0x7a63782e23494263,0x2f2f090a2932706b,0x2d2d2d2d2d2d2d2d,0x2d2d2d2d2d2d2d2d\n"
".quad 0x2d2d2d2d2d2d2d2d,0x2d2d2d2d2d2d2d2d,0x2d2d2d2d2d2d2d2d,0x2d2d2d2d2d2d2d2d\n"
".quad 0x2d2d2d2d2d2d2d2d,0x2f2f090a0a2d2d2d,0x2d2d2d2d2d2d2d2d,0x2d2d2d2d2d2d2d2d\n"
".quad 0x2d2d2d2d2d2d2d2d,0x2d2d2d2d2d2d2d2d,0x2d2d2d2d2d2d2d2d,0x2d2d2d2d2d2d2d2d\n"
".quad 0x2d2d2d2d2d2d2d2d,0x202f2f090a2d2d2d,0x3a736e6f6974704f,0x2d2d2d2d2f2f090a\n"
".quad 0x2d2d2d2d2d2d2d2d,0x2d2d2d2d2d2d2d2d,0x2d2d2d2d2d2d2d2d,0x2d2d2d2d2d2d2d2d\n"
".quad 0x2d2d2d2d2d2d2d2d,0x2d2d2d2d2d2d2d2d,0x0a2d2d2d2d2d2d2d,0x72615420202f2f09\n"
".quad 0x2c7874703a746567,0x5f6d733a41534920,0x69646e45202c3031,0x6c7474696c3a6e61\n"
".quad 0x746e696f50202c65,0x3a657a6953207265,0x20202f2f090a3436,0x74704f2809334f2d\n"
".quad 0x6f6974617a696d69,0x296c6576656c206e,0x672d20202f2f090a,0x6775626544280930\n"
".quad 0x0a296c6576656c20,0x326d2d20202f2f09,0x74726f7065522809,0x726f736976646120\n"
".quad 0x2f2f090a29736569,0x2d2d2d2d2d2d2d2d,0x2d2d2d2d2d2d2d2d,0x2d2d2d2d2d2d2d2d\n"
".quad 0x2d2d2d2d2d2d2d2d,0x2d2d2d2d2d2d2d2d,0x2d2d2d2d2d2d2d2d,0x2d2d2d2d2d2d2d2d\n"
".quad 0x662e090a0a2d2d2d,0x3c22093109656c69,0x2d646e616d6d6f63,0x090a223e656e696c\n"
".quad 0x093209656c69662e,0x6d742f706d742f22,0x3030305f74667870,0x30305f3537303330\n"
".quad 0x382d303030303030,0x2e662e356d73775f,0x5f657475706d6f63,0x66616475632e3031\n"
".quad 0x0a227570672e3265,0x3309656c69662e09,0x6c2f7273752f2209,0x782f6363672f6269\n"
".quad 0x65722d34365f3638,0x6e696c2d74616864,0x362e342e342f7875,0x6564756c636e692f\n"
".quad 0x2e6665646474732f,0x6c69662e090a2268,0x6f682f2209340965,0x7a676e61682f656d\n"
".quad 0x636f6c2f676e6168,0x2f616475632f6c61,0x2f6e69622f302e34,0x756c636e692f2e2e\n"
".quad 0x642f7472632f6564,0x75725f6563697665,0x22682e656d69746e,0x09656c69662e090a\n"
".quad 0x656d6f682f220935,0x61687a676e61682f,0x6c61636f6c2f676e,0x2e342f616475632f\n"
".quad 0x2e2e2f6e69622f30,0x6564756c636e692f,0x65645f74736f682f,0x22682e73656e6966\n"
".quad 0x09656c69662e090a,0x656d6f682f220936,0x61687a676e61682f,0x6c61636f6c2f676e\n"
".quad 0x2e342f616475632f,0x2e2e2f6e69622f30,0x6564756c636e692f,0x6e69746c6975622f\n"
".quad 0x682e73657079745f,0x656c69662e090a22,0x6d6f682f22093709,0x687a676e61682f65\n"
".quad 0x61636f6c2f676e61,0x342f616475632f6c,0x2e2f6e69622f302e,0x64756c636e692f2e\n"
".quad 0x6563697665642f65,0x682e73657079745f,0x656c69662e090a22,0x6d6f682f22093809\n"
".quad 0x687a676e61682f65,0x61636f6c2f676e61,0x342f616475632f6c,0x2e2f6e69622f302e\n"
".quad 0x64756c636e692f2e,0x7265766972642f65,0x682e73657079745f,0x656c69662e090a22\n"
".quad 0x6d6f682f22093909,0x687a676e61682f65,0x61636f6c2f676e61,0x342f616475632f6c\n"
".quad 0x2e2f6e69622f302e,0x64756c636e692f2e,0x6361667275732f65,0x2e73657079745f65\n"
".quad 0x6c69662e090a2268,0x682f220930310965,0x676e61682f656d6f,0x6f6c2f676e61687a\n"
".quad 0x616475632f6c6163,0x6e69622f302e342f,0x6c636e692f2e2e2f,0x747865742f656475\n"
".quad 0x657079745f657275,0x662e090a22682e73,0x2209313109656c69,0x61682f656d6f682f\n"
".quad 0x2f676e61687a676e,0x75632f6c61636f6c,0x622f302e342f6164,0x6e692f2e2e2f6e69\n"
".quad 0x65762f6564756c63,0x7079745f726f7463,0x2e090a22682e7365,0x09323109656c6966\n"
".quad 0x682f656d6f682f22,0x676e61687a676e61,0x632f6c61636f6c2f,0x2f302e342f616475\n"
".quad 0x692f2e2e2f6e6962,0x642f6564756c636e,0x616c5f6563697665,0x7261705f68636e75\n"
".quad 0x2e73726574656d61,0x6c69662e090a2268,0x682f220933310965,0x676e61682f656d6f\n"
".quad 0x6f6c2f676e61687a,0x616475632f6c6163,0x6e69622f302e342f,0x6c636e692f2e2e2f\n"
".quad 0x2f7472632f656475,0x5f656761726f7473,0x22682e7373616c63,0x09656c69662e090a\n"
".quad 0x7273752f22093431,0x6564756c636e692f,0x79742f737469622f,0x090a22682e736570\n"
".quad 0x353109656c69662e,0x692f7273752f2209,0x742f6564756c636e,0x090a22682e656d69\n"
".quad 0x363109656c69662e,0x2f656d6f682f2209,0x6e61687a676e6168,0x2f6c61636f6c2f67\n"
".quad 0x302e342f61647563,0x2f2e2e2f6e69622f,0x2f6564756c636e69,0x665f6e6f6d6d6f63\n"
".quad 0x736e6f6974636e75,0x69662e090a22682e,0x2f2209373109656c,0x6e61682f656d6f68\n"
".quad 0x6c2f676e61687a67,0x6475632f6c61636f,0x69622f302e342f61,0x636e692f2e2e2f6e\n"
".quad 0x74616d2f6564756c,0x6974636e75665f68,0x090a22682e736e6f,0x383109656c69662e\n"
".quad 0x2f656d6f682f2209,0x6e61687a676e6168,0x2f6c61636f6c2f67,0x302e342f61647563\n"
".quad 0x2f2e2e2f6e69622f,0x2f6564756c636e69,0x6e6f635f6874616d,0x682e73746e617473\n"
".quad 0x656c69662e090a22,0x6f682f2209393109,0x7a676e61682f656d,0x636f6c2f676e6168\n"
".quad 0x2f616475632f6c61,0x2f6e69622f302e34,0x756c636e692f2e2e,0x63697665642f6564\n"
".quad 0x6974636e75665f65,0x090a22682e736e6f,0x303209656c69662e,0x2f656d6f682f2209\n"
".quad 0x6e61687a676e6168,0x2f6c61636f6c2f67,0x302e342f61647563,0x2f2e2e2f6e69622f\n"
".quad 0x2f6564756c636e69,0x74615f31315f6d73,0x6e75665f63696d6f,0x682e736e6f697463\n"
".quad 0x656c69662e090a22,0x6f682f2209313209,0x7a676e61682f656d,0x636f6c2f676e6168\n"
".quad 0x2f616475632f6c61,0x2f6e69622f302e34,0x756c636e692f2e2e,0x32315f6d732f6564\n"
".quad 0x5f63696d6f74615f,0x6e6f6974636e7566,0x662e090a22682e73,0x2209323209656c69\n"
".quad 0x61682f656d6f682f,0x2f676e61687a676e,0x75632f6c61636f6c,0x622f302e342f6164\n"
".quad 0x6e692f2e2e2f6e69,0x6d732f6564756c63,0x62756f645f33315f,0x74636e75665f656c\n"
".quad 0x0a22682e736e6f69,0x3209656c69662e09,0x656d6f682f220933,0x61687a676e61682f\n"
".quad 0x6c61636f6c2f676e,0x2e342f616475632f,0x2e2e2f6e69622f30,0x6564756c636e692f\n"
".quad 0x615f30325f6d732f,0x75665f63696d6f74,0x2e736e6f6974636e,0x6c69662e090a2268\n"
".quad 0x682f220934320965,0x676e61682f656d6f,0x6f6c2f676e61687a,0x616475632f6c6163\n"
".quad 0x6e69622f302e342f,0x6c636e692f2e2e2f,0x325f6d732f656475,0x6e6972746e695f30\n"
".quad 0x0a22682e73636973,0x3209656c69662e09,0x656d6f682f220935,0x61687a676e61682f\n"
".quad 0x6c61636f6c2f676e,0x2e342f616475632f,0x2e2e2f6e69622f30,0x6564756c636e692f\n"
".quad 0x656361667275732f,0x6f6974636e75665f,0x2e090a22682e736e,0x09363209656c6966\n"
".quad 0x682f656d6f682f22,0x676e61687a676e61,0x632f6c61636f6c2f,0x2f302e342f616475\n"
".quad 0x692f2e2e2f6e6962,0x742f6564756c636e,0x665f657275747865,0x6e75665f68637465\n"
".quad 0x682e736e6f697463,0x656c69662e090a22,0x6f682f2209373209,0x7a676e61682f656d\n"
".quad 0x636f6c2f676e6168,0x2f616475632f6c61,0x2f6e69622f302e34,0x756c636e692f2e2e\n"
".quad 0x5f6874616d2f6564,0x6e6f6974636e7566,0x74705f6c62645f73,0x0a0a0a22682e3178\n"
".quad 0x0000480100000200,0x0000000000027800,0x0000000000000000,0x0000140001000400\n"
".quad 0x0000090000003800,0x0000000000001500,0x0000000000000000,0x2e662e356d737700\n"
".quad 0x0000000000007563,0x010102464c457f00,0x0000000000000433,0x00000100be000200\n"
".quad 0x0000000000000000,0x0000000000020800,0x0000000000004000,0x3800400014011400\n"
".quad 0x0100040040000200,0x0000000000000000,0x0000000000000000,0x0000000000000000\n"
".quad 0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000\n"
".quad 0x0000000000000000,0x0000030000000100,0x0000000000000000,0x0000000000000000\n"
".quad 0x0000000000014000,0x0000000000003600,0x0000000000000000,0x0000000000000400\n"
".quad 0x0000000000000000,0x0000030000000b00,0x0000000000000000,0x0000000000000000\n"
".quad 0x0000000000017600,0x0000000000000100,0x0000000000000000,0x0000000000000100\n"
".quad 0x0000000000000000,0x0000020000001300,0x0000000000000000,0x0000000000000000\n"
".quad 0x0000000000017700,0x0000000000009000,0x0000060000000200,0x0000000000000100\n"
".quad 0x0000000000001800,0x72747368732e0000,0x7274732e00626174,0x6d79732e00626174\n"
".quad 0x2e766e2e00626174,0x692e6c61626f6c67,0x2e766e2e0074696e,0x00006c61626f6c67\n"
".quad 0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0001000300000000\n"
".quad 0x0000000000000000,0x0000000000000000,0x0002000300000000,0x0000000000000000\n"
".quad 0x0000000000000000,0x0003000300000000,0x0000000000000000,0x0000000000000000\n"
".quad 0x0000000300000000,0x0000000000000000,0x0000000000000000,0x0000000300000000\n"
".quad 0x0000000000000000,0x0000000000000000,0x0000050000000600,0x0000000000020800\n"
".quad 0x0000000000000000,0x0000000000000000,0x0000000000007000,0x0000000000007000\n"
".quad 0x0000000000000400,0x0000056000000000,0x0000000000000000,0x0000000000000000\n"
".quad 0x0000000000000000,0x0000000000020700,0x0000000000020700,0x0000000000000400\n"
".quad 0x0000500100000100,0x00000000000a6500,0x0000380000000000,0x0000140002000300\n"
".quad 0x0000090000004000,0x0000000000001500,0x0000000000000000,0x0000000000000000\n"
".quad 0x2e662e356d737700,0x0000000000007563,0x69737265762e0900,0x090a332e32206e6f\n"
".quad 0x207465677261742e,0x2e090a30325f6d73,0x5f73736572646461,0x0a343620657a6973\n"
".quad 0x706d6f63202f2f09,0x7469772064656c69,0x2f327373682f2068,0x6e61687a676e6168\n"
".quad 0x2f6c61636f6c2f67,0x302e342f61647563,0x2f34366e65706f2f,0x0a65622f2f62696c\n"
".quad 0x706f766e202f2f09,0x302e342063636e65,0x6f20746c69756220,0x302d31313032206e\n"
".quad 0x2f090a0a32312d35,0x2d2d2d2d2d2d2d2f,0x2d2d2d2d2d2d2d2d,0x2d2d2d2d2d2d2d2d\n"
".quad 0x2d2d2d2d2d2d2d2d,0x2d2d2d2d2d2d2d2d,0x2d2d2d2d2d2d2d2d,0x2d2d2d2d2d2d2d2d\n"
".quad 0x2f2f090a2d2d2d2d,0x696c69706d6f4320,0x2f706d742f20676e,0x305f746678706d74\n"
".quad 0x5f35373033303030,0x3030303030303030,0x356d73775f33312d,0x75706d6f632e662e\n"
".quad 0x70632e30325f6574,0x742f2820692e3370,0x23494263632f706d,0x29736e577056452e\n"
".quad 0x2d2d2d2d2f2f090a,0x2d2d2d2d2d2d2d2d,0x2d2d2d2d2d2d2d2d,0x2d2d2d2d2d2d2d2d\n"
".quad 0x2d2d2d2d2d2d2d2d,0x2d2d2d2d2d2d2d2d,0x2d2d2d2d2d2d2d2d,0x0a2d2d2d2d2d2d2d\n"
".quad 0x2d2d2d2d2f2f090a,0x2d2d2d2d2d2d2d2d,0x2d2d2d2d2d2d2d2d,0x2d2d2d2d2d2d2d2d\n"
".quad 0x2d2d2d2d2d2d2d2d,0x2d2d2d2d2d2d2d2d,0x2d2d2d2d2d2d2d2d,0x0a2d2d2d2d2d2d2d\n"
".quad 0x6974704f202f2f09,0x2f2f090a3a736e6f,0x2d2d2d2d2d2d2d2d,0x2d2d2d2d2d2d2d2d\n"
".quad 0x2d2d2d2d2d2d2d2d,0x2d2d2d2d2d2d2d2d,0x2d2d2d2d2d2d2d2d,0x2d2d2d2d2d2d2d2d\n"
".quad 0x2d2d2d2d2d2d2d2d,0x202f2f090a2d2d2d,0x3a74656772615420,0x415349202c787470\n"
".quad 0x202c30325f6d733a,0x6c3a6e6169646e45,0x50202c656c747469,0x53207265746e696f\n"
".quad 0x090a34363a657a69,0x09334f2d20202f2f,0x7a696d6974704f28,0x656c206e6f697461\n"
".quad 0x2f2f090a296c6576,0x44280930672d2020,0x76656c2067756265,0x202f2f090a296c65\n"
".quad 0x65522809326d2d20,0x7664612074726f70,0x29736569726f7369,0x2d2d2d2d2f2f090a\n"
".quad 0x2d2d2d2d2d2d2d2d,0x2d2d2d2d2d2d2d2d,0x2d2d2d2d2d2d2d2d,0x2d2d2d2d2d2d2d2d\n"
".quad 0x2d2d2d2d2d2d2d2d,0x2d2d2d2d2d2d2d2d,0x0a2d2d2d2d2d2d2d,0x09656c69662e090a\n"
".quad 0x6d6d6f633c220931,0x656e696c2d646e61,0x6c69662e090a223e,0x6d742f2209320965\n"
".quad 0x746678706d742f70,0x373033303030305f,0x3030303030305f35,0x73775f32312d3030\n"
".quad 0x6d6f632e662e356d,0x2e30325f65747570,0x2e32656661647563,0x662e090a22757067\n"
".quad 0x2f22093309656c69,0x2f62696c2f727375,0x5f3638782f636367,0x61686465722d3436\n"
".quad 0x2f78756e696c2d74,0x6e692f362e342e34,0x74732f6564756c63,0x0a22682e66656464\n"
".quad 0x3409656c69662e09,0x2f656d6f682f2209,0x6e61687a676e6168,0x2f6c61636f6c2f67\n"
".quad 0x302e342f61647563,0x2f2e2e2f6e69622f,0x2f6564756c636e69,0x697665642f747263\n"
".quad 0x69746e75725f6563,0x2e090a22682e656d,0x22093509656c6966,0x61682f656d6f682f\n"
".quad 0x2f676e61687a676e,0x75632f6c61636f6c,0x622f302e342f6164,0x6e692f2e2e2f6e69\n"
".quad 0x6f682f6564756c63,0x6e696665645f7473,0x2e090a22682e7365,0x22093609656c6966\n"
".quad 0x61682f656d6f682f,0x2f676e61687a676e,0x75632f6c61636f6c,0x622f302e342f6164\n"
".quad 0x6e692f2e2e2f6e69,0x75622f6564756c63,0x79745f6e69746c69,0x090a22682e736570\n"
".quad 0x093709656c69662e,0x682f656d6f682f22,0x676e61687a676e61,0x632f6c61636f6c2f\n"
".quad 0x2f302e342f616475,0x692f2e2e2f6e6962,0x642f6564756c636e,0x79745f6563697665\n"
".quad 0x090a22682e736570,0x093809656c69662e,0x682f656d6f682f22,0x676e61687a676e61\n"
".quad 0x632f6c61636f6c2f,0x2f302e342f616475,0x692f2e2e2f6e6962,0x642f6564756c636e\n"
".quad 0x79745f7265766972,0x090a22682e736570,0x093909656c69662e,0x682f656d6f682f22\n"
".quad 0x676e61687a676e61,0x632f6c61636f6c2f,0x2f302e342f616475,0x692f2e2e2f6e6962\n"
".quad 0x732f6564756c636e,0x745f656361667275,0x0a22682e73657079,0x3109656c69662e09\n"
".quad 0x656d6f682f220930,0x61687a676e61682f,0x6c61636f6c2f676e,0x2e342f616475632f\n"
".quad 0x2e2e2f6e69622f30,0x6564756c636e692f,0x657275747865742f,0x682e73657079745f\n"
".quad 0x656c69662e090a22,0x6f682f2209313109,0x7a676e61682f656d,0x636f6c2f676e6168\n"
".quad 0x2f616475632f6c61,0x2f6e69622f302e34,0x756c636e692f2e2e,0x6f746365762f6564\n"
".quad 0x2e73657079745f72,0x6c69662e090a2268,0x682f220932310965,0x676e61682f656d6f\n"
".quad 0x6f6c2f676e61687a,0x616475632f6c6163,0x6e69622f302e342f,0x6c636e692f2e2e2f\n"
".quad 0x697665642f656475,0x636e75616c5f6563,0x656d617261705f68,0x0a22682e73726574\n"
".quad 0x3109656c69662e09,0x656d6f682f220933,0x61687a676e61682f,0x6c61636f6c2f676e\n"
".quad 0x2e342f616475632f,0x2e2e2f6e69622f30,0x6564756c636e692f,0x6f74732f7472632f\n"
".quad 0x616c635f65676172,0x2e090a22682e7373,0x09343109656c6966,0x6e692f7273752f22\n"
".quad 0x69622f6564756c63,0x73657079742f7374,0x69662e090a22682e,0x2f2209353109656c\n"
".quad 0x6c636e692f727375,0x656d69742f656475,0x69662e090a22682e,0x2f2209363109656c\n"
".quad 0x6e61682f656d6f68,0x6c2f676e61687a67,0x6475632f6c61636f,0x69622f302e342f61\n"
".quad 0x636e692f2e2e2f6e,0x6d6f632f6564756c,0x636e75665f6e6f6d,0x22682e736e6f6974\n"
".quad 0x09656c69662e090a,0x6d6f682f22093731,0x687a676e61682f65,0x61636f6c2f676e61\n"
".quad 0x342f616475632f6c,0x2e2f6e69622f302e,0x64756c636e692f2e,0x665f6874616d2f65\n"
".quad 0x736e6f6974636e75,0x69662e090a22682e,0x2f2209383109656c,0x6e61682f656d6f68\n"
".quad 0x6c2f676e61687a67,0x6475632f6c61636f,0x69622f302e342f61,0x636e692f2e2e2f6e\n"
".quad 0x74616d2f6564756c,0x6174736e6f635f68,0x090a22682e73746e,0x393109656c69662e\n"
".quad 0x2f656d6f682f2209,0x6e61687a676e6168,0x2f6c61636f6c2f67,0x302e342f61647563\n"
".quad 0x2f2e2e2f6e69622f,0x2f6564756c636e69,0x665f656369766564,0x736e6f6974636e75\n"
".quad 0x69662e090a22682e,0x2f2209303209656c,0x6e61682f656d6f68,0x6c2f676e61687a67\n"
".quad 0x6475632f6c61636f,0x69622f302e342f61,0x636e692f2e2e2f6e,0x5f6d732f6564756c\n"
".quad 0x696d6f74615f3131,0x6974636e75665f63,0x090a22682e736e6f,0x313209656c69662e\n"
".quad 0x2f656d6f682f2209,0x6e61687a676e6168,0x2f6c61636f6c2f67,0x302e342f61647563\n"
".quad 0x2f2e2e2f6e69622f,0x2f6564756c636e69,0x74615f32315f6d73,0x6e75665f63696d6f\n"
".quad 0x682e736e6f697463,0x656c69662e090a22,0x6f682f2209323209,0x7a676e61682f656d\n"
".quad 0x636f6c2f676e6168,0x2f616475632f6c61,0x2f6e69622f302e34,0x756c636e692f2e2e\n"
".quad 0x33315f6d732f6564,0x5f656c62756f645f,0x6e6f6974636e7566,0x662e090a22682e73\n"
".quad 0x2209333209656c69,0x61682f656d6f682f,0x2f676e61687a676e,0x75632f6c61636f6c\n"
".quad 0x622f302e342f6164,0x6e692f2e2e2f6e69,0x6d732f6564756c63,0x6d6f74615f30325f\n"
".quad 0x74636e75665f6369,0x0a22682e736e6f69,0x3209656c69662e09,0x656d6f682f220934\n"
".quad 0x61687a676e61682f,0x6c61636f6c2f676e,0x2e342f616475632f,0x2e2e2f6e69622f30\n"
".quad 0x6564756c636e692f,0x695f30325f6d732f,0x6369736e6972746e,0x662e090a22682e73\n"
".quad 0x2209353209656c69,0x61682f656d6f682f,0x2f676e61687a676e,0x75632f6c61636f6c\n"
".quad 0x622f302e342f6164,0x6e692f2e2e2f6e69,0x75732f6564756c63,0x75665f6563616672\n"
".quad 0x2e736e6f6974636e,0x6c69662e090a2268,0x682f220936320965,0x676e61682f656d6f\n"
".quad 0x6f6c2f676e61687a,0x616475632f6c6163,0x6e69622f302e342f,0x6c636e692f2e2e2f\n"
".quad 0x747865742f656475,0x637465665f657275,0x6974636e75665f68,0x090a22682e736e6f\n"
".quad 0x373209656c69662e,0x2f656d6f682f2209,0x6e61687a676e6168,0x2f6c61636f6c2f67\n"
".quad 0x302e342f61647563,0x2f2e2e2f6e69622f,0x2f6564756c636e69,0x6e75665f6874616d\n"
".quad 0x645f736e6f697463,0x2e337874705f6c62,0x0000000a0a0a2268\n"
".text");

extern "C" {

extern const unsigned long long fatbinData[863];

}


static struct {int m; int v; const unsigned long long* d; char* f;} __fatDeviceText __attribute__ ((aligned (8))) __attribute__ ((section (".nvFatBinSegment")))=
 { 0x466243b1, 1, fatbinData, 0 };
# 3 "/tmp/tmpxft_00003075_00000000-4_wsm5.f.compute_10.cudafe1.stub.c" 2
# 115 "wsm5.f.cu"
extern void __device_stub__Z8wsm5_gpuPfS_S_S_S_S_S_S_S_S_S_S_S_S_S_fS_iiiiiiiiiiiiiiiiii(float *, float *, float *, float *, float *, float *, float *, float *, float *, float *, float *, float *, float *, float *, float *, float, float *, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int);
static void __sti____cudaRegisterAll_52_tmpxft_00003075_00000000_6_wsm5_f_compute_10_cpp1_ii_91788a12(void) __attribute__((__constructor__));
static void __sti____cudaRegisterAll_52_tmpxft_00003075_00000000_6_wsm5_f_compute_10_cpp1_ii_91788a12(void) { __cudaFatCubinHandle = __cudaRegisterFatBinary((void*)&__fatDeviceText); atexit(__cudaUnregisterBinaryUtil); }
# 1 "/tmp/tmpxft_00003075_00000000-4_wsm5.f.compute_10.cudafe1.stub.c" 2
