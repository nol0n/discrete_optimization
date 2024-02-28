#include <iostream>
#include <lp_methods.hpp>

int main(int argc, char* argv[]) {
    std::cout << lp_methods::simplex_method("./test.txt", true);
    return 0;
}