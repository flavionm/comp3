#include <tuple>

template <typename F, typename... A>
class Bind {
	public:
		Bind(F f, A... args): f(f), args(args...) {}
	
	private:
		F f;
		std::tuple<A...> args;
};

template <typename F, typename... A>
Bind<F, A...> bind (F f, A... a) {
	return Bind<F, A...>(f, a...);
}