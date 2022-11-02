#include "LinkedList.cpp"

int main() {

	LinkedList linked_list = LinkedList(2, 22, 25);

	Node node;

	int selection;
	int value;
	int position;
	int index;

	do {
		cout << "****************************************" << endl;
		cout << "make a selection: " << endl;
		cout << "0 - print(): " << endl;
		cout << "1 - is_empty(): " << endl;
		cout << "2 - length(): " << endl;
		cout << "3 - find(value): " << endl;
		cout << "4 - insert(value, position): " << endl;
		cout << "5 - add_last(value): " << endl;
		cout << "6 - add_first(value): " << endl;
		cout << "7 - remove_first_occurance(value): " << endl;
		cout << "8 - remove_last_occurance(value): " << endl;
		cout << "9 - remove_first(): " << endl;
		cout << "10 - remove_last(): " << endl;
		cout << "11 - index_of(value): " << endl;
		cout << "12 - last_index_of(value): " << endl;
		cout << "13 - contains(value): " << endl;
		cout << "14 - peek_first(): " << endl;
		cout << "15 - peek_last(): " << endl;
		cout << "16 - remove_at_index(index): " << endl;
		cout << "17 - set(position, value): " << endl;
		cout << "18 - clear(): " << endl;
		cout << "-1 - exit: " << endl;

		cin >> selection;

		switch(selection){
			case 0:
				linked_list.print();
				break;
			case 1:
				if(linked_list.is_empty()) {
					cout << "Empty." << endl;
				}
				else {
					cout << "Not Empty." << endl;
				}

				break;
			case 2:
				cout << "Length is " << linked_list.length() << endl;

				break;

			case 3:
				cout << "Enter a value to find: " << endl;
				cin >> value;

				node = linked_list.find(value);

				cout << "The value found is " << node.value << endl;
				cout << "prev = " << node.previous->value << endl;
				cout << "next = " << node.next->value << endl;

				break;
			case 4:
				cout << "Enter a value to insert: " << endl;
				cin >> value;
				cout << "Enter a position to insert: " << endl;
				cin >> position;

				node = linked_list.insert(value, position);

				cout << "The value inserted is " << node.value << endl;
				cout << "prev = " << node.previous->value << endl;
				cout << "next = " << node.next->value << endl;

				break;
			case 5:
				cout << "Enter value to add last: " << endl;
				cin >> value;

				linked_list.add_last(value);
				break;

			case 6:
				cout << "Enter value to add first: " << endl;
				cin >> value;

				linked_list.add_first(value);
				break;

			case 7:
				cout << "Enter value to remove its first occurance: " << endl;
				cin >> value;

				linked_list.remove_first_occurrence(value);
				break;

			case 8:
				cout << "Enter value to remove its last occurance: " << endl;
				cin >> value;

				linked_list.remove_last_occurrence(value);
				break;

			case 9:
				cout << "Removing first node: " << endl;
				linked_list.remove_first();
				break;

			case 10:
				cout << "Removing last node: " << endl;
				linked_list.remove_last();
				break;

			case 11:
				cout << "Enter value to find its index: " << endl;
				cin >> value;

				index = linked_list.index_of(value);

				cout << "index of " << value << " is " << index << endl;
				break;

			case 12:
				cout << "Enter value to find its last index: " << endl;
				cin >> value;

				index = linked_list.last_index_of(value);
					
				cout << "index of " << value << " is " << index << endl;
				break;

			case 13:
				cout << "Enter a value to see if the list contains it: " << endl;
				cin >> value;

				if(linked_list.contains(value)) {
					cout << "The list contains " << value << endl;
				}
				else {
					cout << "The list does not contain " << value << endl;
				}
				break;

			case 14:
				cout << "Peeking at first node: " << endl;
				node = linked_list.peek_first();

				cout << "value = " << node.value << endl;
				if(node.next != NULL) {
					cout << "next = " << node.next->value << endl;
				}
				else {
					cout << "next node is NULL " << endl;
				}
				break;

			case 15:
				cout << "Peeking at last node: " << endl;
				node = linked_list.peek_last();

				cout << "value = " << node.value << endl;
				if(node.previous != NULL) {
					cout << "previous = " << node.previous->value << endl;
				}
				else {
					cout << "previous node is NULL " << endl;
				}
				break;

			case 16:
				cout << "Enter an index to remove the node at that location: " << endl;
				cin >> index;

				node = linked_list.remove_at_index(index);
				
				cout << "removed " << node.value << endl;
				if(node.next != NULL) {
					cout << "next of removed node = " << node.next->value << endl;
				}
				else {
					cout << "next of removed node is NULL " << endl;
				}
				break;

			case 17:
				cout << "Enter a value to set: " << endl;
				cin >> value;
				cout << "Enter a position to set: " << endl;
				cin >> position;

				node = linked_list.set(value, position);

				cout << "The value set = " << node.value << endl;
				cout << "The position is " << position << endl;
				if(node.next != NULL) {
					// !!! how to know if a function returned an empty object 
					cout << "next of newly set node is " << node.next->value << endl;
				}
				else {
					cout << "next of newly set node is NULL" << endl;
				}
				break;

			case 18:
				// !!! not working
				cout << "Clearing the list" << endl;

				linked_list.clear();
				break;

			case -1:
				cout << "Bye!" << endl;
				break;
		}

	} while(selection != -1);

	return 0;
}

