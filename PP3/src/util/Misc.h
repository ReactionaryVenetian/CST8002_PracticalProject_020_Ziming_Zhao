/**
 * CST8002 Programming Language Research Project
 * Practical Project Part 02 – Project Review I
 *
 * Author: Ziming Zhao 041166304
 * Professor: Stanley Pieda
 * Due Date: 2026-02-22
 *
 * Description:
 * Utility functions including UUID generation using libuuid.
 *
 * References:
 * [1] Stack Overflow, "Generating a random UUID in C," Stack Overflow, 2018.
 *     [Online]. Available: https://stackoverflow.com/questions/51053568/generating-a-random-uuid-in-c
 *     [Accessed: Feb. 22, 2026]. Not really implemented here except for the interface.
 */

#ifndef MISC_H
#define MISC_H

#include <stddef.h>

/**
 * Generates a UUID v4 string.
 *
 * @param out Buffer to store UUID string (must be >= 37 bytes).
 * @param out_size Size of buffer.
 * @return 0 on success, non-zero on failure.
 */
int uuid_generate_v4(char *out, size_t out_size);

#endif /* MISC_H */