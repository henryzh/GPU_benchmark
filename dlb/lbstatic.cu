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

#include "task.h"
#include "lbstatic.h"
#include "helper.h"

LBStatic::~LBStatic()
{
	if(init)
	{
		cudaFree(dwq);
		cudaFree(wq->indeq);
		cudaFree(wq->outdeq);
		free(wq);
	}
}

bool LBStatic::setQueueSize(unsigned int dequelength, unsigned int blocks)
{
	init = true;
	this->blocks = blocks;
	wq = (DLBStatic*)malloc(sizeof(DLBStatic));
	CUDA_SAFE_CALL(cudaMalloc((void**)&dwq,sizeof(DLBStatic)));

	CUDA_SAFE_CALL(cudaMalloc((void**)&(wq->indeq),sizeof(Task)*dequelength));
	CUDA_SAFE_CALL(cudaMalloc((void**)&(wq->outdeq),sizeof(Task)*dequelength));

	CUDA_SAFE_CALL(cudaMalloc((void**)&(wq->ctrs),sizeof(unsigned int)*blocks));

	CUDA_SAFE_CALL(cudaMemset(wq->ctrs,0,sizeof(unsigned int)*blocks));

	wq->ctr=0;
	wq->ctr2=0;

	CUDA_SAFE_CALL(cudaMemcpy(dwq,wq,sizeof(DLBStatic),cudaMemcpyHostToDevice));

	return true;
}

int LBStatic::getMaxMem()
{
	return smaxl;
}

unsigned int LBStatic::blocksleft()
{
	CUDA_SAFE_CALL(cudaMemcpy(wq,dwq,sizeof(DLBStatic),cudaMemcpyDeviceToHost));
	if(wq->ctr==0)
		return 0;

	Task* t = wq->indeq;
	wq->indeq = wq->outdeq;
	wq->outdeq = t;

	int rval = wq->ctr;
	wq->ctr = 0;
	wq->ctr2 = rval;

	CUDA_SAFE_CALL(cudaMemcpy(dwq,wq,sizeof(DLBStatic),cudaMemcpyHostToDevice));
	CUDA_SAFE_CALL(cudaMemset(wq->ctrs,0,sizeof(unsigned int)*blocks));

	if(smaxl<(int)wq->ctr2)
		smaxl=(int)wq->ctr2;

	return rval;
}
