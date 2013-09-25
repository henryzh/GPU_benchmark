// CUDA Stencil, Xuhao Chen
#include "common.h"
#ifdef NAIVE
__global__ void naive(float c0, float c1, float *A0, float *Anext, int nx, int ny, int nz) {
	int i = threadIdx.x;
	int j = blockIdx.x+1;
	int k = blockIdx.y+1;

	if(i>0) {
	Anext[Index3D (nx, ny, i, j, k)] = 
	(A0[Index3D (nx, ny, i, j, k + 1)] +
	A0[Index3D (nx, ny, i, j, k - 1)] +
	A0[Index3D (nx, ny, i, j + 1, k)] +
	A0[Index3D (nx, ny, i, j - 1, k)] +
	A0[Index3D (nx, ny, i + 1, j, k)] +
	A0[Index3D (nx, ny, i - 1, j, k)])*c1
	- A0[Index3D (nx, ny, i, j, k)]*c0;
	}
}
#endif

#ifdef TILE_3D_OLD
__global__ void tile_3D_old(float c0, float c1, float *A0, float *Anext, int nx, int ny, int nz) {
	int tx = threadIdx.x;
	int ty = threadIdx.y;
	int tz = threadIdx.z;
	int bx = blockIdx.x;
	int by = blockIdx.y;
	int bz = blockIdx.z;
	int i = bx*blockDim.x+tx;
	int j = by*blockDim.y+ty;
	int k = bz*blockDim.z+tz;
	const int sh_id=tx+ty*blockDim.x+tz*blockDim.x*blockDim.y;
	extern __shared__ float sh_A0[];
	sh_A0[sh_id]=0.0f;
	__syncthreads();

	bool w_region = (i>0 && j>0 && k>0 && (i<nx-1) && (j<ny-1) && (k<nz-1));
	bool x_l_bound = (tx==0);
	bool x_h_bound = (tx==(blockDim.x-1));
	bool y_l_bound = (ty==0);
	bool y_h_bound = (ty==(blockDim.y-1));
	bool z_l_bound = (tz==0);
	bool z_h_bound = (tz==(blockDim.z-1));
	sh_A0[sh_id] = A0[Index3D(nx, ny, i, j, k)];
	__syncthreads();

	if(w_region) {
		float front, back, left, right, top, down;
		if(x_l_bound) left=A0[Index3D(nx, ny, i-1, j, k)];
		else left=sh_A0[sh_id-1];
		if(x_h_bound) right=A0[Index3D(nx, ny, i+1, j, k)];
		else right=sh_A0[sh_id+1];
		if(y_l_bound) back=A0[Index3D(nx, ny, i, j-1, k)];
		else back=sh_A0[sh_id-blockDim.x];
		if(y_h_bound) front=A0[Index3D(nx, ny, i, j+1, k)];
		else front=sh_A0[sh_id+blockDim.x];
		if(z_l_bound) down=A0[Index3D(nx, ny, i, j, k-1)];
		else down=sh_A0[sh_id-blockDim.x*blockDim.y];
		if(z_h_bound) top=A0[Index3D(nx, ny, i, j, k+1)];
		else top=sh_A0[sh_id+blockDim.x*blockDim.y];
		Anext[Index3D(nx, ny, i, j, k)] = (front+back+left+right+top+down)*c1 - sh_A0[sh_id]*c0;
	}
}
#endif
#ifdef TILE_3D_NEW
__global__ void tile_3D_new(int iter, float c0, float c1, float *A0, float *Anext, int nx, int ny, int nz) {
	int tx = threadIdx.x;
	int ty = threadIdx.y;
	int tz = threadIdx.z;
	int bx = blockIdx.x;
	int by = blockIdx.y;
	int bz = blockIdx.z;
	int i = bx*blockDim.x+tx;
	int j = by*blockDim.y+ty;
	int k = bz*blockDim.z+tz;
	const int num_blocks = gridDim.x;//*gridDim.y*gridDim.z;
	const int tid=tx+ty*blockDim.x+tz*blockDim.x*blockDim.y;
//	if(tid==0) printf("num_blocks = %d\n", num_blocks);
	__shared__ float sh_mem[2*BSX*BSY*BSZ];
	float *sh_A0=sh_mem;
	float *sh_Anext=sh_mem+BSX*BSY*BSZ;
	sh_A0[tid]=0.0f;
	sh_Anext[tid]=0.0f;
	__syncthreads();

	bool w_region = (i>0 && j>0 && k>0 && (i<nx-1) && (j<ny-1) && (k<nz-1));
	bool x_l_bound = (tx==0);
	bool x_h_bound = (tx==(blockDim.x-1));
	bool y_l_bound = (ty==0);
	bool y_h_bound = (ty==(blockDim.y-1));
	bool z_l_bound = (tz==0);
	bool z_h_bound = (tz==(blockDim.z-1));

	sh_A0[tid] = A0[Index3D(nx, ny, i, j, k)];
	__syncthreads();
///*
	for(int t=0;t<iter;t++) {
		if(w_region) {
			float front, back, left, right, top, down;
			if(x_l_bound) left=A0[Index3D(nx, ny, i-1, j, k)];
			else left=sh_A0[tid-1];
			if(x_h_bound) right=A0[Index3D(nx, ny, i+1, j, k)];
			else right=sh_A0[tid+1];
			if(y_l_bound) back=A0[Index3D(nx, ny, i, j-1, k)];
			else back=sh_A0[tid-blockDim.x];
			if(y_h_bound) front=A0[Index3D(nx, ny, i, j+1, k)];
			else front=sh_A0[tid+blockDim.x];
			if(z_l_bound) down=A0[Index3D(nx, ny, i, j, k-1)];
			else down=sh_A0[tid-blockDim.x*blockDim.y];
			if(z_h_bound) top=A0[Index3D(nx, ny, i, j, k+1)];
			else top=sh_A0[tid+blockDim.x*blockDim.y];
			sh_Anext[tid] = (front+back+left+right+top+down)*c1 - sh_A0[tid]*c0;
			Anext[Index3D(nx, ny, i, j, k)] = sh_Anext[tid];
		}
		__threadfence();
#ifdef ATOMIC
		__syncblocks_atomic((t+1)*num_blocks);
#endif
		float *sh_temp = sh_A0;
		sh_A0 = sh_Anext;
		sh_Anext = sh_temp;
	}
//*/
	Anext[Index3D(nx, ny, i, j, k)] = sh_A0[tid];
}
#endif
#ifdef TILE_2D_OLD
__global__ void tile_2D_old(float c0, float c1, float *A0,float *Anext, int nx, int ny, int nz) {
	int i = blockIdx.x*blockDim.x+threadIdx.x;
	int j = blockIdx.y*blockDim.y+threadIdx.y;
	const int sh_id=threadIdx.x+threadIdx.y*blockDim.x;
	extern __shared__ float sh_A0[];
	sh_A0[sh_id]=0.0f;
	__syncthreads();

	bool w_region =  i>0 && j>0 &&(i<nx-1) &&(j<ny-1);
	bool x_l_bound = (threadIdx.x==0);
	bool x_h_bound = (threadIdx.x==(blockDim.x-1));
	bool y_l_bound = (threadIdx.y==0);
	bool y_h_bound = (threadIdx.y==(blockDim.y-1));
	
	for(int k=1;k<nz-1;k++) {
		sh_A0[sh_id] = A0[Index3D(nx, ny, i, j, k)];
		__syncthreads();
		if(w_region) {
			float partial=A0[Index3D (nx, ny, i, j, k+1)] + A0[Index3D(nx, ny, i, j, k-1)];
			float a_left,a_right,a_top,a_down;
			if(x_l_bound) a_left=A0[Index3D(nx, ny, i-1, j, k)];
			else a_left=sh_A0[sh_id-1];
			if(x_h_bound) a_right=A0[Index3D(nx, ny, i+1, j, k)];
			else a_right=sh_A0[sh_id+1];
			if(y_l_bound) a_down=A0[Index3D(nx, ny, i, j-1, k)];
			else a_down=sh_A0[sh_id-blockDim.x];
			if(y_h_bound) a_top=A0[Index3D(nx, ny, i, j+1, k)];
			else a_top=sh_A0[sh_id+blockDim.x];
			Anext[Index3D(nx, ny, i, j, k)] = (a_left+a_right+a_top+a_down+partial)*c1-sh_A0[sh_id]*c0;
		}
		__syncthreads();
	}
}
#endif
#ifdef TILE_2D_NEW
__global__ void tile_2D_new(int iter, float c0, float c1, float *A0,float *Anext, int nx, int ny, int nz) {
	int i = blockIdx.x*blockDim.x+threadIdx.x;
	int j = blockIdx.y*blockDim.y+threadIdx.y;
	const int sh_id=threadIdx.x+threadIdx.y*blockDim.x;
	extern __shared__ float sh_A0[];
	float* sh_Anext=sh_A0+blockDim.x*blockDim.y;
	sh_A0[sh_id]=0.0f;
	sh_Anext[sh_id]=0.0f;
	__syncthreads();

	bool w_region =  i>0 && j>0 &&(i<nx-1) &&(j<ny-1);
	bool x_l_bound = (threadIdx.x==0);
	bool x_h_bound = (threadIdx.x==(blockDim.x-1));
	bool y_l_bound = (threadIdx.y==0);
	bool y_h_bound = (threadIdx.y==(blockDim.y-1));
	
	for(int t=0;t<iter;t++) {
		for(int k=1;k<nz-1;k++) {
			sh_A0[sh_id] = A0[Index3D(nx, ny, i, j, k)];
			__syncthreads();
			if(w_region) {
				float a_left, a_right, a_front, a_back, a_top_down;
				a_top_down=A0[Index3D(nx, ny, i, j, k+1)]+A0[Index3D(nx, ny, i, j, k-1)];
				if(x_l_bound) a_left=A0[Index3D(nx, ny, i-1, j, k)];
				else a_left=sh_A0[sh_id-1];
				if(x_h_bound) a_right=A0[Index3D(nx, ny, i+1, j, k)];
				else a_right=sh_A0[sh_id+1];
				if(y_l_bound) a_back=A0[Index3D(nx, ny, i, j-1, k)];
				else a_back=sh_A0[sh_id-blockDim.x];
				if(y_h_bound) a_front=A0[Index3D(nx, ny, i, j+1, k)];
				else a_front=sh_A0[sh_id+blockDim.x];
				sh_Anext[Index3D(nx, ny, i, j, k)] = (a_left+a_right+a_back+a_front+a_top_down)*c1-sh_A0[sh_id]*c0;
			}
			__syncblocks_atomic();
		}
	}
}
#endif
