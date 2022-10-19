#include <iostream>
#include <string>
using namespace std;

bool is_one_away(string str_1, string str_2);

int main() {
	string str_1;
	string str_2;

	cout << "Enter string 1: Enter -1 to exit " << endl;
	getline(cin, str_1);

	if(str_1 != "-1") {
		cout << "Enter string 2: " << endl;
		getline(cin, str_2);
	}


	while(str_1 != "-1" && str_2 != "-1") {
		if(is_one_away(str_1, str_2)) {
			cout << "One away" << endl;
		}
		else {
			cout << "Not one away" << endl;
		}

		cout << "Enter string 1: Enter -1 to exit. " << endl;
		getline(cin, str_1);

		if(str_1 != "-1") {
			cout << "Enter string 2: Enter -1 to exit. " << endl;
			getline(cin, str_2);
		}
	}

	return 0;
}


// @parameters:
//		str_1 and str_2 = the two strings to compare to see if they are only once 
//			character away from each other. 
// @return:
//		true = if we can get str_1 from str_2 by removing a char from str_1, inserting
//			a char into str_1, or replacing a char from str_1
// 		false = otherwise
bool is_one_away(string str_1, string str_2) {
	// if the difference between the sizes of the strings is > 1, return false immediately
	if((str_1.size() > str_2.size() + 1) || (str_1.size() < str_2.size() - 1)) {
		cout << "Strings have sizes different by > 1." << endl;
		return false;
	}
	else if(str_1.size() < str_2.size()) {
		// we want str_1 to contain the larger string, to avoid doing the insertion case
		string temp_str = str_2;
		str_2 = str_1;
		str_1 = temp_str;
	}
	
	// indices for string 1 and 2
	int index_1 = 0;
	int index_2 = 0;

	// case 1: str_1.size() == str_2.size() + 1. Remove a char from str_1 to get str_2
	if(str_1.size() > str_2.size()) {
		// keep track of number of changes (removals) required to get str_2 from str_1 
		//		if it exceepts 1, we must return false.
		short num_of_removals = 0;

		// we already know that str_1.size = str_2.size() + 1
		while(index_1 < str_1.size() && index_2 < str_2.size()) {
			// if the chars don't match, increment the num_of_removals, and only increment
			//		the longer string's (str_1) index
			if(str_1[index_1] != str_2[index_2]) {
				num_of_removals++;

				// only increment index_1, as we are removeing a char from it
				index_1++;
			}
			// the characters match, so increment both indices
			else {
				index_1++;
				index_2++;
			}
	
			// if more than one away, return false
			if(num_of_removals > 1) {
				return false;
			}
		}

		// if we went through the while loop without returning false, then we can safely
		//		return true
		return true;
	}
	// case 2: str_1.size() == str_2.size(). Replace a char from str_1 to get str_2
	else {
		// keep track of number of replacements required to get str_2 from str_1. if 
		//		it exceeds 1, then we must return false.
		short number_of_replacements = 0;

		// we know that the sizes of boths strings are equal.
		while(index_1 < str_1.size() && index_2 < str_2.size()) {
			// if the chars don't match, increment the number of replacements
			if(str_1[index_1] != str_2[index_2]) {
				number_of_replacements++;
			}

			// always increment both indices
			index_1++;
			index_2++;

			// if number of replacements > 1, return false
			if(number_of_replacements > 1) {
				return false;
			}
		}

		return true;
	}
}

// // Case 2:
// str_1: basis
// str_2: basic


// // Case 1:
// // true
// str_1: basicp
// str_2: basic

// // false
// str_1: bacice
// str_2: basic

// // true
// str_1: basisc
// str_2: basic

// str_1: basis
// str_2: basic

