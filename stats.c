/******************************************************************************
 * Copyright (C) 2020 by Andrew Wihler
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are 
 * permitted to modify this and use it to learn about the field of embedded
 * software. Andrew Wihler is not liable for any misuse of this material. 
 *
 *****************************************************************************/
/**
 * @file stats.c 
 * @brief code file for statistical analytics
 *
 * Intro to Embedded Systems Software and Dev - U of Colorado Boulder
 * Course1 - Module1
 * Programming assignment to create a simple application that performs 
 * statistical analytics on an array of unsigned char data items.
 *
 * @author Andrew Wihler
 * @date 12.APR.2020
 *
 */



#include <stdio.h>
#include "stats.h"

/* Size of the Data Set */
#define SIZE (40)

void main() {

  unsigned char test[SIZE] = { 34, 201, 190, 154,   8, 194,   2,   6,
                              114, 88,   45,  76, 123,  87,  25,  23,
                              200, 122, 150, 90,   92,  87, 177, 244,
                              201,   6,  12,  60,   8,   2,   5,  67,
                                7,  87, 250, 230,  99,   3, 100,  90};

  
  /* Statistics and Printing Functions */

  
}

/* Code for Functions */

void print_array(unsigned char * data, unsigned int size){
  
}

void print_statistics(unsigned char * data, unsigned int size){

}

void sort_array(unsigned char * data, unsigned int size){

}

float find_mean(unsigned char * data, unsigned int size){

}

float find_median(unsigned char * data, unsigned int size){

}

unsigned char find_maximum(unsigned char * data, unsigned int size){

}

unsigned char find_minimum(unsigned char * data, unsigned int size){

}





