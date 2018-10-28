#include <iostream>
#include "bind.cpp"

using namespace std;

long mdc(long a, long b) {
	return a + b;
}

int main() {
	auto f3 = bind( []( int x, int y, int z ){ cout << x*z << (char) y << " " ; } );
	auto f1 = f3( 5, ';' );
	for( int i = 0; i < 5; i++ )
		f1( i );	
	
	return 0;
}
