#include "HashTable.cpp"

#include <string>
#include <map>
using namespace std;

int main() {
	int selection = -1;
	int value;
	int hash;

	HashTable<int> dict = HashTable<int>();

	do {
		cout << "0 - print." << endl;
		cout << "1 - hashFunction(T)." << endl;
		cout << "2 - insert(T)." << endl;
		cout << "3 - search(T)." << endl;
		cout << "4 - delete_(T)." << endl;
		
		cin >> selection;

		switch(selection) {
			case 0:
				dict.print();
				break;
			case 1:
				cout << "Enter a value: " << endl;
				cin >> value;

				hash = dict.hashFunction(value);
				
				cout << "hash = " << hash << endl;
				break;
			case 2:
				cout << "Enter a value to insert: " << endl;

				cin >> value;

				dict.insert(value);

				break;
			case -1:
				cout << "Bye! Thaaank you!" << endl;
				break;
		} 
	}while(selection != -1);


	return 0;
}