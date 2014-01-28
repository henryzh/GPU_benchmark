// (C) Copyright 2013, University of Illinois. All Rights Reserved
// Author: Lijiuan Luo (lluo3@uiuc.edu), Geng Daniel Liu (gengliu2@illinois.edu)

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <parboil.h>
#include <deque>
#include <iostream>
#include "config.h"
FILE *fp;

typedef int2 Node;
typedef int2 Edge;

#include "kernel.cu"
const int h_top = 1;
const int zero = 0;

int main(int argc, char** argv) {
  printf("[BENCH] BFS from Parboil\n");
#ifdef LOCKFREE
  printf("[BENCH] Lock-free Barrier\n");
#endif
#ifdef ATOMIC
  printf("[BENCH] Atomic Barrier\n");
#endif
#ifdef HW_SYNC
  printf("[BENCH] Hardware Barrier\n");
#endif
  int num_of_nodes = 0;
  int num_of_edges = 0;
  struct pb_Parameters *params;
  struct pb_TimerSet timers;

  pb_InitializeTimerSet(&timers);
  params = pb_ReadParameters(&argc, argv);
  if ((params->inpFiles[0] == NULL) || (params->inpFiles[1] != NULL)) {
    fprintf(stderr, "Expecting one input filename\n");
    exit(-1);
  }

  pb_SwitchToTimer(&timers, pb_TimerID_IO);

//  printf("Read in Graph from a file\n");
  fp = fopen(params->inpFiles[0],"r");
  if(!fp) {
    printf("Error Reading graph file\n");
    return 0;
  }
  int source;
  int res;
  res = fscanf(fp,"%d",&num_of_nodes);

//   printf("Allocate host memory\n");
  Node* h_graph_nodes = (Node*) malloc(sizeof(Node)*num_of_nodes);
  int *color = (int*) malloc(sizeof(int)*num_of_nodes);
  int start, edgeno;   

//  printf("Initalize the memory\n");
  for( unsigned int i = 0; i < num_of_nodes; i++) {
    res = fscanf(fp,"%d %d",&start,&edgeno);
    h_graph_nodes[i].x = start;
    h_graph_nodes[i].y = edgeno;
    color[i]=WHITE;
  }
//  printf("Read the source node from the file\n");
  res = fscanf(fp,"%d",&source);
  res = fscanf(fp,"%d",&num_of_edges);
  int id,cost;
  Edge* h_graph_edges = (Edge*) malloc(sizeof(Edge)*num_of_edges);
  for(int i=0; i < num_of_edges ; i++) {
    res = fscanf(fp,"%d",&id);
    res = fscanf(fp,"%d",&cost);
    h_graph_edges[i].x = id;
    h_graph_edges[i].y = cost;
  }
  if(res!=1)
    printf("Reading input failed\n");
  if(fp)
    fclose(fp);

//  printf("Allocate mem for the result on host side\n");
  int* h_cost = (int*) malloc( sizeof(int)*num_of_nodes);
  for(int i = 0; i < num_of_nodes; i++){
    h_cost[i] = INF;
  }
  h_cost[source] = 0;

  pb_SwitchToTimer(&timers, pb_TimerID_COPY);

//  printf("Copy the Node List to device memory\n");
  Node* d_graph_nodes;
  cudaMalloc((void**) &d_graph_nodes, sizeof(Node)*num_of_nodes);
  cudaMemcpy(d_graph_nodes, h_graph_nodes, sizeof(Node)*num_of_nodes, cudaMemcpyHostToDevice);

//  printf("Copy the Edge List to device Memory\n");
  Edge* d_graph_edges;
  cudaMalloc((void**) &d_graph_edges, sizeof(Edge)*num_of_edges);
  cudaMemcpy(d_graph_edges, h_graph_edges, sizeof(Edge)*num_of_edges, cudaMemcpyHostToDevice);

  int* d_color;
  cudaMalloc((void**) &d_color, sizeof(int)*num_of_nodes);
  int* d_cost;
  cudaMalloc((void**) &d_cost, sizeof(int)*num_of_nodes);
  int * d_q1;
  int * d_q2;
  cudaMalloc((void**) &d_q1, sizeof(int)*num_of_nodes);
  cudaMalloc((void**) &d_q2, sizeof(int)*num_of_nodes);
  int * tail;
  cudaMalloc((void**) &tail, sizeof(int));
  int *front_cost_d;
  cudaMalloc((void**) &front_cost_d, sizeof(int));
  cudaMemcpy(d_color, color, sizeof(int)*num_of_nodes, cudaMemcpyHostToDevice);
  cudaMemcpy(d_cost, h_cost, sizeof(int)*num_of_nodes, cudaMemcpyHostToDevice);

  //bind the texture memory with global memory
  cudaBindTexture(0,g_graph_node_ref,d_graph_nodes, sizeof(Node)*num_of_nodes);
  cudaBindTexture(0,g_graph_edge_ref,d_graph_edges,sizeof(Edge)*num_of_edges);

  printf("[BENCH] Starting GPU kernel\n");
  cudaThreadSynchronize();
  pb_SwitchToTimer(&timers, pb_TimerID_KERNEL);

  int num_of_blocks; 
  int num_of_threads_per_block;

  cudaMemcpy(tail,&h_top,sizeof(int),cudaMemcpyHostToDevice);
  cudaMemcpy(&d_cost[source],&zero,sizeof(int),cudaMemcpyHostToDevice);
  cudaMemcpy( &d_q1[0], &source, sizeof(int), cudaMemcpyHostToDevice);

  int num_t;//number of threads
  int k=0;//BFS level index

  //whether or not to adjust "k", see comment on "BFS_kernel_multi_blk_inGPU" for more details 
  int * switch_kd;
  cudaMalloc((void**) &switch_kd, sizeof(int));
  int * num_td;//number of threads
  cudaMalloc((void**) &num_td, sizeof(int));

  //whether to stay within a kernel, used in "BFS_kernel_multi_blk_inGPU"
  bool *stay;
  cudaMalloc( (void**) &stay, sizeof(bool));
  int switch_k;

  //max number of frontier nodes assigned to a block
  int * max_nodes_per_block_d;
  cudaMalloc( (void**) &max_nodes_per_block_d, sizeof(int));
  int *global_kt_d;
  cudaMalloc( (void**) &global_kt_d, sizeof(int));
  cudaMemcpy(global_kt_d,&zero, sizeof(int),cudaMemcpyHostToDevice);

  int h_overflow = 0;
  int *d_overflow;
  cudaMalloc((void**) &d_overflow, sizeof(int));
  cudaMemcpy(d_overflow, &h_overflow, sizeof(int), cudaMemcpyHostToDevice);
  int count1=0, count2=0, count3=0;

  int *in, *out;
#ifdef LOCKFREE
  int flag_size = NUM_SM*sizeof(int);
  cudaMalloc((void **)&in, flag_size);
  cudaMalloc((void **)&out, flag_size);
  cudaMemset(in, 0, flag_size);
  cudaMemset(out, 0, flag_size);
#endif
  cudaThreadSynchronize();

  do {
    cudaMemcpy( &num_t, tail, sizeof(int), cudaMemcpyDeviceToHost);
    cudaMemcpy(tail,&zero,sizeof(int),cudaMemcpyHostToDevice);

    if(num_t == 0) {//frontier is empty
      cudaFree(stay);
      cudaFree(switch_kd);
      cudaFree(num_td);
      break;
    }

    num_of_blocks = 1;
    num_of_threads_per_block = num_t;
    if(num_of_threads_per_block <NUM_BIN)
      num_of_threads_per_block = NUM_BIN;
    if(num_t>MAX_THREADS_PER_BLOCK) {
      num_of_blocks = (int)ceil(num_t/(double)MAX_THREADS_PER_BLOCK); 
      num_of_threads_per_block = MAX_THREADS_PER_BLOCK;
    }
    if(num_of_blocks == 1)//will call "BFS_in_GPU_kernel" 
      num_of_threads_per_block = MAX_THREADS_PER_BLOCK; 
    if(num_of_blocks >1 && num_of_blocks <= NUM_SM)// will call "BFS_kernel_multi_blk_inGPU"
      num_of_blocks = NUM_SM;

    //assume "num_of_blocks" can not be very large
    dim3  grid( num_of_blocks, 1, 1);
    dim3  threads( num_of_threads_per_block, 1, 1);

    if(k%2 == 0) {
      if(num_of_blocks == 1) {
        count1 ++;
        BFS_in_GPU_kernel<<< grid, threads >>>(d_q1,d_q2, d_graph_nodes, 
            d_graph_edges, d_color, d_cost,num_t , tail,GRAY0,k,d_overflow);
      }
      else if(num_of_blocks <= NUM_SM) {
        count2 ++;
        (cudaMemcpy(num_td,&num_t,sizeof(int),
                    cudaMemcpyHostToDevice));
        BFS_kernel_multi_blk_inGPU
          <<< grid, threads >>>(d_q1,d_q2, d_graph_nodes, 
              d_graph_edges, d_color, d_cost, num_td, tail,GRAY0,k,
              switch_kd, max_nodes_per_block_d, global_kt_d,d_overflow, in, out);
        (cudaMemcpy(&switch_k,switch_kd, sizeof(int),
                    cudaMemcpyDeviceToHost));
        if(!switch_k) {
          k--;
        }
      }
      else {
        count3 ++;
        BFS_kernel<<< grid, threads >>>(d_q1,d_q2, d_graph_nodes, 
            d_graph_edges, d_color, d_cost, num_t, tail,GRAY0,k,d_overflow);
      }
    }
    else {
      if(num_of_blocks == 1) {
        count1 ++;
        BFS_in_GPU_kernel<<< grid, threads >>>(d_q2,d_q1, d_graph_nodes, 
            d_graph_edges, d_color, d_cost, num_t, tail,GRAY1,k,d_overflow);
      }
      else if(num_of_blocks <= NUM_SM) {
        count2 ++;
        (cudaMemcpy(num_td,&num_t,sizeof(int),
                    cudaMemcpyHostToDevice));
        BFS_kernel_multi_blk_inGPU
          <<< grid, threads >>>(d_q2,d_q1, d_graph_nodes, 
              d_graph_edges, d_color, d_cost, num_td, tail,GRAY1,k,
              switch_kd, max_nodes_per_block_d, global_kt_d,d_overflow, in, out);
        (cudaMemcpy(&switch_k,switch_kd, sizeof(int),
                    cudaMemcpyDeviceToHost));
        if(!switch_k) {
          k--;
        }
      }
      else {
        count3 ++;
        BFS_kernel<<< grid, threads >>>(d_q2,d_q1, d_graph_nodes, 
            d_graph_edges, d_color, d_cost, num_t, tail, GRAY1,k,d_overflow);
      }
    }
    k++;
    cudaMemcpy(&h_overflow, d_overflow, sizeof(int), cudaMemcpyDeviceToHost);
    if(h_overflow) {
      printf("Error: local queue was overflown. Need to increase W_LOCAL_QUEUE\n");
      return 0;
    }
  } while(1);

  cudaThreadSynchronize();
#ifdef LOCKFREE
  cudaFree(in);
  cudaFree(out);
#endif
  pb_SwitchToTimer(&timers, pb_TimerID_COPY);
  printf("[BENCH] GPU kernel done\n");
  printf("[BENCH] Kernel called %d times (%d, %d, %d)\n", k, count1, count2, count3);

  // Copy result from device to host
  cudaMemcpy(h_cost, d_cost, sizeof(int)*num_of_nodes, cudaMemcpyDeviceToHost);
  cudaMemcpy(color, d_color, sizeof(int)*num_of_nodes, cudaMemcpyDeviceToHost);
  cudaUnbindTexture(g_graph_node_ref);
  cudaUnbindTexture(g_graph_edge_ref);

  cudaFree(d_graph_nodes);
  cudaFree(d_graph_edges);
  cudaFree(d_color);
  cudaFree(d_cost);
  cudaFree(tail);
  cudaFree(front_cost_d);

  // Store the result into a file
  pb_SwitchToTimer(&timers, pb_TimerID_IO);
  FILE *fp = fopen(params->outFile,"w");
  fprintf(fp, "%d\n", num_of_nodes);
  for(int i=0;i<num_of_nodes;i++)
    fprintf(fp,"%d %d\n",i,h_cost[i]);
  fclose(fp);

  // Cleanup memory
  free( h_graph_nodes);
  free( h_graph_edges);
  free( color);
  free( h_cost);
  pb_SwitchToTimer(&timers, pb_TimerID_NONE);
  pb_PrintTimerSet(&timers);
  pb_FreeParameters(params);
  return 0;
}
