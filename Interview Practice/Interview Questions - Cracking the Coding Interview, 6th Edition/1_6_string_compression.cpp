#include <iostream>
#include <string>
using namespace std;

string compress_string(string str);

int main() {
	string str;

	cout << "Enter a string: Enter -1 to exit " << endl;
	getline(cin, str);



	while(str != "-1") {
		cout << compress_string(str) << endl;

		cout << "Enter a string: Enter -1 to exit. " << endl;
		getline(cin, str);

	}


	return 0;
}


// compress a given string
// e.x. aaabbbcc = a3b3c2
// @paramters:
//		str = the string to be compressed
// @return:
//		if the compressed string is longer than the given string, return the given string
//		else, return the compressed string
string compress_string(string str) {
	// use this later to decide whether the new string should be returned or not
	int original_size = str.size();

	// stores the number of consecutive repetitions of a given character 
	int consecutive_reps = 0;


	// compressed version of the string
	string compressed_string = "";

	// index to iterate over the string in a while loop
	int index = 0;

	// stores the letter at the current string (at index)
	char current_letter;

	// iterate over the string
	while(index < original_size) {
		current_letter = str[index];

		// loop through the identical consecutve letters
		while(str[index] == current_letter) {
			// increment the count of the char
			consecutive_reps++;

			// increment the index
			index++;
		}


		// after the loop above, consecutive reps contains the number of repetitions of
		//		the given letter. So add the letter and the reps to the compressed string 
		compressed_string += current_letter + to_string(consecutive_reps);

		// reset consecutive reps to 0
		consecutive_reps = 0;
	}

	cout << compressed_string << endl;

	// check the sizes of the strings. return the one that is shorter
	if(compressed_string.size() < str.size()) {
		return compressed_string;
	}
	else {
		return str;
	}
}


// tthisstringgame