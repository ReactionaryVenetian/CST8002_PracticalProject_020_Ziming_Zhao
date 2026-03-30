/**
 * CST8002 Programming Language Research Project
 * Practical Project Part 03 – Algorithmic manipulation of Structs
 *
 * Author: Ziming Zhao 041166304
 * Professor: Stanley Pieda
 * Due Date: 2026-03-29
 *
 * Description:
 * Header file for the Presentation layer menu system.
 * This module is responsible for handling all user interaction,
 * displaying menu options, and delegating operations to the
 * Business layer.
 *
 * References:
 * [1] Doxygen Manual. (2024). Documenting the code.
 *     Available: https://www.doxygen.nl/manual/docblocks.html
 *     [Accessed: Feb. 22, 2026]. I saw the comment too late for the previous stuff
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

#endif /* MENU_H */