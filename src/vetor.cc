#include <iostream>

template <int D, typename T>
class Vector {
	public:
		Vector();
		int insert(T n);
		class VectorCommaOperatorMediator {
			public:
				VectorCommaOperatorMediator& operator ,(T n);
			private:
				Vector& v;

				VectorCommaOperatorMediator(Vector& caller_v);
				friend class Vector;
		};
		VectorCommaOperatorMediator operator =(T n);

		void printArray(); //Temporary
		void printSize(); //Temporary

	private:
		T array[D];
		int size;

};

template <int D, typename T>
Vector<D, T>::Vector(): size(0) {}

template <int D, typename T>
int Vector<D, T>::insert(T n) {
	if (size < D)
		array[size++] = n;
	else {
		std::cerr << "Vector full" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	return n;
}

template <int D, typename T>
typename Vector<D, T>::VectorCommaOperatorMediator Vector<D, T>::operator =(T n) {
	insert(n);

	return VectorCommaOperatorMediator(*this);
}

template <int D, typename T>
typename Vector<D, T>::VectorCommaOperatorMediator& Vector<D, T>::VectorCommaOperatorMediator::operator ,(T n) {
	v.insert(n);

	return *this;
}

template <int D, typename T>
Vector<D, T>::VectorCommaOperatorMediator::VectorCommaOperatorMediator(Vector& caller_v): v (caller_v) {}

template <int D, typename T>
void Vector<D, T>::printArray() { //Temporary
	for (int i = 0; i < size; i++)
		std::cout << array[i] << std::endl;
}

template <int D, typename T>
void Vector<D, T>::printSize() { //Temporary
	std::cout << size << std::endl;
}
