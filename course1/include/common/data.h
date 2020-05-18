/******************************************************************************

******************************************************************************/

/**
 * @file data.h
 * @brief Abstraction of Integer-to-ASCII and ASCII-to-Integer conversion
 *
 * This header file provides 2 functions to convert between Integer and ASCII
 *
 */

/**
 * @brief Converts Integer to ASCII String
 *
 * Function converts a 32 bit integer to ASCII String representation.
 * Returns the length of the converted data. 
 *
 * @param ptr Pointer to a character data set
 * @param data 32 bit integer
 * @param base Provided base: 2 to 16	
 *
 * @return length of the String including null character incuding negative sign
 */

uint8_t my_itoa(int32_t data, uint8_t * ptr, uint32_t base);


/**
 * @brief Converts ASCII String to Integer
 *
 * Function converts ASCII String representation to a 32 bit integer. 
 * Returns the value of the integer. 
 *
 * @param ptr Pointer to a character data set
 * @param digits Length of ASCII String
 * @param base Provided base: 2 to 16
 *
 * @return value of the integer
 * 
 */

int32_t my_atoi(uint8_t * ptr, uint8_t digits, uint32_t base);
