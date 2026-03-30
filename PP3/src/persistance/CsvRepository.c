/**
 * CST8002 Programming Language Research Project
 * Practical Project Part 02 – Project Review I
 *
 * Author: Ziming Zhao 041166304
 * Professor: Stanley Pieda
 * Due Date: 2026-02-22
 *
 * Description:
 * Implements CSV reading and writing for Record objects.
 * Reads line-by-line using fgets, skips a header row, and parses 4 columns:
 * Visit date, Site identification, Species, Total Black oystercatcher adults.
 * Writes CSV output with a header row.
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

/* ---- local helpers ---- */

/**
 * Trims trailing newline characters from a string.
 *
 * @param s String to trim.
 */
static void trim_newline(char *s) {
    size_t n = strlen(s);
    while (n > 0 && (s[n - 1] == '\n' || s[n - 1] == '\r')) {
        s[n - 1] = '\0';
        n--;
    }
}

/**
 * Checks if a line looks like the dataset header.
 *
 * @param line CSV line.
 * @return 1 if header, 0 otherwise.
 */
static int is_header_line(const char *line) {
    if (line == NULL) return 0;
    /* Very simple check based on known column names */
    return (strstr(line, "Visit date") != NULL) &&
           (strstr(line, "Site identification") != NULL) &&
           (strstr(line, "Species") != NULL);
}

/**
 * Copies a source C-string safely into a destination buffer.
 *
 * @param dst Destination buffer.
 * @param dst_size Destination buffer size.
 * @param src Source string (may be NULL).
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
 * Parses one CSV data line into a Record.
 * Assumes 4 columns separated by commas, no quoted commas.
 *
 * @param line CSV line (will be modified).
 * @param out_record Output Record.
 * @return 0 on success, non-zero on parse failure.
 */
static int parse_record_line(char *line, Record *out_record) {
    if (line == NULL || out_record == NULL) return 1;

    /* Split into 4 tokens */
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
        /* Not enough columns */
        return 2;
    }

    /* There might still be commas in the last field if CSV has extra columns (shouldn't here).
       We accept only the first 4 columns. */

    copy_field(out_record->visit_date, sizeof(out_record->visit_date), tokens[0]);
    copy_field(out_record->site_identification, sizeof(out_record->site_identification), tokens[1]);
    copy_field(out_record->species, sizeof(out_record->species), tokens[2]);

    /* Parse int field (trim spaces) */
    {
        char *s = tokens[3];
        while (*s && isspace((unsigned char)*s)) s++;
        out_record->total_black_oystercatcher_adults = atoi(s);
    }

    return 0;
}

/**
 * Ensures the output directory exists when saving to "output/...".
 *
 * @param path Output path.
 */
static void ensure_output_dir(const char *path) {
    if (path == NULL) return;

    /* only handle the common assignment case */
    if (strncmp(path, "output/", 7) == 0 || strncmp(path, "output\\", 7) == 0) {
#ifdef _WIN32
        _mkdir("output"); /* returns -1 if exists; ok */
#else
        mkdir("output", 0777); /* returns -1 if exists; ok */
#endif
    }
}

/* ---- public functions ---- */

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
        return 2; /* file missing / cannot open */
    }

    while (fgets(line, sizeof(line), fp) != NULL) {
        trim_newline(line);

        /* Skip empty lines */
        if (line[0] == '\0') {
            continue;
        }

        /* Skip header (either first line if it matches, or first non-empty line) */
        if (!header_skipped) {
            if (is_header_line(line)) {
                header_skipped = 1;
                continue;
            }
            /* If it doesn't look like a header, still treat the first line as header per dataset note */
            header_skipped = 1;
            /* If you want to treat first line as data when no header, comment the next continue out. */
            continue;
        }

        if (count >= n || count >= max_out) {
            break;
        }

        record_init(&out[count]);

        /* parse modifies the line, so pass a writable buffer */
        if (parse_record_line(line, &out[count]) == 0) {
            count++;
        } else {
            /* skip bad line */
            continue;
        }
    }

    fclose(fp);

    if (out_count != NULL) {
        *out_count = count;
    }
    return 0;
}

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

    /* header row */
    fprintf(fp, "Visit date,Site identification,Species,Total Black oystercatcher adults\n");

    for (size_t i = 0; i < count; i++) {
        /* No quoting/escaping implemented (dataset and your inputs should avoid commas). */
        fprintf(fp, "%s,%s,%s,%d\n",
                records[i].visit_date,
                records[i].site_identification,
                records[i].species,
                records[i].total_black_oystercatcher_adults);
    }

    fclose(fp);
    return 0;
}