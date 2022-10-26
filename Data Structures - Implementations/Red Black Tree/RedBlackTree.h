#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include <iostream>
#include <queue>
#include <string>
#include <sstream>
#include <time.h>
#include <stdlib.h>

#define RIGHT true
#define LEFT false

#define RED true
#define BLACK false

#define DELETE true
#define INSERT false
using namespace std;

struct node {
	node* left_child = NULL;
	node* right_child = NULL;
	node* parent = NULL;

	bool which_child;

	bool color;

	// for deletion operation
	bool is_double_black;

	int value;
};



class RedBlackTree {
private:
	// stores the root of the tree
	node* root;

	// recursively finds the node that has the given value
	node* binary_search(node* root, int value);

	// recursive helper function to flatten the tree into an array of values
	int to_array_helper(node* root, int* flattened_tree, int& size_of_array);


public:

	// constructors
	RedBlackTree();
	RedBlackTree(int* array_of_values, int size_of_array);
	RedBlackTree(int seed, int number_of_values, int max_value);

	// destructor. Delete all the nodes of the tree. breadth first approach
	~RedBlackTree();

	// return true if the tree is empty (root node is NULL)
	bool is_empty();


	// insert a value into a given red-black tree.
	bool insert(int value);

	// helper function for insert(). implementation of cases 4a and 4b as they are recursive.
	void insert_helper(node* new_node);

	// do RR/RL/LL/LR rotations, respectively
	void RR_rotation(node* parent_node, bool del_or_insert);
	void RL_rotation(node* new_node);
	void LL_rotation(node* parent_node, bool del_or_insert);
	void LR_rotation(node* new_node);

	// use breadth first search to display the tree
	void display_tree();

	// deletes the node with the given value using inorder successor
	void delete_node(node* node_to_del);

	// finds the inorder successor node of the given node node_to_del
	node* find_inorder(node* node_to_del);

	// finds the node that has the given value using the private binary_search function
	node* binary_search(int value);

	
	bool is_binary_tree();


	bool is_red_black_tree();

	// Recursive implementation of checking whether a given tree (with the given root) is
	//		Red-Black
	bool is_red_black_tree_helper1(node* root, int running_total, int tot_bl_nodes_on_leftmost_path);

	// do a depth first search, find the first leaf node, and return the number of black
	//		nodes in the path. This value will then be used in the is_red_black_tree()
	//		function
	int is_red_black_tree_helper2();

	// flatten the tree into an array of values
	int to_array(int* flattened_tree);

};

#endif