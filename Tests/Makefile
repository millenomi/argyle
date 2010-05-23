
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
PLATFORM_PTHREAD_LINK_FLAG = -lpthread
PRODUCT_NAME = PlatformCore-$(PLATFORM_NAME)

PLATFORM = $(shell uname).mk
PLATFORM_NAME = $(patsubst %.mk,%,$(PLATFORM))
include ../$(PLATFORM)

CXXFLAGS = -g -Os $(PLATFORM_CXXFLAGS)
LDFLAGS = $(PLATFORM_PTHREAD_LINK_FLAG) $(PLATFORM_LDFLAGS)

ifeq ($(PLATFORM_DYLIB_SUFFIX),)
ifneq ($(PLATFORM_SUPPORTS_DYLIBS),NO)
$(warning warning: No dylib suffix specified for this platform; dylibs disabled.)
PLATFORM_SUPPORTS_DYLIBS := NO
endif
endif

ARGYLE = ..

ARGYLE_SOURCES = $(wildcard $(ARGYLE)/IL*.cpp)

main-TestTest-$(PLATFORM_NAME): $(ARGYLE_SOURCES) $(SOURCES) Executable/main-TestTest.cpp
	$(CXX) -I$(ARGYLE) -I. $(ARGYLE_SOURCES) $(SOURCES) Executable/main-TestTest.cpp -o "$@"

clean-main-TestTest-$(PLATFORM_NAME):
	-rm "main-TestTest-$(PLATFORM_NAME)"

run-main-TestTest-$(PLATFORM_NAME): main-TestTest-$(PLATFORM_NAME)
	"./$<"

all: main-TestTest-$(PLATFORM_NAME)
clean: clean-main-TestTest-$(PLATFORM_NAME)
run: run-main-TestTest-$(PLATFORM_NAME)

.PHONY: all clean clean-main-TestTest-$(PLATFORM_NAME) run run-main-TestTest-$(PLATFORM_NAME)
