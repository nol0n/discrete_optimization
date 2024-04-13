#pragma once

#include <rational.hpp>
#include <iostream>

namespace nol0n 
{

class Table {
private:
    rational* data;
    size_t _rows;
    size_t _columns;
public:
    Table(size_t, size_t);
    ~Table();

    void makeVarBasicInColumn(size_t row, size_t column);

    rational& operator() (size_t row, size_t column);
    const rational operator() (size_t row, size_t column) const;

    friend std::ostream& operator<<(std::ostream& outs, const Table& table);
};

} // namespace nol0n