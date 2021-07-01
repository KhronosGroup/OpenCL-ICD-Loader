ifndef QCONFIG
QCONFIG=qconfig.mk
endif
include $(QCONFIG)

define PINFO
PINFO DESCRIPTION = "OpenCL ICD Loader"
endef

ICD_ROOT=$(CURDIR)/../../../../..

EXTRA_INCVPATH+=$(ICD_ROOT)/build_qnx
EXTRA_INCVPATH+=$(ICD_ROOT)/inc

EXTRA_SRCVPATH+=$(ICD_ROOT)/loader
EXTRA_SRCVPATH+=$(ICD_ROOT)/loader/linux

SO_VERSION=1
NAME=OpenCL

# Make the library

SRCS = icd.c icd_dispatch.c icd_dispatch_generated.c icd_linux.c icd_linux_envvars.c

LDFLAGS += -Wl,--unresolved-symbols=report-all -Wl,--no-undefined -Wl,-fPIC
LDFLAGS += -Wl,--version-script -Wl,$(ICD_ROOT)/loader/linux/icd_exports.map

include $(MKFILES_ROOT)/qtargets.mk

CCFLAGS += -DCL_ENABLE_LAYERS -DCL_TARGET_OPENCL_VERSION=300 -DOpenCL_EXPORTS
CCFLAGS += -fPIC -std=gnu99

CXXFLAGS += $(CCFLAGS)

INSTALLDIR=usr/lib
