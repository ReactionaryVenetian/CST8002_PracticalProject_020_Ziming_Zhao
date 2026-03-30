/**
 * @file Record.c
 * @brief Implements Record initialization.
 *
 * CST8002 Programming Language Research Project
 * Practical Project Part 03 – Algorithmic manipulation of Structs
 *
 * Author: Ziming Zhao 041166304
 * Professor: Stanley Pieda
 * Due Date: 2026-03-29
 * 
 * References: Nothing new here, just assigning default values to the struct fields.
 */

#include "Record.h"

/**
 * @brief Initializes all fields of a Record to default values.
 *
 * @param r Pointer to Record to initialize.
 */
void record_init(Record *r) {
    if (r == NULL) {
        return;
    }

    r->visit_date[0] = '\0';
    r->site_identification[0] = '\0';
    r->species[0] = '\0';
    r->total_black_oystercatcher_adults = 0;
}