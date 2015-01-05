# target name
TARGET = release
# compiler command
CC := xc8
# compiler options
CFLAGS = --chip=18F26K22 --CCI --outdir=$(OBJDIR) --objdir=$(OBJDIR) -I$(INCLUDE) --asmlist --opt=none
# Link options
LDFLAGS = 
# library paths
LIBS = 
# include paths
INCLUDE := include
# sourse files directory
SRCDIR := src
# intermediate files directory
OBJDIR := bin
# source files
SRCS := $(wildcard $(addprefix $(SRCDIR)/,*.c))
# object files
OBJS := $(addprefix $(OBJDIR)/,$(patsubst %.c,%.p1,$(notdir $(SRCS))))
# dependency
DEPS := $(addprefix $(OBJDIR)/,$(patsubst %.c,%.d,$(notdir $(SRCS))))

# additional suffixes
.SUFFIXES: .p1

all:$(TARGET)

-include $(DEPS)

$(TARGET): $(OBJS) $(LIBS)
	$(CC) $(CFLAGS) -O$@ $^

$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) --pass1 $(SRCS)

.PHONY: debug
debug:
	echo $(addprefix $(OBJDIR)/,$(patsubst %.c,%.d,$(notdir $(SRCS))))

.PHONY: clean
clean:
	rm -f $(wildcard $(addprefix $(OBJDIR)/,*))


