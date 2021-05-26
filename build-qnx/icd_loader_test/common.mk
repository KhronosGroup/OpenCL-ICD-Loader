ifndef QCONFIG
QCONFIG=qconfig.mk
endif
include $(QCONFIG)

define PINFO
PINFO DESCRIPTION = "ICD Loader Test"
endef

ICD_ROOT=$(CURDIR)/../../../../..

EXTRA_INCVPATH+=$(ICD_ROOT)/inc
EXTRA_INCVPATH+=$(ICD_ROOT)/test/inc

EXTRA_SRCVPATH+=$(ICD_ROOT)/test/loader_test
EXTRA_SRCVPATH+=$(ICD_ROOT)/test/log

NAME=icd_loader_test

# Make the library

SRCS = test_kernel.c main.c test_platforms.c icd_test_match.c test_program_objects.c \
	test_sampler_objects.c test_buffer_object.c test_cl_runtime.c callbacks.c \
	test_create_calls.c test_clgl.c test_image_objects.c icd_test_log.c

include $(MKFILES_ROOT)/qtargets.mk

CCFLAGS += -DCL_ENABLE_LAYERS -DCL_TARGET_OPENCL_VERSION=300
CCFLAGS += -std=gnu99

CXXFLAGS += $(CCFLAGS)

LIBS += OpenCL

INSTALLDIR=usr/bin
