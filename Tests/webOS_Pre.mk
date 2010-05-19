PALM_WEBOS_PDK = /opt/PalmPDK

PLATFORM_DYLIB_SUFFIX = .so
PLATFORM_LIB_PREFIX = lib

PLATFORM_CXXFLAGS = -I$(PALM_WEBOS_PDK)/include -mcpu=cortex-a8 -mfpu=neon -mfloat-abi=softfp -I$(PALM_WEBOS_PDK)/include/SDL --sysroot=$(PALM_WEBOS_PDK)/arm-gcc/sysroot -L$(PALM_WEBOS_PDK)/device/lib -Wl,--allow-shlib-undefined -lSDL -lGLESv2

CXX = $(PALM_WEBOS_PDK)/arm-gcc/bin/arm-none-linux-gnueabi-g++
AR = $(PALM_WEBOS_PDK)/arm-gcc/bin/arm-none-linux-gnueabi-ar
RANLIB = $(PALM_WEBOS_PDK)/arm-gcc/bin/arm-none-linux-gnueabi-ranlib
