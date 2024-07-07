#ifndef HASH_TABLE_CPP
#define HASH_TABLE_CPP

#include <cmath>
#include "HashTable.h"
#include "../Helper Methods/helper_methods.cpp"
#include <exception>


// construct the storage of the given size and set everything to null
template<class T>
HashTable<T>::HashTable() {
	this->storage = new LinkedList<T>[SIZE];


	// set all the values in the storage to null
	for(int i = 0; i < SIZE; i++) {
		// cout << "*************************************************" << endl;
		this->storage[i] = LinkedList<T>();
		// cout << "address in Hash = " << &(this->storage[i]) << endl;
		// // cout << i << ": ";
		// cout << this->storage[i].length() << endl;

	}
}

// Destructor
template<class T>
HashTable<T>::~HashTable() {
	// delete each pointer element and the elements of the linked 
	//		list that it points to 
	delete[] storage;
	// for(int i = 0; i < SIZE; i++) {
	// 	delete storage[i];
	// 	storage[i] = nullptr;
	// }
}

// @parameter:
//		object: an object of type T to be used to determine its type
// @return: 
//		0 if a fundamental/primitive type.
// 		1 if string
// 		2 if object
// template<class T>
// short HashTable<T>::get_type(T object) {
// 	// first check for fundamental type
// 	if(std::is_fundamental_v<T> == true) {
// 		return 0;
// 	}
// 	// then check for string	
// 	else if(std::is_same_v<std::remove_cv_t<std::remove_reference_t<T>>, string> == true) {
// 		return 1;
// 	}
// 	// else, it's an object
// 	else {
// 		return 2;
// 	}
// }


// Helper functions for hashFunction
// convert the given value of type T into a numeric value
// calculate the integer representation of a string by summing up
//		the ascii values of all the characters
// Then add the 1st character's ascii value to the total
template<class T>
int HashTable<T>::string_to_int(string value) {
	int total = 0;

	// add up all the int values of the characters in the string
	for(int i = 0; i < value.size(); i++) {
		// cout << value[i] << " = " << int(value[i]) << endl;
		total += int(value[i]);
	}

	// adding the value of the first character again, to add more randomness.
	total += value[0];

	return total;
}

// since all the other types are being specialized, this is in turn becomes a 
//		specialization for classes
// return the key for a given value
// the means of calculating the hash depends on the type of T
// Since we have specialization for every other type, the only one left is a 
template<class T>
int HashTable<T>::hashFunction(const T& value) {
	// cout << "&value = " << &value << endl;
	// cout << "&value = " << uintptr_t(&value) << endl;
	// use the address itself to find the hash of an object
	return uintptr_t(&value) % SIZE;
}

// !!! use math epsilon f to find the epsilon value

// template specialization for string data type
template<>
int HashTable<string>::hashFunction(const string& value) {
	return this->string_to_int(value) % SIZE;
}

// template specialization for integer (including short, long, unsigned int) data types
// int HashTable<enable_if_t<is_integral_v<T>>::hashFunction(const int& value) {
template<>
int HashTable<int>::hashFunction(const int& value) {
	return value % SIZE;
}

// template specialization for floating point (including float, short) data types
template<>
int HashTable<double>::hashFunction(const double& value) {
	// first, round the argument
	double rounded_value = round(value, ROUND);

	// convert the rounded value to a string by multiplying it by 10*ROUND
	int integer = convertToInt(rounded_value,ROUND);

	return integer % SIZE;
}


// insert a value into the hash table
template<class T>
void HashTable<T>::insert(T value) {
	int key = hashFunction(value);
	this->storage[key].add_last(value);
}

// search a value in the hash table
template<class T>
bool HashTable<T>::search(T value){
	return false;
}


// print the hash table
template<class T>
void HashTable<T>::print(){ 
	for(int i = 0; i < SIZE; i++) {
		cout << i << ": ";
		this->storage[i].print();
	}
}

// delete a value from the hash table
template<class T>
void HashTable<T>::delete_(T value){

}

#endif