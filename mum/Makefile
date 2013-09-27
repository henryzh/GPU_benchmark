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
INCLUDE := $(CUDA_DIR)/include
SDK_INC := /home/cxh/CUDA-SDK/cuda-4.1/C/common/inc
SDK_LIB := /home/cxh/CUDA-SDK/cuda-4.1/C/lib

EXE := MUM
CUFILES	:= mummergpu.cu
CU_DEPS	:=
CCFILES	:= mummergpu_main.cpp mummergpu_gold.cpp suffix-tree.cpp PoolMalloc.cpp
SRC := $(CUFILES) $(CCFILES)

release: $(SRC)
	$(NVCC) $(SRC) -o $(EXE) -I$(INCLUDE) -L$(SDK_LIB) -I$(SDK_INC) -L$(CUDA_LIB_DIR)
laplace3d.o: laplace3d.cu 
	$(NVCC) $(NVCC_FLAGS) -c kmeans_cuda.cu
laplace3d_gold.o: $(CCFILES)
	$(CC) $(CC_FLAGS) $(CCFILES) -c -o laplace3d_gold.o
clean: $(SRC)
	rm -f $(EXE) $(EXE).linkinfo result.txt
