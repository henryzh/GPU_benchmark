CUDA_DIR = /usr/local/cuda
# CUDA toolkit libraries
CUDA_LIB_DIR := $(CUDA_DIR)/lib
ifeq ($(shell uname -m), x86_64)
     ifeq ($(shell if test -d $(CUDA_DIR)/lib64; then echo T; else echo F; fi), T)
     	CUDA_LIB_DIR := $(CUDA_DIR)/lib64
     endif
endif

CC := gcc
NVCC := $(CUDA_DIR)/bin/nvcc
INCS := -I$(CUDA_DIR)/include
#SDK_INC := /home/cxh/CUDA-SDK/cuda-4.2/C/common/inc
#SDK_LIB := /home/cxh/CUDA-SDK/cuda-4.2/C/lib
LIBS := -L$(CUDA_LIB_DIR)
EXE := RAY
CUFILES	+= rayTracing.cu
CCFILES := EasyBMP.cpp makebmp.cpp

SRC := $(CUFILES) $(CCFILES)

release: $(SRC)
	$(NVCC) $(SRC) -o $(EXE) $(INCS) $(LIBS) #-L$(SDK_LIB) -I$(SDK_INC)
clean: $(SRC)
	rm -f $(EXE)
