#include "Heap.cpp"


int main() {
	int selection = -1;
	int index;
	int value;


	int arrayInt[15] = {0, 1, 2};//, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
	int arrayInt2[15] = {10, 11, 12};//, 13, 14, 15, 16, 17, 18, 19, 110, 111, 112, 113, 114};

	Heap<int> heap = Heap<int>(arrayInt, 3);
	Heap<int> heap2 = Heap<int>(arrayInt2, 3);
	
	do {
		cout << "0 - print()" << endl;
		cout << "1 - getLeftChildIndex(index)" << endl;
		cout << "2 - getRightChildIndex(index)" << endl;
		cout << "3 - getParentIndex(index)" << endl;
		cout << "4 - isLeaf(index)" << endl;
		cout << "5 - hasRightChild(index)" << endl;
		cout << "6 - getValue(index)" << endl;
		cout << "7 - setValue(index, newValue)" << endl;
		cout << "8 - getNumberOfNodes()" << endl;
		cout << "9 - getHeight()" << endl;
		cout << "10 - peekTop(T)" << endl;
		cout << "11 - add(newValue)" << endl;
		cout << "12 - remove(index)" << endl;
		cout << "13 - clear()" << endl;
		cout << "14 - merge()" << endl;
		cout << "15 - extend()" << endl;
		cout << "-1 - exit" << endl;
		
		cin >> selection;

		switch(selection) {
			case 0:
				heap.print();

				heap2.print();
				break;
			case 1:
				cout << "Enter an index: " << endl;
				cin >> index;

				cout << "left child index = " << heap.getLeftChildIndex(index) << endl;
				
				break;
			case 2:
				cout << "Enter an index: " << endl;
				cin >> index;

				cout << "right child index = " << heap.getRightChildIndex(index) << endl;
				
				break;
			case 3:
				cout << "Enter an index: " << endl;
				cin >> index;

				cout << "parent index = " << heap.getParentIndex(index) << endl;
				
				break;
			case 4:
				cout << "Enter an index: " << endl;
				cin >> index;

				if(heap.isLeaf(index)) {
					cout << heap.getValue(index) << "(" << index << ") is a leaf." << endl;
				}
				else {
					cout << heap.getValue(index) << "(" << index << ") is NOT a leaf." << endl;
				}
				
				break;
			case 5:
				cout << "Enter an index: " << endl;
				cin >> index;

				if(heap.hasRightChild(index)) {
					cout << heap.getValue(index) << "(" << index << ") has a right child." << endl;
				}
				else {
					cout << heap.getValue(index) << "(" << index << ") does not have a right child." << endl;
				}
				break;
			case 6:
				cout << "Enter an index: " << endl;

				cin >> index;

				cout << "Value at " << index << " is " << heap.getValue(index) << endl;

				break;
			case 7:
				cout << "Enter an index: " << endl;

				cin >> index;

				cout << "Enter a value: " << endl;

				cin >> value;

				heap.setValue(index, value);

				cout << "Value at " << index << " is now " << heap.getValue(index) << endl;

				break;
			case 8:
				cout << "number of nodes = " << heap.getNumberOfNodes() << endl;
				break;
			case 9:
				cout << "height = " << heap.getHeight() << endl;
				break;
			case 10:
				cout << "peek top: " << heap.peekTop() << endl;
				break;
			case 11:
				cout << "Enter a value to add: " << endl;
				cin >> value;

				heap.add(value);

				break;
			case 12:
				cout << "Enter an index to remove:" << endl;

				cin >> index;

				heap.remove(index);

				break;
			case 13:
				heap.clear();
				break;
			case 14:
				cout << "heap2 before merge: " << endl;
				heap2.print();
				heap.merge(heap2);
				cout << "heap2 after merge: " << endl;
				heap2.print();
				break;
			case 15:
				heap.extend();
				break;
			case -1:
				cout << "Bye! Thaaank you!" << endl;
				break;
		} 
	}while(selection != -1);




	return 0;
}