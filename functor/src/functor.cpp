class X {
	public:
		double operator () (double x) {
			return x;
		}
		double dx (double x) {
			return 1;
		}
};

class C {
	public:
		C (double c): c(c) {}
		double operator () (double x) {
			return c;
		}
		double dx (double x) {
			return 0;
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

	private:
		F1 f1;
		F2 f2;
};

template <typename F1, typename F2>
Add<F1,F2> operator + ( F1 f1, F2 f2 ) {
   return Add<F1,F2>( f1, f2 );
}

template <typename F2>
Add<C,F2> operator + ( double n, F2 f2 ) {
   return Add<C,F2>( n, f2 );
}

template <typename F1>
Add<F1,C> operator + ( F1 f1, double n ) {
   return Add<F1,C>( f1, n );
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
Multiply<F1,F2> operator * ( F1 f1, F2 f2 ) {
   return Multiply<F1,F2>( f1, f2 );
}

template <typename F2>
Multiply<C,F2> operator * ( double n, F2 f2 ) {
   return Multiply<C,F2>( n, f2 );
}

template <typename F1>
Multiply<F1,C> operator * ( F1 f1, double n ) {
   return Multiply<F1,C>( f1, n );
}
