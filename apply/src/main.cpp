#include <iostream>
#include <vector>
#include <math.h>
#include "apply.cpp"

double f(int i) {
    return double(i*i);
}

int main() {
    std::vector<double> v = {0, 5, 4, 2};

    auto v2 = apply(v, sin);

    for (auto n : v2) {
        std::cout << n << std::endl;
    }
}
