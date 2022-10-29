 CFLAGS=-Wall -g

# OFLAGS= -Ofast -march=native -mtune=native 
OFLAGS= -O0 -march=native -mtune=native 



FILES=main.c 

all:
	$(CC) $(CFLAGS) $(OFLAGS) oneCore.c -o oneCore


clean:
	@rm -Rf oneCore 

clean_data:
	@rm -Rf data/*.dat 
