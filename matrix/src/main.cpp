#include <iostream>
#include "matrix.cpp"

using namespace std;

int main() {
	Matriz<5, 3> a;
	Matriz<3, 4> b;
	Matriz<5, 4> c;

	auto f = Bind{[](double x){return rand() % 1000000;}};

	auto d = f(a) * f(b) + f(c);

	for( int i = 0; i < d.nLin(); i++ ) {
		for( int j = 0; j < d.nCol(); j++ )
			cout << d[i][j] << ' ';
		cout << endl;
	}

	return 0;
}
