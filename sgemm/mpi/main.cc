// (C) Copyright 2013, University of Illinois, All Rights Reserved
#include <mpi.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <malloc.h>
#include <vector>
#include <parboil.h>
#include <iostream>
#include "kernel.cc"
#define WORK_TAG 1
#define DIE_TAG 2
#define MASTER 0

extern bool readColMajorMatrixFile(const char *fn, int &nr_row, int &nr_col, std::vector<float>&v);
extern bool writeColMajorMatrixFile(const char *fn, int, int, std::vector<float>&);


static void worker(int id, int numProcs) {
  int matArow;
  MPI_Bcast(&matArow, 1, MPI_INT, 0, MPI_COMM_WORLD);

  int matBcol;
  MPI_Bcast(&matBcol, 1, MPI_INT, 0, MPI_COMM_WORLD);

  int matAcol;
  MPI_Bcast(&matAcol, 1, MPI_INT, 0, MPI_COMM_WORLD);

//  int workSize = (matBcol + numProcs - 1) / numProcs;
  int workSize = (matArow + numProcs - 1) / numProcs;
  int start = workSize * id;
//  int end = start + workSize > matBcol ? matBcol : start + workSize;
  int end = start + workSize > matArow ? matArow : start + workSize;
  printf("Node[%d]: workSize=%d, start=%d, end=%d\n", id, workSize, start, end);
  printf("Node[%d]: matArow=%d, matAcol=%d, matBcol=%d\n", id, matArow, matAcol, matBcol);

  float *matA = (float *)malloc(sizeof(float) * workSize * matAcol);
  printf("Node[%d]: Recieving data...\n", id);
  MPI_Recv(matA, workSize*matAcol, MPI_FLOAT, MASTER, WORK_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

  for(int i=0; i<1; i++)
    for(int j=0; j<4; j++)
    printf("Node[%d]: matA[%d][%d]=%f\n", id, i, j, matA[i+j*workSize]);
  printf("\n");
  
//  float *matBT = (float *)malloc(sizeof(float) * workSize * matAcol);
  float *matBT = (float *)malloc(sizeof(float) * matBcol * matAcol);
  MPI_Bcast(matBT, matBcol*matAcol, MPI_FLOAT, 0, MPI_COMM_WORLD);

  float *matC = (float *)malloc(sizeof(float) * workSize * matBcol);
  memset(matC, 0, sizeof(float) * workSize * matBcol);

  printf("Node[%d]: Kernel call...\n", id);
  basicSgemm('N', 'T', workSize, matBcol, matAcol, 1.0f, matA, workSize, matBT, matBcol, 0.0f, matC, workSize);

  printf("Node[%d]: Sending data back...\n", id);
  MPI_Send(matC, workSize*matBcol, MPI_FLOAT, MASTER, WORK_TAG, MPI_COMM_WORLD);

  free(matA);
  free(matBT);
  free(matC);

  MPI_Finalize();
  exit(0);
}

int main (int argc, char *argv[]) {
  struct pb_Parameters *params;
  struct pb_TimerSet timers;
  int matArow, matAcol;
  int matBrow, matBcol;
  std::vector<float> matA, matBT;

  MPI_Init(&argc, &argv);
  int numProcs;
  MPI_Comm_size(MPI_COMM_WORLD, &numProcs);
  int id;
  MPI_Comm_rank(MPI_COMM_WORLD, &id);
  if(id) worker(id, numProcs);

  pb_InitializeTimerSet(&timers);
  params = pb_ReadParameters(&argc, argv);
  if ((params->inpFiles[0] == NULL) 
      || (params->inpFiles[1] == NULL)
      || (params->inpFiles[2] == NULL)
      || (params->inpFiles[3] != NULL))
  {
      fprintf(stderr, "Expecting three input filenames\n");
      exit(-1);
  }
  pb_SwitchToTimer(&timers, pb_TimerID_IO);
  readColMajorMatrixFile(params->inpFiles[0], matArow, matAcol, matA);
  readColMajorMatrixFile(params->inpFiles[2], matBcol, matBrow, matBT);
  pb_SwitchToTimer( &timers, pb_TimerID_COMPUTE );
  std::vector<float> matC(matArow*matBcol);

  int workSize = (matArow + numProcs - 1) / numProcs;
  int start = workSize * id;
  int end = start + workSize > matArow ? matArow : start + workSize;
  printf("Node[%d]: workSize=%d, start=%d, end=%d\n", id, workSize, start, end);
  printf("Node[%d]: matArow=%d, matAcol=%d, matBcol=%d\n", id, matArow, matAcol, matBcol);
  MPI_Bcast(&matArow, 1, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Bcast(&matBcol, 1, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Bcast(&matAcol, 1, MPI_INT, 0, MPI_COMM_WORLD);

  printf("Node[%d]: Creating submtrix type...\n", id);
  int matrix_size[2];
  int submatrix_size[2];
  matrix_size[0] = matArow;
  matrix_size[1] = matAcol;
  submatrix_size[0] = workSize;
  submatrix_size[1] = matAcol;
  int matrix_start[2];
  matrix_start[1] = 0;
  float *submatA = (float *)malloc(sizeof(float) * workSize * matAcol);
  MPI_Datatype submatAtype;

  int i;
  for(i=1;i<numProcs;i++) {
    matrix_start[0] = i*workSize;
//    MPI_Datatype submatAtype;
    MPI_Type_create_subarray(2, matrix_size, submatrix_size, matrix_start, MPI_ORDER_FORTRAN, MPI_FLOAT, &submatAtype);
    MPI_Type_commit(&submatAtype);
    printf("Node[%d]: Sending data to Node %d...\n", id, i);
    MPI_Send(&matA.front(), 1, submatAtype, i, WORK_TAG, MPI_COMM_WORLD);
  }

    matrix_start[0] = 0;
    MPI_Type_create_subarray(2, matrix_size, submatrix_size, matrix_start, MPI_ORDER_FORTRAN, MPI_FLOAT, &submatAtype);
    MPI_Type_commit(&submatAtype);
    printf("Node[%d]: Sending data to Node %d...\n", id, 0);
    MPI_Send(&matA.front(), 1, submatAtype, 0, WORK_TAG, MPI_COMM_WORLD);  
    printf("Node[%d]: Recieving data...\n", id);
    MPI_Recv(submatA, workSize*matAcol, MPI_FLOAT, MASTER, WORK_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
 
  MPI_Type_free(&submatAtype);

  for(int i=0; i<1; i++)
    for(int j=0; j<4; j++)
    printf("Node[%d]: matA[%d][%d]=%f\n", id, i, j, submatA[i+j*workSize]);
  printf("\n");

  printf("After sending A to each process\n");
  MPI_Bcast(&matBT.front(), matAcol*matBcol, MPI_FLOAT, 0, MPI_COMM_WORLD);

  float *submatC = (float *)malloc(sizeof(float) * workSize * matBcol);
  memset(submatC, 0, sizeof(float) * workSize * matBcol);

  basicSgemm('N', 'T', workSize, matBcol, matAcol, 1.0f, submatA, workSize, &matBT.front(), matBcol, 0.0f, submatC, workSize);
  MPI_Send(submatC, workSize*matBcol, MPI_FLOAT, MASTER, WORK_TAG, MPI_COMM_WORLD);

  for(int i=0; i<1; i++)
    for(int j=0; j<4; j++)
      printf("Node[%d]: matC[%d][%d]=%f\n", id, i, j, submatC[i+j*workSize]);
  printf("\n");
  free(submatA);
  free(submatC);

  MPI_Datatype submatCtype;
  matrix_size[1] = matBcol;
  submatrix_size[1] = matBcol;
  for(i=0;i<numProcs;i++) {
    matrix_start[0] = i*workSize;
    MPI_Type_create_subarray(2, matrix_size, submatrix_size, matrix_start, MPI_ORDER_FORTRAN, MPI_FLOAT, &submatCtype);
    MPI_Type_commit(&submatCtype);
    MPI_Recv(matC.data(), 1, submatCtype, i, WORK_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  }
//  MPI_Type_free(&submatAtype);
  MPI_Type_free(&submatCtype);

  for(int i=0; i<4; i++)
    for(int j=0; j<4; j++)
    printf("All: matC[%d][%d]=%f\n", i, j, matC[i+j*matArow]);
  printf("\n");

  if (params->outFile) {
    pb_SwitchToTimer(&timers, pb_TimerID_IO);
    writeColMajorMatrixFile(params->outFile, matArow, matBcol, matC); 
  }
  pb_SwitchToTimer(&timers, pb_TimerID_NONE);
  double CPUtime = pb_GetElapsedTime(&(timers.timers[pb_TimerID_COMPUTE]));
  std::cout<< "GFLOPs = " << 2.* matArow * matBcol * matAcol/CPUtime/1e9 << std::endl;

  MPI_Finalize();

  pb_PrintTimerSet(&timers);
  pb_FreeParameters(params);
  return 0;
}
