#include <iostream>
#include <iomanip>
#include <vector>
#include <random>

#include <rational.hpp>
#include <table.hpp>
#include <lp_algs.hpp>

int main(int argc, char *argv[])
{
    obv::Table table;
    
    table.readFile("./test.txt");
    obv::lpalgs::integerCuttingPlane(table);
    std::cout << "\n-- intGomory result --\n" << table << "\n\n";

    table.readFile("./test.txt");
    obv::lpalgs::simplexMethod(table, true);
    obv::lpalgs::cuttingPlane(table, true);
    std::cout << "\n-- Gomory result --\n" << table << "\n\n";

    std::cout << "press ENTER for exit";
    std::cin.get();
    return 0;
}
