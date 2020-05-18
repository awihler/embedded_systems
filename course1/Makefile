#******************************************************************************
# Copyright (C) 2020 by Andrew Wihler
#
# Redistribution, modification or use of this software in source or binary
# forms is permitted as long as the files maintain this copyright. Users are 
# permitted to modify this and use it to learn about the field of embedded
# software. Andrew Wihler is not liable for any misuse of this material. 
#
#*****************************************************************************

#------------------------------------------------------------------------------
# Simple Makefile to compile multiple files, link them together and create a 
# final output executable.
# 
# The make file supports 2 platforms (default platform is HOST):
#   HOST	host environment
#   MSP432	target embedded system
#
# The host embedded system will use the native compiler, gcc. 
# The target embedded system will use the cross compiler, arm-none-eabi-gcc.
#
# Use: make [TARGET] [PLATFORM-OVERRIDES] [VERBOSE] [COURSE1]
#
# Build Targets:
#   build	   	- Builds and links all source files into a final executable
#			- Builds an objective directory if not already existing	
#   clean 	   	- Removes all generated files      
#
# Platform Overrides:
#   CPU		- ARM Cortex Architecture (cortex-m0plus, cortex-m4)
#   ARCH	- ARM Architecture (arm, thumb)
#   SPECS	- Specs file to give the linker (nosys.specs, nano.specs)
#
#------------------------------------------------------------------------------

# Include other make files
include sources.mk

# Platform Overrides
PLATFORM=HOST

# Architecture Specific Flags
CPU = cortex-m4
INSTR = thumb
ARCH = armv7e-m
ABI = hard
FPU = fpv4-sp-d16
SPECS = nosys.specs
LINKER_FILE = msp432p401r.lds

# General Compile Defines
CGFLAGS = -Wall -Werror -O0 -std=c99 -D$(VERBOSE) -D$(COURSE1)
CPPFLAGS = -E

TARGET = course1_final

# Compiler Flags and Defines
ifeq ($(PLATFORM), MSP432)

	# Compile Flags
	ARCHFLAGS = -mcpu=$(CPU) \
		    -m$(INSTR) \
		    -march=$(ARCH) \
		    -mfloat-abi=$(ABI) \
		    -mfpu=$(FPU) \
		    --specs=$(SPECS)


	# Compile Defines
	CC = arm-none-eabi-gcc
	CFLAGS = $(CGFLAGS) -D$(PLATFORM) $(ARCHFLAGS)
	LDFLAGS = -Wl,-Map=$(TARGET).map -T $(LINKER_FILE)
	OBJDUMP = arm-none-eabi-objdump
	SIZE = arm-none-eabi-size

else
	# Compiler Defines	
	CC = gcc
	CFLAGS = $(CGFLAGS) -D$(PLATFORM)
	LDFLAGS = -Wl,-Map=$(TARGET).map
	OBJDUMP = objdump
	SIZE=size
	
endif

# Define Source and Object File Directories
SRC_DIR := src
OBJ_DIR := obj

# Pattern matching
OBJ := $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Print to screen
$(info SOURCES="$(SOURCES)")
$(info OBJ="$(OBJ)")

# Build Targets
.PHONY: all clean

build: $(TARGET).out

$(TARGET).out: $(OBJ)
	$(CC) $(LDFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(INCLUDES) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir $@

clean:
	$(RM) $(OBJ) *.map *.out



