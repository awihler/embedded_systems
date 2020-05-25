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
# Use: make build [PLATFORM] [VERBOSE] [COURSE1]
#
# Build Targets:
#   build	- Builds and links all source files into a final executable
#			- Builds output file directories if not already existing	
#   clean	- Removes all generated files      
#
# Platform Overrides:
#   CPU		- ARM Cortex Architecture (cortex-m0plus, cortex-m4)
#   ARCH	- ARM Architecture (arm, thumb)
#   SPECS	- Specs file to give the linker (nosys.specs, nano.specs)
#
# gcc compiler flags:
# -Wall		- enables all compiler warning messages 
# -Werror	- every warning treates as an error unless specified 
# -g		- default debug information 
# -O0		- optimization for compilation time (default)
# -std		- language standard 
# -mcpu		- specifies name of the target ARM processor
# -mthumb	- select between code that executed in ARM & Thumb states 
# -march	- specifies the name of the target architecture 
# -mfloat-abi	- specifies which floating point ABI to use   
# -mfpu		- specifies what floating point hardware is available on the target
#
# Notes: 
# 1)	To avoid linker errors, $(LDFLAGS) must preceed object files. 
#		$(LDLIBS) (not currently used) should follow object files.
# 2)	Generally both $(INCLUDE) and $(CFLAGS) should not be included in the 
#		build recipe since the object compilation phase is already over.
#		In this Make File $(CFLAGS) and $(INCLUDES) are included in both the 
#       compilation and linking recipes to avoid the following error if
#		$(PLATFORM)=MSP432:
#		"error: filename.o uses VFP register arguments, $(TARGET).out does not"
#		Compilation Recipe:  $(OBJ_DIR)/%.o
#		Linking Recipe:  build: $(TARGET).out
#------------------------------------------------------------------------------

# Include other make files
include sources.mk

# Target
TARGET = course1_final

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
CGFLAGS = -Wall -Werror -g -O0 -std=c99 
CPPFLAGS = -E
CFLAGS = $(CGFLAGS) -D$(PLATFORM) -D$(VERBOSE) -D$(COURSE1)
LDFLAGS = -Wl,-Map=$(TARGET).map

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
	LD = arm-none-eabi-ld
	OBJDUMP = arm-none-eabi-objdump
	SIZE = arm-none-eabi-size
	CFLAGS += $(ARCHFLAGS)
	LDFLAGS += -T $(LINKER_FILE)

else
	# Compiler Defines	
	CC = gcc
	LD = ld
	OBJDUMP = objdump
	SIZE=size
	
endif

# Define File Directories
SRC_DIR := src
PRE_DIR := pre
ASM_DIR := asm
OBJ_DIR := obj
DEP_DIR := dep

# Make directories
$(PRE_DIR):
	mkdir $@
$(ASM_DIR):
	mkdir $@
$(OBJ_DIR):
	mkdir $@
$(DEP_DIR):
	mkdir $@


# Pattern matching
PRE := $(SOURCES:$(SRC_DIR)/%.c=$(PRE_DIR)/%.i)
ASM := $(SOURCES:$(SRC_DIR)/%.c=$(ASM_DIR)/%.asm)
OBJ := $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEP := $(SOURCES:$(SRC_DIR)/%.c=$(DEP_DIR)/%.d)


# Generate .i file for preprocessor
$(PRE_DIR)/%.i : $(SRC_DIR)/%.c | $(PRE_DIR)
	@echo
	@echo Generating preprocessor output file $@ from $^
	$(CC) $(CFLAGS) $(INCLUDES) $(CPPFLAGS) $^ -o $@   

# Generate assembly from c source
$(ASM_DIR)/%.asm : $(SRC_DIR)/%.c | $(ASM_DIR)
	@echo
	@echo Generating assembly file $@ from $^	
	$(CC) $(CFLAGS) $(INCLUDES) -S $^ -o $@ 

# Generate object file from c source
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo
	@echo Generating unlinked object file $@ from $^
	$(CC) $(CFLAGS) $(INCLUDES) -c $^ -o $@

# Generate dependency files
$(DEP_DIR)/%.d : $(SRC_DIR)/%.c | $(DEP_DIR)
	@echo
	@echo Generating dependency file $@ from $^
	$(CC) $(CFLAGS) $(INCLUDES) -MM $^ -o $@


# Generate all preprocessor files (*.i)
.PHONY: preprocess
preprocess: $(PRE)

# Generate all assembly files (*.asm)
.PHONY: assembly
assembly: $(ASM)

# Generate all unlinked object files (*.o)
.PHONY: compile-all
compile-all: $(OBJ)

# Generate all dependency files (*.d)
.PHONY: dependency
dependency: $(DEP)

# Compile all source files into object files and link into final executable
.PHONY: build
build: $(TARGET).out $(TARGET).asm

# See Notes at top of file regarding inclusion of $(CFLAGS) $(INCLUDES) in 
# Linking Recipe:  build: $(TARGET).out 
$(TARGET).out: $(OBJ) $(DEP)
	@echo	
	@echo Building all files for $(PLATFORM) platform: 
	$(CC) $(CFLAGS) $(LDFLAGS) $(INCLUDES) $(OBJ) -o $@
#	@echo	
#	@echo Size Report for $(TARGET).out on $(PLATFORM) platform:
#	$(SIZE) -Atd $@
#	$(SIZE) $@

$(TARGET).asm : $(TARGET).out
	$(OBJDUMP) -d $(TARGET).out >> $@

# Remove all generated files
# use:  @rm: tells make to not echo the recipe to output
#	-rm: tells make to ignore the return value of the recipe (assumes it passes)
#	-f : to suppress messages
.PHONY: clean
clean:
	@echo 	
	@echo All generated files deleted
	@rm -f $(PRE_DIR)/*.i
	@rm -f $(ASM_DIR)/*.asm
	@rm -f $(OBJ_DIR)/*.o
	@rm -f $(DEP_DIR)/*.d
	@rm -f *.map *.out *.asm



