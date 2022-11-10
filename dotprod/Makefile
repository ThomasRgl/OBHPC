CFLAGS= -Wall

# OFLAGS=-Ofast -march=native -mtune=native
OFLAGS= -O2 -march=native -mtune=native 

INTEL_LFLAGS=-qmkl
GNU_LFLAGS=-lm -lcblas -llapack

FILES=main.c tools.c kernels.c

all: dotprod

dotprod:
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
	@echo "ERROR: no compiler specified using CC. Possible values for CC: gcc, icc, icx, clang or aocc"
endif
endif
endif
endif
endif
endif

clean:
	@rm -Rf dotprod

clean_data:
	@rm -Rf data/*

clean_png:
	@rm -Rf *.png
