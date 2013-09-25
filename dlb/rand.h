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


__device__ int randdata[128];

static __device__ int myrand(void) {
    randdata[blockIdx.x] = randdata[blockIdx.x] * 1103515245 + 12345;
    return((unsigned)(randdata[blockIdx.x]/65536) % 32768)+blockIdx.x;
}
