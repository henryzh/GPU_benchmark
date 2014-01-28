# IMPACT, University of Illinois
PARBOIL_DIR = ../common
CUDA_DIR = /usr/local/cuda
CUDA_LIB_DIR := $(CUDA_DIR)/lib
ifeq ($(shell uname -m), x86_64)
     ifeq ($(shell if test -d $(CUDA_DIR)/lib64; then echo T; else echo F; fi), T)
        CUDA_LIB_DIR := $(CUDA_DIR)/lib64
     endif
endif

NVCC = $(CUDA_DIR)/bin/nvcc
CUFLAGS = -arch=sm_20 -Xptxas -dlcm=cg #--ptxas-options=-v
INCLUDE = -I$(CUDA_DIR)/include -I./
SRC = main.cu
OBJS = args.o parboil_cuda.o
EXE = bfs

release: $(OBJS)
	$(NVCC) $(CUFLAGS) $(SRC) $(OBJS) -o $(EXE) $(INCLUDE) -L$(CUDA_LIB_DIR) -lm -lstdc++

parboil_cuda.o: $(PARBOIL_DIR)/parboil_cuda.c
	$(NVCC) $(NVCC_FLAGS) -c $(PARBOIL_DIR)/parboil_cuda.c -o parboil_cuda.o

args.o: $(PARBOIL_DIR)/args.c
	$(CC) $(CC_FLAGS) -c $(PARBOIL_DIR)/args.c -o args.o

clean: $(SRC)
	rm -f $(EXE) *.o result.txt
