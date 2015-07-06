# CUDA Sum
CUDA_DIR ?= $(CUDA_INSTALL_PATH)
CUDA_LIB_DIR := $(CUDA_DIR)/lib
ifeq ($(shell uname -m), x86_64)
     ifeq ($(shell if test -d $(CUDA_DIR)/lib64; then echo T; else echo F; fi), T)
        CUDA_LIB_DIR := $(CUDA_DIR)/lib64
     endif
endif

NVCC = $(CUDA_DIR)/bin/nvcc
INCS := -I$(CUDA_DIR)/include

CC = gcc
CXX = g++ 
CCFLAGS = -g -O2 $(PORT_FLAGS)
CXXFLAGS = -g -O2 $(PORT_FLAGS)
CUFLAGS = -O2 -arch=sm_20 -Xptxas -dlcm=cg
LIBS = -L$(CUDA_LIB_DIR) -lm
SRC = reduction.cu
EXE = reduction

all: $(OBJS)
	$(NVCC) $(CUFLAGS) $(INCS) $(LIBS) $(SRC) $(OBJS) -o $(EXE)
clean:
	rm -f $(EXE) *.o
