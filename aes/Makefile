# Copyright 1993-2006 NVIDIA Corporation.  All rights reserved.
#
CUDA_DIR ?= $(CUDA_INSTALL_PATH)
# CUDA toolkit libraries
CUDA_LIB_DIR := $(CUDA_DIR)/lib
ifeq ($(shell uname -m), x86_64)
     ifeq ($(shell if test -d $(CUDA_DIR)/lib64; then echo T; else echo F; fi), T)
     	CUDA_LIB_DIR := $(CUDA_DIR)/lib64
     endif
endif

CC := gcc
NVCC := $(CUDA_DIR)/bin/nvcc
BOOST_ROOT := /usr/include
BOOST_VER := 
BOOST_LIB := /usr/lib
INCLUDE := $(CUDA_DIR)/include -I./ -I$(BOOST_ROOT)
SDK_INC := /home/cxh/CUDA-SDK/cuda-4.1/C/common/inc
SDK_LIB := /home/cxh/CUDA-SDK/cuda-4.1/C/lib

EXE := AES
CUFILES	:= aesHost.cu
CCFILES	:= aescuda.cpp aesCudaUtils.cpp
LINKFLAGS := -L$(BOOST_LIB) -lboost_filesystem$(BOOST_VER) -lboost_system

CFLAGS := -O3 
CUFLAGS	:= $(CFLAGS)

SRC := $(CUFILES) $(CCFILES)

release: $(SRC)
	$(NVCC) $(CUFLAGS) $(SRC) -o $(EXE) -I$(INCLUDE) -L$(CUDA_LIB_DIR) $(LINKFLAGS)
aesHost.o: aesHost.cu 
	$(NVCC) $(NVCC_FLAGS) -c aesHost.cu
aescuda.o: $(CCFILES)
	$(CC) $(CC_FLAGS) $(CCFILES) -c -o aescuda.o
clean: $(SRC)
	rm -f $(EXE) $(EXE).linkinfo result.txt
