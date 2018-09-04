#ifndef STACK_H
#define STACK_H

#include <cstdlib>

template <typename T>
class Stack {
	public:
		Stack();
		~Stack();
		void push(T value);
		T pop();
		const Stack& operator =(const Stack& s);
		const Stack<T*>& operator =(const Stack<T*>& s);
		Stack& operator <<(T num);
		T& operator >>(T& num);

	private:
		T *list;
		int pointer;
		int max;

		void overflow();
		void replaceList(const T newList[], int size);
};

template <typename T>
Stack<T>::Stack() {
	max = 2;
	list = new T[max];
	pointer = 0;
}

template <typename T>
Stack<T>::~Stack() {
	delete [] list;
}

template <typename T>
void Stack<T>::push(T value) {
	if (pointer >= max)
		overflow();
	list[pointer++] = value;
}

template <typename T>
T Stack<T>::pop() {
	if (pointer <= 0) { //TODO: exception
		std::cerr << "Empty stack\n";
		std::exit(1);
	} else {
		pointer--;
		return list[pointer];
	}
}

template <typename T>
const Stack<T>& Stack<T>::operator =(const Stack& s) {
	pointer = s.pointer;
	if (max != s.max) {
		delete [] list;
		max = s.max;
		list = new T[max];
	}
	for (int i = 0; i < pointer; i++) {
		list[i] = s.list[i];
	}

	return *this;
}

template <typename T>
const Stack<T*>& Stack<T>::operator =(const Stack<T*>& s) {
	pointer = s.pointer;
	if (max != s.max) {
		delete [] list;
		max = s.max;
		list = new T[max];
	}
	for (int i = 0; i < pointer; i++) {
		*(list[i]) = *(s.list[i]);
	}

	return *this;
}

template <typename T>
void Stack<T>::overflow() {
	T *temp = list;
	int oldMax = max;
	max = 2 * max;
	list = new T[max];

	replaceList(temp, oldMax);

	delete [] temp;
}

template <typename T>
void Stack<T>::replaceList(const T newList[], const int size) {
	if (size >= max) {
		std::cerr << "List too small\n";
		std::exit(1);
	} else
		for (int i = 0; i < size; i++)
			list[i] = newList[i];
}

#endif
