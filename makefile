

all: build
	make -C test

build:
	make -C src build

clean:
	make -C src clean
	make -C test clean
