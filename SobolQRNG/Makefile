CUDA_DIR = /usr/local/cuda
CUDA_LIB_DIR := $(CUDA_DIR)/lib
ifeq ($(shell uname -m), x86_64)
     ifeq ($(shell if test -d $(CUDA_DIR)/lib64; then echo T; else echo F; fi), T)
        CUDA_LIB_DIR := $(CUDA_DIR)/lib64
     endif
endif
SDK_LIB := -lshrutil_x86_64 -lcutil_x86_64 -L/home/cxh/CUDA-SDK/cuda-4.2/shared/lib -L/home/cxh/CUDA-SDK/cuda-4.2/C/lib -L/home/cxh/CUDA-SDK/cuda-4.2/C/common/lib/linux
CC := gcc
CXX := g++
NVCC := $(CUDA_DIR)/bin/nvcc
INCS := -I$(CUDA_DIR)/include -I/home/cxh/CUDA-SDK/cuda-4.2/C/common/inc -I/home/cxh/CUDA-SDK/cuda-4.2/shared/inc
LIBS := -L$(CUDA_LIB_DIR) $(SDK_LIB)
EXE := sobol
CUFILES := sobol_gpu.cu
#CUFILES += 
CUFLAGS := -O2 -arch sm_13
CCFLAGS := -O2
CCFILES	:= sobol.cpp sobol_gold.cpp sobol_primitives.cpp
# Do not link with SHRUTIL
OMIT_SHRUTIL_LIB := 1
SRC := $(CUFILES) 
#$(CCFILES)
OBJ := sobol.o sobol_gold.o sobol_primitives.o

release: $(SRC) $(OBJ)
	$(NVCC) $(CUFLAGS) $(OBJ) $(SRC) -o $(EXE) $(INCS) $(LIBS)
sobol_gold.o: sobol_gold.cpp
	$(CXX) $(CCFLAGS) $(INCS) $(LIBS) sobol_gold.cpp -c -o sobol_gold.o
sobol.o: sobol.cpp
	$(CXX) $(CCFLAGS) $(INCS) $(LIBS) sobol.cpp -c -o sobol.o
sobol_primitives.o: sobol_primitives.cpp
	$(CXX) $(CCFLAGS) $(INCS) $(LIBS) sobol_primitives.cpp -c -o sobol_primitives.o
clean: $(SRC)
	rm -f *.o $(EXE) 
