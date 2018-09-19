#include <cmath>
#include <exception>
#include <string>
#include <sstream>

class X {
	public:
		double operator () (double x) {
			return x;
		}
		double dx (double x) {
			x++;

			return 1;
		}
		std::string str () const {
			return "x";
		}
		std::string dx_str () const {
			return "1";
		}
};

class C {
	public:
		C (double c): c(c) {}
		double operator () (double x) {
			x++;

			return c;
		}
		double dx (double x) {
			x++;

			return 0;
		}
		std::string str () const {
			std::stringstream s;

			s << c;

			return s.str();
		}
		std::string dx_str () const {
			return "0";
		}

	private:
		double c;
};

template <typename F1, typename F2>
class Add {
	public:
		Add (F1 f1, F2 f2): f1(f1), f2(f2) {}
		double operator () (double x) {
			return f1(x) + f2(x);
		}
		double dx (double x) {
			return f1.dx(x) + f2.dx(x);
		}
		std::string str () const {
			std::stringstream s;

			s << '(' << f1.str() << ") + (" << f2.str() << ')';

			return s.str();
		}
		std::string dx_str () const {
			std::stringstream s;

			s << '(' << f1.dx_str() << ") + (" << f2.dx_str() << ')';

			return s.str();
		}

	private:
		F1 f1;
		F2 f2;
};

template <typename F1, typename F2>
Add<F1,F2> operator + (F1 f1, F2 f2) {
   return Add<F1,F2>(f1, f2);
}

template <typename F2>
Add<C,F2> operator + (double n, F2 f2) {
   return Add<C,F2>(n, f2);
}

template <typename F1>
Add<F1,C> operator + (F1 f1, double n) {
   return Add<F1,C>(f1, n);
}

template <typename F1, typename F2>
class Subtract {
	public:
		Subtract (F1 f1, F2 f2): f1(f1), f2(f2) {}
		double operator () (double x) {
			return f1(x) - f2(x);
		}
		double dx (double x) {
			return f1.dx(x) - f2.dx(x);
		}
		std::string str () const {
			std::stringstream s;

			s << '(' << f1.str() << ") - (" << f2.str() << ')';

			return s.str();
		}
		std::string dx_str () const {
			std::stringstream s;

			s << '(' << f1.dx_str() << ") - (" << f2.dx_str() << ')';

			return s.str();
		}

	private:
		F1 f1;
		F2 f2;
};

template <typename F1, typename F2>
Subtract<F1,F2> operator - (F1 f1, F2 f2) {
   return Subtract<F1,F2>(f1, f2);
}

template <typename F2>
Subtract<C,F2> operator - (double n, F2 f2) {
   return Subtract<C,F2>(n, f2);
}

template <typename F1>
Subtract<F1,C> operator - (F1 f1, double n) {
   return Subtract<F1,C>(f1, n);
}

template <typename F1, typename F2>
class Multiply {
	public:
		Multiply (F1 f1, F2 f2): f1(f1), f2(f2) {}
		double operator () (double x) {
			return f1(x) * f2(x);
		}
		double dx (double x) {
			return f1.dx(x)*f2(x) + f2.dx(x)*f1(x);
		}

	private:
		F1 f1;
		F2 f2;
};

template <typename F1, typename F2>
Multiply<F1,F2> operator * (F1 f1, F2 f2) {
   return Multiply<F1,F2>(f1, f2);
}

template <typename F2>
Multiply<C,F2> operator * (double n, F2 f2) {
   return Multiply<C,F2>(n, f2);
}

template <typename F1>
Multiply<F1,C> operator * (F1 f1, double n) {
   return Multiply<F1,C>(f1, n);
}

template <typename F1, typename F2>
class Divide {
	public:
		Divide (F1 f1, F2 f2): f1(f1), f2(f2) {}
		double operator () (double x) {
			return f1(x) / f2(x);
		}
		double dx (double x) {
			return (f1.dx(x)*f2(x) - f2.dx(x)*f1(x)) / (f2(x)*f2(x));
		}

	private:
		F1 f1;
		F2 f2;
};

template <typename F1, typename F2>
Divide<F1,F2> operator / (F1 f1, F2 f2) {
   return Divide<F1,F2>(f1, f2);
}

template <typename F2>
Divide<C,F2> operator / (double n, F2 f2) {
   return Divide<C,F2>(n, f2);
}

template <typename F1>
Divide<F1,C> operator / (F1 f1, double n) {
   return Divide<F1,C>(f1, n);
}

template <typename F>
class Exponential {
	public:
		Exponential (F f): f(f) {}
		double operator () (double x) {
			return std::exp(f(x));
		}
		double dx (double x) {
			return std::exp(f(x))*f.dx(x);
		}

	private:
		F f;
};

template <typename F>
Exponential<F> exp (F f) {
   return Exponential<F>(f);
}

template <typename F>
class Logarithm {
	public:
		Logarithm (F f): f(f) {}
		double operator () (double x) {
			return std::log(f(x));
		}
		double dx (double x) {
			return 1 / f(x) * f.dx(x);
		}

	private:
		F f;
};

template <typename F>
Logarithm<F> log (F f) {
   return Logarithm<F>(f);
}

template <typename F>
class Sine {
	public:
		Sine (F f): f(f) {}
		double operator () (double x) {
			return std::sin(f(x));
		}
		double dx (double x) {
			return std::cos(f(x)) * f.dx(x);
		}

	private:
		F f;
};

template <typename F>
Sine<F> sin (F f) {
   return Sine<F>(f);
}

template <typename F>
class Cosine {
	public:
		Cosine (F f): f(f) {}
		double operator () (double x) {
			return std::cos(f(x));
		}
		double dx (double x) {
			return -std::sin(f(x)) * f.dx(x);
		}

	private:
		F f;
};

template <typename F>
Cosine<F> cos (F f) {
   return Cosine<F>(f);
}

template <typename F>
class Power {
	public:
		Power(F f, int p): f(f), p(p) {};
		double operator() (double x) {
			return std::pow(f(x), p);
		}
		double dx (double x) {
			return p * std::pow(f(x), p - 1) * f.dx(x);
		}

	private:
		F f;
		int p;
};

template <typename F>
Power<F> operator ->* (F f, int p) {
	return Power<F>(f, p);
}
