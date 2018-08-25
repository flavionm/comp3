#include <iostream>
#include "vetor.cc"

int main() {
	Vector<3, int> v;
	v = 5, 4, 9;

	v.printArray();
	v.printSize();
}
