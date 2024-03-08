/************************************************************
* Author: Erand Bizati
* Major: Comp Sci
* Due Date: 3/8/24
* Course: CSC237
* Professor Name: Dr. Spiegel
* Project: 2
* Filename: testLL.cpp
************************************************************/

#include "CLinkedList.h"
#include <iostream>
#include <limits>



/*********************************************************************************************************
 * Function: main
 * -------------------------------------------------------------------------------------------------------
 * Description: Serves as the entry point for the program. It provides a test driver for the `CLinkedList` 
 * class, allowing the user to perform operations such as insert, remove, print forwards, and print 
 * backwards on a circular linked list of integers.
 * -------------------------------------------------------------------------------------------------------
 * Parameters: None
 * -------------------------------------------------------------------------------------------------------
 * Returns: int - The exit status of the program.
 * -------------------------------------------------------------------------------------------------------
 * Pre-conditions: None
 * Post-conditions: Executes a series of list operations based on user input until the exit option is chosen.
 *********************************************************************************************************/
int main() {
    CLinkedList<int> list;
    char choice;
    int value;

    do {
        std::cout << "LinkedList Test Driver\nI)nsert\nR)emove\nF)orward Print\nB)ackward Print\nE)xit ";
        std::cin >> choice;
        switch (toupper(choice)) {
            case 'I':
                std::cout << "Enter an integer to insert: ";
                if (!(std::cin >> value)) {
                    std::cin.clear(); 
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                    std::cout << "Invalid input. Please enter an integer.\n";
                    break;
                }
                list.insert(value);
                break;
            case 'R':
                std::cout << "Enter an integer to remove: ";
                if (!(std::cin >> value)) {
                    std::cin.clear(); 
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                    std::cout << "Invalid input. Please enter an integer.\n";
                    break;
                }
                if (!list.remove(value)) {
                    std::cout << "Value not found.\n";
                }
                break;
            case 'F':
                list.printForward();
                break;
            case 'B':
                list.printBackward();
                break;
            case 'E':
                std::cout << "Exiting\n";
                break;
            default:
                std::cout << "Invalid option.\n";
        }
    } while (toupper(choice) != 'E');

    return 0;
}
