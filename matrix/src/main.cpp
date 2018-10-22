#include <iostream>
#include <ctime>
#include "matrix.cpp"

using namespace std;

template <long long L, long long C>
long long tamanho (Matriz<L, C> m) {
		return m.nLin() * m.nCol();
}

template <long long L, long long LC, long long C>
long long tamanho (const Otimizador<L, LC, C>& m) {
		return m.nLin() * m.nCol();
}

int main() {
	Matriz<1000,1> a;
	Matriz<1,1000> b;
	Matriz<1000,1000> c;
	int tempo = 0, lapso1, lapso2;

	tempo = clock();

	Matriz<1000,1000> x1 = a * b;
	Matriz<1000,1000> x2 = x1 * c;

	cout << tamanho(x1) << endl;
	cout << tamanho(x2) << endl;

	lapso1 = clock() - tempo;

	tempo = clock();

	Matriz<1000, 1000> y = a * b * c;

	lapso2 = clock() - tempo;
	cout << tamanho(y) << endl;

	if( lapso1/lapso2 > 10 )
		cout << "Otimizou " << lapso1 << ' ' << lapso2 << endl;
	else
		cout << "Não otimizou " << lapso1 << ' ' << lapso2 << endl;
}
