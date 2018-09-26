template <typename V, typename F>
void operator | (V iterable, F function) {
	for (auto x : iterable)
		function(x);
}
