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
	int a[] = {1, 2, 3, 4, 7, 8};
	vector<int> v = {1, 2, 3, 4, 7, 8};

	v | cout << x + x - x + x << '\n';

	return 0;
}
