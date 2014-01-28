# SAD, Xuhao Chen, UIUC
CUDA_DIR = /usr/local/cuda
CUDA_LIB_DIR = $(CUDA_DIR)/lib64
COMMON = ../common
CC = gcc
CXX = g++
NVCC = $(CUDA_DIR)/bin/nvcc
LIBS = -L$(CUDA_LIB_DIR) -lm
INCS = -I$(CUDA_DIR)/include -I$(COMMON)
CCFLAGS = -O2
NVCC_FLAGS = -O2 $(INCS) $(LIBS)
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
parboil_cuda.o: $(COMMON)/parboil_cuda.c
	$(NVCC) $(NVCC_FLAGS) -c $(COMMON)/parboil_cuda.c -o parboil_cuda.o
args.o: $(COMMON)/args.c
	$(CC) $(CC_FLAGS) -c $(COMMON)/args.c -o args.o
clean: $(SRC)
	rm -f $(EXE) *.o
