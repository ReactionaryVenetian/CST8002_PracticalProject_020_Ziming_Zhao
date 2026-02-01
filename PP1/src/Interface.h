/*
Author: Ziming Zhao
Brave new world towards the defense industries.
Sources:
[1] W3Schools, “C files write,” W3Schools Online Web Tutorials. [Online]. Available: https://www.w3schools.com/c/c_files_write.php
. [Accessed: Jan. 2026].

[2] W3Schools, “C files read,” W3Schools Online Web Tutorials. [Online]. Available: https://www.w3schools.com/c/c_files_read.php
. [Accessed: Jan. 2026].
*/

/* this is the interface that lets the main know what's where*/ 


// ifndef INTERFACE_H, checks if INTERFACE_H is loaded to prevent multiple inclusions, which can cause errors I think
// if it is defined, it skips to the end at #endif
#ifndef INTERFACE_H 
// ifndef returns false(0), then we load all the code between it and #endif 
#define INTERFACE_H

#include <stddef.h>

/*
    Returns 1 if filename is "safe" (no folder separators) and can be used
    in the startup folder. Returns 0 otherwise.
 */
int is_safe_startup_filename(const char *filename);

/*
    Copies input into out, ensuring it ends with ".txt".
    If input already ends with ".txt", it is copied as-is.
    If not, ".txt" is appended (as long as it fits).
 */
void normalize_txt_filename(const char *input, char *out, size_t out_size);

/* Returns 1 if the file exists, 0 if it does not exist. */
int file_exists(const char *filename);

/*
    Reads a text file into buffer (null-terminated).
    Returns 0 on success, nonzero on failure.
 */
int read_text_file(const char *filename, char *buffer, size_t buffer_size);

/*
    Writes text to filename.
    If overwrite == 0 and the file already exists, returns 2 (special code).
    Returns 0 on success, nonzero on failure.
 */
int write_text_file(const char *filename, const char *text, int overwrite);

#endif