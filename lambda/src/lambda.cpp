template <typename V, typename F>
void operator | (V iterable, F function) {
	for (auto x : iterable)
		function(x);
}

template <typename T, int S, typename F>
void operator | (T(& array)[S], F function) {
	for (int i = 0; i < S; i++)
		function(array[i]);
}
