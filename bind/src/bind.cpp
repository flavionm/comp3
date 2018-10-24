#include <tuple>

template <typename F, typename... A>
class Bind {
	public:
		Bind(F f, A... args): f(f), args(args...) {}
		template <typename... R>
		auto operator () (R... rem) {
			std::tuple<R...> t_rem (rem...);
			auto t = std::tuple_cat(args, t_rem);
			return std::apply(f, t);
		}

	private:
		F f;
		std::tuple<A...> args;
};

template <typename F, typename... A>
Bind<F, A...> bind (F f, A... a) {
	return Bind<F, A...>(f, a...);
}
