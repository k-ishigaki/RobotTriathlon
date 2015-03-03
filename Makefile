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

# processor name
PROSESSOR_NAME := 18F26K22
# include paths
INCLUDE_DIRS := hardware/include apps/include
# sourse files directory
SRC_DIRS := hardware/src apps/src
# compiler command
CC := xc8
# compiler options
CFLAGS := --chip=$(PROSESSOR_NAME) \
	--CCI $(addprefix -I,$(INCLUDE_DIRS)) \
	--stack=hybrid --asmlist --opt=all \
	--errformat="%f:%l:%c:%n:%s" --warnformat="%f:%l:%c:%n:%s" --msgdisable=1273
# target directory
TARGET_DIR := bin
# target file
TARGET := $(TARGET_DIR)/release.hex
# Link options
LDFLAGS := 
# library paths
LIBS := 
# source files
SRCS := $(foreach src_dir,$(SRC_DIRS),$(wildcard $(addprefix $(src_dir)/,*.c)))
# object files
OBJS := $(addprefix $(TARGET_DIR)/,$(SRCS:%.c=%.p1))
# intermediate files directory
OBJ_DIRS := $(dir $(OBJS))
# dependency
DEPS := $(OBJS:%.p1=%.d)
# MDB script file
MDB_SCRIPT := ./mdb.prog

# additional suffixes
.SUFFIXES: .p1

$(TARGET): $(OBJS) $(LIBS)
	$(CC) $(CFLAGS) --outdir=$(TARGET_DIR) -O$(call FixPath,$@) $(call FixPath,$^)

$(TARGET_DIR)/%.p1:%.c
	$(CC) $(CFLAGS) --outdir=$(call FixPath,$(@D)) --pass1 $(call FixPath,$<)

.PHONY: all
all: clean $(TARGET)

.PHONY: clean
clean:
# remove intermediate files
	$(RM) $(call FixPath,$(OBJS))
	$(RM) $(call FixPath,$(DEPS))
	$(RM) $(call FixPath,$(OBJS:%.p1=%.pre))
	$(RM) $(call FixPath,bin/release.*)
	$(RM) $(call FixPath,bin/startup.*)
	$(RM) $(call FixPath,bin/doprnt.*)
	$(RM) $(call FixPath,MPLABXLog.*)
	$(RM) funclist l.obj

.PHONY: prog
prog: $(TARGET)
# it is nesessary to press Enter for MDB programing(windows MDB bug)
	$(info prease press Enter to program to device!!!)
	@$(MDB) $(call FixPath,$(MDB_SCRIPT)) > $(TEMP_TARGET) 2>&1
# remove unuse intermediate files
	$(RM) MPLABXLog.*

-include $(DEPS)
