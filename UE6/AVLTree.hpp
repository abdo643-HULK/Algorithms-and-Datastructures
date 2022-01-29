//
// Created by abous on 22/11/2021.
//

#ifndef UE05_AVLTREE_HPP
#define UE05_AVLTREE_HPP

#include <cmath>
#include <iostream>
#include <functional>

using namespace std;

template<typename K>
class AVLTree {
    struct AVLNode {
        // data (also serves as key)
        K element;

        // pointer to the siblings and parents
        AVLNode *left, *right, *parent;
        int node_height;

        AVLNode(K k) : element(k), node_height(1), parent(nullptr), left(nullptr), right(nullptr) {};

        bool operator<(const AVLNode &other) {
            return element < other.element;
        }

        bool operator<=(const AVLNode &other) {
            return element > other.element;
        }

        bool operator>(const AVLNode &other) {
            return !(*this < other);
        }

        bool operator>=(const AVLNode &other) {
            return !(*this > other);
        }

        friend std::ostream &operator<<(std::ostream &os, const AVLNode &node) {
            os << "(" << node.element << " -> ";
            os << "height: " << node.node_height << ")";
            return os;
        }
    };

    AVLNode *root;
    int no_nodes;

private:
    // because we weight it with plus one
    // in updateHeight we need to return -1
    // if the node is empty
    int getHeight(AVLNode *node) {
        return node == nullptr ? 0 : node->node_height;
    }

    // Updates the height of the nodes
    void updateHeight(AVLNode *node) {
        node->node_height = 1 + max(getHeight(node->left), getHeight(node->right));
    }

    // returns the balance of the current node:
    // -1 if the right subtree is higher than the left subtree
    // +1 the left subtree is higher than the right subtree
    int getBalance(AVLNode *node) {
        if (node == nullptr) return 0;

        const int diff = getHeight(node->right) - getHeight(node->left);

        if (diff > 1) return -1;
        if (diff < -1) return 1;

        return 0;
    }

    // Recursively search the tree
    bool containsElement(AVLNode *node, K element) {
        if (node == nullptr) return false;

        if (node->element == element) return true;
        if (node->element > element) return containsElement(node->left, element);
        if (node->element < element) return containsElement(node->right, element);

        return false;
    }

    // Restructure and return new root node
    // from the slides
    AVLNode *rightRotate(AVLNode *y) {
        AVLNode *x = y->left;
        AVLNode *T2 = x->right;

        x->right = y;
        y->left = T2;

        x->parent = y->parent;
        y->parent = x;

        if (T2 != nullptr) T2->parent = y;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    // Restructure and return new root node
    // from the slides
    AVLNode *leftRotate(AVLNode *x) {
        AVLNode *y = x->right;
        AVLNode *T2 = y->left;

        y->left = x;
        x->right = T2;

        y->parent = x->parent;
        x->parent = y;

        if (T2 != nullptr) T2->parent = x;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    AVLNode *rebalance(AVLNode *node, K element) {
        updateHeight(node);
        const int balance = getBalance(node);

        // Left Left Case
        if (balance == 1 && element < node->left->element) {
            return rightRotate(node);
        }

        // Right Right Case
        if (balance == -1 && element > node->right->element) {
            return leftRotate(node);
        }

        // Left Right Case
        if (balance == 1 && element > node->left->element) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Left Case
        if (balance == -1 && element < node->right->element) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    AVLNode *rebalanceWithHeight(AVLNode *node) {
        updateHeight(node);
        const int balance = getBalance(node);

        // Left Left Case
        if (balance == 1 && getHeight(node->left->left) > getHeight(node->left->right)) {
            return rightRotate(node);
        }

        // Right Right Case
        if (balance == -1 && getHeight(node->right->right) > getHeight(node->right->left)) {
            return leftRotate(node);
        }

        // Left Right Case
        if (balance == 1 && getHeight(node->left->left) < getHeight(node->left->right)) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Left Case
        if (balance == -1 && getHeight(node->right->right) < getHeight(node->right->left)) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    AVLNode *getMinimum(AVLNode *node) {
        auto current = node;
        while (current->left != nullptr) {
            current = current->left;
        }

        return current;
    }

public:
    AVLTree() : root(nullptr), no_nodes(0) {};

    // Returns the number of nodes in the tree
    int size() {
        return no_nodes;
    }

    // returns the height of the tree, which is stored at the root node,
    // -1, if the tree is empty
    int height() {
        return no_nodes == 0 ? -1 : root->node_height;
    }

    // Insertion of new node
    void insert(K element) {
        const function<AVLNode *(AVLNode *)> insert = [&](AVLNode *node) -> AVLNode * {
            if (node == nullptr) {
                ++no_nodes;
                return new AVLNode(element);
            };

            if (node->element > element) node->left = insert(node->left);
            else if (element > node->element) node->right = insert(node->right);
            else return node;

            return rebalance(node, element);
        };

        root = insert(root);
    }

    bool find(K element) {
        return containsElement(root, element);
    }

    void deleteElement(K element) {
        // because we are returning nodes with the help of the
        // recursion we don't need to link to the parent manually
        const function<AVLNode *(AVLNode *, K)> deleteElement = [&](AVLNode *node, K element) -> AVLNode * {
            if (node == nullptr) return node;

            // case 1
            if (node->element > element) {
                node->left = deleteElement(node->left, element);
            }
                // case 2
            else if (node->element < element) {
                node->right = deleteElement(node->right, element);
            }
                // case 3
            else {
                // 3a) no children or 1
                if (node->left == nullptr || node->right == nullptr) {
                    const auto tmp = node;
                    node = node->left ? node->left : node->right;
                    delete tmp;
                    --no_nodes;
                }
                    // 3b) 2 children
                else {
                    AVLNode *minimum = getMinimum(node->right);
                    node->element = minimum->element;
                    node->right = deleteElement(node->right, node->element);
                }
            }

            if (node == nullptr) return node;

            // we can't use element, so we need
            // to rebalance with the height
            return rebalanceWithHeight(node);
        };

        root = deleteElement(root, element);
    }

    void printInOrder() const {
        const function<void(AVLNode *)> inorder = [&](AVLNode *node) {
            if (node == nullptr) return;
            inorder(node->left);
            cout << *node << " -> ";
            inorder(node->right);
        };

        inorder(root);
        cout << "end" << "\n";
    }

    // Removes all elements of the tree and frees allocated memory
    void clear() {
        const function<void(AVLNode *)> remove = [&](AVLNode *node) {
            if (node == nullptr) return;
            remove(node->left);
            remove(node->right);
            delete node;
        };
        no_nodes = 0;
        remove(root);
    }

    virtual ~AVLTree() {
        clear();
    }
};


#endif //UE05_AVLTREE_HPP
