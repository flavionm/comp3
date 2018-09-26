#include <iostream>
#include <vector>
#include "lambda.cpp"

using namespace std;

int main() {
	int a[] = {1, 5, 3, 5, 7, 8};
	vector<int> v = {1, 5, 3, 5, 7, 8};

	v | [] (int x) {cout << x << endl;};
	cout << endl;
	a | [] (int x) {cout << x << endl;};

	return 0;
}
