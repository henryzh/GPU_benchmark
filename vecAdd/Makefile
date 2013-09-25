# Vector Addition
BENCH_HOME=/home/cxh/benchmarks
CUDART_DIR=/home/cxh/gem5-stable/src/accel/libcuda
#PREFIX = arm-linux-gnueabi-
CUDA_DIR=/usr/local/cuda
#CUDA_DIR=/home/cxh/local/cuda-3.1/cuda
NVCC = $(CUDA_DIR)/bin/nvcc
CC = $(PREFIX)gcc
CXX = $(PREFIX)g++
AS = $(PREFIX)as
#PORT_FLAGS = -static-libgcc -static 
CC_FLAGS = -g -O2 $(PORT_FLAGS)
CXX_FLAGS = -g -O2 $(PORT_FLAGS)
#HOOKS_INC = -DENABLE_HOOKS -I$(BENCH_HOME)/hooks/include
LIBS = -lm
#OBJS = $(M5OP_OBJ) $(HOOK_OBJ) $(CUDART_OBJ)
M5OP_OBJ = m5op_x86.o
HOOK_OBJ = hooks.o
CUDART_OBJ = cuda_runtime_api_if.o
EXE = vecAdd

all: $(OBJS)
	$(NVCC) $(CC_FLAGS) $(HOOKS_INC) $(LIBS) vecAdd.cu $(OBJS) -o $(EXE)

$(M5OP_OBJ): $(BENCH_HOME)/hooks/m5op_x86.S
	$(CC) $(HOOKS_INC) -O2 -o $(M5OP_OBJ) -c $<

$(HOOK_OBJ): $(BENCH_HOME)/hooks/hooks.c
	$(CC) $(HOOKS_INC) -O2 -Wall -D_GNU_SOURCE -D_XOPEN_SOURCE=600 -o $(HOOK_OBJ) -c $<

$(CUDART_OBJ): $(CUDART_DIR)/cuda_runtime_api_if.cc
	$(CXX) -O2 -Wall -fPIC -I$(CUDA_DIR)/include -I$(CUDART_DIR) -o $(CUDART_OBJ) -c $<

clean:
	rm -f $(EXE) *.o
