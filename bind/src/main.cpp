#include <iostream>
#include "bind.cpp"

using namespace std;

void func(int a, double b) {
	cout << a << " " << b << endl;
}

int main() {
	auto f = bind(func, 5);

	f(4.5);

	return 0;
}
