/**
 * CST8002 Programming Language Research Project
 * Practical Project Part 02 – Project Review I
 *
 * Author: Ziming Zhao 041166304
 * Professor: Stanley Pieda
 * Due Date: 2026-02-22
 *
 * Description:
 * Presentation layer menu. Handles user interaction only
 * and delegates logic to the Business layer.
 *  *
 * References: Nothing new here, just a refactor.
 */


#include <stdio.h>
#include "Menu.h"
#include "../business/Records.h"
#include "../util/Input.h"

void menu_run(const char *dataset_path) {
    int choice = 0;

    do {
        printf("====================================\n");
        printf("Program by Ziming Zhao\n");
        printf("====================================\n");
        printf("1. Reload dataset\n");
        printf("2. Save to new UUID CSV\n");
        printf("3. Display records\n");
        printf("4. Add record\n");
        printf("5. Edit record\n");
        printf("6. Delete record\n");
        printf("7. Exit\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1) {
            clear_input_line();
            printf("Invalid input.\n\n");
            continue;
        }
        clear_input_line();

        switch (choice) {
            case 1:
                records_reload(dataset_path);
                break;

            case 2:
                records_save_to_uuid_csv();
                break;

            case 3:
                records_display_all();
                break;

            case 4:
                records_add_interactive();
                break;

            case 5:
                records_edit_interactive();
                break;

            case 6:
                records_delete_interactive();
                break;

            case 7:
                printf("Exiting program...\n");
                break;

            default:
                printf("Invalid option.\n\n");
        }

    } while (choice != 7);
}