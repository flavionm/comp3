#include <vector>
#include <iostream>

template <long long L, long long C>
class Matriz {
	public:
		Matriz(): m(new double[L*C]) {}
		Matriz(const Matriz& old): m(new double[L*C]) {
			for (int i = 0; i < L*C; i++)
				m[i] = old.m[i];
		}
		Matriz& operator = (const Matriz& old) {
			for (int i = 0; i < L*C; i++)
				m[i] = old.m[i];
			return *this;
		}
		const double* operator[] (long long i) const{
			return (double*) m + C*i;
		}
		double* operator[] (long long i) {
			return (double*) m + C*i;
		}
		long long nLin() {
			return L;
		}
		long long nCol() {
			return C;
		}

	private:
		double *m;
};

template <long long L, long long C>
Matriz<L, C> operator + (Matriz<L, C> a, Matriz<L, C> b) {
	Matriz<L, C> r;
	for (long long i = 0; i < L; i++)
		for (long long j = 0; j < C; j++)
			r[i][j] = a[i][j] + b[i][j];
	return r;
}

template<long long L, long long LC, long long C>
Matriz<L, C> multiply (const Matriz<L, LC>& a, const Matriz<LC, C>& b) {
	Matriz<L, C> r;
	for (long long i = 0; i < L; i++) {
		for (long long j = 0; j < C; j++) {
			r[i][j] = 0;
			for (long long k = 0; k < LC; k++) {
				r[i][j] += a[i][k] * b[k][j];
			}
		}
	}
	return r;
}

template <long long L, long long LC, long long C>
class Otimizador {
	public:
		Otimizador (const Matriz<L, LC>& a, const Matriz<LC, C>& b): a(a), b(b), done(false) {}
		template <long long F>
		Matriz<L, F> otimize (const Matriz<C, F>& c) const {
			Matriz<L, F> r;
			if (L * C < LC * F || done) {
				std::cout << "(a*b)*c" << std::endl;
				r = multiply(multiply(a, b), c);
			} else {
				std::cout << "a*(b*c)" << std::endl;
				r = multiply(a, multiply(b, c));
			}
			return r;
		}
		void finish() {
			if (!done) {
				r = multiply(a, b);
				done = true;
			}
		}
		operator Matriz<L, C> () {
			return multiply(a, b);
		}
		long long nLin() const {
			return L;
		}
		long long nCol() const {
			return C;
		}
		double* operator [] (long long i) {
			finish();
			return r[i];
		}

	private:
		Matriz<L, LC> a;
		Matriz<LC, C> b;
		Matriz<L, C> r;
		bool done;
};

template <long long L, long long LC, long long C>
Otimizador<L, LC, C> operator * (const Matriz<L, LC>& a, const Matriz<LC, C>& b) {
	return Otimizador<L, LC, C> (a, b);
}

template <long long L, long long LC, long long C, long long F>
Matriz<L, F> operator * (const Otimizador<L, LC, C>& a, const Matriz<C, F>& b) {
	return a.otimize(b);
}

template <long long L, long long LC, long long C>
Matriz<L, C> operator + (Otimizador<L, LC, C> a, Matriz<L, C> b) {
	return Matriz<L, C>(a) + b;
}

template <long long L, long long LC, long long C>
Matriz<L, C> operator + (Matriz<L, C> a, Otimizador<L, LC, C> b) {
	return a + Matriz<L, C>(b);
}

template <typename F>
class Bind {
	public:
		Bind (F f): f(f) {}

		template <long long L, long long C>
		Matriz<L, C> operator() (Matriz<L,C> m) const {
			Matriz<L, C> r;
			for (long long i = 0; i < L; i++)
				for (long long j = 0; j < C; j++)
					r[i][j] = f(m[i][j]);
			return r;
		}
		template <long long L, long long LC, long long C>
		Matriz<L, C> operator() (Otimizador<L, LC, C> m) const {
			Matriz<L, C> r;
			auto mr = Matriz<L, C>(m);
			for (long long i = 0; i < L; i++)
				for (long long j = 0; j < C; j++)
					r[i][j] = f(mr[i][j]);
			return r;
		}

	private:
		F f;
};
