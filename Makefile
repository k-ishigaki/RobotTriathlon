# this is a comment
# target name
TARGET = RobotTriathlon
# intermediate files
OBJECTS = $(wildcard *.p1)
# compiler command
COMPILER = xc8
# chip name
CHIP = 18F26K22
# compiler options
CFLAGS += --chip=$(CHIP)
CFLAGS += --CCI
# additional suffixes
.SUFFIXES: .p1

$(TARGET).hex: $(OBJECTS)
	$(COMPILER) $(CFLAGS) -O$@ $(OBJECTS)

# suffix rule(.c -> .p1)
.c.p1:
	$(COMPILER) $(CFLAGS) --PASS1 $<

main.p1: configurationBits.h
