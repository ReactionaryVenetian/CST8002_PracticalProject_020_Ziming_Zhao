/*
Author: Ziming Zhao
Brave new world towards the defense industries.
Sources:
[1] W3Schools, “C functions recursion,” W3Schools Online Web Tutorials. [Online]. Available: https://www.w3schools.com/c/c_functions_recursion.php
. [Accessed: Jan. 2026].

[2] W3Schools, “C stdio reference,” W3Schools Online Web Tutorials. [Online]. Available: https://www.w3schools.com/c/c_ref_stdio.php
. [Accessed: Jan. 2026].

[3] W3Schools, “C files write,” W3Schools Online Web Tutorials. [Online]. Available: https://www.w3schools.com/c/c_files_write.php
. [Accessed: Jan. 2026].

[4] W3Schools, “C files read,” W3Schools Online Web Tutorials. [Online]. Available: https://www.w3schools.com/c/c_files_read.php
. [Accessed: Jan. 2026].
*/

#include "Interface.h"
#include <stdio.h>
#include <string.h>


/* this is the functions lists does stuff when called upon*/ 


#include "Interface.h"
#include <stdio.h>
#include <string.h>


/* Checks if the person entered anything 
    Parameters: filename - to check
    Returns: 1 if safe, 0 otherwise
*/

int is_safe_startup_filename(const char *filename) {
    size_t len;

    if (filename == NULL) return 0;

    len = strlen(filename); 
    if (len == 0) return 0;

    /* Checks if the filename contains any path separators with a loop for each char up to length, so that: 
    "The program will only write to or read from files within the folder or directory the program
    started up from within."*/
    for (size_t i = 0; i < len; i++) {
        if (filename[i] == '/' || filename[i] == '\\') return 0;
    }

    /* Returns 1 if the filename is safe (no path separators) */
    return 1;
}

/* Ensures the filename ends with ".txt"
   Parameters: 
     input    - what the user typed
     out      - buffer where final filename is stored
     out_size - size of output buffer
   Returns: nothing (void)
*/
void normalize_txt_filename(const char *input, char *out, size_t out_size) {
    size_t in_len;

    /* If output buffer is invalid, do nothing */
    if (out == NULL || out_size == 0) return;

    /* Initialize output as empty string */
    out[0] = '\0';

    /* If input is invalid, stop */
    if (input == NULL) return;

    /* Get length of user input */
    in_len = strlen(input);

    /* If filename already ends with ".txt", copy as-is */
    if (in_len >= 4 && strcmp(input + (in_len - 4), ".txt") == 0) {
        strncpy(out, input, out_size - 1);
        out[out_size - 1] = '\0';
        return;
    }

    /* Otherwise, append ".txt" if it fits in buffer */
    if (in_len + 4 < out_size) {
        strcpy(out, input);
        strcat(out, ".txt");
    } else {
        /* If not enough space, copy as much as possible safely */
        strncpy(out, input, out_size - 1);
        out[out_size - 1] = '\0';
    }
}

/* Checks if a file already exists
   Parameters: filename - file to check
   Returns: 1 if file exists, 0 if not
*/
int file_exists(const char *filename) {
    FILE *fp;

    /* If filename is invalid, treat as not existing */
    if (filename == NULL) return 0;

    /* Try opening file for reading */
    fp = fopen(filename, "r");
    if (fp == NULL) return 0;

    /* File opened successfully, so it exists */
    fclose(fp);
    return 1;
}

/* Reads an entire text file into a buffer
   Parameters:
     filename     - name of file to read
     buffer       - where file contents are stored
     buffer_size  - size of buffer
   Returns: 0 on success, non-zero on failure
*/
int read_text_file(const char *filename, char *buffer, size_t buffer_size) {
    FILE *fp;
    size_t total = 0;

    /* Validate parameters */
    if (filename == NULL || buffer == NULL || buffer_size == 0) return 1;

    /* Enforce startup-folder-only rule */
    if (!is_safe_startup_filename(filename)) return 2;

    /* Open file for reading */
    fp = fopen(filename, "r");
    if (fp == NULL) return 3;

    /* Start with empty buffer */
    buffer[0] = '\0';

    /* Read until end of file */
    while (!feof(fp)) {
        size_t space_left = (buffer_size - 1) - total;
        size_t n;

        /* Prevent buffer overflow */
        if (space_left == 0) {
            fclose(fp);
            return 4;
        }

        /* Read next chunk */
        n = fread(buffer + total, 1, space_left, fp);
        if (ferror(fp)) {
            fclose(fp);
            return 5;
        }

        total += n;
    }

    /* Null-terminate final string */
    buffer[total] = '\0';

    fclose(fp);
    return 0;
}

/* Writes text to a file
   Parameters:
     filename  - file to write to
     text      - text to write
     overwrite - 1 to allow overwrite, 0 to block overwrite
   Returns:
     0 on success
     2 if file exists and overwrite not allowed
     non-zero on other failure
*/
int write_text_file(const char *filename, const char *text, int overwrite) {
    FILE *fp;

    /* Validate parameters */
    if (filename == NULL || text == NULL) return 1;

    /* Enforce startup-folder-only rule */
    if (!is_safe_startup_filename(filename)) return 2;

    /* If overwrite not allowed and file exists, block write */
    if (!overwrite && file_exists(filename)) {
        return 2;
    }

    /* Open file for writing (overwrite) */
    fp = fopen(filename, "w");
    if (fp == NULL) return 3;

    /* Write text to file, hey look EOF from cobol notations */
    if (fputs(text, fp) == EOF) {
        fclose(fp);
        return 4;
    }

    fclose(fp);
    return 0;
}

