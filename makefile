
#
# target "all" for building and testing with standard build options
# target "coverage" for building for "coverage" analysis
#

all: build
	make -C test

coverage: clean build-for-coverage
	make -C test CFLAGSBUILD='-O0 --coverage' CLIBSBUILD='-lgcov'

build-for-coverage:
	make -C src build CFLAGSBUILD='-O0 --coverage' CLIBSBUILD='-lgcov'

build:
	make -C src build

clean:
	make -C src clean
	make -C test clean
