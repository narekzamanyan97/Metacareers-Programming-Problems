#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <random>
#include <chrono>
#include <ctime>
#include <unordered_map>
#include <queue>
#include <vector>
using namespace std;

#define HORIZONTAL true
#define VERTICAL false

// define constants for red-black BST
#define RED true
#define BLACK false

#define RIGHT true
#define LEFT false

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//						Approach 6: Red-Black binary search Tree 

// a data structure representing a node in a red-black tree
// NOTE: parent of root node is NIL
struct line_node {
	// attributes specific to red-black tree
	bool color = RED;
	line_node* left_child = NULL;
	line_node* right_child = NULL;
	line_node* parent = NULL;

	// true if this is the right child of its parent, false if the left child
	bool which_child = LEFT;

	// attributes specific to lines
	// the tree will be sorted based on line_coord
	int line_coord = 0;
	// type means horizontal or vertical.
	bool type = HORIZONTAL;
	// a vector that holds all the lines that have the same orientation and coordinate.
	vector<std::array<int, 2>> same_coord_lines;
};


void insertIntoTree(line_node*& root, int new_line_coord, int low_endpoint, int high_endopint);

void insertIntoTreeHelper(line_node*& root, line_node* new_node);

// rotation algorithm implementations
void RR_rotation(line_node*& root, line_node* new_node);
void LL_rotation(line_node*& root, line_node* new_node);
void LR_rotation(line_node*& root, line_node* new_node);
void RL_rotation(line_node*& root, line_node* new_node);

void display_tree(line_node* root);

void merge_lines(line_node* node, int low_endpoint, int high_endpoint);

void flatten_tree(line_node* root, vector<line_node>& flattened_tree);


//						Sort using red-black tree.
int* findNode(line_node* root, int coord);

void insert_coord_and_endpoints(int index, int type, vector<int>& lines, vector<vector<std::array<int, 2>>>& endpoints, int coordinate, int* min_max_endpoints);

long long count_plus_sign3(vector<int> h_lines, vector<int> v_lines, vector<vector<std::array<int, 2>>> h_endpoints, vector<vector<std::array<int, 2>>> v_endpoints);

long long getPlusSignCount3(int, vector<int>, string);





// // a data structure representing a NIL node in a red-black binary search tree.
// //		Every leaf node will point to this object to save space
// // line_length = -1 means the node is NIL
// struct {
// 	int line_length = -1;
// } NIL;

int main(){
	// int N = 500000;
	// int L_i = 50000;
	// string D;
	// vector<int> L;
	// L = generate_lengths(N, L_i);
	// D = generate_directions(N);
	
	// initialize variables for the test
	int coordinate;
	int index;
	int min_endpoint = 0;
	int max_endpoint = 1;
	
	// initialize the root to NULL to begin constructing the tree.
	line_node* root = new line_node;
	root = NULL;

	int line_coordinates[21] = {20, 5, 30, 40, 50, 35, 6, 9, 3, 60, 33, 1, 34, 0, 70, 32,
							2, -1, 37, 65, 38};

	vector<line_node> flattened_tree;

	for(int i = 0; i < 21; i++) {
		// cout << "Type a coordinate: ";
		// cin >> coordinate;
		// cout << endl;
		// cout << "Type a min endpoint: ";
		// cin >> min_endpoint;
		// cout << endl;
		// cout << "Type a max endpoint: ";
		// cin >> max_endpoint;
		// cout << endl;


		insertIntoTree(root, line_coordinates[i], min_endpoint, max_endpoint);

		cout << "==================================" << endl;
		display_tree(root);
	}

	flatten_tree(root, flattened_tree);

	for(auto it = flattened_tree.begin(); it != flattened_tree.cend(); it++) {
		cout << (*it).line_coord << ", ";
	}

	return 0;
}

// implementation of insert into red-black BST (with helper functions)
// @parameters:
//		root = a reference to a pointer for the root of the tree, which can change
//			during rotation. helce, a reference is provided so that the function can
//			change it when necessary.
//		new_line_coord = the coordinate of the line being added to the tree
//		low_endpoint = the min endpoint of the added line
//		high_endpoint = the max endpoint of the added line
void insertIntoTree(line_node*& root, int new_line_coord, int low_endpoint, int high_endopint) {
	// Case 1
	// if the tree is empty (root node is NIL), create new node as root with color black
	if(root == NULL) {
		line_node* new_node = new line_node;

		new_node->color = BLACK;
		new_node->left_child = NULL;
		new_node->right_child = NULL;
		new_node->parent = NULL;	
		new_node->line_coord = new_line_coord;	

		// for the root node, the which_child attribute is not needed

		// add the line endpoints to the vector
		new_node->same_coord_lines.push_back({low_endpoint, high_endopint});

		// since new_node is a pointer, it stores the value of an address. So by doing
		//		root = new_node, we assign that address to root, which is a reference
		//		to a pointer
		// ??? 
		root = new_node;
	} else {
		// declare a new node
		line_node* new_node = new line_node;
	
		// Case 2: If tree is not empty, create new node as leaf with color Red (R)
		// new node is always red
		new_node->color = RED; 

		// set true when a place is found for the new_node to be inserted
		bool found = false;

		// temp pointer to store the current node in iteration. begin with the root node
		line_node* current_node = root;
		
		// to keep track of the parent node in case current_node becomes NIL (NULL)
		line_node* parent_node = new line_node;

		// keep track of the direction of last move in case current_node becomes NULL
		bool right_or_left; 

		// search for the right place to put the new node
		while(!found && current_node != NULL) {
			parent_node = current_node;

			// move to the left of tree
			if(new_line_coord < current_node->line_coord) {
				current_node = current_node->left_child;
				right_or_left = LEFT;
			}
			// move to the right of tree
			else if(new_line_coord > current_node->line_coord) {
				current_node = current_node->right_child;
				right_or_left = RIGHT;
			}
			// place is found
			else {
				found = true;
				// if the line is found, insert its endpoints into the vector of
				//		the existing line node
				// merge if necessary
				merge_lines(current_node, low_endpoint, high_endopint);
			}
		}
		// adding new_node as a leaf node
		if(current_node == NULL) {
			// the new line node is being added as a leaf node
			new_node->left_child = NULL;
			new_node->right_child = NULL;
			new_node->parent = parent_node;
			new_node->line_coord = new_line_coord;

			// insert the line node into the tree, following the rules of red-black tree.
			if(right_or_left == LEFT) {
				// insert the new_node as the left child of the parent_node
				parent_node->left_child = new_node;
				// this node is the left child of its parent
				new_node->which_child = LEFT;
			} else {
				// insert the new_node as the right child of the parent_node
				parent_node->right_child = new_node;
				// this node is the right child of its parent
				new_node->which_child = RIGHT;
			}


			insertIntoTreeHelper(root, new_node);
		}

		// delete the pointer
		new_node = NULL;
		delete new_node;
	}


}

// @parameters:
//		new_node = the new node being inserted. the parent and parent's parent nodes can
//			be derived from new_node
//		root = a reference to a pointer for the root of the tree, so that in case of 
//			rotation, we can reset the root pointer, in case the rotation involves the
//			root.
//			
void insertIntoTreeHelper(line_node*& root, line_node* new_node) {
	line_node* parent_node = new_node->parent;
	line_node* parents_parent_node = parent_node->parent;

	// Case 3: If parent of new node is Black, exit
	// Case 4: If parent of new node is RED
	while(parent_node != NULL && (parent_node->color == RED && new_node->color == RED)) {
		// Case 4 cont: Then check the color of parent's sibling of new node
		// then the sibling of parent_node is the RIGHT child of its parent
		if(parent_node->which_child == LEFT) {
			// Case 4 b) if parent's sibling's color is red
			if(parents_parent_node->right_child != NULL 
					&& parents_parent_node->right_child->color == RED) {
				// Case 4 b) cont: recolor parent and parent's sibling.
				//		if parent's parent is not root, recolor it too and
				//		recheck
				parent_node->color = BLACK;
				parents_parent_node->right_child->color = BLACK;

				// root means the node has no parent
				if(parents_parent_node->parent != NULL) {
					// recolor parent's parent
					parents_parent_node->color = RED;
				}

				// reset the pointers for a recheck
				// parent's parent becomes the new node
				new_node = parents_parent_node;
				parent_node = new_node->parent;
				if(parents_parent_node != NULL) {
					parents_parent_node = parent_node->parent;
				}

				cout << "now " << new_node->line_coord;
				if(parent_node != NULL) {
					cout << parent_node->line_coord << endl;
				}
			}
			// Case 4 a) if parent's sibling's color is Black or it is NIL
			else {
				// do suitable rotation and recolor
				// determine if this is RR, RL, LL, or LR situation (see notes)
				// LR rotation
				if(parent_node->which_child == LEFT && new_node->which_child == RIGHT) {
					LR_rotation(root, new_node);

					// reset the parent node after the LR rotation
					parent_node = new_node->parent;
				}
				// LL rotation
				else {
					LL_rotation(root, new_node);

					// reset the new_node and parent node after LL rotation
					new_node = parent_node;
					parent_node = new_node->parent;
				}
			}
		}
		// then the sibling of parent_node is the LEFT child of its parent
		else {

			// Case 4 a) if parent's sibling's color is Black or it is NIL
			if(parents_parent_node->left_child == NULL 
					|| parent_node->parent->left_child->color == BLACK) {
				// RR rotation
				if(parent_node->which_child == RIGHT && new_node->which_child == RIGHT) {
					// reset the new_node and parent node after RR rotation
					RR_rotation(root, new_node);

					new_node = parent_node;
					parent_node = new_node->parent;
				}
				// RL rotation
				else if(parent_node->which_child == RIGHT && new_node->which_child == LEFT) {
					RL_rotation(root, new_node);

					// reset the parent node after the RL rotation
					parent_node = new_node->parent;
					cout << "                 " << parent_node->line_coord << endl;
				}
			}
			// Case 4 b) if parent's sibling's color is Red
			else {	
				cout << "1 " << endl;

				// Case 4 b) cont: recolor parent and parent's sibling.
				//		if parent's parent is not root, recolor it too and
				//		recheck
				parent_node->color = BLACK;
				parents_parent_node->left_child->color = BLACK;
				cout << "2 " << endl;

				// root means the node has no parent
				if(parents_parent_node->parent != NULL) {
					// recolor parent's parent
					parents_parent_node->color = RED;
				}
				cout << "3 " << endl;

				// reset the pointers for a recheck
				// parent's parent becomes the new node
				new_node = parents_parent_node;
				parent_node = new_node->parent;
				cout << "4 " << endl;
				if(parent_node != NULL) {
					parents_parent_node = parent_node->parent;
				}
				if(parents_parent_node != NULL) {
					cout << "in if " << new_node->line_coord;
				}
				if(parent_node != NULL) {
					cout << parent_node->line_coord << endl;

				}
				display_tree(root);
			}
		}
	} 

	// delete pointers
	parent_node = NULL;
	parents_parent_node = NULL;

	delete parent_node;
	delete parents_parent_node;

}


// !!! delete the pointers at the end

// helper function to execute the RR rotation algorithm
void RR_rotation(line_node*& root, line_node* new_node) {
	cout << "inside RR_rotation" << endl;

	// initialize pointers for parent and parent's parent of new node
	line_node* parent_node = new_node->parent;
	line_node* parents_parent_node = parent_node->parent;

	cout << "before 6-step algorithm" << endl;
	display_tree(root);
	// 6-step algorithm
	parent_node->parent = parents_parent_node->parent;
	cout << "1" << endl;
	
	// if parents_parent_node is not the root node
	if(parents_parent_node->parent != NULL) {
		// left or or right child
		if(parents_parent_node->which_child == LEFT) {
			parents_parent_node->parent->left_child = parent_node;
			parent_node->which_child = LEFT;
		} else {
			parents_parent_node->parent->right_child = parent_node;
		}		
	}
	// if parent's parent node is the root node, then reset the root to be the parent
	else {
		root = parent_node;
	}
	cout << "2" << endl;
	parents_parent_node->parent = parent_node;
	cout << "3" << endl;
	
	if(parent_node->left_child != NULL) {
		parent_node->left_child->parent = parents_parent_node;
	}
	cout << "4" << endl;
	parents_parent_node->right_child = parent_node->left_child;
	cout << "5" << endl;
	
	parent_node->left_child = parents_parent_node;	
	cout << "6" << endl;


	// After the rotation, the parent's parent node becomes a left child
	parents_parent_node->which_child = LEFT;

	// recolor parent and parent's parent nodes
	parent_node->color = BLACK;
	parents_parent_node->color = RED;

	
	// delete the pointers
	parent_node = NULL;
	parents_parent_node = NULL;

	delete parent_node;
	delete parents_parent_node;

	if(root == NULL) {
		cout << "root is null";
	} else {
		cout << root->line_coord << endl;
	}

}

// helper function to execute the LL rotation
void LL_rotation(line_node*& root, line_node* new_node) {
	// initialize pointers for parent and parent's parent of new node
	line_node* parent_node = new_node->parent;
	line_node* parents_parent_node = parent_node->parent;

	// 6-step algorithm
	parent_node->parent = parents_parent_node->parent;
	parents_parent_node->left_child = parent_node->right_child;

	// if parents_parent_node is not the root node
	if(parents_parent_node->parent != NULL) {
		// left or right child
		if(parents_parent_node->which_child == LEFT) {
			parents_parent_node->parent->left_child = parent_node;
			parent_node->which_child = LEFT;
		}
		else {
			parents_parent_node->parent->right_child = parent_node;
			parent_node->which_child = RIGHT;
		}
	}
	// if parent's parent node is the root node, then reset the root to be the parent
	else {
		root = parent_node;
	}
	parents_parent_node->parent = parent_node;
	if(parent_node->right_child != NULL) {
		parent_node->right_child->parent = parents_parent_node;
	}
	parent_node->right_child = parents_parent_node;

	// after LL rotation, parent's parent node becomes a right node.
	parents_parent_node->which_child = RIGHT;

	// recolor parent and parent's parent nodes
	parent_node->color = BLACK;
	parents_parent_node->color = RED;

	// delete the pointers
	parent_node = NULL;
	parents_parent_node = NULL;

	delete parent_node;
	delete parents_parent_node;
}

// helper function to execute the LR rotation
//		converts the LR sub-tree into an LL sub-tree. 
//	Uses LL_rotation function after the above conversion 
void LR_rotation(line_node*& root, line_node* new_node) {
	// initialize pointers for parent and parent's parent of new node
	line_node* parent_node = new_node->parent;
	line_node* parents_parent_node = parent_node->parent;

	// 6-step algorithm
	new_node->parent = parents_parent_node;
	parents_parent_node->left_child = new_node;
	parent_node->right_child = new_node->left_child;
	parent_node->parent = new_node;
	if(new_node->left_child != NULL) {
		new_node->left_child->parent = parent_node;
	}
	new_node->left_child = parent_node;

	// the new node becomes a left child after the LR rotation
	new_node->which_child = LEFT;

	// parent_node has taken the place of new_node. call LL_rotation using parent_node
	LL_rotation(root, parent_node);

	// call the LL algorithm after completing LR algorithm
	// delete the pointers
	parent_node = NULL;
	parents_parent_node = NULL;

	delete parent_node;
	delete parents_parent_node;
}

// helper function to execute the RL rotation
//		converts the RL sub-tree into an RR sub-tree
// uses RR_rotation function after the above conversion
void RL_rotation(line_node*& root, line_node* new_node) {
	// initialize pointers for parent and parent's parent of new node
	line_node* parent_node = new_node->parent;
	line_node* parents_parent_node = parent_node->parent;

	// 6-step algorithm
	new_node->parent = parents_parent_node;
	parent_node->left_child = new_node->right_child;
	parents_parent_node->right_child = new_node;
	parent_node->parent = new_node;
	new_node->right_child = parent_node;
	if(parent_node->left_child != NULL) {
		parent_node->left_child->parent = parent_node;
	}

	// After the RL rotation, the new node becomes a right child
	new_node->which_child = RIGHT;

	// parent_node has taken the place of new_node. call RR_rotation using parent_node
	RR_rotation(root, parent_node);

	// call the LL algorithm after completing LR algorithm
	// delete the pointers
	parent_node = NULL;
	parents_parent_node = NULL;

	delete parent_node;
	delete parents_parent_node;
}

// iterative implementation of breadth first traversal of red-black tree
// @parameters
//		root = a pointer to the root of the tree.
void display_tree(line_node* root) {
	if(root == NULL) {
		return;
	}

	// Create an empty queue for level order traversal
	queue<line_node*> q;

	// Enqueue root and initialize height
	q.push(root);

	int nodeCount;

	while(q.empty() == false){
		// nodeCount (queue size) indicates number of nodes at current level
		nodeCount = q.size();

		// dequeue all nodes of current level
		// enqueue all nodes of next level
		while(nodeCount > 0) {
			line_node* node = q.front();
			if(node->color == RED) {
				cout << node->line_coord << "R";
				if(node->parent != NULL) {
					cout << "("  << node->which_child << " " << node->parent->line_coord << ")    ";
				}

				for(auto it = node->same_coord_lines.begin(); it != node->same_coord_lines.cend(); it++) {
					cout << "[" << (*it)[0] << "," << (*it)[1] << "], ";
				}
			}
			else {
				cout << node->line_coord << "B";
				if(node->parent != NULL) {
					cout << "("  << node->which_child << " " << node->parent->line_coord << ")    ";
				}
				for(auto it = node->same_coord_lines.begin(); it != node->same_coord_lines.cend(); it++) {
					cout << "[" << (*it)[0] << "," << (*it)[1] << "], ";
				}
			}
			q.pop();
			if(node->left_child != NULL) {
				q.push(node->left_child);
			}
			if(node->right_child != NULL) {
				q.push(node->right_child);
			}
			nodeCount--;
		}
		cout << endl;
	}
}

// merge overlapping lines.
// if the low and high endpoints overlap with any of the lines in the node's vector
//		attribute (same_coord_lines)
// @parameters:
//		node = the node that has a line_coord matching the line_coord of the newly added
//			line
//		low_endpoint = the min endpoint of the line
//		high_endpoint = the max endpoint of the line
void merge_lines(line_node* node, int low_endpoint, int high_endpoint) {
	auto it = node->same_coord_lines.begin();

	// temporary variables that will hold each of the low and high endpoints of the
	//		same_coord_lines vector's endpoints.
	int min_endpoint;
	int max_endpoint;

	// set it true in the following while loop if a merge occurs. leave it false 
	//		otherwise. Will be used in the last loop.
	bool merge = false;

	// iterate over the endpoints in the same_coord_lines vector, and merge the newly
	//		added line with one overlapping line in the vector, if possible
	while(it != node->same_coord_lines.cend()) {
		min_endpoint = (*it)[0];
		max_endpoint = (*it)[1];

		// see if the lines overlap
		// case 1: min1 <= min 2 && max1 >= min2
		if(low_endpoint <= min_endpoint && high_endpoint >= min_endpoint) {
			merge = true;
			if(high_endpoint > max_endpoint) {
				(*it)[0] = low_endpoint;
				(*it)[1] = high_endpoint;
			} else {
				(*it)[0] = low_endpoint;
			}
		}
		// case 2: max1 >= max2 && min1 <= max2 
		else if(high_endpoint >= max_endpoint && low_endpoint <= max_endpoint) {
			merge = true;
			if(low_endpoint < min_endpoint) {
				(*it)[0] = low_endpoint;
				(*it)[1] = high_endpoint;
			} else {
				(*it)[1] = high_endpoint;
			}
		}
		// case 3: min1 >= min2 && max1 <= max2
		else if(low_endpoint >= min_endpoint && high_endpoint <= max_endpoint) {
			merge = true;
			// do not need to modify the endpoints
		}

		it++;
	}


	// do not insert unless merge does not happen
	if(!merge) {
		node->same_coord_lines.push_back({low_endpoint, high_endpoint});
	} else {
		// merge the endpoints inside the inner vector one by one, as one merge 
		//		might connect multiple lines along the same coordinate.
		auto it = node->same_coord_lines.begin();
		auto it_2 = it;
		while(it != node->same_coord_lines.cend()) {
			it_2 = it + 1;
			while(it_2 != node->same_coord_lines.cend()) {
				// case 1 (see notebook)
				if((*it)[0] <= (*it_2)[0] && (*it)[1] >= (*it_2)[0]) {
					if((*it)[1] < (*it_2)[1]) {
						// merge the lines
						(*it)[1] = (*it_2)[1];
					}

					// remove the 2nd inner line from the vector
					it_2 = node->same_coord_lines.erase(it_2);

				// case 2 (see notebook)
				} else if((*it)[1] >= (*it_2)[1] && (*it)[0] <= (*it_2)[1]) {
					if((*it)[0] > (*it_2)[0]) {
						(*it)[0] = (*it_2)[0];
					}

					// remove the 2nd inner line from the vector
					it_2 = node->same_coord_lines.erase(it_2);

				} else if((*it)[0] >= (*it_2)[0] && (*it)[1] <= (*it_2)[1]){ 
					if((*it)[0] > (*it_2)[0]) {
						(*it)[0] = (*it_2)[0];
					}
					if((*it)[1] < (*it_2)[1]) {
						(*it)[1] = (*it_2)[1];
					}

					// remove the 2nd inner line from the vector
					it_2 = node->same_coord_lines.erase(it_2);

				}
				else {
					it_2++;
				}
			}
			it++;
		}
	}
}

// !!! flatten the tree for the vertical lines into a vector so that we can make the
//		search for min and max endpoints of horizontal lines faster using divide and
//		conquer.
//	use depth-first traversal to push nodes into the flattened_tree from left to right
//		(in ascending order)
// @parameters:
//		root = the root of the tree to be traversed
//		flattened_tree = the flattened version of the tree
void flatten_tree(line_node* root, vector<line_node>& flattened_tree){
	// if the root is not NIL, proceed
	if(root != NULL) {
		// go to the left of the tree, if left_child is not NULL
		if(root->left_child != NULL) {
			flatten_tree(root->left_child, flattened_tree);
		}
		// push the current node into the tree
		flattened_tree.push_back(*root);
		// go to the right of the tree, if right_child is not NULL
		if(root->right_child != NULL) {
			flatten_tree(root->right_child, flattened_tree);
		}
	}

}

// @return
//		the pointer to the node to which the new node has to be added (either to the
//		left as a left child or to the right as a right child)
int* findNode(line_node* root, int coord) {
	return 0;
}


long long getPlusSignCount3(int, vector<int>, string) {
	return 0;
}