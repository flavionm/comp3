#include <cmath>
#include <exception>
#include <iostream>
#include <string>
#include <sstream>

enum {
	P_ADD = 0, P_MULT, P_POWER, P_FUNC, P_CONST
};

struct precedence_string {
	std::string str;
	int precedence;

	precedence_string() {}
	precedence_string(std::string str, int precedence): str(str), precedence(precedence) {}
};

/*std::ostream& operator << (std::ostream& out, const precedence_string& pstr) {
	out << pstr.str;

	return out;
}*/

class X {
	public:
		double operator () (double x) {
			return x;
		}
		double dx (double x) {
			x++;

			return 1;
		}
		precedence_string str () const {
			return precedence_string("x", P_CONST);
		}
		precedence_string dx_str () const {
			return precedence_string("1", P_CONST);
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
		precedence_string str () const {
			std::stringstream s;

			s << c;

			return precedence_string(s.str(), P_CONST);
		}
		precedence_string dx_str () const {
			return precedence_string("0", P_CONST);
		}

	private:
		const double c;
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
		static precedence_string sum_str(precedence_string f1, precedence_string f2) {
			if (f1.str == "0" && f2.str == "0") {
				return precedence_string("0", P_CONST);
			} else if (f1.str != "0" && f2.str != "0") {
				std::stringstream s;
				if (f1.precedence < P_ADD)
					s << "(" << f1.str << ")";
				else
					s << f1.str;
				s << "+";
				if (f2.precedence < P_ADD)
					s << "(" << f2.str << ")";
				else
					s << f2.str;
				return precedence_string(s.str(), P_ADD);
			} else if (f2.str == "0") {
				return f1;
			} else {
				return f2;
			}
		}
		precedence_string str () const {
			return sum_str(f1.str(), f2.str());
		}
		precedence_string dx_str () const {
			return sum_str(f1.dx_str(), f2.dx_str());
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
		static precedence_string sub_str(precedence_string f1, precedence_string f2) {
			if (f1.str == "0" && f2.str == "0") {
				return precedence_string("0", P_CONST);
			} else if (f1.str != "0" && f2.str != "0") {
				std::stringstream s;
				if (f1.precedence < P_ADD)
					s << "(" << f1.str << ")";
				else
					s << f1.str;
				s << "-";
				if (f2.precedence <= P_ADD)
					s << "(" << f2.str << ")";
				else
					s << f2.str;
				return precedence_string(s.str(), P_ADD);
			} else if (f2.str == "0") {
				return f1;
			} else {
				std::stringstream s;
				s << "-";
				if (f2.precedence <= P_ADD)
					s << "(" << f2.str << ")";
				else
					s << f2.str;
				return precedence_string(s.str(), P_ADD);
			}
		}
		precedence_string str () const {
			return sub_str(f1.str(), f2.str());
		}
		precedence_string dx_str () const {
			return sub_str(f1.dx_str(), f2.dx_str());
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
		static precedence_string mul_str(precedence_string f1, precedence_string f2) {
			if (f1.str == "0" || f2.str == "0") {
				return precedence_string("0", P_CONST);
			} else if (f1.str == "1" && f2.str == "1") {
				return precedence_string("1", P_CONST);
			} else if (f1.str != "1" && f2.str != "1") {
				std::stringstream s;
				if (f1.precedence < P_MULT)
					s << "(" << f1.str << ")";
				else
					s << f1.str;
				s << "*";
				if (f2.precedence < P_MULT)
					s << "(" << f2.str << ")";
				else
					s << f2.str;
				return precedence_string(s.str(), P_MULT);
			} else if (f2.str == "1") {
				return f1;
			} else {
				return f2;
			}
		}
		precedence_string str () const {
			return mul_str(f1.str(), f2.str());
		}
		precedence_string dx_str () const {
			precedence_string mult1 = mul_str(f1.dx_str(), f2.str());
			precedence_string mult2 = mul_str(f1.str(), f2.dx_str());

			return Add<F1, F2>::sum_str(mult1, mult2);
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
		static precedence_string pow_str(precedence_string f, int p) {
			if (f.str == "1" || p == 0) {
				return precedence_string("1", P_CONST);
			} else if (f.str == "0") {
				return precedence_string("0", P_CONST);
			} else if (p == 1) {
				return f;
			} else {
				std::stringstream s;
				if (f.precedence <= P_POWER)
					s << "(" << f.str << ")";
				else
					s << f.str;
				s << "^" << p;
				return precedence_string(s.str(), P_POWER);
			}
		}
		precedence_string str () const {
			return pow_str(f.str(), p);
		}
		precedence_string dx_str () const {
			precedence_string old_p = precedence_string(std::to_string(p), P_CONST);
			precedence_string new_p = pow_str(f.str(), p - 1);

			precedence_string pow_dx = Multiply<F, F>::mul_str(old_p, new_p);

			return Multiply<F, F>::mul_str(pow_dx, f.dx_str());
		}

	private:
		F f;
		int p;
};

template <typename F>
Power<F> operator ->* (F f, int p) {
	return Power<F>(f, p);
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
		static precedence_string div_str(precedence_string f1, precedence_string f2) {
			if (f2.str == "0") {
				throw std::overflow_error("Division by zero exception");
			} else if (f1.str == "0") {
				return precedence_string("0", P_CONST);
			} else if (f1.str == "1" && f2.str == "1") {
				return precedence_string("1", P_CONST);
			} else if (f1.str != "1" && f2.str != "1") {
				std::stringstream s;
				if (f1.precedence < P_MULT)
					s << "(" << f1.str << ")";
				else
					s << f1.str;
				s << "/";
				if (f2.precedence <= P_MULT)
					s << "(" << f2.str << ")";
				else
					s << f2.str;
				return precedence_string(s.str(), P_MULT);
			} else if (f2.str == "1") {
				return f1;
			} else {
				std::stringstream s;
				s << "1/";
				if (f2.precedence <= P_MULT)
					s << "(" << f2.str << ")";
				else
					s << f2.str;
				return precedence_string(s.str(), P_MULT);
			}
		}
		precedence_string str () const {
			return div_str(f1.str(), f2.str());
		}
		precedence_string dx_str () const {
			precedence_string mult1 = Multiply<F1, F2>::mul_str(f1.dx_str(), f2.str());
			precedence_string mult2 = Multiply<F1, F2>::mul_str(f1.str(), f2.dx_str());

			precedence_string diff = Subtract<F1, F2>::sub_str(mult1, mult2);

			precedence_string mult_b = Power<F1>::pow_str(f2.str(), 2);

			return div_str(diff, mult_b);
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
		static precedence_string exp_str(precedence_string f) {
			if (f.str == "0") {
				return precedence_string("1", P_CONST);
			} else {
				std::stringstream s;
				s << "exp(" << f.str << ")";
				return precedence_string(s.str(), P_FUNC);
			}
		}
		precedence_string str () const {
			return exp_str(f.str());
		}
		precedence_string dx_str () const {
			precedence_string exp_dx = exp_str(f.str());

			return Multiply<F, F>::mul_str(exp_dx, f.dx_str());
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
		static precedence_string log_str(precedence_string f) {
			if (f.str == "0") {
				throw std::overflow_error("Logarithm of zero exception");
			} else if (f.str == "1") {
				return precedence_string("0", P_CONST);
			} else {
				std::stringstream s;
				s << "log(" << f.str << ")";
				return precedence_string(s.str(), P_FUNC);
			}
		}
		precedence_string str () const {
			return log_str(f.str());
		}
		precedence_string dx_str () const {
			precedence_string one = precedence_string("1", P_CONST);
			precedence_string log_dx = Divide<F, F>::div_str(one, f.str());

			return Multiply<F, F>::mul_str(log_dx, f.dx_str());
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
		std::string str () const {
			std::stringstream s;

			s << "(sin" << f.str() << ')';

			return s.str();
		}
		std::string dx_str () const {
			std::stringstream s;

			s << "((cos" << f.str() << ")*(" << f.dx_str() << "))";

			return s.str();
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
		std::string str () const {
			std::stringstream s;

			s << "(cos" << f.str() << ')';

			return s.str();
		}
		std::string dx_str () const {
			std::stringstream s;

			s << "(((-1)*(sin" << f.str() << "))*(" << f.dx_str() << "))";

			return s.str();
		}

	private:
		F f;
};

template <typename F>
Cosine<F> cos (F f) {
   return Cosine<F>(f);
}
