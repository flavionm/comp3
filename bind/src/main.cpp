#include <iostream>
#include "bind.cpp"

void func(int a) {}

int main() {
	auto f = bind(func, 5);

	return 0;
}