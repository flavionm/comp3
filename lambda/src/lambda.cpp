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
auto operator | (V iterable, F function) -> typename std::enable_if<std::is_same<decltype(function(iterable[0])), void>::value, void>::type {
	for (auto x : iterable)
		function(x);
}

template <typename V, typename F>
auto operator | (V iterable, F function) -> typename std::enable_if<!std::is_same<decltype(function(iterable[0])), bool>::value && !std::is_same<decltype(function(iterable[0])), void>::value, std::vector<decltype(function(iterable[0]))>>::type {
	std::vector<decltype(function(iterable[0]))> result;
	for (auto x : iterable)
		result.push_back(function(x));
	return result;
}

template <typename T, int S, typename F>
auto operator | (T(& array)[S], F function) -> typename std::enable_if<std::is_same<decltype(function(array[0])), bool>::value, std::vector<T>>::type {
	std::vector<T> filtered;
	for (int i = 0; i < S; i++)
		if (function(array[i])) filtered.push_back(array[i]);
	return filtered;
}

template <typename T, int S, typename F>
auto operator | (T(& array)[S], F function) -> typename std::enable_if<std::is_same<decltype(function(array[0])), void>::value, void>::type {
	for (int i = 0; i < S; i++)
		function(array[i]);
}

template <typename T, int S, typename F>
auto operator | (T(& array)[S], F function) -> typename std::enable_if<!std::is_same<decltype(function(array[0])), bool>::value && !std::is_same<decltype(function(array[0])), void>::value, std::vector<decltype(function(array[0]))>>::type {
	std::vector<decltype(function(array[0]))> result;
	for (int i = 0; i < S; i++)
			result.push_back(function(array[i]));
	return result;
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
			(void) x; //x is needed for this method to be called by the operations
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

	private:
		F1 f1;
		F2 f2;
};

template <typename F1, typename F2>
auto operator + (F1 f1, F2 f2) -> typename std::enable_if<!std::is_scalar<F1>::value && !std::is_scalar<F2>::value, Add<F1, F2>>::type {
	return Add<F1, F2>(f1, f2);
}

template <typename C, typename F2>
auto operator + (C c, F2 f2) -> typename std::enable_if<std::is_scalar<C>::value && !std::is_scalar<F2>::value, Add<Constant<C>, F2>>::type {
	return Add<Constant<C>, F2>(c, f2);
}

template <typename F1, typename C>
auto operator + (F1 f1, C c) -> typename std::enable_if<!std::is_scalar<F1>::value && std::is_scalar<C>::value, Add<F1, Constant<C>>>::type {
	return Add<F1, Constant<C>>(f1, c);
}

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
auto operator - (F1 f1, F2 f2) -> typename std::enable_if<!std::is_scalar<F1>::value && !std::is_scalar<F2>::value, Subtract<F1, F2>>::type {
	return Subtract<F1, F2>(f1, f2);
}

template <typename C, typename F2>
auto operator - (C c, F2 f2) -> typename std::enable_if<std::is_scalar<C>::value && !std::is_scalar<F2>::value, Subtract<Constant<C>, F2>>::type {
	return Subtract<Constant<C>, F2>(c, f2);
}

template <typename F1, typename C>
auto operator - (F1 f1, C c) -> typename std::enable_if<!std::is_scalar<F1>::value && std::is_scalar<C>::value, Subtract<F1, Constant<C>>>::type {
	return Subtract<F1, Constant<C>>(f1, c);
}

template <typename F>
class Print {
	public:
		Print(std::ostream& cout, F f): cout(cout), f(f) {}
		template <typename T>
		std::ostream& operator() (T x) {
			return cout << f(x);
		}

	private:
		std::ostream& cout;
		F f;
};

template <typename F>
auto operator << (std::ostream& cout, F f) -> typename std::enable_if<!std::is_scalar<F>::value, Print<F>>::type {
	return Print<F>(cout, f);
}

template <typename C>
auto operator << (std::ostream& cout, C c) -> typename std::enable_if<std::is_scalar<C>::value, Print<Constant<C>>>::type {
	return Print<Constant<C>>(cout, c);
}

template <typename F1, typename F2>
class RePrint {
	public:
		RePrint(F1 f1, F2 f2): f1(f1), f2(f2) {}
		template <typename T>
		T operator() (T x) {
			f1(x).put(f2(x));
			return x;
		}

	private:
		F1 f1;
		F2 f2;
};

template <typename F1, typename F2>
auto operator << (F1 f1, F2 f2) -> typename std::enable_if<!std::is_scalar<F2>::value, RePrint<F1, F2>>::type {
	return RePrint<F1, F2>(f1, f2);
}

template <typename F1, typename C>
auto operator << (F1 f1, C c) -> typename std::enable_if<std::is_scalar<C>::value, RePrint<F1, Constant<C>>>::type {
	return RePrint<F1, Constant<C>>(f1, c);
}

template <typename F1, typename F2>
class Multiply {
	public:
		Multiply(F1 f1, F2 f2): f1(f1), f2(f2) {}
		template <typename T>
		T operator () (T x) {
			return f1(x) * f2(x);
		}

	private:
		F1 f1;
		F2 f2;
};

template <typename F1, typename F2>
auto operator * (F1 f1, F2 f2) -> typename std::enable_if<!std::is_scalar<F1>::value && !std::is_scalar<F2>::value, Multiply<F1, F2>>::type {
	return Multiply<F1, F2>(f1, f2);
}

template <typename C, typename F2>
auto operator * (C c, F2 f2) -> typename std::enable_if<std::is_scalar<C>::value && !std::is_scalar<F2>::value, Multiply<Constant<C>, F2>>::type {
	return Multiply<Constant<C>, F2>(c, f2);
}

template <typename F1, typename C>
auto operator * (F1 f1, C c) -> typename std::enable_if<!std::is_scalar<F1>::value && std::is_scalar<C>::value, Multiply<F1, Constant<C>>>::type {
	return Multiply<F1, Constant<C>>(f1, c);
}

template <typename F1, typename F2>
class Divide {
	public:
		Divide(F1 f1, F2 f2): f1(f1), f2(f2) {}
		template <typename T>
		T operator () (T x) {
			return f1(x) / f2(x);
		}

	private:
		F1 f1;
		F2 f2;
};

template <typename F1, typename F2>
auto operator / (F1 f1, F2 f2) -> typename std::enable_if<!std::is_scalar<F1>::value && !std::is_scalar<F2>::value, Divide<F1, F2>>::type {
	return Divide<F1, F2>(f1, f2);
}

template <typename C, typename F2>
auto operator / (C c, F2 f2) -> typename std::enable_if<std::is_scalar<C>::value && !std::is_scalar<F2>::value, Divide<Constant<C>, F2>>::type {
	return Divide<Constant<C>, F2>(c, f2);
}

template <typename F1, typename C>
auto operator / (F1 f1, C c) -> typename std::enable_if<!std::is_scalar<F1>::value && std::is_scalar<C>::value, Divide<F1, Constant<C>>>::type {
	return Divide<F1, Constant<C>>(f1, c);
}

template <typename F1, typename F2>
class Module {
	public:
		Module(F1 f1, F2 f2): f1(f1), f2(f2) {}
		template <typename T>
		T operator () (T x) {
			return f1(x) % f2(x);
		}

	private:
		F1 f1;
		F2 f2;
};

template <typename F1, typename F2>
auto operator % (F1 f1, F2 f2) -> typename std::enable_if<!std::is_scalar<F1>::value && !std::is_scalar<F2>::value, Module<F1, F2>>::type {
	return Module<F1, F2>(f1, f2);
}

template <typename C, typename F2>
auto operator % (C c, F2 f2) -> typename std::enable_if<std::is_scalar<C>::value && !std::is_scalar<F2>::value, Module<Constant<C>, F2>>::type {
	return Module<Constant<C>, F2>(c, f2);
}

template <typename F1, typename C>
auto operator % (F1 f1, C c) -> typename std::enable_if<!std::is_scalar<F1>::value && std::is_scalar<C>::value, Module<F1, Constant<C>>>::type {
	return Module<F1, Constant<C>>(f1, c);
}

template <typename F1, typename F2>
class Comparison {
	public:
		Comparison(F1 f1, F2 f2): f1(f1), f2(f2) {}
		template <typename T>
		bool operator() (T x) {
			return f1(x) == f2(x);
		}

	private:
		F1 f1;
		F2 f2;
};

template <typename F1, typename F2>
auto operator == (F1 f1, F2 f2) -> typename std::enable_if<!std::is_scalar<F1>::value && !std::is_scalar<F2>::value, Comparison<F1, F2>>::type {
	return Comparison<F1, F2>(f1, f2);
}

template <typename C, typename F2>
auto operator == (C c, F2 f2) -> typename std::enable_if<std::is_scalar<C>::value && !std::is_scalar<F2>::value, Comparison<Constant<C>, F2>>::type {
	return Comparison<Constant<C>, F2>(c, f2);
}

template <typename F1, typename C>
auto operator == (F1 f1, C c) -> typename std::enable_if<!std::is_scalar<F1>::value && std::is_scalar<C>::value, Comparison<F1, Constant<C>>>::type {
	return Comparison<F1, Constant<C>>(f1, c);
}
