#include <iostream>
#include "pbind.cpp"

using namespace std;

PlaceHolder __;

long mdc(long a, long b) {
	return a + b;
}

int main() {
	auto f3 = bind(mdc);
	f3.print();
	auto f1 = f3(__, 2);
	f1.print();

	return 0;
}
