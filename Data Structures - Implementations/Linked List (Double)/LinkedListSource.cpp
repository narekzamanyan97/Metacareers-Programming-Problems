#include "LinkedList.cpp"

int main() {

	LinkedList linked_list = LinkedList(2, 10, 25);

	int selection;

	do {
		cout << "****************************************" << endl;
		cout << "make a selection: " << endl;
		cout << "0 - print(): " << endl;
		cout << "1 - is_empty(): " << endl;
		cout << "2 - length(): " << endl;
		cout << "3 - find(value): " << endl;
		cout << "4 - insert(value, position): " << endl;
		cout << "5 - push_back(value): " << endl;
		cout << "6 - push_front(value): " << endl;
		cout << "7 - delete_(value): " << endl;
		cout << "8 - pop_back(): " << endl;
		cout << "9 - pop_front(): " << endl;
		cout << "-1 - exit: " << endl;


		cin >> selection;
		
		switch(selection){
			case 0:
				linked_list.print();
				break;
		}

	} while(selection != -1);

	return 0;
}

