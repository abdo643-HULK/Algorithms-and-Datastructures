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
    ListNode *const newNode = new ListNode(data);
    newNode->next = head;
    head = newNode;
}

void LinkedList::addLast(int data) {
    ++listSize;
    penultimate = tail;
    ListNode *const newNode = new ListNode(data);
    newNode->next = nullptr;
    tail = newNode;
}

int LinkedList::removeFirst() {
    if (listSize == 0) return -1;
    --listSize;
    const auto *const tmpNode = head; // ListNode *const
    head = tmpNode->next;
    delete tmpNode;
}

int LinkedList::removeLast() {
    if (listSize == 0) return -1;
     --listSize;
    const auto tmpNode = head; // ListNode *const
    head = tmpNode->next;
    delete tmpNode;
}

int LinkedList::getAt(int index) {
    if (index > listSize - 1 || index < 0) return - 1;
    auto current = head;
    for (int i = 0; i < index; ++i) {
        current = current->next;
    }

    return current->element;
}

bool LinkedList::contains(int value) {
    auto current = head;
    while (current != nullptr && value != current->element) {
        current = current->next;
    }

    if (current != nullptr) return true;
    return false;
}


void LinkedList::printElements() {
    const ListNode *current = head;
    while (current->next != nullptr) {
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