#include "HashTable.cpp"

#include <string>
#include <map>
using namespace std;

int main() {
	int selection = -1;
	string value;
	int hash;



	string v1 = "narek";
	string& ref = v1;

	cout << "ref  = " << ref << endl;
	cout << "&ref = " << &ref << endl;
	cout << "&v1  = " << &v1 << endl;

	// string string_ = (std::is_fundamental_v<string> == 1 ? "Yes" : "No");
	// string string_ = (std::is_same_v<std::remove_cv_t<std::remove_reference_t<string>>, string>) == 1 ? "Yes" : "No";

	// cout << "hash1 = " << std::hash<string>{}("Narek");
	// cout << "hash1 = " << std::hash<string>{}("Narek");
	// cout << "hash1 = " << std::hash<string>{}("Narek");
	// cout << "hash1 = " << std::hash<string>{}("Ray");
	// cout << "hash1 = " << std::hash<string>{}("Manzarek");

	HashTable<string> dict = HashTable<string>();
	// HashTable<int> dict2 = HashTable<int>(20);


	// double d1 = 1.1111;
	// double d2 = 1.111123;
	// double d3 = 1.113;

	// float f1 = 1.1111;
	// float f2 = 1.1111;
	// float f3 = 1.113;

	// HashTable<double> hash_d = HashTable<double>();

	// cout << "d1: " << hash_d.hashFunction(d1) << endl;
	// cout << "d2: " << hash_d.hashFunction(d2) << endl;
	// cout << "d3: " << hash_d.hashFunction(d3) << endl;
	// cout << "f1: " << hash_d.hashFunction(f1) << endl;
	// cout << "f2: " << hash_d.hashFunction(f2) << endl;
	// cout << "f3: " << hash_d.hashFunction(f3) << endl;

	HashTable<LinkedList<int>> hash_o = HashTable<LinkedList<int>>();

	LinkedList<int> ll1 = LinkedList<int>();
	LinkedList<int> ll2 = LinkedList<int>();
	LinkedList<int> ll3 = LinkedList<int>();
	LinkedList<int> ll4 = LinkedList<int>();

	cout << "ll2: " << hash_o.hashFunction(ll2) << endl;
	cout << "ll1: " << hash_o.hashFunction(ll1) << endl;
	cout << "ll3: " << hash_o.hashFunction(ll3) << endl;
	cout << "ll4: " << hash_o.hashFunction(ll4) << endl;




	dict.hashFunction(v1);
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