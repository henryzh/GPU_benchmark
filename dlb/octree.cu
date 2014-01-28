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

#include "octree.h"
#include "helper.h"
#include "octree_kernel.h"

void Octree::printStats()
{
	unsigned int* htree = new unsigned int[MAXTREESIZE];
	unsigned int htreeSize;
	unsigned int hparticlesDone;

	CUDA_SAFE_CALL(cudaMemcpy(&hparticlesDone,particlesDone,sizeof(unsigned int),cudaMemcpyDeviceToHost));

	CUDA_SAFE_CALL(cudaMemcpy(&htreeSize,treeSize,sizeof(unsigned int),cudaMemcpyDeviceToHost));
	CUDA_SAFE_CALL(cudaMemcpy(htree,tree,sizeof(unsigned int)*MAXTREESIZE,cudaMemcpyDeviceToHost));

	if(htreeSize>=MAXTREESIZE)
	{
		printf("Tree to large!\n");
		return;
	}

	unsigned int sum = 0;
	for(unsigned int i=0;i<htreeSize;i++)
	{
		if(htree[i]&0x80000000)
		{
			sum+=htree[i]&0x7fffffff;
		}
	}

	printf("Tree size: %d\n",htreeSize);
	printf("Particles in tree: %d (%d) [%d]\n",sum,numParticles,hparticlesDone);

	delete htree;
}

bool Octree::run(unsigned int threads, unsigned int blocks, LBMethod method, int maxChildren, int numParticles)
{
	this->method = method;
	this->numParticles = numParticles;

	CUDA_SAFE_CALL(cudaMalloc((void**)&tree,sizeof(unsigned int)*MAXTREESIZE));
	CUDA_SAFE_CALL(cudaMemset((void*)tree,0,sizeof(unsigned int)*MAXTREESIZE));

	CUDA_SAFE_CALL(cudaMalloc((void**)&particles,sizeof(float4)*numParticles));
	CUDA_SAFE_CALL(cudaMalloc((void**)&newParticles,sizeof(float4)*numParticles));
	CUDA_SAFE_CALL(cudaMalloc((void**)&particlesDone,sizeof(unsigned int)));

	CUDA_SAFE_CALL(cudaMalloc((void**)&treeSize,sizeof(unsigned int)));


	generateParticles();

	if(method==Dynamic)
		lbws.setQueueSize(64,blocks);
	else
		if(method==Static)
			lbstat.setQueueSize(900000,blocks);

	if(method == Dynamic)
		initOctree<DLBABP><<<1,1>>>(lbws.deviceptr(),treeSize,particlesDone,numParticles);

	if(method == Static)
		initOctree<DLBStatic><<<1,1>>>(lbstat.deviceptr(),treeSize,particlesDone,numParticles);

	CUT_CHECK_ERROR("initOctree failed!\n");

	Time timer(1);
	timer.start();

	if(method == Dynamic)
		makeOctree<DLBABP><<<blocks,threads>>>(lbws.deviceptr(),particles,newParticles,tree,numParticles,treeSize,particlesDone,maxChildren,false);
	else
		if(method == Static)
		{
			while((lbstat.blocksleft())!=0)
			{

				makeOctree<DLBStatic><<<blocks,threads>>>(lbstat.deviceptr(),particles,newParticles,tree,numParticles,treeSize,particlesDone,maxChildren,true);
			}
		}

		CUT_CHECK_ERROR("makeOctree failed!\n");

		float time = timer.stop();

		totalTime = time;

		CUDA_SAFE_CALL(cudaFree(newParticles));
		return true;
}

double genrand_real1(void);
void Octree::generateParticles()
{
	float4* lparticles = new float4[numParticles];

	char fname[256];
	sprintf(fname,"particles-%d.dat",numParticles);
	FILE* f = fopen(fname,"rb");
	if(!f)
	{
		printf("Generating and caching data\n");

		int clustersize = 100;
		for(unsigned int i=0;i<numParticles/clustersize;i++)
		{
			float x = ((float)genrand_real1()*800.0f-400.0f);
			float y = ((float)genrand_real1()*800.0f-400.0f);
			float z = ((float)genrand_real1()*800.0f-400.0f);

			for(int x=0;x<clustersize;x++)
			{	
				lparticles[i*clustersize+x].x = x + ((float)genrand_real1()*100.0f-50.0f);
				lparticles[i*clustersize+x].y = y + ((float)genrand_real1()*100.0f-50.0f);
				lparticles[i*clustersize+x].z = z + ((float)genrand_real1()*100.0f-50.0f);

			}

		}

		FILE* f = fopen(fname,"wb");
		if(f == NULL) {
		    printf("Error: Cannot create output file '%s' for particle data.\n", fname);
		    abort();
		}
		fwrite(lparticles,sizeof(float4),numParticles,f);
		fclose(f);
	}
	else
	{
		fread(lparticles,sizeof(float4),numParticles,f);
		fclose(f);
	}

	CUDA_SAFE_CALL(cudaMemcpy(particles,lparticles,sizeof(float4)*numParticles,cudaMemcpyHostToDevice));
	delete lparticles;
}

float Octree::getTime()
{
	return totalTime;
}

int Octree::getMaxMem()
{
	if(method==Dynamic)
		return lbws.getMaxMem();
	else
		if(method == Static)
			return lbstat.getMaxMem();

	return -1;
}
