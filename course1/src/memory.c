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
 * @file memory.c
 * @brief Abstraction of memory read and write operations
 *
 * This implementation file provides an abstraction of reading and
 * writing to memory via function calls. There is also a globally
 * allocated buffer array used for manipulation.
 *
 * @author Alex Fosdick
 * @date April 1 2017
 *
 */
#include "data.h"
#include "memory.h"
#include "stats.h"
#include <stdio.h>

/***********************************************************
 Function Definitions
***********************************************************/
void set_value(char * ptr, unsigned int index, char value){
  ptr[index] = value;
}

void clear_value(char * ptr, unsigned int index){
  set_value(ptr, index, 0);
}

char get_value(char * ptr, unsigned int index){
   return ptr[index];
}

void set_all(char * ptr, char value, unsigned int size){
  unsigned int i;
  for(i = 0; i < size; i++) {
    set_value(ptr, i, value);
  }
}

void clear_all(char * ptr, unsigned int size){
  set_all(ptr, 0, size);
}

uint8_t * my_memmove(uint8_t * src, uint8_t * dst, size_t length) {

	uint8_t i = 0;
	uint8_t *temp;

	// Allocate dynamic memory
	temp = (uint8_t*)reserve_words(length);
	
	for( i = 0; i < length; i++){
	    *(temp + i ) = *( src + i );
	}

	for( i = 0; i < length; i++){
	    *(dst + i ) = *( temp + i );
			}
	
	return dst;

	// Deallocate dynamic memory
	free_words((uint32_t*)temp);
}

uint8_t * my_memcopy(uint8_t * src, uint8_t * dst, size_t length) {
	
	uint8_t i = 0;

	for( i = 0; i < length; i++){
		*( dst + i ) = *( src + i );
	}

	return dst;

}

uint8_t * my_memset(uint8_t * src, size_t length, uint8_t value) {

	uint8_t i = 0;	
	
	for( i = 0; i < length; i++){
		*( src + i ) = value ;
	}

	return src;

}

uint8_t * my_memzero(uint8_t * src, size_t length) {

	src = my_memset(src , length , 0 );

	return src;

}

uint8_t * my_reverse(uint8_t * src, size_t length) {

	int32_t temp;
	uint8_t i = 0;

	for (i = 0; i <= (length-1)/2; i++){
		temp = *(src + i);
		*(src + i) = *(src + length - i - 1);
		*(src + length - i - 1) = temp;
	} 

/*	uint8_t start=0;
	uint8_t end=length-1;

	while(start < end){
		temp = src[start];
		src[start] = src[end];
		src[end] = temp;
		start++;
		end--;
	}	*/

	return src;
}

int32_t * reserve_words(size_t length) {

	int32_t *ptr;

	// Allocate dynamic memory
	ptr  = (int32_t *) malloc(length * sizeof(int32_t));

	#ifdef VERBOSE
	int i;
	printf("--------------------------------\n");
	printf("reserve_words(size_t length):\n");

	// Check if the memory has been successfully allocated by malloc or not 
	if (ptr == NULL) { 
		printf("	Memory not allocated using malloc.\n"); 
		exit(0); 
    } 
    else {
        // Memory has been successfully allocated 
        printf("	Memory successfully allocated using malloc.\n"); 
  
        // Print the elements of the array 
		printf("	Maximum string size: %zu\n", length);
        printf("	The initialised elements of the array are: "); 

        for (i = 0; i < length; ++i) { 
			if(i == length-1){
				printf("%d", ptr[i]);
			}else{
				printf("%d, ", ptr[i]);
			}    
		} 
    }

	printf("\n");	
	#endif

	return ptr;
}

void free_words(uint32_t * src){

	free(src);

}
