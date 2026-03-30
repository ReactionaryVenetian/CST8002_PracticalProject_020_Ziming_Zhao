/**
 * @file sorter.c
 * @brief Implementation of sorting and display utilities for Student records.
 *
 * CST8002 Programming Language Research Project
 * Practical Assessment 4 – Proof of Concept
 *
 * Author: Ziming Zhao
 *
 * Description:
 * This module implements functions used for sorting and displaying
 * student records. The sorting logic is performed using the C
 * Standard Library function qsort().
 *
 * References:
 * [1] GeeksforGeeks, "Sorting in C using qsort() Function," GeeksforGeeks.
 *     [Online]. Available: https://www.geeksforgeeks.org/c/qsort-function-in-c/
 *     [Accessed: Mar. 14, 2026].
 */

#include <stdio.h>
#include "../include/sorter.h"

/**
 * @brief Comparison function used by qsort().
 *
 * This function compares two Student records by their grade values.
 * It allows qsort() to determine the ordering of elements during
 * the sorting process.
 *
 * @param a Pointer to the first Student record.
 * @param b Pointer to the second Student record.
 *
 * @return Integer representing ordering difference.
 */

int compareGrades(const void *a, const void *b) {
    const Student *s1 = (const Student *)a;
    const Student *s2 = (const Student *)b;

    return s1->grade - s2->grade;
}

/**
 * @brief Prints all students in the container.
 *
 * Iterates through the student array and prints each
 * student name and grade to the console.
 *
 * @param students Array of Student records.
 * @param count Number of elements in the array.
 */
void printStudents(const Student students[], int count) {
    for (int i = 0; i < count; i++) {
        printf("%s %d\n", students[i].name, students[i].grade);
    }
}