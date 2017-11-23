.PHONY: default do_cmake do_build test package
.PHONY: clean clobber

BUILD_DIR?=build
CMAKE_C_COMPILER?=gcc
OPENCL_INCLUDE_DIRS?=./inc
CURRDIR=$(shell pwd)

ICD_VERSION:=$(shell grep FileVersion OpenCL.rc | sed "s/.*\([0-9]\+\.[0-9]\+\.[0-9]\+.[0-9]\+\).*/\1/")
PACKAGE_PATH:=/tmp/opencl-icd-${ICD_VERSION}.tgz

default: do_build

do_build: do_cmake
	${MAKE} -C ${BUILD_DIR}

do_cmake:
	mkdir -p ${BUILD_DIR} &&                     \
	cd ${BUILD_DIR} &&                           \
	cmake                                        \
	-DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}       \
	-DOPENCL_INCLUDE_DIRS=${OPENCL_INCLUDE_DIRS} \
	${CURRDIR}

test:
	${MAKE} -C ${BUILD_DIR} test

package: clobber
	rm -f ${PACKAGE_PATH}
	tar -C .. -czf ${PACKAGE_PATH} --exclude .git .gitignore icd
	@echo "Package created at ${PACKAGE_PATH}"

clean:
	${MAKE} -C ${BUILD_DIR} clean

clobber:
	rm -rf ${BUILD_DIR}
