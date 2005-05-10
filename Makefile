#############################################################################
# Makefile for building: quakemapgen
# Generated by qmake (1.07a) (Qt 3.3.4) on: Mon May  9 22:52:04 2005
# Project:  quakemapgen.pro
# Template: app
# Command: $(QMAKE) -o Makefile quakemapgen.pro
#############################################################################

####### Compiler, tools and options

CC       = gcc
CXX      = g++
LEX      = flex
YACC     = yacc
CFLAGS   = -pipe -Wall -W -g  
CXXFLAGS = -pipe -Wall -W -g  
LEXFLAGS = 
YACCFLAGS= -d
INCPATH  = -I/usr/share/qt3/mkspecs/default -I. -I/usr/include/qt3
LINK     = g++
LFLAGS   = 
LIBS     = $(SUBLIBS) -L/usr/share/qt3/lib -L/usr/X11R6/lib -lqt-mt -lXext -lX11 -lm
AR       = ar cqs
RANLIB   = 
MOC      = /usr/share/qt3/bin/moc
UIC      = /usr/share/qt3/bin/uic
QMAKE    = qmake
TAR      = tar -cf
GZIP     = gzip -9f
COPY     = cp -f
COPY_FILE= $(COPY)
COPY_DIR = $(COPY) -r
INSTALL_FILE= $(COPY_FILE)
INSTALL_DIR = $(COPY_DIR)
DEL_FILE = rm -f
SYMLINK  = ln -sf
DEL_DIR  = rmdir
MOVE     = mv -f
CHK_DIR_EXISTS= test -d
MKDIR    = mkdir -p

####### Output directory

OBJECTS_DIR = ./

####### Files

HEADERS = 
SOURCES = main.cpp \
		world.cpp \
		block.cpp \
		object.cpp \
		stairs.cpp \
		teleport.cpp \
		room.cpp \
		entity.cpp \
		imagetemplateroom.cpp
OBJECTS = main.o \
		world.o \
		block.o \
		object.o \
		stairs.o \
		teleport.o \
		room.o \
		entity.o \
		imagetemplateroom.o
FORMS = 
UICDECLS = 
UICIMPLS = 
SRCMOC   = 
OBJMOC = 
DIST	   = quakemapgen.pro
QMAKE_TARGET = quakemapgen
DESTDIR  = 
TARGET   = quakemapgen

first: all
####### Implicit rules

.SUFFIXES: .c .o .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o $@ $<

####### Build rules

all: Makefile $(TARGET)

$(TARGET):  $(UICDECLS) $(OBJECTS) $(OBJMOC)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJMOC) $(OBJCOMP) $(LIBS)

mocables: $(SRCMOC)
uicables: $(UICDECLS) $(UICIMPLS)

$(MOC): 
	( cd $(QTDIR)/src/moc && $(MAKE) )

Makefile: quakemapgen.pro  /usr/share/qt3/mkspecs/default/qmake.conf 
	$(QMAKE) -o Makefile quakemapgen.pro
qmake: 
	@$(QMAKE) -o Makefile quakemapgen.pro

dist: 
	@mkdir -p .tmp/quakemapgen && $(COPY_FILE) --parents $(SOURCES) $(HEADERS) $(FORMS) $(DIST) .tmp/quakemapgen/ && ( cd `dirname .tmp/quakemapgen` && $(TAR) quakemapgen.tar quakemapgen && $(GZIP) quakemapgen.tar ) && $(MOVE) `dirname .tmp/quakemapgen`/quakemapgen.tar.gz . && $(DEL_FILE) -r .tmp/quakemapgen

mocclean:

uiclean:

yaccclean:
lexclean:
clean:
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) $(TARGET)


FORCE:

####### Compile

main.o: main.cpp world.h \
		entity.h \
		block.h

world.o: world.cpp world.h \
		block.h \
		imagetemplateroom.h \
		stairs.h \
		room.h \
		entity.h \
		object.h

block.o: block.cpp block.h

object.o: object.cpp object.h \
		block.h \
		entity.h

stairs.o: stairs.cpp stairs.h \
		object.h \
		block.h \
		entity.h

teleport.o: teleport.cpp teleport.h \
		room.h \
		object.h \
		block.h \
		entity.h

room.o: room.cpp room.h \
		teleport.h \
		stairs.h \
		object.h \
		block.h \
		entity.h

entity.o: entity.cpp entity.h \
		block.h

imagetemplateroom.o: imagetemplateroom.cpp imagetemplateroom.h \
		teleport.h \
		entity.h \
		object.h \
		block.h

####### Install

install:  

uninstall:  

