
MAIN=main
PRJSRC=$(wildcard test_*.c)
LIBS=-lrt -lm mocks/glut.a mocks/elf.a mocks/simavr.a mocks/pthread.a ../src/ac_input.o -ldl
CC=gcc
CLIBSBUILD?=
CFLAGSBUILD?=-O2 
CFLAGS=-c -Wall -I. -I/usr/local/include/simavr/ -g
CFLAGS+=${CFLAGSBUILD}
OBJ=$(PRJSRC:.c=.o) main.o utils.o
OBJECT_UNDER_TEST=$(PRJSRC:test_%.c=../src/%.o)
ifneq ($(CLIBSBUILD),-lgcov)
	RUN=./build
endif

###############################

all: test

test: build
	ln -nsf ../src/cores cores
	$(RUN)

build: mock ${OBJ} ${MAIN}.o
	$(CC) -o $@ ${OBJ} ${OBJECT_UNDER_TEST} ${LIBS} ${CLIBSBUILD}

%.o: %.c
	$(CC) ${CFLAGS} -o $@ $<

mock:
	make -C mocks

clean:
	make -C mocks clean
	rm -f build ${MAIN} *.o *.gcda *.gcno
