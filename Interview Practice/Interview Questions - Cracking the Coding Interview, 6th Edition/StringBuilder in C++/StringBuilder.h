#ifndef STRING_BUILDER_H
#define STRING_BUILDER_H

#include <string>
#include <iostream>
using namespace std;

class StringBuilder {
private:
	// an array of characters holding the string
	char* char_array;

	// number of characters in the string
	int size;

	// the available space/capacity of the string builder
	int capacity;

	// a helper function that determines the number of digits of a given integer
	int helper_num_of_digits(int i);



	// // a helper function for the delete_() function, to shift chars of the string to the
	// //		left
	// void helper_shift_substring_left(int start, int end);



public:
	// constructs a blank string builder with a capacity of 16 chars
	StringBuilder();

	// constructs a string builder with the given capacity
	StringBuilder(int capacity);

	//constructs a string builder with the given string
	StringBuilder(string s);

	// destructor that deletes the char_array, which is allocated dynamically and need to
	//		be deleted.
	~StringBuilder();


	int getSize();

	int getCapacity();

	string toString();

	// append the given string/char/int/double/boolean with the existing string
	StringBuilder append(string s);
	StringBuilder append(char c);
	StringBuilder append(bool b);
	StringBuilder append(int i);
	StringBuilder append(double d);

	// insert the given string/char/bool/int/double 
	StringBuilder insert(int offset, string s);
	StringBuilder insert(int offset, char c);
	StringBuilder insert(int offset, bool b);
	StringBuilder insert(int offset, int i);
	StringBuilder insert(int offset, double d);


	// replace the original string with the specified string from the start index
	StringBuilder replace(int start, string s);

	// delete the substring from the given start index till the end index
	StringBuilder delete_(int start, int end);

	// reverse the string
	StringBuilder reverse();

	// ensures that the StringBuilder capacity is at least equal to the mentioned min
	void ensureCapacity(int min);

	// return the char at the specified index
	char charAt(int index);

	// return the length (total chars) of the string
	int length();

	// return the substring starting from the given index till the end
	string substring(int start);

	// return the substring starting from the given index till the given end index
	string substring(int start, int end);

	// return the index where the first instance of the specified string occurs
	int indexOf(string str);

	// return the index where the given substring occurs the last
	int lastIndexOf(string str);

	// attempt to reduce the size of the StringBuilder
	void trimToSize();

	// print the string
	void print();

	// a helper function for the insert() function, to shift chars of the string to the
	//		right and open up the required space for insertion
	void helper_shift_substring_right(int offset, int shift_length);

};

#endif