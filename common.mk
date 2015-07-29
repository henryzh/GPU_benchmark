CUDA_DIR = $(CUDA_INSTALL_PATH)
CUDA_LIB_DIR := $(CUDA_DIR)/lib
ifeq ($(shell uname -m), x86_64)
     ifeq ($(shell if test -d $(CUDA_DIR)/lib64; then echo T; else echo F; fi), T)
        CUDA_LIB_DIR := $(CUDA_DIR)/lib64
     endif
endif

CC := $(CUDA_DIR)/bin/nvcc
INCLUDE := $(CUDA_DIR)/include
all:
	$(CC) -O3 ${CUFILES} -o ${EXECUTABLE} -I$(INCLUDE) -L$(CUDA_LIB_DIR)
clean:
	rm -f *~ *.exe
