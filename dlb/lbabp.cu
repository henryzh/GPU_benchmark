/**
 * Octree Partitioning
 * Benchmark for dynamic load balancing using
 * work-stealing on graphics processors.
 * --------------------------------------------------------
 * Copyright 2011 Daniel Cederman and Philippas Tsigas
 *
 * This work is licensed under the Creative Commons
 * Attribution 3.0 Unported (CC BY 3.0) License.
 * To view a copy of this license, visit
 * http://creativecommons.org/licenses/by/3.0 .
 *
**/

#include "lbabp.h"
#include "helper.h"


LBABP::~LBABP()
{
	if(init)
	{
		cudaFree(dwq);
		cudaFree(wq->deq);
		cudaFree(wq->dh);
	}

}


bool LBABP::setQueueSize(unsigned int dequelength, unsigned int blocks)
{
	init = true;
	wq = (DLBABP*)malloc(sizeof(DLBABP));

	CUDA_SAFE_CALL(cudaMalloc((void**)&dwq,sizeof(DLBABP)));

	CUDA_SAFE_CALL(cudaMalloc((void**)&(wq->deq),sizeof(Task)*dequelength*blocks));
	CUDA_SAFE_CALL(cudaMalloc((void**)&(wq->dh),sizeof(DequeHeader)*blocks));

	CUDA_SAFE_CALL(cudaMemset(wq->deq,0,sizeof(Task)*dequelength*blocks));
	CUDA_SAFE_CALL(cudaMemset(wq->dh,0,sizeof(DequeHeader)*blocks));

	wq->maxlength = dequelength;
	CUDA_SAFE_CALL(cudaMemcpy(dwq,wq,sizeof(DLBABP),cudaMemcpyHostToDevice));
	return true;
}

int LBABP::getMaxMem()
{
	int maxle;
	CUDA_SAFE_CALL(cudaMemcpyFromSymbol(&maxle,maxl,sizeof(int),0,cudaMemcpyDeviceToHost));
	return maxle;
}
