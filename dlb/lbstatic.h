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

#pragma once
class LBStatic;

class DLBStatic
{
public:
	friend LBStatic;
	Task* indeq;
	Task* outdeq;
	unsigned int ctr;
	unsigned int ctr2;
	unsigned int* ctrs;
public:
	__device__ void enqueue(Task& val)
    {
    	if(threadIdx.x==0)
    	{
    		int pos = atomicAdd(&ctr,1);
    		indeq[pos]=val;
    	}
    }

	__device__ int dequeue(Task& t)
    {
    	__shared__ volatile int rval;
    	int dval;

	    if(threadIdx.x==0)
    	{
    		if(blockIdx.x+ctrs[blockIdx.x]*gridDim.x<ctr2)
    		{
    			t = outdeq[blockIdx.x+ctrs[blockIdx.x]*gridDim.x];
    			ctrs[blockIdx.x]++;
    			rval = 1;
    		}
    		else
    			rval = 0;
    	}
    	__syncthreads();
    	dval = rval;
    	__syncthreads();
    	return dval;
    }

};


class LBStatic
{
	bool init;
	DLBStatic* wq;
	DLBStatic* dwq;
	int blocks;
	int smaxl;
public:
	LBStatic():init(false),smaxl(0){};
	~LBStatic();
	int getMaxMem();
	bool setQueueSize(unsigned int dequelength, unsigned int blocks);
	DLBStatic* deviceptr() {return dwq;}
	unsigned int blocksleft();
};
