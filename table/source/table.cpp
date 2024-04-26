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

    Table::Table(const Table& table)
    {
        this->_rows = table._rows; 
        this->_columns = table._columns;

        size_t size = _rows * _columns;
        data = new rational[size]{};

        for (int i = 0; i < size; ++i)
        {
            data[i] = table.data[i];
        }
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
            std::cerr << "table::can't open file\n";
            return 1;
        }
        else
        {
            if (debug)
                std::cout << "table::file opened\n";
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

    void Table::changeColumns(size_t changedColumn, size_t sourceColumn, int coefficient, sign sign_value)
    {
        int sign = 1;

        switch(sign_value)
        {
            case PLUS:
                sign = 1;
            case MINUS:
                sign = -1;
        }

        for (int i = 0; i < _rows; ++i)
        {
            (*this)(i, changedColumn) += ((*this)(i, sourceColumn) * obv::rational(coefficient)) * obv::rational(sign);
        }
    }

    void Table::findPositiveValueInRow(const obv::Table &table, const int& row, int &column)
    {
        size_t columns = table.getColumns();

        for (int j = 1; j < columns; ++j)
        {
            // если нашли положительный коэффициент, то запоминаем индекс
            // его столбца, иначе индекс будет равен -1 (входное значение
            // column не изменится)
            if (table(row, j) > obv::rational(0))
            {
                column = j;
                break;
            }
        }
    }
    
    void Table::findNegativeValueInColumn(const obv::Table &table, const int & column, int &row)
    {
        size_t rows = table.getRows();

        for (int i = 1; i < rows; ++i)
        {
            // если нашли отрицательный коэффициент, то запомниаем индекс
            // его строки, иначе индекс будет равен -1 (входное значение
            // row не изменится)
            if (table(i, column) < obv::rational(0))
            {
                row = i;
                break;
            }
        }
    }


    void Table::findNonIntegerInColumn(const obv::Table &table, const int &column, int &row)
    {
        // будем брать число с максмиальной дробной частью
        size_t rows = table.getRows();
        size_t max_row = -1;

        for (int i = 0; i < rows - 1; ++i)
        {
            // если нашли добрное значение, то запоминаем индекс
            // его строки, иначе индекс будет равен -1
            if (!table(i, column).isInteger())
            {
                if (max_row == -1 || table(max_row, column).fractional() < table(i, column).fractional())
                {
                    max_row = i;
                    row = i;
                }
            }
        }
    }

    void Table::findMinmumRelationInRow(const obv::Table &table, const int &row, int &column)
    {
        size_t columns = table.getColumns();

        obv::rational tmp = 1; // это значение не может быть положительным
        for (size_t j = 1; j < columns; ++j)
        {
            // берется наименьшее отношение, если будет несколько равных, будет взято первое
            if (table(row, j) > obv::rational(0) && ((table(0, j) / table(row, j)) > tmp || tmp == obv::rational(1)))
            {
                column = j;
                tmp = table(0, j) / table(row, j);
            }
        }
    }

    void Table::findMinmumRelationInColumn(const obv::Table &table, const int &column, int &row)
    {
        size_t rows = table.getRows();

        obv::rational tmp = 1; // это значение не может быть положительным
        for (size_t i = 1; i < rows; ++i)
        {
            // берется наименьшее отношение, если будет несколько равных, будет взято первое
            if (table(i, column) < obv::rational(0) && ((table(i, 0) / table(i, column)) > tmp || tmp == obv::rational(1)))
            {
                row = i;
                tmp = table(i, 0) / table(i, column);
            }
        }
    }

    void Table::createCut(obv::Table &table, const int &row) 
    {
        size_t lastRowIndex = table.getRows() - 1;
        size_t columns = table.getColumns();
        // в столбец коэффициентов - правая_часть.fractional() - 1
        table(lastRowIndex, 0) = table(row, 0).fractional() - obv::rational(1);

        // в левой части просто - значение.fractional()
        for (int j = 1; j < columns; ++j)
        {
            table(lastRowIndex, j) = table(row, j).fractional();
        }
    }

    void Table::createCutInteger(obv::Table &table, const int &row, const int &column) 
    {
        size_t lastRowIndex = table.getRows() - 1;
        size_t columns = table.getColumns();

        // значение разрешающего элемента
        obv::rational value = table(row, column);

        table(lastRowIndex, 0) = (table(row, 0) / (value * obv::rational(-1))).floor();
        for (size_t j = 1; j < columns; ++j) 
        {
            table(lastRowIndex, j) = ((table(row, j) / value).floor()) * obv::rational(-1);
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
