# Scan, Xuhao Chen, UIUC
#CUDA_DIR = /home/cxh/local/cuda-4.1/cuda
CUDA_DIR ?= $(CUDA_INSTALL_PATH)
CUDA_LIB_DIR = $(CUDA_DIR)/lib64
CC = gcc
CXX = g++
NVCC = $(CUDA_DIR)/bin/nvcc
LIB = -L/home/hangzhang/local/cuda/lib64 -lm -lpthread
INCLUDE = $(CUDA_DIR)/include
CC_FLAGS = -O3 -I$(INCLUDE) -L$(CUDA_LIB_DIR)
NVCC_FLAGS = -O3 -I$(INCLUDE) -L$(CUDA_LIB_DIR) -arch=sm_13# --ptxas-options=-v
SRC = scan_sync.cu
EXE = scan

release: $(SRC)
	$(NVCC) $(NVCC_FLAGS) $(SRC) -o $(EXE)

clean: $(SRC)
	rm -f $(EXE) *.o
