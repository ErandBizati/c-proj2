#ifndef CLINKEDLIST_H
#define CLINKEDLIST_H

#include "Node.h"
#include <iostream>
#include <cassert>

template <typename T>
class CLinkedList {
private:
    Node<T>* last; // Points to the last node in the list

    void destroy(Node<T>*& node) { // Recursive destroy function
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
    ~CLinkedList() {
        destroy(last);
    }
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

   void insert(T value) {
    Node<T>* newNode = new Node<T>(value);
    if (isEmpty()) {
        last = newNode;
        newNode->next = newNode;
    } else {
        Node<T>* temp = last->next; // Start from the first node
        // Special case for insertion before the first node
        if (value < temp->data) {
            newNode->next = temp;
            last->next = newNode;
        } else {
            // Find the insertion point
            while (temp != last && temp->next->data < value) {
                temp = temp->next;
            }
            newNode->next = temp->next;
            temp->next = newNode;
            if (temp == last) {
                last = newNode; // Update last if inserted at or after the last node
            }
        }
    }
}


    bool remove(T value) {
    if (isEmpty()) return false;

    Node<T>* temp = last;
    bool found = false;
    do {
        Node<T>* toDelete = temp->next;
        if (toDelete->data == value) {
            found = true;
            if (last == last->next) { // Only one node
                last = nullptr;
            } else {
                temp->next = toDelete->next;
                if (toDelete == last) { // Removing the last node
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


    bool isEmpty() const {
        return last == nullptr;
    }

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

    void printBackward() const {
    if (isEmpty()) {
        std::cout << "List is empty." << std::endl;
        return;
    }
    std::cout << "List (backward): ";
    Node<T>* start = last;
    do {
        std::cout << start->data << " ";
        // Find the predecessor of start
        Node<T>* pred = last;
        while (pred->next != start) {
            pred = pred->next;
        }
        start = pred;
    } while (start != last);
    std::cout << std::endl;
}

};



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
    T operator*() const { assert(current != nullptr); return current->data; }
    CListItr& operator++() { // Pre-increment
        assert(current != nullptr);
        current = (current == list.last) ? nullptr : current->next;
        return *this;
    }
    CListItr operator++(int) { // Post-increment
        CListItr temp = *this;
        ++(*this);
        return temp;
    }
};

#endif // CLINKEDLIST_H
