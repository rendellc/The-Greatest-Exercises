#pragma once
#include <iostream>
#include "Tree.h"
using namespace diy; // namespace for "Tree.h"

template <typename T>
class Set : public Tree {
	
public:
	/** insert element into set, returns true if inserted
		returns false if element already in set and doesnt insert **/
	bool insert(const T& element) {
		Node<T>* check = root;

		while (true) {
			if (element < check->data) {
				if (check->left != nullptr)
					check = check->left;
				else {// insert at check->left
					check->left = new Node(element);
					return true;
				}
			}
			else if (element == check->data) {
				return false; // element already exists, don't add
			}
			else {
				if (check->right != nullptr)
					check = check->right;
				else { // insert at check->right
					check->right = new Node(element);
					return true;
				}
			}

		}

	}
	bool exists(const T& element) const {
		Node<T>* check = root;
		// depth first search
		while (true) {
			if (element < check->data) {

			}

		}

	}

	/*
		        r
		1          2
		x    y     z      w
	a b  c d  e   f   g h
	*/


	// removes element from 
	bool remove(T element) {
			
	}

};
