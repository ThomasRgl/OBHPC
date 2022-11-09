CFLAGS=-Wall 

OFLAGS= -O2 -march=native -mtune=native 

CLANG=/usr/bin/clang
AOCC=/opt/aocc/bin/clang

INTEL_LFLAGS=-qmkl
GNU_LFLAGS=-lm -llapack -lcblas

# FILES=main.c tools.c kernels.c
#FILES=verif.c tools.c kernels.c
# FILES=verif.c tools.c kernels2.c
FILES=main.c tools.c kernels.c

all: dgemm

dgemm:
ifeq ($(CC),icc)
	$(CC) $(CFLAGS) $(OFLAGS) $(FILES) -o $@ $(INTEL_LFLAGS)
else
ifeq ($(CC),icx)
	$(CC) $(CFLAGS) $(OFLAGS) $(FILES) -o $@ $(INTEL_LFLAGS)
else
ifeq ($(CC),gcc)
	$(CC) $(CFLAGS) $(OFLAGS) $(FILES) -o $@ $(GNU_LFLAGS)
else
ifeq ($(CC),icc)
	$(CC) $(CFLAGS) $(OFLAGS) $(FILES) -o $@ $(INTEL_LFLAGS)
else
ifeq ($(CC),aocc)
	$(AOCC) $(CFLAGS) $(OFLAGS) $(FILES) -o $@ $(GNU_LFLAGS)
else
ifeq ($(CC),clang)
	$(CLANG) $(CFLAGS) $(OFLAGS) $(FILES) -o $@ $(GNU_LFLAGS)
else
	@echo "ERROR: no compiler specified using CC. Possible values for CC: gcc, icc, icx, clang"
endif
endif
endif
endif
endif
endif

clean:
	@rm -Rf dgemm

clean_data:
	@rm -Rf data/*

clean_png:
	@rm -Rf *.png
