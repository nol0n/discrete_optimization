#include <table.hpp>

namespace nol0n 
{

Table::Table(size_t rows, size_t columns) : _rows(rows), _columns(columns) {
    data = new rational[_rows * _columns]{};
}

Table::~Table() {
    delete[] data;
}

void Table::makeVarBasicInColumn(size_t row, size_t column) {
        column--;
        rational value = data[row * _columns + column];

        for (size_t j = 0; j < _columns; ++j) {
            (*this)(row, j) /= value;
        }

        for (size_t i = 0; i < _rows; ++i) {
            if (i == row) continue;
            
            rational div_coeff = (*this)(i, column);
            for (size_t j = 0; j < _columns; j++) {
                (*this)(i, j) -= (*this)(row, j) * div_coeff;
            }
        }
    }

rational& Table::operator() (size_t row, size_t column) {
    return data[row * _columns + column];
}

const rational Table::operator() (size_t row, size_t column) const {
    return data[row * _columns + column];
}

std::ostream& operator<<(std::ostream& outs, const Table& table) {
    for (size_t i = 0; i < table._rows; ++i) {
        for (size_t j = 0; j < table._columns; j++) {
            outs << table(i, j) << "\t";
        }
        outs << "\n";
    }
    return outs;
}

} // namespace nol0n