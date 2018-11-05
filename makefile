all: dir.o
	gcc -o dir dir.o
dir.o: dir.c
	gcc -c dir.c
run:
	./dir $(args)
clean:
	rm -f dir *o
