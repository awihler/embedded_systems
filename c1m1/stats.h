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
 * @file stats.h 
 * @brief header file for statistical analytics
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
#ifndef __STATS_H__
#define __STATS_H__

/**
 * @brief Print an array
 *
 * A function that prints an array of unsigned char data items 
 *
 * @param  data  An array of unsigned char data items
 * @param  size  Number of items in array
 *
 */
void print_array(unsigned char * data, unsigned int size);

/**
 * @brief Print the statistics of an array
 *
 * A function that prints the statistics of an array including :  
 * minimum, maximum, mean, and median.
 *
 * @param  data  An array of unsigned char data items
 * @param  size  Number of items in array
 *
 */
void print_statistics(unsigned char * data, unsigned int size);

/**
 * @brief Sort an array
 *
 * A function that reorders an array of unsigned char data items from large to small
 *
 * @param  data  An array of unsigned char data items
 * @param  size  Number of items in array
 *
 */
void sort_array(unsigned char * data, unsigned int size);

/**
 * @brief Calculate the mean
 *
 * A function that calculates the mean of an array of unsigned char data items 
 *
 * @param  data  An array of unsigned char data items
 * @param  size  Number of items in array
 *
 * @return mean
 */
float find_mean(unsigned char * data, unsigned int size);

/**
 * @brief Calculate the median
 *
 * A function that calculates the median of an array of unsigned char data items 
 *
 * @param  data  An array of unsigned char data items
 * @param  size  Number of items in array
 *
 * @return median
 */
float find_median(unsigned char * data, unsigned int size);

/**
 * @brief Calculate the maximum value
 *
 * A function that calculates the maximum value of an array of unsigned char data items 
 *
 * @param  data  An array of unsigned char data items
 * @param  size  Number of items in array
 *
 * @return maximum value
 */
unsigned char find_maximum(unsigned char * data, unsigned int size);

/**
 * @brief Calculate the minimum value
 *
 * A function that calculates the minimum value of an array of unsigned char data items 
 *
 * @param  data  An array of unsigned char data items
 * @param  size  Number of items in array
 *
 * @return minimum value
 */
unsigned char find_minimum(unsigned char * data, unsigned int size);

#endif /* __STATS_H__ */
