#include <iostream>
#include <cstdlib>
#include "stack_int.h"

StackInt::StackInt() {
	max = 2;
	list = new int[max];
	pointer = 0;
}

StackInt::~StackInt() {
	delete [] list;
}

void StackInt::push(const int num) {
	if (pointer >= max)
		overflow();
	list[pointer] = num;
	pointer++;
}

int StackInt::pop() {
	if (pointer <= 0) {
		std::cerr << "Empty stack\n";
		std::exit(1);
	} else {
		pointer--;
		return list[pointer];
	}
}

const StackInt& StackInt::operator= (const StackInt& s) {
	pointer = s.pointer;
	if (max != s.max) {
		delete [] list;
		max = s.max;
		list = new int[max];
	}
	for (int i = 0; i < pointer; i++) {
		list[i] = s.list[i];
	}

	return *this;
}

StackInt& StackInt::operator<< (const int num) {
	push(num);

	return *this;
}

int& StackInt::operator>> (int& num) {
	num = pop();

	return num;
}

void StackInt::overflow() {
	int *temp = list;
	int oldMax = max;
	max = 2 * max;
	list = new int[max];

	replaceList(temp, oldMax);

	delete [] temp;
}

void StackInt::replaceList(const int newList[], const int size) {
	if (size >= max) {
		std::cerr << "List too small\n";
		std::exit(1);
	} else
		for (int i = 0; i < size; i++)
			list[i] = newList[i];
}
