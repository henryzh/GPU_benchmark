# Vector Addition
BENCH_HOME=/home/cxh/benchmarks
CUDA_DIR ?= $(CUDA_INSTALL_PATH)
NVCC = $(CUDA_DIR)/bin/nvcc
CC = gcc
CXX = g++
CCFLAGS = -g -O2
CXXFLAGS = -g -O2
CUFLAGS = -O2 -arch=sm_13
LIBS = -lm
SRC = vecAdd.cu
EXE = vecAdd

all: $(OBJS)
	$(NVCC) $(CUFLAGS) $(LIBS) $(SRC) $(OBJS) -o $(EXE)
clean:
	rm -f $(EXE) *.o
