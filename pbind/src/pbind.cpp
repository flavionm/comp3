#include <tuple>
#include <type_traits>

template <typename F, typename ...Args1>
class Bind {
private:
    F f;
    std::tuple<Args1...> args1;

public:
    Bind( F f, Args1... args1 ): f(f), args1(args1...) {}
    Bind( F f, std::tuple<Args1...> args1 ): f(f), args1(args1) {}

    template <typename ...Args2>
    auto operator()( Args2... args2 ) {
	if constexpr( std::is_invocable_v< F, Args1..., Args2... > )
	  return std::apply( f, std::tuple_cat( args1, std::tuple{args2...} ) );
	else
	  return Bind<F,Args1...,Args2...>{ f, std::tuple_cat( args1, std::tuple{args2...} ) };
    }
};

template <typename F, typename ...Args1>
auto bind( F f, Args1... args1 ) {
  return Bind{ f, args1... };
}
