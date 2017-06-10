
PROJECTNAME=app
PRJSRC=${PROJECTNAME}.c ac_input.c controller.c model.c view.c
DEPS=$(PRJSRC:.c=.h)
LIBS=-lm -lGL -lGLU -lglut -lelf -lsimavr -lm -lpthread

#######################################

CC=gcc
CFLAGS=-c -Wall -I. -I/usr/local/include/simavr/
CFLAGS+=-O2 -g
OBJ=$(PRJSRC:.c=.o)

run: ${PROJECTNAME}
	./${PROJECTNAME}

%.o: %.c $(DEPS)
	$(CC) ${CFLAGS} -o $@ $<

${PROJECTNAME}: ${OBJ}
	$(CC) -o $@ ${OBJ} ${LIBS}

clean:
	rm -f ${PROJECTNAME} ${OBJ}
