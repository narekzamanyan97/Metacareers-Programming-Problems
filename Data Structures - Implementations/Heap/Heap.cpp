#ifndef HEAP_CPP
#define HEAP_CPP

#include "Heap.h"

// Formulas for left/right child and parent (assuming we start from 0)
// left(i) = 2 * i + 1
// right(i) = 2*i + 2
// parent(i) = floor(i-1/2)

// default constructor
// make it a max heap by default
Heap(int size, bool min_or_max=MAX);
	if(size <= MAX_SIZE) {
		this->heap = new T[size];
	}
	else if(size > MAX_SIZE){
		this->heap = new T[MAX_SIZE];
	}
	else {
		throw std::length_error("Please enter a positive size.")
	}
}

// create a heap from an array of T
Heap(T* array_of_values, min_or_max=MAX) {

}

// destructor
~Heap();

// returns the index of the parent
int parent(T element);

// returns the index of the left child
int lChild(T element);

// returns the index of the right child
int rChild(T element);

// removes the root (either max or min) of the heap, and returns the value
//		of the root
T removeRoot();

// returns the root (either max or min) from the heap
int getRoot();

// returns the current size of the heap (# of elements currently stored in the heap)

// insert a new element
insert(T value);

// delete an element
delete(T value);

// recursive algorithm to balance the heap
// NOTE: this assumes the left and right heaps with the roots being the
//		left and right child of the given note are heaps
void heapRebuild(int subTreeRootIndex);


// creates a heap from an unordered array
void heapCreate();

#endif