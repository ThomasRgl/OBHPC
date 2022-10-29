 CFLAGS=-Wall -g

# OFLAGS= -Ofast -march=native -mtune=native 
OFLAGS= -O0 -march=native -mtune=native 



FILES=main.c 

all:
	$(CC) $(CFLAGS) $(OFLAGS) oneCore.c -o oneCore
	$(CC) $(CFLAGS) $(OFLAGS) multiCore.c -o multiCore


clean:
	@rm -Rf oneCore multiCore 

clean_data:
	@rm -Rf data/*.dat

clean_png:
	@rm -Rf *.png
