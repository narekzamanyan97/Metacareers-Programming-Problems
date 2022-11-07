#include <iostream>
#include "../../Data Structures - Implementations/Linked List (Double)/LinkedList.cpp"
using namespace std;

void delete_middle_node(Node* node_to_del, LinkedList& linked_list);

int main() {
	LinkedList linked_list = LinkedList(99, 22, 100);

	int value;

	Node* node_ptr;

	do {
		linked_list.print();
		cout << "Enter a value to delete, enter -1 to exit: " << endl;
		cin >> value;

		node_ptr = linked_list.find(value);

		if(value != -1) {
			delete_middle_node(node_ptr, linked_list);
		}

	} while (value != -1);

	return 0;
}


// @parameters:
// 		node_to_del = a pointer to the node, which will be deleted from the
//			linked list, unless it is the first or the last node
// 		linked_list = a reference to the linked list
void delete_middle_node(Node* node_to_del, LinkedList& linked_list) {
	// check if the node to del is the first node
	if(node_to_del == linked_list.begin()) {
		// do not do anything
		cout << "First node. Cannot delete." << endl;
	}
	// the node is the last one
	else if(node_to_del->next == NULL){
		// do not do anything
		cout << "Last node. Cannot delete." << endl;
	}
	else {
		// iterate through the list to the node, in order to reset the pointers
		// start from the first node
		Node* previous_node = linked_list.begin();

		// male sure the list is not empty
		if(previous_node != NULL) {
			// get to the previous node of node_to_del
			while(previous_node->next != node_to_del) {
				// go to the next node
				previous_node = previous_node->next;
			}

			// now, previous_node is the node behind node_to_del
			// set its next pointer to the next pointer of node_to_del
			previous_node->next = node_to_del->next;

			// we can now delete the node
			delete node_to_del;
		}
		else {
			cout << "The list is empty." << endl;
		}
	}
}