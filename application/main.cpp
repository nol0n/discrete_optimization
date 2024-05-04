#include <iostream>
#include <iomanip>
#include <vector>
#include <random>

#include <rational.hpp>
#include <table.hpp>
#include <lp_algs.hpp>
#include <lp_algs_dev.hpp>

int main(int argc, char *argv[])
{
    obv::Table table;
    
    // table.readFile("./test.txt");
    // obv::lpalgs::integerCuttingPlane(table);
    // std::cout << table(0, 0) << "\n";

    // table.readFile("./test.txt");
    // obv::lpalgs::simplexMethod(table);
    // obv::lpalgs::cuttingPlane(table);
    // std::cout << table(0, 0) << "\n";

    // lp_algs_dev with some debug output

    // table.readFile("./test.txt");
    // obv::lpalgs_dev::integerCuttingPlane(table, true);

    table.readFile("./test.txt");
    obv::lpalgs_dev::simplexMethod(table);
    
    for (int j = 0; j < table.getColumns(); ++j)
    {
        table(0, j) *= -1;
    }

    obv::lpalgs_dev::cuttingPlane(table, true);

    std::cout << "press ENTER for exit";
    std::cin.get();

    return 0;
}
