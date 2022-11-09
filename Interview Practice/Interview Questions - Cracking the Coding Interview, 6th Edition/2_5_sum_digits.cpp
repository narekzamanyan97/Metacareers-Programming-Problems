#include <iostream>
#include "../../Data Structures - Implementations/Linked List (Double)/LinkedList.cpp"
using namespace std;

LinkedList sum_digits(LinkedList linked_list_1, LinkedList linked_list_2);

int main() {
	int seed;
	do {
		cout << "Enter a seed, enter -1 to exit: " << endl;
		cin >> seed;

		if(seed != -1) {

			LinkedList linked_list_1 = LinkedList(seed, 8, 9);

			cout << "Enter the second seed, enter -1 to exit: " << endl;
			cin >> seed;

			if(seed != -1) {
				LinkedList linked_list_2 = LinkedList(seed, 4, 9);
				linked_list_1.print();
				linked_list_2.print();
				LinkedList sum = sum_digits(linked_list_1, linked_list_2);
		
				sum.print();			
				cout << "after print" << endl;
			}
		}
		cout << "888" << endl;
	} while (seed != -1);

	return 0;
}

// sum two numbers represented by linked lists, where digits are stored in
//		reverse order. e.g. 264 = 4 --> 6 --> 2
// @parameters:
//		linked_list_1/2 = the numbers to add
LinkedList sum_digits(LinkedList linked_list_1, LinkedList linked_list_2) {
	// iterators for the linked lists
	Node* iterator_1 = linked_list_1.begin();
	Node* iterator_2 = linked_list_2.begin();

	// a new linked list that will store the digits for the sum
	LinkedList sum;

	// will hold the sum of the digits
	int sum_of_digits;

	// stores the least significant digit in case sum_of_digits > 9
	int least_significant;

	// stores the carry
	bool carry = false;

	// iterate through the first linked list
	while(iterator_1 != NULL || iterator_2 != NULL) {
		if(iterator_1 != NULL && iterator_2 != NULL) {
			// sum the digits
			sum_of_digits = iterator_1->value + iterator_2->value;

			// increment the iterators as none of them is NULL
			iterator_1 = iterator_1->next;
			iterator_2 = iterator_2->next;	
		}
		else if(iterator_1 != NULL && iterator_2 == NULL) {
			// the sum is just the value of iterator 1
			sum_of_digits = iterator_1->value;

			// increment iterator_1 only (the other one is NULL)
			iterator_1 = iterator_1->next;
		}
		else {
			// the sum is just the value of iterator 2
			sum_of_digits = iterator_2->value;
			
			// increment iterator_2 only (the other one is NULL)
			iterator_2 = iterator_2->next;
		}

		// add the carry to the sum of digits if it exists
		if(carry) {
			sum_of_digits++;
		}

		// no carry after adding the previous carry
		if(sum_of_digits < 10) {			
			// just add the digit sum to the linked list
			sum.add_last(sum_of_digits);
			// set carry false for the next iteration
			carry = false;
		}
		else {
			// subtract 10 from the sum to find what to add to the sum
			//		linked list 
			least_significant = sum_of_digits - 10;

			// append the least significant digit to the sum linked
			//		list
			sum.add_last(least_significant);

			// set carry true for the next iteration
			carry = true;
		}
	}

	// if there was a carry left over, add 1 to the end of the sum linked 
	//		list
	if(carry) {
		sum.add_last(1);
	}

	return sum;
}


// 6841
// 8959
//      	       1
// 1 -> 4 -> 8 -> 6
// 9 -> 5 -> 9 -> 8
// ----------------
// 0 -> 0 -> 8 -> 5 -> 1

// 2568413
//    8959
//      	       1
// 2 -> 5 -> 3 -> 1 -> 4 -> 8 -> 6
// 9 -> 5 -> 9 -> 8
// ----------------
// 0 -> 0 -> 8 -> 5 -> 1