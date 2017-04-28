ifndef VERBOSE
.SILENT:
endif

ifndef BUILD_DIR
$(error Build directory not set)
endif

ifndef OS_DIR
$(error OS directory not set)
endif

ifndef PLATFORM
$(error Platform not set)
endif

ifeq ($(PLATFORM),PIC18F25K80)
CC = xc8
COMPILE = --pass1
INCLUDES = -I$(OS_DIR)
CFLAGS = -DPLATFORM=PIC18F25K80 --chip=18f25k80 --mode=free $(INCLUDES)
OBJECT_EXTENSION=p1

%.$(OBJECT_EXTENSION): %.c
	echo Compiling $< ...
	$(CC) $(COMPILE) $(CFLAGS) --outdir=$(BUILD_DIR) $<
else
$(error Platform set is not supported)
endif

# C files
SOURCES=$(wildcard *.c)
# Object files
OBJECTS=$(SOURCES:.c=.$(OBJECT_EXTENSION))

all: compile

default:
	mkdir -p $(BUILD_DIR)

compile: msg_begin app msg_end

msg_begin:
	echo Compiling OS...

msg_end:
	echo Compiling OS OK!

app: default $(OBJECTS)

test:
	echo PLATFORM=$(PLATFORM)
	echo CFLAGS=$(CFLAGS)