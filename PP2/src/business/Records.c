/**
 * @file Records.c
 * @brief Implements business logic for managing Record objects.
 *
 * CST8002 Programming Language Research Project
 * Practical Project Part 02 – Project Review I
 *
 * Author: Ziming Zhao 041166304
 * Professor: Stanley Pieda
 * Due Date: 2026-02-22
 *
 * Description:
 * This module maintains an in-memory sequential data structure
 * and performs CRUD operations. Persistence is delegated to
 * the CsvRepository module. My name is included cause I'm vain.
 * 
 * References: 
 * [1] Stack Overflow, "Generating a random UUID in C," Stack Overflow, 2018. 
 * [Online]. Available: https://stackoverflow.com/questions/51053568/generating-a-random-uuid-in-c
 * [Accessed: Feb. 22, 2026]. Welp, I needed a UUID generator for the save function, 
 * and this was the best C implementation I could find. I adapted it to fit my needs and included it in the Misc utility module.
 * 
 */

#include "Records.h"

#include <stdio.h>
#include <string.h>

#include "../persistance/CsvRepository.h" //lol, I misspelled persistance 
#include "../util/Misc.h"
#include "../util/Input.h"


#define MAX_RECORDS 1000

/** @brief Global in-memory array of records. */
static Record g_records[MAX_RECORDS];

/** @brief Current number of records stored. */
static size_t g_count = 0;

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

int records_save_to_uuid_csv(void) {
    char uuid[128];
    char path[256];

    if (uuid_generate_v4(uuid, sizeof(uuid)) != 0) {
        return 1;
    }

    snprintf(path, sizeof(path), "output/records_%s.csv", uuid);
    return csv_save_all(path, g_records, g_count);
}

size_t records_count(void) {
    return g_count;
}

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

/* -------- Convenience interactive functions -------- */

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