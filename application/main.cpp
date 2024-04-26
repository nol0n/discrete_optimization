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
    std::cout << table << "\n----table\n\n";
    obv::lpalgs::integerCuttingPlane(table);
    std::cout << table << "\n----intGomory\n\n";

    table.readFile("./test.txt");
    obv::lpalgs::simplexMethod(table);
    std::cout << table << "\n----simplex\n\n";
    obv::lpalgs::cuttingPlane(table, true);
    std::cout << table << "\n----Gomory\n\n";


    std::cout << "press ENTER for exit";
    std::cin.get();
    return 0;
}
