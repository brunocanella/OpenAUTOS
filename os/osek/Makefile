ifndef VERBOSE
.SILENT:
endif

ifndef BUILD_DIR
$(error Build directory not set)
endif

ifeq ($(PLATFORM),PIC18F25K80)
%.$(OBJECT_EXTENSION): %.c
	echo Compiling $< ...
	$(CC) $(COMPILE) $(CFLAGS) --outdir=$(BUILD_DIR)/os $<
else
$(error Platform not set)
endif

# C files
SOURCES=$(wildcard *.c)
# Object files
OBJECTS=$(SOURCES:.c=.$(OBJECT_EXTENSION))

all: compile

default:
	mkdir -p $(BUILD_DIR)/os

compile: msg_begin osek msg_end

msg_begin:
	echo Compiling OSEK/VDX...

msg_end:
	echo Compiling OSEK/VDX OK!

osek: default $(OBJECTS)

