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

[5] W3Schools, “C memory reallocation (realloc),” W3Schools Online Web Tutorials. [Online]. Available: https://www.w3schools.com/c/c_memory_reallocate.php
. [Accessed: Jan. 2026].

[6] Codecademy, “C operators — sizeof,” Codecademy Documentation. [Online]. Available: https://www.codecademy.com/resources/docs/c/operators/sizeof
. [Accessed: Jan. 2026].

[7] W3Schools, “C structs and padding,” W3Schools Online Web Tutorials. [Online]. Available: https://www.w3schools.com/c/c_structs_padding.php
. [Accessed: Jan. 2026].

[8] W3Schools, “C stdio fgets() Function”. [Online]. Available: https://www.w3schools.com/c/ref_stdio_fgets.php
. [Accessed: Jan. 2026].

*/


// this is the functions lists does stuff when called upon




#include "Interface.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_BUF 4096
#define MAX_ROWS 5   /* load only first few rows for Phase 1 */

/*
    Clears remaining characters from the input buffer (waiting in stdin).
    Used to prevent invalid input from affecting subsequent reads in the menu.

    Parameters: none
    Returns: nothing
*/
void clear_input_line(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { //getchar reads next char from stdin, stores it in c, and discards it
        /* discard */
    }
}

/*
    Sometimes people use enter for menu inputs, this trims newlines from strings (/,).

    Parameters:
        s - pointer to a null-terminated character array
    Returns: nothing
*/
static void trim_newline(char *s) {
    size_t n = strlen(s); //strlen returns length of string s (input)
    while (n > 0 && (s[n - 1] == '\n' || s[n - 1] == '\r')) { //trim \n and \r from end of string (windows line endings? they're a thing)
        s[n - 1] = '\0';
        n--;
    }
}

/*
    Counts the number of columns in a CSV header line by
    counting comma delimiters.

    Parameters:
        line - CSV header line
    Returns:
        Number of detected columns
*/
static int count_columns(const char *line) {
    int cols = 1;
    for (const char *p = line; *p; p++) {
        if (*p == ',') {
            cols++;
        }
    }
    return cols;
}

/*
    Frees all dynamically allocated memory associated with
    a DatabaseDTO and resets its fields.

    Parameters:
        dto - pointer to DatabaseDTO to be freed
        Cycles through rows and columns to free each string, then frees row pointers and finally the main values pointer.
    Returns: nothing
*/
static void freeDatabaseDTO(DatabaseDTO *dto) {
    for (int i = 0; i < dto->rows; i++) {
        for (int j = 0; j < dto->columns; j++) {
            free(dto->values[i][j]);
        }
        free(dto->values[i]);
    }
    free(dto->values);

    dto->rows = 0;
    dto->columns = 0;
    dto->values = NULL;
}

/*
    Outputs the contents of the DatabaseDTO to the screen
    by looping over rows and columns.

    Parameters:
        dto - pointer to DatabaseDTO containing loaded data
    Returns: nothing
*/
static void printDatabaseDTO(const DatabaseDTO *dto) {
    printf("\nLoaded %d rows x %d columns\n\n", dto->rows, dto->columns);

    for (int r = 0; r < dto->rows; r++) {
        printf("Row %d:\n", r + 1);
        for (int c = 0; c < dto->columns; c++) {
            printf("  %s\n", dto->values[r][c]);
        }
        printf("\n");
    }
}

/*
    Opens the CSV data file, dynamically reads the first
    few records into a DatabaseDTO, and displays the data.

    Parameters: none
    Returns: nothing
*/
void do_read_file(void) {
    DatabaseDTO dto = {0, 0, NULL};
    FILE *fp = fopen("PP1/App/pacific_rim_npr_coastalmarine_black_oystercatcher_population_nesting_counts_2008-2017_data.csv", "r");
    char line[LINE_BUF];

    if (fp == NULL) {
        printf("Could not open CSV file.\n\n");
        return;
    }

    /* Read header to determine column count */
    fgets(line, sizeof(line), fp);
    dto.columns = count_columns(line);

    /* Read rows dynamically 
    allocate array of pointers for spacing, not value!
    sizeof indicates the memory size of what is being pointed to (the dto's values in dto.values), so we multiply by number of rows. It is a lot leaner this way
    compared to Java using object headers + alignment that takes up more memory. Especially for array of objects each with their own object header + alignment.
    Uhhhh... Better summed up as  “Give me space for rows number of row pointers.”
   
    */
    while (dto.rows < MAX_ROWS && fgets(line, sizeof(line), fp)) {
        trim_newline(line);

        dto.rows++;
        dto.values = realloc(dto.values, dto.rows * sizeof *dto.values);
        dto.values[dto.rows - 1] =
            malloc(dto.columns * sizeof *dto.values[dto.rows - 1]);

        char *saveptr = NULL;
        char *token = strtok_r(line, ",", &saveptr);

        for (int c = 0; c < dto.columns; c++) {
            dto.values[dto.rows - 1][c] = strdup(token ? token : "");
            token = strtok_r(NULL, ",", &saveptr);
        }
    }

    fclose(fp);

    printDatabaseDTO(&dto);
    freeDatabaseDTO(&dto);
}
