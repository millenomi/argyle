
# Must set the GOOGLE_NACL_SDK_TOOLCHAIN setting to the root of the SDK's toolchain directory.

CXX = $(GOOGLE_NACL_SDK_TOOLCHAIN)/bin/nacl64-c++
PLATFORM_SUPPORTS_DYLIBS = NO
PLATFORM_LIB_PREFIX = lib
