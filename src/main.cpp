#include <iostream>
#include "vector.cpp"

using namespace std;

int main() {
	Vector<3, double> v1, v2, v3;
	v1 = 5, 4, 3;
	v2 = 7, 3, 2;
	cout << v1 << endl;
	cout << v2 << endl;
	v1.add(v2);
	cout << v1 << endl;
	v1 + v2 + v2;
	cout << v1 << endl;
	v1.sub(v2);
	cout << v1 << endl;
	v1 - v2 - v2;
	cout << v1 << endl;
	v1.mult(2);
	cout << v1 << endl;
	v1 * 2;
	cout << v1 << endl;
	cout << v2 << endl;
	2.1 * v2;
	cout << v2 << endl;
	std::cout << v1 * v2 << std::endl;
	std::cout << v2.dotProduct(v2) << std::endl;
	cout << v1 << endl;
	cout << v2 << endl;
	v3 = v1 ** v2;
	cout << v3 << endl;
	v3 = crossProduct(v1, v2);
	cout << v3 << endl;
}
