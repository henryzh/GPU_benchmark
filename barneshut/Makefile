CUDA_DIR ?= $(CUDA_INSTALL_PATH)
# CUDA toolkit libraries
CUDA_LIB_DIR := $(CUDA_DIR)/lib
ifeq ($(shell uname -m), x86_64)
     ifeq ($(shell if test -d $(CUDA_DIR)/lib64; then echo T; else echo F; fi), T)
     	CUDA_LIB_DIR := $(CUDA_DIR)/lib64
     endif
endif

CC := $(CUDA_DIR)/bin/nvcc
INCLUDE := $(CUDA_DIR)/include

EXE := barneshut
SRC := barnes_hut.cu
CUFLAGS += -arch=sm_13 -Xptxas -dlcm=cg #-g

release: $(SRC)
	$(CC) $(CUFLAGS) $(SRC) -o $(EXE) -I$(INCLUDE) -L$(CUDA_LIB_DIR)
clean: $(SRC)
	rm -f $(EXE) 

