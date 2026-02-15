/*
Author: Ziming Zhao 041166304
Brave new world towards AI? Unexpected AI topics at work.
Sources: now done in IEEE style in the source code! :)

Nothing really new to reference here, all the new stuff is in processor.C
*/

// this is the main that runs the menu and calls other functions

#include <stdio.h>
#include "Processor.h"

static void runMenu(void);

int main(void) {
    runMenu();
    return 0;
}


/*
    Displays the menu and processes user choices, just adapted it slightly from PA2
    Parameters: none
    Returns: nothing
*/
static void runMenu(void) {
    int choice = 0;

    do {
        printf("By Ziming Zhao\n");
        printf("What would you like to do?\n");
        printf("1. Run the negative test we did\n");
        printf("2. Run the positive test we did\n");
        printf("3. Escape plan (exit)\n");
        printf("Enter choice (number): ");

        if (scanf("%d", &choice) != 1) {
            clear_input_line();
            printf("Invalid input.\n\n");
            continue;
        }
        clear_input_line();

        switch (choice) {
            case 1:
                do_negative_test();
                break;
            case 2:
                do_positive_test();
                break;
            case 3:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid option.\n\n");
        }
    } while (choice != 3);
}
