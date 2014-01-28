
BINDIR:=$(shell pwd)/../bin/
BINSUBDIR=release/
SETENV=export BINDIR=$(BINDIR); export ROOTDIR=$(NVIDIA_COMPUTE_SDK_LOCATION)/C/src/; export BINSUBDIR=$(BINSUBDIR); 
noinline?=0

default: common
	$(SETENV) make noinline=$(noinline) -C gpu-coh/wave
	$(SETENV) make noinline=$(noinline) -C gpu-coh/vtr
	$(SETENV) make noinline=$(noinline) -C gpu-coh/octreepart
	$(SETENV) make noinline=$(noinline) -C gpu-coh/CudaCutsCC
	$(SETENV) make noinline=$(noinline) -C gpu-coh/barneshut

common:
	@ if [ ! -e ../common/ ]; then ln -s $(NVIDIA_COMPUTE_SDK_LOCATION)/C/common ../common; fi 
	@ if [ ! -e common ]; then ln -s $(NVIDIA_COMPUTE_SDK_LOCATION)/C/common common; fi 
	@ if [ ! -e ../common/common.mk ]; then echo "NVIDIA_COMPUTE_SDK_LOCATION environment variable not set properly."; exit 1; fi 

clean: common
	$(SETENV) make clean -C gpu-coh/wave
	$(SETENV) make clean -C gpu-coh/vtr
	$(SETENV) make clean -C gpu-coh/octreepart
	$(SETENV) make clean -C gpu-coh/CudaCutsCC
	$(SETENV) make clean -C gpu-coh/barneshut

