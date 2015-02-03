# commands depend on OS
ifeq ($(OS),Windows_NT)
# /Q option is force remove (no confirmation)
	RM = del /Q
	FixPath = $(subst /,\,$1)
# microchip mdb script file location
	MDB = "C:\Program Files (x86)\Microchip\MPLABX\mplab_ide\bin\mdb.bat"
# TEMP redirect target
	TEMP_TARGET = $(TEMP)\microchip_mdb.log
else
# -f option is force remove (no confirmation)
	RM = rm -f
	FixPath = $1
# microchip mdb script file location
	MDB = /opt/microchip/mplabx/mplab_ide/bin/mdb.sh
# TEMP redirect target
	TEMP_TARGET = /tmp/microchip_mdb.log
endif
# target name
TARGET := release
# compiler command
CC := xc8
# Link options
LDFLAGS := 
# library paths
LIBS := 
# include paths
INCLUDE := include
# sourse files directory
SRCDIR := src
# intermediate files directory
OBJDIR := bin
# compiler options
CFLAGS := --chip=18F26K22 --CCI --outdir=$(OBJDIR) --objdir=$(OBJDIR) -I$(INCLUDE) --asmlist --opt=none --errformat="%f:%l:%c:%n:%s" --warnformat="%f:%l:%c:%n:%s" --msgdisable=1273
# source files
SRCS := $(wildcard $(addprefix $(SRCDIR)/,*.c))
# object files
OBJS := $(addprefix $(OBJDIR)/,$(patsubst %.c,%.p1,$(notdir $(SRCS))))
# dependency
DEPS := $(OBJS:.p1=.d)
# MDB script file
MDB_SCRIPT := ./mdb.prog

# additional suffixes
.SUFFIXES: .p1

$(TARGET): $(OBJS) $(LIBS)
	$(CC) $(CFLAGS) -O$(call FixPath,$@) $(call FixPath,$^)

$(OBJDIR)/%.p1: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) --pass1 $(call FixPath,$<)

.PHONY: all
all: clean $(TARGET)

.PHONY: clean
clean:
# remove intermediate files
	$(RM) $(call FixPath,$(wildcard $(addprefix $(OBJDIR)/,*)))
	$(RM) funclist l.obj

.PHONY: prog
prog: $(TARGET)
# it is nesessary to press Enter for MDB programing(windows MDB bug)
	$(info prease press Enter to program to device!!!)
	@$(MDB) $(call FixPath,$(MDB_SCRIPT)) > $(TEMP_TARGET) 2>&1
# remove unuse intermediate files
	$(RM) MPLABXLog.*

-include $(DEPS)
