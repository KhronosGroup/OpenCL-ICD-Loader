SRC_DIR:=$(dir $(abspath $(lastword $(MAKEFILE_LIST))))
.PHONY: default do_cmake do_build test package
.PHONY: clean clobber

BUILD_DIR?=${SRC_DIR}build
CMAKE_C_COMPILER?=gcc
OPENCL_INCLUDE_DIRS?=${SRC_DIR}inc

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
	${SRC_DIR}

test:
	${MAKE} -C ${BUILD_DIR} test

package: clobber
	rm -f ${PACKAGE_PATH}
	tar -C .. -czf ${PACKAGE_PATH} --exclude .git .gitignore icd
	@echo "Package created at ${PACKAGE_PATH}"

clean:
	${MAKE} -C ${BUILD_DIR} clean

check_clobber_erases_build_dir:
ifeq ($(wildcard ${BUILD_DIR}/CMakeCache.txt),)
	$(warning MakeCache.txt does not exist in the specified BUILD_DIR. You might be \
	pointing to the wrong directory to be cleaned or you have not even built the sources yet.)
	@echo -n "Are you sure to remove ${BUILD_DIR}? [y/N] " && read ans && [ $${ans:-N} = y ]
endif

clobber: check_clobber_erases_build_dir
	rm -rf ${BUILD_DIR}
