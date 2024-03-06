#ifndef NODE_H
#define NODE_H

template <typename eltType> class CLinkedList;
template <typename eltType> class CListItr;

template <typename eltType>
class Node {
private:
    Node(eltType info, Node* link = nullptr) :
        data(info), next(link) {}
    eltType data;
    Node *next;
    friend class CLinkedList<eltType>;
    friend class CListItr<eltType>;
};

#endif
