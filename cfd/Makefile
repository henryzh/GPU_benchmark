# CFD CUDA
#CUDA_DIR = /home/cxh/local/cuda-3.1/cuda
CUDA_DIR = /usr/local/cuda
SDK_DIR = /home/cxh/CUDA-SDK/cuda-4.1/C

# CUDA toolkit libraries
CUDA_LIB_DIR := $(CUDA_DIR)/lib
ifeq ($(shell uname -m), x86_64)
     ifeq ($(shell if test -d $(CUDA_DIR)/lib64; then echo T; else echo F; fi), T)
     	CUDA_LIB_DIR := $(CUDA_DIR)/lib64
     endif
endif

CUDA_SDK_PATH := $(SDK_DIR)
NVCC := $(CUDA_DIR)/bin/nvcc
NVCC_FLAGS := -Xptxas -v #--gpu-architecture=compute_20 --gpu-code=compute_20
INCLUDES := #-I$(CUDA_SDK_PATH)/common/inc
LIBS := -L$(CUDA_LIB_DIR) #-L$(CUDA_SDK_PATH)/lib $(CUTIL_LIB)

# Determine the correct version of the cutil library
CUTIL_LIB = # -lcutil
ifeq ($(shell uname -m), x86_64)
     ifeq ($(shell if test -e $(SDK_DIR)/lib/libcutil_x86_64.a; then echo T; else echo F; fi), T)
        CUTIL_LIB = #-lcutil_x86_64
     endif
endif

all: euler3d  #euler3d_double  pre_euler3d  pre_euler3d_double 
euler3d: euler3d.cu
	$(NVCC)  -O2 $(NVCC_FLAGS) $(INCLUDES) $(LIBS) euler3d.cu -o euler3d
euler3d_double: euler3d_double.cu
	$(NVCC) -O3 $(NVCC_FLAGS) euler3d_double.cu -o euler3d_double $(INCLUDES) $(LIBS)
pre_euler3d: pre_euler3d.cu
	$(NVCC) -O3 $(NVCC_FLAGS) pre_euler3d.cu -o pre_euler3d $(INCLUDES) $(LIBS)
pre_euler3d_double: pre_euler3d_double.cu
	$(NVCC) -O3 $(NVCC_FLAGS) pre_euler3d_double.cu -o pre_euler3d_double $(INCLUDES) $(LIBS)
clean:
	rm -f euler3d euler3d_double pre_euler3d pre_euler3d_double *.linkinfo
