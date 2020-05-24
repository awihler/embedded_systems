## Introduction to Embedded Systems Software and Development Environments
### COURSERA - University of Colorado Boulder

*Author*: Andrew Wihler 

This repository contains the: 
**Peer-Graded Assignment: Week 4 Expanded Build System and Memory** \
\
This assignment reuses the version control repository from Week 1 and adds new c-programming functions that manipulate memory. The code is tested on the host machine, but should compile for both the target platform (MSP432) and host platform.  


### project directory structure

- *Makefile*
- *source.mk*
- *msp432p401r.lds*
- **src** (source files *.c)
	- *main.c* : Main function needed to call test functions (in course1.c)
	- *memory.c* : Memory movement and manipulation functions
	- *data.c* : Integer-to-ASCII and ASCII-to-Integer function
	- *stats.c* : Contains print_array() function (enabled/disabled using a compile time switch VERBOSE)
	- *course1.c* : Course assessment functions
	- *interrupts_msp432p401r_gcc.c* : Target embedded system files
	- *startup_msp432p401r_gcc.c* : Target embedded system files
	- *system_msp432p401r.c* : Target embedded system files 
- **include** (header files *.h)
- **pre** (preprocessing files *.i)
- **asm** (assembly files *.asm)
- **obj** (object files *.o)
- **dep** (dependencies *.d)
\
\
The Make file has been modfied to automatically generate and order all generated files into the appropriate folders (**pre**, **asm**, **obj**, **dep**).  The target output file (.out) is saved to the top of the project directory. 

