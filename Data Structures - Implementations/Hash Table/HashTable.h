#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <string>
#include <cmath>
// This is to use the std::is_integral<float>::value ...
#include <type_traits>
#include "../Linked List (Double)/LinkedList.cpp"

#define SIZE 10
#define ROUND 3
#define FUND 0
#define STR 1
#define OBJ 2

// each element of the hash table will be a pointer pointing to a 
//		linked list, so that values with the same key will be 
//		appended to it.
template<class T>
class HashTable {
private:
	// account for collision of keys
	// integer key and value
	// bucket = an element in the storage that stores a given 
	//		value
	LinkedList<T>* storage; 

	// this will calculate the next prime number that is greater
	//		than the given size of the hash table.
	int calculate_size(int size);

	//***********************************************************
	// 					Helper functions
	// finds the integer representation of a string literal
	int string_to_int(string value);

	// recursive function to delete all the nodes of the linked
	//		list representing an element in a storage
	void destructorHelper(T* storage_el);

	// helper function to determine the type of T
	// short get_type(T object);




public:
	// Constructor
	// @parameters:
	// 		size = the max number of values the hash table will store 
	HashTable();
	
	// Destructor
	~HashTable();

	// return the key for a given value
	int hashFunction(const T& value);

	void insert(T value);

	// search a value in the hash table
	bool search(T value);
	
	// delete a value from the hash table
	void delete_(T value);

	// print the contents of the hash table
	void print();
};

#endif