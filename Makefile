BUILD_DIRECTORY = build-Makefile
LIBTOOL = glibtool

# for now, GCC is required to build Platform Core.
CXX = g++ # DO NOT CHANGE
CXXFLAGS = -g -Os
LDFLAGS = -lpthread

SOURCES = $(wildcard IL*.cpp)
OBJECT_FILES = $(patsubst %.cpp,%.lo,$(SOURCES))

PRODUCT_NAME = PlatformCore

PLATFORM = $(shell uname)
include $(PLATFORM).mk

STATIC_LIBRARY = $(PLATFORM_LIB_PREFIX)$(PRODUCT_NAME).la
DYNAMIC_LIBRARY = $(PLATFORM_LIB_PREFIX)$(PRODUCT_NAME)$(PLATFORM_DYLIB_SUFFIX)

ifeq ($(PLATFORM_SUPPORTS_DYLIBS),NO)
LIBRARIES_TO_BUILD = $(STATIC_LIBRARY)
else
LIBRARIES_TO_BUILD = $(STATIC_LIBRARY) $(DYNAMIC_LIBRARY)
endif


all: $(OBJECT_FILES) $(LIBRARIES_TO_BUILD)
.PHONY: clean

%.lo: %.cpp
	$(LIBTOOL) --mode=compile --tag=CXX $(CXX) $(CXXFLAGS) -c "$<" -o "$@"

clean:
	-rm *.o
	-rm *.lo
	-rm .libs/*
	-rm *.a
	-rm *.la
	-rmdir .libs
ifneq ($(PLATFORM_SUPPORTS_DYLIBS),NO)
	-test x$(PLATFORM_DYLIB_SUFFIX) != x && rm *$(PLATFORM_DYLIB_SUFFIX)
endif

$(STATIC_LIBRARY): $(OBJECT_FILES)
	$(LIBTOOL) --mode=link --tag=CXX $(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJECT_FILES) -o "$@"

$(DYNAMIC_LIBRARY): $(OBJECT_FILES)
	$(LIBTOOL) --mode=link --tag=CXX $(CXX) -shared $(CXXFLAGS) $(LDFLAGS) $(OBJECT_FILES) -o "$@"
