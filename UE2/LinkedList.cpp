//
// Created by abous on 18/10/2021.
//

#include "LinkedList.hpp"

using namespace std;

LinkedList::LinkedList() {
    listSize = 0;
    head = nullptr;
    tail = nullptr;
    penultimate = nullptr;
}

int LinkedList::size() {
    return listSize;
}

int LinkedList::getFirst() {
    return head->element;
}

int LinkedList::getLast() {
    return tail->element;
}

void LinkedList::addFirst(int data) {
    ++listSize;
    ListNode *const newNode = new ListNode(data, head);
    // newNode->next = head;
    head = newNode;
}

void LinkedList::addLast(int data) {
    ++listSize;
    penultimate = tail;
    ListNode *const newNode = new ListNode(data, nullptr);
    // newNode->next = nullptr;
    tail = newNode;
}

int LinkedList::removeFirst() {
    if (listSize == 0)
        return -1;
    --listSize;
    const auto tmpNode = head; // ListNode *const
    const int value = tmpNode->element;
    head = tmpNode->next;
    delete tmpNode;
    return value;
}

int LinkedList::removeLast() {
    if (listSize == 0)
        return -1;
    --listSize;
    const auto tmpNode = head; // ListNode *const
    const int value = tmpNode->element;
    head = tmpNode->next;
    delete tmpNode;
    return value;
}

int LinkedList::getAt(int index) {
    if (index > listSize - 1 || index < 0)
        return -1;
    auto current = head;
    for (int i = 0; i < index; ++i) {
        current = current->next;
    }

    return current->element;
}

int LinkedList::removeAt(int index) {
    if (index > listSize - 1 || index < 0)
        return -1;

    auto current = head;

    for (int i = 0; i < index; ++i) {
        current = current->next;
    }

    const int value = current->element;

    delete current;

    return value;
}

bool LinkedList::contains(int value) {
    auto current = head;
    while (current != nullptr && value != current->element) {
        current = current->next;
    }

    if (current != nullptr)
        return true;
    return false;
}

void LinkedList::addSorted(int val) {
    sortASC();
}

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
    }
}

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
    }
}

void LinkedList::printElements() {
    const ListNode *current = head;
    if (head == nullptr) {
        cout << "Empty List"
             << "\n";
        return;
    }

    while (current != nullptr) {
        cout << current->element << "\n";
        current = current->next;
    }
}

void LinkedList::clear() {
    const ListNode *current = head;
    const ListNode *next = current->next;
    while (current->next != nullptr) {
        delete current;
        current = next;
        next = current->next;
    }
}

LinkedList::~LinkedList() {
    clear();
}