## Introduction to Embedded Systems Software and Development Environments
### COURSERA - University of Colorado Boulder

*Author*: Andrew Wihler 

This repository contains the: 
**Peer-Graded Assignment: Week 2 Application Assignment** \
\
This assignment creates a build system using the GNU tools, GCC and GNU Make. The Makefile compiles multiple files, links them together and creates a final output executable. Two platforms are supported; the host environment and the target embedded system MSP432. The host system allows execution on the host platform. The target system will be used to create our microcontroller applications. \
\
**msp432p401r.lds** - MSP432 linker file \
\
**src** folder : contains five source files
- *Makefile* - The makefile you are to edit for the assignment sources.mk - The source file you are to edit for the assignment
- *main.c* - Main file you are to work with
- *memory.c* - File that interacts with memory through an IO abstraction interface
- *interrupts_msp432p401r_gcc.c* - MSP432 specific C-file for interrupts
- *startup_msp432p401r_gcc.c* - MSP432 specific C-file for startup
- *system_msp432p401r.c* - MSP432 specific C-file for for system information \
\
**includer** folder : contains the three directories of supporting header files
- **common** - Contains common headers for both platform targets
- **msp432** - Contains MSP432 platform headers
- **CMSIS** - Contains ARM architecture specific headers

