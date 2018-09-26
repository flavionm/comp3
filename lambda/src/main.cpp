#include <iostream>
#include <vector>
#include "lambda.cpp"

using namespace std;

int main() {
	int array[] = {1, 5, 3, 5, 7, 8};
	cout << array_size(array) << endl << endl;

	vector<int> v = {1, 5, 3, 5, 7, 8};
	v | [] (int x) {cout << x << endl;};

	return 0;
}
