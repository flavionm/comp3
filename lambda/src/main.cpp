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

int main() {
	int a[] = {1, 2, 3, 4, 7, 8};
	vector<int> v = {1, 2, 3, 4, 7, 8};

	v | [] (int x) {return x % 2 == 0;} | [] (int x) {cout << x << endl;};
	cout << endl;
	v | fi | f;
	cout << endl;
	v | [] (int x) {return x % 2 == 0;} | f;
	cout << endl;
	v | fi | [] (int x) {cout << x << endl;};
	cout << endl;
	a | [] (int x) {return x % 2 == 0;} | [] (int x) {cout << x << endl;};
	cout << endl;

	return 0;
}
