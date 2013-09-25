//Stencil, IMPACT UIUC
#include <stdio.h>
#include <stdlib.h>
#include "parboil.h"
#include "common.h"
#include "barrier.cu"
#include "kernels.cu"
void stencil_gold(float c0, float c1, float* A0, int iterations, float* result, int nx, int ny, int nz) {
	int size=nx*ny*nz;
	float* input = (float*) malloc( sizeof(float)*size);
	float* output = (float*) malloc( sizeof(float)*size);
	memcpy(input, A0, sizeof(float)*size);
	for(int i=0 ;i<iterations; i++) {
		for(int z=1; z<nz-1; z++) {
			for(int y=1; y<ny-1; y++) {
				for(int x=1; x<nx-1; x++) {
					output[Index3D(nx,ny,x,y,z)] = (input[Index3D(nx,ny,x+1,y,z)] +
						input[Index3D(nx,ny,x-1,y,z)] + input[Index3D(nx,ny,x,y+1,z)] + 
						input[Index3D(nx,ny,x,y-1,z)] + input[Index3D(nx,ny,x,y,z+1)] + 
						input[Index3D(nx,ny,x,y,z-1)])*c1-c0*input[Index3D(nx,ny,x,y,z)];
				}
			}
		}
		float* temp_buff = input;
		input = output;
		output = temp_buff;
	}
	memcpy(result, input, sizeof(float)*size);
	free(input);
	free(output);
}

void print_error(float* real_result, float* gold_result, int nx, int ny, int nz) {
	float error_sum = 0.0f;
	for(int z=1; z<nz-1; z++) {
		for(int y=1; y<ny-1; y++) {
			for(int x=1; x<nx-1; x++) {
				error_sum += abs(real_result[Index3D(nx,ny,x,y,z)] - gold_result[Index3D(nx,ny,x,y,z)]);
			}
		}
	}
	printf("[BENCH] Total error = %f\n", error_sum);
	printf("[BENCH] Average error = %f\n", error_sum/((nz-1)*(ny-1)*(nx-1)));
}

void generateInput(float* input, int nx, int ny, int nz) {
    for(int z=0; z<nz; z++) {
        for(int y=0; y<ny; y++) {
            for(int x=0; x<nx; x++) {
                int index = Index3D(nx, ny, x, y, z);
                // Fit N periods of a sinusoid in each dimension
                const float maxAmp = 5.0f;
                const float N = 2;
                float fx, fy, fz;
                fx = (float) x / (float)nx * 2.0f * PI * N;
                fy = (float) y / (float)ny * 2.0f * PI * N;
                fz = (float) z / (float)nz * 2.0f * PI * N;
                input[index] = maxAmp*sin( sqrt(fx*fx + fy*fy + fz*fz));
            }
        }
    }
}
/*
static void inputData(float *A0, int nx, int ny, int nz, FILE *fp) {
	unsigned size;
	size = nx*ny*nz;
	if(fread(A0,sizeof(float),size,fp) != size)
		printf("Reading error\n");
}
*/
void outputData(char* fName, float *h_A0, int nx, int ny, int nz) {
	FILE* fid = fopen(fName, "w");
	unsigned size;
	if (fid == NULL) {
		fprintf(stderr, "Cannot open output file\n");
		exit(-1);
	}
	size = nx*ny*nz;
	fwrite(&size, sizeof(unsigned), 1, fid);
	fwrite(h_A0, sizeof(float), size, fid);
	fclose (fid);
}

int main(int argc, char** argv) {
#ifdef TIMING
	struct pb_TimerSet timers;
	pb_InitializeTimerSet(&timers);
	pb_SwitchToTimer(&timers, pb_TimerID_COMPUTE);
#endif
	struct pb_Parameters *parameters;
	parameters = pb_ReadParameters(&argc, argv);
	int nx=1024, ny=4, nz=4;
	int size;
	int iteration = 10;
	float c0=1.0f/6.0f;
	float c1=1.0f/6.0f/6.0f;
/*
	if (argc<5) {
          printf("Usage: probe nx ny nz tx ty t\n"
	     "nx: the grid size x\n"
	     "ny: the grid size y\n"
	     "nz: the grid size z\n"
	     "t: the iteration time\n");
	  return -1;
	}
	nx = atoi(argv[1]);
	if (nx<1)
		return -1;
	ny = atoi(argv[2]);
	if (ny<1)
		return -1;
	nz = atoi(argv[3]);
	if (nz<1)
		return -1;
	iteration = atoi(argv[4]);
	if(iteration<1)
		return -1;
*/
#ifdef TILE_2D
	printf("[BENCH] CUDA 2D-Tiled Stencil\n");
#endif
#ifdef TILE_3D_NEW
	printf("[BENCH] CUDA 3D-Tiled-new Stencil\n");
#endif
#ifdef TILE_3D_OLD
	printf("[BENCH] CUDA 3D-Tiled-old Stencil\n");
#endif
#ifdef NAIVE
	printf("[BENCH] CUDA Naive Stencil\n");
#endif
	printf("[BENCH] iteration=%d\n", iteration);

	float *h_A0;
	float *h_Anext;
	float *d_A0;
	float *d_Anext;
	size=nx*ny*nz;
	h_A0=(float*)malloc(sizeof(float)*size);
	h_Anext=(float*)malloc(sizeof(float)*size);

#ifdef TIMING
	pb_SwitchToTimer(&timers, pb_TimerID_IO);
#endif
	generateInput(h_A0, nx, ny, nz);
/*
	FILE *fp = fopen(parameters->inpFiles[0], "rb");
	inputData(h_A0, nx, ny, nz, fp);
	fclose(fp);
*/
#ifdef TIMING
	pb_SwitchToTimer(&timers, pb_TimerID_COPY);
#endif

	cudaMalloc((void **)&d_A0, size*sizeof(float));
	cudaMalloc((void **)&d_Anext, size*sizeof(float));
	cudaMemset(d_Anext,0,size*sizeof(float));
	cudaMemcpy(d_A0, h_A0, size*sizeof(float), cudaMemcpyHostToDevice);
	cudaMemcpy(d_Anext, d_A0, size*sizeof(float), cudaMemcpyDeviceToDevice);

#ifdef TIMING
	pb_SwitchToTimer(&timers, pb_TimerID_COMPUTE);
#endif
	printf("[BENCH] nx=%d, ny=%d, nz=%d\n", nx, ny, nz);

#ifdef TILE_3D
	int tx=BSX;
	int ty=BSY;
	int tz=BSZ;
	int bx=(nx+tx-1)/tx;
	int by=(ny+ty-1)/ty;
	int bz=(nz+tz-1)/tz;
#endif
#ifdef TILE_2D
	int tx=32;
	int ty=4;
	int tz=1;
	int bx=(nx+tx-1)/tx;
	int by=(ny+ty-1)/ty;
	int bz=1;
#endif
#ifdef NAIVE
	int tx=nx-1;
	int ty=1;
	int tz=1;
	int bx=ny-2;
	int by=nz-2;
	int bz=1;
#endif
	printf("[BENCH] bx=%d, by=%d, bz=%d\n", bx, by, bz);
	printf("[BENCH] tx=%d, ty=%d, tz=%d\n", tx, ty, tz);
	dim3 block(tx, ty, tz);
	dim3 grid(bx, by, bz);

#if defined(TILE_3D_OLD) || defined(TILE_2D_OLD) 
	int sh_size = tx*ty*tz*sizeof(float);
	printf("[BENCH] sh_size=%d\n", sh_size);
#endif

	cudaThreadSynchronize();
#ifdef TIMING
	pb_SwitchToTimer(&timers, pb_TimerID_KERNEL);
#endif

#ifdef TILE_3D_NEW
	tile_3D_new<<<grid, block>>>(iteration, c0, c1, d_A0, d_Anext, nx, ny, nz);
#endif
#ifdef TILE_2D_NEW
	tile_2D_new<<<grid, block>>>(iteration, c0, c1, d_A0, d_Anext, nx, ny, nz);
#endif
///*
	for(int t=0;t<iteration;t++) {
#ifdef TILE_3D_OLD
		tile_3D_old<<<grid, block, sh_size>>>(c0, c1, d_A0, d_Anext, nx, ny, nz);
#endif
#ifdef TILE_2D_OLD
		tile_2D_old<<<grid, block, sh_size>>>(c0, c1, d_A0, d_Anext, nx, ny, nz);
#endif
#ifdef NAIVE
		naive<<<grid, block>>>(c0, c1, d_A0, d_Anext, nx, ny, nz);
#endif
		float *d_temp = d_A0;
		d_A0 = d_Anext;
		d_Anext = d_temp;
	}
	float *d_temp = d_A0;
	d_A0 = d_Anext;
	d_Anext = d_temp;
//*/
	cudaThreadSynchronize();
	CUT_CHECK_ERROR("Kernl Launch failed")
#ifdef TIMING
	pb_SwitchToTimer(&timers, pb_TimerID_COPY);
#endif
	cudaMemcpy(h_Anext, d_Anext, size*sizeof(float), cudaMemcpyDeviceToHost);

	float *h_result_ref = (float*)malloc(sizeof(float)*size);
	stencil_gold(c0, c1, h_A0, iteration, h_result_ref, nx, ny, nz);
	print_error(h_Anext, h_result_ref, nx, ny, nz);
	outputData("result.out", h_Anext, nx, ny, nz);
/*
	if(parameters->outFile) {
#ifdef TIMING
		pb_SwitchToTimer(&timers, pb_TimerID_IO);
#endif
		outputData(parameters->outFile,h_Anext,nx,ny,nz);
	}
*/
#ifdef TIMING
	pb_SwitchToTimer(&timers, pb_TimerID_NONE);
#endif
	cudaFree(d_A0);
	cudaFree(d_Anext);
	free(h_A0);
	free(h_Anext);
#ifdef TIMING
	pb_PrintTimerSet(&timers);
#endif
	pb_FreeParameters(parameters);
	return 0;
}
