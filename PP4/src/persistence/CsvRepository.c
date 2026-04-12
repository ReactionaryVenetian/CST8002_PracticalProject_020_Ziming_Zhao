/**
 * @file CsvRepository.c
 * @brief Implements CSV reading and writing for Record objects.
 *
 * CST8002 Programming Language Research Project
 * Practical Project Part 04 – multi-column sorting and additional features
 *
 * Author: Ziming Zhao 041166304
 * Professor: Stanley Pieda
 * Due Date: 2026-04-12
 *
 * Description:
 * This module provides persistence operations for Record objects using
 * CSV file input and output. It reads records line-by-line using fgets(),
 * skips the header row, parses four expected columns, and writes records
 * back to CSV format with a header row.
 *
 * References:
 * [1] cppreference.com, "fopen," C standard library reference.
 *     [Online]. Available: https://en.cppreference.com/w/c/io/fopen
 *     [Accessed: Feb. 22, 2026].
 *
 * [2] cppreference.com, "fgets," C standard library reference.
 *     [Online]. Available: https://en.cppreference.com/w/c/io/fgets
 *     [Accessed: Feb. 22, 2026].
 *
 * [3] cppreference.com, "fprintf," C standard library reference.
 *     [Online]. Available: https://en.cppreference.com/w/c/io/fprintf
 *     [Accessed: Feb. 22, 2026].
 */

#include "CsvRepository.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#ifdef _WIN32
#include <direct.h>   /* _mkdir */
#else
#include <sys/stat.h> /* mkdir */
#include <sys/types.h>
#endif

#define LINE_BUF 4096

/* ---- Local helper functions ---- */

/**
 * @brief Removes trailing newline and carriage return characters from a string.
 *
 * This function trims '\n' and '\r' characters from the end of a
 * null-terminated C string.
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
 * @brief Determines whether a CSV line appears to be the dataset header.
 *
 * Checks for the expected dataset column names within the given line.
 *
 * @param line Pointer to the CSV line to inspect.
 * @return int Returns 1 if the line appears to be a header row, otherwise 0.
 */
static int is_header_line(const char *line) {
    if (line == NULL) return 0;

    return (strstr(line, "Visit date") != NULL) &&
           (strstr(line, "Site identification") != NULL) &&
           (strstr(line, "Species") != NULL);
}

/**
 * @brief Safely copies a source string into a destination buffer.
 *
 * Copies up to dst_size - 1 characters from the source string into the
 * destination buffer and ensures null termination.
 *
 * @param dst Pointer to the destination buffer.
 * @param dst_size Size of the destination buffer.
 * @param src Pointer to the source string. May be NULL.
 */
static void copy_field(char *dst, size_t dst_size, const char *src) {
    if (dst == NULL || dst_size == 0) return;

    if (src == NULL) {
        dst[0] = '\0';
        return;
    }

    strncpy(dst, src, dst_size - 1);
    dst[dst_size - 1] = '\0';
}

/**
 * @brief Parses a single CSV data line into a Record object.
 *
 * This function splits a writable CSV line into four expected fields:
 * Visit date, Site identification, Species, and
 * Total Black oystercatcher adults.
 *
 * The function assumes:
 * - fields are separated by commas
 * - the input line may be modified
 * - quoted commas are not supported
 *
 * @param line Pointer to the writable CSV line buffer.
 * @param out_record Pointer to the Record structure to populate.
 * @return int Returns 0 on success, or non-zero on parse failure.
 */
static int parse_record_line(char *line, Record *out_record) {
    if (line == NULL || out_record == NULL) return 1;

    char *tokens[4] = {0};
    int t = 0;

    char *p = line;
    while (t < 4) {
        tokens[t++] = p;
        char *comma = strchr(p, ',');
        if (comma == NULL) break;
        *comma = '\0';
        p = comma + 1;
    }

    if (t < 4) {
        return 2;
    }

    copy_field(out_record->visit_date, sizeof(out_record->visit_date), tokens[0]);
    copy_field(out_record->site_identification, sizeof(out_record->site_identification), tokens[1]);
    copy_field(out_record->species, sizeof(out_record->species), tokens[2]);

    {
        char *s = tokens[3];
        while (*s && isspace((unsigned char)*s)) s++;
        out_record->total_black_oystercatcher_adults = atoi(s);
    }

    return 0;
}

/**
 * @brief Ensures that the output directory exists before saving a file.
 *
 * This function handles the common assignment case of saving files to
 * an "output" directory. If the directory already exists, the attempt
 * to create it is ignored.
 *
 * @param path Path of the output file being saved.
 */
static void ensure_output_dir(const char *path) {
    if (path == NULL) return;

    if (strncmp(path, "output/", 7) == 0 || strncmp(path, "output\\", 7) == 0) {
#ifdef _WIN32
        _mkdir("output");
#else
        mkdir("output", 0777);
#endif
    }
}

/* ---- Public functions ---- */

/**
 * @brief Loads up to n records from a CSV file into an output array.
 *
 * This function opens the specified CSV file, skips the header row,
 * parses each data line into a Record object, and stores the results
 * in the provided output array.
 *
 * The number of records loaded is limited by:
 * - n
 * - max_out
 * - the number of valid rows in the file
 *
 * @param path Path to the CSV file to read.
 * @param out Pointer to the output Record array.
 * @param max_out Maximum capacity of the output array.
 * @param n Maximum number of records to load.
 * @param out_count Pointer to store the actual number of records loaded.
 * @return int Returns 0 on success, or non-zero on error.
 */
int csv_load_first_n(const char *path,
                     Record *out,
                     size_t max_out,
                     size_t n,
                     size_t *out_count) {
    FILE *fp;
    char line[LINE_BUF];
    size_t count = 0;
    int header_skipped = 0;

    if (out_count != NULL) {
        *out_count = 0;
    }
    if (path == NULL || out == NULL || max_out == 0) {
        return 1;
    }

    fp = fopen(path, "r");
    if (fp == NULL) {
        return 2;
    }

    while (fgets(line, sizeof(line), fp) != NULL) {
        trim_newline(line);

        if (line[0] == '\0') {
            continue;
        }

        if (!header_skipped) {
            if (is_header_line(line)) {
                header_skipped = 1;
                continue;
            }
            header_skipped = 1;
            continue;
        }

        if (count >= n || count >= max_out) {
            break;
        }

        record_init(&out[count]);

        if (parse_record_line(line, &out[count]) == 0) {
            count++;
        } else {
            continue;
        }
    }

    fclose(fp);

    if (out_count != NULL) {
        *out_count = count;
    }
    return 0;
}

/**
 * @brief Saves all records to a CSV file.
 *
 * This function writes a header row followed by all records from the
 * provided Record array into the specified CSV file.
 *
 * @param path Path to the CSV file to create.
 * @param records Pointer to the array of Record objects to save.
 * @param count Number of records to write.
 * @return int Returns 0 on success, or non-zero on error.
 */
int csv_save_all(const char *path, const Record *records, size_t count) {
    FILE *fp;

    if (path == NULL || records == NULL) {
        return 1;
    }

    ensure_output_dir(path);

    fp = fopen(path, "w");
    if (fp == NULL) {
        return 2;
    }

    fprintf(fp, "Visit date,Site identification,Species,Total Black oystercatcher adults\n");

    for (size_t i = 0; i < count; i++) {
        fprintf(fp, "%s,%s,%s,%d\n",
                records[i].visit_date,
                records[i].site_identification,
                records[i].species,
                records[i].total_black_oystercatcher_adults);
    }

    fclose(fp);
    return 0;
}