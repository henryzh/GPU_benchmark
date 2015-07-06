TOPLEVEL := ../..
APP=nsp
CUFILES=newsp.cu
SUPPORT=genformula

include ../common.mk

genformula: genformula.c
	$(CC) -I/../include/lonestar -O -o $@ $<
