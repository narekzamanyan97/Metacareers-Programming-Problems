#include <iostream>
#include "../../Data Structures - Implementations/Linked List (Double)/LinkedList.cpp"
#include <ctime>
using namespace std;


bool is_palindrome(LinkedList string);
int revert(LinkedList& string, Node* iterator);

int main() {
	int seed;

	do {
		cout << "Enter any digit to continue. Enter -1 to exit: " << endl;
		cin >> seed;

		if(seed != -1) {
			// //////////////////////////////////////////////////////////////////
			//					Testing is_palindrome(LinkedList string)
			LinkedList string = LinkedList(-1, 39, 9);
			
			is_palindrome(string);		
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
	cout << length << endl;

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
	if(iterator != NULL) {
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

