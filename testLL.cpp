#include "CLinkedList.h"
#include <iostream>
#include <limits>

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
                    std::cin.clear(); // Clears the error flag
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignores the rest of the input
                    std::cout << "Invalid input. Please enter an integer.\n";
                    break;
                }
                list.insert(value);
                break;
            case 'R':
                std::cout << "Enter an integer to remove: ";
                if (!(std::cin >> value)) {
                    std::cin.clear(); // Clears the error flag
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignores the rest of the input
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
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid option.\n";
        }
    } while (toupper(choice) != 'E');

    return 0;
}
