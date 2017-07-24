
#
# target "all" for building and testing with standard build options
# target "coverage" for building for "coverage" analysis
#
PROJECTNAME=dummy
MCU=dummy

all: build
	make -C test

coverage: clean build-for-coverage
	make -C test CFLAGSBUILD='-O0 --coverage' CLIBSBUILD='-lgcov'

build-for-coverage:
	make -C src build CFLAGSBUILD='-O0 --coverage' CLIBSBUILD='-lgcov'
	lcov --directory . --zerocounters

build:
	make -C src build

run-coverage: coverage
	cd test ; ./build ; cd ./
	lcov --directory . --capture --output-file coverage.info
	lcov --remove coverage.info 'test/*' '/usr/*' --output-file coverage.info
	mkdir -p cov
	genhtml -o cov coverage.info

clean:
	rm -f coverage.info
	rm -rf cov
	make -C src clean
	make -C test clean
	make -C example clean
