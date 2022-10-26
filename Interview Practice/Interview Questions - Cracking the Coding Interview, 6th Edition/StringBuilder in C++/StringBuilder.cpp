#ifndef STRING_BUILDER_CPP
#define STRING_BUILDER_CPP

#include <cmath>
#include "StringBuilder.h"

#define INIT_CAPACITY 16

// constructs a blank string builder with a capacity of 16 chars
StringBuilder::StringBuilder() {
	this->char_array = new char[INIT_CAPACITY];
	this->size = 0;
	this->capacity = INIT_CAPACITY;
}

// constructs a string builder with the given capacity
StringBuilder::StringBuilder(int capacity) {
	this->char_array = new char[capacity];

	this->size = 0;

	this->capacity = capacity;
}

//constructs a string builder with the given string
StringBuilder::StringBuilder(string s) {
	// set the size of the array to be the size of the string
	this->size = s.size();

	// set the capacity to be twice the size of the string
	this->capacity = this->size * 2;

	// dynamically allocate an array of size capacity
	this->char_array = new char[this->capacity];


	// copy the chars from the given string s to the char_array  
	for(int i = 0; i < s.size(); i++) {
		this->char_array[i] = s[i];
	}

}

// destructor. delete the dynamically allocated array
StringBuilder::~StringBuilder() {
	delete[] this->char_array;
}

// return a string with the elements of char_array
string StringBuilder::toString() {
	string str_to_return = "";

	// append each char from char_array to the string
	for(int i = 0; i < this->size; i++) {
		str_to_return += this->char_array[i];
	}

	return str_to_return;
}

int StringBuilder::getSize() {
	return this->size;
}

int StringBuilder::getCapacity() {
	return this->capacity;
}

// append the given string/char/int/double/boolean with the existing string
// @parameters:
//		s = the string to be appended to the string builder
// @return:
//		this object
StringBuilder StringBuilder::append(string s) {
	// double the size of the char_array if necessary. If the capacity is already
	//		large enough (to contain the given string), the ensure capacity won't do
	//		anything
	this->ensureCapacity(this->size + s.size());
	

	// start appending the given string to char_array
	for(int i = 0; i < s.size(); i++) {
		this->char_array[this->size + i] = s[i];
	}


	// update the size
	this->size += s.size();

	return *this;
}

// append the given char to char_array
StringBuilder StringBuilder::append(char c) {
	// double the size of the char_array if necessary
	// 1 is the size of the given char
	this->ensureCapacity(this->size + 1);

	// append the char at the back
	this->char_array[this->size] = c;

	// increment the size by one
	this->size++;

	return *this;
}


// append a boolean value to a string
//  	append the string "true" if b == true
//		append the string "false" if b == false
StringBuilder StringBuilder::append(bool b) {
	if(b) {
		// 4 is the size of the string "true"
		this->ensureCapacity(this->size + 4);

		this->char_array[this->size + 0] = 't';
		this->char_array[this->size + 1] = 'r';
		this->char_array[this->size + 2] = 'u';
		this->char_array[this->size + 3] = 'e';

		// update the size of the char_array
		this->size += 4;
	}
	else {
		// 5 is the size of the string "false"
		this->ensureCapacity(this->size + 5);

		this->char_array[this->size + 0] = 'f';
		this->char_array[this->size + 1] = 'a';
		this->char_array[this->size + 2] = 'l';
		this->char_array[this->size + 3] = 's';
		this->char_array[this->size + 4] = 'e';
	
		// update the size of the char_array
		this->size += 5;
	}

	return *this;
}

// append the given int to a string
// @parameters:
//		integer = the integer to append to the string
// @return
//		this = a string builder with the int appended to it
StringBuilder StringBuilder::append(int integer) {
	// determine how many digits the integer has.
	int num_of_ditigs = this->helper_num_of_digits(integer);
	
	// ensure the capacity of the character array before proceeding
	this->ensureCapacity(this->size + num_of_ditigs);

	// stores each digit of the integer as a char
	char temp_char;
	
	// keep track of where in the char array to add each digit 
	int counter = 0;

	// get the digits as chars and append it one by one
	for(int i = num_of_ditigs - 1; i > 0; i--) {
		// get the most significant digit from the integer
		temp_char = (char) (i / (int) pow(10, i));

		// append the current digit to the array
		this->char_array[this->size + counter];

		counter++;

		// remove the most significant digit from i so that we can get the next digit
		i = i % (int) pow(10, i);
	}

	return *this;


}


// append the given double to a string
// @parameters:
//		d = the integer to append to the string
// @return
//		this = a string builder with the double d appended to it
StringBuilder StringBuilder::append(double d) {
	// convert the given double into a string
	string d_str = to_string(d);

	// ensure the capacity before appending the string
	this->ensureCapacity(this->size + d_str.size());

	// !!! append the chars of the d_str one by one
	for(int i = 0; i < d_str.size(); i++) {
		this->char_array[this->size + i] = d_str[i];
	}

	return *this;

}

// insert the given string into the char array at the specified location
// @parameters:
//		offset = the starting index at which to insert the given string
//		s = the string to insert
// @return:
//		this = a string builder with the string s inserted at location offset
StringBuilder StringBuilder::insert(int offset, string s) {
	// shift the char array by the size of the given string s
	this->helper_shift_substring_right(offset, s.size());
	cout << "\n******************************************************\n";
	cout << "******************************************************\n";
	this->print();
	// insert the given string in the space allocated by the right shift above
	for(int i = 0; i < s.size(); i++) {
		this->char_array[i + offset] = s[i];
	}
	cout << "\n******************************************************\n";
	cout << "******************************************************\n";
	this->print();
	
	return *this;
}


// insert the given char into the char array at the specified location
// @parameters:
//		offset = the index at which to insert the given char
//		c = the character to insert
// @return:
//		this = a string builder with the char c inserted at location offset
StringBuilder StringBuilder::insert(int offset, char c) {
	// shift the char array by the size of the given string s
	this->helper_shift_substring_right(offset, 1);


	// insert the given char in the position allocated by the right shift above
	this->char_array[offset] = c;

	return *this;
}


// insert the given boolean into the char array at the specified location as a string
//		"true" if b == true, or "false" if b == false
// @parameters:
//		offset = the index at which to insert the given char
//		b = the boolean to insert 
// @return:
//		this = a string builder with the bool b inserted at location offset
StringBuilder StringBuilder::insert(int offset, bool b) {
	string boolean_str;

	if(b) {
		boolean_str = "true";
	}
	else {
		boolean_str = "false";
	}

	// shift the char array by the size of the boolean string
	this->helper_shift_substring_right(offset, boolean_str.size());

	// insert the given string in the space allocated by the right shift above
	for(int i = 0; i < boolean_str.size(); i++) {
		this->char_array[i + offset] = boolean_str[i];
	}

	return *this;

}

// insert the given integer into the char array at the specified location as a string
// @parameters:
//		offset = the index at which to insert the given char
//		integer = the integer to insert 
// @return:
//		this = a string builder with the given integer inserted at location offset
StringBuilder StringBuilder::insert(int offset, int integer) {
	// convert the given int into a string
	string int_str = to_string(integer);

	// shift the char array by the size of the given integer string
	this->helper_shift_substring_right(offset, int_str.size());

	// insert the given string in the space allocated by the right shift above
	for(int i = 0; i < int_str.size(); i++) {
		this->char_array[i + offset] = int_str[i];
	}

	return *this;
}


// insert the given double into the char array at the specified location as a string
// @parameters:
//		offset = the index at which to insert the given char
//		d = the double to insert 
// @return:
//		this = a string builder with the given double inserted at location offset
StringBuilder StringBuilder::insert(int offset, double d) {
	// convert the given int into a string
	string double_str = to_string(d);

	// shift the char array by the size of the given integer string
	this->helper_shift_substring_right(offset, double_str.size());

	// insert the given string in the space allocated by the right shift above
	for(int i = 0; i < double_str.size(); i++) {
		this->char_array[i + offset] = double_str[i];
	}

	return *this;
}


// // replace the original string with the specified string from the start index till
// //		the end index
StringBuilder StringBuilder::replace(int start, string s) {
	// !!! if start is < 0 or >= char_array.size, throw an error
	if(start < 0 || start >= this->size) {
		cout << "Start index out of bounds." << endl;
	}
	else {
		// iterate through the chars of the given string
		for(int i = 0; i < s.size(); i++) {
			// replace the appropriate chars of the char_array with the chars of s
			this->char_array[start + i] = s[i];
		}

		this->print();
	}

	return *this;
}

// delete the substring from the given start index (inclusive) till the end index 
//		(exclusive)
// e.g.
// start = 3
// end = 6
// 		           start:    v 
//                  end:  	          v
// before delete_: {a, 3, s, g, d, q, l, i, i, u, w, o, p, w}
// after delete_:  {a, 3, s, l, i, i, u, w, o, p, w}
// @parameters:
//		start = the index at which to start deleting chars (inclusive)
//		end = the index at which to stop deleting chars (exclusive)
StringBuilder StringBuilder::delete_(int start, int end) {
	// find the length of the left shift
	int shift_length = end - start;

	// shift the chars to the left, starting from the end index, until the start index
	for(int i = end; i < this->size; i++) {
		// shift
		this->char_array[i - shift_length] = this->char_array[i];
	}

	// decrement the size by shift_length
	this->size -= shift_length;

	return *this;
}


// reverse the string
// e.g.
// before reverse: {a, 3, s, g, d, q, l, i, i, u, w, o, p, w}
// after reverse:  {w, p, o, w, u, i, i, l, q, d, g, s, 3, a}
// @return:
//		the reversed version of string builder
StringBuilder StringBuilder::reverse() {
	// stores the mirror char of the current character (counting from the last position) 
	char temp_char;

	// iterate over the first half of the char array and swap each char with the ones 
	//		in the second half.
	int start_index = 0;
	int end_index = this->size - 1;
	while(start_index < end_index) {
		temp_char = this->char_array[start_index];
		this->char_array[start_index] = this->char_array[end_index];
		this->char_array[end_index] = temp_char;

		// increment start index
		start_index++;
		// decrement start index
		end_index--;
	}

	return *this;

}

// ensures that the StringBuilder capacity is at least equal to the mentioned min
void StringBuilder::ensureCapacity(int min) {
	// check if there is a need to resize the char_array
	if(min >= this->capacity) {
		// !!! double the size of the char_array
		// dynamically allocate a new array, and copy all the chars from the old array to
		//		the new one. 
		char* new_char_array = new char[2*min];

		// copy over all the chars to the new array
		for(int i = 0; i < this->size; i++) {
			new_char_array[i] = this->char_array[i];
		}

		// delete the old array
		delete[] this->char_array;

		// set the char array to the new char array
		this->char_array = new_char_array;

		cout << "after ensuring capacity: " << endl;
		this->print();
	}
}

// return the char at the specified index
// @parameters:
//		index = the index for the char
// @return
//		the char at the given index in char_array 
char StringBuilder::charAt(int index) {
	// ensure the index is not out of bounds
	if(index < 0 || index > this->size) {
		cout << "Index is out of range." << endl;
		throw std::out_of_range("Index is out of range.");
	}
	else {
		return this->char_array[index];
	}
}

// return the length (total chars) of the string
int StringBuilder::length() {
	return this->size;
}

// return the substring starting from the given index till the end
// @parameter:
//		start = the start index of the substring (inclusive)
// @return:
//		the substring of char_array that starts from the start index, and ends at 
//			this->size
string StringBuilder::substring(int start) {
	if(start < 0 || start > this->size) {
		cout << "Index is out of range." << endl;
		throw std::out_of_range("Index is out of range.");
	} else {
		// declare a string with enough size to store the substring (so that no 
		//	reallocation is done while copying the elements of char_array)
		string str_to_return = "";
		str_to_return.resize(this->size - start);
		
		cout << "Capacity = " << str_to_return.capacity() << endl;

		// copy the chars of the substring into the string to return
		for(int i = start; i < this->size; i++) {
			str_to_return += this->char_array[i];
		}

		return str_to_return;
	}
}

// return the substring starting from the given index till the given end index
// @parameter:
//		start = the start index of the substring (inclusive)
//		end = the end index of the substring (exclusive)
// @return:
//		the substring of char_array that starts from the start index, and ends at given
//			end index
string StringBuilder::substring(int start, int end) {
	if(start < 0 || start > this->size || end < 0 || end > this->size || start > end) {
		cout << "Index is out of range." << endl;
		throw std::out_of_range("Index is out of range.");
	} else {
		// declare a string with enough size to store the substring (so that no 
		//	reallocation is done while copying the elements of char_array)
		string str_to_return = "";
		str_to_return.resize(end - start);
		
		cout << "Capacity = " << str_to_return.capacity() << endl;

		// copy the chars of the substring into the string to return
		for(int i = start; i < end; i++) {
			str_to_return += this->char_array[i];
		}

		return str_to_return;
	}
}

// return the index where the first instance of the specified string occurs
// char_array: {a, b, e, q, a, d, c, o, m, n, m, t, y, l}
// str:												l, n, y
// str:										  t, y, l
// str:									   m, t, y
// str:		                         m, t, y
// char_array: {a, b, e, q, a, d, c, o, m, t, m, t, y, m, m, a, i}
// str:		                         m, t, y, m, m 
// char_array: {a, b, e, q, a, d, c, o, m, m, m, y, m, m, a, i}
// str:		                         m, m, y, m, m 
// @parameters:
//		str = a string to look for the in StringBuilder
// @return:
//		the index at which the first match occurs between the given str and a substring
//			in the char array.
int StringBuilder::indexOf(string str) {
	// the index to be used for the char array
	int index = 0;

	// index for the given string str
	int str_index = 0;

	// keep track of the number of char matches. if it is equal to the size of the string,
	// 		then we have a match
	int num_of_matches = 0;

	// iterate through the char array
	while(index < this->size) {
		// looking for a match
		while(index < this->size
				&& str_index < str.size()
				&& this->char_array[index] == str[str_index]) {
			// increment number of char matches by one
			num_of_matches++;

			// increment both index and str_index
			index++;
			str_index++;
		}

		// if all the chars matched, return the index at which the match began to occur
		if(num_of_matches == str.size()) {
			return index - num_of_matches;
		}
		// otherwise, reset the str_index and num_of_matches to 0. 
		//		Also, increment the index
		else {
			// reset str_index
			str_index = 0;

			// only increment index here if there has not been any match in the inner
			//		loop
			index = index - num_of_matches + 1;

			// reset the number of char matches
			num_of_matches = 0;
		}
	}

	return -1;
}

// return the index where the given substring occurs the last
// begin from the end
// @parameters:
//		str = a string to look for the in StringBuilder
// @return:
//		the index at which the last match occurs between the given str and a substring 
//			in the char array.
int StringBuilder::lastIndexOf(string str) {
	// the index to be used for the char array. start from the end
	int index = this->size - 1;

	// index for the given string str. start from the end
	int str_index = str.size() - 1;

	// // keep track of the first index after which the given string starts to match
	// //		This is the index to be returned if the entire str matches with a sequence
	// //		in the char array 
	// int first_instance_index = -1; 

	// keep track of the number of char matches. if it is equal to the size of the string,
	// 		then we have a match
	int num_of_matches = 0;

	// iterate through the char array
	while(index > 0) {
		// looking for a match
		while(index > 0
				&& str_index > 0
				&& this->char_array[index] == str[str_index]) {
			// increment number of char matches by one
			num_of_matches++;

			// increment both index and str_index
			index--;
			str_index--;
		}

		// if all the chars matched, return the index at which the match began to occur
		if(num_of_matches == str.size()) {
			return index;
		}
		// otherwise, reset the str_index and num_of_matches to 0. 
		//		Also, increment the index
		else {
			// reset str_index
			str_index = str.size() - 1;

			// only increment index here if there has not been any match in the inner
			//		loop
			index = index + num_of_matches;

			// reset the number of char matches
			num_of_matches = 0;
		}
	}

	return -1;
}

// attempt to reduce the size of the StringBuilder
// 		if the size (# of actual chars in the char array) is < capacity (the size of the
//			array), then trim the StringBuilder
void StringBuilder::trimToSize() {
	// if there is unused space
	if(this->size < this->capacity) {
		// dynamically create another char array
		char* new_char_array = new char[this->size];

		// copy all the elements in char_array into new_char_array
		for(int i = 0; i < this->size; i++) {
			new_char_array[i] = this->char_array[i];
		}

		// delete char_array
		delete[] this->char_array;

		// set char_array to be new_char_array
		this->char_array = new_char_array;
	}
}


// print the string
void StringBuilder::print() {
	for(int i = 0; i < this->size; i++) {
		cout << this->char_array[i];
	}
}

// determine the number of digits of the given integer
// e.g. 
// @parameters:
//		i = the integer whose number of digits we need to find
// @return
//		the number of digits that the given integer has
int StringBuilder::helper_num_of_digits(int i){
	// store the number of digits of the given int
	int num_of_ditigs = 1;

	// divide the given integer by 10. If the result (divident) is >= 1, then multiply
	//		powers_of_ten by ten and repeat the division, incrementing num_of_digits
	int divident;	

	// divide the given int (i) with this value. If the divident is > 1, multiply this
	//		value by 10, increment num_of_digits by 1, and divide again
	int powers_of_ten = 10;

	divident = i / powers_of_ten;

	// while i has as many digits as powers_of_ten
	while(divident > 1) {
		// increment num_of_digits
		num_of_ditigs++;

		// increment the number of digits of powers_of_ten by 1 (by multiplying it by 10)
		powers_of_ten *= 10;

		divident = num_of_ditigs / powers_of_ten;
	}

	return num_of_ditigs;
}

// shifts the string to the right by the length
// example:
// [a, b, g, d, e, q, a, d, a, g, s, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL]
// [a, b, g, d, e, q, d, e, q, a, d,   a,   g,    s,   NULL, NULL, NULL, NULL, NULL]
// @parameters:
//		offset = the index starting which the chars are shifter to the right
//		shift_length = the number of right shifts that will be done
void StringBuilder::helper_shift_substring_right(int offset, int shift_length) {
	// first, ensure that the string will have the capacity needed for the shift
	this->ensureCapacity(this->size + shift_length);

	// used to swap characters
	char temp_char;

	// loop through the characters to the right of the offset starting from th rightmost
	//		character until offset + shift_length
	for(int i = this->size + shift_length - 1; i >= offset + shift_length; i--) {
		// shift the current char by shift_length positions
		this->char_array[i] = this->char_array[i - shift_length];
	}

	// set all the characters that will be replaced by the insert function to '' (empty)
	for(int i = offset; i < offset + shift_length; i++) {
		this->char_array[i] = '-';
	}

	// increase the size of the char_array by shift_length
	this->size += shift_length;
	this->print();

}



#endif