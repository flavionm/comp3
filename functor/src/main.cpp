#include <iostream>
#include "functor.cpp"

using namespace std;

int main() {
	X x;

	//auto f = sin(exp(x) / 3.0) + cos(x) - x->*3 * log(x) * 5.0;

	//auto f = sin(3.0) - exp(cos(x)) * x->*4 / 4.0 + log(7.0);

	//auto f =  1.0 / (sin(x)->*2 + cos(x)->*2)->*4;

	//cout << f(5.3) << ' ' << f.dx(5.3) << endl;

	//auto f = 1.0 / x/ - 5.0 - x + 3.0 * 2.0 / 1.0;

	auto f = (x->*2+7.0)/(x-7.0);

	cout << "f(x) = " << f.str().str << ", f'(x) = " << f.dx_str().str << endl;
}
