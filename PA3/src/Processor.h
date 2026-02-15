/*
Author: Ziming Zhao 041166304
Sources: Nothing new to learn here.
*/

// this is the interface that lets the main know what's where

// ifndef PROCESSOR_H, checks if PROCESSOR_H is loaded to prevent multiple inclusions, which can cause errors I think
// if it is defined, it skips to the end at #endif
#ifndef PROCESSOR_H 
// ifndef returns false(0), then we load all the code between it and #endif 
#define PROCESSOR_H

// Business function being tested
int add(int a, int b);

// Input helper
void clear_input_line(void);

// Menu options / test runners
void do_negative_test(void);
void do_positive_test(void);

#endif