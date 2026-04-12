/**
 * @file Records.c
 * @brief Implements business logic for managing Record objects.
 *
 * CST8002 Programming Language Research Project
 * Practical Project Part 03 – Algorithmic manipulation of Structs
 *
 * Author: Ziming Zhao 041166304
 * Professor: Stanley Pieda
 * Due Date: 2026-03-29
 *
 *
 * Description:
 * This module maintains an in-memory sequential data structure
 * and performs CRUD operations and now apparently statistical analysis.
 * Persistence is delegated to the CsvRepository module. My name is
 * included cause I'm vain.
 * 
 * New References: 
 * [1]GeeksforGeeks, “qsort() Function in C,” GeeksforGeeks, Apr. 14, 2024. 
 * https://www.geeksforgeeks.org/c/qsort-function-in-c/
 * [Accessed: Mar. 29, 2026]. Welp, turns out there's not many built in algorithms 
 * for in C, so I guess I'll write my own. 
 * 
 * [2]w3schools “C Math,” www.w3schools.com, unknown update.
 *  https://www.w3schools.com/c/c_math.php
‌ * [Accessed: Mar. 29, 2026]. Here's to me remembering simple statistical things. 
 * 
 */

#include "Records.h"
#include <plplot/plplot.h>

#include <stdio.h>
#include <string.h>

/** required for sqrt and qsort */
#include <stdlib.h>
#include <math.h>

#include "../persistance/CsvRepository.h" //lol, I misspelled persistance 
#include "../util/Misc.h"
#include "../util/Input.h"


#define MAX_RECORDS 1000

/** @brief Global in-memory array of records. */
static Record g_records[MAX_RECORDS];

/** @brief Current number of records stored. */
static size_t g_count = 0;


/**
 * @brief Reloads records from the dataset file into memory.
 *
 * Reads up to a fixed number of records from the CSV dataset and stores
 * them in the in-memory collection.
 *
 * @param dataset_path Path to the CSV dataset file.
 * @return int 0 on success, non-zero error code on failure.
 */

int records_reload(const char *dataset_path) {
    size_t loaded = 0;

    if (dataset_path == NULL) {
        return 1;
    }

    int rc = csv_load_first_n(dataset_path, g_records, MAX_RECORDS, 100, &loaded);
    if (rc != 0) {
        g_count = 0;
        return rc;
    }

    g_count = loaded;
    return 0;
}


/**
 * @brief Saves all records to a new CSV file with a generated UUID filename.
 *
 * Uses a UUID to create a unique output filename and persists all records
 * currently stored in memory.
 *
 * @return int 0 on success, non-zero error code on failure.
 */


int records_save_to_uuid_csv(void) {
    char uuid[128];
    char path[256];

    if (uuid_generate_v4(uuid, sizeof(uuid)) != 0) {
        return 1;
    }

    snprintf(path, sizeof(path), "output/records_%s.csv", uuid);
    return csv_save_all(path, g_records, g_count);
}

/**
 * @brief Returns the number of records currently stored in memory.
 *
 * @return size_t Number of records.
 */

size_t records_count(void) {
    return g_count;
}

/**
 * @brief Retrieves a record at the specified index.
 *
 * Copies the record at the given index into the provided output pointer.
 *
 * @param index Index of the record to retrieve.
 * @param out_record Pointer to store the retrieved record.
 * @return int 0 on success, error code if index or pointer is invalid.
 */

int records_get(size_t index, Record *out_record) {
    if (out_record == NULL) {
        return 1;
    }
    if (index >= g_count) {
        return 2;
    }

    *out_record = g_records[index];
    return 0;
}

/**
 * @brief Adds a new record to the in-memory collection.
 *
 * Appends the given record to the end of the collection if space permits.
 *
 * @param record Pointer to the record to add.
 * @return int 0 on success, error code if input is invalid or storage is full.
 */

int records_add(const Record *record) {
    if (record == NULL) {
        return 1;
    }
    if (g_count >= MAX_RECORDS) {
        return 2;
    }

    g_records[g_count++] = *record;
    return 0;
}

/**
 * @brief Updates an existing record at the specified index.
 *
 * Replaces the record at the given index with the provided record.
 *
 * @param index Index of the record to update.
 * @param record Pointer to the new record data.
 * @return int 0 on success, error code if input is invalid.
 */

int records_update(size_t index, const Record *record) {
    if (record == NULL) {
        return 1;
    }
    if (index >= g_count) {
        return 2;
    }

    g_records[index] = *record;
    return 0;
}

/**
 * @brief Deletes a record at the specified index.
 *
 * Removes the record and shifts all subsequent records left.
 *
 * @param index Index of the record to delete.
 * @return int 0 on success, error code if index is invalid.
 */

int records_delete(size_t index) {
    if (index >= g_count) {
        return 1;
    }

    for (size_t i = index; i + 1 < g_count; i++) {
        g_records[i] = g_records[i + 1];
    }

    g_count--;
    return 0;
}

/* -------- Start of interactive functions -------- */

/**
 * @brief Displays all records currently stored in memory.
 *
 * Outputs each record in a formatted list to the console.
 */

void records_display_all(void) {
    printf("Program by Ziming Zhao\n");
    printf("Records in memory: %zu\n\n", g_count);

    for (size_t i = 0; i < g_count; i++) {
        if (i % 10 == 0) {
            printf("Program by Ziming Zhao\n");
        }

        printf("[%zu] %s | %s | %s | %d\n",
               i,
               g_records[i].visit_date,
               g_records[i].site_identification,
               g_records[i].species,
               g_records[i].total_black_oystercatcher_adults);
    }
}

/**
 * @brief Prompts the user to input and add a new record.
 *
 * Collects input from the user and inserts a new record into memory.
 */

void records_add_interactive(void) {
    Record r;
    record_init(&r);

    input_read_string("Visit date: ", r.visit_date, sizeof(r.visit_date));
    input_read_string("Site identification: ", r.site_identification, sizeof(r.site_identification));
    input_read_string("Species: ", r.species, sizeof(r.species));
    r.total_black_oystercatcher_adults =
        input_read_int("Total Black oystercatcher adults: ");

    if (records_add(&r) == 0) {
        printf("Record added successfully.\n");
    } else {
        printf("Failed to add record.\n");
    }
}

/**
 * @brief Prompts the user to edit an existing record.
 *
 * Allows modification of a record selected by index.
 */

void records_edit_interactive(void) {
    if (g_count == 0) {
        printf("No records available.\n");
        return;
    }

    int idx = input_read_int("Enter record index to edit: ");
    if (idx < 0 || (size_t)idx >= g_count) {
        printf("Invalid index.\n");
        return;
    }

    Record r = g_records[idx];

    input_read_string("Visit date: ", r.visit_date, sizeof(r.visit_date));
    input_read_string("Site identification: ", r.site_identification, sizeof(r.site_identification));
    input_read_string("Species: ", r.species, sizeof(r.species));
    r.total_black_oystercatcher_adults =
        input_read_int("Total Black oystercatcher adults: ");

    records_update((size_t)idx, &r);
    printf("Record updated.\n");
}

/**
 * @brief Prompts the user to delete a record.
 *
 * Removes a record selected by index from the collection.
 */

void records_delete_interactive(void) {
    if (g_count == 0) {
        printf("No records available.\n");
        return;
    }

    int idx = input_read_int("Enter record index to delete: ");
    if (idx < 0 || (size_t)idx >= g_count) {
        printf("Invalid index.\n");
        return;
    }

    records_delete((size_t)idx);
    printf("Record deleted.\n");
}

/* -------- Start of PP3 algorithm functions -------- */

/**
 * @brief Calculates the average number of adults across all records.
 *
 * @return double Average value, or 0.0 if no records exist.
 */

double records_average_adults(void) {
    size_t i;
    int sum = 0;

    if (g_count == 0) {
        return 0.0;
    }

    for (i = 0; i < g_count; i++) {
        sum += g_records[i].total_black_oystercatcher_adults;
    }

    return (double)sum / (double)g_count;
}

/**
 * @brief Finds the minimum number of adults across all records.
 *
 * @return int Minimum value, or 0 if no records exist.
 */

int records_min_adults(void) {
    size_t i;
    int min_value;

    if (g_count == 0) {
        return 0;
    }

    min_value = g_records[0].total_black_oystercatcher_adults;

    for (i = 1; i < g_count; i++) {
        if (g_records[i].total_black_oystercatcher_adults < min_value) {
            min_value = g_records[i].total_black_oystercatcher_adults;
        }
    }

    return min_value;
}

/**
 * @brief Finds the maximum number of adults across all records.
 *
 * @return int Maximum value, or 0 if no records exist.
 */
int records_max_adults(void) {
    size_t i;
    int max_value;

    if (g_count == 0) {
        return 0;
    }

    max_value = g_records[0].total_black_oystercatcher_adults;

    for (i = 1; i < g_count; i++) {
        if (g_records[i].total_black_oystercatcher_adults > max_value) {
            max_value = g_records[i].total_black_oystercatcher_adults;
        }
    }

    return max_value;
}

/**
 * @brief Comparator for sorting records in ascending order by adults.
 *
 * Used by qsort() to order records from lowest to highest.
 *
 * @param a Pointer to first record.
 * @param b Pointer to second record.
 * @return int Negative if a < b, positive if a > b, zero if equal.
 */

static int compare_adults_ascending(const void *a, const void *b) {
    const Record *record_a = (const Record *)a;
    const Record *record_b = (const Record *)b;

    if (record_a->total_black_oystercatcher_adults < record_b->total_black_oystercatcher_adults) {
        return -1;
    }
    if (record_a->total_black_oystercatcher_adults > record_b->total_black_oystercatcher_adults) {
        return 1;
    }
    return 0;
}

/**
 * Compares two records for descending sort by Total Black oystercatcher adults.
 *
 * @param a first record
 * @param b second record
 * @return comparison result
 */

static int compare_adults_descending(const void *a, const void *b) {
    const Record *record_a = (const Record *)a;
    const Record *record_b = (const Record *)b;

    if (record_a->total_black_oystercatcher_adults < record_b->total_black_oystercatcher_adults) {
        return 1;
    }
    if (record_a->total_black_oystercatcher_adults > record_b->total_black_oystercatcher_adults) {
        return -1;
    }
    return 0;
}

/**
 * @brief Sorts records in ascending order by Total Black oystercatcher adults.
 *
 * Uses qsort() with a custom comparator to order records from lowest to highest.
 */
void records_sort_by_adults_ascending(void) {
    if (g_count > 1) {
        qsort(g_records, g_count, sizeof(Record), compare_adults_ascending);
    }
}

/**
 * @brief Sorts records in descending order by Total Black oystercatcher adults.
 *
 * Uses qsort() with a custom comparator to order records from highest to lowest.
 */
void records_sort_by_adults_descending(void) {
    if (g_count > 1) {
        qsort(g_records, g_count, sizeof(Record), compare_adults_descending);
    }
}

/**
 * @brief Displays a histogram of adult counts.
 *
 * Groups records into predefined buckets and prints a visual distribution.
 * Buckets: 0-5, 6-10, 11-15, 16-20, 21+
 */
 
void records_display_histogram(void) {
    int buckets[5] = {0, 0, 0, 0, 0};
    size_t i;
    int value;
    int j;

    if (g_count == 0) {
        printf("No records loaded.\n");
        return;
    }

    for (i = 0; i < g_count; i++) {
        value = g_records[i].total_black_oystercatcher_adults;

        if (value <= 5) {
            buckets[0]++;
        } else if (value <= 10) {
            buckets[1]++;
        } else if (value <= 15) {
            buckets[2]++;
        } else if (value <= 20) {
            buckets[3]++;
        } else {
            buckets[4]++;
        }
    }

    printf("\nHistogram of Total Black oystercatcher adults\n");
    printf("---------------------------------------------\n");

    printf("0-5   : ");
    for (j = 0; j < buckets[0]; j++) {
        printf("*");
    }
    printf(" (%d)\n", buckets[0]);

    printf("6-10  : ");
    for (j = 0; j < buckets[1]; j++) {
        printf("*");
    }
    printf(" (%d)\n", buckets[1]);

    printf("11-15 : ");
    for (j = 0; j < buckets[2]; j++) {
        printf("*");
    }
    printf(" (%d)\n", buckets[2]);

    printf("16-20 : ");
    for (j = 0; j < buckets[3]; j++) {
        printf("*");
    }
    printf(" (%d)\n", buckets[3]);

    printf("21+   : ");
    for (j = 0; j < buckets[4]; j++) {
        printf("*");
    }
    printf(" (%d)\n", buckets[4]);
}

/**
 * @brief Displays summary statistics for all records.
 *
 * Includes count, average, minimum, and maximum values.
 */
void records_display_analysis(void) {
    if (g_count == 0) {
        printf("No records loaded.\n");
        return;
    }

    printf("\nRecord Analysis\n");
    printf("---------------\n");
    printf("Count   : %zu\n", g_count);
    printf("Average : %.2f\n", records_average_adults());
    printf("Min     : %d\n", records_min_adults());
    printf("Max     : %d\n", records_max_adults());
}

/**
 * @brief Displays records with adults greater than or equal to a threshold.
 *
 * Performs a linear search through all records in memory and prints
 * only those where the Total Black oystercatcher adults value meets
 * or exceeds the specified threshold.
 *
 * @param threshold Minimum number of adults to filter records.
 */
void records_search_by_min_adults(int threshold) {
    for (size_t i = 0; i < g_count; i++) {
        if (g_records[i].total_black_oystercatcher_adults >= threshold) {
            printf("[%zu] %s | %s | %s | %d\n",
                i,
                g_records[i].visit_date,
                g_records[i].site_identification,
                g_records[i].species,
                g_records[i].total_black_oystercatcher_adults);
        }
    }
}

/**
 * @brief Counts how many records match a given species.
 *
 * Performs a linear scan of all records and compares the species field
 * using strcmp(). Only exact matches are counted.
 *
 * @param species Species name to search for.
 */
void records_count_species(const char *species) {
    int count = 0;

    for (size_t i = 0; i < g_count; i++) {
        if (strcmp(g_records[i].species, species) == 0) {
            count++;
        }
    }

    printf("Species '%s' count: %d\n", species, count);
}

/**
 * @brief Calculates the standard deviation of adult counts.
 *
 * Computes the standard deviation of Total Black oystercatcher adults
 * across all records by first calculating the average and then summing
 * the squared differences from that average.
 *
 * @return double Standard deviation value, or 0.0 if no records exist.
 */
double records_stddev(void) {
    double avg = records_average_adults();
    double sum = 0.0;

    for (size_t i = 0; i < g_count; i++) {
        double diff = g_records[i].total_black_oystercatcher_adults - avg;
        sum += diff * diff;
    }

    return sqrt(sum / g_count);
}


/**
 *  depreciated, ugly, manual, and unintuitive.            
 * @brief Displays a graphical histogram using PLplot.
 *
void records_display_graphical_histogram(void) {
    int buckets[5] = {0, 0, 0, 0, 0};
    size_t i;
    int value;
    
    if (g_count == 0) {
        printf("No records loaded.\n");
        return;
    }
    
    // Calculate bucket counts
    for (i = 0; i < g_count; i++) {
        value = g_records[i].total_black_oystercatcher_adults;
        
        if (value <= 5) {
            buckets[0]++;
        } else if (value <= 10) {
            buckets[1]++;
        } else if (value <= 15) {
            buckets[2]++;
        } else if (value <= 20) {
            buckets[3]++;
        } else {
            buckets[4]++;
        }
    }
    
    // Find max for scaling
    int max_count = 0;
    for (i = 0; i < 5; i++) {
        if (buckets[i] > max_count) max_count = buckets[i];
    }
    
    if (max_count == 0) max_count = 1;
    
    // Initialize PLplot
    plinit();
    
    // Set up the plot - this creates the axes
    plenv(0.0, 5.0, 0.0, (double)max_count * 1.2, 1, 0);
    
    // Label the axes
    pllab("Bucket", "Count", "Black Oystercatcher Adults Distribution");
    
    // Draw bars using simple lines
    for (i = 0; i < 5; i++) {
        double x_left = i + 0.3;
        double x_right = i + 0.7;
        double y_top = (double)buckets[i];
        
        // Draw the bar as a filled rectangle using plfill with 4 points
        if (buckets[i] > 0) {
            double x[4] = {x_left, x_right, x_right, x_left};
            double y[4] = {0.0, 0.0, y_top, y_top};
            
            plcol0(2);  // Red color for bars
            plfill(4, x, y);
            plcol0(1);  // Black for outline
            plline(4, x, y);
        }
    }
    
    // Add labels under each bar
    char* labels[] = {"0-5", "6-10", "11-15", "16-20", "21+"};
    for (i = 0; i < 5; i++) {
        plptex(i + 0.5, -0.5, 0.0, 0.5, 0.0, labels[i]);
    }
    
    // Add count numbers on top of bars
    for (i = 0; i < 5; i++) {
        if (buckets[i] > 0) {
            char text[10];
            sprintf(text, "%d", buckets[i]);
            plptex(i + 0.5, buckets[i] + 0.2, 0.0, 0.5, 0.0, text);
        }
    }
    
    plend();
    
    printf("\nGraphical histogram generated!\n");
}*/