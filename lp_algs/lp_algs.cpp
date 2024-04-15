#include <iostream>
#include <fstream>
#include <cstring>
#include <math.h>

#include <lp_algs.hpp>
#include <rational.hpp>
#include <table.hpp>

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
            // проходим по первой строке в поиске
            // положительных значений
            for (int j = 1; j < columns; ++j)
            {
                // если нашли положительный коэффициент, то
                // запоминаем индекс его столбца, иначе индекс
                // будет равен -1
                if (table(0, j) > rational(0))
                {
                    column = j;
                    break;
                }
            }

            // не было найдено положительного значения
            // в первом столбце => мы нашли оптимальное решение
            if (column == -1)
            {
                return 1;
            }

            // если мы нашли отрицательное значение, то необхожимо
            // преобразовать таблицу

            // найдем элемент в столбце, который будет иметь
            // отношение min(abs(a)), при этом сам будет отрицательным
            // если все элементы положительные, то оптимального плана нет
            rational tmp = 0;
            for (size_t i = 1; i < rows; ++i)
            {
                if (table(i, column) < rational(0) && (table(i, 0) / table(i, column)) > tmp)
                {
                    row = i;
                    tmp = table(i, 0) / table(i, column);
                }
            }

            // не удалось найти допустимый элемент
            // оптимального решения не сущесвтует
            if (row == -1)
            {
                return 0;
            }

            // зануляем выбранную строку
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
