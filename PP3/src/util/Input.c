/**
 * CST8002 Programming Language Research Project
 * Practical Project Part 02 – Project Review I
 *
 * Author: Ziming Zhao 041166304
 * Professor: Stanley Pieda
 * Due Date: 2026-02-22
 *
 * Description:
 * Implements utility functions for reading user input safely.
 * Reuses the clear_input_line and trim_newline approach from PP1.
 * 
 * Sources: nothing new. Refactored from PP1's Functions.c, just moved the input-related functions here for better organization.
 */

#include "Input.h"

#include <stdio.h>
#include <string.h>

/**
 * Clears remaining characters from the input buffer (waiting in stdin).
 * Used to prevent invalid input from affecting subsequent reads in the menu.
 */
void clear_input_line(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        /* discard */
    }
}

/**
 * Trims newline characters from the end of a string.
 *
 * @param s Null-terminated string to trim.
 */
static void trim_newline(char *s) {
    size_t n = strlen(s);
    while (n > 0 && (s[n - 1] == '\n' || s[n - 1] == '\r')) {
        s[n - 1] = '\0';
        n--;
    }
}

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

void input_read_string(const char *prompt, char *out, size_t out_size) {
    if (out == NULL || out_size == 0) {
        return;
    }

    if (prompt != NULL) {
        printf("%s", prompt);
    }

    if (fgets(out, (int)out_size, stdin) == NULL) {
        /* if stdin closed, return empty string */
        out[0] = '\0';
        return;
    }

    trim_newline(out);
}

void input_read_line_discard(void) {
    char buf[8];
    (void)fgets(buf, (int)sizeof(buf), stdin);
}