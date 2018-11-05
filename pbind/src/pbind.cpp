#include <tuple>
#include <type_traits>
#include <utility>
#include <iostream>

class PlaceHolder {};

template <typename T>
constexpr auto head (T t) {
	return std::get<0>(t);
}

template <typename T, std::size_t... I>
constexpr auto __tail (T t, std::index_sequence<I...>) {
	return std::tuple (std::get<I+1>(t)...);
}

template <typename... Args>
constexpr auto tail (std::tuple<Args...> t) {
	return __tail (t, std::make_index_sequence<sizeof...(Args) - 1>{});
}

template <typename... Args1, typename... Args2, typename TF>
constexpr auto __merge (std::tuple<Args1...> t1, std::tuple<Args2...> t2, TF tf) {
	if constexpr (sizeof...(Args1) == 0)
		return std::tuple_cat(tf, t2);
	if constexpr (!std::is_same<decltype(head(t1)), PlaceHolder)
		return merge(tail(t1), t2, tf);
	if constexpr (std::is_same<decltype(head(t1)), PlaceHolder)
		return merge(tail(t1), tail(t2), tuple_cat(tf, std::tuple(__)))
	if
}

template <typename T1, typename T2>
auto merge (T1 t1, T2 t2) {
	return __merge (t1, t2, std::tuple<>{});
}

template <int S, typename T1, typename T2, typename... T3>
auto finish(T1 args1, T2 args2, std::tuple<T3...> args_f) {
	constexpr int SIZE = std::tuple_size<T2>::value > std::tuple_size<T1>::value ? std::tuple_size<T2>::value : std::tuple_size<T1>::value;
	constexpr int I = SIZE - S;
	if constexpr (I == 0)
		return args_f;
	else if constexpr (std::tuple_size<T1>::value > std::tuple_size<T2>::value)
		return finish<S - 1, T1, T2, T3..., decltype(std::get<I>(args1))>(args1, args2, std::tuple_cat(args_f, std::tuple(std::get<I>(args1))));
	else
		return finish<S - 1, T1, T2, T3..., decltype(std::get<I>(args2))>(args1, args2, std::tuple_cat(args_f, std::tuple(std::get<I>(args2))));
}

template <int S, typename T1, typename T2, typename... T3>
auto replace(T1 args1, T2 args2, std::tuple<T3...> args_f) {
	constexpr int SIZE = std::tuple_size<T2>::value <= std::tuple_size<T1>::value ? std::tuple_size<T2>::value : std::tuple_size<T1>::value;
	constexpr int I = SIZE - S;
	if constexpr (I == 0) {
		constexpr int SIZE2 = std::tuple_size<T2>::value > std::tuple_size<T1>::value ? std::tuple_size<T2>::value : std::tuple_size<T1>::value;
		return finish<SIZE2 - SIZE, T1, T2, T3...>(args1, args2, args_f);
	} else if constexpr (std::is_same<decltype(std::get<I>(args1)), PlaceHolder>::value) {
		return replace<S - 1, T1, T2, T3..., decltype(std::get<I>(args2))>(args1, args2, std::tuple_cat(args_f, std::tuple(std::get<I>(args2))));
	} else {
		return replace<S - 1, T1, T2, T3..., decltype(std::get<I>(args1))>(args1, args2, std::tuple_cat(args_f, std::tuple(std::get<I>(args1))));
	}
}

template <typename F, typename ...Args1>
class Bind {
	private:
		F f;
		std::tuple<Args1...> args1;

	public:
		Bind (F f, Args1... args1): f(f), args1(args1...) {}
		Bind (F f, std::tuple<Args1...> args1): f(f), args1(args1) {}

		template <typename... Args2>
		auto operator() (Args2... args2) {
			auto t_args2 = std::tuple(args2...);
			std::cout << std::tuple_size<std::tuple<Args2...>>::value << std::endl;
			if constexpr (std::is_invocable<F, Args1..., Args2...>::value) {
				return std::apply(f, std::tuple_cat(args1, t_args2));
			} else if constexpr (std::tuple_size<std::tuple<Args2...>>::value <= std::tuple_size<std::tuple<Args1...>>::value) {
				auto t2 = replace<std::tuple_size<std::tuple<Args2...>>::value, std::tuple<Args1...>, std::tuple<Args2...>>(args1, t_args2, std::tuple<>());
				return Bind {f, t2};
			} else {
				auto t2 = replace<std::tuple_size<std::tuple<Args1...>>::value, std::tuple<Args1...>, std::tuple<Args2...>>(args1, t_args2, std::tuple<>());
				return Bind {f, t2};
			}
		}

		void print () {
			std::cout << std::tuple_size<std::tuple<Args1...>>::value << std::endl;
		}
};

template <typename F, typename ...Args1>
auto bind( F f, Args1... args1 ) {
	return Bind {f, args1...};
}
