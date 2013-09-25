# FFT, Xuhao Chen, UIUC
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
SRC = fft_base.cu
OBJ = args.o parboil_cuda.o
EXE = fft

release: $(OBJ)
	$(NVCC) $(NVCC_FLAGS) $(SRC) $(OBJ) -o $(EXE)

fft.o: fft.cu
	$(NVCC) $(NVCC_FLAGS) $(SRC) -c -o fft.o

parboil_cuda.o: ../parboil_cuda.c
	$(NVCC) $(NVCC_FLAGS) -c ../parboil_cuda.c -o parboil_cuda.o

args.o: ../args.c
	$(CC) $(CC_FLAGS) -c ../args.c -o args.o

clean: $(SRC)
	rm -f $(EXE) *.o
