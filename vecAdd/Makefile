# Vector Addition
BENCH_HOME=/home/cxh/benchmarks
CUDA_DIR=/usr/local/cuda
NVCC = $(CUDA_DIR)/bin/nvcc
CC = gcc
CXX = g++
CCFLAGS = -g -O2
CXXFLAGS = -g -O2
CUFLAGS = -O2 -arch=sm_20
LIBS = -lm
SRC = vecAdd.cu
EXE = vecAdd

all: $(OBJS)
	$(NVCC) $(CUFLAGS) $(LIBS) $(SRC) $(OBJS) -o $(EXE)
clean:
	rm -f $(EXE) *.o
