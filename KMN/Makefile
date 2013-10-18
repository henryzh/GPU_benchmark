# KMEANS CUDA
#CUDA_DIR = /home/cxh/local/cuda-3.1/cuda
CUDA_DIR = /usr/local/cuda
CUDA_LIB_DIR := $(CUDA_DIR)/lib
ifeq ($(shell uname -m), x86_64)
     ifeq ($(shell if test -d $(CUDA_DIR)/lib64; then echo T; else echo F; fi), T)
     	CUDA_LIB_DIR := $(CUDA_DIR)/lib64
     endif
endif

EXECUTABLE := kmn
CUFILES	:= kmeans_cuda.cu 
CU_DEPS	:= kmeans_cuda_kernel.cu
CFILES	:= kmeans.c kmeans_clustering.c cluster.c rmse.c

CC = gcc
CC_FLAGS =
NVCC = $(CUDA_DIR)/bin/nvcc
NVCC_FLAGS = -I$(CUDA_DIR)/include 
OBJS = cluster.o getopt.o kmeans.o kmeans_clustering.o kmeans_cuda.o rmse.o

kmeans: $(OBJS)
	$(CC) $(CC_FLAGS) $(OBJS) -o kmeans -L$(CUDA_LIB_DIR) -lcuda -lcudart -lm -lstdc++
%.o: %.[ch]
	$(CC) $(CC_FLAGS) $< -c
kmeans_cuda.o: kmeans_cuda.cu 
	$(NVCC) $(NVCC_FLAGS) -c kmeans_cuda.cu
clean:
	rm -f *.o *~ kmeans
