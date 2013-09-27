# (c) Copyright 2013, University of Illinois.
# MPI Sgemm, Xuhao Chen, UIUC

LANGUAGE=mpi
MPI_DIR = /usr/lib/mpich2
MPI_INC_DIR = $(MPI_DIR)/include
MPI_LIB_DIR = $(MPI_DIR)/lib
CC = gcc
CXX = g++
MPICXX = mpicxx
LIBS = -lm -L$(MPI_DIR)/lib
INCS = -I$(MPI_INC_DIR) -I./
CC_FLAGS = -O2
CXX_FLAGS = -O2 -fopenmp -lstdc++
MPI_FLAGS = -O2 -Wall -Wextra -pedantic -std=gnu99
KERNEL_SRC = kernel.cc
SRC = main.cc
OBJ = io.o args.o parboil.o
EXE = sgemm

release: $(OBJ)
	$(MPICXX) $(CXX_FLAGS) $(LIBS) $(INCS) $(SRC) $(OBJ) -o $(EXE)
kernel.o: $(KERNEL_SRC)
	$(CXX) $(CXX_FLAGS) $(KERNEL_SRC) -c -o kernel.o
io.o: io.cc
	$(CXX) $(CXX_FLAGS) io.cc -c -o io.o
args.o: args.c
	$(CC) $(CC_FLAGS) -c args.c -o args.o
parboil.o: parboil.c
	$(CC) $(CC_FLAGS) $(LIBS) -c parboil.c -o parboil.o
parboil_cuda.o: parboil_cuda.c
	$(NVCC) $(NVCC_FLAGS) $(LIBS) -c parboil_cuda.c -o parboil_cuda.o
clean: $(SRC)
	rm -f $(EXE) *.o
