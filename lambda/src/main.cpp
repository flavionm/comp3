#include <iostream>
#include <vector>
#include "lambda.cpp"
#include <type_traits>

using namespace std;

void f (int x) {
	cout << x*x << endl;
}

bool fi (int x) {
	return x % 2 == 1;
}

int main() {
	//cout << std::is_same<decltype(x(0.0)), double>::value << endl;
	//cout << std::is_same<decltype(x(0.0)), double>::value << endl;
	X x;

	vector< vector<int> > m{ { 1, 2, 3 }, { 0, 3, 7 }, { 1, 3 } };
	//m | []( auto v ) { return v[0] != 0; } | [x]( auto v ) { v + 7 | cout << x << ' '; };
	//m | []( auto v ) { return v[0] != 0; } | ( x | cout << x << ' ' );
	//m | x[0] != 0 | ( x | cout << x << ' ' );
	m | x[0] != 0 | (( x + 7 ) | cout << x << ' ' );

	return 0;
}
