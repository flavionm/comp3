#include <iostream>
#include <cstdlib>
#include "stack.h"

Stack::Stack() {
	max = 2;
	list = new int[max];
	pointer = 0;
}

Stack::~Stack() {
	delete [] list;
}

void Stack::push(const int num) {
	if (pointer >= max) {
		overflow();
	} else {
		list[pointer] = num;
		pointer++;
	}
}

int Stack::pop() {
	if (pointer < 0) {
		std::cerr << "Empty stack\n";
		std::exit(1);
	} else {
		pointer--;
		return list[pointer];
	}
}

const Stack& Stack::operator= (const Stack& s) {
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

Stack& Stack::operator<< (const int num) {
	push(num);

	return *this;
}

int& Stack::operator>> (int& num) {
	num = pop();

	return num;
}

void Stack::overflow() {
	int *temp = list;
	int oldMax = max;
	max = 2 * max;
	list = new int[max];

	replaceList(temp, oldMax);

	delete [] temp;
}

void Stack::replaceList(const int newList[], const int size) {
	if (size >= max) {
		std::cerr << "List too small\n";
		std::exit(1);
	} else
		for (int i = 0; i < size; i++)
			list[i] = newList[i];
}
