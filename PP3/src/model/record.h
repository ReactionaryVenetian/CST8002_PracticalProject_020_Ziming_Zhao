/**
 * @file Record.h
 * @brief Defines the Record entity using dataset column names.
 *
 * CST8002 Programming Language Research Project
 * Practical Project Part 03 – Algorithmic manipulation of Structs
 *
 * Author: Ziming Zhao 041166304
 * Professor: Stanley Pieda
 * Due Date: 2026-03-29
 *
 * Description:
 * Dataset columns used as identifiers (C-safe):
 * - Visit date -> visit_date
 * - Site identification -> site_identification
 * - Species -> species
 * - Total Black oystercatcher adults -> total_black_oystercatcher_adults
 * 
 * References: Nothing new here, just a refactor of the previous DTO.
 */

#ifndef RECORD_H
#define RECORD_H

#include <stddef.h>

/**
 * @brief Entity representing one dataset row.
 */
typedef struct {
    char visit_date[32];
    char site_identification[128];
    char species[128];
    int  total_black_oystercatcher_adults;
} Record;

/**
 * @brief Initializes a Record to safe default values.
 *
 * @param r Pointer to Record to initialize.
 */
void record_init(Record *r);

#endif /* RECORD_H */