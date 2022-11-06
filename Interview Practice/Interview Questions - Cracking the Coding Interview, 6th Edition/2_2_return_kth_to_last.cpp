#include <iostream>
#include "../../Data Structures - Implementations/Linked List (Double)/LinkedList.cpp"
using namespace std;

int return_kth_to_last(LinkedList linked_list, int k);

int return_kth_to_last_recursively(Node* iterator, int& k, int counter);

// pair<int, int> return_kth_to_last_recursively(Node* iterator, int k);

int main() {
	LinkedList linked_list = LinkedList(99, 22, 50);

	linked_list.print();

	int k;

	do {
		cout << "Enter the index of the element (from the end) to search: " << endl;
		cin >> k;

		if(k != -1) {
			int kth_to_last = return_kth_to_last_recursively(linked_list.begin(), k, 0);
			cout << kth_to_last << endl;					
		}

	} while (k != -1);

	return 0;
}

// do not use the size of the list
// @parameters:
//		linked_list = the given linked list
//		k = the index starting from the end of the list. 0 <= k < size of the list
// @return:
//		the value of the kth to last node
int return_kth_to_last(LinkedList linked_list, int k) {
	// traverse the list twice
	// in the first traversal, count the number of elements in the list
	Node* iterator = linked_list.begin();

	// keep track of the size of the list
	int size_of_list = 0;

	// loop through the list once and count its size
	while(iterator != NULL) {
		size_of_list++;

		iterator = iterator->next;
	}	

	// calculate the kth element's index if we start from the beginning
	// both indices start from 0
	int k_from_start = size_of_list - 1 - k;

	// if k_from_start is out of range, throw an out of range error
	if(k_from_start < 0 || k_from_start >= size_of_list) {
		throw std::out_of_range("The position provided is out of range.");
	}
	else {
		// reset the iterator
		iterator = linked_list.begin();

		// used to get to the desired node
		int index = 0;

		while(index != k_from_start) {
			// increment both the index and the iterator
			index++;
			iterator = iterator->next;
		}
		
		// return the value
		return iterator->value;
	}
}

// solve the problem recursively
// @parameters:
// 		iterator = a pointer to a node of the list. we start from the beginning (haed) of
//			the list
//		k = the index (from the end (tail) of the list) passed by reference, so caller 
//			and called functions can keep track of whether the node is found or not
// 		counter = starting from 0, it helps us keep track of the first caller in the 
//			stack. When it is 0, then it is the first recursive call.
// @return:
//		the ultimate value returned is the kth to last value
//		in the process of recursion, there are other values returned as well, that is,
//			the values of nodes that are ahead of the kth to last node.
int return_kth_to_last_recursively(Node* iterator, int& k, int counter) {
	if(iterator != NULL) {
		// base case: the iterator points to the last element
		if(iterator->next == NULL){ 
			// return the value in the last node. 
			// This may not be the final return value.
			return iterator->value;
		}
		else {
			// recurse to the next node
			int value = return_kth_to_last_recursively(iterator->next, k, counter + 1);

			// we have already reached kth to last element. return its value in a 
			//		preceding recursive call. 
			if(k == 0) {
				// Return the value returned in the previous recursive call 
				return value;
			}
			else if(k < 0) {
				// a negative index was provided
				throw std::out_of_range("The index cannot be negative.");
			}
			else {
				// k is still not 0, so the current node is not what we are looking for.
				//		the node we are looking for is to the left of the current node.
				//	decrement k
				k--;
			}
		}
		// !!! if k was too large, it never gets to 0, so throw an error
		if(counter == 0 && k > 0) {
			// we are at the front of the linked list, and k is still > 0, so throw an
			//		out of range error (k was too large)
			throw std::out_of_range("k is larger than the size of the list.");
		}
		else {
			// return the value of the current node
			return iterator->value;
		}
	}

	// the list is empty
	else {
		throw std::out_of_range("The linked list is empty.");
	}
}


// // solve the problem recursively, returning 2 values from the function enclosed in a 
// //		pair.
// //  The first value is the value of k, the second value is the node's value 
// // @parameters:
// // 		iterator = a pointer to a node of the list. we start from the beginning (haed) of
// //			the list
// //		k = the index (from the end (tail) of the list)
// // @return:
// //		the ultimate value returned is !!!
// pair<int, int> return_kth_to_last_recursively(Node* iterator, int k) {
// 	if(iterator != NULL) {
// 		// base case: the iterator points to the last element
// 		if(iterator->next == NULL){ 
// 			// return the value in the last node. 
// 			// This may not be the final return value.
// 			return std::make_pair(k, iterator->value);
// 		}
// 		else {
// 			// recurse to the next node
// 			pair<int, int> returned_pair = return_kth_to_last_recursively(iterator->next, k);

// 			// extract the values from the returned pair
// 			int new_k = returned_pair.first
// 			int value = returned_pair.second

// 			// we have already reached kth to last element. return its value in a 
// 			//		preceding recursive call. 
// 			if(k == 0) {
// 				// Return the value returned in the previous recursive call 
// 				return value;
// 			}
// 			else {
// 				// k is still not 0, so the current node is not what we are looking for.
// 				//		the node we are looking for is to the left of the current node.
// 				//	decrement k
// 				k--;

// 				return iterator->value;
// 			}
// 		}
// 	}
// 	// the list is empty
// 	else {
// 		throw std::out_of_range("The linked list is empty.");
// 	}
// }
// Hints: 67, 126