/******************************************************************************
 * Copyright (C) 2017 by Alex Fosdick - University of Colorado
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are 
 * permitted to modify this and use it to learn about the field of embedded
 * software. Alex Fosdick and the University of Colorado are not liable for any
 * misuse of this material. 
 *
 *****************************************************************************/
/**
  @file course1.c 

  @brief This file is to be used to provide test cases for the 
  course 1 final assessment.
  @author Alex Fosdick
  @date April 2, 2017

  @brief Updated to include more diagnostic information (with VERBOSE)
  @author Andrew Wihler
  @date May 20, 2020

 */


#include "course1.h" 
#include "platform.h" 
#include "memory.h"   
#include "data.h"  
#include "stats.h"  

int8_t test_data1() {

	uint8_t *ptr;
	int32_t num = -4096;
	uint32_t digits;
	int32_t value;

	#ifdef VERBOSE
	PRINTF("\n");
	PRINTF("--------------------------------\n");
	PRINTF("test_data1()---START\n");
	#endif
	
	// Allocate dynamic memory
	ptr = (uint8_t*) reserve_words( DATA_SET_SIZE_W );

	// Validate result
	if (! ptr)
	{
		return TEST_ERROR;
	}

	digits = my_itoa( num, ptr, BASE_16);  
	value = my_atoi( ptr, digits, BASE_16); 

	#ifdef VERBOSE
	PRINTF("\n");
	PRINTF("--------------------------------\n");
	PRINTF("test_data1():\n");
	PRINTF("	Initial decimal number: %d\n", num);
	PRINTF("	ASCII string length: %d\n", digits);
	PRINTF("	Final decimal number: %d\n", value);
	#endif

	// Deallocate dynamic memory
	free_words( (uint32_t*)ptr);

	if (value != num)
	{
    	return TEST_ERROR;
  	}

  	return TEST_NO_ERROR;
}

int8_t test_data2() {

	uint8_t * ptr;
	int32_t num = 123456;
	uint32_t digits;
	int32_t value;

	#ifdef VERBOSE
	PRINTF("\n");
	PRINTF("--------------------------------\n");
	PRINTF("test_data2()---START\n");
	#endif

	// Allocate dynamic memory
	ptr = (uint8_t*) reserve_words( DATA_SET_SIZE_W );

	if (! ptr)
	{
		return TEST_ERROR;
	}

	digits = my_itoa( num, ptr, BASE_10);
	value = my_atoi( ptr, digits, BASE_10);
  
	#ifdef VERBOSE
	PRINTF("\n");
	PRINTF("--------------------------------\n");
	PRINTF("test_data2():\n");
	PRINTF("	Initial decimal number: %d\n", num);
	PRINTF("	ASCII string length: %d\n", digits);
	PRINTF("	Final decimal number: %d\n", value);
	#endif

	// Deallocate dynamic memory
  	free_words( (uint32_t*)ptr );

	// Validate result
  	if (value != num)
  	{
    	return TEST_ERROR;
  	}

 	return TEST_NO_ERROR;
}

int8_t test_memmove1() {

	uint8_t i;
	int8_t ret = TEST_NO_ERROR;
	uint8_t * set;
	uint8_t * ptra;
	uint8_t * ptrb;

	#ifdef VERBOSE
	PRINTF("\n");
	PRINTF("--------------------------------\n");
	PRINTF("test_memmove1()---START\n");
	PRINTF("- NO OVERLAP\n");
	#endif

	// Allocate dynamic memory
	set = (uint8_t*) reserve_words( MEM_SET_SIZE_W );

	if (! set) 
	{
		return TEST_ERROR;
	}

	// return address
	ptra = &set[0];
	ptrb = &set[TEST_MEMMOVE_LENGTH];

	// Initialize the set to test values 
	for( i = 0; i < MEM_SET_SIZE_B; i++)
	{
		set[i] = i;
	}

	#ifdef VERBOSE    
	PRINTF("\n");
	PRINTF("--------------------------------\n");
	PRINTF("my_memmove():\n");
	PRINTF("\n	Initial pointer array elements: "); 
	print_array(set, MEM_SET_SIZE_B);
	PRINTF("\n");
	PRINTF("	Address of starting pointer: %p\n", ptra);
	PRINTF("	Value of starting pointer: %d\n", *ptra);
	PRINTF("	Address of ending pointer: %p\n", ptrb);
	PRINTF("	Value of ending pointer: %d\n", *ptrb);
	#endif

	// Move byte pointer from source location to destination
	my_memmove(ptra, ptrb, TEST_MEMMOVE_LENGTH); 

	#ifdef VERBOSE
	PRINTF("\n	Final pointer array elements: "); 
	print_array(set, MEM_SET_SIZE_B);
	#endif

	// Validate result
	for (i = 0; i < TEST_MEMMOVE_LENGTH; i++)
	{
		if (set[i + TEST_MEMMOVE_LENGTH] != i)
		{
			ret = TEST_ERROR;
		}
	}

	// Deallocate dynamic memory
	free_words( (uint32_t*)set );
	
	return ret;
}

int8_t test_memmove2() {

	uint8_t i;
	int8_t ret = TEST_NO_ERROR;
	uint8_t * set;
	uint8_t * ptra;
	uint8_t * ptrb;

	#ifdef VERBOSE
	PRINTF("\n");
	PRINTF("--------------------------------\n");
	PRINTF("test_memmove2()---START\n");
    PRINTF("-OVERLAP END OF SRC BEGINNING OF DST\n");
	#endif

	// Allocate dynamic memory
	set = (uint8_t*) reserve_words(MEM_SET_SIZE_W);

	if (! set )
	{
	    return TEST_ERROR;
	}

	ptra = &set[0];
	ptrb = &set[8];

	// Initialize the set to test values 
	for( i = 0; i < MEM_SET_SIZE_B; i++) {
	    set[i] = i;
	}

	#ifdef VERBOSE    
	PRINTF("\n");
	PRINTF("--------------------------------\n");
	PRINTF("my_memmove():\n");
	PRINTF("\n	Initial pointer array elements: "); 
	print_array(set, MEM_SET_SIZE_B);
	PRINTF("\n");
	PRINTF("	Address of starting pointer: %p\n", ptra);
	PRINTF("	Value of starting pointer: %d\n", *ptra);
	PRINTF("	Address of ending pointer: %p\n", ptrb);
	PRINTF("	Value of ending pointer: %d\n", *ptrb);
	#endif

	// Move byte pointer from source location to destination
	my_memmove(ptra, ptrb, TEST_MEMMOVE_LENGTH);

	#ifdef VERBOSE
	PRINTF("\n	Final pointer array elements: "); 
	print_array(set, MEM_SET_SIZE_B);
	#endif

	// Validate result
	for (i = 0; i < TEST_MEMMOVE_LENGTH; i++)
	{
	    if (set[i + 8] != i)
	    {
			ret = TEST_ERROR;
		}
	}

	// Deallocate dynamic memory
	free_words( (uint32_t*)set );

	return ret;
}

int8_t test_memmove3() {

	uint8_t i;
	int8_t ret = TEST_NO_ERROR;
	uint8_t * set;
	uint8_t * ptra;
	uint8_t * ptrb;

	#ifdef VERBOSE
	PRINTF("\n");
	PRINTF("--------------------------------\n");
	PRINTF("test_memmove3()---START\n");
    PRINTF("-OVERLAP END OF DEST BEGINNING OF SRC\n");
	#endif

	// Allocate dynamic memory
	set = (uint8_t*)reserve_words( MEM_SET_SIZE_W);

	if (! set ) 
	{
		return TEST_ERROR;
	}

	ptra = &set[8];
	ptrb = &set[0];

	// Initialize the set to test values
	for( i = 0; i < MEM_SET_SIZE_B; i++)
	{
    	set[i] = i;
	}

	#ifdef VERBOSE    
	PRINTF("\n");
	PRINTF("--------------------------------\n");
	PRINTF("my_memmove():\n");
	PRINTF("\n	Initial pointer array elements: "); 
	print_array(set, MEM_SET_SIZE_B);
	PRINTF("\n");
	PRINTF("	Address of starting pointer: %p\n", ptra);
	PRINTF("	Value of starting pointer: %d\n", *ptra);
	PRINTF("	Address of ending pointer: %p\n", ptrb);
	PRINTF("	Value of ending pointer: %d\n", *ptrb);
	#endif

	// Move byte pointer from source location to destination
	my_memmove(ptra, ptrb, TEST_MEMMOVE_LENGTH);

	#ifdef VERBOSE
	PRINTF("\n	Final pointer array elements: "); 
	print_array(set, MEM_SET_SIZE_B);
	#endif

	// Validate result
	for (i = 0; i < TEST_MEMMOVE_LENGTH; i++)
	{
		if (set[i] != (i + 8))
		{
			ret = TEST_ERROR;
		}
	}

	// Deallocate dynamic memory
	free_words( (uint32_t*)set );

	return ret;
}

int8_t test_memcopy() {

	uint8_t i;
	int8_t ret = TEST_NO_ERROR;
	uint8_t * set;
	uint8_t * ptra;
	uint8_t * ptrb;

	#ifdef VERBOSE
	PRINTF("\n");
	PRINTF("--------------------------------\n");
	PRINTF("test_memcopy()---START\n");
    PRINTF("\n");
	#endif

	// Allocate dynamic memory
	set = (uint8_t*) reserve_words(MEM_SET_SIZE_W);

	if (! set ) 
	{
		return TEST_ERROR;
	}

	ptra = &set[0];
	ptrb = &set[16];

	// Initialize the set to test values
	for( i = 0; i < MEM_SET_SIZE_B; i++) {
		set[i] = i;
	}

	#ifdef VERBOSE    
	PRINTF("\n");
	PRINTF("--------------------------------\n");
	PRINTF("my_memcopy():\n");
	PRINTF("\n	Initial pointer array elements: "); 
	print_array(set, MEM_SET_SIZE_B);
	PRINTF("\n");
	PRINTF("	Address of starting pointer: %p\n", ptra);
	PRINTF("	Value of starting pointer: %d\n", *ptra);
	PRINTF("	Address of ending pointer: %p\n", ptrb);
	PRINTF("	Value of ending pointer: %d\n", *ptrb);
	#endif

	// Move byte pointer from source location to destination
	my_memmove(ptra, ptrb, TEST_MEMMOVE_LENGTH);

	#ifdef VERBOSE
	PRINTF("\n	Final pointer array elements: "); 
	print_array(set, MEM_SET_SIZE_B);
	#endif

	// Validate result
	for (i = 0; i < TEST_MEMMOVE_LENGTH; i++)
	{
    	if (set[i+16] != i)
    	{
			ret = TEST_ERROR;
		}
	}

	// Deallocate dynamic memory
	free_words( (uint32_t*)set );

	return ret;
}

int8_t test_memset() {
  
	uint8_t i;
	uint8_t ret = TEST_NO_ERROR;
	uint8_t * set;
	uint8_t * ptra;
	uint8_t * ptrb;

	#ifdef VERBOSE
	PRINTF("\n");
	PRINTF("--------------------------------\n");
	PRINTF("test_memset()---START\n");
    PRINTF("\n");
	#endif

	// Allocate dynamic memory
	set = (uint8_t*)reserve_words(MEM_SET_SIZE_W);
  
	if (! set )
	{
		return TEST_ERROR;
	}

	ptra = &set[0];
	ptrb = &set[16];

	// Initialize the set to test values
	for( i = 0; i < MEM_SET_SIZE_B; i++) 
	{
		set[i] = i;
	}

	#ifdef VERBOSE    
	PRINTF("\n");
	PRINTF("--------------------------------\n");
	PRINTF("my_memcopy():\n");
	PRINTF("\n	Initial pointer array elements: "); 
	print_array(set, MEM_SET_SIZE_B);
	PRINTF("\n");
	PRINTF("	Address of starting pointer: %p\n", ptra);
	PRINTF("	Value of starting pointer: %d\n", *ptra);
	PRINTF("	Address of ending pointer: %p\n", ptrb);
	PRINTF("	Value of ending pointer: %d\n", *ptrb);
	#endif
  
	my_memset(ptra, MEM_SET_SIZE_B, 0xFF);

	#ifdef VERBOSE
	PRINTF("\n	Final pointer array elements: "); 
	print_array(set, MEM_SET_SIZE_B);
	#endif

	my_memzero(ptrb, MEM_ZERO_LENGTH);

	#ifdef VERBOSE
	PRINTF("\n	Final pointer array elements: "); 
	print_array(set, MEM_SET_SIZE_B);
	#endif
  
	// Validate Set & Zero Functionality
	for (i = 0; i < MEM_ZERO_LENGTH; i++)
	{
	    if (set[i] != 0xFF)
	    {
			ret = TEST_ERROR;
		}
		if (set[16 + i] != 0)
		{
			ret = TEST_ERROR;
		}
	}

	// Deallocate dynamic memory
	free_words( (uint32_t*)set );
	
	return ret;
}

int8_t test_reverse(){
  
	uint8_t i;
  	int8_t ret = TEST_NO_ERROR;
  	uint8_t * copy;
  	uint8_t set[MEM_SET_SIZE_B] = {
								0x3F, 0x73, 0x72, 0x33, 0x54, 0x43, 0x72, 0x26,
								0x48, 0x63, 0x20, 0x66, 0x6F, 0x00, 0x20, 0x33,
								0x72, 0x75, 0x74, 0x78, 0x21, 0x4D, 0x20, 0x40,
								0x20, 0x24, 0x7C, 0x20, 0x24, 0x69, 0x68, 0x54
								};

	#ifdef VERBOSE
	PRINTF("\n");
	PRINTF("--------------------------------\n");
	PRINTF("test_reverse()---START\n");
    PRINTF("\n");
	#endif

	// Allocate dynamic memory
	copy = (uint8_t*)reserve_words(MEM_SET_SIZE_W);
	
	if (! copy )
	{
		return TEST_ERROR;
	}

	my_memcopy(set, copy, MEM_SET_SIZE_B);

	#ifdef VERBOSE    
	PRINTF("\n");
	PRINTF("--------------------------------\n");
	PRINTF("my_reverse():\n");
	PRINTF("\n	Initial pointer array elements: "); 
	print_array(set, MEM_SET_SIZE_B);
	PRINTF("\n");
	#endif
 
	my_reverse(set, MEM_SET_SIZE_B);

	#ifdef VERBOSE
	PRINTF("\n	Reversed pointer array elements: "); 
	print_array(set, MEM_SET_SIZE_B);
	#endif

	// Validate result
	for (i = 0; i < MEM_SET_SIZE_B; i++)
	{
		if (set[i] != copy[MEM_SET_SIZE_B - i - 1])
		{
  			ret = TEST_ERROR;
		}
	}

	// Deallocate dynamic memory
	free_words( (uint32_t*)copy );

  	return ret;
}

void course1(void) 
{
	uint8_t i;
	int8_t failed = 0;
	int8_t results[TESTCOUNT];

	results[0] = test_data1();
	results[1] = test_data2();
	results[2] = test_memmove1();
	results[3] = test_memmove2();
	results[4] = test_memmove3();
	results[5] = test_memcopy();
	results[6] = test_memset();
	results[7] = test_reverse();

	for ( i = 0; i < TESTCOUNT; i++) 
	{
	    failed += results[i];
	}

	PRINTF("\n");
	PRINTF("--------------------------------\n");
	PRINTF("Test Results:\n");
	PRINTF("  PASSED: %d / %d\n", (TESTCOUNT - failed), TESTCOUNT);
	PRINTF("  FAILED: %d / %d\n", failed, TESTCOUNT);
	PRINTF("--------------------------------\n");
	PRINTF("test_data1() passed: %d\n", 1-results[0]);
	PRINTF("test_data2() passed: %d\n", 1-results[1]);
	PRINTF("test_memmove1() passed: %d\n", 1-results[2]);
	PRINTF("test_memmove2() passed: %d\n", 1-results[3]);
	PRINTF("test_memove3() passed: %d\n", 1-results[4]);
	PRINTF("test_memcopy() passed: %d\n", 1-results[5]);
	PRINTF("test_memset() passed: %d\n", 1-results[6]);
	PRINTF("test_reverse() passed: %d\n", 1-results[7]);
	PRINTF("--------------------------------\n");
}
