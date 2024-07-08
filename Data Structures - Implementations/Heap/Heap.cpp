#ifndef HEAP_CPP
#define HEAP_CPP

#include "Heap.h"
#include <cmath>
#include <exception>

using namespace std;

// Formulas for left/right child and parent (assuming we start from 0)
// left(i) = 2 * i + 1
// right(i) = 2*i + 2
// parent(i) = floor(i-1/2)

// returns the index of the left child
// return -1 if the given node is a leaf
//		otherwise, return the index of the given node
template<class T>
int Heap<T>::getLeftChildIndex(int index) const {
	if(isLeaf(index)) {
		cout << "The given node is a leaf." << endl;
		return -1;
	}
	else {
		return 2*i + 1;
	}
}

// returns the index of the right child
template<class T>
int Heap<T>::getRightChildIndex(int index) const {
	if(isLeaf(index)) {
		cout << "The given node is a leaf." << endl;
		return -1;
	}
	else {
		return 2*i + 2;
	}
}

// returns the index of the parent
// return -1 if the given node is the root (index = 0)
// otherwise, return the index of the parent node
template<class T>
int Heap<T>::getParentIndex(int index) const {
	if(index == 0) {
		cout << "The given node is the root, and has no parent." << endl;
		return -1;
	}
	else {
		return floor((index - 1)/2);
	}
}

// Tests whether this node is a leaf
template<class T>
bool Heap<T>::isLeaf(int nodeIndex) const;


// return true if the given node has a right child
// false otherwise
// NOTE: if a node is a leaf, it has no left nor right child
//		if it's not a leaf, then it must have a left child
//		we still have to check if a non-leaf node has a right child
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
T Heap<T>::getValue(int index) const {
	if(index >= 0 && index < this->itemCount) {
		return this->heap[index];	
	}
	else if(index >= this->itemCount) {
		throw std::out_of_range("Please enter an index less than the size of " + this->itemCount + ".");
	}
	else if(index < 0) {
		throw std::out_of_range("Please enter a positive index. ");
	}
}

// set the value of a given node
void Heap<T>::setValue(int index, T newItem) {
	this->heap[index] = newItem;
}

// balances the heap. e.g. for max-heap, the maximum element is the root after 
// removing or adding a new element
// NOTE: the tree rooted at subTreeRootIndex is a semiheap. 
//		That is, the left and right subtrees formed by the
//		left and right children of the given node are heaps
template<class T>
void Heap<T>::heapRebuild(int subTreeRootIndex, bool min_or_max=MAX) {
	if(min_or_max==MAX) {
		this->heapRebuildMax(subTreeRootIndex);
	}
	else {
		this->heapRebuildMin(subTreeRootIndex);
	}
}


// helper method for max heaps
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
			T tempItem = this->getValue(subTreeRootIndex);
			this->setValue(subTreeRootIndex) = this->getValue(largerChildIndex);
			this->setVakue(largerChildIndex) = tempItem;

			// transform the semiheap rooted at largerChildIndex into a heap
			this->heapRebuildMax(largerChildIndex);
		}
	}
	// else, root is a leaf, so we are done, as it is already a heap
}

// helper method for min heaps
void Heap<T>::heapRebuildMin(int subTreeRootIndex, bool min_or_max=MAX);


// creates a heap from an unordered array
template<class T>
void Heap<T>::heapCreate(bool min_or_max);

// default constructor
// make it a max heap by default
// constructor for a heap of a given size (must be less than MAX_SIZE)
// make it a max heap by default
template<class T>
Heap<T>::Heap(int size, bool min_or_max=MAX) {
	if(size <= MAX_SIZE/2) {
		this->heap = new T[2*size];
		this->itemCount = 0;
		this->maxItems = 2 * size;
	}
	else if(size > MAX_SIZE){
		this->heap = new T[MAX_SIZE];
		this->itemCount = 0;
		this->maxItems = MAX_SIZE;
	}
	else {
		throw std::length_error("Please enter a positive size.");
	}
}

// create a heap from an array of T
template<class T>
Heap<T>::Heap(const T* array_of_values, int array_size, min_or_max=MAX) {

	// allocate the array
	if(size <= MAX_SIZE/2) {
		this->heap = new T[2*size];
	}
	
	// copy given values into the array
	for(int i = 0; i < array_size; i++) {
		this->heap[i] = array_of_values[i];
	} 

	// update the size and capacity of the heap
	this->itemCount = array_size;	
	this->maxItems = 2 * size;

	// reorganize the copied array into a heap
	heapCreate(min_or_max);
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
int Heap<T>::getHeight() const;

// get the root element of the heap.
template<class T>
T Heap<T>::peekTop() const throw(std::PrecondViolatedExcep) {
	return this->heap[0];
}

// insert a new element
template<class T>
bool Heap<T>::add(T value);

// removes the root (either max or min) of the heap, and returns the value
//		of the root
template<class T>
bool Heap<T>::remove() {

}

// clears the heap
void Heap<T>::clear();


// prints the heap in a tree-like fashion
void Heap<T>::print();

#endif