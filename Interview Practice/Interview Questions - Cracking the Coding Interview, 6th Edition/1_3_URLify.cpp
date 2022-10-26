#include <iostream>
#include <string>
#include <utility>
using namespace std;

pair<char*, int> URLify(string str, int size_of_array);

int main() {
	string str;

	cout << "Enter a string to urlify: " << endl;
	getline(cin, str);

	auto url_and_size_pair = URLify(str, str.size());

	char* url = url_and_size_pair.first;

	int size = url_and_size_pair.second;

	// print the resulting url
	for(int k = 0; k < size; k++) {
		cout << url[k];
	}

	// delete the pointer returned by the URLify() fucntion
	delete url;

	return 0;
}


// returns the url version of the given string, replacing spaces (' ') with '%20'
// @parameters:
// 		str = an array of chars representing the string we want to urlify
//		size_of_array = 
pair<char*, int> URLify(string str, int size_of_array) {
	// keep track of the number of spaces
	int number_of_spaces = 0;

	// will hold the size of the extended array (with spaces replaced by "%20")
	int size_of_new_array = 0;

	// first, find the indices of spaces
	for(int i = 0; i < size_of_array; i++) {
		if(str[i] == ' ') {
			number_of_spaces++;
		}
	}

	// calculate the size of the array needed for the url 
	size_of_new_array = size_of_array + 2*number_of_spaces;

	// dynamically allocate a new array with the expanded size
	char* url = new char[size_of_new_array];

	// index for the url to keep track of the index of the newly created array of
	//		chars while iterating over the given (old) array
	int index_url = 0;

	// iterate over the given string again, this time replacing the spaces with "%20"
	for(int j = 0; j < size_of_array; j++) {
		if(str[j] == ' ') {
			url[index_url++] = '%';
			url[index_url++] = '2';
			url[index_url++] = '0';
		}
		else {
			url[index_url++] = str[j];
		}
	}

	cout << endl;

	return {url, size_of_new_array};
}