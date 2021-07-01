ifndef QCONFIG
QCONFIG=qconfig.mk
endif
include $(QCONFIG)

define PINFO
PINFO DESCRIPTION = "OpenCL Layer Print Test"
endef

ICD_ROOT=$(CURDIR)/../../../../..

EXTRA_INCVPATH+=$(ICD_ROOT)/inc
#EXTRA_INCVPATH+=$(ICD_ROOT)/test/inc

EXTRA_SRCVPATH+=$(ICD_ROOT)/test/layer
#EXTRA_SRCVPATH+=$(ICD_ROOT)/test/log

NAME=libPrintLayer

# Make the library

SRCS = icd_print_layer.c icd_print_layer_generated.c

LDFLAGS += -Wl,--unresolved-symbols=report-all -Wl,--no-undefined -Wl,-fPIC
LDFLAGS += -Wl,--version-script -Wl,$(ICD_ROOT)/test/layer/icd_print_layer.map
LDFLAGS += -fvisibility=default

include $(MKFILES_ROOT)/qtargets.mk

CCFLAGS += -DCL_ENABLE_LAYERS -DCL_TARGET_OPENCL_VERSION=300 -DPrintLayer_EXPORTS
CCFLAGS += -fPIC -std=gnu99

CXXFLAGS += $(CCFLAGS)

INSTALLDIR=usr/lib
