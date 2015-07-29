CUDA_DIR ?= $(CUDA_INSTALL_PATH)
CUDA_LIB_DIR := $(CUDA_DIR)/lib
ifeq ($(shell uname -m), x86_64)
     ifeq ($(shell if test -d $(CUDA_DIR)/lib64; then echo T; else echo F; fi), T)
     	CUDA_LIB_DIR := $(CUDA_DIR)/lib64
     endif
endif

CC := $(CUDA_DIR)/bin/nvcc
CUFLAGS := -O2 --ptxas-options=-v
INCLUDE := $(CUDA_DIR)/include
SRC = pathfinder.cu
EXE = pathfinder

release:
	$(CC) $(SRC) $(CUFLAGS) -o $(EXE) -I$(INCLUDE) -L$(CUDA_LIB_DIR)
clean:
	rm -f pathfinder
