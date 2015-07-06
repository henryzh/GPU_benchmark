TOPLEVEL := ../..
APP=sssp
SRC=main.cu
INC=sssp_ls.h
VARIANTS=sssp sssp-wln sssp-wlc
OTHER_VARIANTS=sssp-tpatm
NVCC ?= $(CUDA_INSTALL_PATH)/bin/nvcc

EXTRA = -I$(NVIDIA_CUDA_SDK_LOCATION)/common/inc -I$(CUDAHOME)/include -I../include/lonestar
LIBS = -L$(NVIDIA_CUDA_SDK_LOCATION)/lib -lcutil_x86_64

include ../common.mk

sssp-wln: $(SRC) sssp_worklistn.h ../include/lonestar/worklist.h
	echo $(INCLUDE)
	$(NVCC) $(EXTRA) $(INCLUDE_DIR) $(LIBS) -DVARIANT=1 -o $@ $<
	cp $@ $(BIN)

sssp-wlc: $(SRC) sssp_worklistc.h ../include/lonestar/worklistc.h
	$(NVCC) $(EXTRA) $(INCLUDE_DIR) $(LIBS) -DVARIANT=2 -o $@ $<
	cp $@ $(BIN)

all: sssp-wln sssp-wlc 

.PHONY: all
