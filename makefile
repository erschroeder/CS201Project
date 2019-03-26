# -*- Makefile -*-

collection: movieBST.o da.o main.c
	gcc -o collection movieBST.o da.o main.c
movieBST.o: movieBST.c movieBST.h
	gcc -c movieBST.c
da.o: da.c da.h
	gcc -c da.c
clean:
	rm -f movieBST.o da.o collection
test:
	./collection