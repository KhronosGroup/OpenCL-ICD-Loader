ifndef QCONFIG
QCONFIG=qconfig.mk
endif
include $(QCONFIG)

define PINFO
PINFO DESCRIPTION = "OpenCL Driver Stub"
endef

ICD_ROOT=$(CURDIR)/../../../../..

EXTRA_INCVPATH+=$(ICD_ROOT)/inc
EXTRA_INCVPATH+=$(ICD_ROOT)/test/inc

EXTRA_SRCVPATH+=$(ICD_ROOT)/test/driver_stub
EXTRA_SRCVPATH+=$(ICD_ROOT)/test/log

NAME=libOpenCLDriverStub

# Make the library

SRCS = cl.c cl_ext.c cl_gl.c icd.c icd_test_log.c

LDFLAGS += -Wl,--unresolved-symbols=report-all -Wl,--no-undefined -Wl,-fPIC

include $(MKFILES_ROOT)/qtargets.mk

CCFLAGS += -DCL_ENABLE_LAYERS -DCL_TARGET_OPENCL_VERSION=300 -DOpenCLDriverStub_EXPORTS
CCFLAGS += -fPIC -std=gnu99

CXXFLAGS += $(CCFLAGS)

INSTALLDIR=usr/lib
