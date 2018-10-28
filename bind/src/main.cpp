#include <iostream>
#include "bind.cpp"

using namespace std;

long mdc(long a, long b) {
	return a + b;
}

int main() {
	auto f2 = bind( mdc );

	auto f1 = bind(f2, 12);

	for( int i = 2; i <= 12; i++ )
		cout << f1( i ) <<  " ";

	return 0;
}
