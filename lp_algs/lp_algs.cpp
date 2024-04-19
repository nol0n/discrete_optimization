#include <iostream>
#include <fstream>
#include <cstring>
#include <math.h>

#include <lp_algs.hpp>
#include <rational.hpp>
#include <table.hpp>

namespace obv
{
    /// @brief поиск оптмаильного решения (не целочисленного) для столбцовой таблицы
    /// @param таблица в столбцовом формате
    /// @return 1 - оптимальный план найден 0 - оптимального плана не сущесвтует
    int lpalgs::simplexMethod(Table &table, bool debug)
    {
        size_t rows = table.getRows();
        size_t columns = table.getColumns();
        int column = -1;
        int row = -1;

        if (debug)
            std::cout << table << "\n\n";

        while (true)
        {
            // проходим по первой строке в поиске положительных значений
            Table::findPositiveValueInRow(table, column);

            // не было найдено положительного значения
            // в первом столбце => мы нашли оптимальное решение
            if (column == -1)
            {
                return 1;
            }

            // если мы нашли отрицательное значение, то необхожимо преобразовать таблицу

            // найдем элемент в столбце, который будет иметь отношени, при этом сам будет
            // отрицательным если все элементы положительные, то row будет = -1
            Table::findMinmumRelationInColumn(table, column, row);

            // не удалось найти допустимый элемент => оптимального решения не сущесвтует
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

    /// @brief поиск оптимального целочисленного решения для таблицы полученной симплекс методом
    /// @param таблица в столбцовом формате полученная симплекс методом
    /// @return 1 - найдено целочисленное решение
    int lpalgs::cuttingPlane(Table &table, bool debug)
    {
        if (debug)
            std::cout << table << "\n" << std::endl;

        // добавляем строку для записи отсечений
        table.addBottomRow();
        size_t rows = table.getRows();
        size_t columns = table.getColumns();
        int column = 0;
        int row = -1;

        while (true)
        {
            // проходим первый столбец в поиске дробных значений
            Table::findNonIntegerInColumn(table, row);

            // нет дробных значений => найдено целочисленное решение
            if (row == -1)
            {
                // убираем строку отсечений
                table.removeBottomRow();
                return 1;
            }

            // составляем и записываем отсечение
            Table::createCut(table, row);

            if (debug)
                std::cout << table << "\n" << std::endl;

            // ищем элемент с минимальным отношением
            Table::findMinmumRelationInRow(table, column);

            table.rowZeroing(rows - 1, column);

            column = 0;
            row = -1;
        }

        table.removeBottomRow();
    }

    int lpalgs::integerCuttingPlane(Table &table, bool debug)
    {
        // добавляем строку для записи отсечений
        table.addBottomRow();

        size_t rows = table.getRows();
        size_t columns = table.getColumns();
        int column = -1;
        int row = -1;

        if (debug)
            std::cout << table << "\n\n";
        
        while (true) {
            // проходим по первой строке в поиске положительных значений
            Table::findPositiveValueInRow(table, column);

            // не было найдено положительного значения
            // в первом столбце => мы нашли оптимальное решение
            if (column == -1)
            {
                // убираем строку отсечений
                table.removeBottomRow();
                return 1;
            }

            // если мы нашли отрицательное значение, то необхожимо преобразовать таблицу

            // найдем элемент в столбце, который будет иметь отношени, при этом сам будет
            // отрицательным если все элементы положительные, то row будет = -1
            Table::findMinmumRelationInColumn(table, column, row);

            // не удалось найти допустимый элемент => оптимального решения не сущесвтует
            if (row == -1)
            {
                // убираем строку отсечений
                table.removeBottomRow();
                return 0;
            }

            // составим отсечение
            Table::createCutInteger(table, row, column);

            if (debug)
                std::cout << table << "\n\n";

            table.rowZeroing(rows - 1, column);

            column = -1;
            row = -1;
        }
    }

} // namespace obv
