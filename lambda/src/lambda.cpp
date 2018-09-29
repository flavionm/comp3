#include <typeinfo>
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

template <typename T, int S, typename F>
void operator | (T(& array)[S], F function) {
	for (int i = 0; i < S; i++)
		function(array[i]);
}
