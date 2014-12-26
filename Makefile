# Environment 
ifeq (\$(OS),Windows_NT)
	MKDIR = mkdir
	CP = move
	BASENAME = 
else
	MKDIR = mkdir
	CP = cp
	BASENAME = basename
endif
#CCADMIN=CCadmin	# I don't know what this means
#RANLIB = ranlib	# I don't know what this means
# compiler command
CC = xc8
# compiler options
CFLAGS = --chip=18F26K22 --CCI
# Link options
LDFLAGS = 
# library paths
LIBS = 
# include paths
INCLUDE = 
# target name
TARGET = ../bin/$(shell basename 'readlink -f ..')
# intermediate files directory
OBJDIR = ./bin
ifeq "$(strip (OBJDIR))" ""
  OBJDIR = .
endif
# source files
SOURCES = $(wildcard *.c)
# object files
OBJECTS = $(addprefix $(OBJDIR)/, $(SOURCES:.c=.p1))
# dependency
DEPENDS = $(OBJECTS:.p1=.d)

# additional suffixes
.SUFFIXES: .p1

$(TARGET): $(OBJECTS) $(LIBS)
	$(COMPILER) $(CFLAGS) -O$@ $(OBJDIR)

# suffix rule(.c -> .p1)
.c.p1:
	$(COMPILER) $(CFLAGS) --PASS1 $<

main.p1: configurationBits.h
