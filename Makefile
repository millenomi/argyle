BUILD_DIRECTORY = build-Makefile
LIBTOOL = glibtool

# for now, GCC is required to build Platform Core.

SOURCES = $(wildcard IL*.cpp)
OBJECT_FILES = $(patsubst %.cpp,%.o,$(SOURCES))

CXX = g++
AR = ar
RANLIB = ranlib
PLATFORM_STATIC_LIB_SUFFIX = .a
PLATFORM_LIB_PREFIX = lib

PLATFORM = $(shell uname)
include $(PLATFORM).mk

PRODUCT_NAME = PlatformCore-$(PLATFORM)

CXXFLAGS = -g -Os $(PLATFORM_CXXFLAGS)
LDFLAGS = -lpthread $(PLATFORM_LDFLAGS)


STATIC_LIBRARY = $(PLATFORM_LIB_PREFIX)$(PRODUCT_NAME)$(PLATFORM_STATIC_LIB_SUFFIX)
DYNAMIC_LIBRARY = $(PLATFORM_LIB_PREFIX)$(PRODUCT_NAME)$(PLATFORM_DYLIB_SUFFIX)

ifeq ($(PLATFORM_DYLIB_SUFFIX),)
$(warning No dylib suffix specified for this platform; dylibs disabled.)
PLATFORM_SUPPORTS_DYLIBS := NO
endif

ifeq ($(PLATFORM_SUPPORTS_DYLIBS),NO)
LIBRARIES_TO_BUILD = $(STATIC_LIBRARY)
else
LIBRARIES_TO_BUILD = $(STATIC_LIBRARY) $(DYNAMIC_LIBRARY)
endif


all: $(OBJECT_FILES) $(LIBRARIES_TO_BUILD)
.PHONY: clean

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c "$<" -o "$@"

clean:
	-rm *.o
	-rm *.a
	-rmdir .libs
ifneq ($(PLATFORM_SUPPORTS_DYLIBS),NO)
	-test x$(PLATFORM_DYLIB_SUFFIX) != x && rm *$(PLATFORM_DYLIB_SUFFIX)
endif

$(STATIC_LIBRARY): $(OBJECT_FILES)
	$(AR) rcs "$@" $<
	$(RANLIB) "$@"

$(DYNAMIC_LIBRARY): $(OBJECT_FILES)
	$(CXX) -shared $(CXXFLAGS) $(LDFLAGS) $(OBJECT_FILES) -shared -o "$@"
