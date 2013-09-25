# For graphics, uncomment -lX11 flag and comment out -DNO_GRAPHICS flag

CC = gcc
NVCC = $(CUDA_INSTALL_PATH)/bin/nvcc
LIB_DIR = -L/usr/lib/X11 -L../libvpr -L/usr/lib64/X11
LIB = -lm -lX11 -lvpr_6
#LIB = -lm -lvpr_6
EXE_DIR = $(BINDIR)/$(BINSUBDIR)

CU_LIB = -lcudart #-lcutil_x86_64 -lshrutil_x86_64
CU_LIB_DIR = -L$(CUDA_INSTALL_PATH)/lib64

SRC_DIR = SRC
OBJ_DIR = OBJ
EXE_DIR = ..
OTHER_DIR = -ISRC/util -ISRC/timing -ISRC/pack -ISRC/place -ISRC/base -ISRC/route

WARN_FLAGS = -Wall -Wpointer-arith -Wcast-qual -Wstrict-prototypes -O -D__USE_FIXED_PROTOTYPES__ -ansi -pedantic -Wmissing-prototypes -Wshadow -Wcast-align -D_POSIX_SOURCE
DEBUG_FLAGS = -g
OPT_FLAGS = -O2
INC_FLAGS = -m64 -fno-strict-aliasing -I../libvpr/include
CU_INC_FLAGS = -I$(CUDA_INSTALL_PATH)/lib64 -I../libvpr/include -I$(NVIDIA_COMPUTE_SDK_LOCATION)/C/common/inc  #-Xptxas -dlcm=cg

#FLAGS = $(WARN_FLAGS) -D EZXML_NOMMAP  -D_POSIX_C_SOURCE
#FLAGS = $(OPT_FLAGS) $(INC_FLAGS) -D EZXML_NOMMAP -DNO_GRAPHICS -D_POSIX_C_SOURCE

#FLAGS = $(INC_FLAGS) $(DEBUG_FLAGS) -D EZXML_NOMMAP -D_POSIX_C_SOURCE
FLAGS = $(INC_FLAGS) $(OPT_FLAGS) -D EZXML_NOMMAP -D_POSIX_C_SOURCE -DNO_GRAPHICS

#FLAGS = $(DEBUG_FLAGS) $(INC_FLAGS) -pedantic  -D EZXML_NOMMAP  -D_POSIX_C_SOURCE
#FLAGS = $(DEBUG_FLAGS) -pedantic -D EZXML_NOMMAP -Wall -D_POSIX_C_SOURCE
#FLAGS = $(DEBUG_FLAGS) $(INC_FLAGS) -pedantic  -D EZXML_NOMMAP -DNO_GRAPHICS -D_POSIX_C_SOURCE

CU_FLAGS = --ptxas-options=-v -arch sm_20 -m64 $(CU_INC_FLAGS)

EXE = vpr_exe

OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o,$(wildcard $(SRC_DIR)/*.c $(SRC_DIR)/*/*.c))
OBJ_DIRS=$(sort $(dir $(OBJ)))
CU_OBJ = $(patsubst $(SRC_DIR)/%.cu, $(OBJ_DIR)/%.o,$(wildcard $(SRC_DIR)/*.cu $(SRC_DIR)/*/*.cu))
CU_OBJ_DIRS=$(sort $(dir $(CU_OBJ)))
DEP := $(OBJ:.o=.d)

$(EXE): $(OBJ) $(CU_OBJ) Makefile ../libvpr/libvpr_6.a
	$(CC) $(FLAGS) $(CU_INC_FLAGS) $(CU_OBJ) $(OBJ) -lstdc++ -o $(EXE_DIR)/$(EXE) $(LIB_DIR) $(CU_LIB_DIR) $(LIB) $(CU_LIB)

# Enable a second round of expansion so that we may include
# the target directory as a prerequisite of the object file.
.SECONDEXPANSION:

# The directory follows a "|" to use an existence check instead of the usual
# timestamp check.  Every write to the directory updates the timestamp thus
# without this, all but the last file written to a directory would appear
# to be out of date.
$(OBJ): OBJ/%.o:$(SRC_DIR)/%.c | $$(dir $$@D)
	$(CC) $(FLAGS) -MD -MP $(X11_INCLUDE) -I$(OTHER_DIR) -ISRC/util -I. -c $< -o $@

$(CU_OBJ): OBJ/%.o:$(SRC_DIR)/%.cu | $$(dir $$@D)
	$(NVCC) $(CU_FLAGS) -I$(OTHER_DIR) -ISRC/util -c $< -o $@


# Silently create target directories as need
$(OBJ_DIRS):
	@ mkdir -p $@

-include $(DEP)

clean:
	rm -f $(EXE_DIR)/$(EXE) $(OBJ) $(DEP) $(CU_OBJ)
	
clean_coverage: clean
	rm -rf ./usr
	find ./OBJ -regex ".*.\(gcda\|gcno\)" -exec rm -f {} \;
	rm -f *.html
	find ./SRC -iname "*.html" -exec rm -f {} \;
	

ctags:
	cd $(SRC_DIR) && ctags *.[ch]
	
# This is using Target-specific variable values. See: http://www.gnu.org/software/make/manual/make.html#Target_002dspecific
coverage: FLAGS = $(DEBUG_FLAGS) $(INC_FLAGS) -pedantic  -D EZXML_NOMMAP -fprofile-arcs -ftest-coverage -lgcov
coverage: $(EXE)
	./coverage_reset.sh
