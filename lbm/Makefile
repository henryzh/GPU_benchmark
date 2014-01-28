# LBM, Xuhao Chen, UIUC
#CUDA_DIR = /home/cxh/local/cuda-4.1/cuda
CUDA_DIR = /usr/local/cuda
CUDA_LIB_DIR = $(CUDA_DIR)/lib64
CC = gcc
CXX = g++
NVCC = $(CUDA_DIR)/bin/nvcc
LIB = -L/usr/local/cuda/lib64 -lm -lpthread
INCLUDE = $(CUDA_DIR)/include
CC_FLAGS = -I$(INCLUDE) -L$(CUDA_LIB_DIR)
NVCC_FLAGS = -I$(INCLUDE) -L$(CUDA_LIB_DIR) #-arch=sm_10
# 'make dbg=1' enables NVCC debugging
ifeq ($(dbg),1)
	CC_FLAGS += -g -O0
	NVCC_FLAGS += -g -O0
else
	CC_FLAGS += -O2
	NVCC_FLAGS += -O2
endif
SRC = lbm.cu
OBJ = args.o parboil_cuda.o main.o lbm.o
EXE = lbm

release: $(OBJ)
	$(NVCC) $(NVCC_FLAGS) $(OBJ) -o $(EXE)
lbm.o: lbm.cu
	$(NVCC) $(NVCC_FLAGS) $(SRC) -c -o lbm.o
parboil_cuda.o: ../common/parboil_cuda.c
	$(NVCC) $(NVCC_FLAGS) -c ../common/parboil_cuda.c -o parboil_cuda.o
args.o: ../common/args.c
	$(CC) $(CC_FLAGS) -c ../common/args.c -o args.o
main.o: main.cc
	$(CXX) $(CC_FLAGS) -c main.cc -o main.o
clean: $(SRC)
	rm -f $(EXE) *.o
