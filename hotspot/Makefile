# CUDA Hotspot
CUDA_DIR = /usr/local/cuda
CUDA_LIB_DIR := $(CUDA_DIR)/lib
ifeq ($(shell uname -m), x86_64)
     ifeq ($(shell if test -d $(CUDA_DIR)/lib64; then echo T; else echo F; fi), T)
     	CUDA_LIB_DIR := $(CUDA_DIR)/lib64
     endif
endif

NVCC = $(CUDA_DIR)/bin/nvcc
NVCC_FLAGS = -O2 -arch=sm_20 #-Xptxas -dlcm=cg # -g
INCS = -I$(CUDA_DIR)/include
LIBS = -L$(CUDA_LIB_DIR)
SRC = hotspot.cu
EXE = hotspot

release: $(SRC)
	$(NVCC) $(NVCC_FLAGS) $(SRC) -o $(EXE) $(INCS) $(LIBS)  
clean: $(SRC)
	rm -f $(EXE) result.txt
