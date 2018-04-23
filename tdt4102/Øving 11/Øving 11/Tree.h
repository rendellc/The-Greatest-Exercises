#pragma once
#include <iostream>
#include <algorithm>

namespace diy {

	template <typename T>
	struct Node
	{
		T data;
		Node* left;
		Node* right;
		Node(const T& data) : data(data), left(nullptr), right(nullptr) {}
		bool operator< (const Node& rhs) {
			return data < rhs.data;
		}
		friend std::ostream& operator<< (std::ostream& out, const Node<T>& node);

	};
	

	/*	*** Generic tree class ***
		Type requirement: < operator, no arrays
		Allows duplicate values */
	template <typename T>
	class Tree {
	private:
		Node<T>* root;

		/** inserts node to the right,
		return true if inserted
		false otherwise (if node is occupied) **/
		bool insertRight(Node<T>* parent, const T& data) {
			if (parent->right != nullptr)
				return false;

			parent->right = new Node<T>(data);
			return true;
		}

		/** inserts node to the left,
		return true if inserted
		false otherwise (if node is occupied) **/
		bool insertLeft(Node<T>* parent, const T& data) {
			if (parent->left != nullptr)
				return false;

			parent->left = new Node<T>(data);
			return true;
		}

		/* Delete all subtrees of parent */
		void deleteSubTree(Node<T>* parent) {
			if (parent->left != nullptr)
				deleteSubTree(parent->left);
			if (parent->right != nullptr)
				deleteSubTree(parent->right);

			// now all children are deleted
			delete parent->data; // will this work for arrays? 
		}

		/*  return Node* to minumum value of subtree starting with parent */
		Node<T>* minSubtree(Node<T>* parent) const {
			// everything in right subtree will be greater than or equal to everything in left subtree
			// so to find minimum we have to go as left as possible
			Node<T>* checkNode = parent;
			while (checkNode->left != nullptr) {
				checkNode = checkNode->left;
			}
			return checkNode;
		}

		/*  return Node* to maximum value of subtree starting with parent */
		Node<T>* maxSubtree(Node<T>* parent) const {
			// everything in right subtree will be greater than or equal to everything in left subtree
			// so to find maximum we have to go as right as possible
			// if there are duplicate elements, the right-most one will be returned
			Node<T>* checkNode = parent;
			while (checkNode->right != nullptr) {
				checkNode = checkNode->right;
			}
			return checkNode;
		}


	public:
		Tree(const T& rootElement) : root(new rootElement) {}
		~Tree() {
			deleteSubTree(root);
		}

	
		/*  insert node in correct place */
		void insert(const T& element, const Node<T>* parent = root) {
			if (element < parent->data) {
				if (parent->left == nullptr) {
					parent->left = new Node<T>(element); // base case, insert at left
				}
				else {
					insertElement(element, parent->left); // recursively call insertElement on left subtree
				}
			}
			else {
				if (parent->right == nullptr) {
					parent->right = new Node<T>(element); // base case, insert at right
				}
				else {
					return insertElement(element, parent->right); // recursively call insertElement on right subtree
				}
			}
		}

		/*	returns true if element exists
			false otherwise */
		bool exists(const T& element, Node<T>* checkFrom = root) const  {
			if (element < checkFrom->data) {
				if (checkFrom->left != nullptr)
					return exists(element, checkFrom->left);
				else
					return false;
			}	
			else if (checkFrom->data < element) {
				if (checkFrom->right != nullptr)
					return exists(element, checkFrom.right);
				else
					return false;
			}

			return checkFrom.data == element; // will this always be true?
		}

		/*  removes element from tree
			return true if element was removed
			false if element was not in tree
		*/
		bool remove(const T& element) {

		}

		friend std::ostream& operator<<(std::ostream& out, const Tree<T>& tree);
	};
};


template<typename T>
std::ostream& operator<<(std::ostream& out, const Node<T>& node) {
	out << node.data;
	return out;
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const Tree<T>& tree) {
	out << *(tree.root);
	whil


}