PLATFORM_DYLIB_SUFFIX = .dylib
PLATFORM_LIB_PREFIX = lib

ifneq ($(DARWIN_FOUR_WAY_UNIVERSAL),NO)
PLATFORM_CXXFLAGS = -arch i386 -arch ppc -arch x86_64
endif