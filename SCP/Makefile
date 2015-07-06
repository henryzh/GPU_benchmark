# Copyright 1993-2006 NVIDIA Corporation.  All rights reserved.
CUDA_DIR ?= $(CUDA_INSTALL_PATH)
# CUDA toolkit libraries
CUDA_LIB_DIR := $(CUDA_DIR)/lib
ifeq ($(shell uname -m), x86_64)
     ifeq ($(shell if test -d $(CUDA_DIR)/lib64; then echo T; else echo F; fi), T)
     	CUDA_LIB_DIR := $(CUDA_DIR)/lib64
     endif
endif

CC := gcc
CXX := g++
NVCC := $(CUDA_DIR)/bin/nvcc
SDK_INC := $(NVIDIA_CUDA_SDK_LOCATION)/C/common/inc
SDK_SHARED_INC := $(NVIDIA_CUDA_SDK_LOCATION)/shared/inc
SDK_LIB := $(NVIDIA_CUDA_SDK_LOCATION)/C/lib
SDK_SHARED_LIB := $(NVIDIA_CUDA_SDK_LOCATION)/shared/lib
INCS := -I$(CUDA_DIR)/include -I./ -I$(SDK_INC) -I$(SDK_SHARED_INC)
LIBS := -L$(SDK_LIB) -L$(CUDA_LIB_DIR) -L$(SDK_SHARED_LIB)
EXE := SCP
CUFILES	:= scalarProd.cu
CU_DEPS	:= scalarProd_kernel.cu
CCFILES	:= scalarProd_gold.cpp

CFLAGS := -O3 
CUFLAGS	:= $(CFLAGS)
OBJS := scp_gold.o scp.o
SRC := $(CUFILES) $(CCFILES)

release: $(OBJS)
	$(NVCC) $(CUFLAGS) $(OBJS) -o $(EXE) $(INCS) $(LIBS)
scp.o: $(CUFILES) 
	$(NVCC) $(NVCC_FLAGS) -c $(CUFILES) -o scp.o $(INCS) $(LIBS)
scp_gold.o: $(CCFILES)
	$(CXX) $(CC_FLAGS) $(CCFILES) -c -o scp_gold.o
clean: $(SRC)
	rm -f *.o $(EXE) 
