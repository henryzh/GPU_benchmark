# IIX
EXE := iix
CUFILES	:= main.cu MarsScan.cu  MarsSort.cu MarsLib.cu 
CCFILES	:= MarsUtils.cpp
CUDA_DIR = /usr/local/cuda
SDK_DIR = /home/cxh/CUDA-SDK/cuda-4.2/C
CUDA_LIB_DIR := $(CUDA_DIR)/lib
ifeq ($(shell uname -m), x86_64)
     ifeq ($(shell if test -d $(CUDA_DIR)/lib64; then echo T; else echo F; fi), T)
     	CUDA_LIB_DIR := $(CUDA_DIR)/lib64
     endif
endif

OBJS := main.o MarsLib.o MarsScan.o MarsSort.o MarsUtils.o

CC = gcc
CXX = g++
CC_FLAGS = -g -O2
CXX_FLAGS = -g -O2 -I$(CUDA_DIR)/include -I$(SDK_DIR)/common/inc
NVCC = $(CUDA_DIR)/bin/nvcc
NVCC_FLAGS = -I$(CUDA_DIR)/include -I$(SDK_DIR)/common/inc

$(EXE): $(OBJS)
	$(NVCC) $(NVCC_FLAGS) $(OBJS) -o $(EXE) -L$(CUDA_LIB_DIR) -lcuda -lcudart -lm -lstdc++
MarsUtils.o: MarsUtils.cpp
	$(CXX) $(CXX_FLAGS) $< -c
main.o: main.cu
	$(NVCC) $(NVCC_FLAGS) main.cu -c -o main.o
MarsLib.o: MarsLib.cu
	$(NVCC) $(NVCC_FLAGS) MarsLib.cu -c -o MarsLib.o
MarsScan.o: MarsScan.cu
	$(NVCC) $(NVCC_FLAGS) MarsScan.cu -c -o MarsScan.o
MarsSort.o: MarsSort.cu
	$(NVCC) $(NVCC_FLAGS) MarsSort.cu -c -o MarsSort.o
clean:
	rm -f *.o *~ $(EXE) $(OBJS) 
