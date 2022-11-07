#include <iostream>
#include "../../Data Structures - Implementations/Linked List (Double)/LinkedList.cpp"
#include <map>
using namespace std;

void remove_dups(LinkedList& linked_list);

void remove_dups_without_temp_buff(LinkedList& linked_list);

int main() {
	LinkedList linked_list = LinkedList(12, 22, 50);

	linked_list.print();

	remove_dups_without_temp_buff(linked_list);

	linked_list.print();

	return 0;
}

// using a hash table
void remove_dups(LinkedList& linked_list) {
	// use a hash map
	map<int, bool> encountered_values;

	// traverse the linked list and populate the map
	int list_size = linked_list.length();

	Node* iterator = linked_list.begin();

	// loop through all the elements in the list
	while(iterator != NULL) {
		// if the value is not in the map, add it to the map, with the key
		//		being the value, and the value being true
		if(encountered_values.find(iterator->value) == encountered_values.end()) {
			cout << iterator->value << endl;
			encountered_values[iterator->value] = true;
			iterator = iterator->next;
		}
		else {
			cout << iterator->value << "************************" << endl;
			iterator = linked_list.remove(iterator);
		}
	}

}

// using no hash table (time complexity is O(n^2))
void remove_dups_without_temp_buff(LinkedList& linked_list) {
	// have 2 pointers (iterators)
	Node* iterator_1 = linked_list.begin();
	Node* iterator_2 = linked_list.begin();

	// iterator_2 should always be at least 1 ahead of iterator_1
	if(iterator_1 != NULL) {
		iterator_2 = iterator_1->next;
	}


	// loop through the list and compare the node values pointed to by iterators 1 and 2
	// if the values are the same, remove the node pointed to by iterator 2
	while(iterator_1 != NULL) {
		// reset iterator_2 to start from the next node of iterator 1
		iterator_2 = iterator_1->next;

		// loop through the list with the second iterator
		while(iterator_2 != NULL) {
			// compare the two values
			if(iterator_1->value == iterator_2->value) {
				// remove iterator 2, which will also return a pointer pointing to
				//		the next node of iterator 2
				cout << iterator_2->value << "*******************" << endl;
				iterator_2 = linked_list.remove(iterator_2);
			}
			else {
				// increment iterator 2
				iterator_2 = iterator_2->next;
			}
		}

		// increment iterator 1
		iterator_1 = iterator_1->next;
	} 
}


