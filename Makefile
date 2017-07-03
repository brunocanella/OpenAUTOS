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
	PIC_OPTIONS = -Q -G --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,-space,+debug --addrqual=ignore -P -N255 --warn=-3 --asmlist -DXPRJ_default=default  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=+mcof,+elf:multilocs --stack=compiled:auto:auto:auto
	CFLAGS = -DPLATFORM=PIC18F25K80 --chip=18f25k80 --mode=free $(PIC_OPTIONS) $(INCLUDES)
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
OILER_DIR := $(CURRENT_DIR)/oiler
OS_DIR := $(CURRENT_DIR)/os

OPTIONS += APP_DIR='$(APP_DIR)'
OPTIONS += BUILD_DIR='$(BUILD_DIR)'
OPTIONS += OS_DIR='$(OS_DIR)'

all: build

oiler:
	cd oiler && make

OILER_EXE := $(abspath oiler/oiler)
OIL_FILE := $(abspath $(wildcard app/*.oil))
app: oiler
	#echo $(OILER_EXE)
	cd app && $(OILER_EXE) $(OIL_FILE)
	# Joins all .d files together to form the main.c file in the OS dir.
	echo "#include <openautos.h>\n" | cat - $(OILER_DIR)/*.d $(APP_DIR)/*.d $(OS_DIR)/*.d > $(OS_DIR)/main.c

build_dir:
	mkdir -p $(BUILD_DIR)

os: build_dir
	cd os && make $(OPTIONS) 

compile: app os

build: compile
	echo Starting Build:
	# Object files
	#BUILD_OBJECTS=$(wildcard **/*.$(OBJECT_EXTENSION))
	$(eval BUILD_OBJECTS := $(shell find ./build -name '*.$(OBJECT_EXTENSION)'))
	echo $(BUILD_OBJECTS)
	$(CC) $(CFLAGS) --output=+mcof -m./build/build.map -O./build/build.cof $(BUILD_OBJECTS)	
	echo Finishing Build.

clean:
	rm -rf build

.PHONY: all oiler app build_dir os compile build clean