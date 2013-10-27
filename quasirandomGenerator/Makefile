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
EXE := quasirandomGenerator
CUFILES := quasirandomGenerator_SM10.cu
CUFILES += quasirandomGenerator_SM13.cu
CUFLAGS := -O2 -arch sm_13
CCFLAGS := -O2
CCFILES	:= quasirandomGenerator.cpp quasirandomGenerator_gold.cpp
# Do not link with SHRUTIL
OMIT_SHRUTIL_LIB := 1
SRC := $(CUFILES) 
#$(CCFILES)
OBJ := quasirandomGenerator.o quasirandomGenerator_gold.o

release: $(SRC) $(OBJ)
	$(NVCC) $(CUFLAGS) $(OBJ) $(SRC) -o $(EXE) $(INCS) $(LIBS)
quasirandomGenerator_gold.o: quasirandomGenerator_gold.cpp
	$(CXX) $(CCFLAGS) $(INCS) $(LIBS) quasirandomGenerator_gold.cpp -c -o quasirandomGenerator_gold.o
quasirandomGenerator.o: quasirandomGenerator.cpp
	$(CXX) $(CCFLAGS) $(INCS) $(LIBS) quasirandomGenerator.cpp -c -o quasirandomGenerator.o
clean: $(SRC)
	rm -f *.o $(EXE) 
