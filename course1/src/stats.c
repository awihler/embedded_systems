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
#include "platform.h"


/* Code for Functions */

void print_array(unsigned char * data, unsigned int size){

  #if defined (VERBOSE)  
    int i; 
    for(i=0; i<size; i++){
      if(i == size-1){
        PRINTF("%u \n", data[i]);
      }else{
        PRINTF("%u, ", data[i]);
      }    
    }
  #endif
}

void print_statistics(unsigned char * data, unsigned int size){
  PRINTF("Mean    = %.0f \n", find_mean(data, size));
  PRINTF("Median  = %.0f \n", find_median(data, size));
  PRINTF("Maximum = %u \n", find_maximum(data, size));
  PRINTF("Minimum = %u \n", find_minimum(data, size));
}

void sort_array(unsigned char * data, unsigned int size){
  
  unsigned char temp;
  int i, j;

  for(i=0; i < size-1; i++){
    for(j=i+1; j < size; j++){

      /* ascending: data[i] > data[j]    
        descending: data[i] < data[j] */ 
      if(data[i] < data[j]){
        temp = data[i];
        data[i] = data[j];
        data[j] = temp;
      }
    }
  }
}

float find_mean(unsigned char * data, unsigned int size){

  float sum = 0;
  int i;

  for(i=0; i < size; i++){
    sum += data[i];
  }

  return (int)sum/size;

}

float find_median(unsigned char * data, unsigned int size){

  float median;

  sort_array(data, size);

  if(size % 2 == 0){
    median = (data[size/2] + data[size/2 - 1])/2.0;
  }else{
    median = data[size/2];
  }
 
  return (int)median;

}

unsigned char find_maximum(unsigned char * data, unsigned int size){

  unsigned int max = data[0];
  int i;

  for(i=0; i<size; i++){
    if(data[i] > max){
      max = data[i];
    }
  } 

  return max;

}

unsigned char find_minimum(unsigned char * data, unsigned int size){

  unsigned int min = data[0];
  int i;

  for(i=0; i<size; i++){
    if(data[i] < min){
      min = data[i];
    }
  } 

  return min;

}





