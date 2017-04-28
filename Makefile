ifndef VERBOSE
.SILENT:
endif


CURRENT_DIR := $(shell pwd)

ifndef PLATFORM
PLATFORM=PIC18F25K80
endif

ifeq ($(PLATFORM),PIC18F25K80)
	CC = xc8
	COMPILE = --pass1
	INCLUDES = -I$(OS_DIR)
	CFLAGS = -DPLATFORM=PIC18F25K80 --chip=18f25k80 --mode=free $(INCLUDES)
	OBJECT_EXTENSION := p1
else
	$(error Platform not set)
endif

OPTIONS = PLATFORM='$(PLATFORM)' CC='$(CC)' COMPILE='$(COMPILE)' CFLAGS='$(CFLAGS)' OBJECT_EXTENSION='$(OBJECT_EXTENSION)'
ifdef VERBOSE
	OPTION += VERBOSE='$(VERBOSE)'
endif

#
APP_DIR := $(CURRENT_DIR)/app 
BUILD_DIR := $(CURRENT_DIR)/build
OS_DIR := $(CURRENT_DIR)/os

OPTIONS += APP_DIR='$(APP_DIR)'
OPTIONS += BUILD_DIR='$(BUILD_DIR)'
OPTIONS += OS_DIR='$(OS_DIR)'

all: build

default:
	mkdir -p $(BUILD_DIR)

os: default
	cd os && make $(OPTIONS)

app: os
	cd app && make $(OPTIONS)

compile: os app

build: compile
	echo Starting Build:
	# Object files
	#BUILD_OBJECTS=$(wildcard **/*.$(OBJECT_EXTENSION))
	$(eval BUILD_OBJECTS := $(shell find . -name '*.$(OBJECT_EXTENSION)') )
	$(CC) $(CFLAGS) --output=+mcof -O./build/build.cof $(BUILD_OBJECTS)	
	echo Finishing Build.

clean:
	rm -rf build

.PHONY: build compile os osek app test clean