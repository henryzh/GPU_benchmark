CUDA_DIR ?= $(CUDA_INSTALL_PATH)
CUDA_LIB_DIR := $(CUDA_DIR)/lib
ifeq ($(shell uname -m), x86_64)
     ifeq ($(shell if test -d $(CUDA_DIR)/lib64; then echo T; else echo F; fi), T)
        CUDA_LIB_DIR := $(CUDA_DIR)/lib64
     endif
endif
SDK_DIR ?= $(NVIDIA_CUDA_SDK_LOCATION)
SDK_LIB := -lshrutil_x86_64 -lcutil_x86_64 -L$(SDK_DIR)/shared/lib -L$(SDK_DIR)/C/lib -L$(SDK_DIR)/C/common/lib/linux
CC := gcc
CXX := g++
NVCC := $(CUDA_DIR)/bin/nvcc
INCS := -I$(CUDA_DIR)/include -I$(SDK_DIR)/C/common/inc -I$(SDK_DIR)/shared/inc
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
