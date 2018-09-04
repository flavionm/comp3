#include <iostream>
#include "stack.h"

int main() {
	Stack<int*> s;
	Stack<int*> s2;
	int **v1 = new int*[10];
	int **v2 = new int*[10];


	for (int i = 0; i < 10; i++) {
		*(v1 + i) = new int;
		**(v1 + i) = i;
		*(v2 + i) = new int;
		**(v2 + i) = -i;
	}
	std::cout << "Here\n";

	for (int i = 0; i < 10; i++) {
		s.push(v1[i]);
	}

	s2 = s;

	for (int i = 0; i < 5; i++) {
		s.pop();
	}
	for (int i = 5; i < 10; i++) {
		s.push(v2[i]);
	}
	for (int i = 0; i < 10; i++) {
		std::cout << *(s.pop()) << std::endl;
	}
	for (int i = 0; i < 10; i++) {
		std::cout << *(s2.pop()) << std::endl;
	}
}
