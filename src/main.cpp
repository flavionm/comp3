#include <iostream>
#include "vetor.cc"

using namespace std;

int main() {
	Vector<3, int> v1, v2, v3;
	v1 = 5, 4, 3;
	v2 = 1, 5, 2;
	/*v1.printArray();
	v2.printArray();
	v1.add(v2);
	v1.printArray();
	v1 + v2 + v2;
	v1.printArray();
	v1.sub(v2);
	v1.printArray();
	v1 - v2 - v2;
	v1.printArray();
	v1.mult(2);
	v1.printArray();
	v1 * 2;
	v1.printArray();
	2 * v2;
	v2.printArray();
	std::cout << v1 * v2 << std::endl;
	std::cout << v2.dotProduct(v2) << std::endl;*/
	cout << v1 << endl;
	cout << v2 << endl;
	v3 = v1 ** v2;
	cout << v3 << endl;
	v3 = crossProduct(v1, v2);
	cout << v3 << endl;
}
