# SPMV Parboil
TOOLS_DIR=./common
OBJS=main.o file.o gpu_info.o parboil_cuda.o args.o
TOOLS_FLAG=-I$(TOOLS_DIR)
OBJS += common/convert_dataset.o common/mmio.o

CUDA_DIR = /usr/local/cuda
CUDA_LIB_DIR = $(CUDA_DIR)/lib64
CC = gcc
CXX = g++
NVCC = $(CUDA_DIR)/bin/nvcc
LIB = -L/usr/local/cuda/lib64 -lm -lpthread -lstdc++
INCLUDE = $(CUDA_DIR)/include
CC_FLAGS = -I$(INCLUDE) -L$(CUDA_LIB_DIR)
NVCC_FLAGS = -I$(INCLUDE) -L$(CUDA_LIB_DIR)

# 'make dbg=1' enables NVCC debugging
ifeq ($(dbg),1)
	CC_FLAGS += -g -O0
	NVCC_FLAGS += -g -O0
else
	CC_FLAGS += -O2
	NVCC_FLAGS += -O2
endif
EXE = spmv

release: $(OBJS)
	$(NVCC) $(NVCC_FLAGS) $(OBJS) -o $(EXE)

main.o: main.cu
	$(NVCC) $(NVCC_FLAGS) $(TOOLS_FLAG) main.cu -c -o main.o

file.o: file.cc
	$(CXX) $(CC_FLAGS) -c file.cc -o file.o

gpu_info.o: gpu_info.cc
	$(CXX) $(CC_FLAGS) -c gpu_info.cc -o gpu_info.o

parboil_cuda.o: ../parboil_cuda.c
	$(NVCC) $(NVCC_FLAGS) -c ../parboil_cuda.c -o parboil_cuda.o

args.o: ../args.c
	$(CC) $(CC_FLAGS) -c ../args.c -o args.o

clean: $(SRC)
	rm -f $(EXE) *.o
