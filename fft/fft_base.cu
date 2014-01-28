// (C) Copyright 2013 University of Illinois, All Rights Reserved

#include <stdio.h>
#include <cuda.h>
#include "parboil.h"
//#include "ib_sync.cu"

#define CUERR { cudaError_t err; \
  if ((err = cudaGetLastError()) != cudaSuccess) { \
  printf("CUDA error: %s, line %d\n", cudaGetErrorString(err), __LINE__); \
  return -1; }}

#define bx  blockIdx.x
#define by  blockIdx.y
#define tx  threadIdx.x

// Possible values are 2, 4, 8 and 16
#define R 2
//#define SYNC

inline __device__ float2 operator*(float2 a, float2 b) { return make_float2( a.x*b.x-a.y*b.y, a.x*b.y+a.y*b.x ); }
inline __device__ float2 operator+(float2 a, float2 b) { return make_float2( a.x + b.x, a.y + b.y ); }
inline __device__ float2 operator-(float2 a, float2 b) { return make_float2( a.x - b.x, a.y - b.y ); }
inline __device__ float2 operator*(float2 a, float b ) { return make_float2( b*a.x , b*a.y); }

#define COS_PI_8  0.923879533f
#define SIN_PI_8  0.382683432f
#define exp_1_16  make_float2(  COS_PI_8, -SIN_PI_8 )
#define exp_3_16  make_float2(  SIN_PI_8, -COS_PI_8 )
#define exp_5_16  make_float2( -SIN_PI_8, -COS_PI_8 )
#define exp_7_16  make_float2( -COS_PI_8, -SIN_PI_8 )
#define exp_9_16  make_float2( -COS_PI_8,  SIN_PI_8 )
#define exp_1_8   make_float2(  1, -1 )
#define exp_1_4   make_float2(  0, -1 )
#define exp_3_8   make_float2( -1, -1 )
  
__device__ void GPU_FFT2( float2 &v1,float2 &v2 ) { 
  float2 v0 = v1;  
  v1 = v0 + v2; 
  v2 = v0 - v2; 
}

__device__ void GPU_FFT4( float2 &v0,float2 &v1,float2 &v2,float2 &v3) { 
   GPU_FFT2(v0, v2);
   GPU_FFT2(v1, v3);
   v3 = v3 * exp_1_4;
   GPU_FFT2(v0, v1);
   GPU_FFT2(v2, v3);    
}

inline __device__ void GPU_FFT2(float2* v) {
  GPU_FFT2(v[0],v[1]);
}

inline __device__ void GPU_FFT4(float2* v) {
  GPU_FFT4(v[0],v[1],v[2],v[3] );
}

inline __device__ void GPU_FFT8(float2* v) {
  GPU_FFT2(v[0],v[4]);
  GPU_FFT2(v[1],v[5]);
  GPU_FFT2(v[2],v[6]);
  GPU_FFT2(v[3],v[7]);
  v[5]=(v[5]*exp_1_8)*M_SQRT1_2;
  v[6]=v[6]*exp_1_4;
  v[7]=(v[7]*exp_3_8)*M_SQRT1_2;
  GPU_FFT4(v[0],v[1],v[2],v[3]);
  GPU_FFT4(v[4],v[5],v[6],v[7]);
}

inline __device__ void GPU_FFT16( float2 *v ) {
    GPU_FFT4( v[0], v[4], v[8], v[12] );
    GPU_FFT4( v[1], v[5], v[9], v[13] );
    GPU_FFT4( v[2], v[6], v[10], v[14] );
    GPU_FFT4( v[3], v[7], v[11], v[15] );

    v[5]  = (v[5]  * exp_1_8 ) * M_SQRT1_2;
    v[6]  =  v[6]  * exp_1_4;
    v[7]  = (v[7]  * exp_3_8 ) * M_SQRT1_2;
    v[9]  =  v[9]  * exp_1_16;
    v[10] = (v[10] * exp_1_8 ) * M_SQRT1_2;
    v[11] =  v[11] * exp_3_16;
    v[13] =  v[13] * exp_3_16;
    v[14] = (v[14] * exp_3_8 ) * M_SQRT1_2;
    v[15] =  v[15] * exp_9_16;

    GPU_FFT4( v[0],  v[1],  v[2],  v[3] );
    GPU_FFT4( v[4],  v[5],  v[6],  v[7] );
    GPU_FFT4( v[8],  v[9],  v[10], v[11] );
    GPU_FFT4( v[12], v[13], v[14], v[15] );
}
     
__device__ int GPU_expand(int idxL, int N1, int N2 ) { 
  return (idxL/N1)*N1*N2 + (idxL%N1);
}

__device__ void GPU_FftIteration(int j, int Ns, float2* data0, float2* data1, int N) { 
  float2 v[R];
  int idxS = j;
  float angle = -2*M_PI*(j%Ns)/(Ns*R);
  for(int r=0; r<R; r++) {
    v[r] = data0[idxS+r*N/R];
    v[r] = v[r]*make_float2(cos(r*angle), sin(r*angle));
  }

#if R == 2 
  GPU_FFT2( v ); 
#endif

#if R == 4
  GPU_FFT4( v );
#endif

#if R == 8
  GPU_FFT8( v );
#endif

#if R == 16
  GPU_FFT16( v );
#endif

  int idxD = GPU_expand(j,Ns,R);
  for( int r=0; r<R; r++ ) {
    data1[idxD+r*Ns] = v[r];
  }
}      

__global__ void GPU_FFT_Global(int Ns, float2* data0, float2* data1, int N) { 
  data0+=bx*N;
  data1+=bx*N;
  GPU_FftIteration(tx, Ns, data0, data1, N);
}

#ifdef SYNC
__global__ void GPU_FFT_Sync(float2* data0, float2* data1, int N) {
//  int numBlocks = gridDim.x * gridDim.y * gridDim.z;
//  int goalVal = 0;
  for(int Ns=1; Ns<N; Ns*=R) {
    float2* d0 = data0 + bx*N;
    float2* d1 = data1 + bx*N;
    GPU_FftIteration(tx, Ns, d0, d1, N);
    float2 *tmp = data0;
    data0 = data1;
    data1 = tmp;
    __syncthreads();
//    goalVal += numBlocks;
//    __ib_sync(goalVal);
  }
}
#endif

void inputData(char* fName, float* dat, int numwords) {
  FILE* fid = fopen(fName, "r");
  if (fid == NULL) {
      fprintf(stderr, "Cannot open input file\n");
      exit(-1);
  }
  size_t result = fread(dat, sizeof(float), numwords, fid);
  if (result != numwords) {fputs("Reading error", stderr); exit(3);}
  fclose(fid); 
}

void outputData(char* fName, float* outdat, int numwords) {
  FILE* fid = fopen(fName, "w");
  unsigned size;
  if (fid == NULL) {
      fprintf(stderr, "Cannot open output file\n");
      exit(-1);
  }
  size = numwords;
  fwrite(&size, sizeof(unsigned), 1, fid);
  fwrite (outdat, sizeof (float), numwords, fid);
  fclose (fid);
}

#define TIMING
#define READ_FILE
int main( int argc, char **argv ) {
  printf("[BENCH] CUDA Naive FFT, Xuhao Chen, IMPACT UIUC\n");
#ifndef SYNC
  printf("[BENCH] Running original version\n");
#else
  printf("[BENCH] Running block sync version\n");
#endif

  int N=256, B=1024;
#ifdef READ_FILE
  struct pb_Parameters *params;
  params = pb_ReadParameters(&argc, argv);
  if ((params->inpFiles[0] == NULL) || (params->inpFiles[1] != NULL)) {
      fprintf(stderr, "Expecting one input filename\n");
      exit(-1);
  }
  int err = 0;
  if(argc != 3)
    err |= 1;
  else {
    char* numend;
    N = strtol(argv[1], &numend, 10);
    if(numend == argv[1])
      err |= 2;
    B = strtol(argv[2], &numend, 10);
    if(numend == argv[2])
      err |= 4;
  }
  if(err) {
    fprintf(stderr, "Expecting two integers for N and B\n");
    exit(-1);
  }
#endif
  printf("[BENCH] R=%d, N=%d, B=%d\n", R, N, B);

#ifdef TIMING
  struct pb_TimerSet timers;
  pb_InitializeTimerSet(&timers);
#endif

  int n_bytes = N*B*sizeof(float2);
  float2 *source = (float2 *)malloc(n_bytes);
  float2 *result = (float2 *)malloc(n_bytes);

#ifdef READ_FILE
#ifdef TIMING
  pb_SwitchToTimer(&timers, pb_TimerID_IO);
#endif
  inputData(params->inpFiles[0], (float*)source, N*B*2);
#else
  for( int i = 0; i < N*B; i++ ) {
    source[i].x = (rand()/(float)RAND_MAX)*2-1;
    source[i].y = (rand()/(float)RAND_MAX)*2-1;
  }
#endif

#ifdef TIMING
  pb_SwitchToTimer(&timers, pb_TimerID_COPY);
#endif
  float2 *d_source, *d_work;
  cudaMalloc((void**) &d_source, n_bytes);
  CUERR;
  cudaMemcpy(d_source, source, n_bytes,cudaMemcpyHostToDevice);
  CUERR;
  cudaMalloc((void**) &d_work, n_bytes);
  CUERR;
  cudaMemset(d_work, 0, n_bytes);
  CUERR;

#ifdef TIMING
  pb_SwitchToTimer(&timers, pb_TimerID_KERNEL);
#endif

#ifdef SYNC
  GPU_FFT_Sync<<<dim3(B), dim3(N/R)>>>(d_source, d_work, N);
#else
  for(int Ns=1; Ns<N; Ns*=R) {
    GPU_FFT_Global<<<dim3(B), dim3(N/R)>>>(Ns, d_source, d_work, N);
    float2 *tmp = d_source;
    d_source = d_work;
    d_work = tmp;
  }
#endif

#ifdef TIMING
  pb_SwitchToTimer(&timers, pb_TimerID_COPY);
#endif

  cudaMemcpy(result, d_source, n_bytes, cudaMemcpyDeviceToHost);
  CUERR;
  cudaFree(d_source);
  CUERR;
  cudaFree(d_work);
  CUERR;

#ifdef TIMING
  pb_SwitchToTimer(&timers, pb_TimerID_IO);
#endif
  printf("[BENCH] Writing output to file <result.dat>\n");
  outputData("result.dat", (float*)result, N*B*2);

  free(source);
  free(result);
#ifdef TIMING
  pb_SwitchToTimer(&timers, pb_TimerID_NONE);
  pb_PrintTimerSet(&timers);
#endif
}

