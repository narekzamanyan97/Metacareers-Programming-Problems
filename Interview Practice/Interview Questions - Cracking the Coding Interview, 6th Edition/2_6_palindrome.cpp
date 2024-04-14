#include <iostream>
#include "../../Data Structures - Implementations/Linked List (Double)/LinkedList.cpp"
#include <ctime>
using namespace std;


//////////////////////////////////////////////////////////////////////////////
//				Approach 1: reverting the string (list) recursively and then
//					checking for palindrome 
bool is_palindrome(LinkedList string);
int revert(LinkedList& string, Node* iterator);

//////////////////////////////////////////////////////////////////////////////
//				Approach 2: Assuming length() of string is known. Recursive
//					using hint 29
pair<bool, Node*> is_palindrome(Node* left_it, Node* right_it, int& counter, int length);

//////////////////////////////////////////////////////////////////////////////
//				Approach 3: Assuming length() of string is known. Recursive
//					using hint 61
pair<bool, Node*> is_palindrome(Node* left_it, int& counter, int length);


int main() {
	int seed;

	int counter = 0;

	do {
		cout << "Enter any digit to continue. Enter -1 to exit: " << endl;
		cin >> seed;

		if(seed != -1) {
			// //////////////////////////////////////////////////////////////////
			//					Testing is_palindrome(LinkedList string)
			LinkedList string = LinkedList();
			// string.add_last(9);
			// string.add_last(1);
			// string.add_last(4);
			// string.add_last(2);
			// string.add_last(7);
			// string.add_last(0);
			// string.add_last(9);

			// string.add_last(8);

			// string.add_last(9);
			// string.add_last(0);
			// string.add_last(7);
			// string.add_last(2);
			// string.add_last(4);
			// string.add_last(1);
			// string.add_last(9);

			// reset the counter to 0 for the next call
			counter = 0;

			string.print();

			pair<bool, Node*> is_pal = is_palindrome(string.begin(), counter, string.length());
			if(is_pal.first) {
				cout << "palindrome" << endl;
			}		
			else {
				cout << "not a palindrome" << endl;
			}
		}
	} while (seed != -1);
	return 0;
}


// determine if the given linked list of chars is a palindrome
// @parameters:
//		string = the linked list to determine whether it is a palindrome or not
// @return:
//		true if te given string linked list is a palindrome, false otherwise
bool is_palindrome(LinkedList string) {
	string.print();

	// declare the reverted string
	LinkedList string_reverse = LinkedList();

	// revert the string and place the result into string_reverse and get the 
	//		length of the string
	int length = revert(string_reverse, string.begin());

	string_reverse.print();


	// loop through the lists, stop at the half
	int counter = 0;

	// initialize iterators to test for palindrome
	Node* iterator_1 = string.begin();
	Node* iterator_2 = string_reverse.begin();


	while(counter <  length/2) {
		// if the symmetric node values from both ends are the same, increment the
		//		counter
		if(iterator_1->value == iterator_2->value) {
			// increment the counter by 1
			counter++;
		
			// increment the iterators
			iterator_1 = iterator_1->next;
			iterator_2 = iterator_2->next;
		}
		else {
			// set counter equal to length to end the loop 
			counter = length;
		}

	}

	// return either true or false based on the final of counter
	if(counter == length) {
		return false;
	}
	else {
		return true;
	}

}


// helper function to reverse the string and also get the number of nodes in there
// recursive implementation
// @parameters:
//		string = a reference to a linked list which will eventually contain the
//			reverse of the list passed to the function with its head iterator
//			we begin with an empty string (with no nodes)
//		iterator = an iterator to the linked list that needs to be reverted. begin
//			with the head pointer of the list
// @return:
//		the length of the linked list
int revert(LinkedList& string, Node* iterator) {
	if(iterator != nullptr) {
		// recurse to the next node
		int length = revert(string, iterator->next);

		// add 1 to the length to return
		length++;

		// add the value of the given iterator to the string from the end (tail)
		string.add_last(iterator->value);

		// return the length so far
		return length;
	}
	// base case, stop recursion and return 0
	else {
		return 0;
	}
}


//////////////////////////////////////////////////////////////////////////////
//				Approach 2: Assuming length() of string is known. Recursive
//					using hint #29
// the base case is the last node
// @parameters:
//		left_it = the head of the list. We keep this the same throughout the
//			recursion. When it is time, we move to the left
//		right_it = the iterator in the right half. starts from the right end 
//			(tail) of the list
//		counter = keeps track of the number of opposite nodes being compared. 
// 		lenght = the length of the list. cannot be changed
// @return:
//		a pair of bool and iterator
//			pair.first:		
//				true if the list is a palindrome
//				false otherwise
//		iterator
//			a pointer to the left iterator for the current check
pair<bool, Node*> is_palindrome(Node* left_it, Node* right_it, int& counter, int length) {
	// move the right_it to the right until the end (tail) is reached
	if(right_it != nullptr) {
		// recurse, moving the right iterator to the next node
		pair<bool, Node*> is_pal_and_left = is_palindrome(left_it, right_it->next, counter, length);

		// declare current left node
		Node* current_left_it = is_pal_and_left.second;
		
		// if the previous recursive call returned false, just return false.
		//		otherwise, if counter < length/2, continue the check
		if(is_pal_and_left.first && counter < length/2) {
			
			// at this point, the right_it and current_left_it are the same length
			// 		away from the mid point of the string. compare
			if(current_left_it->value == right_it->value) {
				cout << current_left_it->value << " == " << right_it->value << endl;
				// increment the current_left_it
				current_left_it = current_left_it->next; 			

				// increment the counter
				counter++;

				return std::make_pair(true, current_left_it);				
			}
			else {
				cout << current_left_it->value << " != " << right_it->value << endl;
				// return false
				return std::make_pair(false, left_it);
			}
		}
		// either reached the middle element or palindrome check failed at some
		// 		point
		else {
			// the check has not failed at some point.
			if(is_pal_and_left.first) {
				// reached the middle element (if there is one), return true
				return std::make_pair(true, left_it);				
			}
			// a check has failed.
			else {
				// if false was returned in the recursive call, then we must return
				//		false
				return std::make_pair(false, left_it);				
			}
		}


	}
	// base case, the right_it has reached the tail of the list. return true
	//		to continue the process
	else {
		return std::make_pair(true, left_it);
	}
}

//////////////////////////////////////////////////////////////////////////////
//				Approach 3: Assuming length() of string is known. Recursive
//					using hint 61
// the base case is the middle node
// @parameters:
//		left_it = a pointer to the node that keeps track of the left iterator
//		counter = keeps track of the number of opposite nodes being compared. 
// 		lenght = the length of the list. cannot be changed
// @return:
//		a pair of bool and iterator
//			pair.first:		
//				true if the list is a palindrome
//				false otherwise
//		iterator
//			a pointer to the iterator on the right half of the linked list. The
//				symmetric pair of the left_it
pair<bool, Node*> is_palindrome(Node* left_it, int& counter, int length){
	// proceed only when the string is not empty
	if(length != 0) {
		// base case 1: counter => length / 2
		if(counter == length / 2) {
			// 		(a) if length is even, return the left_it as the iterator in the 
			//			right half
			if(length % 2 == 0) {
				return std::make_pair(true, left_it);
			}
			//  	(b) if it's odd (there is a single middle node), return the next of
			//			left_it
			//		as the iterator in the right half.
			else {
				return std::make_pair(true, left_it->next);
			}		
		}
		else {
			// recurse
			pair<bool, Node*> is_pal_and_right = is_palindrome(left_it->next, ++counter, length); 
			
			// extract the values from the pair returned from the recursive call
			bool is_pal_so_far = is_pal_and_right.first;
			Node* right_it = is_pal_and_right.second;

			// so far so good. Continue comparing symmetric nodes
			if(is_pal_so_far) {
				// compare the values of symmetric nodes (right and left iterators)
				if(left_it->value == right_it->value) {
					cout << left_it->value << " == " << right_it->value << endl;
					// return the right node of the right iterator and true
					return std::make_pair(true, right_it->next);
				}
				// values are different, so not a palindrome
				else {
					cout << left_it->value << " != " << right_it->value << endl;
					// the second value of the pair does not matter
					return std::make_pair(false, right_it);
				}
			}
			// if the palindrome has failed, retusrn false
			else {
				// no need to compare, just return falsed
				return std::make_pair(false, right_it);
			}
		}	

	}
	else {
		// the string (linked list) is empty, so return true
		return std::make_pair(true, left_it);
	}
}

// hints: 5, 13, 29, 61, 101