CUDA_DIR ?= $(CUDA_INSTALL_PATH)
# CUDA toolkit libraries
CUDA_LIB_DIR := $(CUDA_DIR)/lib
ifeq ($(shell uname -m), x86_64)
     ifeq ($(shell if test -d $(CUDA_DIR)/lib64; then echo T; else echo F; fi), T)
     	CUDA_LIB_DIR := $(CUDA_DIR)/lib64
     endif
endif

CC = gcc
NVCC := $(CUDA_DIR)/bin/nvcc
CUFLAGS := -g -O3
INCLUDE := $(CUDA_DIR)/include
SRC = nn_cuda.cu
EXE = nn

all : nn hurricane_gen
nn : nn_cuda.cu
	$(NVCC) $(SRC) -o $(EXE)
hurricane_gen : hurricane_gen.c
	$(CC) -o $@ $< -lm
#data :
#	mkdir data
#	./gen_dataset.sh
clean :
	rm -rf *.o nn hurricane_gen
