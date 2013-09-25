/********************************************************************************************
* Implementing Graph Cuts on CUDA using algorithm given in CVGPU '08                       ** 
* paper "CUDA Cuts: Fast Graph Cuts on GPUs"                                               **  
* Copyright (c) 2008 International Institute of Information Technology.                    **  
* All rights reserved.                                                                     **
* Created By Vibhav Vineet.                                                                ** 
********************************************************************************************/


#ifndef _CUDACUTS_CU_
#define _CUDACUTS_CU_

#include "CudaCuts.h"

/********************************************************************
 * cudaCutsInit(width, height, numOfLabels) function sets the      **
 * width, height and numOfLabels of grid. It also initializes the  **
 * block size  on the device and finds the total number of blocks  **
 * running in parallel on the device. It calls checkDevice         **
 * function which checks whether CUDA compatible device is present **
 * on the system or not. It allocates the memory on the host and   **
 * the device for the arrays which are required through the        **
 * function call h_mem_init and segment_init respectively. This    **
 * function returns 0 on success or -1 on failure if there is no   **
 * * * CUDA compatible device is present on the system             **
 * *****************************************************************/

int cudaCutsInit(int widthGrid, int heightGrid, int labels)
{
	deviceCount = checkDevice();
//	printf("No. of devices %d\n",deviceCount);
	if( deviceCount < 1 )
		return -1;
	int cuda_device = 0;
	cudaSetDevice( cuda_device );
	cudaDeviceProp device_properties;
	CUDA_SAFE_CALL( cudaGetDeviceProperties(&device_properties, cuda_device) );
	int deviceVersion = device_properties.major * 10 + device_properties.minor; 
	if (deviceVersion == 10) 
		deviceCheck = 2; 
	else if (deviceVersion > 10) 
		deviceCheck = 1;
	else 
		deviceCheck = 0;
	gRealSizeX =  widthGrid; 
	gRealSizeY = heightGrid; 
	num_Labels = labels;
	blocks_x = 1;
	blocks_y = 1;
	num_of_blocks = 1; 
	num_of_threads_per_block = 256; 
	threads_x = 32;
	threads_y = 8;
	gSizeX = threads_x * ((int)ceil((float)gRealSizeX/ (float)threads_x));
	gSizeY = threads_y * ( (int)ceil((float) gRealSizeY / (float) threads_y ));
	gRealSizeTotal = gRealSizeX * gRealSizeY;
	gSizeTotal = gSizeX * gSizeY;
	size_int = sizeof(int) * gSizeTotal;
	blocks_x = (int)((ceil)((float)gSizeX/(float)threads_x));
	blocks_y = (int)((ceil)((float)gSizeY/(float)threads_y));
	num_of_blocks = (int)((ceil)((float)gSizeTotal/(float)num_of_threads_per_block));
	h_mem_init();
	d_mem_init();
	cueValues = 0;
	return deviceCheck;
}

int checkDevice() {
	int deviceCount ;
	cudaGetDeviceCount( &deviceCount );
	if(deviceCount == 0) {
		return -1;
	}
	return deviceCount ;
}

void h_mem_init() {
	h_reset_mem = (int* )malloc(sizeof(int) * gSizeTotal);
	h_graph_height = (int* )malloc(size_int);
	pixelLabel = (int*)malloc( size_int);
	h_pixel_mask = (bool*)malloc( sizeof(bool) * gSizeTotal);
	for( int i = 0; i < gSizeTotal; i++ ) {
		pixelLabel[i] = 0 ;
		h_graph_height[i] = 0 ;
	}
	for( int i = 0; i < gSizeTotal; i++ ) {
		h_reset_mem[i] = 0 ;
	}
}

void d_mem_init() {
	CUDA_SAFE_CALL( cudaMalloc((void**)&d_left_weight, sizeof(int) * gSizeTotal ) );
	CUDA_SAFE_CALL( cudaMalloc((void**)&d_right_weight, sizeof(int) * gSizeTotal ) );
	CUDA_SAFE_CALL( cudaMalloc((void**)&d_down_weight, sizeof(int) * gSizeTotal ) );
	CUDA_SAFE_CALL( cudaMalloc((void**)&d_up_weight, sizeof(int) * gSizeTotal ) );
	CUDA_SAFE_CALL( cudaMalloc((void**)&d_push_reser, sizeof(int) * gSizeTotal ) );
	CUDA_SAFE_CALL( cudaMalloc((void**)&d_sink_weight, sizeof(int) * gSizeTotal ) );

	CUDA_SAFE_CALL( cudaMalloc((void**)&d_pull_left, sizeof(int) * gSizeTotal ) );
	CUDA_SAFE_CALL( cudaMalloc((void**)&d_pull_right, sizeof(int) * gSizeTotal ) );
	CUDA_SAFE_CALL( cudaMalloc((void**)&d_pull_down, sizeof(int) * gSizeTotal ) );
	CUDA_SAFE_CALL( cudaMalloc((void**)&d_pull_up, sizeof(int) * gSizeTotal ) );

	CUDA_SAFE_CALL( cudaMalloc((void**)&s_left_weight, sizeof(int) * gSizeTotal ) );
	CUDA_SAFE_CALL( cudaMalloc((void**)&s_right_weight, sizeof(int) * gSizeTotal ) );
	CUDA_SAFE_CALL( cudaMalloc((void**)&s_down_weight, sizeof(int) * gSizeTotal ) );
	CUDA_SAFE_CALL( cudaMalloc((void**)&s_up_weight, sizeof(int) * gSizeTotal ) );
	CUDA_SAFE_CALL( cudaMalloc((void**)&s_push_reser, sizeof(int) * gSizeTotal ) );
	CUDA_SAFE_CALL( cudaMalloc((void**)&s_sink_weight, sizeof(int) * gSizeTotal ) );

	CUDA_SAFE_CALL( cudaMalloc((void**)&d_stochastic, sizeof(int) * num_of_blocks ) );
	CUDA_SAFE_CALL( cudaMalloc((void**)&d_stochastic_pixel, sizeof(int) * gSizeTotal ) );

	//CUDA_SAFE_CALL( cudaMalloc((void**)&d_sink_weight, sizeof(int) * graph_size1 ) );
	//CUDA_SAFE_CALL( cudaMalloc((void**)&d_sink_weight, sizeof(int) * graph_size1 ) );
	//CUDA_SAFE_CALL( cudaMalloc((void**)&d_sink_weight, sizeof(int) * graph_size1 ) );
	//CUDA_SAFE_CALL( cudaMalloc((void**)&d_sink_weight, sizeof(int) * graph_size1 ) );
	
	CUDA_SAFE_CALL( cudaMalloc((void**)&d_graph_heightr, sizeof(int) * gSizeTotal ) );
	CUDA_SAFE_CALL( cudaMalloc((void**)&d_graph_heightw, sizeof(int) * gSizeTotal ) );
	CUDA_SAFE_CALL( cudaMalloc((void**)&d_relabel_mask, sizeof(int) * gSizeTotal ) );

	CUDA_SAFE_CALL( cudaMalloc( ( void**)&d_pixel_mask, sizeof(bool)*gSizeTotal ) );
	CUDA_SAFE_CALL( cudaMalloc( ( void**)&d_over, sizeof(bool)*1 ) );
	CUDA_SAFE_CALL(cudaMalloc((void**)&d_counter,sizeof(int)));

	CUDA_SAFE_CALL( cudaMalloc( ( void **)&dPixelLabel, sizeof(int) * gSizeX * gSizeY ));
	CUDA_SAFE_CALL( cudaMemcpy( d_left_weight, h_reset_mem, sizeof( int ) * gSizeTotal , cudaMemcpyHostToDevice));
	CUDA_SAFE_CALL( cudaMemcpy( d_right_weight, h_reset_mem, sizeof( int ) * gSizeTotal , cudaMemcpyHostToDevice));
	CUDA_SAFE_CALL( cudaMemcpy( d_down_weight, h_reset_mem, sizeof( int ) * gSizeTotal , cudaMemcpyHostToDevice));
	CUDA_SAFE_CALL( cudaMemcpy( d_up_weight, h_reset_mem, sizeof( int ) * gSizeTotal , cudaMemcpyHostToDevice));
	CUDA_SAFE_CALL( cudaMemcpy( d_push_reser, h_reset_mem, sizeof( int ) * gSizeTotal , cudaMemcpyHostToDevice));
	CUDA_SAFE_CALL( cudaMemcpy( d_sink_weight, h_reset_mem, sizeof( int ) * gSizeTotal , cudaMemcpyHostToDevice));

	CUDA_SAFE_CALL( cudaMemcpy( d_pull_left, h_reset_mem, sizeof( int ) * gSizeTotal , cudaMemcpyHostToDevice));
	CUDA_SAFE_CALL( cudaMemcpy( d_pull_right, h_reset_mem, sizeof( int ) * gSizeTotal , cudaMemcpyHostToDevice));
	CUDA_SAFE_CALL( cudaMemcpy( d_pull_down, h_reset_mem, sizeof( int ) * gSizeTotal , cudaMemcpyHostToDevice));
	CUDA_SAFE_CALL( cudaMemcpy( d_pull_up, h_reset_mem, sizeof( int ) * gSizeTotal , cudaMemcpyHostToDevice));
	
	h_relabel_mask = (int*)malloc(sizeof(int)*gSizeX*gSizeY);
	h_stochastic = (int *)malloc(sizeof(int) * num_of_blocks);
	h_stochastic_pixel = (int *)malloc(sizeof(int) * gSizeTotal);
	for(int i = 0; i < gSizeTotal; i++ )
		h_relabel_mask[i] = 1;
	CUDA_SAFE_CALL( cudaMemcpy( d_relabel_mask, h_relabel_mask, sizeof(int) * gSizeTotal, cudaMemcpyHostToDevice));
	int *dpixlab = (int*)malloc(sizeof(int)*gSizeX*gSizeY);
	for( int i = 0 ; i < gSizeX * gSizeY ; i++ ) {
		dpixlab[i] = 0 ;
		h_stochastic_pixel[i] = 1 ; 
	}
	for(int i = 0 ; i < num_of_blocks ; i++ ) {
		h_stochastic[i] = 1 ; 
	}
	CUDA_SAFE_CALL(cudaMemcpy(d_stochastic, h_stochastic, sizeof(int) * num_of_blocks , cudaMemcpyHostToDevice));
	CUDA_SAFE_CALL(cudaMemcpy(d_stochastic_pixel, h_stochastic_pixel, sizeof(int)* gSizeTotal, cudaMemcpyHostToDevice));
	CUDA_SAFE_CALL( cudaMemcpy( dPixelLabel, dpixlab, sizeof(int) * gSizeX * gSizeY , cudaMemcpyHostToDevice));
}

int cudaCutsSetupDataTerm( int *dataTerm ) {
	if( deviceCheck < 1 )
		return -1 ; 
	datacost  =  (int*)malloc(sizeof(int) * gRealSizeX *gRealSizeY * num_Labels );
	CUDA_SAFE_CALL( cudaMalloc( ( void **)&dDataTerm, sizeof(int) * gRealSizeX * gRealSizeY * num_Labels ));
	CUDA_SAFE_CALL( cudaMemcpy( dDataTerm, dataTerm, sizeof(int) * gRealSizeX * gRealSizeY * num_Labels , cudaMemcpyHostToDevice   ) ) ;
	for( int i = 0 ; i < gRealSizeX * gRealSizeY * num_Labels ; i++) {
		datacost[i] = dataTerm[i] ; 
	}
	return 0 ; 
}

int cudaCutsSetupSmoothTerm( int *smoothTerm ) {
	if( deviceCheck < 1 )
		return -1 ; 
	smoothnesscost  =  (int*)malloc(sizeof(int) * num_Labels * num_Labels );
	CUDA_SAFE_CALL( cudaMalloc( ( void **)&dSmoothTerm, sizeof(int) * num_Labels * num_Labels ));
	CUDA_SAFE_CALL( cudaMemcpy( dSmoothTerm, smoothTerm, sizeof(int) * num_Labels * num_Labels, cudaMemcpyHostToDevice));
	for( int i = 0 ; i < num_Labels * num_Labels ; i++) {
		smoothnesscost[i] = smoothTerm[i] ; 
	}
	return 0 ; 
}

int cudaCutsSetupHCue( int *hCue )
{

	if( deviceCheck < 1 )
		return -1 ; 

	hcue  =  (int*)malloc(sizeof(int) * gRealSizeX * gRealSizeY );

	CUDA_SAFE_CALL( cudaMalloc( ( void **)&dHcue, sizeof(int) * gRealSizeX * gRealSizeY ));

	CUDA_SAFE_CALL( cudaMemcpy( dHcue, hCue, sizeof(int) * gRealSizeX * gRealSizeY , cudaMemcpyHostToDevice   ) ) ;

	for( int i = 0 ; i < gRealSizeX * gRealSizeY ; i++)
	{
		hcue[i] = hCue[i] ; 
	}

	cueValues = 1 ; 

	return 0 ; 
}

int cudaCutsSetupVCue( int *vCue )
{
	if( deviceCheck < 1 )
		return -1 ; 

	vcue  =  (int*)malloc(sizeof(int) * gSizeX * gSizeY );

	CUDA_SAFE_CALL( cudaMalloc( ( void **)&dVcue, sizeof(int) * gRealSizeX * gRealSizeY ));

	CUDA_SAFE_CALL( cudaMemcpy( dVcue, vCue, sizeof(int) * gRealSizeX * gRealSizeY , cudaMemcpyHostToDevice   ) ) ;

	for( int i = 0 ; i < gRealSizeX * gRealSizeY ; i++)
	{
		vcue[i] = vCue[i] ; 
	}

	return 0 ; 
}


int cudaCutsSetupGraph() {
	if( deviceCheck < 1 )
		return -1 ; 
	int alpha_label = 1 ;
	for( int i = 0 ; i < gSizeTotal ; i++ ) {
		h_reset_mem[i] = 0 ;
		h_graph_height[i] = 0 ;
	}
	int blockEdge = (int)((ceil)((float)( gRealSizeX * gRealSizeY )/ ( float ) 256 ));
	dim3 block_weight(256, 1, 1);
	dim3 grid_weight(blockEdge,1,1);
	if( cueValues == 1 ) {
		CudaWeightCue<<< grid_weight, block_weight >>>( alpha_label, d_left_weight, d_right_weight, d_down_weight,
						d_up_weight, d_push_reser, d_sink_weight, dPixelLabel, dDataTerm, 
						dSmoothTerm, dHcue, dVcue, gRealSizeX, gRealSizeY, 2) ;
	} else {
		CudaWeight<<< grid_weight , block_weight >>>( alpha_label, d_left_weight, d_right_weight, d_down_weight, 
						d_up_weight, d_push_reser, d_sink_weight, dPixelLabel, dDataTerm, 
						dSmoothTerm, gRealSizeX, gRealSizeY, 2) ;
	}
	int *temp_left_weight, *temp_right_weight, *temp_down_weight, *temp_up_weight, *temp_source_weight, *temp_terminal_weight ;

	CUDA_SAFE_CALL( cudaMalloc( ( void **)&temp_left_weight, sizeof( int ) * gSizeTotal ) ) ;
	CUDA_SAFE_CALL( cudaMalloc( ( void **)&temp_right_weight, sizeof( int ) * gSizeTotal ) ) ;
	CUDA_SAFE_CALL( cudaMalloc( ( void **)&temp_down_weight, sizeof( int ) * gSizeTotal ) ) ;
	CUDA_SAFE_CALL( cudaMalloc( ( void **)&temp_up_weight, sizeof( int ) * gSizeTotal ) ) ;
	CUDA_SAFE_CALL( cudaMalloc( ( void **)&temp_source_weight, sizeof( int ) * gSizeTotal ) ) ;
	CUDA_SAFE_CALL( cudaMalloc( ( void **)&temp_terminal_weight, sizeof( int ) * gSizeTotal ) ) ;

	int blockEdge1 = (int)((ceil)((float)( gSizeX * gSizeY )/ ( float ) 256 ));
	dim3 block_weight1(256, 1, 1);
	dim3 grid_weight1(blockEdge1,1,1);
	adjustedgeweight<<<grid_weight1, block_weight1>>>(d_left_weight, d_right_weight, d_down_weight, d_up_weight, 
		d_push_reser,d_sink_weight, temp_left_weight, temp_right_weight, temp_down_weight, temp_up_weight,
		temp_source_weight, temp_terminal_weight, gRealSizeX,  gRealSizeY,  gRealSizeTotal,  gSizeX, 
		gSizeY, gSizeTotal) ;
	copyedgeweight<<<grid_weight1, block_weight1>>>(d_left_weight, d_right_weight, d_down_weight, d_up_weight, 
		d_push_reser, d_sink_weight, temp_left_weight, temp_right_weight, temp_down_weight,
		temp_up_weight,temp_source_weight, temp_terminal_weight, d_relabel_mask,
		d_graph_heightr, d_graph_heightw, gRealSizeX,  gRealSizeY,  gRealSizeTotal,  gSizeX, gSizeY, gSizeTotal);
	return 0 ; 
}

int cudaCutsAtomicOptimize(  ) {
	if( deviceCheck < 1 ) {
		return -1 ; 
	}
	cudaCutsAtomic();
	bfsLabeling( );
	return 0 ; 
}

int cudaCutsStochasticOptimize() {
	if( deviceCheck < 1 ) {
		return -1 ; 
	}
	cudaCutsStochastic();
	bfsLabeling();
	return 0 ; 
}

void cudaCutsAtomic() {
    printf("Grid dimensions (non-persistent):\n");
    printf("\tthreads_x=%d, threads_y=%d, threads_per_block=%d\n", threads_x, threads_y, threads_x*threads_y);
    printf("\tblocks_x=%d, blocks_y=%d, blocks_per_grid=%d\n", blocks_x, blocks_y, blocks_x*blocks_y);

    // Calculate grid dimensions for persistent threads
    const int max_blocks = 6*16;
    int blocks_xp = blocks_x;
    int blocks_yp = blocks_y;
    if(max_blocks < blocks_x*blocks_y) {
        // Scale worksize tile proportionally
        float blocks_xp_f = sqrt((float) max_blocks * (float) blocks_x / (float) blocks_y);
        blocks_xp = (int) blocks_xp_f;
        blocks_yp = (int)(blocks_xp_f * (float)blocks_y / (float)blocks_x);
        if((blocks_xp+1)*blocks_yp <= max_blocks || blocks_xp*(blocks_yp+1) <= max_blocks) {
            // We can safely increase dimension and still fit
            if( (blocks_xp+1)*blocks_yp > blocks_xp*(blocks_yp+1) )
                blocks_xp++;
            else
                blocks_yp++;
        }
    }
    printf("Grid dimensions (persistent):\n");
    printf("\tthreads_x=%d, threads_y=%d, threads_per_block=%d\n", threads_x, threads_y, threads_x*threads_y);
    printf("\tblocks_x=%d, blocks_y=%d, blocks_per_grid=%d\n", blocks_xp, blocks_yp, blocks_xp*blocks_yp);
    printf("\n");

	dim3 block_push(threads_x, threads_y, 1);
	dim3 grid_push(blocks_x, blocks_y, 1);
	dim3 block_push_p(threads_x, threads_y, 1);
	dim3 grid_push_p(blocks_xp, blocks_yp, 1);
	dim3 d_block(num_of_threads_per_block,1,1);
	dim3 d_grid(num_of_blocks,1,1);
	bool finish = true ;
	counter = num_of_blocks ;
	int numThreadsEnd = 256, numBlocksEnd = 1 ;
	if( numThreadsEnd > counter) {
		numBlocksEnd = 1 ;
		numThreadsEnd = counter ;
	}
	else {
		numBlocksEnd = (int)ceil(counter/(double)numThreadsEnd);
	}
	dim3 End_block(numThreadsEnd,1,1);
	dim3 End_grid(numBlocksEnd,1,1);
	int *d_counter;
	bool *d_finish; 
	for(int i = 0 ; i < num_of_blocks ; i++ ) {
		h_stochastic[i] = 0 ; 
	}

	CUDA_SAFE_CALL( cudaMalloc((void**)&d_counter, sizeof(int)));
	CUDA_SAFE_CALL( cudaMalloc((void**)&d_finish, sizeof(bool)));
	CUDA_SAFE_CALL( cudaMemcpy( d_counter, &counter, sizeof(int), cudaMemcpyHostToDevice));
	counter = 0;
	int *d_relabel;
	CUDA_SAFE_CALL( cudaMalloc((void**)&d_relabel,sizeof(int) ));
	int h_relabel = 0;
	int block_num = gSizeX / 32;
	int *d_block_num;
	CUDA_SAFE_CALL( cudaMalloc((void**)&d_block_num, sizeof(int)));
	CUDA_SAFE_CALL( cudaMemcpy( d_block_num, &block_num, sizeof(int), cudaMemcpyHostToDevice));
	int h_count_blocks = num_of_blocks ; 
	int *d_count_blocks;
	CUDA_SAFE_CALL( cudaMalloc((void**)&d_count_blocks, sizeof(int)));
	CUDA_SAFE_CALL( cudaMemcpy( d_count_blocks, &h_count_blocks, sizeof(int), cudaMemcpyHostToDevice));
	h_count_blocks = 0;
	CUDA_SAFE_CALL( cudaMemcpy(d_relabel, &h_relabel, sizeof(int), cudaMemcpyHostToDevice));
	int sum_at_start = cudaCutsTotalWeightSum(d_push_reser, d_sink_weight);
	printf("SUM AT START = %d\n", sum_at_start);
	counter = 1 ; 
	kernel_start_sink<<<grid_push,block_push>>>(d_left_weight,d_right_weight, d_down_weight, d_up_weight,
			d_sink_weight, d_push_reser,
			d_relabel_mask,d_graph_heightr, gRealSizeTotal,gRealSizeX,gRealSizeY,
			gSizeTotal, gSizeX , gSizeY,d_relabel, d_stochastic, d_counter, d_finish );
	kernel_relabel<<<grid_push,block_push>>>(d_left_weight,d_right_weight, d_down_weight, d_up_weight,
	                        d_sink_weight, d_push_reser,
	                        d_relabel_mask,d_graph_heightr,gRealSizeTotal,gRealSizeX,gRealSizeY,
	                        gSizeTotal, gSizeX , gSizeY);
	CUDA_SAFE_CALL(cudaThreadSynchronize());
//	unsigned int timer = 0;
//	CUT_SAFE_CALL(cutCreateTimer(&timer));
//	CUT_SAFE_CALL(cutStartTimer(timer));
	do {
        kernel_push<<<grid_push_p,block_push_p>>>(9, blocks_x, blocks_y,
                d_left_weight,d_right_weight, d_down_weight, d_up_weight,
                d_pull_left, d_pull_right, d_pull_down, d_pull_up,
                d_sink_weight, d_push_reser,
                d_relabel_mask,d_graph_heightr,gRealSizeTotal,gRealSizeX,gRealSizeY,
                gSizeTotal, gSizeX , gSizeY );
        kernel_pull_end<<<grid_push,block_push>>>(d_left_weight,d_right_weight, d_down_weight, d_up_weight,
                d_pull_left, d_pull_right, d_pull_down, d_pull_up,
                d_push_reser,
                gRealSizeTotal,gRealSizeX,gRealSizeY,gSizeTotal,gSizeX,gSizeY );
        // Check finish criteria
        finish = true ;
        CUDA_SAFE_CALL( cudaMemcpy( d_finish, &finish, sizeof(bool), cudaMemcpyHostToDevice));
        kernel_push_stochastic1<<<grid_push,block_push>>>(d_push_reser, s_push_reser,  d_count_blocks, d_finish, d_block_num, gSizeX);
        CUDA_SAFE_CALL( cudaMemcpy( &finish, d_finish, sizeof(bool), cudaMemcpyDeviceToHost));
        // Run 1 iteration (k=1)
        kernel_push<<<grid_push_p,block_push_p>>>(1, blocks_x, blocks_y,
                        d_left_weight,d_right_weight, d_down_weight, d_up_weight,
                        d_pull_left, d_pull_right, d_pull_down, d_pull_up,
                        d_sink_weight, d_push_reser,
                        d_relabel_mask,d_graph_heightr,gRealSizeTotal,gRealSizeX,gRealSizeY,
                        gSizeTotal, gSizeX , gSizeY );
        kernel_pull_end<<<grid_push,block_push>>>(d_left_weight,d_right_weight, d_down_weight, d_up_weight,
                d_pull_left, d_pull_right, d_pull_down, d_pull_up,
                d_push_reser,
                gRealSizeTotal,gRealSizeX,gRealSizeY,gSizeTotal,gSizeX,gSizeY );
        CUDA_SAFE_CALL(cudaMemset(d_stochastic, 0, sizeof(int)*num_of_blocks));
        h_count_blocks = 0 ;
        CUDA_SAFE_CALL( cudaMemcpy( d_count_blocks, &h_count_blocks, sizeof(int), cudaMemcpyHostToDevice));
        kernel_push_stochastic2<<<grid_push,block_push>>>(d_push_reser, s_push_reser, d_stochastic, d_block_num, gSizeX);
        kernel_End<<<End_grid, End_block>>>(d_stochastic, d_count_blocks, d_counter);
	counter++;
//	printf("counter=%d\n", counter);
	}
	while(finish);
    int sum_at_end = cudaCutsTotalWeightSum(d_push_reser, d_sink_weight);
    printf("SUM AT END = %d\n", sum_at_end);
	CUDA_SAFE_CALL(cudaThreadSynchronize());
//	CUT_SAFE_CALL(cutStopTimer(timer));
//	printf("TT Cuts :: %f\n",cutGetTimerValue(timer));
//	CUT_SAFE_CALL(cutDeleteTimer(timer));

}

int cudaCutsTotalWeightSum(int* d_push_reser, int* d_sink_weight) {
    int* h_temp_push_reser = (int*)malloc(sizeof(int) * gSizeTotal);
    int* h_temp_sink_weight = (int*)malloc(sizeof(int) * gSizeTotal);
    CUDA_SAFE_CALL( cudaMemcpy( h_temp_push_reser, d_push_reser, sizeof(int) * gSizeTotal, cudaMemcpyDeviceToHost));
    CUDA_SAFE_CALL( cudaMemcpy( h_temp_sink_weight, d_sink_weight, sizeof(int) * gSizeTotal, cudaMemcpyDeviceToHost));
    int sum = 0;
    for(int i=0; i<gSizeTotal; i++)
        sum += h_temp_push_reser[i];
    for(int i=0; i<gSizeTotal; i++)
        sum -= h_temp_sink_weight[i];
    free(h_temp_push_reser);
    free(h_temp_sink_weight);
    return sum;
}

void cudaCutsStochastic() {
	dim3 block_push(threads_x, threads_y, 1);
	dim3 grid_push(blocks_x, blocks_y, 1);
	dim3 d_block(num_of_threads_per_block,1,1);
	dim3 d_grid(num_of_blocks,1,1);
	bool finish = true ;
	counter = num_of_blocks ;
	int numThreadsEnd = 256, numBlocksEnd = 1 ; 
	if( numThreadsEnd > counter) {
		numBlocksEnd = 1 ; 
		numThreadsEnd = counter ; 
	}
	else {
		numBlocksEnd = (int)ceil(counter/(double)numThreadsEnd);
	}
	dim3 End_block(numThreadsEnd,1,1);
	dim3 End_grid(numBlocksEnd,1,1);
	bool *d_finish ; 
	for(int i = 0 ; i < num_of_blocks ; i++ ) {
		h_stochastic[i] = 0 ; 
	}
	CUDA_SAFE_CALL( cudaMalloc((void**)&d_counter, sizeof(int)));
	CUDA_SAFE_CALL( cudaMalloc((void**)&d_finish, sizeof(bool)));
	CUDA_SAFE_CALL( cudaMemcpy( d_counter, &counter, sizeof(int), cudaMemcpyHostToDevice));
	counter = 0;
	int *d_relabel;
	CUDA_SAFE_CALL( cudaMalloc((void**)&d_relabel,sizeof(int) ));
	int h_relabel = 0;
	int block_num = gSizeX / 32;
	int *d_block_num;
	CUDA_SAFE_CALL( cudaMalloc((void**)&d_block_num, sizeof(int)));
	CUDA_SAFE_CALL( cudaMemcpy( d_block_num, &block_num, sizeof(int), cudaMemcpyHostToDevice));
	int h_count_blocks = num_of_blocks ; 
	int *d_count_blocks;
	CUDA_SAFE_CALL( cudaMalloc((void**)&d_count_blocks, sizeof(int)));
	CUDA_SAFE_CALL( cudaMemcpy( d_count_blocks, &h_count_blocks, sizeof(int), cudaMemcpyHostToDevice));
	h_count_blocks = 0 ;
	CUDA_SAFE_CALL( cudaMemcpy(d_relabel, &h_relabel, sizeof(int), cudaMemcpyHostToDevice));
	counter = 1 ; 
	kernel_push1_start_stochastic<<<grid_push,block_push>>>(d_left_weight,d_right_weight, d_down_weight, d_up_weight, 
			d_sink_weight, d_push_reser,
			d_relabel_mask,d_graph_heightr,d_graph_heightw, gRealSizeTotal,gRealSizeX,gRealSizeY, 
			gSizeTotal, gSizeX , gSizeY,d_relabel, d_stochastic, d_counter, d_finish );
	CUDA_SAFE_CALL(cudaThreadSynchronize());
//	unsigned int timer = 0;
//	CUT_SAFE_CALL(cutCreateTimer(&timer));
//	CUT_SAFE_CALL(cutStartTimer(timer));
	do {
		if(counter%10 == 0) {
			finish = true ; 
			CUDA_SAFE_CALL( cudaMemcpy( d_finish, &finish, sizeof(bool), cudaMemcpyHostToDevice));
			kernel_push_stochastic1<<<grid_push,block_push>>>(d_push_reser, s_push_reser,  d_count_blocks, d_finish, d_block_num, gSizeX);
			CUDA_SAFE_CALL( cudaMemcpy( &finish, d_finish, sizeof(bool), cudaMemcpyDeviceToHost));
		}
		if(counter%11 == 0 ) {
			CUDA_SAFE_CALL(cudaMemset(d_stochastic, 0, sizeof(int)*num_of_blocks));
			h_count_blocks = 0 ; 
			CUDA_SAFE_CALL( cudaMemcpy( d_count_blocks, &h_count_blocks, sizeof(int), cudaMemcpyHostToDevice));
			kernel_push_stochastic2<<<grid_push,block_push>>>(d_push_reser, s_push_reser, d_stochastic, d_block_num, gSizeX);
			
			kernel_End<<<End_grid, End_block>>>(d_stochastic, d_count_blocks, d_counter);
		}
		if( counter % 2 == 0 ) {
			kernel_push1_stochastic<<<grid_push,block_push>>>(d_left_weight, d_right_weight, d_down_weight, 
					d_up_weight, d_sink_weight, d_push_reser,
					d_relabel_mask, d_graph_heightr, d_graph_heightw, gRealSizeTotal, gRealSizeX,
					gRealSizeY, gSizeTotal, gSizeX , gSizeY, d_stochastic, d_block_num);
			kernel_relabel_stochastic<<<grid_push,block_push>>>(d_left_weight, d_right_weight, d_down_weight, 
					d_up_weight, d_sink_weight, d_push_reser,
					d_relabel_mask,d_graph_heightr,d_graph_heightw, gRealSizeTotal, gRealSizeX, 
					gRealSizeY, gSizeTotal, gSizeX , gSizeY, d_stochastic,d_block_num );
		}
		else {
			kernel_push1_stochastic<<<grid_push,block_push>>>(d_left_weight,d_right_weight, d_down_weight, 
					d_up_weight, d_sink_weight, d_push_reser,
					d_relabel_mask,d_graph_heightw,d_graph_heightr, gRealSizeTotal, gRealSizeX, 
					gRealSizeY, gSizeTotal, gSizeX , gSizeY, d_stochastic, d_block_num);
			
			kernel_relabel_stochastic<<<grid_push,block_push>>>(d_left_weight,d_right_weight, d_down_weight, 
					d_up_weight, d_sink_weight, d_push_reser,
					d_relabel_mask,d_graph_heightw,d_graph_heightr, gRealSizeTotal,gRealSizeX,
					gRealSizeY, gSizeTotal, gSizeX , gSizeY, d_stochastic, d_block_num );
		}
		counter++ ;
	}
	while(finish);
	CUDA_SAFE_CALL(cudaThreadSynchronize());
//	CUT_SAFE_CALL(cutStopTimer(timer));
//	printf("TT Cuts :: %f\n",cutGetTimerValue(timer));
//	CUT_SAFE_CALL(cutDeleteTimer(timer));
}

void bfsLabeling() {
	dim3 block_push(threads_x, threads_y, 1);
	dim3 grid_push(blocks_x, blocks_y, 1);
	dim3 d_block(num_of_threads_per_block,1,1);
	dim3 d_grid(num_of_blocks,1,1);
	CUDA_SAFE_CALL( cudaMemcpy( d_graph_heightr, h_graph_height, size_int, cudaMemcpyHostToDevice));
	for(int i = 0 ; i < gRealSizeTotal ; i++ )
		h_pixel_mask[i]=true;
	CUDA_SAFE_CALL( cudaMemcpy( d_pixel_mask, h_pixel_mask, sizeof(bool) * gSizeTotal, cudaMemcpyHostToDevice));
	kernel_bfs_t<<<d_grid,d_block,0>>>(d_push_reser,d_sink_weight,d_graph_heightr,d_pixel_mask,gRealSizeTotal,gRealSizeX,gRealSizeY, gSizeTotal, gSizeX, gSizeY);
	counter=1;

	CUDA_SAFE_CALL( cudaMemcpy( d_counter, &counter, sizeof(int), cudaMemcpyHostToDevice));
	do {
		h_over=false;
		CUDA_SAFE_CALL( cudaMemcpy( d_over, &h_over, sizeof(bool), cudaMemcpyHostToDevice) );
		kernel_bfs<<< d_grid,d_block, 0 >>>(d_left_weight, d_right_weight, d_down_weight, d_up_weight, d_graph_heightr, d_pixel_mask,
				gRealSizeTotal, gRealSizeX, gRealSizeY, gSizeTotal, gSizeX, gSizeY, d_over,d_counter);
		CUT_CHECK_ERROR("Kernel execution failed");
		CUDA_SAFE_CALL( cudaMemcpy( &h_over, d_over, sizeof(bool), cudaMemcpyDeviceToHost) );
		counter++;
		CUDA_SAFE_CALL(cudaMemcpy(d_counter,&counter,sizeof(int),cudaMemcpyHostToDevice));
	}
	while(h_over);
	CUDA_SAFE_CALL(cudaMemcpy(h_graph_height,d_graph_heightr,size_int,cudaMemcpyDeviceToHost));
}


int cudaCutsGetResult( ) {
	if( deviceCheck < 1 )
		return -1 ; 
	int alpha = 1 ;
	for(int i = 0 ; i < gSizeTotal ; i++ ) {
		int row_here = i / gSizeX, col_here = i % gSizeX ;
		if(h_graph_height[i]>0 && row_here < gRealSizeY && row_here > 0 && col_here < gRealSizeX && col_here > 0 ) {
			pixelLabel[i]=alpha;
		}
	}
	return 0;
}

int cudaCutsGetEnergy() {
	return data_energy() + smooth_energy() ;
}

int data_energy() {
	int eng=0;
	for(int i = 0 ; i < gRealSizeY ; i ++) {
		for(int j = 0 ; j < gRealSizeX ; j++) {
			eng += datacost(i*gRealSizeX+j, pixelLabel[i*gSizeX+j]);
		}
	}
	printf("DATA ENERGY: %d\n",eng);
	return(eng);
}

int smooth_energy() {
	int eng = 0;
	int x,y;
	for ( y = 0; y < gRealSizeY; y++ )
		for ( x = 1; x < gRealSizeX; x++ ) {
			if( cueValues == 1 )
				eng = eng + smoothnesscost(pixelLabel[y*gSizeX+x],pixelLabel[y*gSizeX+x-1])*hcue[y*gRealSizeX+x-1];
			else
				eng = eng + smoothnesscost(pixelLabel[y*gSizeX+x],pixelLabel[y*gSizeX+x-1]);
		}
	for ( y = 1; y < gSizeY; y++ )
		for ( x = 0; x < gSizeX; x++ ) {
			if(cueValues == 1)
				eng = eng + smoothnesscost(pixelLabel[y*gSizeX+x],pixelLabel[y*gSizeX+x-gSizeX])*vcue[y*gRealSizeX+x-gRealSizeX];
			else
				eng = eng + smoothnesscost(pixelLabel[y*gSizeX+x],pixelLabel[y*gSizeX+x-gSizeX]);
		}
	printf("SMOOTHNESS ENERGY: %d\n",eng);
	return(eng);
}


void cudaCutsFreeMem() {
	free(h_reset_mem);
	free(h_graph_height);
	CUDA_SAFE_CALL(cudaFree(d_left_weight));
	CUDA_SAFE_CALL(cudaFree(d_right_weight));
	CUDA_SAFE_CALL(cudaFree(d_down_weight));
	CUDA_SAFE_CALL(cudaFree(d_up_weight));
	CUDA_SAFE_CALL(cudaFree(d_sink_weight));
	CUDA_SAFE_CALL(cudaFree(d_push_reser));
	CUDA_SAFE_CALL(cudaFree(d_pull_left));
	CUDA_SAFE_CALL(cudaFree(d_pull_right));
	CUDA_SAFE_CALL(cudaFree(d_pull_down));
	CUDA_SAFE_CALL(cudaFree(d_pull_up));
	CUDA_SAFE_CALL(cudaFree(d_graph_heightr));
	CUDA_SAFE_CALL(cudaFree(d_graph_heightw));
}

#endif

