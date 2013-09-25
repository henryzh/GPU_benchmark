
/***********************************************************************************************
 * * Implementing Graph Cuts on CUDA using algorithm given in CVGPU '08                       **
 * * paper "CUDA Cuts: Fast Graph Cuts on GPUs"                                               **
 * * Copyright (c) 2008 International Institute of Information Technology.                    **
 * * All rights reserved.                                                                     **
 * * Created By Vibhav Vineet.                                                                **
 * ********************************************************************************************/

#ifndef _PUSHRELABEL_KERNEL_CU_
#define _PUSHRELABEL_KERNEL_CU_

#include "CudaCuts.h"

#define LOCAL_INDEX(localX,localY) __umul24(localY+1 , 34 ) + localX + 1;
#define LOCAL_LEFT(index) (index-1)
#define LOCAL_RIGHT(index) (index+1)
#define LOCAL_TOP(index) (index-34)
#define LOCAL_BOTTOM(index) (index+34)

#define GLOBAL_LEFT(gid) (gid-1)
#define GLOBAL_RIGHT(gid) (gid+1)
#define GLOBAL_TOP(gid) (gid-gSizeX)
#define GLOBAL_BOTTOM(gid) (gid+gSizeX)

__device__ void
load_shared_mem(int* height_fn, int *g_graph_height, const int gSizeX, const int gSizeY) {
    const int gX  = __umul24( blockIdx.x, blockDim.x ) + threadIdx.x ;
    const int gY  = __umul24( blockIdx.y , blockDim.y ) + threadIdx.y ;
    const int gid = __umul24( gY , gSizeX ) + gX ;

    const int lX = threadIdx.x;
    const int lY = threadIdx.y;
    const int lid = LOCAL_INDEX(lX, lY);

    height_fn[lid] = g_graph_height[gid] ;
    (lX == 31 && gX < gSizeX - 1 ) ? height_fn[LOCAL_RIGHT(lid)] =  (g_graph_height[GLOBAL_RIGHT(gid)]) : 0;
    (lX == 0 && gX > 0 ) ? height_fn[LOCAL_LEFT(lid)] = (g_graph_height[GLOBAL_LEFT(gid)]) : 0;
    (lY == 7 && gY < gSizeY - 1 ) ? height_fn[LOCAL_BOTTOM(lid)] = (g_graph_height[GLOBAL_BOTTOM(gid)]) : 0;
    (lY == 0 && gY > 0 ) ? height_fn[LOCAL_TOP(lid)] = (g_graph_height[GLOBAL_TOP(gid)]) : 0;
}


__device__ void
set_state(int *g_left_weight, int *g_right_weight, int *g_down_weight, int *g_up_weight,
        int *g_sink_weight, int *g_push_reser,
        int *g_relabel_mask, int *g_graph_height,
        int gid, int gSizeX, int gSizeY)
{
    int flow_push = g_push_reser[gid] ;

    if(flow_push <= 0 || (g_left_weight[gid] == 0 && g_right_weight[gid] == 0 && g_down_weight[gid] == 0 && g_up_weight[gid] == 0 && g_sink_weight[gid] == 0))
        g_relabel_mask[gid] = 2 ;
    else
    {
        ( flow_push > 0 &&
          (
            ( (g_graph_height[gid] == g_graph_height[GLOBAL_LEFT(gid)] + 1 ) && g_left_weight[gid] > 0  ) ||
            ( (g_graph_height[gid] == g_graph_height[GLOBAL_RIGHT(gid)]+1 ) && g_right_weight[gid] > 0) ||
            ( (g_graph_height[gid] == g_graph_height[GLOBAL_BOTTOM(gid)]+1 ) && g_down_weight[gid] > 0) ||
            ( (g_graph_height[gid] == g_graph_height[GLOBAL_TOP(gid)]+1 ) && g_up_weight[gid] > 0 ) ||
            ( g_graph_height[gid] == 1 && g_sink_weight[gid] > 0 )
          )
        ) ? g_relabel_mask[gid] = 1 : g_relabel_mask[gid] = 0 ;
    }
}

/************************************************
 * Relabel operation                           **
 * *********************************************/

__device__ void
relabel( int *g_left_weight, int *g_right_weight, int *g_down_weight, int *g_up_weight,
        int *g_sink_weight, int *g_push_reser,
        int *g_relabel_mask, int *g_graph_height,
        int gRealSizeTotal, int gRealSizeX, int gRealSizeY, int gSizeTotal, int gSizeX, int gSizeY,
        int gid, int gX, int gY)
{
    set_state(g_left_weight, g_right_weight, g_down_weight, g_up_weight,
                g_sink_weight, g_push_reser,
                g_relabel_mask, g_graph_height,
                gid, gSizeX, gSizeY);


    __syncthreads();

    if(gid < gSizeTotal && gX < gRealSizeX - 1  && gX > 0 && gY < gRealSizeY - 1  && gY > 0  )
    {
        if(g_sink_weight[gid] > 0)
        {
            g_graph_height[gid] = 1 ;
        }
        else
        {
            int min_height = gRealSizeTotal ;
            (g_left_weight[gid] > 0 && min_height > g_graph_height[GLOBAL_LEFT(gid)] ) ? min_height = g_graph_height[GLOBAL_LEFT(gid)] : 0 ;
            (g_right_weight[gid] > 0 && min_height > g_graph_height[GLOBAL_RIGHT(gid)]) ? min_height = g_graph_height[GLOBAL_RIGHT(gid)] : 0 ;
            (g_down_weight[gid] > 0 && min_height > g_graph_height[GLOBAL_BOTTOM(gid)] ) ? min_height = g_graph_height[GLOBAL_BOTTOM(gid)] : 0 ;
            (g_up_weight[gid] > 0 && min_height > g_graph_height[GLOBAL_TOP(gid)] ) ? min_height = g_graph_height[GLOBAL_TOP(gid)] : 0 ;
            g_graph_height[gid] = min_height + 1 ;
        }
    }
}

__global__ void
kernel_relabel( int *g_left_weight, int *g_right_weight, int *g_down_weight, int *g_up_weight,
        int *g_sink_weight, int *g_push_reser,
        int *g_relabel_mask, int *g_graph_height,
        int gRealSizeTotal, int gRealSizeX, int gRealSizeY, int gSizeTotal, int gSizeX, int gSizeY )
{
    const int gX  = __umul24( blockIdx.x, blockDim.x ) + threadIdx.x ;
    const int gY  = __umul24( blockIdx.y , blockDim.y ) + threadIdx.y ;
    const int gid = __umul24( gY , gSizeX ) + gX ;

    relabel( g_left_weight, g_right_weight, g_down_weight,g_up_weight,
            g_sink_weight, g_push_reser,
            g_relabel_mask, g_graph_height,
            gRealSizeTotal, gRealSizeX, gRealSizeY, gSizeTotal, gSizeX, gSizeY,
            gid, gX, gY);
}


/************************************************
 * Push operation                              **
 * *********************************************/

__device__ void
push_sink(int *g_sink_weight, int *g_push_reser,
        int *g_graph_height,
        int gid)
{
    int temp_weight = g_sink_weight[gid];
    int flow_push = g_push_reser[gid];

    if(temp_weight > 0 && flow_push > 0 && g_graph_height[gid] == 1 )
    {
        int min_flow_pushed = flow_push ;
        (temp_weight < flow_push) ? min_flow_pushed = temp_weight : 0 ;

        g_sink_weight[gid] -= min_flow_pushed;
        g_push_reser[gid] -= min_flow_pushed;
    }
}

__device__ void
push_neighbour(int *g_sink_weight, int *g_push_reser, int *g_graph_height,
        int* my_weight, int* neighbour_pull_weight,
        int gid, int neighbour_id)
{
    int flow_push = g_push_reser[gid];
    int temp_weight = *my_weight;

    if(temp_weight > 0 && flow_push > 0 && g_graph_height[gid] == g_graph_height[neighbour_id] + 1 && *neighbour_pull_weight==0 )
    {
        int min_flow_pushed = flow_push;
        (temp_weight < flow_push) ? min_flow_pushed = temp_weight : 0;

        *my_weight -= min_flow_pushed;
        g_push_reser[gid] -= min_flow_pushed;
        *neighbour_pull_weight = min_flow_pushed;

    }
}

__device__ void pull(int* my_pull_weight, int* my_weight, int *g_push_reser, int gid) {
    if(*my_pull_weight > 0) {
        int pull_weight = *my_pull_weight;
        *my_weight += pull_weight;
        g_push_reser[gid] += pull_weight;
        __threadfence();
        *my_pull_weight = 0;
    }
}

__device__ void
push_all(int *g_left_weight, int *g_right_weight, int *g_down_weight, int *g_up_weight,
        int *g_pull_left, int *g_pull_right, int *g_pull_down, int *g_pull_up,
        int *g_sink_weight, int *g_push_reser,
        int *g_relabel_mask, int *g_graph_height,
        int gRealSizeTotal, int gRealSizeX, int gRealSizeY, int gSizeTotal, int gSizeX, int gSizeY,
        int gid, int gX, int gY) {


    if( gid < gSizeTotal && g_relabel_mask[gid] == 1 && gX < gRealSizeX-1 && gX > 0 && gY < gRealSizeY-1 && gY > 0 )
    {
        push_sink(g_sink_weight, g_push_reser, g_graph_height, gid);

        push_neighbour(g_sink_weight, g_push_reser, g_graph_height,
                &g_left_weight[gid], &g_pull_right[GLOBAL_LEFT(gid)],
                gid, GLOBAL_LEFT(gid));


        push_neighbour(g_sink_weight, g_push_reser, g_graph_height,
                &g_up_weight[gid], &g_pull_down[GLOBAL_TOP(gid)],
                gid, GLOBAL_TOP(gid));


        push_neighbour(g_sink_weight, g_push_reser, g_graph_height,
                &g_right_weight[gid], &g_pull_left[GLOBAL_RIGHT(gid)],
                gid, GLOBAL_RIGHT(gid));


        push_neighbour(g_sink_weight, g_push_reser, g_graph_height,
                &g_down_weight[gid], &g_pull_up[GLOBAL_BOTTOM(gid)],
                gid, GLOBAL_BOTTOM(gid));
    }
}

__device__ void
pull_all(int *g_left_weight, int *g_right_weight, int *g_down_weight, int *g_up_weight,
        int *g_pull_left, int *g_pull_right, int *g_pull_down, int *g_pull_up,
        int *g_push_reser,
        int gRealSizeTotal, int gRealSizeX, int gRealSizeY, int gSizeTotal, int gSizeX, int gSizeY,
        int gid, int gX, int gY)
{

    pull(&g_pull_right[gid], &g_right_weight[gid], g_push_reser, gid);
    pull(&g_pull_down[gid], &g_down_weight[gid], g_push_reser, gid);
    pull(&g_pull_left[gid], &g_left_weight[gid], g_push_reser, gid);
    pull(&g_pull_up[gid], &g_up_weight[gid], g_push_reser, gid);
}


__global__ void
kernel_push( const int k, const int total_blocks_x, const int total_blocks_y,
        int *g_left_weight, int *g_right_weight, int *g_down_weight, int *g_up_weight,
        int *g_pull_left, int *g_pull_right, int *g_pull_down, int *g_pull_up,
        int *g_sink_weight, int *g_push_reser,
        int *g_relabel_mask, int *g_graph_height,
        int gRealSizeTotal, int gRealSizeX, int gRealSizeY, int gSizeTotal, int gSizeX, int gSizeY)
{
    const int gridSizeX = gridDim.x;
    const int gridSizeY = gridDim.y;

    for(int j=0; j<k; j++) {    // Number of iterations for whole kernel

        for( int bidY=blockIdx.y; bidY<total_blocks_y; bidY+=gridSizeY){
        for( int bidX=blockIdx.x; bidX<total_blocks_x; bidX+=gridSizeX){ // Loop over all tiles for this block (persistent threads style)

            int gX  = bidX*blockDim.x + threadIdx.x ;
            int gY  = bidY*blockDim.y + threadIdx.y ;
            int gid = gY*gSizeX + gX ;

            const int m = 1;
            for(int i=0; i<m; i++) {
                push_all(g_left_weight, g_right_weight, g_down_weight, g_up_weight,
                                g_pull_left, g_pull_right, g_pull_down, g_pull_up,
                                g_sink_weight, g_push_reser,
                                g_relabel_mask, g_graph_height,
                                gRealSizeTotal, gRealSizeX, gRealSizeY, gSizeTotal, gSizeX, gSizeY,
                                gid, gX, gY);

                __syncthreads();

                pull_all(g_left_weight, g_right_weight, g_down_weight, g_up_weight,
                        g_pull_left, g_pull_right, g_pull_down, g_pull_up,
                        g_push_reser,
                        gRealSizeTotal, gRealSizeX, gRealSizeY, gSizeTotal, gSizeX, gSizeY,
                        gid, gX, gY);

                __syncthreads();

                if(i<m-1) { // Don't run this in last iteration as relabel will run it
                    set_state(g_left_weight, g_right_weight, g_down_weight, g_up_weight,
                            g_sink_weight, g_push_reser,
                            g_relabel_mask, g_graph_height,
                            gid, gSizeX, gSizeY);

                    __syncthreads();
                }
            }

            relabel( g_left_weight, g_right_weight, g_down_weight,g_up_weight,
                        g_sink_weight, g_push_reser,
                        g_relabel_mask, g_graph_height,
                        gRealSizeTotal, gRealSizeX, gRealSizeY, gSizeTotal, gSizeX, gSizeY,
                        gid, gX, gY);

            __syncthreads();

        } // Loop over all tiles for this block
        }

    } // Number of iterations for whole kernel
}

__global__ void
kernel_pull_end(int *g_left_weight, int *g_right_weight, int *g_down_weight, int *g_up_weight,
        int *g_pull_left, int *g_pull_right, int *g_pull_down, int *g_pull_up,
        int *g_push_reser,
        int gRealSizeTotal, int gRealSizeX, int gRealSizeY, int gSizeTotal, int gSizeX, int gSizeY)
{
    const int gX  = __umul24( blockIdx.x, blockDim.x ) + threadIdx.x ;
    const int gY  = __umul24( blockIdx.y , blockDim.y ) + threadIdx.y ;
    const int gid = __umul24( gY , gSizeX ) + gX ;

    pull_all(g_left_weight, g_right_weight, g_down_weight, g_up_weight,
            g_pull_left, g_pull_right, g_pull_down, g_pull_up,
            g_push_reser,
            gRealSizeTotal, gRealSizeX, gRealSizeY, gSizeTotal, gSizeX, gSizeY,
            gid, gX, gY);
}

__global__ void
kernel_start_sink( int *g_left_weight, int *g_right_weight, int *g_down_weight, int *g_up_weight,
        int *g_sink_weight, int *g_push_reser,
        int *g_relabel_mask, int *g_graph_height,
        int gRealSizeTotal, int gRealSizeX, int gRealSizeY, int gSizeTotal, int gSizeX, int gSizeY, int *d_relabel, int *d_stochastic, int *d_counter, bool *d_finish)
{
    const int gX  = __umul24( blockIdx.x, blockDim.x ) + threadIdx.x ;
    const int gY  = __umul24( blockIdx.y , blockDim.y ) + threadIdx.y ;
    const int gid = __umul24( gY , gSizeX ) + gX ;

    if( gid < gSizeTotal && g_relabel_mask[gid] == 1 && gX < gRealSizeX-1 && gX > 0 && gY < gRealSizeY-1 && gY > 0 )
    {
        push_sink(g_sink_weight, g_push_reser, g_graph_height, gid);
    }
}

__global__ void
kernel_relabel_stochastic( int *g_left_weight, int *g_right_weight, int *g_down_weight, int *g_up_weight,
		int *g_sink_weight, int *g_push_reser,
		int *g_relabel_mask, int *g_graph_height, int *g_height_write,
		int gRealSizeTotal, int gRealSizeX, int gRealSizeY, int gSizeTotal, int gSizeX, int gSizeY, int *d_stochastic, int *g_block_num )
{
	if(d_stochastic[blockIdx.y * (*g_block_num) + blockIdx.x] == 1 )
	{
        const int gX  = __umul24( blockIdx.x, blockDim.x ) + threadIdx.x ;
        const int gY  = __umul24( blockIdx.y , blockDim.y ) + threadIdx.y ;
        const int gid = __umul24( gY , gSizeX ) + gX ;
        const int lX = threadIdx.x;
        const int lY = threadIdx.y;
        const int lid = LOCAL_INDEX(lX, lY);

        __shared__ int height_fn[356];
        load_shared_mem(height_fn, g_graph_height, gSizeX, gSizeY);

		__syncthreads();


		int min_flow_pushed = g_left_weight[gid] ;
		int flow_push = g_push_reser[gid] ;

		if(flow_push <= 0 || (g_left_weight[gid] == 0 && g_right_weight[gid] == 0 && g_down_weight[gid] == 0 && g_up_weight[gid] == 0 && g_sink_weight[gid] == 0))
			g_relabel_mask[gid] = 2 ;
		else
		{
			( flow_push > 0 && ( ( (height_fn[lid] == height_fn[LOCAL_LEFT(lid)] + 1 ) && g_left_weight[gid] > 0  ) ||( (height_fn[lid] == height_fn[LOCAL_RIGHT(lid)]+1 ) && g_right_weight[gid] > 0) || ( ( height_fn[lid] == height_fn[LOCAL_BOTTOM(lid)]+1 ) && g_down_weight[gid] > 0) || ( (height_fn[lid] == height_fn[LOCAL_TOP(lid)]+1 ) && g_up_weight[gid] > 0 ) || ( height_fn[lid] == 1 && g_sink_weight[gid] > 0 )  ) ) ? g_relabel_mask[gid] = 1 : g_relabel_mask[gid] = 0 ;
		}


		__syncthreads();

		if(gid < gSizeTotal && gX < gRealSizeX - 1  && gX > 0 && gY < gRealSizeY - 1  && gY > 0  )
		{
			if(g_sink_weight[gid] > 0)
			{
				g_height_write[gid] = 1 ;
			}
			else
			{
				int min_height = gRealSizeTotal ;
				(min_flow_pushed > 0 && min_height > height_fn[LOCAL_LEFT(lid)] ) ? min_height = height_fn[LOCAL_LEFT(lid)] : 0 ;
				(g_right_weight[gid] > 0 && min_height > height_fn[LOCAL_RIGHT(lid)]) ? min_height = height_fn[LOCAL_RIGHT(lid)] : 0 ;
				(g_down_weight[gid] > 0 && min_height > height_fn[LOCAL_BOTTOM(lid)] ) ? min_height = height_fn[LOCAL_BOTTOM(lid)] : 0 ;
				(g_up_weight[gid] > 0 && min_height > height_fn[LOCAL_TOP(lid)] ) ? min_height = height_fn[LOCAL_TOP(lid)] : 0 ;
				g_height_write[gid] = min_height + 1 ;
			}
		}
	}
}

__global__ void
kernel_End( int *g_stochastic, int *g_count_blocks, int *g_counter)
{
	int gid = blockIdx.x * blockDim.x + threadIdx.x ; 
	if( gid < ( *g_counter ) )
	{
		if( g_stochastic[gid] == 1 )
			atomicAdd(g_count_blocks,1);
			//(*g_count_blocks) = (*g_count_blocks) + 1 ; 
	}
}

__global__ void
kernel_push1_stochastic( int *g_left_weight, int *g_right_weight, int *g_down_weight, int *g_up_weight,
	int *g_sink_weight, int *g_push_reser, int *g_relabel_mask, int *g_graph_height, int *g_height_write,
	int gRealSizeTotal, int gRealSizeX, int gRealSizeY, int gSizeTotal, int gSizeX, int gSizeY,
	int *d_stochastic,int *g_block_num ) {
	if(d_stochastic[blockIdx.y * (*g_block_num) + blockIdx.x] == 1 ) {
		const int gX  = __umul24( blockIdx.x, blockDim.x ) + threadIdx.x ;
		const int gY  = __umul24( blockIdx.y , blockDim.y ) + threadIdx.y ;
		const int gid = __umul24( gY , gSizeX ) + gX ;
		const int lX = threadIdx.x;
		const int lY = threadIdx.y;
		const int lid = LOCAL_INDEX(lX, lY);

		__shared__ int height_fn[356];
		load_shared_mem(height_fn, g_graph_height, gSizeX, gSizeY);
		__syncthreads();
		int flow_push = 0, min_flow_pushed = 0 ;
		flow_push = g_push_reser[gid] ;
		if( gid < gSizeTotal && g_relabel_mask[gid] == 1 && gX < gRealSizeX-1 && gX > 0 && gY < gRealSizeY-1 && gY > 0 ) {
			int temp_weight = 0;
			temp_weight = g_sink_weight[gid] ;
			min_flow_pushed = flow_push ;
			if(temp_weight > 0 && flow_push > 0 && height_fn[lid] == 1 ) {
				(temp_weight < flow_push) ? min_flow_pushed = temp_weight : 0 ;
				temp_weight = temp_weight - min_flow_pushed ;
				g_sink_weight[gid] = temp_weight ;
				atomicSub(&g_push_reser[gid] , min_flow_pushed);
			}
			__threadfence();
			flow_push = g_push_reser[gid] ;
			min_flow_pushed = flow_push ;
			temp_weight = g_left_weight[gid] ;
			if(temp_weight > 0 && flow_push > 0 && height_fn[lid] == height_fn[LOCAL_LEFT(lid)] + 1 ) {
				(temp_weight < flow_push) ? min_flow_pushed = temp_weight : 0;
				temp_weight = temp_weight - min_flow_pushed ;
				atomicSub(&g_left_weight[gid] , min_flow_pushed);
				atomicAdd(&g_right_weight[GLOBAL_LEFT(gid)],min_flow_pushed);
				atomicSub(&g_push_reser[gid] , min_flow_pushed);
				atomicAdd(&g_push_reser[GLOBAL_LEFT(gid)], min_flow_pushed);

			}
			__threadfence();
			flow_push = g_push_reser[gid] ;
			min_flow_pushed = flow_push ;
			temp_weight = g_up_weight[gid] ;
			if(temp_weight > 0 && flow_push > 0 && height_fn[lid] == height_fn[LOCAL_TOP(lid)] + 1) {
				(temp_weight<flow_push) ? min_flow_pushed = temp_weight : 0 ;
				temp_weight = temp_weight - min_flow_pushed ;
				atomicSub(&g_up_weight[gid] , min_flow_pushed);
				atomicAdd(&g_down_weight[GLOBAL_TOP(gid)],min_flow_pushed);
				atomicSub(&g_push_reser[gid] , min_flow_pushed);
				atomicAdd(&g_push_reser[GLOBAL_TOP(gid)], min_flow_pushed);
			}
			__threadfence();
			flow_push = g_push_reser[gid] ;
			min_flow_pushed = flow_push ;
			temp_weight = g_right_weight[gid] ;
			if(temp_weight > 0 && flow_push > 0 && height_fn[lid] == height_fn[LOCAL_RIGHT(lid)] + 1 ) {
				(temp_weight < flow_push) ? min_flow_pushed = temp_weight : 0 ;
				temp_weight = temp_weight - min_flow_pushed ;
				atomicSub(&g_right_weight[gid] , min_flow_pushed);
				atomicAdd(&g_left_weight[GLOBAL_RIGHT(gid)],min_flow_pushed);
				atomicSub(&g_push_reser[gid] , min_flow_pushed);
				atomicAdd(&g_push_reser[GLOBAL_RIGHT(gid)], min_flow_pushed);
			}
			__threadfence();
			flow_push = g_push_reser[gid] ;
			min_flow_pushed = flow_push ;
			temp_weight = g_down_weight[gid] ;
			if(temp_weight > 0 && flow_push > 0 && height_fn[lid] == height_fn[LOCAL_BOTTOM(lid)] + 1 ) {
				(temp_weight<flow_push) ? min_flow_pushed = temp_weight : 0 ;
				temp_weight = temp_weight - min_flow_pushed ;
				atomicSub(&g_down_weight[gid] , min_flow_pushed);
				atomicAdd(&g_up_weight[GLOBAL_BOTTOM(gid)], min_flow_pushed);
				atomicSub(&g_push_reser[gid] , min_flow_pushed);
				atomicAdd(&g_push_reser[GLOBAL_BOTTOM(gid)], min_flow_pushed);
			}
			__threadfence();
		}
	}
}

__global__ void
kernel_push2_stochastic( int *g_left_weight, int *g_right_weight, int *g_down_weight, int *g_up_weight,
	int *g_sink_weight, int *g_push_reser, int *g_relabel_mask, int *g_graph_height, int *g_height_write,
	int gRealSizeTotal, int gRealSizeX, int gRealSizeY, int gSizeTotal, int gSizeX, int gSizeY,
	int *d_relabel, int *d_stochastic, int *d_counter, bool *d_finish) {
	if(d_stochastic[blockIdx.y * 20 + blockIdx.x] == 1 ) {
		const int gX  = __umul24( blockIdx.x, blockDim.x ) + threadIdx.x ;
		const int gY  = __umul24( blockIdx.y , blockDim.y ) + threadIdx.y ;
		const int gid = __umul24( gY , gSizeX ) + gX ;
		const int lX = threadIdx.x;
		const int lY = threadIdx.y;
		const int lid = LOCAL_INDEX(lX, lY);
		__shared__ int height_fn[356];
		load_shared_mem(height_fn, g_graph_height, gSizeX, gSizeY);
		__syncthreads();
		int flow_push = 0, min_flow_pushed = 0 ;
		flow_push = g_push_reser[gid] ;
		if( gid < gSizeTotal && g_relabel_mask[gid] == 1 && gX < gRealSizeX-1 && gX > 0 && gY < gRealSizeY-1 && gY > 0 ) {
			int temp_weight = 0;
			temp_weight = g_sink_weight[gid] ;
			min_flow_pushed = flow_push ;
			if(temp_weight > 0 && flow_push > 0 && height_fn[lid] == 1 ) {
				(temp_weight < flow_push) ? min_flow_pushed = temp_weight : 0 ;
				temp_weight = temp_weight - min_flow_pushed ;
				g_sink_weight[gid] = temp_weight ;
				atomicSub(&g_push_reser[gid] , min_flow_pushed);
			}
			__threadfence();
			flow_push = g_push_reser[gid] ;
			min_flow_pushed = flow_push ;
			temp_weight = g_left_weight[gid] ;
			if(temp_weight > 0 && flow_push > 0 && height_fn[lid] == height_fn[LOCAL_LEFT(lid)] + 1 ) {
				(temp_weight < flow_push) ? min_flow_pushed = temp_weight : 0;
				temp_weight = temp_weight - min_flow_pushed ;
				atomicSub(&g_left_weight[gid] , min_flow_pushed);
				atomicAdd(&g_right_weight[GLOBAL_LEFT(gid)],min_flow_pushed);
				atomicSub(&g_push_reser[gid] , min_flow_pushed);
				atomicAdd(&g_push_reser[GLOBAL_LEFT(gid)], min_flow_pushed);

			}
			__threadfence();
			flow_push = g_push_reser[gid] ;
			min_flow_pushed = flow_push ;
			temp_weight = g_up_weight[gid] ;

			if(temp_weight > 0 && flow_push > 0 && height_fn[lid] == height_fn[LOCAL_TOP(lid)] + 1) {
				(temp_weight<flow_push) ? min_flow_pushed = temp_weight : 0 ;
				temp_weight = temp_weight - min_flow_pushed ;

				atomicSub(&g_up_weight[gid] , min_flow_pushed);
				atomicAdd(&g_down_weight[GLOBAL_TOP(gid)],min_flow_pushed);
				atomicSub(&g_push_reser[gid] , min_flow_pushed);
				atomicAdd(&g_push_reser[GLOBAL_TOP(gid)], min_flow_pushed);

			}
 			__threadfence();
			flow_push = g_push_reser[gid] ;
			min_flow_pushed = flow_push ;
			temp_weight = g_right_weight[gid] ;
			if(temp_weight > 0 && flow_push > 0 && height_fn[lid] == height_fn[LOCAL_RIGHT(lid)] + 1) {
				(temp_weight < flow_push) ? min_flow_pushed = temp_weight : 0 ;
				temp_weight = temp_weight - min_flow_pushed ;
				atomicSub(&g_right_weight[gid] , min_flow_pushed);
				atomicAdd(&g_left_weight[GLOBAL_RIGHT(gid)],min_flow_pushed);
				atomicSub(&g_push_reser[gid] , min_flow_pushed);
				atomicAdd(&g_push_reser[GLOBAL_RIGHT(gid)], min_flow_pushed);
			}
			__threadfence();
			flow_push = g_push_reser[gid] ;
			min_flow_pushed = flow_push ;
			temp_weight = g_down_weight[gid] ;
			if(temp_weight > 0 && flow_push > 0 && height_fn[lid] == height_fn[LOCAL_BOTTOM(lid)] + 1 ) {
				(temp_weight<flow_push) ? min_flow_pushed = temp_weight : 0 ;
				temp_weight = temp_weight - min_flow_pushed ;
				atomicSub(&g_down_weight[gid] , min_flow_pushed);
				atomicAdd(&g_up_weight[GLOBAL_BOTTOM(gid)], min_flow_pushed);
				atomicSub(&g_push_reser[gid] , min_flow_pushed);
				atomicAdd(&g_push_reser[GLOBAL_BOTTOM(gid)], min_flow_pushed);
			}
			__threadfence();
		}	
		__syncthreads() ; 
		min_flow_pushed = g_left_weight[gid] ;
		flow_push = g_push_reser[gid] ;

		if(flow_push <= 0 || (g_left_weight[gid] == 0 && g_right_weight[gid] == 0 && g_down_weight[gid] == 0 && g_up_weight[gid] == 0 && g_sink_weight[gid] == 0))
			g_relabel_mask[gid] = 2 ;
		else {
			( flow_push > 0 && ( ( (height_fn[lid] == height_fn[LOCAL_LEFT(lid)] + 1 ) && g_left_weight[gid] > 0  ) ||( (height_fn[lid] == height_fn[LOCAL_RIGHT(lid)]+1 ) && g_right_weight[gid] > 0) || ( ( height_fn[lid] == height_fn[LOCAL_BOTTOM(lid)]+1 ) && g_down_weight[gid] > 0) || ( (height_fn[lid] == height_fn[LOCAL_TOP(lid)]+1 ) && g_up_weight[gid] > 0 ) || ( height_fn[lid] == 1 && g_sink_weight[gid] > 0 )  ) ) ? g_relabel_mask[gid] = 1 : g_relabel_mask[gid] = 0 ;
		}
		__syncthreads() ;
		if( gid < gSizeTotal && g_relabel_mask[gid] == 1 && gX < gRealSizeX-1 && gX > 0 && gY < gRealSizeY-1 && gY > 0 )
		{
			int temp_weight = 0;
			temp_weight = g_sink_weight[gid] ;
			min_flow_pushed = flow_push ;
			if(temp_weight > 0 && flow_push > 0 && height_fn[lid] == 1 ) {
				(temp_weight < flow_push) ? min_flow_pushed = temp_weight : 0 ;
				temp_weight = temp_weight - min_flow_pushed ;
				g_sink_weight[gid] = temp_weight ;
				atomicSub(&g_push_reser[gid] , min_flow_pushed);
			}
			__threadfence();
			flow_push = g_push_reser[gid] ;
			min_flow_pushed = flow_push ;
			temp_weight = g_left_weight[gid] ;
			if(temp_weight > 0 && flow_push > 0 && height_fn[lid] == height_fn[LOCAL_LEFT(lid)] + 1 ) {
				(temp_weight < flow_push) ? min_flow_pushed = temp_weight : 0;
				temp_weight = temp_weight - min_flow_pushed ;
				atomicSub(&g_left_weight[gid] , min_flow_pushed);
				atomicAdd(&g_right_weight[GLOBAL_LEFT(gid)],min_flow_pushed);
				atomicSub(&g_push_reser[gid] , min_flow_pushed);
				atomicAdd(&g_push_reser[GLOBAL_LEFT(gid)], min_flow_pushed);
			}
			__threadfence();
			flow_push = g_push_reser[gid] ;
			min_flow_pushed = flow_push ;
			temp_weight = g_up_weight[gid] ;
			if(temp_weight > 0 && flow_push > 0 && height_fn[lid] == height_fn[LOCAL_TOP(lid)] + 1) {
				(temp_weight<flow_push) ? min_flow_pushed = temp_weight : 0 ;
				temp_weight = temp_weight - min_flow_pushed ;
				atomicSub(&g_up_weight[gid] , min_flow_pushed);
				atomicAdd(&g_down_weight[GLOBAL_TOP(gid)],min_flow_pushed);
				atomicSub(&g_push_reser[gid] , min_flow_pushed);
				atomicAdd(&g_push_reser[GLOBAL_TOP(gid)], min_flow_pushed);
			}
			__threadfence();
			flow_push = g_push_reser[gid] ;
			min_flow_pushed = flow_push ;
			temp_weight = g_right_weight[gid] ;
			if(temp_weight > 0 && flow_push > 0 && height_fn[lid] == height_fn[LOCAL_RIGHT(lid)] + 1) {
				(temp_weight < flow_push) ? min_flow_pushed = temp_weight : 0 ;
				temp_weight = temp_weight - min_flow_pushed ;
				atomicSub(&g_right_weight[gid] , min_flow_pushed);
				atomicAdd(&g_left_weight[GLOBAL_RIGHT(gid)],min_flow_pushed);
				atomicSub(&g_push_reser[gid] , min_flow_pushed);
				atomicAdd(&g_push_reser[GLOBAL_RIGHT(gid)], min_flow_pushed);
			}
			__threadfence();
			flow_push = g_push_reser[gid] ;
			min_flow_pushed = flow_push ;
			temp_weight = g_down_weight[gid] ;
			if(temp_weight > 0 && flow_push > 0 && height_fn[lid] == height_fn[LOCAL_BOTTOM(lid)] + 1 ) {
				(temp_weight<flow_push) ? min_flow_pushed = temp_weight : 0 ;
				temp_weight = temp_weight - min_flow_pushed ;
				atomicSub(&g_down_weight[gid] , min_flow_pushed);
				atomicAdd(&g_up_weight[GLOBAL_BOTTOM(gid)], min_flow_pushed);
				atomicSub(&g_push_reser[gid] , min_flow_pushed);
				atomicAdd(&g_push_reser[GLOBAL_BOTTOM(gid)], min_flow_pushed);
			}
			__threadfence();
		}
	}
}

__global__ void
kernel_bfs_t(int *g_push_reser, int  *g_sink_weight, int *g_graph_height, bool *g_pixel_mask,
		int vertex_num, int gRealSizeX, int gRealSizeY, int vertex_num1, int gSizeX, int gSizeY) {
	int gid = __umul24(blockIdx.x, blockDim.x) + threadIdx.x ;
	if(gid < vertex_num && g_pixel_mask[gid] == true ) {
		int col = gid % gSizeX , row = gid / gSizeX ;
		if(col > 0 && row > 0 && col < gRealSizeX - 1 && row < gRealSizeY - 1 && g_push_reser[gid] > 0 ) {
			g_graph_height[gid] = 1 ;
			g_pixel_mask[gid] = false ;
		}
		else
			if(g_sink_weight[gid] > 0) {
				g_graph_height[gid] = -1 ;
				g_pixel_mask[gid] = false ;
			}
	}
}	

__global__ void
kernel_push_stochastic1( int *g_push_reser, int *s_push_reser, int *g_count_blocks, bool *g_finish, int *g_block_num, int gSizeX) {
	int gX  = __umul24( blockIdx.x, blockDim.x ) + threadIdx.x ;
	int gY  = __umul24( blockIdx.y , blockDim.y ) + threadIdx.y ;
	int gid = __umul24( gY , gSizeX ) + gX ;
	s_push_reser[gid] = g_push_reser[gid] ;
	if( gid == 0 ) {
		if((*g_count_blocks) < 50 )
			(*g_finish) = false ; 
	}
}

__global__ void
kernel_push_stochastic2( int *g_push_reser, int *s_push_reser, int *d_stochastic, int *g_block_num, int gSizeX) {
	int gX  = __umul24( blockIdx.x, blockDim.x ) + threadIdx.x ;
	int gY  = __umul24( blockIdx.y , blockDim.y ) + threadIdx.y ;
	int gid = __umul24( gY , gSizeX ) + gX ;
	int stochastic = 0 ;
	stochastic = ( s_push_reser[gid] - g_push_reser[gid]) ;
	if(stochastic != 0) {
		d_stochastic[blockIdx.y * (*g_block_num) + blockIdx.x] = 1 ;
	}
}

__global__ void
kernel_push1_start_stochastic( int *g_left_weight, int *g_right_weight, int *g_down_weight, int *g_up_weight,
		int *g_sink_weight, int *g_push_reser,
		int *g_relabel_mask, int *g_graph_height, int *g_height_write,
		int gRealSizeTotal, int gRealSizeX, int gRealSizeY, int gSizeTotal, int gSizeX, int gSizeY, int *d_relabel, int *d_stochastic, int *d_counter, bool *d_finish) {
    const int gX  = __umul24( blockIdx.x, blockDim.x ) + threadIdx.x ;
    const int gY  = __umul24( blockIdx.y , blockDim.y ) + threadIdx.y ;
    const int gid = __umul24( gY , gSizeX ) + gX ;
    const int lX = threadIdx.x;
    const int lY = threadIdx.y;
    const int lid = LOCAL_INDEX(lX, lY);

    __shared__ int height_fn[356];
    load_shared_mem(height_fn, g_graph_height, gSizeX, gSizeY);
	__syncthreads();
	int flow_push = 0, min_flow_pushed = 0 ;
	flow_push = g_push_reser[gid] ;
	if( gid < gSizeTotal && g_relabel_mask[gid] == 1 && gX < gRealSizeX-1 && gX > 0 && gY < gRealSizeY-1 && gY > 0) {
		int temp_weight = 0;
		temp_weight = g_sink_weight[gid] ;
		min_flow_pushed = flow_push ;
		if(temp_weight > 0 && flow_push > 0 && height_fn[lid] == 1 ) {
			(temp_weight < flow_push) ? min_flow_pushed = temp_weight : 0 ;
			temp_weight = temp_weight - min_flow_pushed ;
			g_sink_weight[gid] = temp_weight ;
			atomicSub(&g_push_reser[gid] , min_flow_pushed);
			flow_push = flow_push - min_flow_pushed ;
		}
	}
	__syncthreads() ;
	min_flow_pushed = g_left_weight[gid] ;

	( flow_push > 0 && ( ((height_fn[lid] == height_fn[LOCAL_LEFT(lid)] + 1 ) && min_flow_pushed > 0  ) ||( (height_fn[lid] == height_fn[LOCAL_RIGHT(lid)]+1 ) && g_right_weight[gid] > 0) || ( ( height_fn[lid] == height_fn[LOCAL_BOTTOM(lid)]+1 ) && g_down_weight[gid] > 0) || ( (height_fn[lid] == height_fn[LOCAL_TOP(lid)]+1 ) && g_up_weight[gid] > 0 ) || ( height_fn[lid] == 1 && g_sink_weight[gid] > 0 )  ) ) ? g_relabel_mask[gid] = 1 : g_relabel_mask[gid] = 0 ;
	if(gid < gSizeTotal && gX < gRealSizeX - 1  && gX > 0 && gY < gRealSizeY - 1  && gY > 0  ) {
		if(g_sink_weight[gid] > 0) {
			g_height_write[gid] = 1 ;
		}
		else {
			int min_height = gRealSizeTotal ;
			(min_flow_pushed > 0 && min_height > height_fn[LOCAL_LEFT(lid)] ) ? min_height = height_fn[LOCAL_LEFT(lid)] : 0 ;
			(g_right_weight[gid] > 0 && min_height > height_fn[LOCAL_RIGHT(lid)]) ? min_height = height_fn[LOCAL_RIGHT(lid)] : 0 ;
			(g_down_weight[gid] > 0 && min_height > height_fn[LOCAL_BOTTOM(lid)] ) ? min_height = height_fn[LOCAL_BOTTOM(lid)] : 0 ;
			(g_up_weight[gid] > 0 && min_height > height_fn[LOCAL_TOP(lid)] ) ? min_height = height_fn[LOCAL_TOP(lid)] : 0 ;
			g_height_write[gid] = min_height + 1 ;
		}
	}

}

__global__ void
kernel_bfs(int *g_left_weight, int *g_right_weight, int *g_down_weight, int *g_up_weight,
		int *g_graph_height, bool *g_pixel_mask, int vertex_num,int gRealSizeX,int gRealSizeY,
		int vertex_num1, int gSizeX, int gSizeY, bool *g_over, int *g_counter) {
	/*******************************
	 *threadId is calculated ******
	 *****************************/

	int gid = __umul24(blockIdx.x, blockDim.x) + threadIdx.x ;
	if(gid < vertex_num && g_pixel_mask[gid] == true) {
		int col = gid % gSizeX , row = gid / gSizeX ;
		if(col < gRealSizeX - 1 && col > 0 && row < gRealSizeY - 1 && row > 0 ) {
			int height_l = 0, height_d = 0, height_u = 0 , height_r = 0 ;
			height_r = g_graph_height[GLOBAL_RIGHT(gid)] ;
			height_l = g_graph_height[GLOBAL_LEFT(gid)] ;
			height_d = g_graph_height[GLOBAL_BOTTOM(gid)] ;
			height_u = g_graph_height[GLOBAL_TOP(gid)] ;

			if(((height_l == (*g_counter) && g_right_weight[GLOBAL_LEFT(gid)] > 0)) ||((height_d == (*g_counter) && g_up_weight[GLOBAL_BOTTOM(gid)] > 0) || ( height_r == (*g_counter) && g_left_weight[GLOBAL_RIGHT(gid)] > 0 ) || ( height_u == (*g_counter) && g_down_weight[GLOBAL_TOP(gid)] > 0 ) ))
			{
				g_graph_height[gid] = (*g_counter) + 1 ;
				g_pixel_mask[gid] = false ;
				*g_over = true ;
			}
		}
	}
}

/************************************************************
 * functions to construct the graph on the device          **
 * *********************************************************/
__device__ void add_edge(int from, int to, int cap, int rev_cap, int type, int *d_left_weight,
		int *d_right_weight, int *d_down_weight, int *d_up_weight) {
	if(type==1) {
		d_left_weight[from] = d_left_weight[from]+cap;
		d_right_weight[to] = d_right_weight[to]+rev_cap;
	}
	if(type==2) {
		d_right_weight[from] = d_right_weight[from]+cap;
		d_left_weight[to] = d_left_weight[to]+rev_cap;
	}
	if(type==3) {
		d_down_weight[from] = d_down_weight[from]+cap;
		d_up_weight[to] = d_up_weight[to]+rev_cap;
	}
	if(type==4) {
		d_up_weight[from] = d_up_weight[from]+cap;
		d_down_weight[to] = d_down_weight[to]+cap;
	}
}

__device__ void add_tweights(int i, int cap_source, int  cap_sink, int *d_push_reser, int *d_sink_weight) {
	int diff = cap_source - cap_sink ;
	if(diff>0) {
		d_push_reser[i] = d_push_reser[i] + diff ;
	}
	else {
		d_sink_weight[i] = d_sink_weight[i] - diff ;
	}
}

__device__
void add_term1(int i, int A, int B, int *d_push_reser, int *d_sink_weight) {
	add_tweights(i,B,A, d_push_reser, d_sink_weight);
}

__device__
void add_t_links_Cue(int alpha_label, int gid, int *d_left_weight, int *d_right_weight,
		int *d_down_weight, int *d_up_weight, int *d_push_reser, int *d_sink_weight,
		int *dPixelLabel, int *dDataTerm, int gRealSizeX , int gRealSizeY, int num_labels) {
	{
		if(dPixelLabel[gid]!=alpha_label) {
			add_term1(gid , dDataTerm[gid*num_labels+alpha_label] , dDataTerm[gid * num_labels + dPixelLabel[gid]], d_push_reser, d_sink_weight  );
		}
	}
}

__device__
void add_t_links(int alpha_label, int gid, int *d_left_weight, int *d_right_weight,
		int *d_down_weight, int *d_up_weight, int *d_push_reser, int *d_sink_weight,
		int *dPixelLabel, int *dDataTerm, int gRealSizeX , int gRealSizeY, int num_labels) {
	{
		if(dPixelLabel[gid]!=alpha_label) {
			add_term1(gid , dDataTerm[gid*num_labels+alpha_label] , dDataTerm[gid * num_labels + dPixelLabel[gid]], d_push_reser, d_sink_weight  );
		}
	}
}

__device__
void add_term2(int x, int y, int A, int B, int C, int D, int type, int *d_left_weight,
		int *d_right_weight, int *d_down_weight, int *d_up_weight, int *d_push_reser, int *d_sink_weight) {
	if ( A+D > C+B) {
		int delta = A+D-C-B;
		int subtrA = delta/3;
		A = A-subtrA;
		C = C+subtrA;
		B = B+(delta-subtrA*2);
#ifdef COUNT_TRUNCATIONS
		truncCnt++;
#endif
	}
#ifdef COUNT_TRUNCATIONS
	totalCnt++;
#endif
	add_tweights(x, D, A, d_push_reser, d_sink_weight);
	B -= A; C -= D;
	if (B < 0) {
		add_tweights(x, 0, B, d_push_reser, d_sink_weight);
		add_tweights(y, 0, -B, d_push_reser, d_sink_weight ) ;
		add_edge(x, y, 0, B+C,type , d_left_weight, d_right_weight, d_down_weight, d_up_weight );
	}
	else if (C < 0) {
		add_tweights(x, 0, -C, d_push_reser, d_sink_weight);
		add_tweights(y, 0, C , d_push_reser, d_sink_weight);
		add_edge(x, y, B+C, 0,type , d_left_weight, d_right_weight, d_down_weight, d_up_weight);
	}
	else {
		add_edge(x, y, B, C,type, d_left_weight, d_right_weight , d_down_weight, d_up_weight);
	}
}

__device__
void set_up_expansion_energy_G_ARRAY(int alpha_label,int gid, int *d_left_weight,int *d_right_weight,
		int *d_down_weight, int *d_up_weight, int *d_push_reser,
		int *d_sink_weight, int *dPixelLabel, int *dDataTerm, int *dSmoothTerm,
		int gRealSizeX , int gRealSizeY, int num_labels ) {
	int x,y,nPix;
	int weight;
	int i = gid ;
	{
		if(dPixelLabel[i]!=alpha_label) {
			y = i/gRealSizeX;
			x = i - y*gRealSizeX;
			if ( x < gRealSizeX - 1 ) {
				nPix = i + 1;
				weight = 1 ;
				if ( dPixelLabel[nPix] != alpha_label ) {
					add_term2(i,nPix,
					( dSmoothTerm[alpha_label + alpha_label * num_labels]) * weight,
					( dSmoothTerm[alpha_label + dPixelLabel[nPix]*num_labels]) * weight,
					( dSmoothTerm[ dPixelLabel[i] +  alpha_label * num_labels] ) * weight,
					( dSmoothTerm[ dPixelLabel[i] +  dPixelLabel[nPix] * num_labels] )  * weight,
							2, d_left_weight, d_right_weight, d_down_weight, d_up_weight, d_push_reser, d_sink_weight); // 1-left, 2-right, 3-down, 4-up
				}
				else   add_term1(i,
						( dSmoothTerm[alpha_label + dPixelLabel[nPix] * num_labels]) * weight,
						( dSmoothTerm[dPixelLabel[i] + alpha_label*num_labels]) * weight,
						d_push_reser, d_sink_weight);
			}

			if ( y < gRealSizeY - 1 ) {
				nPix = i + gRealSizeX;
				weight = 1 ;
				if ( dPixelLabel[nPix] != alpha_label ) {
					add_term2(i,nPix,
					( dSmoothTerm[alpha_label + alpha_label * num_labels]) * weight,
					( dSmoothTerm[alpha_label + dPixelLabel[nPix]*num_labels]) * weight,
					( dSmoothTerm[ dPixelLabel[i] +  alpha_label * num_labels] ) * weight,
					( dSmoothTerm[ dPixelLabel[i] +  dPixelLabel[nPix] * num_labels] )  * weight,
					3, d_left_weight, d_right_weight, d_down_weight, d_up_weight, d_push_reser, d_sink_weight );
				}
				else   add_term1(i,
						( dSmoothTerm[alpha_label + dPixelLabel[nPix] * num_labels]) * weight,
						( dSmoothTerm[dPixelLabel[i] + alpha_label*num_labels]) * weight,
						d_push_reser, d_sink_weight);
			}
			if ( x > 0 ) {
				nPix = i - 1;
				weight = 1 ;
				if ( dPixelLabel[nPix] == alpha_label )
					add_term1(i,
						( dSmoothTerm[alpha_label + dPixelLabel[nPix] * num_labels]) * weight,
						( dSmoothTerm[dPixelLabel[i] + alpha_label*num_labels]) * weight,
						d_push_reser, d_sink_weight );
			}

			if ( y > 0 ) {
				nPix = i - gRealSizeX;
				weight = 1 ;
				if ( dPixelLabel[nPix] == alpha_label ) {
					add_term1(i,
						( dSmoothTerm[alpha_label + alpha_label * num_labels]) * weight,
						( dSmoothTerm[dPixelLabel[i] + alpha_label*num_labels]) * weight,
						d_push_reser, d_sink_weight);
				}
			}
		}
	}
}

__device__
void set_up_expansion_energy_G_ARRAY_Cue(int alpha_label,int gid, int *d_left_weight,int *d_right_weight,
		int *d_down_weight, int *d_up_weight, int *d_push_reser,
		int *d_sink_weight, int *dPixelLabel, int *dDataTerm, int *dSmoothTerm,
		int *dHcue, int *dVcue, int gRealSizeX , int gRealSizeY, int num_labels ) {
	int x,y,nPix;
	int weight;
	int i = gid ;
	{
		if(dPixelLabel[i]!=alpha_label) {
			y = i/gRealSizeX;
			x = i - y*gRealSizeX;

			if ( x < gRealSizeX - 1 ) {
				nPix = i + 1;
				weight=dHcue[i];
				if ( dPixelLabel[nPix] != alpha_label ) {
					add_term2(i,nPix,
					( dSmoothTerm[alpha_label + alpha_label * num_labels]) * weight,
					( dSmoothTerm[alpha_label + dPixelLabel[nPix]*num_labels]) * weight,
					( dSmoothTerm[ dPixelLabel[i] +  alpha_label * num_labels] ) * weight,
					( dSmoothTerm[ dPixelLabel[i] +  dPixelLabel[nPix] * num_labels] )  * weight,

					2, d_left_weight, d_right_weight, d_down_weight, d_up_weight, d_push_reser, d_sink_weight); // 1-left, 2-right, 3-down, 4-up
				}
				else   add_term1(i,
						( dSmoothTerm[alpha_label + dPixelLabel[nPix] * num_labels]) * weight,
						( dSmoothTerm[dPixelLabel[i] + alpha_label*num_labels]) * weight,
						d_push_reser, d_sink_weight);
			}
			if ( y < gRealSizeY - 1 ) {
				nPix = i + gRealSizeX;
				weight=dVcue[i];
				if ( dPixelLabel[nPix] != alpha_label ) {
					add_term2(i,nPix,
					( dSmoothTerm[alpha_label + alpha_label * num_labels]) * weight,
					( dSmoothTerm[alpha_label + dPixelLabel[nPix]*num_labels]) * weight,
					( dSmoothTerm[ dPixelLabel[i] +  alpha_label * num_labels] ) * weight,
					( dSmoothTerm[ dPixelLabel[i] +  dPixelLabel[nPix] * num_labels] )  * weight,
			3, d_left_weight, d_right_weight, d_down_weight, d_up_weight, d_push_reser, d_sink_weight );
				}
				else   add_term1(i,
						( dSmoothTerm[alpha_label + dPixelLabel[nPix] * num_labels]) * weight,
						( dSmoothTerm[dPixelLabel[i] + alpha_label*num_labels]) * weight,
						d_push_reser, d_sink_weight);
			}
			if ( x > 0 ) {
				nPix = i - 1;
				weight=dHcue[nPix];
				if ( dPixelLabel[nPix] == alpha_label )
					add_term1(i,
						( dSmoothTerm[alpha_label + dPixelLabel[nPix] * num_labels]) * weight,
						( dSmoothTerm[dPixelLabel[i] + alpha_label*num_labels]) * weight,
						d_push_reser, d_sink_weight );
			}
			if ( y > 0 ) {
				nPix = i - gRealSizeX;
				weight = dVcue[nPix] ;
				if ( dPixelLabel[nPix] == alpha_label ) {
					add_term1(i,
						( dSmoothTerm[alpha_label + alpha_label * num_labels]) * weight,
						( dSmoothTerm[dPixelLabel[i] + alpha_label*num_labels]) * weight,
						d_push_reser, d_sink_weight);
				}
			}
		}
	}
}

__global__
void CudaWeightCue(int alpha_label, int *d_left_weight, int *d_right_weight, int *d_down_weight,
		int *d_up_weight, int *d_push_reser, int *d_sink_weight, int *dPixelLabel,
		int *dDataTerm, int *dSmoothTerm, int *dHcue, int *dVcue, int gRealSizeX, int gRealSizeY, int num_labels ) {
	int gid = blockIdx.x * 256 + threadIdx.x ;
	add_t_links_Cue(alpha_label, gid, d_left_weight, d_right_weight, d_down_weight, d_up_weight, d_push_reser, d_sink_weight, dPixelLabel, dDataTerm, gRealSizeX, gRealSizeY, num_labels);
	set_up_expansion_energy_G_ARRAY_Cue(alpha_label, gid, d_left_weight, d_right_weight, d_down_weight, d_up_weight, d_push_reser, d_sink_weight, dPixelLabel, dDataTerm, dSmoothTerm, dHcue, dVcue, gRealSizeX, gRealSizeY, num_labels);
}

__global__
void CudaWeight(int alpha_label, int *d_left_weight, int *d_right_weight, int *d_down_weight,
		int *d_up_weight, int *d_push_reser, int *d_sink_weight, int *dPixelLabel,
		int *dDataTerm, int *dSmoothTerm, int gRealSizeX, int gRealSizeY, int num_labels) {
	int gid = blockIdx.x * 256 + threadIdx.x ;
	add_t_links(alpha_label, gid, d_left_weight, d_right_weight, d_down_weight, d_up_weight, d_push_reser, d_sink_weight, dPixelLabel, dDataTerm, gRealSizeX, gRealSizeY, num_labels);
	set_up_expansion_energy_G_ARRAY(alpha_label, gid, d_left_weight, d_right_weight, d_down_weight, d_up_weight, d_push_reser, d_sink_weight, dPixelLabel, dDataTerm, dSmoothTerm, gRealSizeX, gRealSizeY, num_labels);
}



/*********************************************************
 * function which adjusts the array size for efficiency **
 * consideration                                        **
 * ******************************************************/

__global__
void adjustedgeweight(int *d_left_weight, int *d_right_weight, int *d_down_weight, int *d_up_weight,
		int *d_push_reser, int *d_sink_weight, int *temp_left_weight, int *temp_right_weight,
		int *temp_down_weight, int *temp_up_weight, int *temp_push_reser, int *temp_sink_weight,
		int gRealSizeX, int gRealSizeY, int gRealSizeTotal, int gSizeX, int gSizeY, int gSizeTotal) {
	int gid = blockIdx.x * 256 + threadIdx.x ;
	if( gid < gSizeTotal ) {
		int row = gid / gSizeX , col = gid % gSizeX ;
		if(row < gRealSizeY && col < gRealSizeX) {
			temp_left_weight[row* gSizeX + col] = d_left_weight[row * gRealSizeX + col] ;
			temp_right_weight[row * gSizeX + col] = d_right_weight[row * gRealSizeX + col] ;
			temp_down_weight[row * gSizeX + col] = d_down_weight[row * gRealSizeX + col] ;
			temp_up_weight[row * gSizeX + col] = d_up_weight[row * gRealSizeX + col] ;
			temp_push_reser[row * gSizeX + col] = d_push_reser[row * gRealSizeX + col] ;
			temp_sink_weight[row * gSizeX + col] = d_sink_weight[row * gRealSizeX + col] ;

		}
		else {
			temp_left_weight[row * gSizeX + col] = 0 ;
			temp_right_weight[row * gSizeX + col] = 0 ;
			temp_down_weight[row * gSizeX + col] = 0 ;
			temp_up_weight[row * gSizeX + col] = 0 ;
			temp_push_reser[row * gSizeX + col] = 0 ;
			temp_sink_weight[row * gSizeX + col] = 0 ;
		}
	}
}

// Intializes memory on the gpu
__global__
void copyedgeweight( int *d_left_weight, int *d_right_weight, int *d_down_weight, int *d_up_weight,
		int *d_push_reser, int *d_sink_weight, int *temp_left_weight, int *temp_right_weight,
		int *temp_down_weight, int *temp_up_weight, int *temp_push_reser, int *temp_sink_weight,
		int *d_relabel_mask,
		int *d_graph_heightr, int *d_graph_heightw, int gRealSizeX, int height, int gRealSizeTotal, int gSizeX, int gSizeY, int gSizeTotal) {
	int gid = blockIdx.x * 256 + threadIdx.x ;
	if( gid < gSizeTotal ) {
		d_left_weight[gid] = temp_left_weight[gid] ;
		d_right_weight[gid] = temp_right_weight[gid] ;
		d_down_weight[gid] = temp_down_weight[gid] ;
		d_up_weight[gid] = temp_up_weight[gid] ;
		d_push_reser[gid] = temp_push_reser[gid] ;
		d_sink_weight[gid] = temp_sink_weight[gid] ;
		d_relabel_mask[gid] = 0 ;
		d_graph_heightr[gid] = 1 ;
		d_graph_heightw[gid] = 1 ;
	}
}

#endif
