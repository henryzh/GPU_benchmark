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

#include "lbabp.h"
#include "lbstatic.h"


enum LBMethod
{
	Dynamic,
	Static
};

class Octree
{
	static const unsigned int MAXTREESIZE = 11000000;
	unsigned int numParticles;
	float4* particles;
	float4* newParticles;
	unsigned int* tree;
	unsigned int* treeSize;
	unsigned int* particlesDone;
	LBABP lbws;
	LBStatic lbstat;
	
	float totalTime;
	LBMethod method;
public:
	void generateParticles();
	bool run(unsigned int threads, unsigned int blocks, LBMethod method, int maxChildren, int numParticles);
	void printStats();
	float getTime();
	int getMaxMem();
};


