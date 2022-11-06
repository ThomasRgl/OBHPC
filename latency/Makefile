CC=clang
CFLAGS=-g

OFLAGS= -O2 -march=native -mtune=native 

CLANG=/usr/bin/clang
AOCC=/opt/aocc/bin/clang

LDFLAGS=-lm 

FILES=main.c tools.c kernels.c

all: 
	$(CC) $(CFLAGS) $(OFLAGS) $(FILES) -o stability $(LDFLAGS)


clean:
	@rm -Rf dgemm

clean_data:
	@rm -Rf data/*

clean_png:
	@rm -Rf *.png
