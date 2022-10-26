#ifndef BINARY_SEARCH_TREE_CPP
#define BINARY_SEARCH_TREE_CPP

#include "binarySearchTree.h"
#include <string>
#include <ctime>

#define RIGHT true
#define LEFT false

#define SUCCESSOR true
#define PREDECESSOR false

// Implementation of Binary Search Tree (BST), insertion, deletion, display,
// Also includes Binary Search


// a constructor that creates an empty binary tree
BinarySearchTree::BinarySearchTree() {
	// create a NULL root pointer
	this->root = NULL;
}

// constructor to generate a binary search tree from a given array of integer values
// @parameters:
//		array_of_values = an array of integers to construct the tree
//		size_of_array = the size of the given array
BinarySearchTree::BinarySearchTree(int* array_of_values, int size_of_array) {
	// create a NULL root pointer
	this->root = NULL;

	// insert the values in the given array into the tree one by one
	for(int i = 0; i < size_of_array; i++) {
		this->insert(array_of_values[i]);
	}
}

// construct a bst with num_of_nodes nodes randomly, with a given seed and a given max value
// @parameters:
//		seed = a seed for the random generator. Enter -1 for random seed
//		num_of_nodes = an int specifing how many nodes we want for the tree
BinarySearchTree::BinarySearchTree(int seed, int num_of_nodes, int max_value) {
	// create a NULL root pointer
	this->root = NULL;
	
	// value to add
	int value; 

	// if the seed is -1, randomly generate a seed. Otherwise, use the given seed
	if(seed == -1) {
		srand(time(NULL));
	}
	else {
		srand(seed);
	}

	// if max_value < num_of_nodes, then reset max value to be 10 higher
	if(max_value < num_of_nodes) {
		max_value = num_of_nodes + 10;
	}

	for(int i = 0; i < num_of_nodes; i++) {
		value = rand() % (max_value);

		// if the random number has already been generated and inserted into the tree,
		//		try again
		while(!this->insert(value)) {
			value = rand() % max_value;
		}	
		cout << value << ", ";	
	}

	cout << endl;
}


// a destructor to delete the root pointer
BinarySearchTree::~BinarySearchTree() {
	// delete all the pointers (nodes) from the tree, as they have all been allocated
	//		dynamically in the insert funciton
		// a queue of bst_node pointers to help traverse the tree in breadth first approach
	queue<bst_node*> nodes_queue;
	
	// will store the front of the queue in the while loop
	bst_node* current_node;

	int num_of_nodes_on_level = 1;

	if(this->root != NULL) {
		nodes_queue.push(this->root);
	}

	string which_child;

	cout << "*****************************************************" << endl;
	cout << "*****************************************************" << endl;
	while(!nodes_queue.empty()) {

		while(num_of_nodes_on_level > 0) {
			current_node = nodes_queue.front();
			
			// before deleting the node
			// push the children of the given node into the queue. After push, the queue
			//		has a mix of nodes from the current and next levels. 
			if(current_node->left_child != NULL) {
				nodes_queue.push(current_node->left_child);
			}
			if(current_node->right_child != NULL) {
				nodes_queue.push(current_node->right_child);
			}


			// delete the node
			delete current_node;
			current_node = NULL;
			
			// pop the front node from the queue
			nodes_queue.pop();
			// decrement the number of nodes in the queue
			num_of_nodes_on_level--;


		}		
		num_of_nodes_on_level = nodes_queue.size();
		
	}
}


// inserts a new node with the given value into the bst with the given root.
// @parameters:
//		value = the value that the new node will have in the tree
// @return
//		true = if the value was successfully inserted
//		false = otherwise. e.g. the value is already in the tree.
bool BinarySearchTree::insert(int value) {
	// create a new node
	bst_node* new_node = new bst_node;
	
	// set the given value to the new node, later to be inserted into the tree. 
	new_node->value = value;

	// if the tree is empty, insert the new node as the root of the tree
	if(this->root == NULL) {
		this->root = new_node;

		return true;
	}
	else {
		// use current_node to traverse the root and find the proper place to insert the
		//		new node
		bst_node* current_node = this->root;

		// will be used as the parent of the new node.
		bst_node* parent_node = current_node;

		// LEFT if the new node should be inserted as the left child of the parent_node
		//		(after the following while loop terminates)
		// RIGHT if the new node should be inserted as the right child of the parent_node
		bool left_or_right;

		// true if a node with the given value is found.
		bool found = false;

		// while there is a node in the path to traverse, continue with the loop.
		while(current_node != NULL) {
			// reset parent_node
			parent_node = current_node;

			// go to the left of current_node
			if(value < current_node->value) {
				left_or_right = LEFT;
				current_node = current_node->left_child;
			}
			// go to the right of current_node
			else if(value > current_node->value) {
				left_or_right = RIGHT;
				current_node= current_node->right_child;
			}
			// node with the given value already exists in the tree, so do not insert
			else {
				// the node is found
				found = true;

				current_node = NULL;
			}
		}

		// if the value was not found in the tree, insert a node with that value.
		if(!found) {
			// set the new node as either left or right child of the parent node,
			//		based on left_or_right variable's value.
			if(left_or_right == RIGHT) {
				parent_node->right_child = new_node;
				new_node->which_child = RIGHT;
			}
			else {
				parent_node->left_child = new_node;
				new_node->which_child = LEFT;
			}
			// set the parent of the newly added node to be the parent_node
			new_node->parent = parent_node;
		}

		cout << "root = " << this->root->value << endl;
		// if the value was found, return false
		if(found) {
			return false;
		}
		else {
			return true;
		}
	}


}


// displays the tree with breadth_first traversal
//	@parameters:
//		root = the root of the tree to be displayed
void BinarySearchTree::display_tree() {
	// a queue of bst_node pointers to help traverse the tree in breadth first approach
	queue<bst_node*> nodes_queue;
	
	// will store the front of the queue in the while loop
	bst_node* current_node;

	int num_of_nodes_on_level = 1;

	if(this->root != NULL) {
		nodes_queue.push(this->root);
	}

	string which_child;

	cout << "*****************************************************" << endl;
	cout << "*****************************************************" << endl;
	while(!nodes_queue.empty()) {

		while(num_of_nodes_on_level > 0) {
			current_node = nodes_queue.front();

			if(current_node->which_child == RIGHT) {
				which_child = "R";
			}
			else {
				which_child = "L";
			}

			if(current_node != NULL) {
				cout << current_node->value;
			}
			if(current_node->parent != NULL) {
				cout << "(" << which_child << "," << current_node->parent->value << ")   ";
			}
			
			// push both children of the current_node into the queue
			if(current_node->left_child != NULL) {
				nodes_queue.push(current_node->left_child);
			}
			if(current_node->right_child != NULL) {
				nodes_queue.push(current_node->right_child);
				
			}
			
			// pop the front node from the queue
			nodes_queue.pop();
			// decrement the number of nodes in the queue
			num_of_nodes_on_level--;



		}		
		num_of_nodes_on_level = nodes_queue.size();
		

		cout << endl;
		cout << "-------------------------------------------" << endl;
	}

}

// !!! pass in the value, not the node
// deletes the node with the given value using inorder successor
// keeps the binary search tree nature of the tree after deletion
// @parameters
//		value = the value of the node to be deleted
// @return:
//		true = if the deletion is successful
//		false otherwise
bool BinarySearchTree::delete_node(int value) {
	bst_node* node_to_del = this->binary_search(value);
	if(node_to_del == NULL) {
		return false;
	}
	else {
		this->delete_node(node_to_del);
		return true;
	}
}

// deletes the node using inorder successor
// keeps the binary search tree nature of the tree after deletion
// @parameters
//		node_to_del = a pointer to the node to be deleted
void BinarySearchTree::delete_node(bst_node* node_to_del) {
	// Case 0: tree is empty. don't do anything
	if(this->root == NULL) {
		// don't do anything
	}
	// Case 1: the node to be deleted is a leaf node, just delete it, and set it's parent's
	//		appropriate child to null
	else if(node_to_del->left_child == NULL && node_to_del->right_child == NULL) {
		// the node is the root with no children
		if(node_to_del->parent == NULL) {
			delete node_to_del;
			node_to_del = NULL;

			this->root = NULL;
		}
		// the node is a leaf node
		else {
			// if the node to be deleted is the right child of its parent, set the right child
			// 		of its parent to NULL
			if(node_to_del->which_child == RIGHT) {
				node_to_del->parent->right_child = NULL;
		   		delete node_to_del;			
				node_to_del = NULL;
			}
			else {
				node_to_del->parent->left_child = NULL;
		   		delete node_to_del;			
				node_to_del = NULL;
			}

		}
	}
	// Case 2a: the node to be deleted has 1 child, left 
	else if(node_to_del->right_child == NULL && node_to_del->left_child != NULL) {
		// if the node is the root node
		if(node_to_del->parent == NULL) {
			// set the left child of the node to be the root
			this->root = node_to_del->left_child;
			this->root->parent = NULL;

			// delete the node
			delete node_to_del;			
			node_to_del = NULL;
		} else {
			// reset the child and parent pointers appropriately before deleting the 
			//		node_to_del
			node_to_del->left_child->parent = node_to_del->parent;
			if(node_to_del->which_child == RIGHT) {
				node_to_del->parent->right_child = node_to_del->left_child;
				node_to_del->left_child->which_child = RIGHT;
			} else {
				node_to_del->parent->left_child = node_to_del->left_child;
			}

			// delete the node
			delete node_to_del;
			node_to_del = NULL;
		}
	}
	// Case 2b: the node to be deleted has 1 child, right 
	else if(node_to_del->right_child != NULL && node_to_del->left_child == NULL) {
		// if the node is the root node
		if(node_to_del->parent == NULL) {
			// set the right child of the node to be the root
			this->root = node_to_del->right_child;
			this->root->parent = NULL;

			// delete the node
			delete node_to_del;
			node_to_del = NULL;
		} else {
			// reset the child and parent pointers appropriately before deleting the 
			//		node_to_del
			node_to_del->right_child->parent = node_to_del->parent;
			if(node_to_del->which_child == RIGHT) {
				node_to_del->parent->right_child = node_to_del->right_child;
			} else {
				node_to_del->parent->left_child = node_to_del->right_child;
				node_to_del->right_child->which_child = LEFT;
			}
			// delete the node
			delete node_to_del;
			node_to_del = NULL;
		}
	}
	// Case 3: the node has 2 children
	else {

		// the node to be deleted has a right child
		// find its inorder successor
		// find the inorder of the node to be deleted
		bst_node* inorder = find_inorder(node_to_del->value, SUCCESSOR);

		
		// change the value of node_to_delete with the value of inorder successor
		node_to_del->value = inorder->value;

		// recursively call delete node to delete the inorder successor found above
		delete_node(inorder);
	}

}


// finds the inorder successor/predecessor of the given node. we use binary_search
//		function to get the node corresponding to the given value
// @parameters:
//		value = the value of the node whose inorder successor we are trying to find
// 		successor_or_predecessor = true or false
//			true if it finds successor
//			false if it finds predecessor
BinarySearchTree::bst_node* BinarySearchTree::find_inorder(int value, bool successor_or_predecessor) {
	bst_node* node = binary_search(value);
	
	bst_node* inorder;

	// if the node has no children, return NULL
	if(node == NULL || (node->left_child == NULL && node->right_child == NULL)) {
		cout << "Node is null" << endl;
		inorder = NULL;
		return inorder;
	}
	// find inorder successor
	if(successor_or_predecessor == SUCCESSOR) {
		inorder = node->right_child;
		
		// go right, then keep going left
		if(node->right_child != NULL) {
			bst_node* inorder = node->right_child;
			// while there is left_child, keep going down the tree
			while(inorder->left_child != NULL) {
				inorder = inorder->left_child;
			}


			// after the while, loop inorder_successor is the inorder successor of 
			//		the node
			return inorder;
		}
	}
	// PREDECESSOR
	else {
		inorder = node->left_child;

		// go left, then keep going right
		if(node->left_child != NULL) {
			// while there is right child, keep going down the tree
			while(inorder->right_child != NULL) {
				inorder = inorder->right_child;
			}

			// return the inorder
			return inorder;
		}
	}
}

// binary search that uses another recursive function to do the actual search.
// @parameters
//		value = the value to be searched for
BinarySearchTree::bst_node* BinarySearchTree::binary_search(int value) {
	this->binary_search(this->root, value);
}

// search for the node with the given value
// @parameters
//		root = a pointer to the root of the tree (or subtree)
//		value = the value to be searched for
// @return
//		a reference to a pointer to the node that has the given value
//		or 
//		NULL if the value is not found in the bst
//		it is a reference because we need to be able to delete that node in case this
//			function is called from delete_node
BinarySearchTree::bst_node* BinarySearchTree::binary_search(BinarySearchTree::bst_node* root, int value) {
	if(root == NULL) {
		bst_node* node;
		node = NULL;
		return node;
	} else {
		// search in the right subtree
		if(value > root->value) {
			this->binary_search(root->right_child, value);
		} 
		// search in the left subtree
		else if(value < root->value) {
			this->binary_search(root->left_child, value);
		}
		// node is found
		else {
			return root;
		}
	}
}


// determine if the given tree with the given root node is binary. (left child is
//		less than the parent, and right child is greater than the parent, for every node)
// Note: It is assumed that duplicates are not allowed.
// @return
//		true = if the tree is binary (left child of any node is either NULL or < node)
//		false = if the tree is not binary
bool BinarySearchTree::is_binary_tree() { 
	// stores the nodes of a tree in a breadth-first traversal. Updated throughout the
	//		inner while loop
	queue<BinarySearchTree::bst_node*> nodes_on_level;
	
	// stores the number of nodes on a given level.
	int num_of_nodes_on_level;

	if(this->root != NULL) {
		// push the node on the zeroth level (root) into the queue
		nodes_on_level.push(this->root);
		num_of_nodes_on_level = 1;
	} else {
		//Tree is empty, so return true
		return true;
	}


	// go through every node of each level (breadth-first).
	//	If, for any of them, 
	//		node->value <= node->left_child->value
	//				or
	//		node->value >= node->right_child->value
	//	then return false

		// at the beginning of the loop, the queue (nodes_on_level) contains all the nodes
	//		on the current level
	while(nodes_on_level.size() > 0) {
		// traverse the nodes of the current level
		while(num_of_nodes_on_level > 0) {
			// display the node

			// push the children of the given node into the queue. After push, the queue
			//		has a mix of nodes from the current and next levels.
			if(nodes_on_level.front()->left_child != NULL) {
				// if the left child is not less than the node, return false
				if(nodes_on_level.front()->left_child->value >= nodes_on_level.front()->value) {
					cout << nodes_on_level.front()->value << "has a wrong left child" << endl;
					return false;
				}
				// else, keep checking
				else {
					nodes_on_level.push(nodes_on_level.front()->left_child);
				}
			}			
			if(nodes_on_level.front()->right_child != NULL) {
				// if the right child is not greateer than the node, return false
				if(nodes_on_level.front()->right_child->value <= nodes_on_level.front()->value) {
					cout << nodes_on_level.front()->value << "has a wrong right child" << endl;
					return false;
				}
				// else, keep searching the tree
				else {
					nodes_on_level.push(nodes_on_level.front()->right_child);
				}
			}

			// Additional check, in case recoloring is not done properly, or parent
			//		attribute is not reset properly
			// do the same test as above, but this time starting with the child node.
			//		that is, make sure that the parent has a larger value than the node
			//		if the node is a left child, and a lower value if the node is a 
			//		right child
			if(nodes_on_level.front()->parent != NULL) {
				// the node is a right child. it must have a value greater than the value
				//	of its parent
				if(nodes_on_level.front()->which_child == RIGHT) {
					if(nodes_on_level.front()->value <= nodes_on_level.front()->parent->value) {
						cout << nodes_on_level.front()->value << "has a wrong parent" << endl;
						// not a binary tree
						return false;
					}
				}
				else {
					if(nodes_on_level.front()->value >= nodes_on_level.front()->parent->value) {
						cout << nodes_on_level.front()->value << "has a wrong parent" << endl;
						// not a binary tree
						return false;
					}
				}
			}

			// remove from the queue and decrement num_of_nodes_on_level
			nodes_on_level.pop();
			num_of_nodes_on_level--;
		}

		// reset the number of nodes on the current level for the next iterations of the
		//		inner while loop
		num_of_nodes_on_level = nodes_on_level.size();
	}

	// if we get to this point, then the tree is binary
	return true;
}


// determine if the tree is empty
bool BinarySearchTree::is_empty() {
	if(this->root == NULL) {
		return true;
	}
	else {
		return false;
	}
}

#endif