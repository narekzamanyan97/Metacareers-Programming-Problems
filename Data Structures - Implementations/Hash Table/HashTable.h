#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <string>

// each element of the hash table will be a pointer pointing to a 
//		linked list, so that values with the same key will be 
//		appended to it.
class HashTable {
private:
	// account for collision of keys
	// integer key and value
	// bucket = an element in the storage that stores a given 
	//		value
	string** storage[SIZE]; 

	// this will calculate the next prime number that is greater
	//		than the given size of the hash table.
	int calculate_size(int size);

	//***********************************************************
	// 					Helper functions
	// finds the integer representation of a string literal
	int string_to_int(string value);

	// recursive function to delete all the nodes of the linked
	//		list representing an element in a storage
	void destructorHelper(string* storage_el);


public:
	// Constructor
	// @parameters:
	// 		size = the max number of values the hash table will store 
	HashTable(int size);
	
	// Destructor
	~HashTable();

	// return the key for a given value
	int hashFunction(string value);

	void insert(string value);

	// search a value in the hash table
	bool search(string value);
	
	// delete a value from the hash table
	void delete_(string value);
}