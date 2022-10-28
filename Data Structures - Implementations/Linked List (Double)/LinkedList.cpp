#ifndef LINKED_LIST_CPP
#define LINKED_LIST_CPP

#include <iostream>
#include <ctime>
#include "LinkedList.h"
using namespace std;

// Constructors for linked list
LinkedList::LinkedList() {
	// set the head pointer to null
	this->head = NULL;

	// set the number of nodes to 0
	this->number_of_nodes = 0;
}

// create a linked list from a given array of values
// @parameters:
//		array_of_values = an array whose values will be added to the linked list
//		size = the size of the array
LinkedList::LinkedList(int* array_of_values, int size) {
	// set the head pointer to null
	this->head = NULL;

	// loop through the given array and build the linked list
	for(int i = 0; i < size; i++) {
		// use the push_back method
		this->push_back(array_of_values[i]);
	}

	// set the number_of_nodes to size
	this->number_of_nodes = size;

}

// create a linked list randomly
// @parameters:
// 		seed = a seed for the random generator
// 		num_of_nodes = number of nodes to be added to the linked list
//		max_value = the max integer value to be randomly generated.
LinkedList::LinkedList(int seed, int num_of_nodes, int max_value) {
	// set the head pointer to null
	this->head = NULL;

	// if max_value < 2 * number_of_nodes, reset max_value to be twice num_of_nodes
	if(max_value < 2 * num_of_nodes) {
		max_value = 2 * num_of_nodes;
	}

	// use random seed if seed = -1
	if(seed == -1) {
		srand(time(NULL));
	}
	else {
		srand(seed);
	}

	// value to add
	int value;

	for(int i = 0; i < num_of_nodes; i++) {
		// generate the random value
		value = rand() % (max_value + 1);

		cout << value << ", ";
		// push the value at the end of the linked list
		this->push_back(value);
	}

	cout << endl;

	// set the number_of_nodes to size
	this->number_of_nodes = num_of_nodes;
}

// destructor
// delete all the nodes in the linked list one by one, starting from the head node
LinkedList::~LinkedList() {
	// will be used to loop over the nodes and delete them
	Node* current_node = this->head;

	// stores the next node. acts as a placeholder
	Node* next_node = current_node;

	// while there are nodes, delete them
	while(current_node != NULL) {
		// update the next node to be the next node of the current node
		next_node = current_node->next;

		// delete the current node
		delete current_node;

		// set the current node to the next node
		current_node = next_node;
	}
}

// determine if the linked list is empty
// @return:
//		true if the linked list is empty
//		false otherwise
bool LinkedList::is_empty() {
	if(this->head == NULL) {
		return true;
	}
	else {
		false;
	}
}

// determine the number of elements in the linked list
// count the number of nodes in the linked list and return it
// @return:
//		the number of nodes in the linked list
int LinkedList::length() {
	return this->number_of_nodes;
}

// traverse the linked list and return a pointer to that node
// @parameters:
//		value = a value to search for in the 
// @return:
//		the node that has the given value, or null, if the value is not in the linked list
Node LinkedList::find(int value) {
	// a pointer to a node to traverse, starting from the head
	Node* current_node = this->head;

	// look for the value in the linked list
	while(current_node != NULL) {
		// if the current node has the given value, return that node
		if(current_node->value == value) {
			return *current_node;
		}
		// otherwise, go to the next node
		current_node = current_node->next;
	}


	// return current node, which is NULL if we are here
	return *current_node;
}

// print the values in the linked list
void LinkedList::print() {
	// a pointer to a node to traverse, starting from the head
	Node* current_node = this->head;

	cout << endl;
	while(current_node != NULL) {
		cout << current_node->value << " --> ";
		
		// move on to the next node
		current_node = current_node->next;
	}
	cout << endl;
}



// insert at the given position. Return an object to the head pointer
// @parameters:
//		value = the value to insert into the linked list
//		position = the position to insert the value at
// @return:
//		the newly inserted node, or NULL if the position is out of range
Node LinkedList::insert(int value, int position) {
	// if position < 0 or > length of linked list, return null
	if(position < 0 || position > this->length()) {
		throw std::out_of_range("The position provided is out of range.");
	}
	// position > 0 && position <= this->length
	else {
		// a pointer to a node to traverse, starting from the head
		Node* current_node = this->head;
		
		// declare a new node
		Node* new_node = new Node;

		new_node->value = value;

		// if the linked list is not empty
		if(current_node != NULL) {
			// loop through the linked list, and stop at the given position
			int current_pos = 0;
			while(current_pos < position) {
				if(current_node->next != NULL) {
					current_node = current_node->next;
					current_pos++;
				}
				else {
					current_pos = position;
				}
			}		




			// reset the next and previous pointers
			// case 1: inserting in the middle of two elements
			if(position < this->length()) {
				new_node->next = current_node;

				new_node->previous = current_node->previous;

				current_node->previous = new_node;	


				// when the current node is the head (inserting at position 0), the previous 
				//		node is NULL.
				if(new_node->previous != NULL) {
					new_node->previous->next = new_node;
				}			
			}
			// appending at the end
			else {
				new_node->next = current_node->next;

				current_node->next = new_node;

				new_node->previous = current_node;
			}


			// increment number of nodes by 1
			this->number_of_nodes++;

			return *new_node;			
		}
		// the linked list is empty. 
		else {
			// set the head to be the new node
			this->head = new_node;

			this->head->previous = NULL;
			this->head->next = NULL;
		}

	}
}

// append at the end (after the last element)
// @parameters:
//		value = the value to append to the linked list
// @return:
//		the newly appended node
Node LinkedList::push_back(int value) {
	// appending at the back is the same as inserting as the last element
	return this->insert(value, this->length());
}

// append at the front (position = 0, before head)
// @parameters:
//		value = the value to append to the linked list
// @return:
//		the newly appended node
Node LinkedList::push_front(int value) {
	// appending at the front is the same as inserting as the first element (position 0)
	return this->insert(value, 0);
}


// delete a node with the given value
// @parameter:
//		value = the value of the node to be deleted
void LinkedList::delete_(int value) {
	// a pointer to a node to traverse, starting from the head
	Node* node_to_del = this->head;

	// look for the value in the linked list
	while(node_to_del != NULL) {
		// if the current node has the given value, delete it
		if(node_to_del->value == value) {
			// !!! reset next and previous pointers before deleting the node
			if(node_to_del->previous != NULL) {
				node_to_del->previous->next = node_to_del->next;
			}

			if(node_to_del->next != NULL) {
				node_to_del->next->previous = node_to_del->previous;
			}

			// delete the node
			delete node_to_del;
			// set it to NULL to end the loop
			node_to_del = NULL;
		}
		else {
			// otherwise, go to the next node
			node_to_del = node_to_del->next;
		}
	}

}

// delete (pop) the node at the end
void LinkedList::pop_back() {
	// get to the last node
	Node* node_to_del = this->head;

	// loop through the linked list and get to the last node
	while(node_to_del->next != NULL) {
		node_to_del = node_to_del->next;
	}

	// set the next node of the previous node to NULL
	// if the linked list has more than 1 element
	if(node_to_del->previous != NULL) {
		// set the next pointer of the previous of the node to delete to NULL
		node_to_del->previous->next = NULL;

		// delete the node
		delete node_to_del;
	}
	// if the linked list has exactly 1 element
	else{
		// delete the node 
		delete node_to_del;

		// set the head node pointer to NULL
		this->head = NULL;

	}

	// now, node_to_del points to the last node. delete it
	delete node_to_del;
}

// delete (pop) the element at the front (the head)
void LinkedList::pop_front() {
	// pop the head as long as it is not NULL
	if(this->head != NULL) {		
		// set the previous of the next node to NULL
		if(this->head->next != NULL) {
			this->head->next->previous = NULL;
		}

		// temporarily store the head node
		Node* temp_node = this->head;

		// reset the head to the next node
		this->head = this->head->next;

		// delete the address pointed to by the temporary node
		delete temp_node;
	}


}


#endif