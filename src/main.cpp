#include <iostream>
#include "stack.h"

int main() {
	Stack s;

	for (int i = 0; i < 100; i++) {
		s.push(i);
	}

	for (int i = 0; i < 100; i++) {
		std::cout << s.pop() << std::endl;
	}
}
