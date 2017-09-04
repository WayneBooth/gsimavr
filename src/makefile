
PROJECTNAME=app
PRJSRC=$(wildcard *.c)
LIBS=-lm -lGL -lGLU -lglut -lelf -lsimavr -lpthread -ldl

#######################################
FIRMWAREDIR?=$(shell /usr/bin/realpath -s ${CURDIR}/.. )
FIRMWARENAME:=$(shell grep -i '^PROJECTNAME=' ${FIRMWAREDIR}/makefile | sed -e 's/PROJECTNAME=//')
FIRMWAREMCU:=$(shell grep -i '^MCU=' ${FIRMWAREDIR}/makefile | sed -e 's/MCU=//')

CC=gcc
CLIBSBUILD?= 
CFLAGSBUILD?=-O2 
CFLAGS=-c -Wall -Wunreachable-code -I. -I/usr/local/include/simavr/ -g
CFLAGS+=${CFLAGSBUILD}
CFLAGS+=-DFIRMWARENAME=${FIRMWARENAME}
CFLAGS+=-DFIRMWAREMCU="${FIRMWAREMCU}"
CFLAGS+=-DFIRMWAREDIR=${FIRMWAREDIR}
OBJ=$(PRJSRC:.c=.o)

-include $(OBJS:.o=.d)

all: build
	./${PROJECTNAME}

build: ${PROJECTNAME}

%.o: %.c
ifndef FIRMWARENAME
	@echo "######################################################################\n\n   \
	Could not determine the firmware to build against.\n   \
	Make sure the gsimavr src is in a (non symlinked) directory, parented by your firmware.\n   \
	Or, provide the "FIRMWAREDIR=/path/to/firmware" parameter to the make command.\n\n\
	######################################################################"
	exit 1
endif
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
