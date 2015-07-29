# Bitonic Sort, Xuhao Chen, UIUC
PARBOIL_DIR = ../common
CUDA_DIR ?= $(CUDA_INSTALL_PATH)
CUDA_LIB_DIR = $(CUDA_DIR)/lib64
CC = gcc
CXX = g++
NVCC = $(CUDA_DIR)/bin/nvcc
LIB = -L/home/hangzhang/local/cuda/lib64 -lm -lpthread
INCLUDE = -I$(CUDA_DIR)/include -I$(PARBOIL_DIR)
NVCC_FLAGS = -O2 -arch=sm_13 -Xptxas -dlcm=cg
SRC = bitonic_sort.cu $(PARBOIL_DIR)/parboil_cuda.c
EXE = bs

release: $(SRC)
	$(NVCC) $(NVCC_FLAGS) $(INCLUDE) -L$(CUDA_LIB_DIR) $(SRC) -o $(EXE)

clean:
	rm -f $(EXE) 
