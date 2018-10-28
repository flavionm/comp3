#include <iostream>
#include <tuple>

template <typename F, typename... A>
class Bind;

template <typename F, typename... A>
Bind<F, A...> bind (F f, A... a);

template <typename F, typename... A, typename... B>
Bind<F, A..., B...> bind (Bind<F, A...> b, B... args);

template <typename F, typename... A>
class Bind {
	public:
		Bind(F f, A... args): f(f), args(args...) {}
		Bind(F f, std::tuple<A...> args): f(f), args(args) {}
		template <typename... R>
		Bind<F, A..., R...> operator () (R... rem) {
			std::tuple<R...> t_rem (rem...);
			std::tuple<A..., R...> t = std::tuple_cat(args, t_rem);
			if constexpr(std::is_invocable<F, A..., R...>::value)
				std::apply(f, t);
			return Bind<F, A..., R...>(f, t);
		}
		auto call () const {
			return std::apply(f, args);
		}
		template <typename _F, typename... _A, typename... B>
		friend Bind<_F, _A..., B...> bind (Bind<_F, _A...> b, B... args);

	private:
		F f;
		std::tuple<A...> args;
};

template <typename F, typename... A>
std::ostream& operator << (std::ostream& cout, const Bind<F, A...>& bind) {
	return cout << bind.call();
}

template <typename F, typename... A>
Bind<F, A...> bind (F f, A... a) {
	return Bind<F, A...>(f, a...);
}

template <typename F, typename... A, typename... B>
Bind<F, A..., B...> bind (Bind<F, A...> b, B... args) {
	auto t_a = std::tuple(args...);
	auto t = std::tuple_cat(b.args, t_a);
	return Bind<F, A..., B...>(b.f, t);
}
