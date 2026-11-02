# V0 y V2 usan el kernel de v0.c, compilado SIN vectorizar.
# V1 y V3 usan el kernel de v1.c, compilado con -O3 y vectorizacion.
CC      = gcc
BASE    = -std=c11 -march=native -ffp-contract=off -pthread -Wall -Wextra

conv: main.o v0.o v1.o
	$(CC) $(BASE) -O3 main.o v0.o v1.o -o conv

main.o: main.c pgm.h filtros.h
	$(CC) $(BASE) -O3 -c main.c -o main.o

v0.o: v0.c filtros.h
	$(CC) $(BASE) -O2 -fno-tree-vectorize -c v0.c -o v0.o

v1.o: v1.c filtros.h
	$(CC) $(BASE) -O3 -fopt-info-vec -c v1.c -o v1.o

clean:
	rm -f conv *.o
