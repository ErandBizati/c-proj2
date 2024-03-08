/************************************************************
* Author: Erand Bizati
* Major: Comp Sci
* Due Date: 3/8/24
* Course: CSC237
* Professor Name: Dr. Spiegel
* Project: 2
* Filename: ClinkedList.h
************************************************************/

#ifndef CLINKEDLIST_H
#define CLINKEDLIST_H

#include "Node.h"
#include <iostream>
#include <cassert>



/*********************************************************************************************************
 * Class: CLinkedList
 * -------------------------------------------------------------------------------------------------------
 * Description: A templated circular linked list class that provides functionality for managing a circular
 * sequence of nodes in ascending order based on their value. It supports operations such as insertion,
 * removal, checking if the list is empty, and printing the list contents both forwards and backwards. The
 * class maintains a pointer to the last node to facilitate circular linkage and efficient access to both
 * ends of the list.
 * -------------------------------------------------------------------------------------------------------
 * Template Parameter:
 * - T : The data type of the elements stored in the list. This allows the CLinkedList to be used with any
 *       data type.
 * -------------------------------------------------------------------------------------------------------
 * Private Member Functions:
 * - destroy : Recursively deallocates the nodes of the list starting from a specified node, effectively
 *             clearing the list.
 * -------------------------------------------------------------------------------------------------------
 * Public Member Functions:
 * - CLinkedList() : Default constructor that initializes an empty list.
 * - CLinkedList(const CLinkedList& other) : Copy constructor for creating a deep copy of another list.
 * - ~CLinkedList() : Destructor that cleans up all allocated resources, deleting all nodes in the list.
 * - operator= : Allows assignment between two lists, replacing the current list's contents with a deep
 *               copy of another list's contents.
 * - insert(T value) : Inserts a new value into the list in ascending order.
 * - remove(T value) : Removes the first occurrence of a specified value from the list.
 * - isEmpty() : Checks if the list is empty.
 * - printForward() : Prints the contents of the list from the first node to the last.
 * - printBackward() : Prints the contents of the list from the last node to the first, in reverse order.
 *********************************************************************************************************/
template <typename T>
class CLinkedList {
private:
    Node<T>* last; 

    void destroy(Node<T>*& node) { 
        if (!node) return;
        Node<T>* current = (node->next == node) ? nullptr : node->next;
        while (current != node && current != nullptr) {
            Node<T>* next = current->next;
            delete current;
            current = next;
        }
        delete node;
        node = nullptr;
    }

public:

    CLinkedList() : last(nullptr) {}
    CLinkedList(const CLinkedList& other) : last(nullptr) {
        if (!other.isEmpty()) {
            Node<T>* current = other.last->next;
            do {
                insert(current->data);
                current = current->next;
            } while (current != other.last->next);
        }
    }
    /*********************************************************************************************************
     * Destructor: ~CLinkedList
     *********************************************************************************************************/
    ~CLinkedList() {
        destroy(last);
    }

    /*********************************************************************************************************
     * Function: operator=
     *********************************************************************************************************/
    CLinkedList& operator=(const CLinkedList& other) {
        if (this != &other) {
            destroy(last);
            if (!other.isEmpty()) {
                Node<T>* current = other.last->next;
                do {
                    insert(current->data);
                    current = current->next;
                } while (current != other.last->next);
            }
        }
        return *this;
    }

    /*********************************************************************************************************
 * Function: insert
 *********************************************************************************************************/
   void insert(T value) {
    Node<T>* newNode = new Node<T>(value);
    if (isEmpty()) {
        last = newNode;
        newNode->next = newNode;
    } else {
        Node<T>* temp = last->next; 
        
        if (value < temp->data) {
            newNode->next = temp;
            last->next = newNode;
        } else {
            
            while (temp != last && temp->next->data < value) {
                temp = temp->next;
            }
            newNode->next = temp->next;
            temp->next = newNode;
            if (temp == last) {
                last = newNode; 
            }
        }
    }
}

/*********************************************************************************************************
 * Function: remove
 *********************************************************************************************************/
    bool remove(T value) {
    if (isEmpty()) return false;

    Node<T>* temp = last;
    bool found = false;
    do {
        Node<T>* toDelete = temp->next;
        if (toDelete->data == value) {
            found = true;
            if (last == last->next) { 
                last = nullptr;
            } else {
                temp->next = toDelete->next;
                if (toDelete == last) { 
                    last = temp;
                }
            }
            delete toDelete;
            break;
        }
        temp = temp->next;
    } while (temp != last);

    return found;
}


/*********************************************************************************************************
 * Function: isEmpty
 *********************************************************************************************************/
    bool isEmpty() const {
        return last == nullptr;
    }

/*********************************************************************************************************
 * Function: printForward
 *********************************************************************************************************/
    void printForward() const {
        if (isEmpty()) {
            std::cout << "List is empty." << std::endl;
            return;
        }
        Node<T>* start = last->next;
        Node<T>* current = start;
        do {
            std::cout << current->data << " ";
            current = current->next;
        } while (current != start);
        std::cout << std::endl;
    }

/*********************************************************************************************************
 * Function: printBackward
 *********************************************************************************************************/
    void printBackward() const {
    if (isEmpty()) {
        std::cout << "List is empty." << std::endl;
        return;
    }
    std::cout << "List (backward): ";
    Node<T>* start = last;
    do {
        std::cout << start->data << " ";
        
        Node<T>* pred = last;
        while (pred->next != start) {
            pred = pred->next;
        }
        start = pred;
    } while (start != last);
    std::cout << std::endl;
}

};


/*********************************************************************************************************
 * Class: CLinkedList
 * -------------------------------------------------------------------------------------------------------
 * Description: A template class for implementing a circular linked list in C++. It supports various 
 * operations such as adding elements in a sorted order, removing specific elements, checking for list 
 * emptiness, and iterating over its elements both forwards and backwards. The list is circular, meaning 
 * the last node points back to the first node, facilitating an efficient circular traversal. This class 
 * embodies principles of data encapsulation and resource management, ensuring that all dynamically 
 * allocated memory is properly handled to prevent memory leaks.
 * -------------------------------------------------------------------------------------------------------
 * Template Parameter:
 * - T : The data type of the elements stored in the list. This allows the CLinkedList class to be used 
 *       with any data type.
 * -------------------------------------------------------------------------------------------------------
 * Private Member Variables:
 * - last : A pointer to the last node of the list. In an empty list, this pointer is set to nullptr. For 
 *          a non-empty list, it facilitates access to both the beginning and end of the list due to the 
 *          circular nature of the linked structure.
 * -------------------------------------------------------------------------------------------------------
 * Private Member Function:
 * - destroy : A helper function responsible for recursively deleting all nodes in the list starting from 
 *             a given node to manage memory and prevent leaks.
 * -------------------------------------------------------------------------------------------------------
 * Public Member Functions:
 * - CLinkedList() : Default constructor that initializes an empty list.
 * - CLinkedList(const CLinkedList& other) : Copy constructor that creates a deep copy of another list.
 * - ~CLinkedList() : Destructor that cleans up all dynamically allocated memory to prevent leaks.
 * - operator= : Copy assignment operator that assigns the contents of another list to this list.
 * - insert(T value) : Inserts a new element into the list in a position that maintains the list's order.
 * - remove(T value) : Removes the first occurrence of an element from the list, if it exists.
 * - isEmpty() const : Checks if the list is empty and returns a boolean value accordingly.
 * - printForward() const : Prints the contents of the list from the first element to the last.
 * - printBackward() const : Prints the contents of the list from the last element to the first.
 * -------------------------------------------------------------------------------------------------------
 * Member Type: Container Class
 * -------------------------------------------------------------------------------------------------------
 * Pre-conditions: For operations on existing elements, the list should not be empty.
 * Post-conditions: The list may be modified by insertions or removals but remains in a valid state.
 *********************************************************************************************************/
template <typename T>
class CListItr {
private:
    const CLinkedList<T>& list;
    Node<T>* current;

public:
    CListItr(const CLinkedList<T>& list) : list(list), current(nullptr) {}

    void begin() { current = list.isEmpty() ? nullptr : list.last->next; }
    bool isEmpty() const { return list.isEmpty(); }
    bool isLastNode() const { return current == list.last; }
    bool isFirstNode() const {
    return !isEmpty() && current == list.last->next; }
    T operator*() const { assert(current != nullptr); return current->data; }
    CListItr& operator++() { // pre-increment
        assert(current != nullptr);
        current = (current == list.last) ? nullptr : current->next;
        return *this;
    }
    CListItr operator++(int) { // post-increment
        CListItr temp = *this;
        ++(*this);
        return temp;
    }
};

#endif // CLINKEDLIST_H
