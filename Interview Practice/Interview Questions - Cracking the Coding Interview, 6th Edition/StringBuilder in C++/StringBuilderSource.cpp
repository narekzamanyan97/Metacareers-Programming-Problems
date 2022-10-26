using namespace std;

int main(){
	int selection;

	StringBuilder string_builder = StringBuilder("I am Narek Zamanyan. I am an Applications Programmer at LADWP. I am 180cm tall. I Love Johann Sebastian Bach. I do Judo, and I am a Brown Belt.");
	
	// variables that will be needed for the test
	int offset;
	int index;
	string str;
	bool b;
	int start;
	int end;
	int shift_length;

	do {
		cout << "\n***********************************************" << endl;
		cout << "Select a function to test: " << endl;
		cout << "1 - toString() " << endl;
		cout << "2 - append(string) " << endl;
		cout << "3 - append(char)" << endl;
		cout << "4 - append(bool)" << endl;
		cout << "5 - append(int)" << endl;
		cout << "6 - append(double)" << endl;
		cout << "7 - insert(offset, string)" << endl;
		cout << "8 - insert(offset, char)" << endl;
		cout << "9 - insert(offset, bool)" << endl;
		cout << "10 - insert(offset, int)" << endl;
		cout << "11 - insert(offset, double)" << endl;
		cout << "12 - replace(start, str)" << endl;
		cout << "13 - delete_(start, end)" << endl;
		cout << "14 - reverse()" << endl;
		cout << "15 - ensureCapacity()" << endl;
		cout << "16 - charAt(index)" << endl;
		cout << "17 - length()" << endl;
		cout << "18 - substring(start)" << endl;
		cout << "19 - substring(start, end)" << endl;
		cout << "20 - indexOf(str)" << endl;
		cout << "21 - lastIndexOf(str)" << endl;
		cout << "22 - trimToSize()" << endl;
		cout << "23 - print()" << endl;
		cout << "24 - getCapacity()" << endl;
		cout << "25 - getCharArray()" << endl;
		cout << "26 - shiftRight()" << endl;

		cin >> selection;

		switch(selection) {
			case 1:
				cout << string_builder.toString() << endl;
				
				break;
			case 2:
				cout << "Enter a string to append: " << endl;

				cin.ignore();
				
				getline(cin, str);


				string_builder.append(str);

				break;
			case 7:
				cout << "Enter the offset: " << endl;
				cin >> offset;
				cout << "Enter the string to insert: " << endl;

				cin.ignore();
			
				getline(cin, str);
				string_builder.insert(offset, str);

				break;
			case 12:
				cout << "Enter the start: " << endl;
				cin >> start;
				cout << "Enter the string to replace: " << endl;

				cin.ignore();
			
				getline(cin, str);
				string_builder.replace(start, str);	

				break;

			case 16:
				cout << "Enter the index: " << endl;
				cin >> index;

				cout << "char at " << index << " = " << string_builder.charAt(index) << endl;

				break;

			case 17:
				cout << "length is " << string_builder.length() << endl;

				break;

			case 23:
				string_builder.print();

				break;

			case 24:
				cout << "capacity is " << string_builder.getCapacity() << endl;

				break;
			case 26:
				cout << "Enter shift offset " << endl;
				cin >> offset;

				cout << "Enter shift length" << endl;
				cin >> shift_length;

				string_builder.helper_shift_substring_right(offset, shift_length);


				break;
		}

	} while (selection != -2);
	

	return 0;
}