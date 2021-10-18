//
// Created by Abdo on 18.10.21.
//

#include "ListNode.hpp"

ListNode::ListNode() {
    next = nullptr;
}

ListNode::ListNode(int d) {
    element = d;
    next = nullptr;
}

ListNode::ListNode(int d, ListNode *n) {
    element = d;
    next = n;
}