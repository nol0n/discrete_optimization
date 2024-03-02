#include <iostream>
#include <iomanip>
#include <lp_methods.hpp>

int main(int argc, char* argv[]) {
    // lp_methods::two_phase_method("./test.txt", true);
    // lp_methods::simplex_method("./test.txt", true);
    lp_methods::backpack_max("./backpack.txt", true);

    return 0;
}