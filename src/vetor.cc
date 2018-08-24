#include <iostream> //Temporary

template <int N, typename T>
class Vector {
	public:
		Vector();
		~Vector();
		void printArray(); //Temporary
		void printSize(); //Temporary

	private:
		T array[N];
		int size;
};

template <int N, typename T>
Vector<> Vector<N, T>::Vector(): size(0) {}

void Vector::printArray() {
	for (int i = 0; i < size; i++)
		cout << array[i] << endl;
}

void Vector::printSize() {
	cout << size << endl;
}
