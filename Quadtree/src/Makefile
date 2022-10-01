CC=gcc

src/build: main.c bmp.o quadtree.o
	$(CC) -o ../output main.c bmp.o quadtree.o -lm

src/bmp.o: bmp.c
	$(CC) -O -Wall -c bmp.c -lm

src/quadtree.o: quadtree.c
	$(CC) -O -Wall -c quadtree.c -lm

clean:
	rm bmp.o quadtree.o ../output
