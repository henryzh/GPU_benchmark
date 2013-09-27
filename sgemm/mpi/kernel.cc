// (C) Copyright 2013, University of Illinois, All Rights Reserved
//#include <iostream>

void basicSgemm(char transa, char transb, int m, int n, int k, float alpha, const float *A, int lda, const float *B, int ldb, float beta, float *C, int ldc ) {
//void basicSgemm( int start, int end, char transa, char transb, int m, int n, int k, float alpha, const float *A, int lda, const float *B, int ldb, float beta, float *C, int ldc ) {
  if ((transa != 'N') && (transa != 'n')) {
    std::cerr << "unsupported value of 'transa' in regtileSgemm()" << std::endl;
    return;
  }
  
  if ((transb != 'T') && (transb != 't')) {
    std::cerr << "unsupported value of 'transb' in regtileSgemm()" << std::endl;
    return;
  }

  for(int mm=0; mm<m; ++mm) {  
//  for (int mm = start; mm < end; ++mm) {
    for (int nn = 0; nn < n; ++nn) {
//    for(int mm=0; mm<m; ++mm) {
      float c = 0.0f;
      for (int i = 0; i < k; ++i) {
        float a = A[mm + i * lda]; 
        float b = B[nn + i * ldb];
        c += a * b;
      }
//      C[mm+(nn+start)*ldc] = C[mm+(nn+start)*ldc] * beta + alpha * c;
      C[mm+nn*ldc] = C[mm+nn*ldc] * beta + alpha * c;
    }
  }
}
