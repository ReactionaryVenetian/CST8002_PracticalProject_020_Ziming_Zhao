/**
 * @file Input.c
 * @brief Provides utility functions for safe user input handling.
 *
 * CST8002 Programming Language Research Project
 * Practical Project Part 04 – multi-column sorting and additional features
 *
 * Author: Ziming Zhao 041166304
 * Professor: Stanley Pieda
 * Due Date: 2026-04-12
 *
 * Description:
 * This module contains helper functions for safely reading user input
 * from stdin. It handles common issues such as leftover input buffer
 * characters, newline trimming, and validation of numeric input.
 *
 * These functions were refactored from earlier project work to improve
 * modularity and code organization.
 *
 * References:
 * No additional references were required for this module.
 */

#include "Input.h"

#include <stdio.h>
#include <string.h>

/**
 * @brief Clears remaining characters from the input buffer.
 *
 * Removes any leftover characters in stdin until a newline or EOF
 * is encountered. This prevents invalid or extra input from affecting
 * subsequent reads.
 */
void clear_input_line(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        /* discard */
    }
}

/**
 * @brief Removes trailing newline characters from a string.
 *
 * Trims '\n' and '\r' characters from the end of a null-terminated string.
 *
 * @param s Pointer to the string to trim.
 */
static void trim_newline(char *s) {
    size_t n = strlen(s);
    while (n > 0 && (s[n - 1] == '\n' || s[n - 1] == '\r')) {
        s[n - 1] = '\0';
        n--;
    }
}

/**
 * @brief Reads an integer value from user input.
 *
 * Prompts the user and repeatedly attempts to read a valid integer.
 * Invalid input is cleared and the user is prompted again.
 *
 * @param prompt Prompt message displayed to the user.
 * @return int The valid integer entered by the user.
 */
int input_read_int(const char *prompt) {
    int value = 0;

    for (;;) {
        if (prompt != NULL) {
            printf("%s", prompt);
        }

        if (scanf("%d", &value) != 1) {
            clear_input_line();
            printf("Invalid input. Enter a number.\n");
            continue;
        }

        clear_input_line();
        return value;
    }
}

/**
 * @brief Reads a string from user input safely.
 *
 * Prompts the user and reads a line of text into the provided buffer.
 * Ensures the string is null-terminated and removes trailing newline characters.
 *
 * @param prompt Prompt message displayed to the user.
 * @param out Destination buffer for the input string.
 * @param out_size Size of the destination buffer.
 */
void input_read_string(const char *prompt, char *out, size_t out_size) {
    if (out == NULL || out_size == 0) {
        return;
    }

    if (prompt != NULL) {
        printf("%s", prompt);
    }

    if (fgets(out, (int)out_size, stdin) == NULL) {
        out[0] = '\0';
        return;
    }

    trim_newline(out);
}

/**
 * @brief Reads and discards a line of input.
 *
 * Consumes a small amount of input from stdin and ignores it.
 * Useful for clearing residual input in specific cases.
 */
void input_read_line_discard(void) {
    char buf[8];
    (void)fgets(buf, (int)sizeof(buf), stdin);
}