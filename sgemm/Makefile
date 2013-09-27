# Sgemm, Xuhao Chen, UIUC
CUDA_DIR = /usr/local/cuda
CUDA_LIB_DIR = $(CUDA_DIR)/lib64
CC = gcc
CXX = g++
NVCC = $(CUDA_DIR)/bin/nvcc
LIBS = -lm #-L$(CUDA_LIB_DIR)
INCLUDE = -I$(CUDA_DIR)/include
CC_FLAGS = -O2
CXX_FLAGS = -O2 -fopenmp -lstdc++
NVCC_FLAGS = -O2 -arch=sm_20
KERNEL_SRC = kernel_omp.cc
SRC = main.cc
OBJ = kernel.o io.o args.o parboil.o #parboil_cuda.o
EXE = sgemm

release: $(OBJ)
	$(CXX) $(CXX_FLAGS) $(LIBS) $(SRC) $(OBJ) -o $(EXE)
kernel.o: $(KERNEL_SRC)
	$(CXX) $(CXX_FLAGS) $(KERNEL_SRC) -c -o kernel.o
io.o: io.cc
	$(CXX) $(CXX_FLAGS) io.cc -c -o io.o
args.o: ../args.c
	$(CC) $(CC_FLAGS) -c ../args.c -o args.o
parboil.o: ../parboil.c
	$(CC) $(CC_FLAGS) $(LIBS) -c ../parboil.c -o parboil.o
parboil_cuda.o: ../parboil_cuda.c
	$(NVCC) $(NVCC_FLAGS) $(LIBS) -c ../parboil_cuda.c -o parboil_cuda.o
clean: $(SRC)
	rm -f $(EXE) *.o
