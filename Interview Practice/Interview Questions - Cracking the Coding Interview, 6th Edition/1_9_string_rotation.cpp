#include <string>
#include <iostream>
using namespace std;

bool isSubstring(string str_1, string str_2);
bool isRotation(string str_1, string str_2);

int main() {
	string str_1;
	string str_2;

	cout << "Enter the first string: " << endl;
	getline(cin, str_1);

	cout << "Enter the second string: " << endl;
	getline(cin, str_2);

	if(isRotation(str_1, str_2)) {
		cout << "Yes" << endl;
	}
	else {
		cout << "No" << endl;
	}
	return 0;
}

// determine if str_2 is a rotation of str_1 (or vice-versa)
// @parameters:
//		str_1 = the first string
//		str_2 = the second string
// @return:
//		true = if str_2 is a rotation of str_1
bool isRotation(string str_1, string str_2) {
	// if the strings have different sizes, return false immediately
	if(str_1.size() != str_2.size()) {
		return false;
	}
	else {
		// find the splitting point
		ffiiiffffi
		ffffi ffiii

		waterb aatlewaterbottle
		attlewaterbottle waterb

		waterbaa tlewaterbottle
		attlewaterbot tlewaterb

	}
}

// determine if str_2 is a substring of str_1
// @parameters:
//		str_1 = the first string
//		str_2 = the second string
// @return:
//		true = if str_2 is a substring of str_1
bool isSubstring(string str_1, string str_2) {
	// size of the first string
	int size_1 = str_1.size();
	// size of the second string
	int size_2 = str_2.size();

	// the index for the first string
	int index_1 = 0;

	// the index for the second string
	int index_2 = 0; 

	// keep track of the number of char matches. if it is equal to the size of the string,
	// 		then we have a match
	int num_of_matches = 0;

	// compare the lowercase chars instead of the actual chars, because, e.g. N = n
	char lowercase_1;
	char lowercase_2;

	// if str_2 is longer than str_1, no need to proceed. return false.
	if(size_2 > size_1) {
		return false;
	}
	else{ 
		// iterate through the first string
		while(index_1 < size_1) {
			// set the lowercase chars
			lowercase_1 = tolower(str_1[index_1]);
			lowercase_2 = tolower(str_2[index_2]);
			// looking for a match
			while(index_1 < size_1
					&& index_2 < size_2
					&& lowercase_1 == lowercase_2) {
				// increment number of char matches by one
				num_of_matches++;

				// increment both index and str_index
				index_1++;
				index_2++;

				// reset the lowercase characters to be compared in the loop conditional
				//		statement
				lowercase_1 = tolower(str_1[index_1]);
				lowercase_2 = tolower(str_2[index_2]);
			}

			// if all the chars matched, return true
			if(num_of_matches == size_2) {
				return true;
			}
			// otherwise, reset the str_index and num_of_matches to 0. 
			//		Also, increment the index
			else {
				// reset str_index
				index_2 = 0;

				// only increment index here if there has not been any match in the inner
				//		loop
				index_1 = index_1 - num_of_matches + 1;

				// reset the number of char matches
				num_of_matches = 0;
			}
		}
	}

	return false;
}
