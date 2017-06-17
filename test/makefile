
MAIN=main
PRJSRC=$(wildcard test_*.c)
LIBS=-lrt -lm -lGL -lGLU -lglut -lelf -lsimavr -lpthread -ldl
CC=gcc
CFLAGS=-c -Wall -I. -I/usr/local/include/simavr/ -O2 -g
OBJ=$(PRJSRC:.c=.o) main.o
OBJECT_UNDER_TEST=$(PRJSRC:test_%.c=../src/%.o)

###############################

all: test

test: build
	./build

build: ${OBJ} ${MAIN}.o
	$(CC) ${OBJ} ${OBJECT_UNDER_TEST} ${LIBS} -o $@

%.o: %.c
	$(CC) ${CFLAGS} -o $@ $<

clean:
	rm -f ${MAIN} *.o