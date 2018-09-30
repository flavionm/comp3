#include <iostream>
#include <vector>
#include <type_traits>

template <typename V, typename F>
auto operator | (V iterable, F function) -> typename std::enable_if<std::is_same<decltype(function(iterable[0])), bool>::value, V>::type {
	V filtered;
	for (auto x : iterable)
		if (function(x)) filtered.push_back(x);
	return filtered;
}

template <typename V, typename F>
auto operator | (V iterable, F function) -> typename std::enable_if<!std::is_same<decltype(function(iterable[0])), bool>::value, void>::type {
	for (auto x : iterable)
		function(x);
}

template <typename T, int S, typename F>
auto operator | (T(& array)[S] , F function) -> typename std::enable_if<std::is_same<decltype(function(array[0])), bool>::value, std::vector<T>>::type {
	std::vector<T> filtered;
	for (int i = 0; i < S; i++)
		if (function(array[i])) filtered.push_back(array[i]);
	return filtered;
}

template <typename T, int S, typename F>
auto operator | (T(& array)[S], F function) -> typename std::enable_if<!std::is_same<decltype(function(array[0])), bool>::value, void>::type {
	for (int i = 0; i < S; i++)
		function(array[i]);
}

class X {
	public:
	template <typename T>
		T operator () (T x) {
			return x;
		}
};

template <typename T>
class Constant {
	public:
		Constant(T c): c(c) {}
		T operator () (T x) {
			return c;
		}

	private:
		T c;
};

template <typename F1, typename F2>
class Add {
	public:
		Add(F1 f1, F2 f2): f1(f1), f2(f2) {}
		template <typename T>
		T operator () (T x) {
			return f1(x) + f2(x);
		}
		/*template <typename T>
		auto operator () (T x) -> typename std::enable_if<std::is_invocable<F1>::value && std::is_invocable<F2>::value, T>::type {
			T result = f1(x) + f2(x);
			std::cout << result << std::endl; //temporary
			return result;
		}
		template <typename T>
		auto operator () (T x) -> typename std::enable_if<!std::is_same<typename std::result_of<F1(T)>::type, T>::value && std::is_same<typename std::result_of<F2(T)>, T>::value, T>::type {
			T result = f1 + f2(x);
			std::cout << result << std::endl; //temporary
			return result;
		}
		template <typename T>
		auto operator () (T x) -> typename std::enable_if<std::is_same<typename std::result_of<F1(T)>::type, T>::value && !std::is_same<typename std::result_of<F2(T)>, T>::value, T>::type {
			T result = f1(x) + f2;
			std::cout << result << std::endl; //temporary
			return result;
		}*/

	private:
		F1 f1;
		F2 f2;
};

template <typename F1, typename F2>
Add<F1, F2> operator + (F1 f1, F2 f2) {
	return Add<F1, F2>(f1, f2);
}

/*template <typename C, typename F2>
Add<Constant<C>, F2> operator + (C c, F2 f2) {
	return Add<Constant<C>, F2>(c, f2);
}

template <typename F1, typename C>
Add<F1, Constant<C>> operator + (F1 f1, C c) {
	return Add<F1, Constant<C>>(f1, c);
}*/

template <typename F1, typename F2>
class Subtract {
	public:
		Subtract(F1 f1, F2 f2): f1(f1), f2(f2) {}
		template <typename T>
		T operator () (T x) {
			return f1(x) - f2(x);
		}

	private:
		F1 f1;
		F2 f2;
};

template <typename F1, typename F2>
Subtract<F1, F2> operator - (F1 f1, F2 f2) {
	return Subtract<F1, F2>(f1, f2);
}

template <typename F>
class Print {
	public:
		Print(std::ostream& cout, F f): cout(cout), f(f) {}
		template <typename T>
		std::ostream& operator() (T x) {
			return cout << x;
		}

	private:
		std::ostream& cout;
		F f;
};

template <typename F>
Print<F> operator << (std::ostream& cout, F f) {
	return Print<F>(cout, f);
}

template <typename F1, typename F2>
class RePrint {
	public:
		RePrint(F1 f1, F2 f2): f1(f1), f2(f2) {}
		template <typename T>
		std::ostream& operator() (T x) {
			return f1(x).put(f2);
		}

	private:
		F1 f1;
		F2 f2;
};

template <typename F1, typename F2>
RePrint<F1, F2> operator << (F1 f1, F2 f2) {
	return RePrint<F1, F2>(f1, f2);
}
