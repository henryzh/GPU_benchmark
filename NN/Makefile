# Copyright 1993-2006 NVIDIA Corporation.  All rights reserved.
CUDA_DIR = /usr/local/cuda
CUDA_LIB_DIR := $(CUDA_DIR)/lib
ifeq ($(shell uname -m), x86_64)
     ifeq ($(shell if test -d $(CUDA_DIR)/lib64; then echo T; else echo F; fi), T)
     	CUDA_LIB_DIR := $(CUDA_DIR)/lib64
     endif
endif

CC := gcc
NVCC := $(CUDA_DIR)/bin/nvcc
INCLUDE := $(CUDA_DIR)/include -I./
SDK_INC := /home/cxh/CUDA-SDK/cuda-4.1/C/common/inc
SDK_LIB := /home/cxh/CUDA-SDK/cuda-4.1/C/lib

EXE := NN
CUFILES	:= NN.cu
CCFILES	:= 

CFLAGS := -O3 
CUFLAGS	:= $(CFLAGS)

SRC := $(CUFILES) $(CCFILES)

release: $(SRC)
	$(NVCC) $(CUFLAGS) $(SRC) -o $(EXE) -I$(INCLUDE) -L$(CUDA_LIB_DIR)
NN.o: NN.cu 
	$(NVCC) $(NVCC_FLAGS) -c NN.cu
NN_gold.o: $(CCFILES)
	$(CC) $(CC_FLAGS) $(CCFILES) -c -o NN_gold.o
clean: $(SRC)
	rm -f $(EXE) 
