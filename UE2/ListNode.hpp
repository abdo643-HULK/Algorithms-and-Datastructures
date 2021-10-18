#ifndef LISTNODE_HPP_
#define LISTNODE_HPP_
class ListNode
{
public:
    int element;    // contains the data element
    ListNode *next; // pointer to the next element in the list

    // Constructors
    ListNode();
    ListNode(int d);
    ListNode(int d, ListNode *n);
};
#endif /* LISTNODE_HPP_ */