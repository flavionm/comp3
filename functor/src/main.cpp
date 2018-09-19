#include <iostream>
#include "functor.cpp"

using namespace std;

int main() {
	X x;

	//auto f = sin(exp(x) / 3.0) + cos(x) - x->*3 * log(x) * 5.0;

	//cout << f(5.3) << ' ' << f.dx(5.3) << endl;

	auto f = 3.0 + x * x + 7.0;

	cout << "str: " << f.str() << ", dx_str: " << f.dx_str() << endl;
}
