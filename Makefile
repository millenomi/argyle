BUILD_DIRECTORY = build-Makefile

# for now, GCC is required to build Platform Core.

BUILT_PRODUCTS_DIR = .
ifeq ($(BUILT_PRODUCTS_DIR),)
	$(error Built products dir is empty; use '.' for the sources directory.)
endif

INTERMEDIATE_PRODUCTS_DIR = .
ifeq ($(INTERMEDIATE_PRODUCTS_DIR),)
	$(error Intermediate products dir is empty; use '.' for the sources directory.)
endif

SOURCES = $(wildcard IL*.cpp)
OBJECT_FILES = $(addprefix $(INTERMEDIATE_PRODUCTS_DIR)/,$(patsubst %.cpp,%.o,$(SOURCES)))

CXX = g++
AR = ar
RANLIB = ranlib
PLATFORM_STATIC_LIB_SUFFIX = .a
PLATFORM_LIB_PREFIX = lib

PLATFORM = $(shell uname).mk
PLATFORM_NAME = $(patsubst %.mk,%,$(PLATFORM))
include $(PLATFORM)

PRODUCT_NAME = PlatformCore-$(PLATFORM_NAME)

CXXFLAGS = -g -Os $(PLATFORM_CXXFLAGS)
LDFLAGS = -lpthread $(PLATFORM_LDFLAGS)


STATIC_LIBRARY = $(BUILT_PRODUCTS_DIR)/$(PLATFORM_LIB_PREFIX)$(PRODUCT_NAME)$(PLATFORM_STATIC_LIB_SUFFIX)
DYNAMIC_LIBRARY = $(BUILT_PRODUCTS_DIR)/$(PLATFORM_LIB_PREFIX)$(PRODUCT_NAME)$(PLATFORM_DYLIB_SUFFIX)

ifeq ($(PLATFORM_DYLIB_SUFFIX),)
ifneq ($(PLATFORM_SUPPORTS_DYLIBS),NO)
$(warning warning: No dylib suffix specified for this platform; dylibs disabled.)
PLATFORM_SUPPORTS_DYLIBS := NO
endif
endif

ifeq ($(PLATFORM_SUPPORTS_DYLIBS),NO)
LIBRARIES_TO_BUILD = $(STATIC_LIBRARY)
else
LIBRARIES_TO_BUILD = $(STATIC_LIBRARY) $(DYNAMIC_LIBRARY)
endif


all: $(OBJECT_FILES) $(LIBRARIES_TO_BUILD)
.PHONY: clean

$(INTERMEDIATE_PRODUCTS_DIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c "$<" -o "$@"

clean:
	-rm $(INTERMEDIATE_PRODUCTS_DIR)/*.o
	-rm $(BUILT_PRODUCTS_DIR)/*.a
	-rmdir .libs
ifneq ($(PLATFORM_SUPPORTS_DYLIBS),NO)
	-test x$(PLATFORM_DYLIB_SUFFIX) != x && rm $(BUILT_PRODUCTS_DIR)/*$(PLATFORM_DYLIB_SUFFIX)
endif

$(STATIC_LIBRARY): $(OBJECT_FILES)
	$(AR) rcs "$@" $(OBJECT_FILES)
	$(RANLIB) "$@"

$(DYNAMIC_LIBRARY): $(OBJECT_FILES)
	$(CXX) -shared $(CXXFLAGS) $(LDFLAGS) $(OBJECT_FILES) -shared -o "$@"
