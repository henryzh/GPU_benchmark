CUDA_DIR ?= $(CUDA_INSTALL_PATH)
CUDA_LIB_DIR := $(CUDA_DIR)/lib
ifeq ($(shell uname -m), x86_64)
     ifeq ($(shell if test -d $(CUDA_DIR)/lib64; then echo T; else echo F; fi), T)
        CUDA_LIB_DIR := $(CUDA_DIR)/lib64
     endif
endif
SDK_LOCATION = $(NVIDIA_CUDA_SDK_LOCATION)
SDK_LIB := -lcutil_x86_64 -L$(NVIDIA_CUDA_SDK_LOCATION)/shared/lib -L$(NVIDIA_CUDA_SDK_LOCATION)/C/lib -L$(NVIDIA_CUDA_SDK_LOCATION)/C/common/lib/linux
CC := gcc
CXX := g++
NVCC := $(CUDA_DIR)/bin/nvcc
INCS := -I$(CUDA_DIR)/include -I$(NVIDIA_CUDA_SDK_LOCATION)/C/common/inc -I$(NVIDIA_CUDA_SDK_LOCATION)/shared/inc
LIBS := -L$(CUDA_LIB_DIR) $(SDK_LIB)
EXE := MonteCarlo
CUFILES := MonteCarlo_SM10.cu
CUFILES += MonteCarlo_SM13.cu
CUFLAGS := -O2 -arch sm_13
CCFLAGS := -O2
CU_DEPS	:= MonteCarlo_kernel.cuh \
	MonteCarlo_reduction.cuh \
	MonteCarlo_common.h \
	quasirandomGenerator_kernel.cuh \
	realtype.h
CCFILES	:= MonteCarlo.cpp MonteCarlo_gold.cpp
# Do not link with SHRUTIL
OMIT_SHRUTIL_LIB := 1
SRC := $(CUFILES) 
#$(CCFILES)
OBJ := MonteCarlo.o MonteCarlo_gold.o

release: $(SRC) $(OBJ)
	$(NVCC) $(CUFLAGS) $(OBJ) $(SRC) -o $(EXE) $(INCS) $(LIBS)
MonteCarlo_gold.o: MonteCarlo_gold.cpp
	$(CXX) $(CCFLAGS) MonteCarlo_gold.cpp -c -o MonteCarlo_gold.o
MonteCarlo.o: MonteCarlo.cpp
	$(CXX) $(CCFLAGS) $(INCS) $(LIBS) MonteCarlo.cpp -c -o MonteCarlo.o
clean: $(SRC)
	rm -f *.o $(EXE) 
