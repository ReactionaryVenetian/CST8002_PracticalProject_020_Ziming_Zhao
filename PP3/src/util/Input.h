/**
 * CST8002 Programming Language Research Project
 * Practical Project Part 02 – Project Review I
 *
 * Author: Ziming Zhao 041166304
 * Professor: Stanley Pieda
 * Due Date: 2026-02-22
 *
 * Description:
 * Utility functions for reading user input safely from stdin.
 * Reuses the clear_input_line and newline trimming approach from PP1.
 * 
 * Sources: nothing new. Refactored from PP1's Functions.c, just moved the input-related functions here for better organization.
 */

#ifndef INPUT_H
#define INPUT_H

#include <stddef.h>

/**
 * Clears remaining characters from stdin up to and including the next newline.
 * Used after scanf to prevent leftover characters from affecting the next read.
 */
void clear_input_line(void);

/**
 * Reads an integer from stdin with a prompt. Re-prompts until valid.
 *
 * @param prompt Prompt text displayed to the user.
 * @return The integer entered.
 */
int input_read_int(const char *prompt);

/**
 * Reads a line of text (possibly containing spaces) from stdin with a prompt.
 * The returned string will not contain trailing newline characters.
 *
 * @param prompt Prompt text displayed to the user.
 * @param out Output buffer to store the string.
 * @param out_size Size of output buffer.
 */
void input_read_string(const char *prompt, char *out, size_t out_size);

/**
 * Reads and discards one line (used for "Press Enter to continue" behavior).
 */
void input_read_line_discard(void);

#endif /* INPUT_H */