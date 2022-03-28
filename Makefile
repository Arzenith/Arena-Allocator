CC=       	gcc
CFLAGS= 	-g -gdwarf-2 -std=gnu99 -Wall -lmavalloc
CLFLAGS= 	-g -gdwarf-2 -std=gnu99 -Wall 
LDFLAGS=
LIBRARIES=      lib/libmavalloc.a

all:   unit_test 

unit_test: main.o libmavalloc.a
	gcc -o unit_test main.o -L. -lmavalloc

main.o: main.c
	# added -g so that we can use valgrind to check for memory leaks
	gcc -O -c -g main.c 

mavalloc.o: mavalloc.c
	gcc -O -c mavalloc.c

libmavalloc.a: mavalloc.o
	ar rcs libmavalloc.a mavalloc.o

clean:
	rm -f *.o *.a unit_test

.PHONY: all clean
