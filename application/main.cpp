#include <iostream>
#include <iomanip>
#include <vector>
#include <random>

#include <lp_algs.hpp>
#include <rational.hpp>
#include <lp_methods.hpp>
#include <table.hpp>

int main(int argc, char *argv[])
{
    // lp_methods::two_phase_method("./test.txt", true);
    // lp_methods::simplex_method("./test.txt", true);
    // lp_methods::backpack_max("./backpack.txt", true);

    obv::Table table;
    table.readFile("./test.txt");

    obv::lpalgs::simplexMethod(table);
    obv::lpalgs::cuttingPlane(table, true);
    std::cout << table << "\n\n";

    table.readFile("./test.txt");
    obv::lpalgs::integerCuttingPlane(table);
    std::cout << table << "\n\n";

    return 0;
}
