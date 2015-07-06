TOPLEVEL := ../..
APP=nsp
CUFILES=newsp.cu
SUPPORT=genformula

include ../common.mk

genformula: genformula.c
	$(CC) -O -o $@ $<
