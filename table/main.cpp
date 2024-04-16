#include <iostream>
#include <fstream>

#include <rational.hpp>
#include <table.hpp>

int main(int argc, char *argv[])
{
    obv::Table table{};
    table.readFile("./test.txt");

    std::cout << table << "\n\n";

    table.rowZeroing(4, 2);

    std::cout << table << "\n\n";

    return 0;
}
