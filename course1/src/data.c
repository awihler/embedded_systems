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
  @file data.c
  @brief This file includes the Integer-to-ASCII and ASCII-to-Integer 
  functions to convert data between a standard integer type and an ASCII string.
  			
  @author Andrew Wihler
  @date May, 2020
 
 */

#include <stdint.h>
#include "data.h"
#include "platform.h"
#include "memory.h"
#include "stats.h"

uint8_t my_itoa(int32_t data, uint8_t *ptr, uint32_t base) {
	
//	int32_t temp; 
	char flag = 0;
	uint8_t i = 0, length; 

	// assign null terminator at end of string
	if(data == 0) {
		*(ptr + ++i) = '\0';
		return i+1;	
	}
	else{
		*(ptr + i++) = '\0';
	}

	#ifdef VERBOSE
	PRINTF("\n");
	PRINTF("--------------------------------\n");
	PRINTF("my_itoa():\n");
	PRINTF("	Base: %d\n", base); 
	PRINTF("	Given decimal number: %d\n", data);
	PRINTF("	ptr[%d] (assigned null terminator): %d\n", i-1, ptr[i-1]); 
	#endif

	// Remove negative sign if existing
	// if(data < 0 && base == 10){
	if(data < 0){
		flag = 1;	
		data = -data;
	}

	#ifdef VERBOSE
	PRINTF("	flag (=1 for negative number): %d\n", flag);
	#endif

	// Conversion algorithm:
	// Divide integer by base and store remainder in pointer array
	// Divide integer by base and repeat
	while(data != 0) {
		*(ptr + i) = data%base;   // modulo division

		#ifdef VERBOSE    
		PRINTF("	data: %d\n", data);
		PRINTF("	ptr[%d] (modulo division): %d\n", i, ptr[i]); 
		#endif

		i = i+1;
		data = data/base;
	}
  
	// Assign "-" dash for negative number (flag==1)
	if(flag == 1) {
		*(ptr + i++) = '-';

		#ifdef VERBOSE
		PRINTF("	ptr[%d] (negative sign ascii): %d\n", i-1, ptr[i-1]); 
		#endif
	}
 
	// Assign length of digit
	length = i;

	// reverse the order of the pointer array
	ptr = my_reverse(ptr, length);

	#ifdef VERBOSE
	// Print the elements of the pointer array 
	PRINTF("\n	pointer array elements: "); 
	print_array(ptr, length);
	PRINTF("	(reversed order)\n");
	// Print the length of the word 
	PRINTF("\n	number of digits: %d\n", length);
	#endif

	return length;

}

int32_t my_atoi(uint8_t * ptr, uint8_t digits, uint32_t base) {

	int32_t data = 0;

	// number of digits excluding null terminator
	uint8_t i = digits-1;  

	//initialise base factor to unit
	uint32_t base_factor = 1;		

	
	if(!ptr){
		return -9999;
	}
	
	#ifdef VERBOSE    
	PRINTF("\n");
	PRINTF("--------------------------------\n");
	PRINTF("my_atoi():\n");
	PRINTF("	number of digits (excluding null terminator): %d\n", i);
	PRINTF("\n	pointer array elements: "); 
	print_array(ptr, i);
	PRINTF("\n");
	#endif
	
	// Conversion algorithm:
	// Multiple element of the ascii string with base factor and store sum.
	// Base factor is sequence product of the base.
	while(i > 1){

		data += (*(ptr + i-1)) * (base_factor) ;

		#ifdef VERBOSE    
		PRINTF("	ptr[%d]: %d\n", i-1, ptr[i-1]); 
		PRINTF("	data: %d\n", data);
		#endif

		i = i - 1;
		base_factor *= base;
	}
   
 	// Convert to negative number if last variable contains "-" dash
 	// (stored in array with ASCII=45)
	if(*(ptr + i-1) == '-'){  
		data = -data;
	}
	else{
		data += (*(ptr + i-1)) * (base_factor);
	}

	#ifdef VERBOSE
	PRINTF("	ptr[%d]: %d\n", i-1, ptr[i-1]); 
	PRINTF("	data: %d\n", data);
	#endif 

	return data;

}

