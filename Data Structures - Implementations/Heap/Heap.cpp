#ifndef HEAP_CPP
#define HEAP_CPP

#include "Heap.h"
#include <string>
#include <cmath>
#include <exception>
#include <iostream>


// Formulas for left/right child and parent (assuming we start from 0)
// left(i) = 2 * i + 1
// right(i) = 2*i + 2
// parent(i) = floor(i-1/2)
// height = ceiling(log2(n + 1))

// returns the index of the left child
// return -1 if the given node is a leaf
//		otherwise, return the index of the given node
template<class T>
int Heap<T>::getLeftChildIndex(int nodeIndex) const {
	if(isLeaf(nodeIndex)) {
		cout << "The given node is a leaf." << endl;
		return -1;
	}
	else {
		return 2*nodeIndex + 1;
	}
}

// returns the index of the right child
template<class T>
int Heap<T>::getRightChildIndex(int nodeIndex) const {
	if(isLeaf(nodeIndex)) {
		cout << "The given node is a leaf." << endl;
		return -1;
	}
	else {
		return 2*nodeIndex + 2;
	}
}

// returns the index of the parent
// return -1 if the given node is the root (index = 0)
// otherwise, return the index of the parent node
template<class T>
int Heap<T>::getParentIndex(int nodeIndex) const {
	if(nodeIndex == 0) {
		cout << "The given node is the root, and has no parent." << endl;
		return -1;
	}
	else {
		return floor((nodeIndex - 1)/2);
	}
}

// Tests whether this node is a leaf
template<class T>
bool Heap<T>::isLeaf(int nodeIndex) const {
	// check for the index of the left child. If it's > the itemCount, then
	//		this node is a leaf
	if(this->getNumberOfNodes() <= 2 * nodeIndex + 1) {
		return true;
	}
	else {
		return false;
	}
}


// return true if the given node has a right child
// false otherwise
// NOTE: if a node is a leaf, it has no left nor right child
//		if it's not a leaf, then it must have a left child
//		we still have to check if a non-leaf node has a right child
template<class T>
bool Heap<T>::hasRightChild(int nodeIndex) const {
	int rChildIndex = nodeIndex * 2 + 2;
	if(rChildIndex >= this->itemCount) {
		return false;
	}
	else {
		return true;
	}
}

// get the value of the node at the given index
template<class T>
T Heap<T>::getValue(int nodeIndex) const {
	if(nodeIndex >= 0 && nodeIndex < this->itemCount) {
		return this->heap[nodeIndex];	
	}
	else if(nodeIndex >= this->getNumberOfNodes()) {
		throw std::out_of_range("Please enter an index less than the size of " + to_string(this->itemCount) + ".");
	}
	else {
		throw std::out_of_range("Please enter a positive index. ");
	}
}

// set the value of a given node
template<class T>
void Heap<T>::setValue(int nodeIndex, T newValue) {
	this->heap[nodeIndex] = newValue;

	this->heapRebuild(nodeIndex);
}

// balances the heap. e.g. for max-heap, the maximum element is the root after 
// removing or adding a new element
// NOTE: the tree rooted at subTreeRootIndex is a semiheap. 
//		That is, the left and right subtrees formed by the
//		left and right children of the given node are heaps
template<class T>
void Heap<T>::heapRebuild(int subTreeRootIndex) {
	if(this->heapType == MAX) {
		this->heapRebuildMax(subTreeRootIndex);
	}
	else {
		this->heapRebuildMin(subTreeRootIndex);
	}
}


// helper method for max heaps
template<class T>
void Heap<T>::heapRebuildMax(int subTreeRootIndex) {
	// first, check if the root is not a leaf
	// otherwise, it means it's already a heap, and we are done.
	if(!this->isLeaf(subTreeRootIndex)) {
		// must have a left child since not a leaf node
		int lChildIndex = this->getLeftChildIndex(subTreeRootIndex);

		// assume the left child is the larger one, for now
		int largerChildIndex = lChildIndex;

		// if the root has a right child
		if(this->hasRightChild(subTreeRootIndex)) {
			// or do rChildIndex = rChildIndex + 1
			int rChildIndex = this->getRightChildIndex(subTreeRootIndex);

			// swap the largerChildIndex if the right > left child
			if(this->getValue(lChildIndex) < this->getValue(rChildIndex)) {
				largerChildIndex = rChildIndex;
			}
		}

		// if the item in the root is smaller than the item in the larger child,
		//		swap items
		if(this->getValue(subTreeRootIndex) < this->getValue(largerChildIndex)) {
			T tempValue = this->getValue(subTreeRootIndex);
			this->heap[subTreeRootIndex] = this->getValue(largerChildIndex);
			this->heap[largerChildIndex] = tempValue;


			// transform the semiheap rooted at largerChildIndex into a heap
			this->heapRebuildMax(largerChildIndex);
		}
		// else, move up
		else{
			if(subTreeRootIndex != 0) {
				int parentIndex = this->getParentIndex(subTreeRootIndex);
				
				// transform the semiheap rooted at the parent index
				this->heapRebuildMax(parentIndex);
			}
		}
	}
	// else, root is a leaf, so we are done, as it is already a heap
}

// helper method for min heaps
template<class T>
void Heap<T>::heapRebuildMin(int subTreeRootIndex) {
		// first, check if the root is not a leaf
	// otherwise, it means it's already a heap, and we are done.
	if(!this->isLeaf(subTreeRootIndex)) {
		// must have a left child since not a leaf node
		int lChildIndex = this->getLeftChildIndex(subTreeRootIndex);

		// assume the left child is the smaller one, for now
		int smallerChildIndex = lChildIndex;

		// if the root has a right child
		if(this->hasRightChild(subTreeRootIndex)) {
			// or do rChildIndex = rChildIndex + 1
			int rChildIndex = this->getRightChildIndex(subTreeRootIndex);

			// swap the smallerChildIndex if the right < left child
			if(this->getValue(lChildIndex) > this->getValue(rChildIndex)) {
				smallerChildIndex = rChildIndex;
			}
		}

		// if the item in the root is larger than the item in the smaller child,
		//		swap items
		if(this->getValue(subTreeRootIndex) > this->getValue(smallerChildIndex)) {
			T tempItem = this->getValue(subTreeRootIndex);
			this->heap[subTreeRootIndex] = this->getValue(smallerChildIndex);
			this->heap[smallerChildIndex] = tempItem;

			// transform the semiheap rooted at smallerChildIndex into a heap
			this->heapRebuildMin(smallerChildIndex);
		}
		// else, move up
		else{
			if(subTreeRootIndex != 0) {
				int parentIndex = this->getParentIndex(subTreeRootIndex);
				
				// transform the semiheap rooted at the parent index
				this->heapRebuildMin(parentIndex);
			}
		}
	}
	// else, root is a leaf, so we are done, as it is already a heap
}


// creates a heap from an unordered array
template<class T>
void Heap<T>::heapCreate() {
	// we can safely use itemCount/2 to ignore all the leaf nodes, which are already
	//		heaps
	for(int index = this->itemCount/2; index >= 0; index--) {
		// Assertion: The tree rooted at index is a semiheap
		if(this->heapType == MAX) {
			heapRebuildMax(index);
		}
		else {
			heapRebuildMin(index);
		}
		// Assertion: The tree rooted at index is a heap
	}
}

// default constructor
// make it a max heap by default
// constructor for a heap of a given size (must be less than MAX_SIZE)
// make it a max heap by default
template<class T>
Heap<T>::Heap(int size, bool min_or_max) {
	// set the type of the heap
	this->heapType = min_or_max;

	if(size <= MAX_CAPACITY/2) {
		this->heap = new T[2*size];
		this->itemCount = 0;
		this->maxItems = 2 * size;
	}
	else if(size > MAX_CAPACITY){
		this->heap = new T[MAX_CAPACITY];
		this->itemCount = 0;
		this->maxItems = MAX_CAPACITY;
	}
	else {
		throw std::length_error("Please enter a positive size.");
	}
}

// create a heap from an array of T
template<class T>
Heap<T>::Heap(const T* array_of_values, int array_size, bool min_or_max) {
	this->heapType = min_or_max;
	cout << "heapType = " << this->heapType << endl;

	// allocate the array
	if(array_size <= MAX_CAPACITY/2) {
		this->heap = new T[2*array_size];
	}
	
	// copy given values into the array
	for(int i = 0; i < array_size; i++) {
		this->heap[i] = array_of_values[i];
	} 

	// update the size and capacity of the heap
	this->itemCount = array_size;	
	this->maxItems = 2 * array_size;

	// reorganize the copied array into a heap
	heapCreate();
}

// destructor
template<class T>
Heap<T>::~Heap() {
	delete[] this->heap;
}

// determines if the heap is has items or not
template<class T>
bool Heap<T>::isEmpty() const {
	if(this->itemCount == 0) {
		return true;
	}
	else {
		return false;
	}
}

// returns the current size of the heap (# of elements currently stored in the heap)
template<class T>
int Heap<T>::getNumberOfNodes() const {
	return this->itemCount;
}

// return the height (number of levels) in the heap.
template<class T>
int Heap<T>::getHeight() const {
	return ceil(log2(this->itemCount + 1));
}

// get the root element of the heap.
template<class T>
T Heap<T>::peekTop() const { //throw(std::out_of_range) {
	if(this->isEmpty()) {
		throw std::out_of_range("Attempted peek into an empty heap.");
	}
	return this->heap[0];
}

// insert a new element
template<class T>
void Heap<T>::add(T newValue) {
	// !!! need to extend the size of the heap if we keep adding new values
	// insert new data into the bottom of the tree
	this->heap[itemCount] = newValue;

	// Trickle new item up to the appropriate spot in the tree
	int newDataIndex = this->itemCount;

	// wheter the new node is in its appropriate place. So far, assume it's false
	bool inPlace = false;

	while((newDataIndex >= 0) and !inPlace) {
		// get the parent of the new node
		int parentIndex = this->getParentIndex(newDataIndex);
		
		// for max heap
		if(this->heapType == MAX) {
			if(this->getValue(newDataIndex) < this->getValue(parentIndex)) {
				inPlace = true;
			}
		}
		// for min heap
		else {
			if(this->getValue(newDataIndex) > this->getValue(parentIndex)) {
				inPlace = true;
			}
		}

		if(inPlace == false) {
			// swap the values of the parent and new node
			T tempValue = this->getValue(newDataIndex);
			this->heap[newDataIndex] = this->getValue(parentIndex);
			this->heap[parentIndex] = tempValue;

			// update the loop variable
			newDataIndex = parentIndex;
		}
	}

	this->itemCount++;
}

// removes the root (either max or min) of the heap, and returns the value
//		of the root
// the default node to remove is the root
template<class T>
void Heap<T>::remove(int nodeIndex) {
	T lastItem = this->getValue(this->itemCount - 1);

	// copy the item from the last node into the root
	this->heap[nodeIndex] = lastItem;

	// remove the last node
	this->itemCount--;

	// transform the semiheap back into a heap
	heapRebuild(nodeIndex);
}

// clears the heap
template<class T>
void Heap<T>::clear() {
	this->itemCount = 0;
}


// prints the heap in a tree-like fashion
template<class T>
void Heap<T>::print() {
	// these are the start and end indices to be printed on a given line (level)
	int start_index = 0;
	int end_index = 0;

	// first, print the root
	cout << " -- " << this->getValue(start_index) << "(" << start_index << ") -- ";


	// loop through the levels
	// for a given level n (1 being the 2nd level)
	// start index = 2^n - 1
	// end index = 2^(n+1) - 2
	for(int n = 1; n <= this->getHeight(); n++) {
		cout << "\n----------------------------------------" << endl;
	
		start_index = pow(2, n) - 1;
		end_index = pow(2, n+1) - 2;



		// if the end_index > the length of the heap, set it to be the length of the heap
		//		so we don't have to check for out of range index in the following loop.
		if(end_index > this->getNumberOfNodes()) {
			end_index = this->getNumberOfNodes() - 1;
		}		

		// loop throug the start and end indices and print
		for(int i = start_index; i <= end_index; i++) {
			cout << this->getValue(i) << " (" << i << ") -- ";
		}

	}
}

#endif