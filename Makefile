CC=gcc
#CC=mips_4KCle-gcc

CFLAGS=-g3 -O0 -ggdb -static

all: swapbin

swapbin: swapbin.c Makefile
	$(CC) $(CFLAGS) swapbin.c -o swapbin 

clean: 
	rm -f swapbin
