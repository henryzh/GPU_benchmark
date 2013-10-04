#CUDA Srad1
CUDA_DIR = /usr/local/cuda
CUDA_LIB_DIR := $(CUDA_DIR)/lib
ifeq ($(shell uname -m), x86_64)
     ifeq ($(shell if test -d $(CUDA_DIR)/lib64; then echo T; else echo F; fi), T)
     	CUDA_LIB_DIR := $(CUDA_DIR)/lib64
     endif
endif

CC = gcc
NVCC = $(CUDA_DIR)/bin/nvcc
INCS = -I$(CUDA_DIR)/include
LIBS = -L$(CUDA_LIB_DIR) -lm -lcuda -lcudart

a.out: main.o
	$(NVCC)	main.o $(INCS) $(LIBS) -o srad
main.o: main.cu define.c graphics.c extract_kernel.cu prepare_kernel.cu \
	reduce_kernel.cu srad_kernel.cu srad2_kernel.cu compress_kernel.cu
	$(NVCC) main.cu -c -O3 
#-arch sm_13
clean:
	rm *.o srad
