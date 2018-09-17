#include <iostream>
#include "functor.cpp"

using namespace std;

int main() {
	X x;

	auto f = 3.0 * x + x * 5.0;

	cout << f(5) << ' ' << f.dx(5) << endl;
}
