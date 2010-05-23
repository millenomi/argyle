
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
# OBJECT_FILES = $(addprefix $(INTERMEDIATE_PRODUCTS_DIR)/,$(patsubst %.cpp,%.o,$(SOURCES)))

CXX = g++
AR = ar
RANLIB = ranlib
PLATFORM_STATIC_LIB_SUFFIX = .a
PLATFORM_LIB_PREFIX = lib
PLATFORM_PTHREAD_LINK_FLAG = -lpthread
PRODUCT_NAME = PlatformCore-$(PLATFORM_NAME)

PLATFORM = $(shell uname).mk
PLATFORM_NAME = $(patsubst %.mk,%,$(PLATFORM))
ifneq ($(PLATFORM),None)
include ../$(PLATFORM)
endif

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

TestTest-$(PLATFORM_NAME): $(ARGYLE_SOURCES) $(SOURCES) Executable/main-TestTest.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -I$(ARGYLE) -I. $(ARGYLE_SOURCES) $(SOURCES) Executable/main-TestTest.cpp -o "$@"

clean-TestTest-$(PLATFORM_NAME):
	-rm "TestTest-$(PLATFORM_NAME)"

run-TestTest-$(PLATFORM_NAME): TestTest-$(PLATFORM_NAME)
	"./$<"

all: TestTest-$(PLATFORM_NAME)
clean: clean-TestTest-$(PLATFORM_NAME)
run: run-TestTest-$(PLATFORM_NAME)
test: run

.PHONY: all test clean clean-TestTest-$(PLATFORM_NAME) run run-TestTest-$(PLATFORM_NAME)
