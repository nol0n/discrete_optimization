#include <iostream>
#include <fstream>
#include <cstring>
#include <math.h>

#include <lp_algs.hpp>
#include <rational.hpp>
#include <table.hpp>

namespace simplexMethod {

    void findPositiveValueInRow(const nol0n::Table& table, const size_t& columns, size_t& column)
    {
        for (int j = 1; j < columns; ++j)
        {
            // если нашли положительный коэффициент, то запоминаем индекс 
            // его столбца, иначе индекс будет равен -1
            if (table(0, j) > nol0n::rational(0))
            {
                column = j;
                break;
            }
        }
    }

    void findMinmumRelationInColumn(const nol0n::Table& table, const size_t& rows, const size_t& column, size_t& row)
    {
        // найдем элемент в столбце, который будет иметь отношени, при этом сам будет
        // отрицательным если все элементы положительные, то row будет = -1
        nol0n::rational tmp = 0;
        for (size_t i = 1; i < rows; ++i)
        {
            if (table(i, column) < nol0n::rational(0) && (table(i, 0) / table(i, column)) > tmp)
            {
                row = i;
                tmp = table(i, 0) / table(i, column);
            }
        }
    }

} // namespace anonymous

namespace nol0n
{
    /// @brief find optimal solution (non-integer) for column table
    /// @param table
    /// @return 1 - found solution 0 - optmial solution doesn't exit
    int lpalgs::simplexMethod(Table &table, bool debug)
    {
        size_t rows = table.getRows();
        size_t columns = table.getColumns();
        size_t column = -1;
        size_t row = -1;

        if (debug)
            std::cout << table << "\n\n";

        while (true)
        {
            // проходим по первой строке в поиске положительных значений
            simplexMethod::findPositiveValueInRow(table, columns, column);

            // не было найдено положительного значения
            // в первом столбце => мы нашли оптимальное решение
            if (column == -1)
            {
                return 1;
            }

            // если мы нашли отрицательное значение, то необхожимо преобразовать таблицу

            // найдем элемент в столбце, который будет иметь отношени, при этом сам будет
            // отрицательным если все элементы положительные, то оптимального плана нет
            simplexMethod::findMinmumRelationInColumn(table, rows, column, row);

            // не удалось найти допустимый элемент оптимального решения не сущесвтует
            if (row == -1)
            {
                return 0;
            }

            table.rowZeroing(row, column);
            if (debug)
                std::cout << table << "\n\n";

            column = -1;
            row = -1;
        }
    }

    void lpalgs::cuttingPlane(Table &table)
    {
    }

    void lpalgs::integerCuttingPlane(Table &table)
    {
    }

} // namespace nol0n
