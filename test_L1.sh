#!/bin/sh

GPGPUSIM_DIR=/scr1/wu14/build/gpgpu-sim-ruby
BENCHMARK_DIR=$PWD

BUILD_TYPE=release
PROTOCOL=TO_ST_bp_g

OUTPUT_DIR=$1

#BENCHMARK_NAMES="BFS2 spmv IIX KMN ssc sad"
#BENCHMARK_NAMES="BFS2 spmv IIX KMN ssc sad stencil hotspot FWT backprop srad1 srad2 nw fft lavaMD pvc bfs-rod"
BENCHMARK_NAMES="backprop"

echo "GPGPU-Sim: $GPGPUSIM_DIR"
echo "BENCHMARKs: $BENCHMARK_DIR"
echo "output to $OUTPUT_DIR"

export CUDA_INSTALL_PATH=/usr/local/cuda
export PATH=$PATH:$CUDA_INSTALL_PATH/bin

#$GPGPUSIM_DIR/setup_environment $BUILD_TYPE

export GPGPUSIM_ROOT=$GPGPUSIM_DIR
export CUDA_VERSION_NUMBER=4010
export GPGPUSIM_CONFIG=$CUDA_VERSION_NUMBER/$BUILD_TYPE
export NVOPENCL_LIBDIR=/usr/lib
export NVOPENCL_INCDIR=/usr/local/cuda/include
export RUBY_PROTOCOL_NAME=$PROTOCOL
export LD_LIBRARY_PATH=$GPGPUSIM_ROOT/lib/$GPGPUSIM_CONFIG/ruby/$RUBY_PROTOCOL_NAME/:$GPGPUSIM_ROOT/lib/$GPGPUSIM_CONFIG/


for BENCHMARK in $BENCHMARK_NAMES
do
    nohup ./run_benchmark.sh $BENCHMARK_DIR/$BENCHMARK $OUTPUT_DIR &
done
