/*
Author: Ziming Zhao
Brave new world towards the defense industries.
Sources:
File IO stuff: https://www.w3schools.com/c/c_ref_stdio.php
Methods/structures:  https://www.w3schools.com/c/c_structs.php
Loops: https://www.w3schools.com/c/c_functions_recursion.php
*/

#include <stdio.h> //this is the header, it allows us to import modules like input/output functions such as printf()

// prints the meat of the assignment
int main(void) {



    void runMenu(void) {

        int choice;
        do{
        printf("Hello Ziming Zhao\n");
        printf("What would you like to to?\n");
        printf("1. Import file (read)\n");
        printf("2. Export file (write)\n");
        printf("3. Escape plan (exit)\n");
        printf("Enter choice (number): \n");
            
            scanf("%i", &choice);

            switch (choice) {
            case 1:
                printf("Read file selected.\n");
                break;

            case 2:
                printf("Write file selected.\n");
                break;

            case 3:
                printf("Exiting program...\n");
                break;

            default:
                printf("Invalid option. Try again.\n");
            }
        while (choice!=3)
        {
            /* code */
        }
        }
    }

    return 0;
}