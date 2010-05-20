ILABS_PLATFORM_CORE_DIR = /Users/millenomi/Developer/Multiverse/Argyle

TARGET      = infinitelabs-platform-core
HEADERS     +=  $$ILABS_PLATFORM_CORE_DIR/IL*.h
SOURCES     +=  $$ILABS_PLATFORM_CORE_DIR/IL*.cpp
FORMS       += 
LEXSOURCES  += #LEXS#
YACCSOURCES += #YACCS#

INCLUDEPATH += $$ILABS_PLATFORM_CORE_DIR
LIBS        += -lpthread
DEFINES     +=

# All generated files goes same directory
OBJECTS_DIR = build
MOC_DIR     = build
UI_DIR      = build

DESTDIR     = build
TEMPLATE    = lib
DEPENDPATH  +=
VPATH       += $$ILABS_PLATFORM_CORE_DIR
CONFIG      -= qt
CONFIG      += debug
CONFIG      += staticlib dll
#QTMODULES#

INSTALLS    += target
target.path  = /usr/lib/

#
# Targets for debian source and binary package creation
#
debian-src.commands = dpkg-buildpackage -S -r -us -uc -d
debian-bin.commands = dpkg-buildpackage -b -r -uc -d
debian-all.depends = debian-src debian-bin

#
# Clean all but Makefile
#
compiler_clean.commands = -$(DEL_FILE) $(TARGET)

QMAKE_EXTRA_TARGETS += debian-all debian-src debian-bin compiler_clean
