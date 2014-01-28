#include "common.h"

/*
#ifdef LOCKFREE
__device__ inline void lockfree_barrier(volatile uint *counter, int *partial_sums, int *predicate, int current_value, uint bx, uint tx) {
	if(tx==0) {
//		if(bx>0) while(counter[bx-1] != 1) {}
		if(bx>0) while(counter[bx] != 1) {}
	}
	__syncthreads();

	if(tx==0) {
		predicate[0] = partial_sums[bx];
		partial_sums[bx+1] = predicate[0] + current_value;
	}
	__threadfence();

	if(tx==0) {
//		counter[bx] = 1;
		counter[bx+1] = 1;
	}
//	__syncthreads();
}
#endif
//*/
///*
#ifdef LOCKFREE
__device__ inline void lockfree_barrier(volatile unsigned *counter, int* partial_sums, int *predicate, int current_value, uint bx, uint tx) {
	if(tx==0) {

//		while(1) {
//			unsigned flag = counter[bx];
//			if(bx==0 || flag!=0) break;
//		} // end while


		if(bx>0) while(counter[bx] != 1) {}
		predicate[0] = partial_sums[bx];
		partial_sums[bx+1] = predicate[0] + current_value;
	}
	__threadfence();
//	__syncthreads();
	if(tx==0) {
		counter[bx+1] = 1;
	}
}
#endif
//*/

#ifdef ATOMIC
__device__ inline void atomic_barrier(unsigned *counter, int* partial_sums, int *predicate, int current_value, uint bx, uint tx) {
	if(tx==0) {
		unsigned flag = 0;
		while(1) {
			flag = atomicAdd(counter+bx, flag);
			if(bx==0 || flag!=0) {
				break;
			}
		} // end while
		predicate[0] = partial_sums[bx];
		partial_sums[bx+1] = predicate[0] + current_value;
	}
	__threadfence();
	if(tx==0) {
		atomicAdd(counter+bx+1, 1);
	}
}
#endif


#ifdef FREE
__device__ inline void free_barrier(int* partial_sums, int *predicate, int current_value, uint bx, uint tx) {

	__syncthreads();
	if(tx==0) {
//		predicate[0] += predicate[0];

		predicate[0] = partial_sums[bx];
		partial_sums[bx+1] = predicate[0] + current_value;
	}

	__syncthreads();
}
#endif

#ifdef UNSAFE
__device__ inline void unsafe_barrier(volatile int* partial_sums, int *predicate, int current_value, uint bx, uint tx) {
	__syncthreads();
	if(tx==0) {
		int cc=0;
		while(1) {
			cc = partial_sums[bx];
			if(bx==0 || cc!=0) {
				break;
			}
		}
//		printf("bx=%d, cc=%d, current_value=%d\n", bx, cc, current_value);
		predicate[0] = cc;
		partial_sums[bx+1] = predicate[0] + current_value;
//		printf("partial_sums[%d]=%d\n", bx+1, partial_sums[bx+1]);
	}
	__syncthreads();
}
#endif

#ifdef FORWARD
//double the size of partial_sums
__device__ inline void forward_barrier(volatile int* partial_sums, int *predicate, int current_value, uint bx, uint tx) {
	if(tx<2) {
		int cc;
		while(1) {
			cc = partial_sums[2*bx+tx];
			// cc 0: flag   1: value
			if(tx==1)
				predicate[0]=cc;
			
			//check value
			if( bx==0|| predicate[0]!=0) { //assume initialized as 0
				break;
			}
			
			//if value == initialized
			//check flag
			if(tx==0)
				predicate[0]=cc;
			if(predicate[0]==1)
				break;
			//repeat polling
		} // end while	

		//got value
		if(tx==1)
			predicate[0]=cc;
		if(tx==0) {
			//if value is equal to initialized
			if((predicate[0]+current_value)==0) {
				//write flag
				partial_sums[2*bx+2]=1;
			}
			else {
				//write value
				partial_sums[2*bx+3]=predicate[0]+current_value;
			}
		}
	}
}
#endif

#ifdef FORWARD_ATOMIC
//double the size of partial_sums
__device__ inline void forward_atomic_barrier(int* partial_sums, int *predicate, int current_value, uint bx, uint tx) {
	if(tx<2) {
		int cc=0;
		while(1) {
			cc = atomicExch(partial_sums+2*bx+tx,cc);
			// cc 0: flag   1: value
			if(tx==1)
				predicate[0]=cc;
			
			//check value
			if( bx==0|| predicate[0]!=0) { //assume initialized as 0
				break;
			}
			
			//if value == initialized
			//check flag
			if(tx==0)
				predicate[0]=cc;
			if(predicate[0]==1)
				break;
			//repeat polling
		}
		//got value
		if(tx==1)
			predicate[0]=cc;
		if(tx==0) {
			//if value is equal to initialized
			if((predicate[0]+current_value)==0) {
				//write flag
//				partial_sums[2*bx+2]=1;
				atomicAdd(partial_sums+2*bx+2,1);
			}
			else {
				//write value
//				partial_sums[2*bx+3]=predicate[0]+warp_sums[15];
				atomicAdd(partial_sums+2*bx+3,predicate[0]+current_value);
			}
		}
	}	
}
#endif

