#ifndef HASH_TABLE_CPP
#define HASH_TABLE_CPP

#include <cmath>
#include "HashTable.h"
#include <string>


#define SIZE 200;

// construct the storage of the given size and set everything to null
// Since there might be 
HashTable::HashTable(int size) {
	string** storage = new *string(size);

	// set all the values in the storage to null
	for(int i = 0; i < SIZE; i++) {
		this->storage[i] = nullptr;
	}
}

// Destructor
HashTable::~HashTable() {
	// delete each pointer element and the elements of the linked 
	//		list that it points to 
	for(int i = 0; i < size; i++) {
		destructorHelper(this->storage[i]);
	}
	delete[] storage;
	storage = nullptr;
}

// recursively deletes all the pointers linked to the given
//		element
void HashTable::destructorHelper(string* storage_el) {
	if(storage_el != nullptr) {
		destructorHelper(storage_el)
	}
}

// Helper functions for hashFunction
// calculate the integer representation of a string by summing up
//		the ascii values of all the characters
// Then add the 1st character's ascii value to the total
int HashTable::string_to_int(string value) {
	int total = 0;

	for(int i = 0; i < value.size(); i++) {
		total += int(value[i]);
	}

	total += value[0];

	return total;
}

// return the key for a given value
int HashTable::hashFunction(string value) {
	return this.string_to_int(value) % SIZE;
}


// insert a value into the hash table
void HashTable::insert(string value) {
	int key = hashFunction(value);


}

// search a value in the hash table
bool HashTable::search(string value){

}

// delete a value from the hash table
void HashTable::delete_(string value){

}