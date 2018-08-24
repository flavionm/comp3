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
Vector<N, T>::Vector(): size(0) {}

template <int N, typename T>
Vector<N, T>::~Vector() {}

template <int N, typename T>
void Vector<N, T>::printArray() {
	for (int i = 0; i < size; i++)
		std::cout << array[i] << std::endl;
}

template <int N, typename T>
void Vector<N, T>::printSize() {
	std::cout << size << std::endl;
}
