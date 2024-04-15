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

    nol0n::Table table;
    table.readFile("./test.txt");

    try
    {
        nol0n::lpalgs::simplexMethod(table, true);
        std::cout << "--------- Gomery Cutting Plane ----------\n\n\n";
        nol0n::lpalgs::cuttingPlane(table, true);
    }
    catch (const char *err)
    {
        std::cerr << err;
    }

    std::cout << table << "\n\n";

    return 0;
}
