#include <iostream>
#include "../../Data Structures - Implementations/Linked List (Double)/LinkedList.cpp"
#include <ctime>
using namespace std;


// Problem:
// Intersection: Given two (singly) linked lists, determine if the two lists intersect. Return the intersecting
// node. Note that the intersection is defined based on reference, not value. That is, if the kth
// node of the first linked list is the exact same node (by reference) as the jth node of the second
// linked list, then they are intersecting.
// Hints:#20, #45, #55, #65, #76, #93, #111,

int main() {

	return 0;
}


// helper function to count the number of nodes in a linked list
// @parameters:
//		linked_list = a linked list object whose number of nodes we need to count
// @return:
//		length = the length of the given linked list
int count_length(LinkedList linked_list) {
	// declare an iterator
	Node* iterator = linked_list.begin();

	// declare the running total number of elements of the list
	int length = 0;

	// loop over all the nodes of the linked list
	while(iterator != nullptr) {
		// increment the length
		length++;

		// move on to the next node
		iterator = iterator->next;
	}

	// return the length
	return length;
}


// @parameters:
//		linked_list_1/2 = linked list objects, the intersection node of which we want to
//			find
//		length_1/2 = the number of nodes of lists 1 and 2, respectively
// @return
// 		The intersection node
//		null if the notes don't intersect
Node* intersection(LinkedList linked_list_1, LinkedList linked_list_2, int lnegth_1, int length_2) {
	// for the longer linked list, skip ahead to the node to align with the shorter list,
	//		so that both iterators arrive at the last node of each list simultaneously.
	
}

// recursive implementation to search for the common node (intersection) from the tail
//		of the linked list 
// base case is when the iterators reach the last nodes of each linked list
// @parameters:
// @return:
std::pair<bool, Node*> intersection(Node* iterator_1, Node* iterator_2) {

}