/**
 * Octree Partitioning
 * Benchmark for dynamic load balancing using
 * work-stealing on graphics processors.
 * Copyright 2011 Daniel Cederman and Philippas Tsigas
**/

#include <string.h>
#include <stdio.h>
#include "octree.h"
#include "helper.h"

int main(int argc, char* argv[]) {
	if(argc!=6&&argc!=5) {
		printf("\nUsage:\t./octreepart threads blocks [abp|static] particleCount maxChildren\n\n");
		return 1;
	}
	int threads = atoi(argv[1]);
	if(threads<=0||threads>512) {
		printf("Threads must be between 1 and 128\n");
		return 1;
	}
	int blocks = atoi(argv[2]);
	if(blocks<=0||blocks>512) {
		printf("Blocks must be between 1 and 512\n");
		return 1;
	}
	int particleCount = atoi(argv[4]);
	if(particleCount<=0||particleCount>50000000) {
		printf("particleCount must be between 1 and 50000000\n");
		return 1;
	}
	int maxChildren = atoi(argv[5]);
	if(maxChildren<=0||maxChildren>100) {
		printf("maxChildren must be between 1 and 100\n");
		return 1;
	}
	LBMethod method;
	if(!strcmp(argv[3],"abp"))
		method=Dynamic;
	else
	if(!strcmp(argv[3],"static"))
		method=Static;
	else {
		printf("Load balancing method needs to be either 'abp' or 'static'\n");
		return 1;
	}
	Octree o;
	o.run(threads,blocks,method,maxChildren,particleCount);
	printf("Threads: %d Blocks: %d Method: %s ParticleCount: %d maxChildren: %d MaxMem: %d Time: %f\n",threads,blocks,argv[3],particleCount,maxChildren,o.getMaxMem(),o.getTime());
	o.printStats();
	return 0;
}
