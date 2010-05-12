
# Must set the GOOGLE_NACL_SDK_TOOLCHAIN setting to the root of the SDK's toolchain directory.

ifeq ($(GOOGLE_NACL_SDK_TOOLCHAIN),)
$(error Set the GOOGLE_NACL_SDK_TOOLCHAIN variable to the root of the Google Native Client SDK's toolchain directory.)
endif

CXX = $(GOOGLE_NACL_SDK_TOOLCHAIN)/bin/nacl64-c++
AR = $(GOOGLE_NACL_SDK_TOOLCHAIN)/bin/nacl64-ar
RANLIB = $(GOOGLE_NACL_SDK_TOOLCHAIN)/bin/nacl64-ranlib

PLATFORM_SUPPORTS_DYLIBS = NO
PLATFORM_LIB_PREFIX = lib

