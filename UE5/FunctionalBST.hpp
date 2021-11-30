//
// Created by Abdo on 15.11.21.
//

#ifndef UE05__FUNCTIONALBST_HPP_
#define UE05__FUNCTIONALBST_HPP_


#include "iostream";

template<typename K, typename V>
class FunctionalBST {
	struct Node {
		K key;
		V value;
		Node *left, *right;
		Node(K k, V v) : key(k), value(v), left(nullptr), right(nullptr) {};
		bool operator<(const Node &other);
		bool operator>(const Node &other);
		bool operator>=(const Node &other);
		bool operator<=(const Node &other);
		friend std::ostream &operator<<(std::ostream &os, const Node &node);

		bool containsKey(K key) {
			if (this->key == key) {
				return key;
			}
		}
	};

  private:
	Node *root = nullptr;

	bool contains(K key) {
		auto current = root;

		while (current->key != key) {

		}
	}

  public:
	FunctionalBST() {
	};

	/**
	 * inserts an element into the binary search tree the elements are sorted according to K key
	 *
	 * @param key
	 * @param value
	 */
	void insertElement(K key, V value) {
		if (root != nullptr) {

		} else {
			root = Node(key, value);
			return;
		}
	};

	/**
	 * @param key
	 * @return true if the binary search tree contains the given key false otherwise
	 */
	bool containsKey(K key) {
		root->containsKey(key);

	};

	// returns a pointer to the value which is stored under key
	V *getValue(K key);

	// returns a pointer to the value which is referred to by the smallest key

	V *getMinimum();
	/**
	 * returns a pointer to the value which is referred to by the highest key
	 *
	 * @return pointer to the highest value
	 */
	V *getMaximum();

	/**
	 * removes the element referred to by key and deletes the allocated memory
	 *
	 * @param key the key to the element to remove
	 */
	void deleteElement(K key);

	/**
	 * prints the elements in the tree in order,
	 * for each node the pair (key, value) should be printed.
	 */
	void printInOrder() const {

	};

	// removes all nodes of the tree and deletes the memory
	void clear() {

	};

	virtual ~FunctionalBST() {
		clear();
	};
};

#endif //UE05__FUNCTIONALBST_HPP_
