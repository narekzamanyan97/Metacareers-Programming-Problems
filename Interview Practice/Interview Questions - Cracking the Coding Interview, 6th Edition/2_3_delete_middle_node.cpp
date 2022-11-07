#include <iostream>
#include "../../Data Structures - Implementations/Linked List (Double)/LinkedList.cpp"
using namespace std;


int main() {
	LinkedList linked_list = LinkedList(99, 22, 50);

	linked_list.print();

	int k;

	do {
		cout << "Enter the index of the element (from the end) to search: " << endl;
		cin >> k;

		if(k != -1) {
			// approach 1
			// int kth_to_last = return_kth_to_last_recursively(linked_list.begin(), k);
			// approach 2
			// int kth_to_last = return_kth_to_last_recursively(linked_list.begin(), k);
			// approach 3
			// std::pair<int, int> kth_to_last = return_kth_to_last_recursively_pair(linked_list.begin(), k);
			// approach 4
			int kth_to_last = return_kth_to_last_two_pointers(linked_list.begin(), k);
			cout << kth_to_last << endl;					
		}

	} while (k != -1);

	return 0;
}


