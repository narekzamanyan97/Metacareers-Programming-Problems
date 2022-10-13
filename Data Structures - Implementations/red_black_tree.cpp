#include <iostream>
#include <queue>
using namespace std;

#define RIGHT true
#define LEFT false

#define RED true
#define BLACK false

#define DELETE true
#define INSERT false


///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
//							Function and struct declarations
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

void insert(node*& root, int value);
void insert_helper(node*& root, node* new_node);

void RR_rotation(node*& root, node* parent_node, bool del_or_insert);
void RL_rotation(node*& root, node* new_node);
void LL_rotation(node*& root, node* parent_node, bool del_or_insert);
void LR_rotation(node*& root, node* new_node);

void display_tree(node* root);

void delete_node(node*& root, node* node_to_del);

node* find_inorder(node* node_to_del);

node* binary_search(node* root, int value);
bool is_binary_tree(node* root);


bool is_red_black_tree(node* root);
bool is_red_black_tree_helper1(node* root, int running_total, int tot_bl_nodes_on_leftmost_path);
int is_red_black_tree_helper2(node* root);

// functions for the main method to demo the insert, delete, display, and check 
//		functions
void demo_delete_node_array(node* root, int vals_to_del[], int size_of_array);
node* demo_build_tree_from_array(int array_of_values[], int size_of_array);
void demo_delete_node_input(node* root);
node* demo_build_tree_input();

int main() {
	node* root;
	root = NULL;

	int value;
	int line_coordinates[] = {30, 5, 6, 40, 20, 33, 70, 34, 0, 2, 1, 3, 60, 50, 100, 29, 39, 51, 54, 66, 64, 9, 8, 18, 28, 98, 38, 17, 64, 61, 31, 32, 33, 43, 13};
	
	// int line_coordinates[21] = {20, 5, 30, 40, 50, 35, 6, 9, 3, 60, 33, 1, 34, 0, 70, 32,
	// 						2, -1, 37, 65, 38};
	
	// int line_coordinates[17] = {4, 10, 16, 12, 11, 3, 9, 7, 5, 2, 13, 15, 1, 14, 10, 17};
	// int line_coordinates[] = {1, 5, 2};

	root = demo_build_tree_from_array(line_coordinates, sizeof(line_coordinates)/sizeof(line_coordinates[0]));
	display_tree(root);

	int vals_to_del[] = {33, 30, 17, 39, 64};

	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	demo_delete_node_array(root, vals_to_del, sizeof(vals_to_del)/sizeof(vals_to_del[0]));
	display_tree(root);

	return 0;
}


// deletes the nodes having the given values in the array from the tree with the given
//		root
// @parameters:
//		root = a pointer to the root of the tree
//		vals_to_del = an array of integer values representing the nodes that need to be
//		size_of_array = the size of the input array
//			deleted 
void demo_delete_node_array(node* root, int* vals_to_del, int size_of_array) {
	node* node_to_del;

	// Example 1)
	// int line_coordinates[16] = {20, 5, 30, 40, 50, 35, 6, 9, 3, 60, 33, 1, 34, 0, 70, 2};
	// int vals_to_del[] = {30, 5, 6, 40, 20, 33, 70, 34, 0, 2, 1, 3, 60, 50};
	// int vals_to_del[] = {30, 5, 6, 40, 20, 33, 70, 34, 0, 60, 2, 50};
	for(int i = 0; i < size_of_array; i++) {
		node_to_del = binary_search(root, vals_to_del[i]);
		if(node_to_del != NULL) {

			delete_node(root, node_to_del);
		}
		else {
			cout << "value not in the tree.\n";
		}
	}
	
	display_tree(root);				
}

// build a tree using the values in a given array
// @parameters:
//		array_of_values = an array of int values to be inserted into the tree
//		size_of_array = the size of the input array
// @return
//		root = a pointer to the root of the array
node* demo_build_tree_from_array(int* array_of_values, int size_of_array) {
	// a pointer holding the root of the tree
	node* root = NULL;

	// iterate over the array of values, and insert the values into the tree one by one
	for(int i = 0; i < size_of_array; i++) {
		cout << size_of_array << endl;
		insert(root, array_of_values[i]);
	}
	display_tree(root);

	return root;
}

// deletes user-input values from a tree
// asks the user for the values to delete from the tree that was built.
// @parameters:
//		root = a pointer to the root of the tree
void demo_delete_node_input(node* root) {
	// reset is_done to anything other than 'e' or 'E'
	char is_done;

	// the variable for the value to be deleted.
	int value;

	node* node_to_del;

	while(is_done != 'e' && is_done != 'E') {
		cout << "Enter a value to delete. enter -1 to exit: \n";
		cin >> value;
		if(value != -1) {
			node_to_del = binary_search(root, value);
			if(node_to_del != NULL) {

				delete_node(root, node_to_del);
				display_tree(root);				
			}
			else {
				cout << "value not in the tree.\n";
			}

		}

		cout << "Enter 'e' or 'E' to exit. Press anything else to continue: " << endl;
		cin >> is_done;
	}
}

// builds a tree from input values given by the user
// @return:
//		root = a pointer to the root node of the newly built tree
node* demo_build_tree_input() {
	// a pointer holding the root of the tree
	node* root = NULL;

	// the variable for the value to be inserted.
	int value;

	// a char variable for exiting from the loop
	char is_done;

	while(is_done != 'e' && is_done != 'E') {
		cout << "Enter a value: ";
		cin >> value;
		cout << endl;
		insert(root, value);

		// display the tree after inserting a value
		display_tree(root);	

		cout << "Enter 'e' or 'E' to exit. Press anything else to continue: " << endl;
		cin >> is_done;
	}

	return root;
}

// determine if the given tree with the given root node is binary. (left child is
//		less than the parent, and right child is greater than the parent, for every node)
// Note: It is assumed that duplicates are not allowed.
// @parameters:
//		root = a pointer to the root node of the tree.
// @return
//		true = if the tree is binary (left child of any node is either NULL or < node)
//		false = if the tree is not binary
bool is_binary_tree(node* root) { 
	// stores the nodes of a tree in a breadth-first traversal. Updated throughout the
	//		inner while loop
	queue<node*> nodes_on_level;
	
	// stores the number of nodes on a given level.
	int num_of_nodes_on_level;

	if(root != NULL) {
		// push the node on the zeroth level (root) into the queue
		nodes_on_level.push(root);
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
					return false;
				}
				// else, keep searching the tree
				else {
					nodes_on_level.push(nodes_on_level.front()->right_child);
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
// @parameters:
//		root = a pointer to the root node of the tree
// @return
//		true = if the tree is Red-Black
//		false = otherwise
bool is_red_black_tree(node* root) {
	int tot_bl_nodes_on_leftmost_path = is_red_black_tree_helper2(root); 

	// At the beginning, the running total is 0
	return is_red_black_tree_helper1(root, 0, tot_bl_nodes_on_leftmost_path);
}

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
bool is_red_black_tree_helper1(node* root, int running_total, int tot_bl_nodes_on_leftmost_path) {
	// stores the return values of the leaf nodes in each path. Do not continue 
	//		recursion if its value becomes false
	bool passed_the_test = true;

	// base case. If the node is leaf, compare it to the second argument
	if(root->left_child == NULL && root->right_child == NULL) {
		if(root->color == BLACK) {
			running_total++;
		}

		// !!!
		if(running_total == tot_bl_nodes_on_leftmost_path) {
			cout << "value = " << root->value << endl;
			cout << "correct: " << running_total << endl;
			cout << "-------------------------------------------------------" << endl;
			return true;
		}
		else {
			cout << "value = " << root->value << endl;
			cout << "Should be: " << tot_bl_nodes_on_leftmost_path << endl;
			cout << "Is: " << running_total << endl;
			cout << "-------------------------------------------------------" << endl;
			return false;
		}
	}
	// not a base case, continue doing a depth first traversal
	else {
		///////////////////////////////////////////////////////////////////////////////
		// check property 3 before recursing
		// if the current node is RED
		if(root->color == RED) {
			// if any of its children are RED, set passed_the_test to false
			if(root->left_child != NULL) {
				if(root->left_child->color == RED) {
					passed_the_test = false;
				}
			}

			// if the previous test is not passed, skip the right child
			if(root->right_child != NULL && passed_the_test) {
				if(root->right_child->color == RED) {
					passed_the_test = false;
				}
			}
		} 

		///////////////////////////////////////////////////////////////////////////////
		// Recurse to check property 4
		// go to the left child (if passed_the_test from property 3 is true)
		if(passed_the_test) {
			passed_the_test = is_red_black_tree(root->left_child, tot_bl_nodes_on_leftmost_path);
		}

		// go to the right child (if passed_the_test from the left recursion is true
		if (passed_the_test) {
			passed_the_test = is_red_black_tree(root->right_child, tot_bl_nodes_on_leftmost_path);
		}	
	}

	return passed_the_test;

	
}

// do a depth first search, find the first leaf node, and return the number of black
//		nodes in the path. This value will then be used in the is_red_black_tree()
//		function
//	@parameters
//		root = a pointer to the root node of the tree
int is_red_black_tree_helper2(node* root) {
	// keeps track of the black nodes on the way to the left-most node
	int tot_bl_nodes_on_leftmost_path = 0;

	while(root != NULL) {
		// if the current node to the left-most leaf is black
		if(root->color == BLACK) {
			// increment the number of black nodes on the path
			tot_bl_nodes_on_leftmost_path++;
		}
		
		root = root->left_child;
	}

	return tot_bl_nodes_on_leftmost_path;

}

// insert a value into a red-black tree that has the given root.
// @parameters
//		root = a reference to a pointer for the root of the tree. It is a reference 
//			to allow us to set it in case root is NULL (the there is empty) and the
//			value is the first node in the tree
//		value = the value of the node to be isnerted
void insert(node*& root, int value) {
	// Case 1: Tree is empty. Create a new Black node as the root
	if(root == NULL) {
		root = new node;
		root->value = value;
		root->right_child = NULL;
		root->left_child = NULL;
		root->parent = NULL;

		root->color = BLACK;
		root->is_double_black = false;
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
		while(current_node != NULL && !found) {
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
				cout << "Node is already in the tree. No duplicates are allowed." << endl;
				found = true;
			}
		}

		cout << found << endl;

		// Case 2: Tree is not empty. Create a new Red node
		// a node with the given value is not found, so insert as a child to the 
		//		parent_node to its right or left, depending on the value of right_or_left
		if(current_node == NULL && !found) {
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
			insert_helper(root, new_node);
		}

	}
}

// implementation of cases 4a and 4b.
// @parameters
//		root = a reference to a pointer to the root of the tree
//		new_node = a pointer to the new node. It is assumed that new_node is already
//				inserted into the tree as a Red leaf node
void insert_helper(node*& root, node* new_node) {
	// declare temporary pointers to store the parent, parent's parent, and parent's 
	//		sibling 
	node* parent_node = new_node->parent;
	node* parent_parent_node = parent_node->parent;
	node* parent_sibling_node;

	if(parent_parent_node != NULL) {
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
		if(parent_sibling_node == NULL || parent_sibling_node->color == BLACK) {
			// do suitable rotation (RR, RL, LR, or LL)
			if(new_node->which_child == RIGHT && parent_node->which_child == RIGHT){
				RR_rotation(root, new_node->parent, INSERT);
			} else if(new_node->which_child == LEFT && parent_node->which_child == RIGHT) {
				RL_rotation(root, new_node);
			} else if(new_node->which_child == LEFT && parent_node->which_child == LEFT) {
				LL_rotation(root, new_node->parent, INSERT);
			} else {
				LR_rotation(root, new_node);
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
			if(parent_parent_node != root) {
				parent_parent_node->color = RED;
				
				// recursively call insert_helper with parent_parent_node being the 
				//		second argument (for new_node)
				insert_helper(root, parent_parent_node);
			}


		}

		// go through cases 3 and 4 again and recolor/rotate if necessary
	// Case 3: parent of new node is Black, exit
	}
}

// do an RR rotation
// @parameters
//		root = a reference to a pointer to the root of the tree
//		parent_node = a pointer to the parent of the node to be inserted or deleted.
//		del_or_insert = true if RR is used for deletion operation
//						false if this function is used for insert operation
//			The difference is to recolor or not recolor the parent and parents parent
void RR_rotation(node*& root, node* parent_node, bool del_or_insert) {
	// declare temporary pointers to store the parent and parent's parent 
	// node* parent_node = new_node->parent;
	node* parent_parent_node = parent_node->parent;

	// steps are taken from notebook

	// step 1
	// cout << "parent_node->parent = parent_parent_node->parent " << parent_node->parent->value << " = " << parent_parent_node->parent->value << endl;
	parent_node->parent = parent_parent_node->parent;

	// step 2
	// reset parent's parent child (unless it is NULL)
	if(parent_parent_node->parent != NULL) {
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
	if(parent_node->left_child != NULL) {
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
	if(root == parent_parent_node) {
		root = parent_node;
	}
}

// do an RL rotation
// @parameters
//		root = a reference to a pointer to the root of the tree
//		new_node = a pointer to the new node.
void RL_rotation(node*& root, node* new_node) {
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
	if(parent_node->left_child != NULL) {
		parent_node->left_child->parent = parent_node;
		// reset which_child of parent_node->left_child
		parent_node->left_child->which_child = RIGHT;
	}

	// call LL_rotation
	RR_rotation(root, parent_node->parent, INSERT);

}

// do an LL rotation
// @parameters
//		root = a reference to a pointer to the root of the tree
//		parent_node = a pointer to the parent of the node to be inserted or deleted.
//		del_or_insert = true if RR is used for deletion operation
//						false if this function is used for insert operation
//			The difference is to recolor or not recolor the parent and parents parent
void LL_rotation(node*& root, node* parent_node, bool del_or_insert) {
	// declare temporary pointers to store the parent and parent's parent 
	// node* parent_node = new_node->parent;
	node* parent_parent_node = parent_node->parent;

	// step 1 
	parent_node->parent = parent_parent_node->parent;
	// step 2
	parent_parent_node->left_child = parent_node->right_child;
	// reset which child of parent_node->right_child
	if(parent_node->right_child != NULL) {
		parent_node->right_child->which_child = LEFT;
	}
	// step 3
	if(parent_parent_node->parent != NULL) {
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
	if(parent_node->right_child != NULL) {
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
	if(root == parent_parent_node) {
		root = parent_node;
	}
}

// do an LR rotation
// @parameters
//		root = a reference to a pointer to the root of the tree
//		new_node = a pointer to the new node.
void LR_rotation(node*& root, node* new_node) {
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
	if(new_node->left_child != NULL) {
		new_node->left_child->parent = parent_node;
		// reset which_child of new_node->left child
		new_node->left_child->which_child = RIGHT;
	}

	// step 6
	new_node->left_child = parent_node;
	// no need to change which child of parent node, because it is already LEFT

	// call LL_rotation
	LL_rotation(root, parent_node->parent, INSERT);

	// // delete local pointers
	// delete parent_node;
	// delete parent_parent_node;

	// parent_node = NULL;
	// parent_parent_node = NULL;
}

void display_tree(node* root) {
	// stores the nodes of a tree in a breadth-first traversal. Updated throughout the
	//		inner while loop
	queue<node*> nodes_on_level;
	
	// stores the number of nodes on a given level.
	int num_of_nodes_on_level;

	if(root != NULL) {
		// push the node on the zeroth level (root) into the queue
		nodes_on_level.push(root);
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
			if(nodes_on_level.front()->parent != NULL) {
				cout << "(" << left_or_right << " of " << nodes_on_level.front()->parent->value << ")   ";
			}

			// push the children of the given node into the queue. After push, the queue
			//		has a mix of nodes from the current and next levels. num_of_nodes_on_level
			//		helps us stop the printing on the right node and start the iteration
			//		of the outer loop for the next level
			if(nodes_on_level.front()->left_child != NULL) {
				nodes_on_level.push(nodes_on_level.front()->left_child);
			}			
			if(nodes_on_level.front()->right_child != NULL) {
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
//		root = the root of the tree from which we want to delete the given value
//		value = the value of the node to be deleted
void delete_node(node*& root, node* node_to_del) {
	// *** Case 1 (a) and (b) (Base Case)
	if(!node_to_del->is_double_black) {
		// Step 1: if the node is an internal node, find the inorder successor
		if(node_to_del->left_child != NULL && node_to_del->right_child != NULL) {
			// find the inorder of the node to delete
			node* inorder = find_inorder(node_to_del);

			// set the value of the inorder to the value of node_to_del
			node_to_del->value = inorder->value;

			// recurse, with inorder being the new node to delete
			delete_node(root, inorder);
		}
		// * Case 1 (a): the node is Red, and is Leaf
		// if the node is not an internal node (2 children), and is RED, then it must be
		//		a leaf node
		else if(node_to_del->color == RED) {
			// delete the node
			// delete the left/right child pointer of its parent node
			if(node_to_del->which_child == RIGHT) { 
				node_to_del->parent->right_child = NULL;
			} else {
				node_to_del->parent->left_child = NULL;
			}
			delete node_to_del;
			node_to_del = NULL;
		}
		// The node is not internal, and is not Red. So it must be Black and either a leaf
		//		node or a node with a Red child.
		else {
			// The node must be Black (no need to check).
			//	 It is a leaf or has 1 Red child (the latter has no children). 
			// * Case 1 (b) (i): The node has a Red child, left
			if(node_to_del->left_child != NULL) {
				// assign the value in the red child to the node, and delete the node
				node_to_del->value = node_to_del->left_child->value;

				// create a node pointer with the keyword new, to delete the child node
				//		dynamically allocated nodes can be deleted
				node* child_to_delete = new node;

				// point this dynamically allocated pointer to the child node, before 
				//		disconnecting it from the parent
				child_to_delete = node_to_del->left_child;

				// disconnect the child node from the parent node
				node_to_del->left_child = NULL;

				
				// delete the left child
				delete child_to_delete;
				child_to_delete = NULL;

			}
			// * Case 1 (b) (ii): The node has a Red child, right
			else if(node_to_del->right_child != NULL) {
				// do the same this as above, but for the right child
				node_to_del->value = node_to_del->right_child->value;

				node* child_to_delete = new node;

				child_to_delete = node_to_del->right_child;

				node_to_del->right_child = NULL;

				// delete the right child
				delete child_to_delete;
				child_to_delete = NULL;
			}

			// The node is a Black leaf node
			else {
				// make node DB and recurse
				node_to_del->is_double_black = true;
				// recurse, with inorder being the new node to delete
				delete_node(root, node_to_del);
			}
		}
	}
	// node is DB
	// Note: node and node_to_del are used interchangeably.
	// *** Cases 2 through 6
	else {
		// * Case 2: node is a root node, make DB into B, and exit: Base Case
		if(node_to_del->parent == NULL) {
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
				//		either NULL or Black
				if((far_child == NULL || far_child->color == BLACK) 
						&& (near_child == NULL || near_child->color == BLACK)) {
					// if node_to_del (the DB node) is a leaf node, delete it
					if(node_to_del->left_child == NULL && node_to_del->right_child == NULL) {
						// dynamically allocate a new pointer to delete the node_to_del
						node* node_for_deletion = new node;

						node_for_deletion = node_to_del;

						// set the parent's left or right child to null before deleting
						//		the node
						if(node_to_del->which_child == RIGHT) {
							parent->right_child = NULL;
						}
						else {
							parent->left_child = NULL;
						}
						
						// delete the node
						delete node_for_deletion;
						node_for_deletion = NULL;

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
						delete_node(root, parent);
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
				else if((far_child == NULL || far_child->color == BLACK)
						&& (near_child != NULL && near_child->color == RED)) {
					// swap color of DB's sibling with near child
					bool temp_color = sibling->color;
					sibling->color = near_child->color;
					near_child->color = temp_color;

					// !!! rotate sibling in opposite direction from DB
					if(sibling->which_child == LEFT) {
						sibling->right_child = near_child->left_child;
						if(near_child->left_child != NULL) {
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
						if(near_child->right_child != NULL) {
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
					delete_node(root, node_to_del);
				} 
				// * Case 6: DB's (node_to_del's) sibling is Black, far child is Red,
				//		near child is Black
				else if((far_child != NULL && far_child->color == RED)) {
					cout << "in case 6" << endl;
					display_tree(root);
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
						RR_rotation(root, sibling, DELETE);
					}
					// 2) mirror case of case 1: sibling is the left child of parent
					else {
						// identical to LL rotation, with 
						//		far_child = new_node
						//		sibling = parent
						//		parent = parents_parent
						LL_rotation(root, sibling, DELETE);
					}

					// change DB to B or delete node_to_del if it is a leaf node
					if(node_to_del->left_child == NULL && node_to_del->right_child == NULL) {
						if(node_to_del->which_child == RIGHT) {
							parent->right_child = NULL;
						} else {
							parent->left_child = NULL;
						}
						delete node_to_del;
						node_to_del = NULL;
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
					LL_rotation(root, sibling, DELETE);
				}
				// sibling is a right child
				else {
					// call RR rotation with DELETE option
					RR_rotation(root, sibling, DELETE);				
				}

				// reapply cases (recurse)
				delete_node(root, node_to_del);
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
node* find_inorder(node* node_to_del) {
	// if the given node is not null
	if(node_to_del != NULL) {
		// node_to_del will be the node that this function will return

		// if the node has a right child
		if(node_to_del->right_child != NULL ){
			// first, go to the right, then keep going left
			node_to_del = node_to_del->right_child;

			// now, keep going left until the left child is NULL
			while(node_to_del->left_child != NULL) {
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

// finds the node that has the given value
// @parameters
//		root = a pointer to the root of the tree
// 		value = the value of the node that we are searching for
// @return
//		either
//			a pointer to the node that contains the given value
//		or
//			a null pointer if value is not found 
node* binary_search(node* root, int value) {
	// value is not found, return NULL
	if(root == NULL) {
		node* null_node;
		null_node = NULL;
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
