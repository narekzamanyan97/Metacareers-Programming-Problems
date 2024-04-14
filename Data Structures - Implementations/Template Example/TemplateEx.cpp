#ifndef TEMPLATE_EX_CPP
#define TEMPLATE_EX_CPP

#include <iostream>
#include <ctime>
#include "TemplateEx.h"
using namespace std;


template<class T>
TemplateEx<T>::TemplateEx(T value, int size) {
	cout << "calling the constructor" << endl;
}

template<class T>
void TemplateEx<T>::print(T value) {
	cout << "printing: " << value << endl;
}

#endif