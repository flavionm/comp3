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

				VectorCommaOperatorMediator(Vector& callerV);
				friend class Vector;
		};
		VectorCommaOperatorMediator operator =(T n);
		void add(const Vector& v);
		Vector& operator +(const Vector& v);
		void sub(const Vector& v);
		Vector& operator -(const Vector& v);
		void product(T n);
		Vector& operator *(T n);
		T dotProduct(const Vector& v);
		T operator *(const Vector& v);

		void printArray(); //Temporary
		void printSize(); //Temporary

	private:
		T array[D];
		int size;
};

template <int D, typename T>
Vector<D, T>::Vector(): size(0) {
	for (int i = 0; i < D; i++)
		array[i] = 0;
}

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
typename Vector<D, T>::VectorCommaOperatorMediator& Vector<D, T>::VectorCommaOperatorMediator::operator ,(T n) {
	v.insert(n);

	return *this;
}

template <int D, typename T>
Vector<D, T>::VectorCommaOperatorMediator::VectorCommaOperatorMediator(Vector& callerV): v (callerV) {}

template <int D, typename T>
typename Vector<D, T>::VectorCommaOperatorMediator Vector<D, T>::operator =(T n) {
	insert(n);

	return VectorCommaOperatorMediator(*this);
}

template <int D, typename T>
void Vector<D, T>::add(const Vector& v) {
	for (int i = 0; i < D; i++) {
		array[i] += v.array[i];
	}
}

template <int D, typename T>
Vector<D, T>& Vector<D, T>::operator +(const Vector& v) {
	add(v);

	return *this;
}

template <int D, typename T>
void Vector<D, T>::sub(const Vector& v) {
	for (int i = 0; i < D; i++) {
		array[i] -= v.array[i];
	}
}

template <int D, typename T>
Vector<D, T>& Vector<D, T>::operator -(const Vector& v) {
	sub(v);

	return *this;
}

template <int D, typename T>
void Vector<D, T>::product(T n) {
	for (int i = 0; i < D; i++) {
		array[i] *= n;
	}
}

template <int D, typename T>
Vector<D, T>& Vector<D, T>::operator *(T n) {
	product(n);

	return *this;
}

template <int D, typename T>
T Vector<D, T>::dotProduct(const Vector& v) {
	T result = 0;

	for (int i = 0; i < D; i++) {
		result += array[i] * v.array[i];
	}

	return result;
}

template <int D, typename T>
T Vector<D, T>::operator *(const Vector& v) {
	return dotProduct(v);
}

template <int D, typename T>
void Vector<D, T>::printArray() { //Temporary
	for (int i = 0; i < D; i++)
		std::cout << array[i] << ' ';
	std::cout << std::endl;
}

template <int D, typename T>
void Vector<D, T>::printSize() { //Temporary
	std::cout << size << std::endl;
}
