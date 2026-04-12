/**
 * @file Records.h
 * @brief Business layer for managing in-memory Record objects.
 *
 * CST8002 Programming Language Research Project
 * Practical Project Part 04 – multi-column sorting and additional features
 *
 * Author: Ziming Zhao 041166304
 * Professor: Stanley Pieda
 * Due Date: 2026-04-12
 *
 * Description:
 * This module owns the sequential in-memory data structure
 * (an array of Record objects) and provides CRUD operations.
 * File I/O is delegated to the Persistence layer.
 *
 * References: Nothing too new here.
 */

#ifndef RECORDS_H
#define RECORDS_H

#include <stddef.h>
#include "../model/Record.h"

/**
 * @brief Reloads dataset into memory.
 *
 * Replaces the current in-memory records with data loaded
 * from the CSV dataset file.
 *
 * @param dataset_path Path to CSV dataset.
 * @return 0 on success, non-zero on failure.
 */
int records_reload(const char *dataset_path);

/**
 * @brief Saves in-memory records to a new CSV file.
 *
 * Generates a UUID filename and writes all records
 * to disk in CSV format.
 *
 * @return 0 on success, non-zero on failure.
 */
int records_save_to_uuid_csv(void);

/**
 * @brief Gets number of records currently in memory.
 *
 * @return Number of records stored.
 */
size_t records_count(void);

/**
 * @brief Retrieves a record by index.
 *
 * @param index Index of record.
 * @param out_record Pointer to store the record.
 * @return 0 on success, non-zero if invalid index.
 */
int records_get(size_t index, Record *out_record);

/**
 * @brief Adds a new record to memory.
 *
 * @param record Pointer to record to add.
 * @return 0 on success, non-zero if full or invalid.
 */
int records_add(const Record *record);

/**
 * @brief Updates an existing record.
 *
 * @param index Index to update.
 * @param record Pointer to updated record.
 * @return 0 on success, non-zero on error.
 */
int records_update(size_t index, const Record *record);

/**
 * @brief Deletes a record by index.
 *
 * @param index Index of record to remove.
 * @return 0 on success, non-zero if invalid index.
 */
int records_delete(size_t index);

/* --- Convenience methods used by Presentation layer --- */

/**
 * @brief Displays all records to stdout.
 */
void records_display_all(void);

/**
 * @brief Prompts user and adds a new record.
 */
void records_add_interactive(void);

/**
 * @brief Prompts user and edits a record.
 */
void records_edit_interactive(void);

/**
 * @brief Prompts user and deletes a record.
 */
void records_delete_interactive(void);

/* --- Algorithmic / Analysis Functions (PP3) --- */

/**
 * @brief Calculates the average number of adults across all records.
 *
 * @return double Average value, or 0.0 if no records exist.
 */
double records_average_adults(void);

/**
 * @brief Finds the minimum number of adults across all records.
 *
 * @return int Minimum value, or 0 if no records exist.
 */
int records_min_adults(void);

/**
 * @brief Finds the maximum number of adults across all records.
 *
 * @return int Maximum value, or 0 if no records exist.
 */
int records_max_adults(void);

/**
 * @brief Sorts records in ascending order by Total Black oystercatcher adults.
 *
 * Uses qsort() with a custom comparator to order records from lowest to highest.
 */
void records_sort_by_adults_ascending(void);

/**
 * @brief Sorts records in descending order by Total Black oystercatcher adults.
 *
 * Uses qsort() with a custom comparator to order records from highest to lowest.
 */
void records_sort_by_adults_descending(void);

/**
 * @brief Displays a histogram of adult counts.
 *
 * Groups records into predefined buckets and prints a visual distribution.
 */
void records_display_histogram(void);

/**
 * @brief Displays a graphical histogram of adult counts.
 *
 * Groups records into predefined buckets and prints a visual distribution.
 *
 */
void records_display_graphical_histogram(void);

/**
 * @brief Displays summary statistics for all records.
 *
 * Includes count, average, minimum, and maximum values.
 */
void records_display_analysis(void);

/**
 * @brief Displays records with adults greater than or equal to a threshold.
 *
 * Performs a linear search through all records and prints matches.
 *
 * @param threshold Minimum number of adults to filter by.
 */
void records_search_by_min_adults(int threshold);

/**
 * @brief Counts the number of records matching a given species.
 *
 * Performs a frequency count using string comparison on the species field.
 *
 * @param species Species name to search for.
 */
void records_count_species(const char *species);

/**
 * @brief Calculates the standard deviation of adult counts.
 *
 * Uses the average value and computes variance across all records.
 *
 * @return double Standard deviation, or 0.0 if no records exist.
 */
double records_stddev(void);


/**
 * @brief Sort keys available for multi-column sorting.
 */
typedef enum {
    SORT_BY_VISIT_DATE = 1,
    SORT_BY_SITE_IDENTIFICATION,
    SORT_BY_SPECIES,
    SORT_BY_TOTAL_BLACK_OYSTERCATCHER_ADULTS
} SortKey;

/**
 * @brief Sort order options.
 */
typedef enum {
    SORT_ASC = 1,
    SORT_DESC
} SortOrder;

/**
 * @brief Sorts records using up to three columns.
 *
 * The first key is the primary sort key. If two records are equal on the
 * first key, the second key is used. If still equal, the third key is used.
 *
 * @param primary_key First sort key.
 * @param secondary_key Second sort key.
 * @param tertiary_key Third sort key.
 * @param order Ascending or descending.
 */
void records_sort_multiple_columns(
    SortKey primary_key,
    SortKey secondary_key,
    SortKey tertiary_key,
    SortOrder order
);

#endif /* RECORDS_H */

