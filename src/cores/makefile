
PRJSRC=atmega328p.c 

#######################################


CC=gcc
LIBS=-lc
CFLAGS=-fPIC -c -Wall -I. -I/usr/local/include/simavr/ -O2 -g
OBJ=$(PRJSRC:.c=.o)
SO=$(PRJSRC:.c=.so)

-include $(OBJS:.o=.d)

all: ${SO}

%.o: %.c
	$(CC) ${CFLAGS} -o $@ $<
	$(CC) -MM $(CFLAGS) $*.c > $*.d

%.so: %.o
	$(CC) -fPIC -shared ${LIBS} -o $@ $<

clean:
	rm -f ${OBJ} *.so *.d
