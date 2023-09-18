#include "application.h"
#include "utils.h"

#include <iostream>
#include <iomanip>

/**
 * Reads the number input via cin
 * @param[out] variable Reference to a declared variable
 * @param[in] isSpaceSep If true, it does not check the last character of the input for newline
 * @param[in] isUnsigned If true, then negative numbers will lead to an error
 * @return True if input was correct, else false
 */
template <typename NumType>
bool inputNumber(NumType &variable, bool isSpaceSep = false, bool isUnsigned = false) {
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

    std::cout.setf(std::ios::boolalpha);
    std::cout << "Enter 'h' to get list of commands\n";

    char userChoice;
    while (true) {
        // Get command from the keyboard
        if (!menu(userChoice)) continue; // Error occurred
        if (userChoice == '0') break;       // Exit command

        // Execute
        switch (userChoice) {
            // Short int repr
            case '1': {
                short int userInput;
                std::cout << "<< Enter a short integer\n>> ";
                if (!inputNumber(userInput)) continue;

                std::string binarySInt = getBitsOfSInt(userInput);
                std::cout << "Decimal: " << userInput << '\n';
                std::cout << " Binary: " << binarySInt << '\n';

                break;
            }

            // Long double repr
            case '2': {
                long double userInput;
                std::cout << "<< Enter a long double\n>> ";
                if (!inputNumber(userInput)) continue;

                std::string binaryLDouble = getBitsOfLDouble(userInput);
                std::cout << "Decimal: " << userInput << '\n';
                std::cout << " Binary: " << binaryLDouble << '\n';

                break;
            }

            // Swap bits
            case '3':
                break;

            // Help menu
            case 'h':
                std::cout << "Available commands:\n";
                std::cout << std::setw(32) << std::setfill('-') << '\n';
                std::cout << "h: Help (this menu)\n";
                std::cout << std::setw(32) << std::setfill('-') << '\n';
                std::cout << "1: Short integer binary representation\n";
                std::cout << "2: Long double binary representation\n";
                std::cout << "3: Task 19. Swap the values of bits in a given number of bit pairs\n";
                std::cout << std::setw(32) << std::setfill('-') << '\n';
                std::cout << "0: Exit\n";
                std::cout << std::setw(32) << std::setfill('-') << '\n';
                std::cout << std::setfill(' ');
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
    std::cout << "<< Action:\n>> ";
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