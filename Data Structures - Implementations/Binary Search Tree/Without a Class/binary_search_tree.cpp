#include <iostream>
#include <queue>
using namespace std;

#define RIGHT true
#define LEFT false

#define SUCCESSOR true
#define PREDECESSOR false

// Implementation of Binary Search Tree (BST), insertion, deletion, display,
// Also includes Binary Search

////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
//							Declarations of structure and functions
// a node structure for a binary search tree.
struct bst_node {
	bst_node* parent = nullptr;
	bst_node* left_child = nullptr;
	bst_node* right_child = nullptr;

	// RIGHT if this node is the right child of its parent
	// LEFT otherwise
	bool which_child;

	int value;
};


void display_tree(bst_node* root);


void insert(bst_node*& root, int value);

void delete_node(bst_node*& root, bst_node* node_to_del);

bst_node* find_inorder(bst_node* root, int value, bool successor_or_predecessor);


bst_node* binary_search(bst_node* root, int value);


int main() {
	int value;
	bst_node* root = nullptr;

	// for(int i = 0; i < 20; i++) {
	// 	cout << "Enter a value: " << endl;
	// 	cin >> value;
	// 	cout << endl;

	// 	insert(root, value);
	// 	display_tree(root);
	// }

	int values[31] = {11, 19, 29, 5, 1, 14, 10, 3,
					8, 7, 30, 40, 35, 22, 24, 20, 16, 17,
					2, 18, 12, 36, 0, -4, 15, 27, 34, 41, 21,
					13, 9};
	for(int i = 0; i < sizeof(values)/sizeof(values[0]); i++) {
		insert(root, values[i]);
	}
	display_tree(root);

	bst_node* node = nullptr;

	// delete an element
	for(int i = 0; i < 10; i++) {
		cout << "delete element: " << endl;
		cin >> value;
		cout << endl;

		node = binary_search(root, value);

		delete_node(root, node);
		
		display_tree(root);
	}

	return 0;
}

// inserts a new node with the given value into the bst with the given root.
// @parameters:
//		root = a reference pointer to the root of the tree to which the new node will be
//			inserted
//		value = the value that the new node will have in the tree
void insert(bst_node*& root, int value) {
	bst_node* new_node = new bst_node;
	
	// set the given value to the new node, later to be inserted into the tree. 
	new_node->value = value;

	// if the tree is empty, insert the new node as the root of the tree
	if(root == nullptr) {
		root = new_node;
	}
	else {
		// use current_node to traverse the root and find the proper place to insert the
		//		new node
		bst_node* current_node = root;

		// will be used as the parent of the new node.
		bst_node* parent_node = current_node;

		// LEFT if the new node should be inserted as the left child of the parent_node
		//		(after the following while loop terminates)
		// RIGHT if the new node should be inserted as the right child of the parent_node
		bool left_or_right;

		// true if a node with the given value is found.
		bool found = false;

		// while there is a node in the path to traverse, continue with the loop.
		while(current_node != nullptr) {
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

				current_node = nullptr;
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
	}
}


// displays the tree with breadth_first traversal
//	@parameters:
//		root = the root of the tree to be displayed
void display_tree(bst_node* root) {
	// a queue of bst_node pointers to help traverse the tree in breadth first approach
	queue<bst_node*> nodes_queue;
	
	// will store the front of the queue in the while loop
	bst_node* current_node;

	int num_of_nodes_on_level = 1;

	if(root != nullptr) {
		nodes_queue.push(root);
	}

	cout << "*****************************************************" << endl;
	cout << "*****************************************************" << endl;
	while(!nodes_queue.empty()) {

		while(num_of_nodes_on_level > 0) {
			current_node = nodes_queue.front();

			if(current_node != nullptr) {
				cout << current_node->value;
			}
			if(current_node->parent != nullptr) {
				cout << "(" << current_node->which_child << "," << current_node->parent->value << ")   ";
			}
			
			// push both children of the current_node into the queue
			if(current_node->left_child != nullptr) {
				nodes_queue.push(current_node->left_child);
			}
			if(current_node->right_child != nullptr) {
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


// deletes the node with the given value using inorder successor
// keeps the binary search tree nature of the tree after deletion
// @parameters
//		root = the root of the tree from which we want to delete the given value
//		value = the value of the node to be deleted
void delete_node(bst_node*& root, bst_node* node_to_del) {
	
	// Case 0: tree is empty. don't do anything
	if(root == nullptr) {
		// don't do anything
	}
	// Case 1: the node to be deleted is a leaf node, just delete it, and set it's parent's
	//		appropriate child to null
	else if(node_to_del->left_child == nullptr && node_to_del->right_child == nullptr) {
		// the node is the root with no children
		if(node_to_del->parent == nullptr) {
			delete node_to_del;
			node_to_del = nullptr;

			root = nullptr;
		}
		// the node is a leaf node
		else {
			// if the node to be deleted is the right child of its parent, set the right child
			// 		of its parent to nullptr
			if(node_to_del->which_child == RIGHT) {
				node_to_del->parent->right_child = nullptr;
		   		delete node_to_del;			
				node_to_del = nullptr;
			}
			else {
				node_to_del->parent->left_child = nullptr;
		   		delete node_to_del;			
				node_to_del = nullptr;
			}

		}
	}
	// Case 2a: the node to be deleted has 1 child, left 
	else if(node_to_del->right_child == nullptr && node_to_del->left_child != nullptr) {
		// if the node is the root node
		if(node_to_del->parent == nullptr) {
			// set the left child of the node to be the root
			root = node_to_del->left_child;
			root->parent = nullptr;

			// delete the node
			delete node_to_del;			
			node_to_del = nullptr;
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
			node_to_del = nullptr;
		}
	}
	// Case 2b: the node to be deleted has 1 child, right 
	else if(node_to_del->right_child != nullptr && node_to_del->left_child == nullptr) {
		// if the node is the root node
		if(node_to_del->parent == nullptr) {
			// set the right child of the node to be the root
			root = node_to_del->right_child;
			root->parent = nullptr;

			// delete the node
			delete node_to_del;
			node_to_del = nullptr;
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
			node_to_del = nullptr;
		}
	}
	// Case 3: the node has 2 children
	else {
	// the node to be deleted has a right child
	// find its inorder successor
		// find the inorder of the node to be deleted
		bst_node* inorder = find_inorder(root, node_to_del->value, SUCCESSOR);

		cout << "inorder successor = " << inorder->value << endl;
		
		// change the value of node_to_delete with the value of inorder successor
		node_to_del->value = inorder->value;

		// recursively call delete node to delete the inorder successor found above
		delete_node(root, inorder);
	}

}


// finds the inorder successor/predecessor of the given node. we use binary_search
//		function to get the node corresponding to the given value
// @parameters:
//		root = pointer to the root of the tree
//		value = the value of the node whose inorder successor we are trying to find
// 		successor_or_predecessor = true or false
//			true if it finds successor
//			false if it finds predecessor
bst_node* find_inorder(bst_node* root, int value, bool successor_or_predecessor) {
	bst_node* node = binary_search(root, value);
	
	bst_node* inorder;

	// if the node has no children, return nullptr
	if(node == nullptr || (node->left_child == nullptr && node->right_child == nullptr)) {
		cout << "Node is null" << endl;
		inorder = nullptr;
		return inorder;
	}
	// find inorder successor
	if(successor_or_predecessor == SUCCESSOR) {
		inorder = node->right_child;
		
		// go right, then keep going left
		if(node->right_child != nullptr) {
			bst_node* inorder = node->right_child;
			// while there is left_child, keep going down the tree
			while(inorder->left_child != nullptr) {
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
		if(node->left_child != nullptr) {
			// while there is right child, keep going down the tree
			while(inorder->right_child != nullptr) {
				inorder = inorder->right_child;
			}

			// return the inorder
			return inorder;
		}
	}
}


// search for the node with the given value
// @parameters
//		root = a pointer to the root of the tree
//		value = the value to be searched for
// @return
//		a reference to a pointer to the node that has the given value
//		or 
//		nullptr if the value is not found in the bst
//		it is a reference because we need to be able to delete that node in case this
//			function is called from delete_node
bst_node* binary_search(bst_node* root, int value) {
	if(root == nullptr) {
		bst_node* node;
		cout << "Node is not found. " << endl;
		node = nullptr;
		return node;
	} else {
		// search in the right subtree
		if(value > root->value) {
			binary_search(root->right_child, value);
		} 
		// search in the left subtree
		else if(value < root->value) {
			binary_search(root->left_child, value);
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
// @parameters:
//		root = a pointer to the root node of the tree.
// @return
//		true = if the tree is binary (left child of any node is either nullptr or < node)
//		false = if the tree is not binary
bool is_binary_tree(node* root) { 
	// stores the nodes of a tree in a breadth-first traversal. Updated throughout the
	//		inner while loop
	queue<node*> nodes_on_level;
	
	// stores the number of nodes on a given level.
	int num_of_nodes_on_level;

	if(root != nullptr) {
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
			if(nodes_on_level.front()->left_child != nullptr) {
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
			if(nodes_on_level.front()->right_child != nullptr) {
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