
PROJECTNAME=app
PRJSRC=${PROJECTNAME}.c ac_input.c controller.c model.c view.c
LIBS=-lm -lGL -lGLU -lglut -lelf -lsimavr -lm -lpthread -ldl

#######################################

FIRMWARENAME:=$(shell grep -i '^PROJECTNAME=' ../makefile | sed -e 's/PROJECTNAME=//')
FIRMWAREMCU:=$(shell grep -i '^MCU=' ../makefile | sed -e 's/MCU=//')

CC=gcc
CFLAGS=-c -Wall -I. -I/usr/local/include/simavr/
CFLAGS+=-O2 -g
CFLAGS+=-DFIRMWARENAME=${FIRMWARENAME}
CFLAGS+=-DFIRMWAREMCU="${FIRMWAREMCU}"
OBJ=$(PRJSRC:.c=.o)

-include $(OBJS:.o=.d)

run: core ${PROJECTNAME}
	./${PROJECTNAME}

%.o: %.c
	$(CC) ${CFLAGS} -o $@ $<
	$(CC) -MM $(CFLAGS) $*.c > $*.d

${PROJECTNAME}: ${OBJ}
	$(CC) -o $@ ${OBJ} ${LIBS}

core:
	echo MAKING CORES
	make -C cores

clean:
	rm -f ${PROJECTNAME} ${OBJ} *.d
	make -C cores clean
