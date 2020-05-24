/******************************************************************************
 * Copyright (C) 2020
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are 
 * permitted to modify this and use it to learn about the field of embedded
 * software. No one is liable for any misuse of this material. 
 *
 *****************************************************************************/

/**
 @file data.h
 @brief Abstraction of Integer-to-ASCII and ASCII-to-Integer conversion
 
 This header file provides 2 functions to convert between Integer and ASCII.
 */

#include <stdint.h>

/**
 @brief Converts Integer to ASCII String
 
 Function converts a 32 bit integer to ASCII String representation.
 Returns the length of the converted data. 
  
 The simplest algorithm is to repeatedly do integer division by the given base
 (2, 10 or 16) resulting in a quotient and a remainder. 
 The remainder is converted to ASCII character and prepended to the result
 string.  
 The quotient, if non-zero, is passed to the next iteration of the algorithm.

 @param ptr Pointer to a character data set
 @param data 32 bit integer
 @param base Provided base: 2 to 16	
 
 @return length of the String including null character and negative sign
 */
uint8_t my_itoa(int32_t data, uint8_t * ptr, uint32_t base);

/**
 @brief Converts ASCII String to Integer
 
 Function converts ASCII String representation to a 32 bit integer. 
 Returns the value of the integer. 
 
 @param ptr Pointer to a character data set
 @param digits Length of String
 @param base Provided base: 2 to 16
 
 @return value of the integer
 */
int32_t my_atoi(uint8_t * ptr, uint8_t digits, uint32_t base);

