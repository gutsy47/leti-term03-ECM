#include "application.h"

#include <iostream>
#include <iomanip>

/**
 * Reads the integer input via cin
 * @param[out] variable Reference to a declared variable
 * @param[in] isSpaceSep If true, it does not check the last character of the input for newline
 * @param[in] isUnsigned If true, then negative numbers will lead to an error
 * @return True if input was correct, else false
 */
bool inputInt(int &variable, bool isSpaceSep = false, bool isUnsigned = false) {
    std::cin >> variable;
    if (std::cin.fail() || (isUnsigned && variable < 0) || (isSpaceSep && std::cin.peek() != '\n')) {
        std::cout << "Invalid input\n";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        return false;
    }
    return true;
}

/**
 * Executes the program
 * @return 0 if correct exit
 */
int TApplication::execute() {

    char userChoice;
    while (true) {
        // Get command from the keyboard
        if (!menu(userChoice)) continue; // Error occurred
        if (userChoice == '0') break;       // Exit command

        // Execute
        switch (userChoice) {
            case '1':
                break;

            // Runtime error. Unknown command
            default: std::cout << "RuntimeError. Unknown command\n";
        }
        system("pause");
    }
    return 0;
}

/**
 * Prints the menu of commands and reads the user action input via cin
 * @param[out] userChoice Reference to a declared user's choice variable
 * @return True if input was correct, else false (error)
 */
bool TApplication::menu(char &userChoice) {
    std::cout << "<< Action:\n"
                 "   1. Do smh\n"
              << std::setw(28) << std::setfill('-') << '\n'
              << std::setfill(' ') <<
              "   0. Exit\n"
              ">> ";
    std::cin >> userChoice;

    // Error handler (i.e. more than one symbol input)
    if (std::cin.fail() || std::cin.get() != '\n') {
        std::cout << "RuntimeError. Unknown command\n";
        std::cin.clear();
        std::cin.ignore(100000, '\n');
        return false;
    }
    return true;
}