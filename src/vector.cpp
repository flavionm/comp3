#include <iostream>

template <int D, typename T>
class Vector;

template <typename T>
Vector<3, T> crossProduct(const Vector<3, T>& u, const Vector<3, T>& v);

template <int D, typename T>
class Vector {
	public:
		Vector();
		void insert(T n);
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
		void mult(T n);
		Vector& operator *(T n);
		void div(T n);
		Vector& operator /(T n);
		T dotProduct(const Vector& v);
		T operator *(const Vector& v);
		template <typename _T>
		friend Vector<3, _T> crossProduct(const Vector<3, _T>& u, const Vector<3, _T>& v);
		void print(decltype(std::cout)& ostream) const;

	private:
		T array[D];
		int size;
};

template <int D, typename T>
Vector<D, T>& operator *(T n, Vector<D, T>& v);

template <typename T>
class VectorCrossOperatorMediator;

template <typename T>
VectorCrossOperatorMediator<T> operator *(const Vector<3, T>& v);

template <typename T>
Vector<3, T> operator *(const Vector<3, T>& v, const VectorCrossOperatorMediator<T>& m);

template <typename T>
class VectorCrossOperatorMediator {
	private:
		const Vector<3, T>& v;
		template <typename _T>
		friend Vector<3, _T> operator *(const Vector<3, _T>& v, const VectorCrossOperatorMediator<_T>& m);

		VectorCrossOperatorMediator(const Vector<3, T>& callerV);
		template <typename _T>
		friend VectorCrossOperatorMediator<_T> operator *(const Vector<3, _T>& v);
};

//Definitions

template <int D, typename T>
Vector<D, T>::Vector(): size(0) {
	for (int i = 0; i < D; i++)
		array[i] = 0;
}

template <int D, typename T>
void Vector<D, T>::insert(T n) {
	if (size < D)
		array[size++] = n;
	else {
		std::cerr << "Vector full" << std::endl;
		std::exit(EXIT_FAILURE);
	}
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
void Vector<D, T>::mult(T n) {
	for (int i = 0; i < D; i++) {
		array[i] *= n;
	}
}

template <int D, typename T>
Vector<D, T>& Vector<D, T>::operator *(T n) {
	mult(n);

	return *this;
}

template <int D, typename T>
void Vector<D, T>::div(T n) {
	if (n != 0)
		for (int i = 0; i < D; i++) {
			array[i] /= n;
		}
	else {
		std::cerr << "Division by zero" << std::endl;
		std::exit(EXIT_FAILURE);
	}
}

template <int D, typename T>
Vector<D, T>& Vector<D, T>::operator /(T n) {
	div(n);

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
void Vector<D, T>::print(decltype(std::cout)& ostream) const {
	for (int i = 0; i < D - 1; i++)
		ostream << array[i] << ' ';
	ostream << array[D - 1];
}

template <int D, typename T>
Vector<D, T>& operator *(T n, Vector<D, T>& v) {
	return v * n;
}

template <typename T>
VectorCrossOperatorMediator<T>::VectorCrossOperatorMediator(const Vector<3, T>& callerV): v (callerV) {}

template <typename T>
VectorCrossOperatorMediator<T> operator *(const Vector<3, T>& v) {
	return VectorCrossOperatorMediator<T>(v);
}

template <typename T>
Vector<3, T> crossProduct(const Vector<3, T>& u, const Vector<3, T>& v) {
	T r1 = u.array[1]*v.array[2] - u.array[2]*v.array[1];
	T r2 = u.array[2]*v.array[0] - u.array[0]*v.array[2];
	T r3 = u.array[0]*v.array[1] - u.array[1]*v.array[0];

	Vector<3, T> result;
	result = r1, r2, r3;

	return result;
}

template <typename T>
Vector<3, T> operator *(const Vector<3, T>& v, const VectorCrossOperatorMediator<T>& m) {
	return crossProduct(v, m.v);
}

template <int D, typename T>
decltype(std::cout)& operator <<(decltype(std::cout)& cout, const Vector<D, T>& v) {
	v.print(cout);

	return cout;
}
