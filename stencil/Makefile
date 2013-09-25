#Xuhao Chen <cxh@illinois.edu>
CUDA_DIR = /usr/local/cuda
#CUDA_DIR = /home/cxh/local/cuda-5.5
CUDA_LIB_DIR = $(CUDA_DIR)/lib64
CC = gcc
CXX = g++
NVCC = $(CUDA_DIR)/bin/nvcc
LIBS = -L/usr/local/cuda/lib64 -lm -lpthread -lstdc++
INCS = -I$(CUDA_DIR)/include
CCFLAGS = -g -O2 -I$(INCLUDE) -L$(CUDA_LIB_DIR)
CUFLAGS= -O2 -arch=sm_20
SRC = main.cu
OBJ = args.o parboil_cuda.o
EXE = stencil

release: $(OBJ)
	$(NVCC) $(CUFLAGS) $(SRC) $(OBJ) -o $(EXE) $(INCS) $(LIBS) 

parboil_cuda.o: parboil_cuda.c
	$(CC) -c parboil_cuda.c -o parboil_cuda.o $(INCS) $(LIBS)

args.o: args.c
	$(CC) -c args.c -o args.o $(CC_FLAGS)

main.o: main.cu
	$(NVCC) -O2 main.cu -c -o main.o -I$(INCLUDE) -L$(CUDA_LIB_DIR) 

clean: $(SRC)
	rm -f $(EXE) *.o
