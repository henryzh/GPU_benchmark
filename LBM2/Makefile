# LBM, Xuhao Chen, UIUC
COMMON=/home/cxh/benchmarks/common
CUDA_DIR = /usr/local/cuda
CUDA_LIB_DIR = $(CUDA_DIR)/lib64
CC = gcc
CXX = g++
NVCC = $(CUDA_DIR)/bin/nvcc
LIB = -L/usr/local/cuda/lib64 -lm -lpthread
INCLUDE = $(CUDA_DIR)/include -I$(COMMON)
CC_FLAGS = -I$(INCLUDE) -L$(CUDA_LIB_DIR)
NVCC_FLAGS = -I$(INCLUDE) -L$(CUDA_LIB_DIR) #-arch=sm_10
SRC = lbm.cu
OBJ = args.o parboil_cuda.o main.o lbm.o
EXE = lbm

release: $(OBJ)
	$(NVCC) $(NVCC_FLAGS) $(OBJ) -o $(EXE)
lbm.o: lbm.cu
	$(NVCC) $(NVCC_FLAGS) $(SRC) -c -o lbm.o
parboil_cuda.o: $(COMMON)/parboil_cuda.c
	$(NVCC) $(NVCC_FLAGS) -c $(COMMON)/parboil_cuda.c -o parboil_cuda.o
args.o: $(COMMON)/args.c
	$(CC) $(CC_FLAGS) -c $(COMMON)/args.c -o args.o
main.o: main.cc
	$(CXX) $(CC_FLAGS) -c main.cc -o main.o
clean: $(SRC)
	rm -f $(EXE) *.o
