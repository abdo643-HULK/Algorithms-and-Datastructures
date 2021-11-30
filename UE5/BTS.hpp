//
// Created by Abdo on 15.11.21.
//

#ifndef UE05__BTS_HPP_
#define UE05__BTS_HPP_

#include "iostream"

using namespace std;

template<typename K, typename V>
class BST {
	enum Side {
		left, right
	};

	struct Node {
		K key;
		V value;
		Node *left, *right;
		Node(K k, V v) : key(k), value(v), left(nullptr), right(nullptr) {}

		bool operator<(const Node &other) {
			return key < other.key;
		}

		bool operator>(const Node &other) {
			return key > other.key;
		}

		bool operator>=(const Node &other) {
			return !(*this < other);
		}

		bool operator<=(const Node &other) {
			return !(*this > other);
		}

		friend std::ostream &operator<<(std::ostream &os, const Node &node) {
			os << "(" << node.key << ": " << node.value << ")";
			return os;
		}
	};

  private:
	Node *root;

	// find a key recursively
	bool contains(Node *node, K key) {
		if (node == nullptr) return false;

		if (node->key == key) return true;
		if (node->key > key) return contains(node->left, key);
		if (node->key < key) return contains(node->right, key);

		return false;
	}

	void inorder(Node *node) const {
		if (node == nullptr) return;
		// Traverse left
		inorder(node->left);

		// dereference node and use the overloading
		cout << *node << " -> ";

		// Traverse right
		inorder(node->right);
	}

	/**
	 * find the key by looping and returning early
	 *
	 * @param key
	 * @return the Node with the key
	 */
	Node *findNode(K key) {
		auto node = root;

		while (node != nullptr) {
			if (key == node->key) return node;
			if (key < node->key) node = node->left;
			if (key > node->key) node = node->right;
		}

		return nullptr;
	}

	/**
	 * get the parent Element by looping and
	 * checking both sides and returning early if
	 * they are equal. if not check the key and assign the
	 * new current depending on the key
	 *
	 * @param node
	 * @return parent node of the node param
	 */
	Node *getParent(Node *node) {
		Node *current = root;
		if (node == nullptr || current == nullptr) return nullptr;

		while (current != nullptr) {
			if (current->left == node) return current;
			if (current->right == node) return current;

			if (node->key < current->key) {
				current = current->left;
			} else {
				current = current->right;
			}
		}

		return nullptr;
	}

//	Node *successor(Node *node) {
//		if (node->right != nullptr) return getMinimum(node->right);
//		Node *y = getParent(node);
//		while (y != nullptr && node == y->right) {
//			node = y;
//			y = getParent(y);
//		}
//		return y;
//	}

//	void remove(Node *node) {
//		if (node == nullptr) return;
//		cout << "removing: " << (*node) << "\n";
//		remove(node->left);
//		remove(node->right);
//		delete node;
//	}

  public:
	BST() {
		root = nullptr;
	}

	/**
	 * inserts an element into the binary search tree the elements are sorted according to K key
	 *
	 * @param key
	 * @param value
	 */
	void insertElement(K key, V value) {
		const auto newNode = new Node(key, value);

		if (root == nullptr) return root = newNode;

		auto current = root;

		// could be done in the loop, but I am trying
		// to get better at c++ lambdas
		const auto addSide = [&](const Side side) {
		  switch (side) {
			  case Side::left: {
				  if (current->left == nullptr) {
					  current->left = newNode;
					  return;
				  }
				  current = current->left;
				  break;
			  }
			  case Side::right: {
				  if (current->right == nullptr) {
					  current->right = newNode;
					  return;
				  }
				  current = current->right;
				  break;
			  }
		  }
		};

		while (current->key != key) {
			if (key < current->key) addSide(Side::left);
			else addSide(Side::right);
		}
	}

	/**
	 * removes the element referred to by key and deletes the allocated memory
	 *
	 * @param key the key to the element to remove
	 */
	void deleteElement(K key) {
		const auto node = findNode(key);
		if (node == nullptr) return;
		const auto parent = getParent(node);
		const auto next = node->right != nullptr ? node->right : node->left;

		if (parent->left == node) {
			parent->left = next;
		} else {
			parent->right = next;
		}

		delete node;
	}

	/**
	 * @param key
	 * @return true if the binary search tree contains the given key false otherwise
	 */
	bool containsKey(K key) {
		return contains(root, key);
	}

	/**
	 * @param key
	 * @return pointer to the value which is stored under key
	 */
	V *getValue(K key) {
		auto node = findNode(key);
		return node != nullptr ? &node->value : nullptr;
	}

	/**
	 * because a BST has all the small elements on the left side
	 * we recursively get the most left element
	 *
	 * returns a pointer to the value which is referred to by the smallest key
	 *
	 * @return pointer to the value of the smallest key
	 */
	V *getMinimum() {
		if (root == nullptr) return nullptr;
		Node *node = root;

		while (node->left != nullptr) {
			node = node->left;
		}

		return &node->value;
	}

	/**
	 * returns a pointer to the value which is referred to by the highest key
	 *
	 * @return pointer to the value of the highest key
	 */
	V *getMaximum() {
		if (root == nullptr) return nullptr;
		Node *node = root;

		while (node->right != nullptr) {
			node = node->right;
		}

		return &node->value;
	}

	/**
	 * prints the elements in the tree in order,
	 * for each node the pair (key, value) should be printed.
	 */
	void printInOrder() const {
		inorder(root);
		cout << "end" << "\n";
	}

	/**
	 * removes all nodes of the tree and deletes the memory.
	 * Trying to get better with lambdas
	 */
	void clear() {
		/// version 1
//		remove(root);

		/// version 2
		const function<void(Node *)> remove = [&](Node *node) {
		  if (node == nullptr) return;
//		  cout << "removing: " << (*node) << "\n";
		  remove(node->left);
		  remove(node->right);
		  delete node;
		};

		remove(root);

		/// version 3
//		const auto remove = [&](Node *node, auto &remove) {
//		  if (node == nullptr) return;
//		  cout << "removing: " << node->key << "\n";
//		  remove(node->left, remove);
//		  remove(node->right, remove);
//		  delete node;
//		};
//
//		remove(root, remove);
	}

	virtual ~BST() {
		clear();
	}
};

#endif //UE05__BTS_HPP_
