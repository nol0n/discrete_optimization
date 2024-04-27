#pragma once

#include <rational.hpp>
#include <iostream>

namespace obv
{

    class Table
    {
    private:
        rational *data;
        size_t _rows;
        size_t _columns;

    public:
        enum sign 
        {
            PLUS,
            MINUS,
        };

        Table();
        Table(size_t, size_t);
        Table(const Table &);
        ~Table();

        size_t getRows() const;
        size_t getColumns() const;

        void addBottomRow();
        void removeBottomRow();

        int readFile(const char[], bool = false);

        void columnZeroing(size_t, size_t);
        void rowZeroing(size_t, size_t);
        void changeColumns(size_t, size_t, int, sign = PLUS);

        static void findPositiveValueInRow(const obv::Table &, const int &, int &);
        static void findMaxPositiveValueInRow(const obv::Table &, const int &, int &);
        static void findNegativeValueInColumn(const obv::Table &, const int &, int &);
        static void findMaxNegativeValueInColumn(const obv::Table &, const int &, int &);
        static void findNonIntegerInColumn(const obv::Table &, const int &, int &);
        static void findNonIntegerInColumnWithMaxFractional(const obv::Table &, const int &, int &); 
        static void findMinmumRelationInRow(const obv::Table &, const int &, int &);
        static void findMinmumRelationInColumn(const obv::Table &, const int &, int &);
        static void createCut(obv::Table &, const int &);
        static void createCutInteger(obv::Table &, const int &, const int &);

        rational &operator()(size_t, size_t);
        const rational operator()(size_t, size_t) const;

        friend std::ostream &operator<<(std::ostream &, const Table &);
    };

} // namespace obv
