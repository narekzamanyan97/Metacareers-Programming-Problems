#ifndef LINKED_LIST_H
#define LINKED_LIST_H

// !!! Push the changes to git (04/13/2024)
//		Commit Message:
//		Modified the LinkedList class to work with a template, so that the type can be
//			any class or type.
//		Added an exception handling in the main method for the insert(), set(), and 
//			remove_at_index() methods
//		Fixed the remvoe_at_index() to return the removed node object

template <class T> 
struct Node {
	T value;
	Node* next = nullptr;
	Node* previous = nullptr;
};

// duplicates are allowed
template <class T> 
class LinkedList {
private:
	// a pointer to the front of the linked list (the first element)
	Node<T>* head;

	// a pointer to the back of the linked list (the last element)
	Node<T>* tail;

	// keep track of the number of nodes in the linked list
	int number_of_nodes;


	// remove last/first occurrence helper
	// template <typename T> 
	bool remove_occurrence_helper(T value, bool first_or_last);

public:
	// Constructors for linked list
	LinkedList();

	// create a linked list from a given array of values
	// template <typename T> 
	LinkedList(T* array_of_values, int size);

	// create a linked list randomly
	// template <typename T> 
	LinkedList(int seed, int num_of_nodes, T max_value);

	// override the asignment operator
	LinkedList& operator=(const LinkedList& other_list);

	// destructor
	~LinkedList();

	// return a pointer to the first node (as an iterator)
	Node<T>* begin();

	// return a pointer to the last node (as an iterator)
	Node<T>* end();


	// return a pointer to the first node (as an iterator)
	Node<T>* cbegin() const;

	// return a pointer to the last node (as an iterator)
	Node<T>* cend() const;

	// remove the given node pointer (iterator) from the list
	Node<T>* remove(Node<T>* pointer);

	// set the given node's value
	// template <typename T> 
	Node<T> set(Node<T>* pointer, T value);

	// determine if the linked list is empty
	bool is_empty();

	// returns the number of elements in the linked list
	int length();

	// traverse the linked list and return that node object
	// find a node with the given value
	// template <typename T> 
	Node<T>* find(T value);

	// print the values in the linked list
	void print() const;

	// insert at the given position. Return an object to the head pointer
	// template <typename T> 
	Node<T> insert(T value, int position);

	// append at the end (after the last element)
	// template <typename T> 
	Node<T> add_last(T value);

	// append at the front (position = 0, before head)
	// template <typename T> 
	Node<T> add_first(T value);

	// append at the end (after the last element)
	void add_last(Node<T>* iterator);

	// append at the front (position = 0, before head)
	void add_first(Node<T>* iterator);

	// append the given linked list at the end (after the last element)
	void add_last(LinkedList linked_list);

	// append the given linked list at the front (position = 0, before head)
	void add_first(LinkedList linked_list);

	// remove the first oocurrence a node with the given value
	// template <typename T> 
	bool remove_first_occurrence(T value);

	// remove the last oocurrence a node with the given value
	// template <typename T> 
	bool remove_last_occurrence(T value);

	// delete (pop) the element at the end and return the node object
	Node<T> remove_last();

	// delete (pop) the element at the front (the head)
	Node<T> remove_first();

	// Returns the index of the first occurrence of the specified element in the list,
	//		or -1 if the does not contain the element.
	// template <typename T> 
	int index_of(T value);

	// Returns the index of the last occurrence of the specified element in the list,
	//		or -1 if the does not contain the element.
	// template <typename T> 
	int last_index_of(T value);

	// !!! implement the ones below
	// return true if this list contains the specified element
	// template <typename T> 
	bool contains(T value);

	// retrieve (does not remove) the first element in the list
	Node<T> peek_first();

	// retrieve (does not remove) the last element in the list
	Node<T> peek_last();	

	// removes the element at the specified position in this list 
	Node<T> remove_at_index(int index);



	// sets the given value at the given position in the list
	// template <typename T> 
	Node<T> set(T value, int position);

	// removes all the elements from this list
	void clear();

	// swaps the given nodes
	void swap_nodes(Node<T>* left_it, Node<T>* right_it);

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