
PROJECTNAME=app
PRJSRC=${PROJECTNAME}.c ac_input.c controller.c model.c view.c
DEPS=$(PRJSRC:.c=.h)
LIBS=-lm -lGL -lGLU -lglut -lelf -lsimavr -lm -lpthread

#######################################

FIRMWARENAME:=$(shell grep -i '^PROJECTNAME=' ../makefile | sed -e 's/PROJECTNAME=//')
FIRMWAREMCU:=$(shell grep -i '^MCU=' ../makefile | sed -e 's/MCU=//')

CC=gcc
CFLAGS=-c -Wall -I. -I/usr/local/include/simavr/
CFLAGS+=-O2 -g
CFLAGS+=-DFIRMWARENAME=${FIRMWARENAME}
CFLAGS+=-DFIRMWAREMCU="${FIRMWAREMCU}"
OBJ=$(PRJSRC:.c=.o)

run: ${PROJECTNAME}
	./${PROJECTNAME}

%.o: %.c $(DEPS)
	$(CC) ${CFLAGS} -o $@ $<

${PROJECTNAME}: ${OBJ}
	$(CC) -o $@ ${OBJ} ${LIBS}

clean:
	rm -f ${PROJECTNAME} ${OBJ}

