/**
 * CST8002 Programming Language Research Project
 * Practical Project Part 04 – multi-column sorting and additional features
 *
 * Author: Ziming Zhao 041166304
 * Professor: Stanley Pieda
 * Due Date: 2026-04-12
 *
 * Description:
 * Header file for the Presentation layer menu system.
 * This module is responsible for handling all user interaction,
 * displaying menu options, and delegating operations to the
 * Business layer.
 *
 * References:
 * Added secondary menu for multi-column sort, nothing conceptually mew-just more complicated.
 */

#ifndef MENU_H
#define MENU_H

/**
 * Runs the interactive console menu loop.
 *
 * This function repeatedly displays menu options,
 * accepts user input, and calls the appropriate
 * business-layer functions.
 *
 * @param dataset_path Path to the dataset CSV file.
 */
void menu_run(const char *dataset_path);

/**
 * @brief Runs the multi-column sort feature menu.
 */
void menu_sort_multiple_columns(void);

#endif /* MENU_H */