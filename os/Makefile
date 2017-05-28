ifndef VERBOSE
.SILENT:
endif

ifndef BUILD_DIR
$(error Build directory not set)
endif

ifeq ($(PLATFORM),PIC18F25K80)
%.$(OBJECT_EXTENSION): %.c
	echo Compiling $< ...
	$(CC) $(COMPILE) $(CFLAGS) --outdir=$(BUILD_DIR) $<
else
$(error Platform not set)
endif

# C files
SOURCES=$(wildcard *.c)
# Object files
OBJECTS=$(SOURCES:.c=.$(OBJECT_EXTENSION))

# Generate OPTIONS to send to sub builds
OPTIONS = PLATFORM='$(PLATFORM)' CC='$(CC)' COMPILE='$(COMPILE)' CFLAGS='$(CFLAGS)' OBJECT_EXTENSION='$(OBJECT_EXTENSION)'
ifdef VERBOSE
	OPTION += VERBOSE='$(VERBOSE)'
endif
OPTIONS += APP_DIR='$(APP_DIR)'
OPTIONS += BUILD_DIR='$(BUILD_DIR)'
OPTIONS += OS_DIR='$(OS_DIR)'

all: compile

default:
	mkdir -p $(BUILD_DIR)

compile: msg_begin os osek $(PLATFORM) msg_end

msg_begin:
	echo Compiling OS...

msg_end:
	echo Compiling OS OK!

os: default $(OBJECTS)

osek: default
	cd ./osek && make $(OPTIONS)

PIC18F25K80: default
	echo Compiling Platform...
	cd ./platform/pic18f25k80 && make CC=$(CC) COMPILE='$(COMPILE)' CFLAGS='$(CFLAGS)' PLATFORM=$(PLATFORM) BUILD_DIR=$(BUILD_DIR)/platform VERBOSE=$(VERBOSE)	
	echo Compiling Platform OK!

.PHONY: all compile os osek PIC18F25K80