#include <iostream>
#include "matrix.cpp"

using namespace std;

int main() {
	Matriz<4, 3> a;
	Matriz<4, 3> b;
	//auto c = a*b;
	
	// aplicar uma função à uma matriz:
	
	auto f = Bind{[](double x){return rand() % 1000000;}};
	
	//c = f(c);
	auto d = f(a) + f(b);
	
	for( int i = 0; i < d.nLin(); i++ ) {
		for( int j = 0; j < d.nCol(); j++ )
			cout << d[i][j] << ' ';
		cout << endl;
	}

	return 0;
}
