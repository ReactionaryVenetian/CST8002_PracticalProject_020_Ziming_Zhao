/*
Author: Ziming Zhao
Brave new world towards the defense industries.
Sources: now done in IEEE style in the source code! :)

Nothing really new to reference here.
*/



#include <stdio.h>
#include "../src/Interface.h"

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
        printf("Hello Ziming Zhao\n");
        printf("What would you like to do?\n");
        printf("1. Import and display datafile (read)\n");
        printf("2. Escape plan (exit)\n");
        printf("Enter choice (number): ");

        if (scanf("%d", &choice) != 1) {
            clear_input_line();
            printf("Invalid input.\n\n");
            continue;
        }
        clear_input_line();

        switch (choice) {
            case 1:
                do_read_file();
                break;
            case 2:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid option.\n\n");
        }
    } while (choice != 2);
}
