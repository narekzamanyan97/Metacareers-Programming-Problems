#ifndef TEMPLATE_EX_H
#define TEMPLATE_EX_H

// template <typename T> struct Node {
// 	T value;
// 	Node* next = nullptr;
// 	Node* previous = nullptr;
// };


// duplicates are allowed
template <class T> 
class TemplateEx {
private:
	// // a pointer to the front of the linked list (the first element)
	// Node<T>* head;

	// // a pointer to the back of the linked list
	// Node<T>* tail;


public:
	TemplateEx(T value, int size);
	
	void print(T value);
};


#endif