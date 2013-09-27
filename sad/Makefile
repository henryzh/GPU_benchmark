# SAD, Xuhao Chen, UIUC
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
EXE = sad
OBJ = file.o image.o sad4.o largerBlocks.o main.o parboil_cuda.o args.o

all: $(OBJ)
	$(NVCC) $(NVCC_FLAGS) $(OBJ) -o $(EXE)
main.o: main.cu
	$(NVCC) $(NVCC_FLAGS) main.cu -c -o main.o
largerBlocks.o: largerBlocks.cu
	$(NVCC) $(NVCC_FLAGS) largerBlocks_base.cu -c -o largerBlocks.o
sad4.o: sad4.cu
	$(NVCC) $(NVCC_FLAGS) sad4_base.cu -c -o sad4.o
file.o: file.c
	$(CC) $(CC_FLAGS) file.c -c -o file.o
image.o: image.c
	$(CC) $(CC_FLAGS) image.c -c -o image.o
parboil_cuda.o: ../parboil_cuda.c
	$(NVCC) $(NVCC_FLAGS) -c ../parboil_cuda.c -o parboil_cuda.o
args.o: ../args.c
	$(CC) $(CC_FLAGS) -c ../args.c -o args.o
clean: $(SRC)
	rm -f $(EXE) *.o
