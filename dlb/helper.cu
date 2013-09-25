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


#include "helper.h"

Time::Time(unsigned int iterations):iterations(iterations)
{
	cudaThreadSynchronize();
	cudaEventCreate(&startevent);
	cudaEventCreate(&endevent);
}

void Time::start()
{
	cudaEventRecord(startevent, 0);
}

float Time::stop()
{
   cudaEventRecord(endevent, 0);
   cudaEventSynchronize(endevent);

   float runTime;
   cudaEventElapsedTime(&runTime, startevent, endevent);
   runTime /= float(iterations);

   return runTime;
}
