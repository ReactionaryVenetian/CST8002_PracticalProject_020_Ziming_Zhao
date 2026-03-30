/**
 * CST8002 Programming Language Research Project
 * Practical Project Part 03 – Algorithmic manipulation of Structs
 *
 * Author: Ziming Zhao 041166304
 * Professor: Stanley Pieda
 * Due Date: 2026-03-29
 *
 * Description:
 * This file is responsible for printing my name and calling the presentation layer
 *
 * Sources:
 * Nothing new here
 */


// this is the main that runs the menu and calls other functions

#include <stdio.h>

/* Presentation layer */
#include "presentation/Menu.h"

/**
 * Program entry point.
 *
 * @return 0 on success.
 */

int main(void) {
    /* Dataset path: keep it simple and relative for marking screenshots */
    const char *dataset_path = "data/dataset.csv";

    printf("Program by Ziming Zhao\n");
    printf("Dataset: %s\n\n", dataset_path);

    menu_run(dataset_path);

    printf("\nProgram by Ziming Zhao\n");
    return 0;
}