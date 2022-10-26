#include <iostream>
#include <string>
#include <map>
using namespace std;

bool is_permutation(string str_1, string str_2);

int main() {
	string str_1;
	string str_2;

	int is_done = '2';

	while(is_done != '1') {
		cout << "************************************************" << endl;
		cout << "Enter the first string: " << endl;
		cin >> str_1;

		cout << "Enter the second string: " << endl;
		cin >> str_2;

		if(is_permutation(str_1, str_2)) {
			cout << str_1 << " is a permutation of " << str_2;
		}
		else {
			cout << str_1 << " is not a permutation of " << str_2;
		}	

		cout << endl;
		cout << "Enter 1 to exit: " << endl;
		cin >> is_done;
	}

	

}


// determines whether str_1 is a permutation of str_2
// @parameters:
//		str_1 = the first string
//		str_2 = the second string
// @return 
//		true = if the given strings are permutations of one another
//		false = otherwise
bool is_permutation(string str_1, string str_2) {
	// stores the number of occurances of each distinct character in str_1
	map<char, int> occurances_of_chars;

	// keeps track of the number of characters in the map
	int chars_remaining = 0;

	// stores the lowercase version of a char (if it is a letter)
	char lowercase;

	// traverse str_1 once and store each character into a map, with the key being
	//		each character, and the value being the number of occurances of the 
	//		character
	for(int i = 0; i < str_1.size(); i++) {
		lowercase = tolower(str_1[i]);

		// if the char at index i has not been encountered yet, create a new entry
		//		in the map, and set it to 0
		if(occurances_of_chars.find(lowercase) == occurances_of_chars.end()) {
			occurances_of_chars[lowercase] = 1;
		}
		// otherwise, increment the number of occurances of the char by 1
		else {
			occurances_of_chars[lowercase]++;
		}

		chars_remaining++;
	}

	// now traverse str_2. use the occurances_of_chars map.
	for(int j = 0; j < str_2.size(); j++) {
		lowercase = tolower(str_2[j]);

		// if the current char is not in the map, then return false;
		if(occurances_of_chars.find(lowercase) == occurances_of_chars.end()) {
			cout << lowercase << " is not in " << str_1 << endl;
			return false;
		}
		// else if the char key is in the map, but its value is 0, then the current char
		//		is extra in the second string, so return false.
		else if(occurances_of_chars[lowercase] == 0) {
			cout << lowercase << " appears more in " << str_2 << endl;
			return false;
		}
		// otherwise, decrement the value of the map with the key being the current char.
		else {
			occurances_of_chars[lowercase]--;
			chars_remaining--;
		}
	}

	// return true if there are no more chars remaining in the map
	if(chars_remaining == 0) {
		return true;
	}
	// else, the first string has more characters than the second string, so the second
	//		string cannot be a permutation of the first string
	else {
		cout << str_1 << " has more characters than " << str_2 << endl;
		return false;
	}

}
