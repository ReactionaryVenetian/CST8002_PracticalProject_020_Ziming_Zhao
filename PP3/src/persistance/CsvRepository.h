/**
 * CST8002 Programming Language Research Project
 * Practical Project Part 02 – Project Review I
 *
 * Author: Ziming Zhao 041166304
 * Professor: Stanley Pieda
 * Due Date: 2026-02-22
 *
 * Description:
 * Persistence layer for reading and writing Record objects to CSV files.
 * Provides functions to load the first N records from a dataset and to
 * save all in-memory records to a new CSV file.
 *
 * References:
 * [1] cppreference.com, "fopen," C standard library reference.
 *     [Online]. Available: https://en.cppreference.com/w/c/io/fopen
 *     [Accessed: Feb. 22, 2026]. Used for opening files for reading and writing.
 *
 * [2] cppreference.com, "fgets," C standard library reference.
 *     [Online]. Available: https://en.cppreference.com/w/c/io/fgets
 *     [Accessed: Feb. 22, 2026].  Used for reading lines from the CSV file.
 *
 * [3] cppreference.com, "fprintf," C standard library reference.
 *     [Online]. Available: https://en.cppreference.com/w/c/io/fprintf
 *     [Accessed: Feb. 22, 2026].  Look I did this before, just me covering my ass.
 */

#ifndef CSV_REPOSITORY_H
#define CSV_REPOSITORY_H

#include <stddef.h>
#include "../model/Record.h"

/**
 * Loads up to the first N records from a CSV dataset file into an output array.
 * If the CSV has a header row, it should be skipped.
 *
 * @param path Path to CSV dataset file.
 * @param out Output array of Record.
 * @param max_out Maximum capacity of output array.
 * @param n Maximum number of records to load.
 * @param out_count Number of records actually loaded.
 * @return 0 on success, non-zero on failure.
 */
int csv_load_first_n(const char *path,
                     Record *out,
                     size_t max_out,
                     size_t n,
                     size_t *out_count);

/**
 * Saves all records to a CSV file at the given path.
 * Writes a header row followed by data rows.
 *
 * @param path Output file path.
 * @param records Array of Record to write.
 * @param count Number of records in the array.
 * @return 0 on success, non-zero on failure.
 */
int csv_save_all(const char *path, const Record *records, size_t count);

#endif /* CSV_REPOSITORY_H */