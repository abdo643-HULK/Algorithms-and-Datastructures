#ifndef LINKEDLIST_HPP_
#define LINKEDLIST_HPP_

#include <iostream>
#include "ListNode.hpp"

class LinkedList {
    unsigned int listSize;
    ListNode *head;
    ListNode *penultimate; // Das vorletzte Element für removeLast Geschwindigkeit
    ListNode *tail;

public:
    LinkedList(); // constructs an empty list
    /**
     *
     * @return size of the list
     */
    int size();

    /**
     * returns the first element in the list
     *
     * @return element, -1 if empty
     */
    int getFirst();

    /**
     * returns the last element in the list
     * @return element, -1 if empty
     */
    int getLast();

    /**
     * adds an element at the beginning of the list
     * @param data - The Nodes value(element)
     */
    void addFirst(int data);

    /**
     * adds an element at the end of the list
     * @param data - The Nodes value(element)
     */
    void addLast(int data);

    /**
     * removes  the  first  element
     *
     * @return value of the removed element, -1 if empty
     */
    int removeFirst();

    /**
     * removes the  last  element
     *
     * @return value of the removed element, -1 if empty
     */
    int removeLast();

    /**
     * returns  element  at  position  index,
     * @param index
     * @return -1  if  index  is  out  of  bounds
     */
    int getAt(int index);

    /**
     * remove  element  at  position  index  and  returns  element  value,
     * -1  if  index  is  out  of  bounds
     * @param index - 0 or bigger
     * @return
     */
    int removeAt(int index);

    /**
     * Checks if the list contains a certain value
     *
     * @param value
     * @return true if value in the list, else false
     */
    bool contains(int value);

    /**
     * adds an element in a sorted list
     * @param val
     */
    void addSorted(int val);

    /**
     * sorts the list in ascending order: 1, 2, 3
     */
    void sortASC();

    /**
     * sorts the list in descending order: 3, 2, 1
     */
    void sortDES();

    /**
     * removes  and  deletes  all  elements  of  the  list
     */
    void clear();

    /**
     * prints  the  list
     */
    void printElements();

    /**
     *  destructor must  free  all  allocated  memory
     */
    ~LinkedList();
};

#endif
/*  LINKEDLIST_HPP_  */