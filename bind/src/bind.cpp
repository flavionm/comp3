#include <iostream>
#include <tuple>

template <typename F, typename... A>
class Bind;

template <typename F, typename... A>
Bind<F, A...> bind (F f, A... a);

template <typename F, typename... A>
class Bind {
	public:
		Bind(F f, A... args): f(f), args(args...) {}
		template <typename... R>
		auto operator () (R... rem) {
			std::tuple<F> func (f);
			std::tuple<R...> t_rem (rem...);
			auto t = std::tuple_cat(func, args, t_rem);
			return std::apply(bind<F, A..., R...>, t);
		}
		auto call () const {
			return std::apply(f, args);
		}

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
