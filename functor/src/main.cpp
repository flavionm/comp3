#include <iostream>
#include "functor.cpp"

using namespace std;

int main() {
	X x;

	auto f = sin(exp(x) / 3.0) + x - x * log(x) * 5.0;

	cout << f(5) << ' ' << f.dx(5) << endl;
}
