## Introduction to Embedded Systems Software and Development Environments
### COURSERA - University of Colorado Boulder

*Author*: Andrew Wihler 

This repository contains the: 
**Peer-Graded Assignment: Week 4 Expanded Build System and Memory** \
\
This assignment reuses the version control repository from Week 1 and adds some new c-programming functions that manipulate memory. The code is tested on the host machine, but should compile for both the target platform and host platform.  \
\
**‘src’ folder** : contains source files (*.c) \
- *main.c* : Main function needed to call test functions (in course1.c).
- *memory.c* : Contains basic memory movement and manipulation options.
- *data.c* : Contains both an Integer-to-ASCII and ASCII-to-Integer function.
- *stats.c* : Contains the print_array() function that is enabled/disabled using a compile time switch (VERBOSE flag in the makefile; -DVERBOSE).
- *course1.c* : Contains the course assessment functions. \
\
The src folder also contains the target embedded system files:
- *interrupts_msp432p401r_gcc.c*
- *startup_msp432p401r_gcc.c*
- *system_msp432p401r.c*  \
\
**‘include’ folder** : contains all header files (*.h) \
The Make file has been modfied to automatically generate a obj directory for locating all the .o object files.  The traget output file (.out) is located with the Make file at the top of the project directory. \
\
**project directory structure**
- Makefile
- source.mk
- target.out
- include (header files *.h)
- src (source files *.c)
- obj (object files *.o)
