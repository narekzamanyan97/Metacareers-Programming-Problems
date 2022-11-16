#include <iostream>
#include "../../Data Structures - Implementations/Linked List (Double)/LinkedList.cpp"
#include <ctime>
using namespace std;

LinkedList sum_digits(LinkedList linked_list_1, LinkedList linked_list_2);
// !!! make all the NULL to nullptr
// !!! override assignment operator
LinkedList revert(Node* iterator);

LinkedList sum_digits_reverse(LinkedList linked_list_1, LinkedList linked_list_2);

LinkedList sum_digits_recursive(Node* iterator_1, Node* iterator_2, bool carry = false);

int main() {
	int seed;
	LinkedList sum;

	do {
		cout << "Enter any digit to continue. Enter -1 to exit: " << endl;
		cin >> seed;

		if(seed != -1) {
			//////////////////////////////////////////////////////////////////
			//					Testing sum_digits()
			// LinkedList linked_list_1 = LinkedList(-1, 8, 9);
			// LinkedList linked_list_2 = LinkedList(-1, 4, 9);

			// linked_list_1.print();
			// linked_list_2.print();


			// sum = sum_digits(linked_list_1, linked_list_2);
			
			// sum.print();	
			// cout << "hello" << endl;
			// //////////////////////////////////////////////////////////////////
			//					Testing sum_digits_reverse()
			// LinkedList linked_list_1 = LinkedList(-1, 4, 9);
			// LinkedList linked_list_2 = LinkedList(-1, 4, 9);
			// linked_list_1.print();
			// cout << "+" << endl;
			// linked_list_2.print();
			
			// LinkedList sum = LinkedList();
			
			// sum = sum_digits_reverse(linked_list_1, linked_list_2);
			// cout << "=" << endl;
			// sum.print();
			// //////////////////////////////////////////////////////////////////
			//					Testing sum_digits_recursive()
			LinkedList linked_list_1 = LinkedList(-1, 4, 9);
			LinkedList linked_list_2 = LinkedList(-1, 4, 9);
			linked_list_1.print();
			cout << "+" << endl;
			linked_list_2.print();
			
			LinkedList sum = LinkedList();
			
			sum = sum_digits_recursive(linked_list_1.begin(), linked_list_2.begin());
			cout << "=" << endl;
			sum.print();
		}
	} while (seed != -1);
	return 0;
}

// sum two numbers represented by linked lists, where digits are stored in
//		reverse order. e.g. 264 = 4 --> 6 --> 2
// @parameters:
//		linked_list_1/2 = the numbers to add
// @return:
//		an linked list object representing the sum 
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
	while(iterator_1 != nullptr || iterator_2 != nullptr) {
		if(iterator_1 != nullptr && iterator_2 != nullptr) {
			// sum the digits
			sum_of_digits = iterator_1->value + iterator_2->value;

			// increment the iterators as none of them is nullptr
			iterator_1 = iterator_1->next;
			iterator_2 = iterator_2->next;	
		}
		else if(iterator_1 != nullptr && iterator_2 == nullptr) {
			// the sum is just the value of iterator 1
			sum_of_digits = iterator_1->value;

			// increment iterator_1 only (the other one is nullptr)
			iterator_1 = iterator_1->next;
		}
		else {
			// the sum is just the value of iterator 2
			sum_of_digits = iterator_2->value;
			
			// increment iterator_2 only (the other one is nullptr)
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

// // recursive implementation of the reverse case, where the head of the list is the
// //		most significant digit, and the tail is the least significant digit.
// // @parameters:
// //		sum = a reference parameter that will be changed as we recurse
// //		number_1/number_2 = pointers to LinkedList Nodes
// // @return:
// //		carry of the sum of the previous digits
// // ??? how do we recurse and add the appropriate digits when the numbers have
// //		different number of digits?
// void sum_digits(LinkedList& sum, Node* iterator_1, Node* iterator_2) {
// 	// !!! use next and then check for nullptr
// 	// none of them is nullptr
// 	if(iterator_1 != nullptr && iterator_2 != nullptr) {
// 		// if next node exists for both linked lists, recurse to the next of both
// 		if(iterator_1->next != nullptr && iterator_2->next != nullptr) {
// 			// recurse to the next (less significant) digit of both lists
// 			int carry = sum_digits(sum, iterator_1->next, iterator_2->next);
// 		}
// 		// iterator_2 is the last node of list 2
// 		else if(iterator_1->next != nullptr) {
// 			// recurse to the next (less significant) digit of the first list
// 			int carry = sum_digits(sum, iterator_1->next, iterator_2);
// 		}
// 		// iterator_1 is the last node of list 1
// 		else if(iterator_2->next != nullptr) {
// 			// recurse to the next (less significant) digit of the second list
// 			int carry = sum_digits(sum, iterator_1, iterator_2->next);
// 		}

// 		// base case. both iterators point to the last nodes
// 		else {

// 		}
// 	}
// 	// if either of the iterators (and therefore the linked lists) is empty,
// 	//		do not change sum

// }

// the recursive version of sum_digits. 
// Note: 912 is represented as 2 --> 1 --> 9
// Note: 3914 is represented as 4 --> 1 --> 9 --> 3
// @parameters:
//		linked_list_1/2 = linked lists representing the numbers to add
//		carry = a boolean that is used to pass the carry as we recurse to the most
//			significant digit
// @return:
//		linked list representing the sum so far. The last one returned will be
//			the total sum
LinkedList sum_digits_recursive(Node* iterator_1, Node* iterator_2, bool carry) {
	if(iterator_1 != nullptr || iterator_2 != nullptr) {
		// values for both iterators
		int value_1 = 0;
		int value_2 = 0;

		int digit_sum;

		// if the iterator is not nullptr, reset its corresponding value variable
		if(iterator_1 != nullptr) {
			value_1 = iterator_1->value;

			// also, move the iterator for recursion later 
			iterator_1 = iterator_1->next;
		}
		if(iterator_2 != nullptr) {
			value_2 = iterator_2->value;

			// also, move the iterator for recursion later 
			iterator_2 = iterator_2->next;
		}


		////////////////////////////////////////////////////////////////////////
		// 			calculate the sum using the carry
		// sum the two digits
		if(carry) {
			// add extra 1 if there is a carry from the previous call
			digit_sum = value_1 + value_2 + 1;
		}
		else {
			digit_sum = value_1 + value_2;
		}

		// set carry to false
		carry = false;

		// if the digit_sum is > 10, then there is carry. reset digit_sum to
		//		a single digit by subtracting by 10
		if(digit_sum >= 10) {
			digit_sum = digit_sum - 10;
			// reset carry to true
			carry = true;
		}

		LinkedList sum = LinkedList();




		////////////////////////////////////////////////////////////////////////
		// 			recurse
		sum = sum_digits_recursive(iterator_1, iterator_2, carry);
		
		////////////////////////////////////////////////////////////////////////
		// 			add to first the calculated digit_sum
		sum.add_first(digit_sum);

		////////////////////////////////////////////////////////////////////////
		// 			return the sum
		return sum;

	}
	// base case: 
	// both iterators are nullptr
	else {
		// return an empty linked list
		LinkedList sum = LinkedList();

		// if carry is 1, append 1 to the list before returning
		if(carry) {
			sum.add_first(1);
		}
		
		return sum;
		// throw std::exception("One or both of the linked lists is empty.");
	}
}

// approach: revert both lists by recursion and apply the original solution
// @parameters:
//		linked_list_1/2 = linked lists representing the numbers to add
LinkedList sum_digits_reverse(LinkedList linked_list_1, LinkedList linked_list_2) {
	// revert the input linked lists
	linked_list_1 = revert(linked_list_1.begin());
	linked_list_2 = revert(linked_list_2.begin());

	// call the sum_digits on the reverted lists
	LinkedList sum_reverse = sum_digits(linked_list_1, linked_list_2);
	// revert the sum_reverse
	sum_reverse = revert(sum_reverse.begin());

	// return the sum_reverse
	return sum_reverse;
}

// 7, 30, 71, 95, 109

// reverts the list with the given iterator, such that the list becomes linked 
//		from tail to head.
// @parameters:
//		iterator = a pointer to a node (the head at the begining) of the list to
//				be reverted
LinkedList revert(Node* iterator) {
	// make sure iterator is not null.
	if(iterator != nullptr) {
		// base case: iterator points to the last node of the list
		if(iterator->next == nullptr) {
			// declare a linked list
			LinkedList reverse;

			// revert the node
			reverse.add_last(iterator->value);
			
			return reverse;
		}
		else {
			// declare a linked list
			LinkedList reverse;

			// recurse to the next node
			reverse = revert(iterator->next);

			// add the current node at the end of the list
			reverse.add_last(iterator->value);
			return reverse;
		}
	}


}