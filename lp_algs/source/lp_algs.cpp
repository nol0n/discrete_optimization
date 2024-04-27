#include <iostream>
#include <fstream>
#include <cstring>
#include <math.h>

#include <lp_algs.hpp>

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
            std::cout << "--- Simplex method --- \n\n";

        while (true)
        {
            // вывод таблицы в начале итерации
            if (debug)
                std::cout << table << "\n";

            // проходим по первой строке в поиске положительных значений
            // берем ! НАИБОЛЬШЕЕ ! (пока еще нет (уже да))
            Table::findPositiveValueInRow(table, 0, column);
            // Table::findMaxPositiveValueInRow(table, 0, column);


            // не было найдено положительного значения
            // в первом столбце => мы нашли оптимальное решение
            if (column == -1)
            {
                return 1;
            }

            // если мы нашли положительное значение, то необхожимо преобразовать таблицу

            // найдем элемент в столбце, который будет иметь мин. отношени, при этом сам будет
            // отрицательным если все элементы положительные, то row будет = -1
            Table::findMinmumRelationInColumn(table, column, row);

            // не удалось найти допустимый элемент => оптимального решения не сущесвтует
            if (row == -1)
            {
                return 0;
            }

            table.rowZeroing(row, column);

            // вывод таблицы после получения нового баазиса
            if (debug) 
            {
                std::cout << "column: " << column + 1 << " row: " << row + 1 << "\n\n";
                std::cin.get();
            }

            column = -1;
            row = -1;
        }
    }

    /// @brief поиск оптмаильного решения (не целочисленного) для двойственной задачи
    /// @param таблица в столбцовом формате
    /// @return 1 - оптимальный план найден 0 - оптимального плана не сущесвтует
    int lpalgs::dualSimplexMethod(Table &table, bool debug) 
    {
        size_t rows = table.getRows();
        size_t columns = table.getColumns();
        int column = -1;
        int row = -1;

        if (debug)
            std::cout << "--- Dual Simplex method --- \n\n";

        while (true)
        {
            // проходим по первому столбцу в поиске отрицательных значений (каких?)
            Table::findNegativeValueInColumn(table, 0, row);
            // Table::findMaxNegativeValueInColumn(table, 0, row);

            // не было найдено отрицательного значения
            // в первом столбце => мы нашли оптимальное решение
            if (row == -1)
            {
                return 1;
            }

            // печать таблицы в начале итерации
            if (debug)
                std::cout << table << "\n";

            // если мы нашли отрицательное значение, то необхожимо преобразовать таблицу

            // найдем элемент в строке, который будет иметь мин. отношени, при этом сам будет
            // положительным если все элементы отрицательные, то row будет = -1
            Table::findMinmumRelationInRow(table, row, column);

            // не удалось найти допустимый элемент => оптимального решения не сущесвтует
            if (column == -1)
            {
                return 0;
            }

            // после получения нового базиса
            table.rowZeroing(row, column);
            if (debug) {
                std::cout << "row: " << row + 1 << " column: " << column + 1 << "\n\n";
                std::cin.get();
            }

            column = -1;
            row = -1;
        }
    }

    /// @brief поиск оптимального целочисленного решения для таблицы полученной симплекс методом
    /// @param таблица в столбцовом формате полученная симплекс методом
    /// @return 1 - найдено целочисленное решение
    int lpalgs::cuttingPlane(Table &table, bool debug)
    {
        // добавляем строку для записи отсечений
        table.addBottomRow();
        size_t rows = table.getRows();
        size_t columns = table.getColumns();
        int column = 0;
        int row = -1;

        if (debug)
            std::cout << "--- Cutting plane method --- \n\n";

        while (true)
        {
            // печать таблицы в начале итерации
            if (debug)
                std::cout << table << "\n";

        // проходим первый столбец в поиске дробных значений
        // берем c ! НАИБОЛЬШЕЙ ! дробной частью
            // Table::findNonIntegerInColumnWithMaxFractional(table, 0, row);
        // или необязатлеьно, я не знаю...
            Table::findNonIntegerInColumn(table, 0, row);

            // нет дробных значений => найдено целочисленное решение
            if (row == -1)
            {
                // убираем строку отсечений
                table.removeBottomRow();
                return 1;
            }

            // составляем и записываем отсечение
            Table::createCut(table, row);

            // информация об отсечении
            if (debug) {
                std::cout << "added cut from row " << row + 1 << "\n\n";
                std::cin.get();
            }

            // введённое отсечение нарушает допустимость таблицы
            // применяем двойсвтенный симплекс метод
            if (dualSimplexMethod(table, debug) == 0) 
            {
                // оптимального решения не существует
                return 0;
            }

            if (debug)
                std::cout << "--- Cutting plane method --- \n\n";

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
        {
            std::cout << "--- Integer Cutting plane method --- \n\n";
            std::cout << table << "\n";
        }
        
        // test :)
        // int iters = table.getColumns() * 1;
        // int num = 1;

        // while (true) {
        //     // test
        //     iters--;
        //     if (iters == 0)
        //     {
        //         iters = table.getColumns() * 1;
        //         num *= -1;
        //     }

        //     // проходим по первой строке в поиске положительных значений
        //     if (num == 1)
        //     {
        //         Table::findMaxPositiveValueInRow(table, 0, column);
        //     }
        //     else 
        //     {
        //         Table::findPositiveValueInRow(table, 0, column);
        //     }

        while (true) {
            // проходим по первой строке в поиске положительных значений (каких-то...)
            // Table::findMaxPositiveValueInRow(table, 0, column);
            Table::findPositiveValueInRow(table, 0, column);

            // не было найдено положительного значения
            // в первом столбце => мы нашли оптимальное решение
            if (column == -1)
            {
                // убираем строку отсечений
                table.removeBottomRow();
                return 1;
            }

            // если мы нашли положительное значение, то необхожимо преобразовать таблицу

            // найдем элемент в столбце, который будет иметь мнимальное отношени, при этом сам будет
            // отрицательным, если все элементы положительные, то row будет = -1
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

            // информация об отсечении
            if (debug) {
                std::cout << "cut from row: " << row + 1 << 
                " column: " << column + 1 << "\n\n";
                std::cout << table << "\n";
                std::cin.get();
            }

            table.rowZeroing(rows - 1, column);

            if (debug) {
                std::cout << "changed table: \n\n";
                std::cout << table << "\n";
                std::cin.get();
            }

            column = -1;
            row = -1;
        }
    }

} // namespace obv
