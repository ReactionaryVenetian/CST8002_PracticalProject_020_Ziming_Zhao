/**
 * CST8002 Programming Language Research Project
 * Practical Project Part 04 – multi-column sorting and additional features
 *
 * Author: Ziming Zhao 041166304
 * Professor: Stanley Pieda
 * Due Date: 2026-04-12
 *
 * Description:
 * Presentation layer menu. Handles user interaction only
 * and delegates logic to the Business layer.
 * 
 * References: Added secondary menu for multi-column sort, nothing conceptually mew-just more complicated.
 */


#include <stdio.h>
#include "Menu.h"
#include "../business/Records.h"
#include "../util/Input.h"

/**
 * @brief Runs the main console menu loop for the application.
 *
 * Displays the available menu options, reads the user's choice,
 * validates input, and calls the appropriate business-layer
 * function based on the selected operation.
 *
 * Supported operations include:
 * - reloading the dataset
 * - saving records to a UUID-based CSV file
 * - displaying all records
 * - adding, editing, and deleting records
 * - displaying summary analysis
 * - sorting by Total Black oystercatcher adults
 * - displaying a histogram
 * - searching by minimum adults threshold
 * - counting records by species
 * - calculating standard deviation
 *
 * The menu continues running until the user selects the exit option.
 *
 * @param dataset_path Path to the CSV dataset file used for reload operations.
 */

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
        printf("7. Display analysis\n");
        printf("8. Sort by adults ascending\n");
        printf("9. Sort by adults descending\n");
        printf("10. Display histogram\n");
        printf("11. Search by minimum adults\n");
        printf("12. Count species\n");
        printf("13. Standard deviation\n");
        printf("14. Graphical histogram\n");
        printf("15. Sort by multiple columns\n");
        printf("16. Exit\n");
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
                records_display_analysis();
                break;
            case 8:
                records_sort_by_adults_ascending();
                printf("Records sorted by adults ascending.\n");
                break;

            case 9:
                records_sort_by_adults_descending();
                printf("Records sorted by adults descending.\n");
                break;

            case 10:
                records_display_histogram();
                break;

            case 11: {
                int threshold = input_read_int("Enter minimum adults: ");
                records_search_by_min_adults(threshold);
                break;
            }

            case 12: {
                char species[100];
                input_read_string("Enter species: ", species, sizeof(species));
                records_count_species(species);
                break;
            }

            case 13:
                printf("Standard deviation: %.2f\n", records_stddev());
                break;

            case 14:
                records_display_graphical_histogram();
                break;

            case 15:
            menu_sort_multiple_columns();
            break;

            case 16:
                printf("Exiting program...\n");
                break;

            default:
                printf("Invalid option.\n\n");
        }

    } while (choice != 14);
}


/**
 * @brief Displays the available sort keys (sub-menu of case 15).
 */
static void display_sort_key_options(void) {
    printf("Choose a sort key:\n");
    printf("1. Visit date\n");
    printf("2. Site identification\n");
    printf("3. Species\n");
    printf("4. Total Black oystercatcher adults\n");
}

/**
 * @brief Runs the menu for multi-column sorting.
 */
void menu_sort_multiple_columns(void) {
    int primary = 0;
    int secondary = 0;
    int tertiary = 0;
    int order = 0;

    printf("\n=== Multi-Column Sort ===\n");

    display_sort_key_options();
    printf("Enter primary sort key: ");
    scanf("%d", &primary);

    display_sort_key_options();
    printf("Enter secondary sort key: ");
    scanf("%d", &secondary);

    display_sort_key_options();
    printf("Enter tertiary sort key: ");
    scanf("%d", &tertiary);

    printf("Choose order:\n");
    printf("1. Ascending\n");
    printf("2. Descending\n");
    printf("Enter order: ");
    scanf("%d", &order);

    records_sort_multiple_columns(
        (SortKey)primary,
        (SortKey)secondary,
        (SortKey)tertiary,
        (SortOrder)order
    );
}