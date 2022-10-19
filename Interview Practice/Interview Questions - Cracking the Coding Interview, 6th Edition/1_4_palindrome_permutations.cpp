#include <iostream>
#include <map>
#include <string>
using namespace std;

bool palindrome_permutations(string str);

bool check_even_and_odd(int str_size, map<char, int>* occurances_of_chars);

int main() {
	string str = "";

	cout << "Enter a string: Enter -1 to exit: " << endl;
	getline(cin, str);

	while (str != "-1") {
		if(palindrome_permutations(str)) { 
			cout << "True" << endl;
		} else {
			cout << "False" << endl;
		}

		cout << "Enter a string: Enter -1 to exit: " << endl;
		getline(cin, str);

	}

	return 0;		
}


// checks if a given string is a permutation of a palindrome.
// @parameters:
//		str = the string to check
// @return:
//		true = if the given string is a permutation of a palindrome
//		false = otherwise
bool palindrome_permutations(string str) {
	// a map that stores the number of occurances of each distinct character in the given
	//		string
	map<char, int> occurances_of_chars;

	// will store the lowercase version of each character (if it is a letter)
	char lowercase;

	// stores the size of the string without the spaces as spaces are ignored
	int size_without_spaces = str.size();

	// iterate over the given string and set the number of occurances 
	for(int i = 0; i < str.size(); i++) {
		lowercase = tolower(str[i]);

		// ignore spaces
		if(lowercase != ' ') {
			// if the char in the given string is not yet encountered, add it to the map as a
			//		key and set its value to 1
			if(occurances_of_chars.find(lowercase) == occurances_of_chars.end()) {
				occurances_of_chars[lowercase] = 1;
			}
			// the key (char) is already in the map. increment its value by 1
			else {
				occurances_of_chars[lowercase]++;
			}			
		}
		else {
			// a space is encountered, so decrement the size_without_spaces by 1
			size_without_spaces--;
		}
	}

	return check_even_and_odd(size_without_spaces, &occurances_of_chars);
}

// given a map of number of occurances of chars and a string size, determine whether the
//		string is a permutation of a palindrome.
// @parameters:
//		str_size = the size of the string
//		occurances_of_chars = a 
// @return:
//		if the string size is even
//			return
//				 true = if all the chars occur even number of times
//				 false = otherwise		
//		if the string size is odd
//			return 
//				true = if at most 1 char occurs odd times (the rest of chars occur even times)
//				false = otherwise
bool check_even_and_odd(int str_size, map<char, int>* occurances_of_chars) {
	// if str.size() is even, then all of the chars have to occur even times for a 
	//		palindrome to be possible
	if(str_size % 2 == 0) {
		// iterate over the map. If any value is odd, return false
		for(auto it = occurances_of_chars->begin(); it != occurances_of_chars->end(); it++) {
			if((*it).second % 2 != 0) {
				cout << (*it).first << " happens " << (*it).second << " times." << endl;
				return false;
			}
		}
	}
	// if str.size() is odd, then one of the chars is allowed to occur odd times.
	else {
		// if this becomes > 1, return false;
		int number_of_odd_occurances = 0;

		// iterate over the map. If more than two values are odd, return false
		for(auto it = occurances_of_chars->begin(); it != occurances_of_chars->end(); it++) {
			if((*it).second % 2 != 0) {
				cout << (*it).first << " happens " << (*it).second << " (odd) times." << endl;
				// if this is the first case of odd occurances, increment the number of 
				//		odd occurances
				if(number_of_odd_occurances == 0) {
					cout << "It is ok so far." << endl;
					number_of_odd_occurances++;
				}
				// otherwise, return false
				else {
					cout << "Not ok." << endl;
					return false;
				}
			}
		}
	}

	return true;
}