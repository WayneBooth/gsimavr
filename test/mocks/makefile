
PRJSRC=$(wildcard *.c)
CC=gcc
CFLAGSBUILD?=-O2 
CFLAGS=-c -Wall -I. -I/usr/local/include/simavr/ -g
CFLAGS+=${CFLAGSBUILD}
LIBS=$(PRJSRC:.c=.a) 

###############################

all: ${LIBS}

%.a: %.o
	ar rcs $@ $^

%.o: %.c
	$(CC) ${CFLAGS} -o $@ $<

clean:
	rm -f *.a *.o *.gcda *.gcno
