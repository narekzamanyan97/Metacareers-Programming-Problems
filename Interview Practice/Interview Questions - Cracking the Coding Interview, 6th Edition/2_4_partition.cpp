#include <iostream>
#include "../../Data Structures - Implementations/Linked List (Double)/LinkedList.cpp"
using namespace std;

void partition_doubly_linked(LinkedList& linked_list, int value);

int main() {
	LinkedList linked_list = LinkedList(44, 30, 120);

	int value;

	Node* node_ptr;

	do {
		linked_list.print();
		cout << "Enter a value to partition, enter -1 to exit: " << endl;
		cin >> value;

		if(value != -1) {
			partition_doubly_linked(linked_list, value);
		}

	} while (value != -1);

	return 0;
}

// partitions a linked list around the given value, such that all nodes less
//		than x come before all nodes greater than or equal to x. Use doubly
//		linked list
// @parameters:
//		linked_list = a reference to the linked list object
//		value = the value to be used for partition
void partition_doubly_linked(LinkedList& linked_list, int value) {
	// instantiate left and right iterators
	Node* left_it = linked_list.begin();
	Node* right_it = linked_list.end();

	// temporary values for swapping if we are swapping only the values, 
	//		leaving the nodes unmoved.
	int temp_value;

	// temporary node pointers for swapping, if we are swapping the acutal
	//		nodes
	Node* temp_next_of_left;
	Node* temp_prev_of_left;

	// temporary left it for swapping the actual nodes
	Node* temp_left_it;

	// when these two iterators point to the same value, that's when we stop
	while(left_it != right_it) {
		// if left and right sides contain the wrong nodes, swap them
		if(left_it->value >= value && right_it->value < value) {
			// ////////////////////////////////////////////////////////////
			// 					only swap values
			// temp_value = left_it->value;
			// left_it->value = right_it->value;
			// right_it->value = temp_value;
			// move the iterators
			// left_it = left_it->next;
			// prevent infinite loop
			// if(left_it != right_it) {
			// 	right_it = right_it->previous;
			// }
			// ////////////////////////////////////////////////////////////
			// 					swap nodes
			// need this for swapping the iterators
			temp_left_it = left_it;
		
			linked_list.swap_nodes(left_it, right_it);

			// swap the iterators
			left_it = right_it;
			right_it = temp_left_it;

			// move the iterators
			left_it = left_it->next;
			// prevent infinite loop
			if(left_it != right_it) {
				right_it = right_it->previous;
			}			
		}
		// the left node is correctly placed, but the right one is not
		// 		only move the left node iterator (the correct node iterator)
		else if(left_it->value < value && right_it->value < value) {
			left_it = left_it->next;
		}
		// the right node is correctly placed, but the left one is not
		//		only move the right node iterator (the correct node iterator)
		else if(left_it->value >= value && right_it->value >= value) {
			right_it = right_it->previous;
		}
		// both are correct
		// first move the left iterator, then, if it is not the same as the 
		//		right iterator, move the right iterator as well, to avoid
		//		infinite loop
		else {
			left_it = left_it->next;
			// prevent infinite loop
			if(left_it != right_it) {
				right_it = right_it->previous;
			}
		}
	}
}