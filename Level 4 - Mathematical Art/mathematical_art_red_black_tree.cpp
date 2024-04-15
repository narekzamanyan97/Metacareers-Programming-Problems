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
	long long line_coord = 0;

	// is single line.
	//		true if same_coord_lines contains only one element
	//		false if it contains more than one element
	bool is_single_line = false;

	// stores the single line, so that instead of iterating over the vector, we just
	//		access this variable, saving time.
	long long single_line_endpoints[2] = {0, 0};

	// a vector that holds all the lines that have the same orientation and coordinate.
	vector<std::array<long long, 2>> same_coord_lines;
};


void insertIntoTree(line_node*& root, long long new_line_coord, long long low_endpoint, long long high_endopint);

void insertIntoTreeHelper(line_node*& root, line_node* new_node);

// rotation algorithm implementations
void RR_rotation(line_node*& root, line_node* new_node);
void LL_rotation(line_node*& root, line_node* new_node);
void LR_rotation(line_node*& root, line_node* new_node);
void RL_rotation(line_node*& root, line_node* new_node);

void display_tree(line_node* root);

void merge_lines(line_node* node, int low_endpoint, int high_endpoint);

void flatten_tree(line_node* root, vector<line_node*>& flattened_tree);

int* findNodeIndex(vector<line_node*> flattened_tree, int coord);

long long getPlusSignCountTree(int N, vector<int> L, string D);

long long countPlusSignTree(vector<line_node*> h_flattened_tree, vector<line_node*> v_flattened_tree);

long long countPlusSignTreeOld(vector<line_node*> h_flattened_tree, vector<line_node*> v_flattened_tree);

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//						Helper Functions
string generate_directions(int number_of_moves, int seed);

char digit_to_dir_conv(int digit);

vector<int> generate_lengths(int number_of_moves, int max_move_size, int seed);



// //						Sort using red-black tree.
// int* findNode(line_node* root, int coord);

// void insert_coord_and_endpoints(int index, int type, vector<int>& lines, vector<vector<std::array<int, 2>>>& endpoints, int coordinate, int* min_max_endpoints);

// long long count_plus_sign3(vector<int> h_lines, vector<int> v_lines, vector<vector<std::array<int, 2>>> h_endpoints, vector<vector<std::array<int, 2>>> v_endpoints);






// // a data structure representing a NIL node in a red-black binary search tree.
// //		Every leaf node will point to this object to save space
// // line_length = -1 means the node is NIL
// struct {
// 	int line_length = -1;
// } NIL;

int main(){
	int N = 2000000;
	int L_i = 1000000000;
	string D;
	vector<int> L;
	L = generate_lengths(N, L_i, 1);
	D = generate_directions(N, 1);
	

	// initialize variables for the test
	int coordinate;
	int index;
	int min_endpoint = 0;
	int max_endpoint = 1;
	
	// initialize the root to NULL to begin constructing the tree.
	line_node* root = new line_node;
	root = NULL;

	// int line_coordinates[21] = {20, 5, 30, 40, 50, 35, 6, 9, 3, 60, 33, 1, 34, 0, 70, 32,
	// 						2, -1, 37, 65, 38};
	/////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////
	//						input test
	// vector<line_node*> flattened_tree;

	// for(int i = 0; i < 21; i++) {
	// 	cout << "Type a coordinate: ";
	// 	cin >> coordinate;
	// 	cout << endl;
	// 	// cout << "Type a min endpoint: ";
	// 	// cin >> min_endpoint;
	// 	// cout << endl;
	// 	// cout << "Type a max endpoint: ";
	// 	// cin >> max_endpoint;
	// 	// cout << endl;


	// 	insertIntoTree(root, coordinate, min_endpoint, max_endpoint);

	// 	cout << "==================================" << endl;
	// 	display_tree(root);
	// }

	// flatten_tree(root, flattened_tree);

	// for(auto it = flattened_tree.begin(); it != flattened_tree.cend(); it++) {
	// 	cout << (*it)->line_coord << ", ";
	// }

	// char exit = 'c';
	// int coord;

	// cout << endl;
	// while(exit != 'e') {
	// 	cout << "Enter a coord: " << endl;
	// 	cin >> coord;
	// 	cout << endl;
	// 	index = findNodeIndex(flattened_tree, coord)[0];
		
	// 	cout << "index = " << index << endl;
	// }
	/////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////
	// #1 (see notebook)
	// L ={2,6,1,6,1,6,1,1,1,3,1,4,1,4,1,4,1,4,1,4,6,4,6,3,1,3,2,1,3,10,2,12,1,11,5};
	// D = "RULDLURRDLDRDLDRDLDRULDULLURDRULURD";

	// #2 (see notebook)
	// L = {2,4,1,3,1,1,1,2,1,2,1,1,1,3,2,1,2,1,3,2,6,2,2,3,6,1,3,3,3,2,2,1,1,4,1,2,2,1,7,4,3,2,4,1,2,5,8,2,3,5};
	// D = "DUDRURDRDLULDLLURLDRULDRDRRULDRULDLURDLURDLULURULD";
	
	for(int i = 0; i < 1; i++) {
		// L = generate_lengths(N, L_i, 23);
		// D = generate_directions(N, 23);

		getPlusSignCountTree(N, L, D);
	}

	// // // int array[] = {47, 14, 34, 1, 27, 1, 25, 36, 34, 15, 35, 31, 16, 41, 37, 22, 34, 11, 26, 1, 23, 11, 32, 18, 15, 40, 32, 16, 19, 27, 0, 32, 46, 22, 39, 26, 13, 37, 28, 45, 6, 36, 22, 13, 7, 20, 35, 44, 31, 38, 16, 27, 22, 9, 20, 42, 36, 43, 46, 13, 1, 45, 34, 48, 34, 40, 48, 48, 31, 12, 8, 6, 31, 23, 37, 1, 45, 3, 29, 18, 38, 9, 36, 32, 40, 45, 0, 5, 32, 20, 49, 10, 43, 17, 5, 29, 26, 7, 44, 31, 41, 39, 21, 6, 35, 20, 49, 38, 0, 34, 18, 17, 44, 41, 39, 10, 37, 36, 3, 46, 41, 5, 16, 38, 35, 27, 21, 30, 48, 21, 6, 5, 18, 10, 16, 25, 14, 37, 48, 40, 43, 0, 26, 30, 33, 6, 24, 10, 19, 38, 26, 26, 14, 1, 3, 37, 42, 9, 20, 0, 43, 42, 0, 9, 47, 27, 15, 44, 41, 21, 49, 40, 6, 18, 21, 49, 37, 10, 47, 26, 43, 42, 35, 3, 32, 34, 16, 28, 34, 18, 11, 49, 17, 3, 20, 46, 20, 3, 27, 34, 41, 41, 41, 27, 24, 48, 5, 38, 40, 46, 31, 1, 27, 46, 1, 32, 49, 14, 12, 6, 44, 12, 48, 20, 14, 28, 46, 11, 40, 18, 41, 45, 40, 49, 19, 39, 31, 46, 42, 47, 42, 12, 16, 16, 10, 44, 24, 44, 42, 6, 8, 47, 4, 21, 18, 10, 4, 3, 0, 26, 43, 2, 32, 5, 9, 21, 38, 5, 26, 43, 35, 24, 37, 21, 12, 37, 27, 5, 11, 45, 27, 8, 14, 22, 29, 39, 24, 17, 45, 37, 45, 11, 47, 10, 19, 7, 36, 17, 9, 35, 37, 23, 13, 13, 25, 13, 32, 39, 46, 33, 38, 27, 32, 9, 7, 12, 49, 3, 1, 46, 22, 29, 37, 31, 38, 14, 39, 16, 25, 49, 49, 34, 46, 20, 10, 1, 15, 40, 3, 39, 3, 4, 26, 35, 37, 17, 27, 26, 44, 48, 0, 0, 5, 43, 35, 25, 48, 22, 45, 13, 46, 34, 18, 17, 32, 40, 33, 5, 37, 31, 23, 3, 27, 26, 4, 16, 2, 38, 38, 18, 9, 16, 4, 25, 47, 49, 7, 0, 9, 13, 9, 5, 17, 43, 47, 26, 38, 6, 0, 18, 14, 30, 28, 6, 1, 46, 19, 7, 35, 19, 8, 40, 4, 17, 12, 45, 48, 1, 49, 1, 4, 19, 8, 46, 22, 30, 44, 1, 42, 34, 33, 12, 42, 18, 35, 1, 7, 31, 34, 7, 14, 12, 30, 17, 20, 15, 6, 31, 43, 41, 6, 22, 9, 7, 13, 32, 12, 23, 40, 41, 1, 36, 14, 38, 26, 31, 10, 4, 6, 1, 45, 12, 11, 34, 6, 38, 1, 23, 45, 30, 30, 48, 5, 15, 7, 1, 3, 38, 33, 15, 5, 42, 41, 30, 11, 22, 24, 25, 34, 8};
	// int array[] = {6, 6, 9, 9, 5, 8, 0, 0, 0, 8, 8, 8, 8, 8, 8, 7, 6, -2, -2, -10, 5, 5, 5, 23, 38, 23, 23, 23, 23, 18, 12, 13, 13, 13, 13, 13, 13, 13, 2, 4, 29, 29, 20, 23, 21, 21, 21, 21, 29, 55, 44, 35, 44, 53, 50};//, 39};
	// // int array[] = {47, 14, 34, 1, 27, 1, 25, 36, 34, 15, 35, 31};
	// for(int i = 0; i < sizeof(array)/sizeof(array[0]); i++) {
	// 	insertIntoTree(root, array[i], 0, 1);
	// 	if(i == 30 || i == 31) {
	// 		cout << array[i] << endl;
	// 		display_tree(root);
	// 		cout << "***********************************************" << endl;
	// 		cout << "***********************************************" << endl;
	// 		cout << "***********************************************" << endl;
	// 	}
		

	// 	// NOTE: The loop is: 17-18-15
	// 	// two nodes have the same parent with the input below:
	// 	// {47, 14, 34, 1, 27, 1, 25, 36, 34, 15, 35, 31}
	// }



	return 0;
}


// converts the string of directions and the vector of lengths into a red-black tree of
//		lines, with nodes represented by a struct called line_node. 
//		Then calls helper functions to count the number of plus signs.
// @parameters:
//		N = the number of lines to be drawn (before any merging of overlapping lines)
//		L = a vector of lengths indicating how much to move for each movement.
//		D = a string of direction characters, 'D', 'L', 'R', and 'U'. used with L
//			to form lines with their endpoints and coordinates.
// @return
//		number_of_pluses = the total number of plus signs formed by the lines.
long long getPlusSignCountTree(int N, vector<int> L, string D) {
	// keeps track of the running total of the number of pluses
	int number_of_pluses = 0;

	// keeps track of the current coordinate of the brush, [x, y]
	long long current_coordinate[2] = {0, 0};

	// keeps track of the previous coordinate of the brush, [x, y], before moving it
	//		by L
	long long previous_coordinate[2] = {0, 0};

	// keeps pointers to all the objects (line_node) for horizontal lines
	vector<line_node*> h_flattened_tree;

	// keeps pointers to all the objects (line_node) for vertical lines
	vector<line_node*> v_flattened_tree;


	// declare roots for trees for horizontal and vertical lines
	line_node* h_root = new line_node;
	line_node* v_root = new line_node;
	h_root = NULL;
	v_root = NULL;

	// count the index to be used to access elements of D while iterating over the 
	//		elements of L
	int  index = 0;

	int ix;

	// stores the direction of the move
	char direction;

	// added for readability
	long long left_endpoint = 0;
	long long right_endpoint = 0;
	long long top_endpoint = 0;
	long long bottom_endpoint = 0;

	// will hold the given min and max endpoints
	long long min_max_endpoints[2] = {0, 0};

	// will hold the array returned by find_index function
	int* index_and_type;



	// !!! add each line to the tree (give the function the root)
	//		need a horizontal and vertical root pointers inside of this function
	// !!! flatten each of those 2 trees (vertical and horizontal)
	//		need two vectors of line_node pointers
	// !!! pass the flattened trees to count_plus_sign_tree, finito.
	for(auto it = L.begin(); it != L.cend(); it++) {
		direction = D.at(index);

		previous_coordinate[0] = current_coordinate[0];
		previous_coordinate[1] = current_coordinate[1];
		


		switch(direction) {
			case 'L':
				// update the current cooridnate after moving the brush
				current_coordinate[0] -= *it;
				

				// set the variables to be used later
				left_endpoint = current_coordinate[0];
				right_endpoint = previous_coordinate[0];


				// insert the new line into the tree for horizontal lines. insertIntoTree 
				//		will also merge this line with any existing overlapping lines.
				insertIntoTree(h_root, current_coordinate[1], left_endpoint, right_endpoint);
			

				break;
			case 'R':
				current_coordinate[0] += *it;

				left_endpoint = previous_coordinate[0];
				right_endpoint = current_coordinate[0];

				
				// insert the new line into the tree for horizontal lines. insertIntoTree 
				//		will also merge this line with any existing overlapping lines.
				insertIntoTree(h_root, current_coordinate[1], left_endpoint, right_endpoint);

				break;
			case 'U':
				// update the current cooridnate after moving the brush
				current_coordinate[1] += *it;


				top_endpoint = current_coordinate[1];
				bottom_endpoint = previous_coordinate[1];

				// insert the new line into the tree for vertical lines. insertIntoTree 
				//		will also merge this line with any existing overlapping lines.
				insertIntoTree(v_root, current_coordinate[0], bottom_endpoint, top_endpoint);

				break;
			case 'D':

				current_coordinate[1] -= *it;		



				top_endpoint = previous_coordinate[1];
				bottom_endpoint = current_coordinate[1];
				
				// insert the new line into the tree for vertical lines. insertIntoTree 
				//		will also merge this line with any existing overlapping lines.
				insertIntoTree(v_root, current_coordinate[0], bottom_endpoint, top_endpoint);
				break;
		}


		index++;

	}

	flatten_tree(h_root, h_flattened_tree);
	flatten_tree(v_root, v_flattened_tree);
	cout << "counting" << endl;

	// cout << "******************************************" << endl;
	// cout << "Horizontal lines: " << endl;
	// for(auto it = h_flattened_tree.begin(); it != h_flattened_tree.cend(); it++) {
	// 	cout << (*it)->line_coord << ": ";
	// 	for(auto endpoint_it = (*it)->same_coord_lines.begin(); endpoint_it != (*it)->same_coord_lines.cend(); endpoint_it++) {  
	// 		cout << "[" << (*endpoint_it)[0] << "," << (*endpoint_it)[1] << "], "; 
	// 	}
	// 	cout << endl;
	// }
	// cout << endl;
	// cout << "******************************************" << endl;
	// cout << "Vertical lines: " << endl;

	// for(auto it = v_flattened_tree.begin(); it != v_flattened_tree.cend(); it++) {
	// 	cout << (*it)->line_coord << ": ";
	// 	for(auto endpoint_it = (*it)->same_coord_lines.begin(); endpoint_it != (*it)->same_coord_lines.cend(); endpoint_it++) {  
	// 		cout << "[" << (*endpoint_it)[0] << "," << (*endpoint_it)[1] << "], "; 
	// 	}
	// 	cout << endl;
	// }

	auto start_time = std::chrono::steady_clock::now();
	countPlusSignTree(h_flattened_tree, v_flattened_tree);
	auto end_time_1 = std::chrono::steady_clock::now();
	// countPlusSignTreeOld(h_flattened_tree, v_flattened_tree);
	// auto end_time_2 = std::chrono::steady_clock::now();


	std::chrono::duration<double> elapsed_seconds_1 = end_time_1 - start_time;
	//std::chrono::duration<double> elapsed_seconds_2 = end_time_2 - end_time_1;
	
	// cout << "performance new: " << elapsed_seconds_1.count() << "sec" << endl;
	// cout << "performance old: " << elapsed_seconds_2.count() << "sec" << endl;
	// cout << "performance gain (1/2): " << elapsed_seconds_2.count() / elapsed_seconds_1.count() << "x" << endl;

	
	// delete the root pointers
	// Note: Call delete first, then set the pointer to NULL
	delete h_root;
	delete v_root;
	h_root = NULL;
	v_root = NULL;



}


// implementation of insert into red-black BST (with helper functions)
// @parameters:
//		root = a reference to a pointer for the root of the tree, which can change
//			during rotation. helce, a reference is provided so that the function can
//			change it when necessary.
//		new_line_coord = the coordinate of the line being added to the tree
//		low_endpoint = the min endpoint of the added line
//		high_endpoint = the max endpoint of the added line
void insertIntoTree(line_node*& root, long long new_line_coord, long long low_endpoint, long long high_endpoint) {
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
		new_node->same_coord_lines.push_back({low_endpoint, high_endpoint});

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


		parent_node = current_node;
		// !!! here is the problem in the loop. infinicio.
		// search for the right place to put the new node
		while(!found && current_node != NULL) {
			// if(new_line_coord == 39) {
				// cout << "in the while" << endl;
				// display_tree(root);
				// cout << "*******************************************" << endl;
				// cout << "*******************************************" << endl;
				// cout << "*******************************************" << endl;
				// cout << "*******************************************" << endl;
			// }
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
				// cout << current_node->line_coord << endl;
				// if the line is found, insert its endpoints into the vector of
				//		the existing line node
				// merge if necessary
				merge_lines(current_node, low_endpoint, high_endpoint);
			}
		}
		// adding new_node as a leaf node
		if(current_node == NULL) {
			// the new line node is being added as a leaf node
			new_node->left_child = NULL;
			new_node->right_child = NULL;
			new_node->parent = parent_node;
			new_node->line_coord = new_line_coord;

			// push the endpoints into same_coord_line vector as the first element
			new_node->same_coord_lines.push_back({low_endpoint, high_endpoint});
			// cout << new_line_coord << ", ";
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
		delete new_node;
		new_node = NULL;
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
				if(parent_node != NULL) {
					parents_parent_node = parent_node->parent;
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
					new_node = parent_node;
					parent_node = new_node->parent;
				}
			}
			// Case 4 b) if parent's sibling's color is Red
			else {	

				// Case 4 b) cont: recolor parent and parent's sibling.
				//		if parent's parent is not root, recolor it too and
				//		recheck
				parent_node->color = BLACK;
				parents_parent_node->left_child->color = BLACK;

				// root means the node has no parent
				if(parents_parent_node->parent != NULL) {
					// recolor parent's parent
					parents_parent_node->color = RED;
				}

				// reset the pointers for a recheck
				// parent's parent becomes the new node
				new_node = parents_parent_node;
				parent_node = new_node->parent;
				if(parent_node != NULL) {
					parents_parent_node = parent_node->parent;
				}

			}
		}
	} 


	// delete pointers
	delete parent_node;
    parent_node = NULL;

	delete parents_parent_node;
	parents_parent_node = NULL;

}


// !!! delete the pointers at the end

// helper function to execute the RR rotation algorithm
void RR_rotation(line_node*& root, line_node* new_node) {
	// initialize pointers for parent and parent's parent of new node
	line_node* parent_node = new_node->parent;
	line_node* parents_parent_node = parent_node->parent;

	// 6-step algorithm
	parent_node->parent = parents_parent_node->parent;
	
	// if parents_parent_node is not the root node
	if(parents_parent_node->parent != NULL) {
		// left or or right child
		if(parents_parent_node->which_child == LEFT) {
			parents_parent_node->parent->left_child = parent_node;
			parent_node->which_child = LEFT;
		} else {
			parents_parent_node->parent->right_child = parent_node;
			parent_node->which_child = RIGHT;
		}		
	}
	// if parent's parent node is the root node, then reset the root to be the parent
	else {
		root = parent_node;
	}
	parents_parent_node->parent = parent_node;

	if(parent_node->left_child != NULL) {
		parent_node->left_child->parent = parents_parent_node;
	
		// since parent node's left child becomes the parent's parent's node's right child,
		//		update the which_child attribute of parent's left child.
		parent_node->left_child->which_child = RIGHT;
	}
	
	parents_parent_node->right_child = parent_node->left_child;

	
	parent_node->left_child = parents_parent_node;	

	// After the rotation, the parent's parent node becomes a left child
	parents_parent_node->which_child = LEFT;

	// recolor parent and parent's parent nodes
	parent_node->color = BLACK;
	parents_parent_node->color = RED;


	// delete the pointers
	delete parent_node;
	delete parents_parent_node;

	parent_node = NULL;
	parents_parent_node = NULL;



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

		// since parent node's right child becomes the parent's parent's node's left child,
		//		update the which_child attribute of parent's right child.
		parent_node->right_child->which_child = LEFT;
	}
	parent_node->right_child = parents_parent_node;

	// after LL rotation, parent's parent node becomes a right node.
	parents_parent_node->which_child = RIGHT;

	// recolor parent and parent's parent nodes
	parent_node->color = BLACK;
	parents_parent_node->color = RED;

	// delete the pointers
	delete parent_node;
	delete parents_parent_node;

	parent_node = NULL;
	parents_parent_node = NULL;
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
		// Since the parent of left_child of new node changes, we must also change the
		//		which child, which changes from LEFT to RIGHT
		new_node->left_child->which_child = RIGHT;
	}

	new_node->left_child = parent_node;

	// the new node becomes a left child after the LR rotation
	new_node->which_child = LEFT;

	// parent_node has taken the place of new_node. call LL_rotation using parent_node
	LL_rotation(root, parent_node);

	// call the LL algorithm after completing LR algorithm
	// delete the pointers
	delete parent_node;
	delete parents_parent_node;

	parent_node = NULL;
	parents_parent_node = NULL;
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
		// Since the parent of left_child of new node changes, we must also change the
		//		which child, which changes from LEFT to RIGHT
		parent_node->left_child->which_child = LEFT;
	}

	// After the RL rotation, the new node becomes a right child
	new_node->which_child = RIGHT;

	// parent_node has taken the place of new_node. call RR_rotation using parent_node
	RR_rotation(root, parent_node);

	// call the LL algorithm after completing LR algorithm
	// delete the pointers
	delete parent_node;
	delete parents_parent_node;

	parent_node = NULL;
	parents_parent_node = NULL;

}

// iterative implementation of breadth first traversal of red-black tree.
//		store all the nodes in a given level using queue and a nodeCount to keep track
//			of level changes. 
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
		cout << "-------------------------------------------------" << endl;
		// dequeue all nodes of current level
		// enqueue all nodes of next level
		while(nodeCount > 0) {
			line_node* node = q.front();
			if(node->color == RED) {
				cout << node->line_coord << "R";
				if(node->parent != NULL) {
					cout << "("  << node->which_child << " " << node->parent->line_coord << ")   ";
				}

				// for(auto it = node->same_coord_lines.begin(); it != node->same_coord_lines.cend(); it++) {
				// 	cout << "[" << (*it)[0] << "," << (*it)[1] << "], ";
				// }
			}
			else {
				cout << node->line_coord << "B";
				if(node->parent != NULL) {
					cout << "("  << node->which_child << " " << node->parent->line_coord << ")   ";
				}
				// for(auto it = node->same_coord_lines.begin(); it != node->same_coord_lines.cend(); it++) {
				// 	cout << "[" << (*it)[0] << "," << (*it)[1] << "], ";
				// }
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

// flatten the tree for the vertical lines into a vector so that we can make the
//		search for min and max endpoints of horizontal lines faster using divide and
//		conquer.
//	use depth-first traversal to push nodes into the flattened_tree from left to right
//		(in ascending order)
// @parameters:
//		root = the root of the tree to be traversed
//		flattened_tree = the flattened version of the tree. pass by reference so that we
//			can add nodes to the vector while recursively traversing the tree.
//			The vector holds not line_node objects, but pointers to those objects
void flatten_tree(line_node* root, vector<line_node*>& flattened_tree){
	// if the root is not NIL, proceed
	if(root != NULL) {
		// go to the left of the tree, if left_child is not NULL
		if(root->left_child != NULL) {
			flatten_tree(root->left_child, flattened_tree);
		}

		// before pushing the node, check if its vector has only 1 element (array of endoints
		// 		if it does, set is_single_line to true, and set signle_line_endpoints
		//		with the only element in the vector same_coord_lines.
		if(root->same_coord_lines.size() == 1) {
			root->is_single_line = true;

			// set the array single_line_endpoints to be used later
			root->single_line_endpoints[0] = (*root->same_coord_lines.begin())[0];
			root->single_line_endpoints[1] = (*root->same_coord_lines.begin())[1];
		}

		// push the current node into the tree
		flattened_tree.push_back(root);
		// go to the right of the tree, if right_child is not NULL
		if(root->right_child != NULL) {
			flatten_tree(root->right_child, flattened_tree);
		}
	}

}

// @return
//		the pointer to the node to which the new node has to be added (either to the
//		left as a left child or to the right as a right child)
int* findNodeIndex(vector<line_node*> flattened_tree, int coord) {
	int size_of_vector = flattened_tree.size();

	// hold the low and high indices, which are used to split the vector, speeding up
	//		the search. 
	int low = 0;
	int high = size_of_vector - 1;

	// we start by splitting the vector and checking the middle element
	int current_index = (low + high)/2;

	long long current_coord;

	if(size_of_vector != 0) {
		// the value of the x_coord/y_coord of the vertical/horizontal line for the current
		//		vector element (line) being observer.
		current_coord = flattened_tree.at(current_index)->line_coord;
	}
		
	// true if the index is found, whether the index points to the line with the exact
	//		coord or to a position in between two other indices.
	// used to terminate the while loop that searches for the index.
	bool index_found = false;

	// true if a line with the same coord is found. false otherwise.
	int exact_index_found;


	static int return_arr[2] = {0, 0};
	
	// search based on coord, then on min_endpoint.
	while(!index_found) {
		// if the vector is empty, return 0
		if(size_of_vector == 0) {
			return_arr[0] = 0;
			return_arr[1] = -2;
			return return_arr;
		} else {
			// sorting by the coord
			if(current_coord < coord) {
				// the coord at the current index is < the given coord. shift the index
				//		to the right
				low = current_index + 1;
				if(low > high) {
					// to get out of the loop
					index_found = true;

				
					// set the current_index to be the index of low 
					current_index = low;
					
					// if the coord is larger than all the other coords in the vector
					if(low >= size_of_vector) {							
						// set the value of the 2nd element of the return array.
						// means the coord should be pushed at the back of the vector.
						exact_index_found = 2;
						
					} else {
						// if the coord is in between two coords in the vector.
						exact_index_found = 0;
					}

				} else {
					// update the current index
					current_index = (low + high)/2;
					current_coord = flattened_tree.at(current_index)->line_coord;
				}
			} else if(current_coord > coord) {
				// the coord at the current index is > the given coord. So divide the
				//		vector further, shifting the index to the left, between the
				//		low and the current_index. the latter becomes the high.
				high = current_index - 1;

				if(high < low) {
					// to get out of the loop
					index_found = true;

					if(high < 0) {
						// means the coord should be pushed at the front of the vector.
						exact_index_found = -1;
						// set the current_index to be the index of the first element in the
						//		vector.
						current_index = 0;						
					} else {
						// if the coord is in between two coords in the vector
						current_index = low;
						exact_index_found = 0;
					}

				} else {
					// update the current index
					current_index = (low + high)/2;
					current_coord = flattened_tree.at(current_index)->line_coord;
				}
			} else {
				// found a line with the same coordinate
				index_found = true;
				exact_index_found = 1;
			}
		}
	}

	return_arr[0] = current_index;
	return_arr[1] = exact_index_found;
	return return_arr;
}

// count the number of plus signs formed by vertical and horizontal lines
// @parameters:
//		h_flattened_tree = a vector holding pointers to horizontal line struct objects.
//			the objects contain all the details for a given coordinate, including an
//			internal vector called same_coord_lines that hold the non-overlapping 
//			endpoints on a given coordinate.
//		v_flattened_tree = the counterpart of h_flattened_tree for vertical lines
//	@return:
//		total_pluses = the number of plus signs formed by crossing horizontal and vertical
//			lines 
long long countPlusSignTree(vector<line_node*> h_flattened_tree, vector<line_node*> v_flattened_tree) {
	// initialize outer and inner horizontal line iterators
	// Note: the outer iterator for vertical lines is declared and initialized in the
	//		for loop. 
	auto h_ln_it_outer = h_flattened_tree.begin();
	vector<std::array<long long, 2>>::iterator h_ln_it_inner;
	vector<std::array<long long, 2>>::iterator v_ln_it_inner;

	// declare left and right endpoints for the horizontal lines to be used in the loops.
	long long h_left_endpoint;
	long long h_right_endpoint;


	// declare left and right endpoints for the vertical lines to be used in the loops.
	long long v_bottom_endpoint;
	long long v_top_endpoint;

	// declare the y_axis varialbe for horizontal lines
	long long h_y_axis;

	// declare the x_axis varialbe for vertical lines
	long long v_x_axis;

	// running total of the number of plus signs found
	int total_plus_signs = 0;

	// these pair of variables hold the indices that correspond to the left and right
	//		endpoints being the coordinates of the two vertical lines that set 
	//		boundaries for traversing the vertical lines.
	int low_index = 0;
	int high_index = 25;

	int counter = 0;
	cout << "h size = " << h_flattened_tree.size() << endl;
	cout << "v size = " <<  v_flattened_tree.size() << endl;

	// iterate over the horizontal lines
	while(h_ln_it_outer != h_flattened_tree.cend()) {
		if(counter % 10000 == 0) {
			cout << counter << endl;
		}
		counter++;
		h_y_axis = (*h_ln_it_outer)->line_coord;
		
		// if same_coord_line of the given horizontal line has only one element,
		//		then no need to iterate over the vector. Only use the array 
		//		single_line_endpoints
		if((*h_ln_it_outer)->is_single_line) {
			int successful_checks;

			// set the left and right endpoint variables using the horizontal endpoint vector
			//		for readability
			h_left_endpoint = (*h_ln_it_outer)->single_line_endpoints[0];
			h_right_endpoint = (*h_ln_it_outer)->single_line_endpoints[1];


			// !!! uncomment this
			low_index = findNodeIndex(v_flattened_tree, h_left_endpoint + 1)[0];
			high_index = findNodeIndex(v_flattened_tree, h_right_endpoint)[0];

			// cout << low_index << " to " << high_index << endl;

			// iterate over the outer vectors of v_endpoints
			for(auto v_ln_it_outer = v_flattened_tree.begin() + low_index; v_ln_it_outer != v_flattened_tree.begin() + high_index; v_ln_it_outer++) {
				v_x_axis = (*v_ln_it_outer)->line_coord;

				// if is_single_line == true, then do not iterate over the same_coord-lines
				if((*v_ln_it_outer)->is_single_line) {
						// determine if the given horizontal and vertical lines form a plus
						// cout << "2222222" << endl;
						//		sign
						if((*v_ln_it_outer)->single_line_endpoints[0] < h_y_axis && (*v_ln_it_outer)->single_line_endpoints[1] > h_y_axis) {
							total_plus_signs++;
							// successful_checks++;
						}
				}
				// else, there are > 1 elements in same_coord_line vector, so we need
				//		to iterate
				else {
					// set the inner vertical endpoints iterator
					v_ln_it_inner = (*v_ln_it_outer)->same_coord_lines.begin();

					//iterate over the inner vectors of v_endpoints
					while(v_ln_it_inner != (*v_ln_it_outer)->same_coord_lines.cend()) {
						
						// cout << "3333333333333333333333333333333333333333333333333333333" << endl;
						// determine if the given horizontal and vertical lines form a plus
						//		sign
						if((*v_ln_it_inner)[0] < h_y_axis && (*v_ln_it_inner)[1] > h_y_axis) {
							total_plus_signs++;
							// successful_checks++;
						}

						// increment the iterator for the inner v_endpoints vector.
						v_ln_it_inner++;
					}
				}
				
			}
		}
		// else, the given horizontal line has more than one line with the given y-axis 
		else {
			// set the inner horizontal endpoints iterator
			h_ln_it_inner = (*h_ln_it_outer)->same_coord_lines.begin();
			

			int successful_checks;

			// !!! iterate over the inner vectors of h_endpoints.
			while(h_ln_it_inner != (*h_ln_it_outer)->same_coord_lines.cend()) {
				// successful_checks = 0;

				// set the left and right endpoint variables using the horizontal endpoint vector
				//		for readability
				h_left_endpoint = (*h_ln_it_inner)[0];
				h_right_endpoint = (*h_ln_it_inner)[1];


				// !!! uncomment this
				low_index = findNodeIndex(v_flattened_tree, h_left_endpoint + 1)[0];
				high_index = findNodeIndex(v_flattened_tree, h_right_endpoint)[0];


				// iterate over the outer vectors of v_endpoints
				for(auto v_ln_it_outer = v_flattened_tree.begin() + low_index; v_ln_it_outer != v_flattened_tree.begin() + high_index; v_ln_it_outer++) {
					v_x_axis = (*v_ln_it_outer)->line_coord;

					// if is_single_line == true, then do not iterate over the same_coord-lines
					if((*v_ln_it_outer)->is_single_line) {
							// determine if the given horizontal and vertical lines form a plus
							//		sign
							if((*v_ln_it_outer)->single_line_endpoints[0] < h_y_axis && (*v_ln_it_outer)->single_line_endpoints[1] > h_y_axis) {
								total_plus_signs++;
								// successful_checks++;
							}
					}
					// else, there are > 1 elements in same_coord_line vector, so we need
					//		to iterate
					else {
						// set the inner vertical endpoints iterator
						v_ln_it_inner = (*v_ln_it_outer)->same_coord_lines.begin();

						//iterate over the inner vectors of v_endpoints
						while(v_ln_it_inner != (*v_ln_it_outer)->same_coord_lines.cend()) {
							
							// determine if the given horizontal and vertical lines form a plus
							//		sign
							if((*v_ln_it_inner)[0] < h_y_axis && (*v_ln_it_inner)[1] > h_y_axis) {
								total_plus_signs++;
								// successful_checks++;
							}

							// increment the iterator for the inner v_endpoints vector.
							v_ln_it_inner++;
						}
					}
					
				}

				// cout << successful_checks << endl;
				// cout << "****************************************" << endl;

				// increment the iterator for the inner h_endpoints vector
				h_ln_it_inner++;
			}
		}
		// increment the iterator for h_lines.
		h_ln_it_outer++;
	}

	cout << "total plus signs = " << total_plus_signs << endl;
	return total_plus_signs;
}



///////////////////////////////////////////////////////////////////////////////////////
//							random D generator
// randomly generates a string of direction characters with length equal to
//	@parameters: 
//		number_of_moves = The chars in the string can be U, R, D, or L.
// 			2 <= number_of_moves <= 2,000,000
//	@return
//		a string of characters containing only 'U', 'R', 'D', or 'L'
string generate_directions(int number_of_moves, int seed) {
	// unsigned int seed = 1663783308;
	// unsigned int seed = (unsigned) time(NULL);
	
	// srand((unsigned) time(NULL));
	srand(seed);

	int random;
	char dir;

	// cout << "d seed = " << seed << endl;

	string direction_string = "";

	for(int i = 0; i < number_of_moves; i++) {
		random = rand() % 4;
		
		dir = digit_to_dir_conv(random);

		direction_string += dir;

		// cout << dir;
	}

	// cout << direction_string << endl;
	return direction_string;
}

// helper function to convert a number representing one of four directions (Up Right Down 
//		and Left) to its respective character (0 == Up == U, 1 == Right == R,
//		2 == Down == D, 3 == Left = L)
// @parameters
//		digit = from 0 to 3
// @return
//		the corresponding direction character for the given digit
char digit_to_dir_conv(int digit) {
	if(digit == 0) {
		return 'U';
	} else if(digit == 1) {
		return 'R';
	} else if(digit == 2) {
		return 'D';
	} else if(digit == 3) {
		return 'L';
	} else {
		cout << "Wrong digit." << endl;
		return 'W';
	}
}

///////////////////////////////////////////////////////////////////////////////////////
//							random L generator
// 1 <= Li <= 1,000,000,000
// generates an array of integers, with a size of number_of_moves. The integers can be
//	from 1 to 1,000,000,000
// @parameters
//		number_of_moves = the number of integers to be generated
//		max_move_size = the maximum integer value that a given random integer can be
// @return
//		a vector of integers representing the number of units for each move, i.e. the
//			lengths generated by the function
vector<int> generate_lengths(int number_of_moves, int max_move_size, int seed) {
	int random_int;

	// int *array_of_lengths = new int(number_of_moves);
	vector<int> vector_of_lengths;
	// int seed = 1663783308;
	// int seed = (unsigned) time(NULL);
	
	auto start = std::chrono::steady_clock::now();
	
	// will be used to obtain a seed for the random number engine	
	// std::mt19937 generator(time(NULL));
	std::mt19937 generator(seed);
 	std::uniform_int_distribution<int> distribution(1, max_move_size);
	for(int i = 0; i < number_of_moves; i++) {
		random_int = distribution(generator);

		vector_of_lengths.push_back(random_int);
		// cout << vector_of_lengths.at(i) << endl;
	}


	// srand(seed);
	// // std::mt19937 generator(time(NULL));
	// // std::mt19937 generator(3);

	// for(int i = 0; i < number_of_moves; i++) {
	// 	random_int = rand() % 50;

	// 	vector_of_lengths.push_back(random_int);
	// 	// cout << vector_of_lengths.at(i) << endl;
	// }

	return vector_of_lengths;
} 


long long countPlusSignTreeOld(vector<line_node*> h_flattened_tree, vector<line_node*> v_flattened_tree) {
	// initialize outer and inner horizontal line iterators
	// Note: the outer iterator for vertical lines is declared and initialized in the
	//		for loop. 
	auto h_ln_it_outer = h_flattened_tree.begin();
	vector<std::array<long long, 2>>::iterator h_ln_it_inner;
	vector<std::array<long long, 2>>::iterator v_ln_it_inner;

	// declare left and right endpoints for the horizontal lines to be used in the loops.
	long long h_left_endpoint;
	long long h_right_endpoint;


	// declare left and right endpoints for the vertical lines to be used in the loops.
	long long v_bottom_endpoint;
	long long v_top_endpoint;

	// declare the y_axis varialbe for horizontal lines
	long long h_y_axis;

	// declare the x_axis varialbe for vertical lines
	long long v_x_axis;

	// running total of the number of plus signs found
	int total_plus_signs = 0;

	// these pair of variables hold the indices that correspond to the left and right
	//		endpoints being the coordinates of the two vertical lines that set 
	//		boundaries for traversing the vertical lines.
	int low_index;
	int high_index;

	int counter = 0;
	cout << "h size = " << h_flattened_tree.size() << endl;
	cout << "v size = " <<  v_flattened_tree.size() << endl;

	// iterate over the horizontal lines
	while(h_ln_it_outer != h_flattened_tree.cend()) {
		counter++;

		h_y_axis = (*h_ln_it_outer)->line_coord;
		// set the left and right endpoint variables using the horizontal endpoint vector
		//		for readability

		// set the inner horizontal endpoints iterator
		h_ln_it_inner = (*h_ln_it_outer)->same_coord_lines.begin();
		
		// !!! iterate over the inner vectors of h_endpoints.
		while(h_ln_it_inner != (*h_ln_it_outer)->same_coord_lines.cend()) {
			h_left_endpoint = (*h_ln_it_inner)[0];
			h_right_endpoint = (*h_ln_it_inner)[1];

			low_index = findNodeIndex(v_flattened_tree, h_left_endpoint + 1)[0];
			high_index = findNodeIndex(v_flattened_tree, h_right_endpoint)[0];

			// iterate over the outer vectors of v_endpoints
			for(auto v_ln_it_outer = v_flattened_tree.begin() + low_index; v_ln_it_outer != v_flattened_tree.begin() + high_index; v_ln_it_outer++) {
				v_x_axis = (*v_ln_it_outer)->line_coord;

				// set the inner vertical endpoints iterator
				v_ln_it_inner = (*v_ln_it_outer)->same_coord_lines.begin();

				//iterate over the inner vectors of v_endpoints
				while(v_ln_it_inner != (*v_ln_it_outer)->same_coord_lines.cend()) {
					
					// determine if the given horizontal and vertical lines form a plus
					//		sign
					if((*v_ln_it_inner)[0] < h_y_axis && (*v_ln_it_inner)[1] > h_y_axis) {
						total_plus_signs++;
					}

					// increment the iterator for the inner v_endpoints vector.
					v_ln_it_inner++;
				}
			}

			// increment the iterator for the inner h_endpoints vector
			h_ln_it_inner++;
		}



		// increment the iterator for h_lines.
		h_ln_it_outer++;

	}

	cout << "total plus signs = " << total_plus_signs << endl;
	return total_plus_signs;
}