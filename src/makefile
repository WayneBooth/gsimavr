
PROJECTNAME=app
PRJSRC=$(wildcard *.c)
LIBS=-lm -lGL -lGLU -lglut -lelf -lsimavr -lpthread -ldl

#######################################

FIRMWARENAME:=$(shell grep -i '^PROJECTNAME=' ../makefile | sed -e 's/PROJECTNAME=//')
FIRMWAREMCU:=$(shell grep -i '^MCU=' ../makefile | sed -e 's/MCU=//')

CC=gcc
CLIBSBUILD?= 
CFLAGSBUILD?=-O2 
CFLAGS=-c -Wall -Wunreachable-code -I. -I/usr/local/include/simavr/ -g
CFLAGS+=${CFLAGSBUILD}
CFLAGS+=-DFIRMWARENAME=${FIRMWARENAME}
CFLAGS+=-DFIRMWAREMCU="${FIRMWAREMCU}"
OBJ=$(PRJSRC:.c=.o)

-include $(OBJS:.o=.d)

all: build
	./${PROJECTNAME}

build: ${PROJECTNAME}

%.o: %.c
	$(CC) ${CFLAGS} -o $@ $<
	$(CC) -MM $(CFLAGS) $*.c > $*.d

${PROJECTNAME}: core ${OBJ}
	$(CC) -o $@ ${OBJ} ${LIBS} ${CLIBSBUILD}

core:
	export CFLAGSBUILD='${CFLAGSBUILD}'
	make -C cores

clean:
	rm -f ${PROJECTNAME} ${OBJ} *.d *.gcda *.gcno
	make -C cores clean
