#include "binarySearchTree.cpp"

void demo_delete_node_input(BinarySearchTree* tree);

int main() {
	// // an array of values
	// int values[31] = {11, 19, 29, 5, 1, 14, 10, 3,
	// 				8, 7, 30, 40, 35, 22, 24, 20, 16, 17,
	// 				2, 18, 12, 36, 0, -4, 15, 27, 34, 41, 21,
	// 				13, 9};

	// BinarySearchTree bst_tree = BinarySearchTree(values, 31);
	BinarySearchTree bst_tree = BinarySearchTree(-1, 5, 100);

	bst_tree.display_tree();
	demo_delete_node_input(&bst_tree);


	return 0;
}

// deletes user-input values from a tree
// asks the user for the values to delete from the tree that was built.
// @parameters:
//		tree = a pointer to the BinarySearchTree object
void demo_delete_node_input(BinarySearchTree* tree) {
	int val_to_del = 0;
	
	// delete an element
	while(val_to_del != -1 && !tree->is_empty()) {
		if(!tree->is_empty()) {
			cout << "tree is not empty." << endl;
		}
		cout << "*******************************************************" << endl;
		cout << "Enter value to delete: " << endl;
		cin >> val_to_del;

		if(!tree->delete_node(val_to_del)) {
			cout << "value " << val_to_del << " is not in the tree." << endl;
			tree->display_tree();
		}
		else{
			if(tree->is_binary_tree()) {
				cout << "Binary Tree." << endl;
			}
			else {
				cout << "Not a binary tree" << endl;
			}
			tree->display_tree();
		}
	}

	if(tree->is_empty()) {
		cout << "The tree is empty." << endl;
	}
}