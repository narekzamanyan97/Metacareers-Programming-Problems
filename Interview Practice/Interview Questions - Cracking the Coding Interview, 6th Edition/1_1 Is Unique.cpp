#include <iostream>
#include <stdlib.h>
#include <string>
#include <map>
#include <vector>
#include <cctype>
using namespace std;

bool all_unique_with_hash(string str);

bool all_unique_bit_vector(string str);

void expand_vector(vector<bool>& bitmap, int index);

int main() {
	// stores the string being checked
	string str;

	// will store the return value of all_unique.
	bool is_all_unique;

	cout << "Enter a string: " << endl;
	cin >> str;

	is_all_unique = all_unique_bit_vector(str);

	if(is_all_unique) {
		cout << "Unique." << endl;
	}
	else {
		cout << "Not unique" << endl;
	}
}


// use a hash map to determine if all the chars of the given string are unique
// @parameters:
//		str = the given string
// @return:
//		true = if the string contains all unique characters
//		false = otherwise
bool all_unique_with_hash(string str) {
	// declare the map
	// the value is not relevant here. The key is the character we are interested in.
	map<char, int> characters;

	// will store the lower case value of the given char
	char temp_char;

	// iterate over the characters of the given string
	for(int i = 0; i < str.size(); i++) {

		temp_char = tolower(str[i]);

		// if the character is not found, insert it into the map
		if(characters.find(temp_char) == characters.end()) {
			characters[temp_char] = i;
		}
		// the character is already in the map. So there is a duplicate. return false
		else {
			cout << "character " << temp_char << " is repeated." << endl;
			return false;
		}
	}

	return true;
}

// use a bit vector. the index is the indeger value of the character. the value at that
//		index is either true or false
//		true = if the character having that index is present in the string
//		false = otherwise
// @parameters:
//		str = the given string
// @return:
//		true = if the string contains all unique characters
//		false = otherwise
bool all_unique_bit_vector(string str) {
	// declare a bit vector
	// a value at index is true if the character having that integer index is 
	//		in the string
	//	false otherwise
	vector<bool> bitmap(128, false);

	// will store the integer value of the casted character
	int int_value_of_char;

	// will store the lowercase equivalent of the character
	char lowercase;

	// will be used for insertion
	std::vector<bool>::iterator it;


	for(int i = 0; i < str.size(); i++) {
		lowercase = tolower(str[i]);

		// cast the char into int
		int_value_of_char = (int) lowercase;
		cout << lowercase << " = " << int_value_of_char << endl;
		if((bitmap.size() > int_value_of_char) && bitmap[int_value_of_char]) {
			cout << "character " << lowercase << " is repeated." << endl;
			return false;
		}
		else {

			// if the size of the vector is not large enough to insert the given
			//		char's value, expand it
			if(bitmap.capacity() <= int_value_of_char) {
				// expand_vector(bitmap, int_value_of_char);
			}

			bitmap[int_value_of_char] = true;

			int counter = 0;
			for(auto it = bitmap.begin(); it != bitmap.cend(); it++) {
				if(*it == true) {
					cout << "(" << counter << ")" << *it << " ";
				}
				counter++;
			}
			cout << endl;
		}
	}

	return true;
}

// a helper function that expands the size of the vector to include the given index
// @parameters:
//		bitmap = a reference to the vector whose size we want to increase
//		index = the index we want the vector to include. That is, the new size of the
//			vector has to be > index
void expand_vector(vector<bool>& bitmap, int index) {
	bitmap.resize(2*index);
}