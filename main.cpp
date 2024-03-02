#include <iostream>
#include <lp_methods.hpp>

#include <string>
#include <fstream>
#include <vector>

#include <iomanip>

int main(int argc, char* argv[]) {
    // lp_methods::two_phase_method("./test.txt", true);
    lp_methods::simplex_method("./test.txt", true);

    return 0;
}