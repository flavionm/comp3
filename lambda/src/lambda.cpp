template <typename V, typename F>
void operator | (V iterable, F function) {
	for (auto x : iterable)
		function(x);
}

template<typename T, int S>
int array_size(T(& t)[S]) {
	return S;
}
