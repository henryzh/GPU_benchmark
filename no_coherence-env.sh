
export GPGPUSIM_ROOT=/home/cxh/gpgpu-sim-ruby
export CUDA_VERSION_NUMBER=4020
export GPGPUSIM_CONFIG=$CUDA_VERSION_NUMBER/release
export CUDA_INSTALL_PATH=/usr/local/cuda
export PATH=$PATH:$CUDA_INSTALL_PATH/bin
#source setup_environment release
export NVOPENCL_LIBDIR=/usr/lib
export NVOPENCL_INCDIR=/usr/local/cuda/include
#export RUBY_PROTOCOL_NAME=TO_MSI_wt_g
#export RUBY_PROTOCOL_NAME=TO_PSI_wt_g
export RUBY_PROTOCOL_NAME=non_coherent_g
#export RUBY_PROTOCOL_NAME=MESI_CMP_directory_g
export LD_LIBRARY_PATH=$GPGPUSIM_ROOT/lib/$GPGPUSIM_CONFIG/ruby/$RUBY_PROTOCOL_NAME/:$GPGPUSIM_ROOT/lib/$GPGPUSIM_CONFIG/
