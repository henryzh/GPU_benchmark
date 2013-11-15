# Copyright 1993-2006 NVIDIA Corporation.  All rights reserved.
CUDA_DIR = /usr/local/cuda
# CUDA toolkit libraries
CUDA_LIB_DIR := $(CUDA_DIR)/lib
ifeq ($(shell uname -m), x86_64)
     ifeq ($(shell if test -d $(CUDA_DIR)/lib64; then echo T; else echo F; fi), T)
     	CUDA_LIB_DIR := $(CUDA_DIR)/lib64
     endif
endif

CC := gcc
NVCC := $(CUDA_DIR)/bin/nvcc
SDK_INC := /home/cxh/CUDA-SDK/cuda-4.1/C/common/inc
SDK_SHARED_INC := /home/cxh/CUDA-SDK/cuda-4.1/shared/inc
SDK_LIB := /home/cxh/CUDA-SDK/cuda-4.1/C/lib
SDK_SHARED_LIB := /home/cxh/CUDA-SDK/cuda-4.1/shared/lib
INCS := -I$(CUDA_DIR)/include -I./ -I$(SDK_INC) -I$(SDK_SHARED_INC)
LIBS := -L$(SDK_LIB) -L$(CUDA_LIB_DIR) -L$(SDK_SHARED_LIB)
EXE := FWT
CUFILES	:= fastWalshTransform.cu
CU_DEPS	:= fastWalshTransform_kernel.cu
CCFILES	:= fastWalshTransform_gold.cpp

CFLAGS := -O3 
CUFLAGS	:= $(CFLAGS)
OBJS := fwt_gold.o fwt.o
SRC := $(CUFILES) $(CCFILES)

release: $(OBJS)
	$(NVCC) $(CUFLAGS) $(OBJS) -o $(EXE) $(INCS) $(LIBS)
fwt.o: $(CUFILES) 
	$(NVCC) $(NVCC_FLAGS) -c $(CUFILES) -o fwt.o $(INCS) $(LIBS)
fwt_gold.o: $(CCFILES)
	$(CC) $(CC_FLAGS) $(CCFILES) -c -o fwt_gold.o
clean: $(SRC)
	rm -f *.o $(EXE) 
