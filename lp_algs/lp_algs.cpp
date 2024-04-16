#include <iostream>
#include <fstream>
#include <cstring>
#include <math.h>

#include <lp_algs.hpp>
#include <rational.hpp>
#include <table.hpp>

namespace simplexMethod
{

    void findPositiveValueInRow(const obv::Table &table, int &column)
    {
        size_t columns = table.getColumns();

        for (int j = 1; j < columns; ++j)
        {
            // если нашли положительный коэффициент, то запоминаем индекс
            // его столбца, иначе индекс будет равен -1
            if (table(0, j) > obv::rational(0))
            {
                column = j;
                break;
            }
        }
    }

    void findMinmumRelationInColumn(const obv::Table &table, const int &column, int &row)
    {
        size_t rows = table.getRows();

        obv::rational tmp = 0;
        for (size_t i = 1; i < rows; ++i)
        {
            // берется наименьшее отношение, если будет несколько равных, будет взято первое
            if (table(i, column) < obv::rational(0) && ((table(i, 0) / table(i, column)) > tmp || tmp == obv::rational(0)))
            {
                row = i;
                tmp = table(i, 0) / table(i, column);
            }
        }
    }

} // namespace simplexMethod

namespace cuttingPlane
{

    void findNonIntegerInColumn(const obv::Table &table, int &row)
    {
        size_t rows = table.getRows();

        for (int i = 0; i < rows - 1; ++i)
        {
            // если нашли добрное значение, то запоминаем индекс
            // его строки, иначе индекс будет равен -1
            if (!table(i, 0).isInteger())
            {
                row = i;
                break;
            }
        }
    }

    void createCut(obv::Table &table, const int &row) 
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

    void findMinmumRelationInRow(const obv::Table &table, int &column)
    {
        size_t lastRowIndex = table.getRows() - 1;
        size_t columns = table.getColumns();

        obv::rational tmp = 0;
        for (size_t j = 1; j < columns; ++j)
        {
            // берется наименьшее отношение, если будет несколько равных, будет взято первое
            if (table(lastRowIndex, j) > obv::rational(0) && ((table(0, j) / table(lastRowIndex, j)) > tmp || tmp == obv::rational(0)))
            {
                column = j;
                tmp = table(0, j) / table(lastRowIndex, j);
            }
        }
    }

} // namespace cuttingPlane

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
            simplexMethod::findPositiveValueInRow(table, column);

            // не было найдено положительного значения
            // в первом столбце => мы нашли оптимальное решение
            if (column == -1)
            {
                return 1;
            }

            // если мы нашли отрицательное значение, то необхожимо преобразовать таблицу

            // найдем элемент в столбце, который будет иметь отношени, при этом сам будет
            // отрицательным если все элементы положительные, то row будет = -1
            simplexMethod::findMinmumRelationInColumn(table, column, row);

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
            cuttingPlane::findNonIntegerInColumn(table, row);

            // нет дробных значений => найдено целочисленное решение
            if (row == -1)
            {
                return 1;
            }

            // составляем и записываем отсечение
            cuttingPlane::createCut(table, row);

            if (debug)
                std::cout << table << "\n" << std::endl;

            // ищем элемент с минимальным отношением
            cuttingPlane::findMinmumRelationInRow(table, column);

            table.rowZeroing(rows - 1, column);

            column = 0;
            row = -1;
        }

        table.removeBottomRow();
    }

    void lpalgs::integerCuttingPlane(Table &table, bool debug)
    {
    }

} // namespace obv
