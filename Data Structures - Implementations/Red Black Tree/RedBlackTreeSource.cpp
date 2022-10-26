#include "RedBlackTree.cpp"


// functions for the main method to demo the insert, delete, display, and check 
//		functions
RedBlackTree demo_build_tree_from_array(int array_of_values[], int size_of_array);
RedBlackTree demo_build_tree_input();
RedBlackTree demo_build_tree_random(int num_of_nodes, int max_value);
void demo_delete_node_array(RedBlackTree& tree, int vals_to_del[], int size_of_array);
void demo_delete_node_input(RedBlackTree& tree);
void demo_delete_node_random(RedBlackTree& tree, int* array_of_values, int size_of_array, int num_of_nodes_to_del);

bool is_integer(string str);

int main() {

	int array[] = {20, 47, 27, 37, 29, 56, 33, 79, 42, 87, 35, 6, 74, 55, 21, 52, 61, 71, 34, 62, 75, 98, 91, 69, 11, 80, 72, 0, 85, 8};
	// RedBlackTree tree = demo_build_tree_random(150, 250);
	// RedBlackTree tree = demo_build_tree_from_array(array, 30);
	// RedBlackTree tree = RedBlackTree(array, 30);
	RedBlackTree tree = RedBlackTree(-1, 220, 400);

	int* flattened_tree = new int[230];


	int size = tree.to_array(flattened_tree);

	demo_delete_node_random(tree, flattened_tree, 220, 220);

	// int values_to_delete[207] = {42, 399, 149, 303, 153, 257, 427, 99, 70, 446, 352, 245, 143, 116, 156, 4, 434, 473, 24, 301, 387, 43, 240, 194, 497, 431, 346, 411, 351, 252, 368, 302, 192, 390, 354, 287, 450, 383, 74, 189, 289, 126, 330, 163, 87, 115, 454, 459, 55, 471, 2, 316, 397, 280, 146, 52, 495, 376, 97, 488, 466, 342, 310, 360, 361, 145, 89, 417, 36, 170, 409, 6, 242, 362, 100, 258, 254, 44, 159, 314, 319, 17, 285, 300, 88, 57, 140, 373, 26, 475, 498, 231, 200, 128, 441, 133, 371, 455, 268, 401, 267, 113, 138, 134, 398, 353, 462, 331, 272, 127, 19, 262, 211, 305, 234, 109, 335, 20, 467, 141, 137, 47, 29, 199, 238, 403, 312, 317, 135, 35, 381, 295, 413, 255, 288, 439, 83, 355, 183, 132, 469, 491, 483, 266, 440, 16, 198, 412, 392, 375, 180, 185, 377, 188, 325, 274, 499, 10, 477, 470, 158, 50, 394, 14, 264, 480, 391, 68, 422, 222, 418, 228, 201, 349, 367, 478, 445, 400, 136, 79, 324, 457, 142, 157, 456, 7, 250, 419, 378, 315, 246, 484, 444, 313, 276, 437, 31, 63, 322, 235, 225, 464, 476, 177, 179, 277, 438};
	// demo_delete_node_random(tree, 230, 205);

	cout << "after deletion: " << endl;
	tree.display_tree();	
	if(tree.is_red_black_tree()) {
		cout << "Red black tree." << endl;
	}
	else {
		cout << "Not a red black tree." << endl;
	}

	delete[] flattened_tree;
	flattened_tree = NULL;

	return 0;
}



// deletes the nodes having the given values in the array from the given tree 
// @parameters:
//		tree = a RedBlackTree object
//		vals_to_del = an array of integer values representing the nodes that need to be
//			deleted
//		size_of_array = the size of the input array
//			deleted 
void demo_delete_node_array(RedBlackTree& tree, int* vals_to_del, int size_of_array) {
	node* node_to_del;

	// Example 1)
	// int line_coordinates[16] = {20, 5, 30, 40, 50, 35, 6, 9, 3, 60, 33, 1, 34, 0, 70, 2};
	// int vals_to_del[] = {30, 5, 6, 40, 20, 33, 70, 34, 0, 2, 1, 3, 60, 50};
	// int vals_to_del[] = {30, 5, 6, 40, 20, 33, 70, 34, 0, 60, 2, 50};
	for(int i = 0; i < size_of_array; i++) {
		node_to_del = tree.binary_search(vals_to_del[i]);
		if(node_to_del != NULL) {

			tree.delete_node(node_to_del);
		}
		else {
			cout << "value not in the tree.\n";
		}
	}
	
	// tree.display_tree();				
}

// randomly delete num_of_nodes number of nodes from the given tree. Deletes nodes in 
//		order
// @parameters
//		tree = a RedBlackTree object
//		array_of_values = the flattened version of the tree
//		size_of_array = the number of elements in the array_of_values (tree)
//		num_of_nodes_to_del = the number of nodes to be deleted from the tree. Must be
//			less than the number of nodes
void demo_delete_node_random(RedBlackTree& tree, int* array_of_values, int size_of_array, int num_of_nodes_to_del) {
	// temp variable to store the node to be deleted
	node* node_to_del;

	// value to delete
	int value; 

	// reset num_of_nodes to delete if it is larger than the size of the given array
	if(num_of_nodes_to_del > size_of_array) {
		num_of_nodes_to_del = size_of_array - 10;
	}

	// delete given number of nodes
	for(int i = size_of_array - 1; i >= size_of_array - num_of_nodes_to_del; i--) {
		// if there are no more nodes in the tree (tree is empty), break from the loop
		//		and exit the function
		if(tree.is_empty()) {
			cout << "Tree is empty." << endl;
			break;
		} else {

			// store the node found into node_to_del
			node_to_del = tree.binary_search(array_of_values[i]);

			// cout << value << endl;
			// delete the node
			tree.delete_node(node_to_del);
		}
	}
}

// deletes user-input values from a tree
// asks the user for the values to delete from the tree that was built.
// @return
//		tree = a RedBlackTree object to delete nodes from
void demo_delete_node_input(RedBlackTree& tree) {
	// reset is_done to anything other than 'e' or 'E'
	string is_done;

	// the variable for the value to be deleted.
	int value;


	// store the node to be deleted
	node* node_to_del;


	cout << "Enter a value to insert. Enter Non Int to exit \n";
	cin >> is_done;

	while(is_integer(is_done)) {
		// convert the input string into an int
		value = stoi(is_done);

		node_to_del = tree.binary_search(value);

		if(node_to_del != NULL) {

			tree.delete_node(node_to_del);
			tree.display_tree();		

			if(tree.is_binary_tree()) {
				cout << "tree is still a binary tree." << endl;
			} else {
				cout << "Not a binary tree." << endl;
			}
			if(tree.is_red_black_tree()) {
				cout << "tree is still a red black tree." << endl;
			} else {
				cout << "Not a red black tree." << endl;
			}
		}
		else {
			cout << "value not in the tree.\n";
		}
	
		cout << "Enter a value to delete. Enter Non Int to exit \n";
		cin >> is_done;
	}
}

// build a tree using the values in a given array
// @parameters:
//		array_of_values = an array of int values to be inserted into the tree
//		size_of_array = the size of the input array
// @return
//		tree = a RedBlackTree object built using the given array
RedBlackTree demo_build_tree_from_array(int* array_of_values, int size_of_array) {
	// a pointer holding the root of the tree
	RedBlackTree tree = RedBlackTree();

	// iterate over the array of values, and insert the values into the tree one by one
	for(int i = 0; i < size_of_array; i++) {
		// cout << array_of_values[i] << endl;
		tree.insert(array_of_values[i]);
		// if(!is_binary_tree(root)) {
		// 	cout << "Not a Binary tree" << endl;
		// 	display_tree(root);
		// }
		// display_tree(root);
	}

	return tree;
}

// builds a tree from input values given by the user
// @return
//		tree = a RedBlackTree object built using input values
RedBlackTree demo_build_tree_input() {
	// a pointer holding the root of the tree
	RedBlackTree tree = RedBlackTree();

	// the variable for the value to be inserted.
	int value;

	// a char variable for exiting from the loop
	string is_done;


	cout << "Enter a value to insert. Enter Non Int to exit \n";
	cin >> is_done;

	while(is_integer(is_done)) {
		// convert the string into an int
		value = stoi(is_done);

		tree.insert(value);

		cout << "Enter a value to delete. Enter Non Int to exit \n";
		cin >> is_done;
	}

	return tree;
}


// build a tree from a randomly generated integers. The tree will have num_of_nodes
//		number of elements
// @parameters
//		num_of_nodes = the number of nodes we want the tree to have
// @return
//		tree = a RedBlackTree object built using randomly generated values
RedBlackTree demo_build_tree_random(int num_of_nodes, int max_value) {
	// a pointer holding the root of the tree
	RedBlackTree tree = RedBlackTree();

	// initialize random seed
	srand(time(NULL));
	
	// if max_value < num_of_nodes, then reset max value to be 10 higher
	if(max_value < num_of_nodes) {
		max_value = num_of_nodes + 10;
	}

	// value to add
	int value; 

	for(int i = 0; i < num_of_nodes; i++) {
		value = rand() % (max_value);

		// if the random number has already been generated and inserted into the tree,
		//		try again
		while(!tree.insert(value)) {
			value = rand() % max_value;
		}	
		cout << value << ", ";	
	}

	cout << endl;

	return tree;

}


// a helper function to determine if a given string is an integer
// @parameter:
//		str = a string to check
// @return
//		true = if the string is an int (e.g. "31232")
//		false = otherwise (e.g. "3kd20")
bool is_integer(string str) {
	for(int i = 0; i < str.length(); i++) {
		if(isdigit(str[i]) == false) {
			return false;
		}
	}

	return true;
}