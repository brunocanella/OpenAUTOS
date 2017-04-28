ifndef VERBOSE
.SILENT:
endif

ifeq ($(PLATFORM),PIC18F25K80)
else
$(error Platform not set)
endif

ifndef BUILD_DIR
$(error Build directory not set)
endif

SOURCES=$(wildcard *.c)
OBJECTS=$(SOURCES:.c=.p1)

all: compile

default:	
	mkdir -p $(BUILD_DIR)

%.p1: %.c
	echo Compiling $< ...
	$(CC) $(COMPILE) $(CFLAGS) --outdir=$(BUILD_DIR) $<

compile: default $(OBJECTS)
