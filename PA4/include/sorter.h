/**
 * @file sorter.h
 * @brief Header file defining the Student structure and sorting utilities.
 *
 * CST8002 Programming Language Research Project
 * Practical Assessment 4 – Proof of Concept
 *
 * Author: Ziming Zhao
 *
 * Description:
 * This header defines the Student container structure and declares the
 * functions used for sorting and displaying student records. These
 * functions are used to demonstrate an algorithm that manipulates
 * container data using the standard C library function qsort().
 *
 * References:
 * [1] GeeksforGeeks, "Sorting in C using qsort() Function," GeeksforGeeks.
 *     [Online]. Available: https://www.geeksforgeeks.org/c/qsort-function-in-c/
 *     [Accessed: Mar. 14, 2026].
 */

#ifndef SORTER_H
#define SORTER_H

/**
 * @struct Student
 * @brief Represents a student record.
 *
 * This structure acts as a container that stores basic
 * student information used for sorting demonstrations.
 */
typedef struct {
    char name[20];  /**< Name of the student */
    int grade;      /**< Numeric grade value */
} Student;

/**
 * @brief Compares two Student records by grade.
 *
 * This function is used as a comparison callback for qsort().
 * It determines the ordering of elements in the container.
 *
 * @param a Pointer to the first Student object.
 * @param b Pointer to the second Student object.
 *
 * @return
 * - Negative value if the first grade is less than the second
 * - Zero if the grades are equal
 * - Positive value if the first grade is greater than the second
 */
int compareGrades(const void *a, const void *b);

/**
 * @brief Prints a list of student records.
 *
 * Displays each student’s name and grade from the container.
 *
 * @param students Array containing Student records.
 * @param count Number of Student records in the container.
 */
void printStudents(const Student students[], int count);

#endif