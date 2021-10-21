//
// Created by abous on 18/10/2021.
//

#include "LinkedList.hpp"

using namespace std;

// O(1)
LinkedList::LinkedList() {
    listSize = 0;
    head = nullptr;
    tail = nullptr;
}

// O(1)
int LinkedList::size() {
    return listSize;
}

// O(1)
int LinkedList::getFirst() {
    if (head != nullptr) return head->element;
    return -1;
}

// O(1)
int LinkedList::getLast() {
    if (tail != nullptr) return tail->element;
    return -1;
}

// O(1)
void LinkedList::addFirst(int data) {
    ListNode *const newNode = new ListNode(data, head);
    head = newNode;
    if (listSize == 0) tail = newNode;
    ++listSize;
}

// O(1)
void LinkedList::addLast(int data) {
    ListNode *const newNode = new ListNode(data);
    if (listSize == 0) {
        head = newNode;
        tail = newNode;
        return;
    }
    tail->next = newNode;
    tail = newNode;
    ++listSize;
}

// O(1)
int LinkedList::removeFirst() {
    if (listSize == 0)
        return -1;
    const int value = head->element;
    --listSize;
    if (listSize == 0) {
        delete head;
        head = nullptr;
        tail = nullptr;
        return value;
    }
    const auto tmpNode = head; // ListNode *const
    head = tmpNode->next;
    delete tmpNode;
    return value;
}

// O(n)
int LinkedList::removeLast() {
    if (listSize == 0)
        return -1;
    const int value = tail->element;
    --listSize;
    if (listSize == 0) {
        delete head;
        head = nullptr;
        tail = nullptr;
        return value;
    }

    const ListNode *current = head;
    while (current->next->next != nullptr) {
        current = current->next;
    }

    delete tail;
    tail = (ListNode *) current; // ListNode *const
    tail->next = nullptr;

    return value;
}

// O(n)
int LinkedList::getAt(int index) {
    if (listSize == 0) return -1;
    if (index < 0 || index > listSize - 1)
        return -1;
    auto current = head;
    for (int i = 0; i < index; ++i) {
        current = current->next;
    }

    return current->element;
}

// O(n)
int LinkedList::removeAt(int index) {
    if (listSize == 0) return -1;
    if (index < 0 || index > listSize - 1)
        return -1;

    if (index == 0) return removeFirst();
    if (index == listSize - 1) return removeLast();

    auto current = head;

    for (int i = 0; i < index - 1 ; ++i) {
        current = current->next;
    }

    const int value = current->element;
    const auto newNext = current->next->next;
    const auto toDelete= current->next;

    current->next = newNext;

    delete toDelete;

    return value;
}

// O(n)
bool LinkedList::contains(int value) {
    auto current = head;
    while (current != nullptr && value != current->element) {
        current = current->next;
    }

    if (current != nullptr)
        return true;
    return false;
}

// O(1)
void LinkedList::addSorted(int val) {
    // In der Angabe steht nicht, ob ich es
    // am Anfang oder in der richtigen Position
    // oder am Ende einfügen soll.
    // Nur dass es in eine sortierte Liste
    // einfügen soll
    sortASC(); // O(n^2)
    addFirst(val);
}

// O(n^2)
void LinkedList::sortASC() {
    if (listSize == 0)
        return;

    ListNode *current = head;
    // int tmpNode;

    while (current != nullptr) {
        ListNode *next = current->next;

        while (next != nullptr) {
            if (current->element > next->element) {
                // XOR can be used to swap without temp variable
                current->element ^= next->element;
                next->element ^= current->element;
                current->element ^= next->element;
            }

            next = next->next;
        }

        current = current->next;
        if (current != nullptr && current->next == nullptr) tail = current;
    }
}

// O(n^2)
void LinkedList::sortDES() {
    if (listSize == 0)
        return;

    ListNode *current = head;
    // int tmpNode;

    while (current != nullptr) {
        ListNode *next = current->next;

        while (next != nullptr) {
            if (current->element < next->element) {
                // XOR can be used to swap without temp variable
                current->element ^= next->element;
                next->element ^= current->element;
                current->element ^= next->element;
            }

            next = next->next;
        }

        current = current->next;
        if (current != nullptr && current->next == nullptr) tail = current;
    }
}

// O(n)
void LinkedList::printElements() {
    const ListNode *current = head;
    if (head == nullptr) {
        cout << "Empty List"
             << "\n";
        return;
    }

    cout << "List: ";

    while (current->next != nullptr) {
        cout << current->element << ",";
        current = current->next;
    }

    cout << current->element << "\n";
}

// O(n)
void LinkedList::clear() {
    if (head == nullptr || listSize == 0) return;
    const ListNode *current = head;
    const ListNode *next = current->next;
    while (current->next != nullptr) {
        delete current;
        current = next;
        next = current->next;
    }
    head = nullptr;
    tail = nullptr;
    listSize = 0;
}

// O(1)
LinkedList::~LinkedList() {
    cout << "Destructor called" << "\n";
    printElements(); // O(n)
    clear(); // O(n)
}