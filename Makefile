BUILD_DIRECTORY = build-Makefile
LIBTOOL = glibtool

# for now, GCC is required to build Platform Core.
CXX = g++ # DO NOT CHANGE
CXXFLAGS = -g -Os
LDFLAGS = -lpthread

SOURCES = $(wildcard IL*.cpp)
OBJECT_FILES = $(patsubst %.cpp,%.lo,$(SOURCES))

PRODUCT_NAME = PlatformCore

include $(shell uname).mk

STATIC_LIBRARY = $(PLATFORM_LIB_PREFIX)$(PRODUCT_NAME).la
DYNAMIC_LIBRARY = $(PLATFORM_LIB_PREFIX)$(PRODUCT_NAME)$(PLATFORM_DYLIB_SUFFIX)

all: $(OBJECT_FILES) $(STATIC_LIBRARY) $(DYNAMIC_LIBRARY)
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
	-test x$(PLATFORM_DYLIB_SUFFIX) != x && rm *$(PLATFORM_DYLIB_SUFFIX)

$(STATIC_LIBRARY): $(OBJECT_FILES)
	$(LIBTOOL) --mode=link --tag=CXX $(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJECT_FILES) -o "$@"

$(DYNAMIC_LIBRARY): $(OBJECT_FILES)
	$(LIBTOOL) --mode=link --tag=CXX $(CXX) -shared $(CXXFLAGS) $(LDFLAGS) $(OBJECT_FILES) -o "$@"
