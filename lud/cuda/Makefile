
CUDA_DIR ?= $(CUDA_INSTALL_PATH)
CC = gcc
NVCC = $(CUDA_DIR)/bin/nvcc
DEFS += -DGPU_TIMER $(SPACE)
NVCCFLAGS += -I../common -O3 -use_fast_math -lm $(SPACE)# -arch=sm_13
CFLAGS += -I../common -I/usr/include/cuda -O3 -Wall $(SPACE)
EXECUTABLE := lud_cuda
CUFILES := lud_kernel.cu
CCFILES := lud.c lud_cuda.c ../common/common.c
OBJS = ../common/common.o lud.o lud_kernel.o

.PHONY: all clean 
all : $(EXECUTABLE)
.c.o : 
	$(NVCC) $(NVCCFLAGS) $(DEFS) -o $@ -c $<
%.o:	%.cu 
	$(NVCC) $(NVCCFLAGS) $(DEFS) -o $@ -c $<
$(EXECUTABLE) : $(OBJS)
	$(NVCC) $(NVCCFLAGS) -o $@  $?
clean:
	rm -f $(EXECUTABLE) $(OBJS) *.linkinfo
