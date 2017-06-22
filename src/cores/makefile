
PRJSRC=$(wildcard *.c)

#######################################


CC=gcc
LIBS=-lc
CLIBSBUILD?=
CFLAGSBUILD?=-O2
CFLAGS=-fPIC -c -Wall -I. -I/usr/local/include/simavr/ -g
CFLAGS+=${CFLAGSBUILD}
OBJ=$(PRJSRC:.c=.o)
SO=$(PRJSRC:.c=.so)

-include $(OBJS:.o=.d)

all: ${SO}

%.o: %.c
	$(CC) ${CFLAGS} -o $@ $<
	$(CC) -MM $(CFLAGS) $*.c > $*.d

%.so: %.o
	$(CC) -fPIC -shared -o $@ $< ${LIBS} ${CLIBSBUILD}

clean:
	rm -f ${OBJ} *.so *.d *.gcda *.gcno
