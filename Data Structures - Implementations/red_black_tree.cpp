#include <iostream>
#include <queue>
using namespace std;

#define RIGHT true
#define LEFT false

#define RED true
#define BLACK false


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

void RR_rotation(node*& root, node* new_node);
void RL_rotation(node*& root, node* new_node);
void LL_rotation(node*& root, node* new_node);
void LR_rotation(node*& root, node* new_node);

void display_tree(node* root);


int main() {
	node* root = new node;
	root = NULL;

	int value;
	int line_coordinates[21] = {20, 5, 30, 40, 50, 35, 6, 9, 3, 60, 33, 1, 34, 0, 70, 32,
							2, -1, 37, 65, 38};
	for(int i = 0; i < sizeof(line_coordinates)/4; i++) {
		// cout << "Enter a value: ";
		// cin >> value;
		// cout << endl;
		// cout << line_coordinates[i] << endl;
		insert(root, line_coordinates[i]);
		display_tree(root);
	}


	return 0;
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
		node* new_node = new node;

		new_node->value = value;

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
		while(current_node != NULL) {
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
			// // found the node, no need to insert it (because no duplicates are allowed)
			// else {
			// 	found = true;
			// }
		}

		// Case 2: Tree is not empty. Create a new Red node
		// a node with the given value is not found, so insert as a child to the 
		//		parent_node to its right or left, depending on the value of right_or_left
		if(current_node == NULL) {
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
				RR_rotation(root, new_node);
			} else if(new_node->which_child == LEFT && parent_node->which_child == RIGHT) {
				RL_rotation(root, new_node);
			} else if(new_node->which_child == LEFT && parent_node->which_child == LEFT) {
				LL_rotation(root, new_node);
			} else {
				LL_rotation(root, new_node);
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

	// delete local pointers
	parent_node = NULL;
	parent_sibling_node = NULL;
	parent_parent_node = NULL;

	delete parent_node;
	delete parent_sibling_node;
	delete parent_parent_node;
}

// do an RR rotation
// @parameters
//		root = a reference to a pointer to the root of the tree
//		new_node = a pointer to the new node.
void RR_rotation(node*& root, node* new_node) {
	// declare temporary pointers to store the parent and parent's parent 
	node* parent_node = new_node->parent;
	node* parent_parent_node = parent_node->parent;

	cout << "before rr rotation: " << endl;
	display_tree(root);

	cout << "parents parent parent = " << parent_parent_node->parent->value << endl;
	cout << "parents parent = " << parent_parent_node->value << endl;
	cout << "parent = " << parent_node->value << endl;
	cout << "new node = " << new_node->value << endl;
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
	// cout << "parent_parent_node->right_child = parent_node->left_child " << 	parent_parent_node->right_child->value << " = " << parent_node->left_child->value << endl;
	parent_parent_node->right_child = parent_node->left_child;
	// step 6
	// cout << "parent_node->left_child == parent_parent_node " << parent_node->left_child->value << " = " << parent_parent_node->value << endl;
	parent_node->left_child = parent_parent_node;
	// reset which child of parents_parent node
	parent_parent_node->which_child = LEFT;


	// step 7: recolor parent and parent's parent nodes
	parent_node->color = BLACK;
	parent_parent_node->color = RED;
	// cout << "after RR rotation\n";
	// display_tree(root);
	// delete local pointers
	parent_node = NULL;
	parent_parent_node = NULL;

	delete parent_node;
	delete parent_parent_node;



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
	RR_rotation(root, parent_node);

	// delete local pointers
	parent_node = NULL;
	parent_parent_node = NULL;

	delete parent_node;
	delete parent_parent_node;
}

// do an LL rotation
// @parameters
//		root = a reference to a pointer to the root of the tree
//		new_node = a pointer to the new node.
void LL_rotation(node*& root, node* new_node) {
	// declare temporary pointers to store the parent and parent's parent 
	node* parent_node = new_node->parent;
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
	if(parent_parent_node->which_child == LEFT) {
		parent_parent_node->parent->left_child = parent_node;
	} else {
		parent_parent_node->parent->right_child = parent_node;
		// reset which child of parent node
		parent_node->which_child = RIGHT;
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


	// step 7: recolor parent and parent's parent nodes
	parent_node->color = BLACK;
	parent_parent_node->color = RED;

	// delete local pointers
	parent_node = NULL;
	parent_parent_node = NULL;

	delete parent_node;
	delete parent_parent_node;
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
	LL_rotation(root, parent_node);

	// delete local pointers
	parent_node = NULL;
	parent_parent_node = NULL;

	delete parent_node;
	delete parent_parent_node;
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


	cout << "*********************************************************************\n";
	cout << "*********************************************************************\n";

	// at the beginning of the loop, the queue (nodes_on_level) contains all the nodes
	//		on the current level
	while(nodes_on_level.size() > 0) {
		// traverse the nodes of the current level
		while(num_of_nodes_on_level > 0) {
			// display the node
			cout << nodes_on_level.front()->value;
			// display the which_child and parent's value of the node
			if(nodes_on_level.front()->parent != NULL) {
				cout << "(" << nodes_on_level.front()->which_child << ", " << nodes_on_level.front()->parent->value << ")   ";
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

		// level breaks for visualization
		cout << "\n------------------------------------------------------------------\n"; 

		// reset the number of nodes on the current level for the next iterations of the
		//		inner while loop
		num_of_nodes_on_level = nodes_on_level.size();

	}
}


// deletes the node with the given value using inorder successor
// recurses until there is no DB problem
// keeps the binary search tree nature of the tree after deletion
// @parameters
//		root = the root of the tree from which we want to delete the given value
//		value = the value of the node to be deleted
void delete_node(bst_node*& root, bst_node* node_to_del) {
	// *** Case 1 (a) and (b)
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
			node_to_del = NULL;
			delete node_to_del;
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
			}
		}
	}
	// node is DB
	// *** Cases 2 through 6
	else {
		// * Case 2: node is a root node, make DB into B, and exit
		if(node_to_del->parent == NULL) {
			// node is a root node
			node->is_double_black = false;
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

						// delete the node
						delete node_for_deletion;
						node_for_deletion = NULL;
					}
					// node_to_del is not a leaf node, so only make the DB into B
					else {
						node_to_del->is_double_black = false;
						node_to_del->color = BLACK;
					}

					// add Black to node_to_del's parent
					if(parent->color == BLACK) {
						parent->is_double_black = true;
					} else {
						parent->color = BLACK;
					}


					// make sibling Red
					sibling->color = RED;

					// now the parent becomes the node_to_del. 
					// recursively call this function, where parent becomes the new 
					//		node_to_del
					delete_node(root, parent);

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
				}
			}
			// * Case 4: sibling is Red
			else {

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
