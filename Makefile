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
TARGET = RobotTriathlon
# sourse files directory
SRCDIR = ./src
# intermediate files directory
OBJDIR = ./bin
# source files
SOURCES = $(addprefix $(SRCDIR)/, $(wildcard *.c))
# object files
OBJECTS = $(addprefix $(OBJDIR)/, $(addsuffix .p1, $(basename $(notdir $(SOURCES)))))
# dependency
DEPENDS = $(OBJECTS:.p1=.d)

# additional suffixes
.SUFFIXES: .p1

$(TARGET): $(OBJECTS) $(LIBS)
	$(CC) $(CFLAGS) -O$@ $(OBJDIR)

# suffix rule(.c -> .p1)
.c.p1:
	$(CC) $(CFLAGS) --PASS1 $<

#main.p1: configurationBits.h
