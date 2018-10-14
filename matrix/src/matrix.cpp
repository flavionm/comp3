template <int L, int C>
class Matriz {
	public:
		const double* operator[] (int i) const{
			return m[i];
		}
		double* operator[] (int i) {
			return m[i];
		}
		int nLin() {
			return L;
		}
		int nCol() {
			return C;
		}

	private:
		double m[L][C];
};

template<int L, int C>
Matriz<L, C> operator + (Matriz<L, C> a, Matriz<L, C> b) {
	Matriz<L, C> r;
	for (int i = 0; i < L; i++)
		for (int j = 0; j < C; j++)
			r[i][j] = a[i][j] + b[i][j];
	return r;
}

/*template <int L, int LC, int C>
Otimizador< ?? > operator * ( const Matriz<L,LC>& a, const Matriz<LC,C>& b ) {
}*/

template <typename F>
class Bind {
	public:
		Bind (F f): f(f) {}
	
		template <int L, int C>
		Matriz<L, C> operator() (const Matriz<L,C>& m) const {
			Matriz<L, C> r;
			for (int i = 0; i < L; i++)
				for (int j = 0; j < C; j++)
					r[i][j] = f(m[i][j]);
			return r;
		}
	
	private:
		F f;
};
