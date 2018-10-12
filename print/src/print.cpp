#include <iostream>
#include <initializer_list>
#include <string>
#include <sstream>

class Pair {
    public:
        template <typename A, typename B>
        Pair(A a, B b) {
            std::stringstream ssa;
            std::stringstream ssb;
            ssa << a;
            ssb << b;
            sa = ssa.str();
            sb = ssb.str();
        }

        std::string sa;
        std::string sb;
};

void print (std::initializer_list<Pair> list) {
    for (auto p : list)
        std::cout << p.sa << " = " << p.sb << std::endl;
}
