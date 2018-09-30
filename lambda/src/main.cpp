#include <iostream>
#include <vector>
#include "lambda.cpp"

using namespace std;

void f (int x) {
	cout << x*x << endl;
}

bool fi (int x) {
	return x % 2 == 1;
}

X x;

int main() {
	int tab[] = {1, 2, 3, 4, 7, 8};
	vector<int> v = {1, 2, 3, 4, 7, 8};

	v | cout << 2 + x * x / 3 - 5 << '\n';
	cout << endl;
	tab | cout << x*x << '\n';
	cout << endl;
	tab | [ &v ]( int x ) { v.push_back( x ); };
	for (auto x : v) cout << x << endl;
	cout << endl;
	v | (x % 2 == 0) | cout << x*x + 1 << '\n';
	cout << endl;
	v | x % 2 == 1 | x*x | cout << x << '\n';

	return 0;
}
