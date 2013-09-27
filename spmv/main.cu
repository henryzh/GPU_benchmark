// UIUC IMPACT
#include "parboil.h"
#include <stdio.h>
#include <stdlib.h>

#include "file.h"
#include "gpu_info.h"
#include "spmv_jds.h"
#include "jds_kernels.cu"
#include "convert_dataset.h"
/*
static int generate_vector(float *x_vector, int dim) {	
	srand(54321);	
	for(int i=0;i<dim;i++) {
		x_vector[i] = (rand() / (float) RAND_MAX);
	}
	return 0;
}
*/
int main(int argc, char** argv) {
	struct pb_TimerSet timers;
	struct pb_Parameters *parameters;
	parameters = pb_ReadParameters(&argc, argv);
	if ((parameters->inpFiles[0] == NULL) || (parameters->inpFiles[1] == NULL)) {
		fprintf(stderr, "Expecting one two filenames\n");
		exit(-1);
	}
	pb_InitializeTimerSet(&timers);
	pb_SwitchToTimer(&timers, pb_TimerID_COMPUTE);
	int len;
	int depth;
	int dim;
	int pad=32;
	int nzcnt_len;
	float *h_data;
	int *h_indices;
	int *h_ptr;
	int *h_perm;
	int *h_nzcnt;
	float *h_Ax_vector;
	float *h_x_vector;
	float *d_data;
	int *d_indices;
	int *d_ptr;
	int *d_perm;
	int *d_nzcnt;
	float *d_Ax_vector;
	float *d_x_vector;
	pb_SwitchToTimer(&timers, pb_TimerID_IO);
	int col_count;
//	printf("Input file %s\n", parameters->inpFiles[0]);
	coo_to_jds(
		parameters->inpFiles[0], // bcsstk32.mtx, fidapm05.mtx, jgl009.mtx
		1, // row padding
		pad, // warp size
		1, // pack size
		1, // is mirrored?
		0, // binary matrix
		0, // debug level [0:2]
		&h_data, &h_ptr, &h_nzcnt, &h_indices, &h_perm,
		&col_count, &dim, &len, &nzcnt_len, &depth
	);
	h_Ax_vector=(float*)malloc(sizeof(float)*dim);
	h_x_vector=(float*)malloc(sizeof(float)*dim);
	input_vec( parameters->inpFiles[1],h_x_vector,dim);
	pb_SwitchToTimer(&timers, pb_TimerID_COPY);
	cudaMalloc((void **)&d_data, len*sizeof(float));
	cudaMalloc((void **)&d_indices, len*sizeof(int));
	cudaMalloc((void **)&d_ptr, depth*sizeof(int));
	cudaMalloc((void **)&d_perm, dim*sizeof(int));
	cudaMalloc((void **)&d_nzcnt, nzcnt_len*sizeof(int));
	cudaMalloc((void **)&d_x_vector, dim*sizeof(float));
	cudaMalloc((void **)&d_Ax_vector,dim*sizeof(float));
	cudaMemset( (void *) d_Ax_vector, 0, dim*sizeof(float));
	cudaMemcpy(d_data, h_data, len*sizeof(float), cudaMemcpyHostToDevice);
	cudaMemcpy(d_indices, h_indices, len*sizeof(int), cudaMemcpyHostToDevice);
	cudaMemcpy(d_perm, h_perm, dim*sizeof(int), cudaMemcpyHostToDevice);
	cudaMemcpy(d_x_vector, h_x_vector, dim*sizeof(int), cudaMemcpyHostToDevice);
	cudaMemcpyToSymbol(jds_ptr_int, h_ptr, depth*sizeof(int));
	cudaMemcpyToSymbol(sh_zcnt_int, h_nzcnt,nzcnt_len*sizeof(int));
	cudaThreadSynchronize();
	pb_SwitchToTimer(&timers, pb_TimerID_COMPUTE);
	unsigned int grid;
	unsigned int block;
	cudaDeviceProp deviceProp;
	cudaGetDeviceProperties(&deviceProp, 0);
	compute_active_thread(&block, &grid,nzcnt_len,pad, deviceProp.major,deviceProp.minor,
					deviceProp.warpSize,deviceProp.multiProcessorCount);
//	cudaFuncSetCacheConfig(spmv_jds_naive, cudaFuncCachePreferL1);

	//main execution
	pb_SwitchToTimer(&timers, pb_TimerID_KERNEL);
//	for (int i=0; i<50; i++)
	spmv_jds_naive<<<grid, block>>>(d_Ax_vector, d_data, d_indices, d_perm, d_x_vector, d_nzcnt, dim);
	CUERR // check and clear any existing errors
	cudaThreadSynchronize();
	pb_SwitchToTimer(&timers, pb_TimerID_COPY);
	cudaMemcpy(h_Ax_vector, d_Ax_vector,dim*sizeof(float), cudaMemcpyDeviceToHost);	
	cudaThreadSynchronize();
	cudaFree(d_data);
	cudaFree(d_indices);
	cudaFree(d_ptr);
	cudaFree(d_perm);
	cudaFree(d_nzcnt);
	cudaFree(d_x_vector);
	cudaFree(d_Ax_vector);
	if (parameters->outFile) {
		pb_SwitchToTimer(&timers, pb_TimerID_IO);
		outputData(parameters->outFile,h_Ax_vector,dim);
	}
	pb_SwitchToTimer(&timers, pb_TimerID_COMPUTE);
	free (h_data);
	free (h_indices);
	free (h_ptr);
	free (h_perm);
	free (h_nzcnt);
	free (h_Ax_vector);
	free (h_x_vector);
	pb_SwitchToTimer(&timers, pb_TimerID_NONE);
	pb_PrintTimerSet(&timers);
	pb_FreeParameters(parameters);
	return 0;
}
