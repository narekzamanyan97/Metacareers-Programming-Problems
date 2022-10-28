#ifndef LINKED_LIST_H
#define LINKED_LIST_H

struct Node {
	int value;
	Node* next;
	Node* previous;
};

// duplicates are allowed
class LinkedList {
private:
	// this is the front of the linked list.
	// front = head
	// back = tail
	Node* head;

	// keep track of the number of nodes in the linked list
	int number_of_nodes;

public:
	// Constructors for linked list
	LinkedList();

	// create a linked list from a given array of values
	LinkedList(int* array_of_values, int size);

	// create a linked list randomly
	LinkedList(int seed, int num_of_nodes, int max_value);

	// destructor
	~LinkedList();


	// determine if the linked list is empty
	bool is_empty();

	// determine the number of elements in the linked list
	int length();

	// traverse the linked list and return a pointer to that node
	// find a node with the given value
	Node find(int value);

	// print the values in the linked list
	void print();

	// insert at the given position. Return an object to the head pointer
	Node insert(int value, int position);

	// append at the end (after the last element)
	Node push_back(int value);

	// append at the front (position = 0, before head)
	Node push_front(int value);


	// delete a node with the given value
	void delete_(int value);

	// delete (pop) the element at the end
	void pop_back();

	// delete (pop) the element at the front (the head)
	void pop_front();

};


#endif