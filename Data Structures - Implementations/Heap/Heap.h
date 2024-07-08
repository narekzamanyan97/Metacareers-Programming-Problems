#ifndef HEAP_H
#define HEAP_H

#define MAX_CAPACITY 100
#define MAX = false
#define MIN = true

// https://www.youtube.com/watch?v=0wPlzMU-k00
// https://www.youtube.com/watch?v=pAU21g-jBiE

template<class T>
class Heap {
private:
	// an array that will store the heap
	T* heap;

	// the number of elements currently in the heap
	int itemCount;

	// an integer equal to the maximum capacity of the heap
	int maxItems;


	// returns the index of the left child
	int getLeftChildIndex(int index) const;

	// returns the index of the right child
	int getRightChildIndex(int index) const;

	// returns the index of the parent
	int getParentIndex(int index) const;

	// Tests whether this node is a leaf
	bool isLeaf(int nodeIndex) const;

	// if the node has a right child
	bool hasRightChild(int nodeIndex) const;

	// balances the heap. e.g. for max-heap, the maximum element is the root after 
	// removing or adding a new element
	// NOTE: this assumes the left and right heaps with the roots being the
	//		left and right child of the given note are heaps
	void heapRebuild(int subTreeRootIndex, bool min_or_max=MAX);

	// helper method for max heaps
	void heapRebuildMax(int subTreeRootIndex);

	// helper method for min heaps
	void heapRebuildMin(int subTreeRootIndex);

	// get the value of the node at the given index
	T getValue(int index) const;

	// set the value of a given node
	void setValue(int index, T newItem);

	// creates a heap from an unordered array
	void heapCreate(bool min_or_max);


public:
	// constructor for a heap of a given size (must be less than MAX_SIZE)
	// make it a max heap by default
	Heap(int size, bool min_or_max=MAX);

	// create a heap from an array of T
	Heap(const T* array_of_values, int array_size, min_or_max=MAX);

	// destructor
	~Heap();

	// determines if the heap is has items or not
	bool isEmpty() const;

	// returns the current size of the heap (# of elements currently stored in the heap)
	int getNumberOfNodes() const;

	// return the height (number of levels) in the heap.
	int getHeight() const;

	// get the root element of the heap.
	T peekTop() const throw(std::PrecondViolatedExcep);

	// insert a new element
	bool add(T value);

	// removes the root (either max or min) of the heap, and returns the value
	//		of the root
	bool remove();

	// clears the heap
	void clear();


	// prints the heap in a tree-like fashion
	void print();
}

#endif