#ifndef RED_BLACK_TREE_CPP
#define RED_BLACK_TREE_CPP

#include "RedBlackTree.h"


// default constructor
RedBlackTree::RedBlackTree() {
	// set the root to be nullptr
	this->root = nullptr;
}


// a constructor to build a tree using the values in a given array
// @parameters:
//		array_of_values = an array of int values to be inserted into the tree
//		size_of_array = the size of the input array
RedBlackTree::RedBlackTree(int* array_of_values, int size_of_array) {
	// set the root to be nullptr
	this->root = nullptr;

	// iterate over the array of values, and insert the values into the tree one by one
	for(int i = 0; i < size_of_array; i++) {
		this->insert(array_of_values[i]);
	}
}

// a constructor to build a tree using random values
// @parameters:
//		seed = a positive integer for the seed to be used in the random generator
//		number_of_values = the number of nodes to insert the tree
//		max_value = the max possible value for any node, has to be at least 2 times 
//			larger than the number_of_values
RedBlackTree::RedBlackTree(int seed, int number_of_values, int max_value) {
	// set the root to be nullptr
	this->root = nullptr;

	// max_value should be at least twice as large as number of values
	if(max_value < 2 * number_of_values) {
		// reset the max_value
		max_value = 2 * number_of_values;
	}

	// initialize random seed, if the given seed is -1
	if(seed == -1) {
		srand(time(nullptr));
	}
	else {
		srand(seed);
	}

	// value to add
	int value; 

	for(int i = 0; i < number_of_values; i++) {
		value = rand() % (max_value);

		// if the random number has already been generated and inserted into the tree,
		//		try again
		while(!this->insert(value)) {
			value = rand() % max_value;
		}	
	}

	cout << endl;
}


// destructor function to delete all the nodes of the tree. used in the destructor
RedBlackTree::~RedBlackTree() {
	// stores the nodes of a tree in a breadth-first traversal. Updated throughout the
	//		inner while loop
	queue<node*> nodes_on_level;
	
	// stores the number of nodes on a given level.
	int num_of_nodes_on_level;

	if(this->root != nullptr) {
		// push the node on the zeroth level (root) into the queue
		nodes_on_level.push(this->root);
		num_of_nodes_on_level = 1;
	} else {
		cout << "Tree is empty" << endl;
	}

	char left_or_right;

	// at the beginning of the loop, the queue (nodes_on_level) contains all the nodes
	//		on the current level
	while(nodes_on_level.size() > 0) {
		// traverse the nodes of the current level
		while(num_of_nodes_on_level > 0) {

			// before deleting the node
			// push the children of the given node into the queue. After push, the queue
			//		has a mix of nodes from the current and next levels.
			if(nodes_on_level.front()->left_child != nullptr) {
				nodes_on_level.push(nodes_on_level.front()->left_child);
			}			
			if(nodes_on_level.front()->right_child != nullptr) {
				nodes_on_level.push(nodes_on_level.front()->right_child);
			}

			// delete the node
			delete nodes_on_level.front();
			nodes_on_level.front() = nullptr;

			// remove from the queue and decrement num_of_nodes_on_level
			nodes_on_level.pop();
			num_of_nodes_on_level--;
		}

		// reset the number of nodes on the current level for the next iterations of the
		//		inner while loop
		num_of_nodes_on_level = nodes_on_level.size();
	}

}

// return true if the tree is empty. False otherwise.
bool RedBlackTree::is_empty() {
	if(this->root == nullptr) {
		return true;
	}
	else {
		return false;
	}
}

// determine if the given tree with the given root node is binary. (left child is
//		less than the parent, and right child is greater than the parent, for every node)
// Note: It is assumed that duplicates are not allowed.
// @return
//		true = if the tree is binary (left child of any node is either nullptr or < node)
//		false = if the tree is not binary
bool RedBlackTree::is_binary_tree() { 
	// stores the nodes of a tree in a breadth-first traversal. Updated throughout the
	//		inner while loop
	queue<node*> nodes_on_level;
	
	// stores the number of nodes on a given level.
	int num_of_nodes_on_level;

	if(this->root != nullptr) {
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
			if(nodes_on_level.front()->left_child != nullptr) {
				// if the left child is not less than the node, return false
				if(nodes_on_level.front()->left_child->value >= nodes_on_level.front()->value) {
					cout << nodes_on_level.front()->parent->value << endl;
					cout << nodes_on_level.front()->value << " has a wrong left child" << endl;
					cout << nodes_on_level.front()->left_child->value << " is the left child" << endl;
					if(nodes_on_level.front()->which_child == RIGHT) {	
						cout << "Right" << endl;

					}else {
						cout << "left " << endl;
					}

					return false;
				}
				// else, keep checking
				else {
					nodes_on_level.push(nodes_on_level.front()->left_child);
				}
			}			
			if(nodes_on_level.front()->right_child != nullptr) {
				// if the right child is not greateer than the node, return false
				if(nodes_on_level.front()->right_child->value <= nodes_on_level.front()->value) {
					cout << nodes_on_level.front()->parent->value << endl;
					cout << nodes_on_level.front()->value << " has a wrong right child" << endl;
					cout << nodes_on_level.front()->right_child->value << " is the right child" << endl;
					if(nodes_on_level.front()->which_child == RIGHT) {	
						cout << "Right" << endl;

					}else {
						cout << "left " << endl;
					}
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
			if(nodes_on_level.front()->parent != nullptr) {
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

// use the two helper functions is_red_black_tree_helper1/2 to determine if the given
//		tree is Red-Black or not
// @return
//		true = if the tree is Red-Black
//		false = otherwise
bool RedBlackTree::is_red_black_tree() {
	// first, check if the tree is a binary tree. If not, return
	if(this->is_binary_tree()) {
		int tot_bl_nodes_on_leftmost_path = this->is_red_black_tree_helper2(); 
		// At the beginning, the running total is 0
		return is_red_black_tree_helper1(this->root, 0, tot_bl_nodes_on_leftmost_path);	
	} else {
		cout << "Not a binary tree" << endl;
		// not a binary tree, so cannot be a red black tree.
		return false;
	}
	
}

// Recursive implementation of checking whether a given tree (with the given root) is
//		Red-Black
// Things to test:
// 1. Check  property 4 (all paths from any node to its NILL descendants contain the same
//		number of black nodes) 
//		compare the number of black nodes on the path of every leaf to the value returned
//		by is_red_black_tree_helper, which is the number of black nodes on the path to
//		the left-most node in the tree. Call the number of black nodes on the path to the 
//		left-most node tot_bl_nodes_on_leftmost_path. 
// 2. Check  property 3 (children of RED node are BLACK) 
// 		Makes sure a RED node does not have RED children
// @parameters:
//		root = a pointer to the root of the tree
//		running_total = the number of black nodes through the given path so far
//			at the beginning, the running total is 0
//		tot_bl_nodes_on_leftmost_path = the total number of black nodes through the path
//			that takes to the leftmost (smallest) node.
// @return
//		true = if every leaf has first_path number of black nodes from the root node
//		false = if there is at least one node that does not have first_path black nodes
//			traversed from the root
bool RedBlackTree::is_red_black_tree_helper1(node* root, int running_total, int tot_bl_nodes_on_leftmost_path) {
	// stores the return values of the leaf nodes in each path. Do not continue 
	//		recursion if its value becomes false
	bool passed_the_test = true;
	// base case. If the node is NIL node, compare it to the second argument
	if(root == nullptr) {
		// if the running total (the # of black nodes on the path to this node) is
		//		the same as the one for the left-most node, return true 
		if(running_total == tot_bl_nodes_on_leftmost_path) {
			// cout << "correct: " << running_total << endl;
			// cout << "-------------------------------------------------------" << endl;
			return true;
		}
		else {
			// cout << "Should be: " << tot_bl_nodes_on_leftmost_path << endl;
			// cout << "Is: " << running_total << endl;


			cout << "-------------------------------------------------------" << endl;
			return false;
		}
	}
	// not a base case, continue doing a depth first traversal
	else {
		// increment the running total of the black nodes on the path if the current 
		//		node (root) is BLACK
		if(root->color == BLACK) {
			running_total++;
		}
		///////////////////////////////////////////////////////////////////////////////
		// check property 3 before recursing
		// if the current node is RED
		if(root->color == RED) {
			// if any of its children are RED, set passed_the_test to false
			if(root->left_child != nullptr) {
				if(root->left_child->color == RED) {
					// cout << "Red node has a red child" << endl;
					// cout << root->value << " and " << root->left_child->value << endl;
					passed_the_test = false;
				}
			}

			// if the previous test is not passed, skip the right child
			if(root->right_child != nullptr && passed_the_test) {
				if(root->right_child->color == RED) {
					// cout << "Red node has a red child" << endl;
					// cout << root->value << " and " << root->right_child->value << endl;
					passed_the_test = false;
				}
			}
		} 

		// check property 3, this time, starting from the child, and going to the parent
		if(root->color == RED) {
			// if the node has a parent, then check if it is RED. If it is, then set
			//		passed_the_test to false
			if(root->parent != nullptr) {
				if(root->parent->color == RED) {
					passed_the_test = false;
				}
			}
		}


		///////////////////////////////////////////////////////////////////////////////
		// Recurse to check property 4
		// go to the left child (if passed_the_test from property 3 is true)
		if(passed_the_test) {
			// cout << "recursing left of " << root->value << endl;
			passed_the_test = is_red_black_tree_helper1(root->left_child, running_total, tot_bl_nodes_on_leftmost_path);
		}

		// go to the right child (if passed_the_test from the left recursion is true
		if (passed_the_test) {
			// cout << "recursing right of " << root->value << endl;
			passed_the_test = is_red_black_tree_helper1(root->right_child, running_total, tot_bl_nodes_on_leftmost_path);
		}	
	}


	return passed_the_test;

	
}

// do a depth first search, find the first leaf node, and return the number of black
//		nodes in the path. This value will then be used in the is_red_black_tree()
//		function
int RedBlackTree::is_red_black_tree_helper2() {
	node* current_node = this->root;

	// keeps track of the black nodes on the way to the left-most node
	int tot_bl_nodes_on_leftmost_path = 0;

	while(current_node != nullptr) {
		// if the current node to the left-most leaf is black
		if(current_node->color == BLACK) {
			// increment the number of black nodes on the path
			tot_bl_nodes_on_leftmost_path++;
		}
		
		current_node = current_node->left_child;
	}

	return tot_bl_nodes_on_leftmost_path;

}

// insert a value into a given red-black tree.
//		value = the value of the node to be isnerted
// @return
//		true = if the new node was successfully inserted
//		false = if it was not (a node with the same value is already in the tree)
bool RedBlackTree::insert(int value) {
	// Case 1: Tree is empty. Create a new Black node as the root
	if(this->root == nullptr) {
		this->root = new node;
		this->root->value = value;
		this->root->right_child = nullptr;
		this->root->left_child = nullptr;
		this->root->parent = nullptr;

		this->root->color = BLACK;
		this->root->is_double_black = false;
		return true;
	} 
	// Case 2: Tree is not empty. Create a new Red node
	else {
		// dynamically create a new node pointer
		node* new_node = new node;

		// set the value of the new node to the given value
		new_node->value = value;

		// set the double black to false (default)
		new_node->is_double_black = false;

		// the new node always has a color red.
		new_node->color = RED;

		// to traverse the tree and find the parent for the new node
		node* current_node = root;

		// keep track of the parent node of current node. The former will be the parent
		//		of the new node
		node* parent_node = current_node;


		// true if a node with the given value is found.
		bool found = false;

		// keep track of the last move in the while loop below. This tells us which
		//		child (right or left) of parent node the new node is
		bool right_or_left;

		// find the parent of the new node and whether it is a left or a right child
		while(current_node != nullptr && !found) {
			// reset parent node
			parent_node = current_node;

			// go to the left child
			if(value < current_node->value) {
				current_node = current_node->left_child;
				right_or_left = LEFT;
			}
			// go to the right child
			else if(value > current_node->value) {
				current_node = current_node->right_child;
				right_or_left = RIGHT;
			}
			// found the node, no need to insert it (because no duplicates are allowed)
			else {
				found = true;
			}
		}

		// Case 2: Tree is not empty. Create a new Red node
		// a node with the given value is not found, so insert as a child to the 
		//		parent_node to its right or left, depending on the value of right_or_left
		if(current_node == nullptr && !found) {
			if(right_or_left == RIGHT) {
				parent_node->right_child = new_node;
				new_node->which_child = RIGHT;
				new_node->parent = parent_node;
			} else {
				parent_node->left_child = new_node;
				new_node->which_child = LEFT;
				new_node->parent = parent_node;
			}
			// Case 4 is taken care of insert_helper function
			insert_helper(new_node);
		}

		// return the negation of found.
		//	if not found, it means the value was inserted
		//	if found, then it was not inserted.
		return !found;

	}
}

// implementation of cases 4a and 4b.
// @parameters
//		new_node = a pointer to the new node. It is assumed that new_node is already
//				inserted into the tree as a Red leaf node
void RedBlackTree::insert_helper(node* new_node) {
	// declare temporary pointers to store the parent, parent's parent, and parent's 
	//		sibling 
	node* parent_node = new_node->parent;
	node* parent_parent_node = parent_node->parent;
	node* parent_sibling_node;

	if(parent_parent_node != nullptr) {
		// store the uncle node as well (parent_sibling_node)
		if(parent_node->which_child == RIGHT){ 
			parent_sibling_node = parent_parent_node->left_child;
		} else {
			parent_sibling_node = parent_parent_node->right_child;
		}		
	}


	// Case 4: parent of new node is Red
	if(parent_node->color == RED) {
		// Case 4a: parent's sibling is Black or Null, then rotate and recolor
		if(parent_sibling_node == nullptr || parent_sibling_node->color == BLACK) {
			// do suitable rotation (RR, RL, LR, or LL)
			if(new_node->which_child == RIGHT && parent_node->which_child == RIGHT){
				RR_rotation(new_node->parent, INSERT);
			} else if(new_node->which_child == LEFT && parent_node->which_child == RIGHT) {
				RL_rotation(new_node);
			} else if(new_node->which_child == LEFT && parent_node->which_child == LEFT) {
				LL_rotation(new_node->parent, INSERT);
			} else {
				LR_rotation(new_node);
			}
		}
		// Case 4b: parent's sibling is Red, recolor parent and parent's parent
		//		if parent's parent is not the root, recolor it too. 
		//		set the new node to be the parent's parent, and call insert_helper
		//		recursively
		else {
			// recolor parent and parent's sibling
			parent_node->color = BLACK;
			parent_sibling_node->color = BLACK;

			// if parent's parent is not the root node, recolor it too (make it Red)
			if(parent_parent_node != this->root) {
				parent_parent_node->color = RED;
				
				// recursively call insert_helper with parent_parent_node being the 
				//		second argument (for new_node)
				insert_helper(parent_parent_node);
			}


		}

		// go through cases 3 and 4 again and recolor/rotate if necessary
	// Case 3: parent of new node is Black, exit
	}
}

// do an RR rotation
// @parameters
//		parent_node = a pointer to the parent of the node to be inserted or deleted.
//		del_or_insert = true if RR is used for deletion operation
//						false if this function is used for insert operation
//			The difference is to recolor or not recolor the parent and parents parent
void RedBlackTree::RR_rotation(node* parent_node, bool del_or_insert) {
	// declare temporary pointers to store the parent and parent's parent 
	// node* parent_node = new_node->parent;
	node* parent_parent_node = parent_node->parent;

	// steps are taken from notebook

	// step 1
	// cout << "parent_node->parent = parent_parent_node->parent " << parent_node->parent->value << " = " << parent_parent_node->parent->value << endl;
	parent_node->parent = parent_parent_node->parent;

	// step 2
	// reset parent's parent child (unless it is nullptr)
	if(parent_parent_node->parent != nullptr) {
		if(parent_parent_node->which_child == LEFT) {
			parent_parent_node->parent->left_child = parent_node;
			// reset which child of parent node
			parent_node->which_child = LEFT;
		}
		else {
			// cout << "parent_parent_node->parent->right_child = parent_node " << parent_parent_node->parent->right_child->value << " = " << parent_node->value << endl;
			parent_parent_node->parent->right_child = parent_node;

		}		
	}
	// step 3
	// cout << "parent_parent_node->parent = parent_node " << parent_parent_node->parent->value << " = " << parent_node->value << endl;
	parent_parent_node->parent = parent_node;
	// step 4
	if(parent_node->left_child != nullptr) {
		// cout << "parent_node->left_child->parent = parent_parent_node " << parent_node->left_child->parent->value << " = " << parent_parent_node->value << endl;
		parent_node->left_child->parent = parent_parent_node;
		// reset which child of parent_node->left_child
		parent_node->left_child->which_child = RIGHT; 
	}
	// step 5
	parent_parent_node->right_child = parent_node->left_child;
	// step 6
	parent_node->left_child = parent_parent_node;
	// reset which child of parents_parent node
	parent_parent_node->which_child = LEFT;


	// step 7: recolor parent and parent's parent nodes (if called for insertion)
	if(del_or_insert == INSERT) {
		parent_node->color = BLACK;
		parent_parent_node->color = RED;		
	}


	// reset the root if necessary
	if(this->root == parent_parent_node) {
		this->root = parent_node;
	}
}

// do an RL rotation
// @parameters
//		new_node = a pointer to the new node.
void RedBlackTree::RL_rotation(node* new_node) {
	// declare temporary pointers to store the parent and parent's parent 
	node* parent_node = new_node->parent;
	node* parent_parent_node = parent_node->parent;

	// step 1
	new_node->parent = parent_parent_node;

	// step 2
	parent_node->left_child = new_node->right_child;


	// step 3
	parent_parent_node->right_child = new_node;

	// reset which_child of new_node
	new_node->which_child = RIGHT;

	// step 4
	parent_node->parent = new_node;

	// step 5
	new_node->right_child = parent_node;
	// no need to reset which child of parent node, because it is already RIGHT

	// step 6
	if(parent_node->left_child != nullptr) {
		parent_node->left_child->parent = parent_node;
	
		// reset which child of parent_node->left_child child to LEFT
		parent_node->left_child->which_child = LEFT;
	}

	// call LL_rotation
	RR_rotation(parent_node->parent, INSERT);

}

// do an LL rotation
// @parameters
//		parent_node = a pointer to the parent of the node to be inserted or deleted.
//		del_or_insert = true if RR is used for deletion operation
//						false if this function is used for insert operation
//			The difference is to recolor or not recolor the parent and parents parent
void RedBlackTree::LL_rotation(node* parent_node, bool del_or_insert) {
	// declare temporary pointers to store the parent and parent's parent 
	// node* parent_node = new_node->parent;
	node* parent_parent_node = parent_node->parent;

	// step 1 
	parent_node->parent = parent_parent_node->parent;
	// step 2
	parent_parent_node->left_child = parent_node->right_child;
	// reset which child of parent_node->right_child
	if(parent_node->right_child != nullptr) {
		parent_node->right_child->which_child = LEFT;
	}
	// step 3
	if(parent_parent_node->parent != nullptr) {
		if(parent_parent_node->which_child == LEFT) {
			parent_parent_node->parent->left_child = parent_node;
		} else {
			parent_parent_node->parent->right_child = parent_node;
			// reset which child of parent node
			parent_node->which_child = RIGHT;
		}		
	}

	// step 4
	parent_parent_node->parent = parent_node;
	// step 5
	if(parent_node->right_child != nullptr) {
		parent_node->right_child->parent = parent_parent_node;
	}
	// step 6
	parent_node->right_child = parent_parent_node;
	// reset which child of parent_parent_node
	parent_parent_node->which_child = RIGHT;


	// step 7: recolor parent and parent's parent nodes (if called for insertion)
	if(del_or_insert == INSERT) {
		parent_node->color = BLACK;
		parent_parent_node->color = RED;		
	}


	// reset the root if necessary
	if(this->root == parent_parent_node) {
		this->root = parent_node;
	}
}

// do an LR rotation
// @parameters
//		new_node = a pointer to the new node.
void RedBlackTree::LR_rotation(node* new_node) {
	// declare temporary pointers to store the parent and parent's parent 
	node* parent_node = new_node->parent;
	node* parent_parent_node = parent_node->parent;

	// step 1 
	new_node->parent = parent_parent_node;

	// step 2
	parent_parent_node->left_child = new_node;

	// reset which child of new_node
	new_node->which_child = LEFT;

	// step 3
	parent_node->right_child = new_node->left_child;

	// step 4
	parent_node->parent = new_node;
	// step 5
	if(new_node->left_child != nullptr) {
		new_node->left_child->parent = parent_node;
		// reset which_child of new_node->left child
		new_node->left_child->which_child = RIGHT;
	}

	// step 6
	new_node->left_child = parent_node;
	// no need to change which child of parent node, because it is already LEFT

	// call LL_rotation
	LL_rotation(parent_node->parent, INSERT);

	// // delete local pointers
	// delete parent_node;
	// delete parent_parent_node;

	// parent_node = nullptr;
	// parent_parent_node = nullptr;
}

// use breadth first search to display the tree
void RedBlackTree::display_tree() {
	// stores the nodes of a tree in a breadth-first traversal. Updated throughout the
	//		inner while loop
	queue<node*> nodes_on_level;
	
	// stores the number of nodes on a given level.
	int num_of_nodes_on_level;

	if(this->root != nullptr) {
		// push the node on the zeroth level (root) into the queue
		nodes_on_level.push(this->root);
		num_of_nodes_on_level = 1;
	} else {
		cout << "Tree is empty" << endl;
	}

	char left_or_right;

	cout << "*********************************************************************\n";
	cout << "*********************************************************************\n";

	// at the beginning of the loop, the queue (nodes_on_level) contains all the nodes
	//		on the current level
	while(nodes_on_level.size() > 0) {
		// traverse the nodes of the current level
		while(num_of_nodes_on_level > 0) {
			// display the node
			cout << nodes_on_level.front()->value;
			if(nodes_on_level.front()->color == BLACK) {
				cout << "B";
			}
			else {
				cout << "R";
			}

			if(nodes_on_level.front()->which_child == LEFT) {
				left_or_right = 'L';
			} else {
				left_or_right = 'R';
			}
			// display the which_child and parent's value of the node
			if(nodes_on_level.front()->parent != nullptr) {
				cout << "(" << left_or_right << " of " << nodes_on_level.front()->parent->value << ")   ";
			}

			// push the children of the given node into the queue. After push, the queue
			//		has a mix of nodes from the current and next levels. num_of_nodes_on_level
			//		helps us stop the printing on the right node and start the iteration
			//		of the outer loop for the next level
			if(nodes_on_level.front()->left_child != nullptr) {
				nodes_on_level.push(nodes_on_level.front()->left_child);
			}			
			if(nodes_on_level.front()->right_child != nullptr) {
				nodes_on_level.push(nodes_on_level.front()->right_child);
			}

			// remove from the queue and decrement num_of_nodes_on_level
			nodes_on_level.pop();
			num_of_nodes_on_level--;
		}
		// NOTE: after the inner loop is done, the queue exclusively contains the nodes of the
		//		next level

		// reset the number of nodes on the current level for the next iterations of the
		//		inner while loop
		num_of_nodes_on_level = nodes_on_level.size();

		if(nodes_on_level.size() != 0) {
			// level breaks for visualization
			cout << "\n------------------------------------------------------------------\n"; 			
		}


	}
	cout << "\n*********************************************************************\n";
	cout << "*********************************************************************\n";
}


// deletes the node with the given value using inorder successor
// recurses until there is no DB problem
// keeps the binary search tree nature of the tree after deletion
// @parameters
//		value = the value of the node to be deleted
void RedBlackTree::delete_node(node* node_to_del) {
	// case 0: if the node is the root, and it is the only node in the tree
	if(node_to_del->parent == nullptr && node_to_del->left_child == nullptr 
			&& node_to_del->right_child == nullptr) {

		// delete the root and set it to nullptr
		delete this->root;
		this->root = nullptr;
	}
	// *** Case 1 (a) and (b) (Base Case)
	else if(!node_to_del->is_double_black) {
		// Step 1: if the node is an internal node, find the inorder successor
		if(node_to_del->left_child != nullptr && node_to_del->right_child != nullptr) {
			// find the inorder of the node to delete
			node* inorder = find_inorder(node_to_del);

			// set the value of the inorder to the value of node_to_del
			node_to_del->value = inorder->value;

			// recurse, with inorder being the new node to delete
			delete_node(inorder);
		}
		// * Case 1 (a): the node is Red, and is Leaf
		// if the node is not an internal node (2 children), and is RED, then it must be
		//		a leaf node
		else if(node_to_del->color == RED) {
			// delete the node
			// delete the left/right child pointer of its parent node
			if(node_to_del->which_child == RIGHT) { 
				node_to_del->parent->right_child = nullptr;
			} else {
				node_to_del->parent->left_child = nullptr;
			}
			delete node_to_del;
			node_to_del = nullptr;
		}
		// The node is not internal, and is not Red. So it must be Black and either a leaf
		//		node or a node with a Red child.
		else {
			// The node must be Black (no need to check).
			//	 It is a leaf or has 1 Red child (the latter has no children). 
			// * Case 1 (b) (i): The node has a Red child, left
			if(node_to_del->left_child != nullptr) {
				// assign the value in the red child to the node, and delete the node
				node_to_del->value = node_to_del->left_child->value;

				// create a node pointer with the keyword new, to delete the child node
				//		dynamically allocated nodes can be deleted
				node* child_to_delete = new node;

				// point this dynamically allocated pointer to the child node, before 
				//		disconnecting it from the parent
				child_to_delete = node_to_del->left_child;

				// disconnect the child node from the parent node
				node_to_del->left_child = nullptr;

				
				// delete the left child
				delete child_to_delete;
				child_to_delete = nullptr;

			}
			// * Case 1 (b) (ii): The node has a Red child, right
			else if(node_to_del->right_child != nullptr) {
				// do the same this as above, but for the right child
				node_to_del->value = node_to_del->right_child->value;

				node* child_to_delete = new node;

				child_to_delete = node_to_del->right_child;

				node_to_del->right_child = nullptr;

				// delete the right child
				delete child_to_delete;
				child_to_delete = nullptr;
			}

			// The node is a Black leaf node
			else {
				// make node DB and recurse
				node_to_del->is_double_black = true;
				// recurse, with inorder being the new node to delete
				delete_node(node_to_del);
			}
		}
	}
	// node is DB
	// Note: node and node_to_del are used interchangeably.
	// *** Cases 2 through 6
	else {
		// * Case 2: node is a root node, make DB into B, and exit: Base Case
		if(node_to_del->parent == nullptr) {
			// node is a root node
			node_to_del->is_double_black = false;
		}
		// *** Cases 3 through 6
		else {
			// declare pointers necessary for cases 3 through 6
			node* sibling;
			node* parent = node_to_del->parent;
			node* far_child;
			node* near_child;

			// determine which child is far child, and set far/near children accordingly
			if(node_to_del->which_child == RIGHT) {
				// the sibling is a left child of node_to_del's parent
				sibling = parent->left_child;

				// the far child of sibling (relative to node_to_del) is the left child
				//		of sibling
				far_child = sibling->left_child;
				near_child = sibling->right_child;
			} else {
				// the sibling is a right child of node_to_del's parent
				sibling = parent->right_child;

				// the far child of sibling (relative to node_to_del) is the righ child
				//		of sibling
				far_child = sibling->right_child;
				near_child = sibling->left_child;
			}

			// *** Cases 3, 5, and 6
			if(sibling->color == BLACK) {
				// * Case 3: sibling is Black, both children of sibling (far and near) are
				//		either nullptr or Black
				if((far_child == nullptr || far_child->color == BLACK) 
						&& (near_child == nullptr || near_child->color == BLACK)) {
					// if node_to_del (the DB node) is a leaf node, delete it
					if(node_to_del->left_child == nullptr && node_to_del->right_child == nullptr) {
						// dynamically allocate a new pointer to delete the node_to_del
						node* node_for_deletion = new node;

						node_for_deletion = node_to_del;

						// set the parent's left or right child to null before deleting
						//		the node
						if(node_to_del->which_child == RIGHT) {
							parent->right_child = nullptr;
						}
						else {
							parent->left_child = nullptr;
						}
						
						// delete the node
						delete node_for_deletion;
						node_for_deletion = nullptr;

					}
					// node_to_del is not a leaf node, so only make the DB into B
					else {
						node_to_del->is_double_black = false;
						node_to_del->color = BLACK;
					}

					// case 3 (b) (P is Black)
					// add Black to node_to_del's parent
					if(parent->color == BLACK) {
						parent->is_double_black = true;
						// now the parent becomes the node_to_del. 
						// recursively call this function, where parent becomes the new 
						//		node_to_del
						delete_node(parent);
					// case 3 (a) (P is Red)
					} else {
						// no need to recurse
						parent->color = BLACK;
					}


					// make sibling Red
					sibling->color = RED;
				}
				// * Case 5: DB's (node_to_del's) sibling is Black, far_child is Black,
				//		near child is red
				else if((far_child == nullptr || far_child->color == BLACK)
						&& (near_child != nullptr && near_child->color == RED)) {
					// swap color of DB's sibling with near child
					bool temp_color = sibling->color;
					sibling->color = near_child->color;
					near_child->color = temp_color;

					// !!! rotate sibling in opposite direction from DB
					if(sibling->which_child == LEFT) {
						sibling->right_child = near_child->left_child;
						if(near_child->left_child != nullptr) {
							near_child->left_child->parent = sibling;
							near_child->left_child->which_child = RIGHT;
						}

						parent->left_child = near_child;
						near_child->parent = parent;
						near_child->which_child = LEFT;

						sibling->parent = near_child;
						near_child->left_child = sibling;

					} 
					// mirror case of the above rotation
					else {
						sibling->left_child = near_child->right_child;
						if(near_child->right_child != nullptr) {
							near_child->right_child->parent = sibling;
							near_child->right_child->which_child = LEFT;
						}

						parent->right_child = near_child;
						near_child->parent = parent;
						near_child->which_child = RIGHT;

						sibling->parent = near_child;
						near_child->right_child = sibling;
					}

					// recurse, case 6 will be applied after case 5 always.
					delete_node(node_to_del);
				} 
				// * Case 6: DB's (node_to_del's) sibling is Black, far child is Red,
				//		near child is Black
				else if((far_child != nullptr && far_child->color == RED)) {
					// swap color of Parent and sibling
					bool temp_color = sibling->color;
					sibling->color = parent->color;
					parent->color = temp_color;

					// rotate P in DB's (node_to_del's) direction
					// 2 mirror cases for rotation.
					// 1) sibling is the right child of parent
					if(sibling->which_child == RIGHT) {
						// identical to LL rotation, with 
						//		far_child = new_node
						//		sibling = parent
						//		parent = parents_parent
						RR_rotation(sibling, DELETE);
					}
					// 2) mirror case of case 1: sibling is the left child of parent
					else {
						// identical to LL rotation, with 
						//		far_child = new_node
						//		sibling = parent
						//		parent = parents_parent
						LL_rotation(sibling, DELETE);
					}

					// change DB to B or delete node_to_del if it is a leaf node
					if(node_to_del->left_child == nullptr && node_to_del->right_child == nullptr) {
						if(node_to_del->which_child == RIGHT) {
							parent->right_child = nullptr;
						} else {
							parent->left_child = nullptr;
						}
						delete node_to_del;
						node_to_del = nullptr;
					} 
					// make it Black
					else {
						node_to_del->color = BLACK;
						node_to_del->is_double_black = false;
					}

					// change far child's color to BLACK
					far_child->color = BLACK;
				}
			}
			// * Case 4: sibling is Red
			else {
				// swap colors of P and sibling
				bool temp_color = sibling->color;
				sibling->color = parent->color;
				parent->color = temp_color;

				// rotate P in DB direction
				// if sibling is a LEFT child
				if(sibling->which_child == LEFT) {
					// call LL rotation with DELETE option
					LL_rotation(sibling, DELETE);
				}
				// sibling is a right child
				else {
					// call RR rotation with DELETE option
					RR_rotation(sibling, DELETE);				
				}

				// reapply cases (recurse)
				delete_node(node_to_del);
			}
		}
	}
}


// finds the inorder successor node of the given node node_to_del
// @parameters
//		node_to_del = a pointer to the node whose inorder successor we need to find
// @return
//		node_to_return = a pointer to the inorder successor node of the given node 
//			node_to_del. the parameter will be reused to arrive to the inorder successor
node* RedBlackTree::find_inorder(node* node_to_del) {
	// if the given node is not null
	if(node_to_del != nullptr) {
		// node_to_del will be the node that this function will return

		// if the node has a right child
		if(node_to_del->right_child != nullptr ){
			// first, go to the right, then keep going left
			node_to_del = node_to_del->right_child;

			// now, keep going left until the left child is nullptr
			while(node_to_del->left_child != nullptr) {
				node_to_del = node_to_del->left_child;
			}

			return node_to_del;			
		}
		// the node does not have a right child to begin with. So the node is its own
		//		inorder successor
		else {
			return node_to_del;
		}
	}
	// the given node is null.
	else {
		// return null
		return node_to_del;
	}
}

// finds the node that has the given value. 
// @parameters
// 		value = the value of the node that we are searching for
node* RedBlackTree::binary_search(int value) {
	// call the recursive binary search method
	return this->binary_search(this->root, value);
}


// finds the node that has the given value
// @parameters
//		root = a pointer to the root of the tree
// 		value = the value of the node that we are searching for
// @return
//		either
//			a pointer to the node that contains the given value
//		or
//			a null pointer if value is not found 
node* RedBlackTree::binary_search(node* root, int value) {
	// value is not found, return nullptr
	if(root == nullptr) {
		node* null_node;
		null_node = nullptr;
		return null_node;
	}
	else {
		// go (recurse) to the left subtree
		if(value < root->value) {
			binary_search(root->left_child, value);
		}
		// go (recurse to the right subtree)
		else if (value > root->value) {
			binary_search(root->right_child, value);
		}
		// value is found. return root
		else {
			return root;
		}
	}
}


// flatten the tree into an array
// @parameters:
//		flattened_tree = a pointer that will eventually be the array of values in the
//			tree
// @return:
//		the size of the flattened array
int RedBlackTree::to_array(int* flattened_tree) {
	int size_of_array = 0;
	// call the private helper function
	return this->to_array_helper(this->root, flattened_tree, size_of_array);
}


// recursive helper function to flatten the tree into an array of values
// @parameters:
//		node = a node to recurse. represents the current node in a depth first search
//		flattened_tree = a pointer that will eventually be the array of values in the
//			tree
//		size_of_array = the size of the flattened_tree array. This keeps track of the 
//			size of the array as we recurse.
// @return:
//		the size of the flattened array
int RedBlackTree::to_array_helper(node* node, int* flattened_tree, int& size_of_array) {
	// depth first search
	if(node != nullptr) {
		// go to the left child
		if(node->left_child != nullptr) {
			to_array_helper(node->left_child, flattened_tree, size_of_array);
		}


		// append the value to the flattened tree
		flattened_tree[size_of_array] = node->value;

		// increment the size of the array
		size_of_array++;

		// go to the right child
		if(node->right_child != nullptr) {
			to_array_helper(node->right_child, flattened_tree, size_of_array);
		}
	}
	else {
		cout << "node is null";
	}
	return size_of_array;
}

#endif