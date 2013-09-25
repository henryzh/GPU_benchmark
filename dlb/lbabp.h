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

#include "task.h"
#include "rand.h"

struct DequeHeader
{
	volatile int tail;
	volatile int head;
};

class LBABP;

static __device__ int maxl=0;

static __device__ int getIndex(int head)
{
	return head&0xffff;
}

static __device__ int getZeroIndexIncCtr(int head)
{
	return (head+0x10000)&0xffff0000;
}

static __device__ int incIndex(int head)
{
	return head+1;
}


class DLBABP
{
public:
	friend LBABP;
	Task* deq;
	DequeHeader* dh;
	unsigned int maxlength;

	__device__ int pop(Task& val)
	{
		int localTail;
		int oldHead;
		int newHead;

		localTail = dh[blockIdx.x].tail;
		if(localTail==0)
			return -1;
	
		localTail--;

		val = deq[blockIdx.x*maxlength+localTail];

		__threadfence();    // grab data before updating pointers

		dh[blockIdx.x].tail=localTail;

		oldHead = dh[blockIdx.x].head;

		if (localTail > getIndex(oldHead))
		{
			return 1;
		}

		dh[blockIdx.x].tail = 0;
		newHead = getZeroIndexIncCtr(oldHead);
		if(localTail == getIndex(oldHead))
			if(atomicCAS((int*)&(dh[blockIdx.x].head), oldHead, newHead)==oldHead)
				return 1;
		dh[blockIdx.x].head=newHead;
		return -1;
	}	

	__device__ int steal(Task& val, unsigned int idx)
	{
		int localTail;
		int oldHead;
		int newHead;

		oldHead = dh[idx].head;
		localTail = dh[idx].tail;
		if(localTail<=getIndex(oldHead))
			return -1;

		val = deq[idx*maxlength+getIndex(oldHead)];

		__threadfence();    // grab data before updating pointers

		newHead = incIndex(oldHead);
		if(atomicCAS((int*)&(dh[idx].head),oldHead,newHead)==oldHead)
			return 1;

		return -1;
	}
	
    __device__ void push(Task& val)
    {
    	deq[blockIdx.x*maxlength+dh[blockIdx.x].tail] = val;

    	__threadfence();    // push data before updating pointers

    	dh[blockIdx.x].tail++;
    
    	if(maxl<dh[blockIdx.x].tail)
    		atomicMax(&maxl,dh[blockIdx.x].tail);
    }

    __device__ int dequeue2(Task& val)
    {
    	if(pop(val)==1)
    		return 1;
    
    	if(steal(val,myrand()%gridDim.x)==1)
    		return 1;
    	else return 0;
    }	

public:
    __device__ void enqueue(Task& val)
    {
    	if(threadIdx.x==0)
    	{
    		push(val);
    	}
    }
	
    __device__ int dequeue(Task& val)
    {
    	__shared__ volatile int rval;
    	int dval=0;
    
    	if(threadIdx.x==0)
    	{
    		rval = dequeue2(val);
    	}
    	__syncthreads();
    	dval = rval;
    	__syncthreads();
    
    	return dval;
    }

};

class LBABP
{
	bool init;
	DLBABP* wq;
	DLBABP* dwq;
public:
	LBABP():init(false){}
	~LBABP();
	int getMaxMem();
	int blocksleft() {return 0;}
	bool setQueueSize(unsigned int dequelength, unsigned int blocks);
	DLBABP* deviceptr() {return dwq;}
};
