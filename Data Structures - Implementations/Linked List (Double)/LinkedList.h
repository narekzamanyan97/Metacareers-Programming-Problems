#ifndef LINKED_LIST_H
#define LINKED_LIST_H

struct Node {
	int value;
	Node* next = NULL;
	Node* previous = NULL;
};

// duplicates are allowed
class LinkedList {
private:
	// a pointer to the front of the linked list (the first element)
	Node* head;

	// a pointer to the back of the linked list
	Node* tail;

	// keep track of the number of nodes in the linked list
	int number_of_nodes;


	// remove last/first occurrence helper
	bool remove_occurrence_helper(int value, bool first_or_last);

public:
	// Constructors for linked list
	LinkedList();

	// create a linked list from a given array of values
	LinkedList(int* array_of_values, int size);

	// create a linked list randomly
	LinkedList(int seed, int num_of_nodes, int max_value);

	// destructor
	~LinkedList();


	// determine if the linked list is empty
	bool is_empty();

	// returns the number of elements in the linked list
	int length();

	// traverse the linked list and return that node object
	// find a node with the given value
	Node find(int value);

	// print the values in the linked list
	void print();

	// insert at the given position. Return an object to the head pointer
	Node insert(int value, int position);

	// append at the end (after the last element)
	Node add_last(int value);

	// append at the front (position = 0, before head)
	Node add_first(int value);


	// remove the first oocurrence a node with the given value
	bool remove_first_occurrence(int value);

	// remove the last oocurrence a node with the given value
	bool remove_last_occurrence(int value);

	// delete (pop) the element at the end and return the node object
	Node remove_last();

	// delete (pop) the element at the front (the head)
	Node remove_first();

	// Returns the index of the first occurrence of the specified element in the list,
	//		or -1 if the does not contain the element.
	int index_of(int value);

	// Returns the index of the last occurrence of the specified element in the list,
	//		or -1 if the does not contain the element.
	int last_index_of(int value);

	// !!! implement the ones below
	// return true if this list contains the specified element
	bool contains(int value);

	// retrieve (does not remove) the first element in the list
	Node peek_first();

	// retrieve (does not remove) the last element in the list
	Node peek_last();	

	// removes the element at the specified position in this list 
	Node remove_at_index(int index);



	// sets the given value at the given position in the list
	Node set(int value, int position);

	// removes all the elements from this list
	void clear();

};


#endif

// boolean	add(E e)
// Appends the specified element to the end of this list.
// void	add(int index, E element)
// Inserts the specified element at the specified position in this list.
// boolean	addAll(Collection<? extends E> c)
// Appends all of the elements in the specified collection to the end of this list, in the order that they are returned by the specified collection's iterator.
// boolean	addAll(int index, Collection<? extends E> c)
// Inserts all of the elements in the specified collection into this list, starting at the specified position.
// void	addFirst(E e)
// Inserts the specified element at the beginning of this list.
// void	addLast(E e)
// Appends the specified element to the end of this list.
// void	clear()
// Removes all of the elements from this list.
// Object	clone()
// Returns a shallow copy of this LinkedList.
// boolean	contains(Object o)
// Returns true if this list contains the specified element.
// Iterator<E>	descendingIterator()
// Returns an iterator over the elements in this deque in reverse sequential order.
// E	element()
// Retrieves, but does not remove, the head (first element) of this list.
// E	get(int index)
// Returns the element at the specified position in this list.
// E	getFirst()
// Returns the first element in this list.
// E	getLast()
// Returns the last element in this list.
// int	indexOf(Object o)
// Returns the index of the first occurrence of the specified element in this list, or -1 if this list does not contain the element.
// int	lastIndexOf(Object o)
// Returns the index of the last occurrence of the specified element in this list, or -1 if this list does not contain the element.
// ListIterator<E>	listIterator(int index)
// Returns a list-iterator of the elements in this list (in proper sequence), starting at the specified position in the list.
// boolean	offer(E e)
// Adds the specified element as the tail (last element) of this list.
// boolean	offerFirst(E e)
// Inserts the specified element at the front of this list.
// boolean	offerLast(E e)
// Inserts the specified element at the end of this list.
// E	peek()
// Retrieves, but does not remove, the head (first element) of this list.
// E	peekFirst()
// Retrieves, but does not remove, the first element of this list, or returns null if this list is empty.
// E	peekLast()
// Retrieves, but does not remove, the last element of this list, or returns null if this list is empty.
// E	poll()
// Retrieves and removes the head (first element) of this list.
// E	pollFirst()
// Retrieves and removes the first element of this list, or returns null if this list is empty.
// E	pollLast()
// Retrieves and removes the last element of this list, or returns null if this list is empty.
// E	pop()
// Pops an element from the stack represented by this list.
// void	push(E e)
// Pushes an element onto the stack represented by this list.
// E	remove()
// Retrieves and removes the head (first element) of this list.
// E	remove(int index)
// Removes the element at the specified position in this list.
// boolean	remove(Object o)
// Removes the first occurrence of the specified element from this list, if it is present.
// E	removeFirst()
// Removes and returns the first element from this list.
// boolean	removeFirstOccurrence(Object o)
// Removes the first occurrence of the specified element in this list (when traversing the list from head to tail).
// E	removeLast()
// Removes and returns the last element from this list.
// boolean	removeLastOccurrence(Object o)
// Removes the last occurrence of the specified element in this list (when traversing the list from head to tail).
// E	set(int index, E element)
// Replaces the element at the specified position in this list with the specified element.
// int	size()
// Returns the number of elements in this list.
// Object[]	toArray()
// Returns an array containing all of the elements in this list in proper sequence (from first to last element).
// <T> T[]	toArray(T[] a)
// Returns an array containing all of the elements in this list in proper sequence (from first to last element); the runtime type of the returned array is that of the specified array.