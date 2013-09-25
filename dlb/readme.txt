/**
 * Two benchmarks for dynamic load balancing using
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

This package contains two example applications that both
use work-stealing for load balancing.

The latest version of the code can always be found at
http://www.cse.chalmers.se/research/group/dcs/gpuloadbal.html

Four-in-a-row
-------------

The first is a four-in-a-row game that requires the following
parameters to run:

  ./fourinarow threads blocks [abp|static] lookahead [scenario]

Threads is the number of threads per block to use. Between 1 and 128.

Blocks is the number of thread blocks. Between 1 and 512.

ABP means that work-stealing should be used and static that the kernel
should exit to the CPU for synchronization.

Lookahead is the number of future moves the computer opponent
should evaluate before deciding its move. Between 1 and 7.

Scenario is optional and automatically plays one of three
predefined scenarios for benchmarking purposes. If no scenario
is given, the game will be interactive. 

Octree partitioning
-------------------

In the second benchmark an octree partitioning is created from
a set of particles.

  ./octreepart threads blocks [abp|static] particleCount maxChildren

Threads is the number of threads per block to use. Between 1 and 128.

Blocks is the number of thread blocks. Between 1 and 512.

ABP means that work-stealing should be used and static that the kernel
should exit to the CPU for synchronization.

ParticleCount is the total number of particles to partition.

MaxChildren is the maximum number of particles that are allowed in an octant.


Other
-----

The benchmarks are known to work with Visual Studio 2008, CUDA 3.0 and
a sm_13 capable graphics processor. They are only meant to demonstrate
dynamic load balancing using work-stealing. No claim is given that they
are the optimal way to implement a four-a-in-row opponent or to do
octree partitioning.




