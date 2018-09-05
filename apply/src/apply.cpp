#include <vector>

template <typename T, typename T2>
auto apply(const std::vector<T>& v, T2 func) -> std::vector<decltype(func(v[0]))> {
    std::vector<decltype(func(v[0]))> v2;
    for (auto n : v) {
        v2.push_back(func(n));
    }
    return v2;
}
