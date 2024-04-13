#include <iostream>
#include <fstream>

#include <rational.hpp> 
#include <table.hpp>

int main(int argc, char* argv[]) 
{
    size_t rows = 0;
    size_t columns = 0;
    int tmp = 0;

    std::fstream test("./test.txt");

    test >> rows >> columns;
    nol0n::Table table(++rows, ++columns);

    for (size_t j = 0; j < columns - 1; ++j) {
        test >> tmp;
        table(0, j) = nol0n::rational(tmp);
    }
    table(0, columns) = nol0n::rational{};

    for (size_t i = 1; i < rows; ++i) {
        for (size_t j = 0; j < columns; ++j) {
            test >> tmp;
            table(i, j) = nol0n::rational(tmp);
        }
    }

    std::cout << table << "\n\n";

    table.makeVarBasicInColumn(2, 1);

    std::cout << table << "\n\n";

    return 0;
}