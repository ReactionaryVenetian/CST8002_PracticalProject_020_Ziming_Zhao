/*
Author: Ziming Zhao
Brave new world towards the defense industries.
Sources:

/* this is the interface that lets the main know what's where*/ 

// ifndef INTERFACE_H, checks if INTERFACE_H is loaded to prevent multiple inclusions, which can cause errors I think
// if it is defined, it skips to the end at #endif
#ifndef INTERFACE_H 
// ifndef returns false(0), then we load all the code between it and #endif 
#define INTERFACE_H


/* 
    My DTO, a simple struct to hold database data in memory.    
    It has three fields: number of columns, number of rows, and a 3D array of strings for the values.
*/
typedef struct {
    int columns;
    int rows;   // number of rows in the database entry, int type will be an issue for larger datasets
    char ***values;  // number of values per row, dynamically allocated array, * is for level of memory, so the first level is just the pointer,    
    //the second level is the array of pointers to each row, the third level is the char string for each column in that row.

} DatabaseDTO; //data transfer object for database entries, dynamically sized depending on input data.

/* Input helpers */
void clear_input_line(void);

/* Main menu action */
void do_read_file(void);

#endif