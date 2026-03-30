/**
 * @file PA4.c
 * @brief Demonstrates sorting records in C using the standard library qsort() function.
 *
 * CST8002 Programming Language Research Project
 * Practical Assessment 4 – Proof of Concept
 *
 * Author: Ziming Zhao
 *
 * Description:
 * This program demonstrates the use of the C Standard Library sorting function
 * qsort() to sort a container of records. The records are stored in an array
 * of Student structures containing a name and grade. The program prints the
 * records before sorting and after sorting to demonstrate the algorithm.
 *
 * References:
 * [1] GeeksforGeeks, "Sorting in C using qsort() Function," GeeksforGeeks.
 *     [Online]. Available: https://www.geeksforgeeks.org/c/qsort-function-in-c/
 *     [Accessed: Mar. 14, 2026].
 */


 // lolololol 40 mins debugging a compile error, turns out I just didn't save the file before compiling so it was just an empty file. I am a genius. 
 // honestly the more work I do the more I realize how much of programming is just quality assurance and the hardest issues require non-code problem solving. 
#include <stdio.h>
#include <stdlib.h>

/**
 * @struct Student
 * @brief Represents a student record containing a name and grade.
 *
 * This structure acts as a simple container for storing student data.
 * It is used in an array which is sorted using the qsort() algorithm.
 */
typedef struct {
    char name[20];   /**< Name of the student */
    int grade;       /**< Student grade value */
} Student;

/**
 * @brief Comparison function used by qsort() to sort student records.
 *
 * This function compares two Student records based on their grade values.
 * The function is passed as a function pointer to qsort().
 *
 * @param a Pointer to the first Student record.
 * @param b Pointer to the second Student record.
 *
 * @return
 * - Negative value if first grade is less than second
 * - Zero if grades are equal
 * - Positive value if first grade is greater than second
 */
int compareGrades(const void *a, const void *b) {
    Student *s1 = (Student*)a;
    Student *s2 = (Student*)b;
    return s1->grade - s2->grade;
}

/**
 * @brief Program entry point.
 *
 * The main function initializes a small dataset of student records,
 * prints them before sorting, sorts them using the qsort() algorithm,
 * and then prints the sorted results.
 *
 * @return int Returns 0 when the program executes successfully.
 */
int main() {

    printf("Ziming Zhao - CST8002 PA4 Proof of Concept\n\n");

    /**
     * Sample dataset used for demonstrating sorting.
     */
    Student students[] = {
        {"Alice",85},
        {"Bob",72},
        {"Charlie",91},
        {"Dave",66}
    };

    /**
     * Determine number of elements in the student array.
     */
    int n = sizeof(students)/sizeof(students[0]);

    printf("Before sorting:\n");
    for(int i=0;i<n;i++)
        printf("%s %d\n", students[i].name, students[i].grade);

    /**
     * Sort the student array using qsort().
     *
     * Parameters:
     * - students: array to sort
     * - n: number of elements
     * - sizeof(Student): size of each element
     * - compareGrades: comparison function
     */
    qsort(students,n,sizeof(Student),compareGrades);

    printf("\nAfter sorting:\n");
    for(int i=0;i<n;i++)
        printf("%s %d\n", students[i].name, students[i].grade);

    return 0;
}