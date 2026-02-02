/*
Author: Ziming Zhao
Brave new world towards the defense industries.
Sources: now done in IEEE style in the source code! :)

/*
Author: Ziming Zhao
Brave new world towards the defense industries.
Sources: now done in IEEE style in the source code! :)

[1] W3Schools, “C user input,” W3Schools Online Web Tutorials. [Online]. Available: https://www.w3schools.com/c/c_user_input.php
. [Accessed: Jan. 2026].

[2] W3Schools, “C structures,” W3Schools Online Web Tutorials. [Online]. Available: https://www.w3schools.com/c/c_structs.php
. [Accessed: Jan. 2026].

[3] W3Schools, “C function pointers,” W3Schools Online Web Tutorials. [Online]. Available: https://www.w3schools.com/c/c_functions_pointers.php
. [Accessed: Jan. 2026].

https://www.w3schools.com/c/c_arrays.php

https://www.w3schools.com/c/c_arrays_loop.php

*/

#include <stdio.h>
#include "../Src/Interface.h" //all files centalized into one interface file, because there isn't private or public ways to hide stuff and localize in C

int main(void) {
    runMenu();
    return 0;
}


/* 
    Displays the menu and processes user choices, just adapted it slightly from PA2
    Parameters: none
    Returns: maybe the entire csv, if nothing goes wrong.
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



