
export GPGPUSIM_ROOT=/data1/cxh/gpgpu-sim-ruby
export CUDA_VERSION_NUMBER=4000
export GPGPUSIM_CONFIG=$CUDA_VERSION_NUMBER/release
export CUDA_INSTALL_PATH=/usr/local/cuda
export PATH=$PATH:$CUDA_INSTALL_PATH/bin
export RUBY_PROTOCOL_NAME=non_coherent_g
export LD_LIBRARY_PATH=$GPGPUSIM_ROOT/lib/$GPGPUSIM_CONFIG/ruby/$RUBY_PROTOCOL_NAME/:$GPGPUSIM_ROOT/lib/$GPGPUSIM_CONFIG/
