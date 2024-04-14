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
    Table();
    Table(size_t, size_t);
    ~Table();

    size_t getRows();
    size_t getColumns();

    int readFile(const char[], bool = false);

    void columnZeroing(size_t, size_t);
    void rowZeroing(size_t, size_t);

    rational& operator() (size_t, size_t);
    const rational operator() (size_t, size_t) const;

    friend std::ostream& operator<<(std::ostream&, const Table&);
};

} // namespace nol0n
