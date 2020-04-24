#******************************************************************************
# Copyright (C) 2017 by Alex Fosdick - University of Colorado
#
# Redistribution, modification or use of this software in source or binary
# forms is permitted as long as the files maintain this copyright. Users are 
# permitted to modify this and use it to learn about the field of embedded
# software. Alex Fosdick and the University of Colorado are not liable for any
# misuse of this material. 
#
#*****************************************************************************

#------------------------------------------------------------------------------
# Simple makefile to compile multiple files, link them together and create a 
# final output executable. 
# The make file supports 2 platforms (default platform is HOST):
#   HOST	host environment
#   MSP432	target embedded system
#
# The host embedded system will use the native compiler, gcc. 
# The target embedded system will use the cross compiler, arm-none-eabi-gcc.
#
# Use: make [TARGET] [PLATFORM-OVERRIDES]
#
# Build Targets:
#   <FILE>.i	      	- Builds <FILE>.i preprocessed output of all cfiles
#   <FILE>.asm		- Builds <FILE>.asm assembly output file of c-files
#   <FILE>.o		- Builds <FILE>.o object file for all c-files (not linked)
#   <FILE>.d		- Builds <FILE>.d dependency file for all c-files
#   compile-all		- Compiles all object files, but DOES NOT link
#   build	   	- Builds and links all source files into a final executable	
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
LINKER_FILE = ../msp432p401r.lds

# General Compile Defines
CGFLAGS = -Wall -Werror -g -O0 -std=c99
CPPFLAGS = -E
TARGET = c1m2

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

# Pattern matching
OBJS = $(SOURCES:.c=.o)
DEPS = $(SOURCES:.c=.d)

# Define output files to remove with Clean Target:
FILES = *.i *.asm *.o *.d *.map *.out

# Build Targets
%.i : %.c
	$(CC) $(CFLAGS) $(INCLUDES) $(CPPFLAGS) $^ -o $@  

%.asm : %.c
	$(CC) $(CFLAGS) $(INCLUDES) -S $^ -o $@ 

%.o : %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $^ -o $@

%.d : %.c
	$(CC) $(CFLAGS) $(INCLUDES) -MM $^ -o $@

.PHONY: compile-all
compile-all: $(OBJS)

OBJS: $(SOURCES) $(INCLUDES)
	$(CC) -c $(SOURCES) -o $@ 

.PHONY: build
build: $(TARGET).out $(TARGET).asm

$(TARGET).out: $(OBJS) $(DEPS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(INCLUDES) $(OBJS) -o $@
	$(SIZE) -Atd $@
	$(SIZE) $@

$(TARGET).asm : $(TARGET).out
	$(OBJDUMP) -d $(TARGET).out >> $@

.PHONY: clean
clean: 
	rm -f $(FILES)



