# commands depend on OS
ifeq ($(OS),Windows_NT)
	RM = del /Q
# windows separator "\" is defined only in this way
	FixPath = $(subst /,\,$1)
else
# -f option is force remove (no confirmation)
	RM = rm -f
	FixPath = $1
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
CFLAGS := --chip=18F26K22 --CCI --outdir=$(OBJDIR) --objdir=$(OBJDIR) -I$(INCLUDE) --asmlist --opt=none
# source files
SRCS := $(wildcard $(addprefix $(SRCDIR)/,*.c))
# object files
OBJS := $(addprefix $(OBJDIR)/,$(patsubst %.c,%.p1,$(notdir $(SRCS))))
# dependency
DEPS := $(OBJS:.p1=.d)

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
	$(RM) $(call FixPath,$(wildcard $(addprefix $(OBJDIR)/,*)))

-include $(DEPS)
