#ifndef LINKED_LIST_CPP
#define LINKED_LIST_CPP

#include <iostream>
#include <ctime>
#include "LinkedList.h"
using namespace std;

#define FIRST true
#define LAST false

// Constructors for linked list
LinkedList::LinkedList() {
	// set the head and tail pointers to null
	this->head = NULL;
	this->tail = NULL;

	// set the number of nodes to 0
	this->number_of_nodes = 0;
}

// create a linked list from a given array of values
// @parameters:
//		array_of_values = an array whose values will be added to the linked list
//		size = the size of the array
LinkedList::LinkedList(int* array_of_values, int size) {
	// set the head and tail pointers to null
	this->head = NULL;
	this->tail = NULL;	

	// set the number of nodes to 0
	this->number_of_nodes = 0;

	// loop through the given array and build the linked list
	for(int i = 0; i < size; i++) {
		// use the add_last method
		this->add_last(array_of_values[i]);
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
	// set the head and tail pointers to null
	this->head = NULL;
	this->tail = NULL;	

	// set the number of nodes to 0
	this->number_of_nodes = 0;

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

		// push the value at the end of the linked list
		this->add_last(value);


	}

	// set the number_of_nodes to size
	this->number_of_nodes = num_of_nodes;

}

// destructor
// delete all the nodes in the linked list one by one, starting from the head node
LinkedList::~LinkedList() {
	// call the clear function
	this->clear();
}

// return a pointer to the first node (as an iterator)
Node* LinkedList::begin() {
	return this->head;
}

// return a pointer to the last node (as an iterator)
Node* LinkedList::end() {
	return this->tail;
}

// remove the given node pointer (iterator) from the list
// @parameter:
//		pointer = a pointer to the node that needs to be deleted
// @return:
//		return an pointer (iterator) to the next node
Node* LinkedList::remove(Node* pointer) {
	// reset the next and previous pointers around the given pointer
	if(pointer->previous != NULL) {
		pointer->previous->next = pointer->next;
	}

	if(pointer->next != NULL) {
		pointer->next->previous = pointer->previous;
	}

	// next pointer to return
	Node* next_pointer = pointer->next;

	// if the pointer is the head, set head to NULL
	if(pointer == this->head) {
		this->head = NULL;
	}

	// if the pointer is the tail, set tail to NULL
	if(pointer == this->tail) {
		this->tail = NULL;
	}

	// delete the given pointer
	delete pointer;

	return next_pointer;
}

// set the given node's value. The given node is a pointer to that node (as an
//		iterator) so that we don't need to traverse the list. Time complexity
//		is O(1)
// @parameter:
//		pointer = a pointer to the node that needs to be deleted
//		value = the value to set the given node to
// @return:
//		a node object with the set value, its next and previous links set to null
Node set(Node* pointer, int value) {
	// set the value of the node
	pointer->value = value;

	// declare a new node to return
	Node new_node = *pointer;

	// reset the links of the node to make it impossible to change the list
	//		outside of this function
	new_node.next = NULL;
	new_node.previous = NULL;

	return new_node;
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
		return false;
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
Node* LinkedList::find(int value) {
	// a pointer to a node to traverse, starting from the head
	Node* current_node = this->head;

	// look for the value in the linked list
	while(current_node != NULL) {
		// if the current node has the given value, return that node
		if(current_node->value == value) {
			return current_node;
		}
		// otherwise, go to the next node
		current_node = current_node->next;
	}


	// return current node, which is NULL if we are here
	return current_node;
}

// print the values in the linked list
void LinkedList::print() {
	// a pointer to a node to traverse, starting from the head
	Node* current_node = this->head;

	cout << endl;

	int index = 0;
	while(current_node != NULL) {
		cout << current_node->value << "(" << index << ") --> ";
		
		// move on to the next node
		current_node = current_node->next;
		index++;
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
	else if(position == 0) {
		// call add_first method
		return this->add_first(value);
	}
	else if(position == this->length()) {
		// call the add_last method
		return this->add_last(value);
	}
	// position > 0 && position < this->length
	else {
		// declare a new node
		Node* new_node = new Node;
		new_node->value = value;

		// declare the current node
		Node* current_node;

		// if closer to the first element, start from the head pointer
		if(this->length() - position > position) {
			// a pointer to a node to traverse, starting from the head
			current_node = this->head;	
		}
		// if closer to the last element, start the iteration from the tail pointer
		else {
			// a pointer to a node to traverse, starting from the head
			current_node = this->tail;	
		}
		
		// if the linked list is not empty
		if(current_node != NULL) {
			// if we loop from the front
			if(this->length() - position > position) {
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
			}
			// if we loop from the back, then current position = length - 1
			else {
				// loop through the linked list, and stop at the given position
				int current_pos = this->length() - 1;
				while(current_pos > position) {
					if(current_node->next != NULL) {
						current_node = current_node->next;
						// decrement the current position
						current_pos--;
					}
					else {
						current_pos = position;
					}
				}	
			}

			// reset the next and previous pointers
			new_node->next = current_node;

			new_node->previous = current_node->previous;

			current_node->previous = new_node;	

			// when the current node is the head (inserting at position 0), the previous 
			//		node is NULL.
			if(new_node->previous != NULL) {
				new_node->previous->next = new_node;
			}			

			// increment number of nodes by 1
			this->number_of_nodes++;

			return *new_node;			
		}
	}
}

// append at the end (after the last element)
// @parameters:
//		value = the value to append to the linked list
// @return:
//		the newly appended node
Node LinkedList::add_last(int value) {
	// declare a new node
	Node* new_node = new Node;
	new_node->value = value;

	// if the list is empty
	if(this->length() == 0) {
		this->head = new_node;
		this->tail = new_node;
	}
	else {
		// appending at the back is the same as inserting as the last element	
		// same as new_node->next = NULL
		new_node->next = this->tail->next;

		this->tail->next = new_node;

		new_node->previous = this->tail;

		// reset the tail of the list
		this->tail = new_node;

	}

	// increment the number_of_nodes
	this->number_of_nodes++;

	return *new_node;	
	
}


// append at the front (position = 0, before head)
// @parameters:
//		value = the value to append to the linked list
// @return:
//		the newly appended node
Node LinkedList::add_first(int value) {
	// declare a new node
	Node* new_node = new Node;
	new_node->value = value;

	// if the list is empty
	if(this->length() == 0) {
		this->head = new_node;
		this->tail = new_node;
	}
	else {
		// appending at the back is the same as inserting as the last element	
		// same as new_node->next = NULL
		new_node->previous = this->head->previous
		;
		new_node->next = this->head;

		this->head->previous = new_node;


		// reset the tail of the list
		this->head = new_node;
	}

	// increment the number_of_nodes
	this->number_of_nodes++;

	return *new_node;
}


// append the given linked list at the end (after the last element)
// @parameters:
//		linked_list = the linked list to append to this list
void LinkedList::add_last(LinkedList linked_list) {
	// iterate through the given linked list and create new nodes for each
	//		node in that list, and append it to this list one at a time
	Node* iterator = linked_list.begin();

	while(iterator != NULL) {
		// create a new node
		Node* new_node = new Node;

		// set its value to the value of the iterator
		new_node->value = iterator->value;
		// set the next to NULL to avoid strange behavior (infinite list)
		new_node->next = NULL;

		// append it to this linked list
		if(this->tail != NULL) {
			this->tail->next = new_node;
		}
		new_node->previous = this->tail;
		this->tail = new_node;

		// move on to the next node
		iterator = iterator->next;
	}
}

// append the given linked list at the front (position = 0, before head)
// @parameters:
//		linked_list = the linked list to append to this list
void LinkedList::add_first(LinkedList linked_list) {
	// start from the end of the given linked list
	Node* iterator = linked_list.end();

	while(iterator != NULL) {
		cout << "adding " << iterator->value << endl;
		// create a new node
		Node* new_node = new Node;

		// set its value to the value of the iterator
		new_node->value = iterator->value;
		// set the previous to NULL to avoid strange behavior (infinite list)
		new_node->previous = NULL;

		// append it to this linked list
		if(this->head != NULL) {
			this->head->previous = new_node;
		}
		new_node->next = this->head;
		this->head = new_node;

		// move on to the previous node
		iterator = iterator->previous;
	}
}


// remove the first oocurrence a node with the given value
// @parameter:
//		value = the value of the node to be deleted
bool LinkedList::remove_first_occurrence(int value) {
	return this->remove_occurrence_helper(value, FIRST);
}



// remove the node at the end
// return the removed node
Node LinkedList::remove_last() {
	// declare the node to return
	Node removed_node_to_return;

	// if the list is not empty
	if(this->length() >= 1) {
		// store the tail in a variable so we can return it 
		Node removed_node_to_return = *(this->tail);

		// if there is only 1 element, set both head and tail to NULL after deletion
		if(this->length() == 1) {
			// delete the tail
			delete this->tail;

			// set both head and tail to NULL
			this->head = NULL;
			this->tail = NULL;

		}
		// only work with tail
		else {
			// temporarily store the second of the last node, so that we can set the tail
			//		to that node after deleting the tail
			Node* new_last = this->tail->previous;

			// set the next of the tail's previous node to NULL
			this->tail->previous->next = NULL;

			

			delete this->tail;

			// set the tail to its previous node
			this->tail = new_last;
		}

		// decrement the number_of_nodes by 1
		this->number_of_nodes--;
	}

	// return the node deleted
	return removed_node_to_return;
}

// remove the element at the front (the head)
Node LinkedList::remove_first() {
	// declare the node to return
	Node removed_node_to_return;

	// pop the head as long as it is not NULL
	if(this->head != NULL) {	
		// store the head in a variable so we can return it 
		Node removed_node_to_return = *(this->tail);

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

		// decrement the number_of_nodes by 1
		this->number_of_nodes--;
	}


}


// removes all elements from the list
void LinkedList::clear() {
	// start from the head node
	Node* node_to_remove = this->head;

	// use this to keep track of the next node after the node_to_del is deleted
	Node* next_node;

	// delete all the node pointers in the list, because they have been allocated 
	//		dynamically
	while(node_to_remove != NULL) {
		next_node = node_to_remove->next;

		// delete the node
		delete node_to_remove;

		// move on to the next node
		node_to_remove = next_node;


	}

	cout << endl;

	// set both head and tail node pointers to null
	this->head = NULL;
	this->tail = NULL;

	// set the size of the list to 0
	this->number_of_nodes = 0;
}

// Returns the index of the first occurrence of the specified element in the list,
//		or -1 if the does not contain the element.
// @parameters:
//		value = the value whose index we want to find (from the beginning)
// @return
//		the index of the given value in the list
int LinkedList::index_of(int value) {
	// begin from the head (first element)
	Node* current_node = this->head;

	// keep track of the index in the following loop
	int current_index = 0;

	// iterate through the elements in the list
	while(current_node != NULL) {
		if(current_node->value == value){
			// return the index
			return current_index;
		}
		else {
			// move on to the next node
			current_node = current_node->next;
		}

		// increment the index
		current_index++;
	}

	// if we are here, then the value was not found.
	return -1;
}

// Returns the index of the last occurrence of the specified element in the list,
//		or -1 if the does not contain the element.
// @parameters:
//		value = the value whose index we want to find (from the end)
// @return
//		the index of the given value in the list
int LinkedList::last_index_of(int value) {
	// begin from the tail (last element)
	Node* current_node = this->tail;

	// keep track of the index in the following loop
	// begin with the last index
	int current_index = this->length() - 1;

	// iterate through the elements in the list
	while(current_node != NULL) {
		if(current_node->value == value){
			// return the index
			return current_index;
		}	
		// move on to the next node
		current_node = current_node->previous;

		// decrement the index
		current_index--;
	}

	// if we are here, then the value was not found.
	return -1;
}

// !!! implement the ones below
// return true if this list contains the specified element
// @parameters:
//		value = the given value we want to find in the list
// @return:
//		true if the value is in the list
//		false otherwise
bool LinkedList::contains(int value) {
		// begin from the head (first element)
	Node* current_node = this->head;

	// iterate through the elements in the list
	while(current_node != NULL) {
		if(current_node->value == value){
			// return true
			return true;
		}	
		// move on to the next node
		current_node = current_node->next;
	}

	// if we are here, then the value was not found. return false
	return false;
}

// retrieve (do not remove) the first element in the list
Node LinkedList::peek_first() {
	return *(this->head);
}

// retrieve (do not remove) the last element in the list
Node LinkedList::peek_last() {
	return *(this->tail);
}	

// removes the element at the specified position in this list 
// @return:
//		the removed element
Node LinkedList::remove_at_index(int index) {
	if(index > 0 && index < this->length()) {
		// declare current node
		Node* current_node;

		// declare is_next
		bool is_next;
		
		// start from the beginning if the index is less than half of the size of the list
		if(this->length() - index > index) {
			current_node = this->head;

			// we need to iterate forward
			is_next = true;

		}
		else {
			current_node = this->tail;
			
			// we need to iterate forward
			is_next = false;

			// convert the index from starting from the beginning to starting from the end
			index = this->length() - index - 1;
		}		

		// loop until getting to the desired node
		// iterate over the list, either forward or backward, depending on is_next
		for(int i = 0; i < index; i++) { 
			if(is_next) {
				current_node = current_node->next;
			}
			else {
				current_node = current_node->previous;
			}
		}

		// store the node before removing
		Node node_to_return = *current_node;

		delete current_node;

		return node_to_return;
	}
	else {
		throw std::out_of_range("The index provided is out of range.");
	}
}

// sets the given value at the given position in the list
// @parameters:
//		position = the index at which to set the value
//		value = the value to reset at the given position
// @return:
//		the set node
Node LinkedList::set(int value, int position) {
	// if position is out of range, throw out of range error
	if(position < 0 || position >= this->length()){ 
		throw std::out_of_range("The position provided is out of range."); 
	}
	else {
		// node pointer to iterate
		Node* node_to_set = this->head;

		// keep track of the position
		int counter = 0;

		// get to the node and set its value
		while(counter != position) {
			node_to_set = node_to_set->next;

			counter++;
		}

		// set the value of the node at the given position
		node_to_set->value = value;

		// declare a new node to return
		Node new_node = *node_to_set;

		// reset the links of the node to make it impossible to change the list
		//		outside of this function
		new_node.next = NULL;
		new_node.previous = NULL;

		return new_node;
	}
}

	
// remove the last oocurrence a node with the given value
// @parameter:
//		value = the value of the node to be deleted
// @return:
//		true = if the node with the given value was successfully deleted
//		false = otherwise
bool LinkedList::remove_last_occurrence(int value) {
	// call the helper function to remove the last occurrence
	return this->remove_occurrence_helper(value, LAST);
}


// remove last/first occurrence helper
// since removing the last and firs occurrence are almost the same, we have a helper
// 		function to do all the things in common
// @parameters:
//		value = the value of the node to delete
//		first_or_last = which occurrence to delete, the first or last 
// @return:
//		true = if the node with the given value was successfully deleted
//		false = otherwise
bool LinkedList::remove_occurrence_helper(int value, bool first_or_last) {
	// declare node_to_del
	Node* node_to_del;

	// delete the first occurrence
	if(first_or_last == FIRST) { 
		// a pointer to a node to traverse, starting from the head
		node_to_del = this->head;		
	}
	else {
		// a pointer to a node to traverse, starting from the tail
		node_to_del = this->tail;		
	}

	// will store either the head or the tail of the list
	Node* temp_head_or_tail = NULL;

	// look for the value in the linked list
	while(node_to_del != NULL) {
		// if the current node has the given value, delete it
		if(node_to_del->value == value) {
			// !!! reset next and previous pointers before deleting the node
			if(node_to_del->previous != NULL) {
				node_to_del->previous->next = node_to_del->next;
			}
			// it is the head of the list
			else {
				temp_head_or_tail = this->head;
			}

			// if this node is not the tail of the list
			if(node_to_del->next != NULL) {
				node_to_del->next->previous = node_to_del->previous;
			}
			// else it's the tail of the list
			else {
				temp_head_or_tail = this->tail;
			}

			// delete the node
			delete node_to_del;
		
			// // set it to NULL to end the loop
			// node_to_del = temp_head_or_tail;

			// decrement the number_of_nodes by 1
			this->number_of_nodes--;

			return true;
		}
		else {
			// if first occurrence, go to the next node
			if(first_or_last == FIRST) {
				// otherwise, go to the previous node
				node_to_del = node_to_del->next;				
			}
			else {
				// otherwise, go to the previous node
				node_to_del = node_to_del->previous;
			}

		}
	}
	// node was not found
	return false;
}

// swaps the given nodes
void LinkedList::swap_nodes(Node* left_it, Node* right_it) {
	Node* temp_next_of_left = left_it->next;
	Node* temp_prev_of_left = left_it->previous;

	// adjust the next and previous pointers before swapping
	if(left_it->next != NULL) {
		left_it->next->previous = right_it;
	}
	if(left_it->previous != NULL) {
		left_it->previous->next = right_it;
	}
	if(right_it->next != NULL) {
		right_it->next->previous = left_it;
	}
	if(right_it->previous != NULL) {
		right_it->previous->next = left_it;
	}

	// swap the left and right iterators
	left_it->next = right_it->next;
	left_it->previous = right_it->previous;

	right_it->next = temp_next_of_left;
	right_it->previous = temp_prev_of_left;

	// make sure the head and tail pointers point to the right node, in case
	//		either the left or the right iterators are the head/tail of the
	//		list. 
	if(this->head == left_it) {
		this->head = right_it;
	}
	if(this->tail == right_it) {
		this->tail = left_it;
	}

}

#endif