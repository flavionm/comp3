#include <iostream>
#include "bind.cpp"

using namespace std;

double func(int a, double b) {
	return b;
}

int main() {
	auto f = bind(func, 5);

	auto f2 = f(4.5);

	cout << f2() << endl;

	return 0;
}
