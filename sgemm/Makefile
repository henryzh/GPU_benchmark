# Sgemm, Xuhao Chen, UIUC
CUDA_DIR = /usr/local/cuda
CUDA_LIB_DIR = $(CUDA_DIR)/lib64
COMMON = ../common
CC = gcc
CXX = g++
NVCC = $(CUDA_DIR)/bin/nvcc
LIBS = -L$(CUDA_LIB_DIR) -lm -lstdc++
INCS = -I$(CUDA_DIR)/include -I$(COMMON)
CFLAGS = -O2
NVFLAGS = -O2 -arch=sm_20
KERNEL_SRC = kernel_omp.cc
SRC = main.cu
OBJ = main.o io.o args.o parboil_cuda.o
EXE = sgemm

release: $(OBJ)
	$(NVCC) $(NVFLAGS) $(LIBS) $(INCS) $(OBJ) -o $(EXE)
main.o: $(SRC)
	$(NVCC) $(NVFLAGS) $(LIBS) $(INCS) $(SRC) -c -o main.o
io.o: io.cc
	$(CXX) $(CFLAGS) io.cc -c -o io.o
parboil_cuda.o: $(COMMON)/parboil_cuda.c
	$(NVCC) $(NVCC_FLAGS) -c $(COMMON)/parboil_cuda.c -o parboil_cuda.o
args.o: $(COMMON)/args.c
	$(CC) $(CC_FLAGS) -c $(COMMON)/args.c -o args.o
clean: $(SRC)
	rm -f $(EXE) *.o
