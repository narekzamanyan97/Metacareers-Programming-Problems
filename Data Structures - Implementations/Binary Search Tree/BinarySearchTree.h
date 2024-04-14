#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <iostream>
#include <queue>
using namespace std;

class BinarySearchTree {
private:

	////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////
	//							Declarations of structure and functions
	// a node structure for a binary search tree.
	struct bst_node {
		// pointers to the parent and children bst nodes
		bst_node* parent = nullptr;
		bst_node* left_child = nullptr;
		bst_node* right_child = nullptr;

		// RIGHT if this node is the right child of its parent
		// LEFT otherwise
		bool which_child;

		// the value of the node
		int value;
	};

	bst_node* root;

public:
	// construct an empty binary search tree
	BinarySearchTree();

	// construct a bst from a given array of integer values
	BinarySearchTree(int* array_of_values, int size_of_array);

	// construct a bst with number_of_nodes nodes randomly, with a given seed and a given max value
	BinarySearchTree(int seed, int num_of_nodes, int max_value);

	// delete the dynamically allocated pointer
	~BinarySearchTree();

	// display the tree with levels
	void display_tree();

	// insert a new node into the tree with the given value
	bool insert(int value);

	// delete the node having the given value
	bool delete_node(int value);

	// delete the node with the given pointer pointing at it
	void delete_node(bst_node* node_to_del);

	// find and return the inorder successor of the node having the given value
	bst_node* find_inorder(int value, bool successor_or_predecessor);

	// search and return the node with the given value
	bst_node* binary_search(int value);

	// binary search that uses another recursive function to do the actual search.
	bst_node* binary_search(BinarySearchTree::bst_node* root, int value);


	// determine if the given tree with the given root node is binary. (left child is
	//		less than the parent, and right child is greater than the parent, for every node)
	// Note: It is assumed that duplicates are not allowed.
	bool is_binary_tree();


	// determine if the tree is empty
	bool is_empty();
};

#endif