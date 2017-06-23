
MAIN=main
PRJSRC=$(wildcard test_*.c)
LIBS=-lrt -lm -lGL -lGLU -lglut mocks/elf.a mocks/simavr.a -lpthread -ldl
CC=gcc
CLIBSBUILD?=
CFLAGSBUILD?=-O2 
CFLAGS=-c -Wall -I. -I/usr/local/include/simavr/ -g
CFLAGS+=${CFLAGSBUILD}
OBJ=$(PRJSRC:.c=.o) main.o
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
	$(CC) -o $@ ${OBJ} ${OBJECT_UNDER_TEST} ../src/logger.o ${LIBS} ${CLIBSBUILD}

%.o: %.c
	$(CC) ${CFLAGS} -o $@ $<

mock:
	make -C mocks

clean:
	make -C mocks clean
	rm -f build ${MAIN} *.o *.gcda *.gcno
