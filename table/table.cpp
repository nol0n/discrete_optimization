#include <fstream>

#include <table.hpp>

namespace obv
{

    Table::Table() : _rows(0), _columns(0)
    {
        data = nullptr;
    }

    Table::Table(size_t rows, size_t columns) : _rows(rows), _columns(columns)
    {
        data = new rational[_rows * _columns]{};
    }

    Table::~Table()
    {
        delete[] data;
    }

    size_t Table::getRows() const
    {
        return _rows;
    }

    size_t Table::getColumns() const
    {
        return _columns;
    }

    void Table::addBottomRow() {
        rational* newData = new rational[(_rows + 1) * _columns]{};

        for (size_t i = 0; i < _rows; ++i) {
            for (size_t j = 0; j < _columns ; ++j) {
                    newData[(i * _columns) + j] = (*this)(i, j);
            }
        }

        delete[] data;

        data = newData;
        _rows++;
    }
    
    void Table::removeBottomRow() {
        if (_rows == 1) return;

        rational* newData = new rational[(_rows - 1) * _columns]{};
        _rows--;

        for (size_t i = 0; i < _rows; ++i) {
            for (size_t j = 0; j < _columns ; ++j) {
                newData[(i * _columns) + j] = (*this)(i, j);
            }
        }

        delete[] data; 

        data = newData;
    }

    int Table::readFile(const char path_to_file[], bool debug)
    {
        // чтение условия из файла
        int variables = 0;
        int constraints = 0;
        std::fstream task(path_to_file);

        if (!task)
        {
            std::cerr << "table::can't open file\n\n";
            return 1;
        }
        else
        {
            std::cout << "table::file opened\n\n";
        }

        // установка размерности целевой функции и кол-ва ограничений
        task >> variables >> constraints;
        _columns = variables + 1;
        _rows = variables + constraints + 1;

        if (data != nullptr)
        {
            delete[] data;
        }
        data = new rational[_rows * _columns]{};

        // запись целеовой функции
        for (int j = 1; j < _columns; ++j)
        {
            task >> (*this)(0, j);
        }

        // запись базиса
        for (int i = 1; i < variables + 1; ++i)
        {
            (*this)(i, i) = 1;
        }

        // запись ограничений
        for (int i = 1 + variables; i < _rows; ++i)
        {
            for (int j = 1; j < _columns; ++j)
            {
                task >> (*this)(i, j);
                (*this)(i, j) *= -1;
            }
            task >> (*this)(i, 0);
        }

        if (debug)
            std::cout << (*this);

        task.close();
        return 0;
    }

    void Table::columnZeroing(size_t row, size_t column)
    {
        column--;
        rational value = data[row * _columns + column];

        for (size_t j = 0; j < _columns; ++j)
        {
            (*this)(row, j) /= value;
        }

        for (size_t i = 0; i < _rows; ++i)
        {
            if (i == row)
                continue;

            rational div_coeff = (*this)(i, column);
            for (size_t j = 0; j < _columns; j++)
            {
                (*this)(i, j) -= (*this)(row, j) * div_coeff;
            }
        }
    }

    void Table::rowZeroing(size_t row, size_t column)
    {
        rational value = data[row * _columns + column];

        for (size_t i = 0; i < _rows; ++i)
        {
            (*this)(i, column) /= value;
        }

        for (size_t j = 0; j < _columns; ++j)
        {
            if (j == column)
                continue;

            rational div_coeff = (*this)(row, j);
            for (size_t i = 0; i < _rows; i++)
            {
                (*this)(i, j) -= (*this)(i, column) * div_coeff;
            }
        }
    }

    rational &Table::operator()(size_t row, size_t column)
    {
        return data[row * _columns + column];
    }

    const rational Table::operator()(size_t row, size_t column) const
    {
        return data[row * _columns + column];
    }

    std::ostream &operator<<(std::ostream &outs, const Table &table)
    {
        for (size_t i = 0; i < table._rows; ++i)
        {
            for (size_t j = 0; j < table._columns; j++)
            {
                outs << table(i, j) << "\t";
            }
            outs << "\n";
        }
        return outs;
    }

} // namespace obv
