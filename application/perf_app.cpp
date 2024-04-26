#include <math.h>

#include <rational.hpp>
#include <table.hpp>
#include <lp_algs.hpp>
#include <perf.hpp>

obv::Table generateTable (const int& variables, const int& constraints)
{
    size_t rows = 1 + variables + constraints;
    size_t columns = 1 + variables;

    obv::Table table(rows, columns);    

    // заполнение строку с коэффициентами целеовей функции 
    int *nums = obv::Perf::getInt(0, 10, variables);
    for (int j = 1; j < variables + 1; ++j)
    {
        table(0, j) = nums[j - 1]; 
    }
    delete[] nums;

    // заполняем базис
    for (int i = 1; i < variables + 1; ++i)
    {
        table(i, i) = 1;
    }

    // заполняем огранчения
    int* lhs = obv::Perf::getInt(-10, 0, variables * constraints);
    int* rhs = obv::Perf::getInt(5, 100, constraints);
    for (int i = (1 + variables); i < (1 + variables + constraints); ++i)
    {
        table(i, 0) = rhs[i - (1 + variables)];

        for (int j = 0; j < variables; ++j)
        {
            table(i, 1 + j) = lhs[(i - (1 + variables)) * variables + j];
        }
    }
    delete[] lhs;
    delete[] rhs;

    return table;
}

int main(int argc, char *argv[])
{    
    // создание матриц 

    for (int i = 0; i < 10'000; ++i)
    {
        obv::Table table_1 = generateTable(2, 1);
        obv::Table table_2 = table_1;

        std::cout << "-- table --\n" << table_1 << "\n";

        obv::lpalgs::integerCuttingPlane(table_2);

        std::cout << table_2(0, 0) << " | ";

        obv::lpalgs::simplexMethod(table_1);
        obv::lpalgs::cuttingPlane(table_1);

        std::cout << table_1(0, 0) << "\n\n";
    }

    // obv::Perf collector{};

    // for (int i = 1; i < 20; ++i) 
    // {
    //     double sum = 0;
    //     std::cout << i << "  ";

    //     collector.startTimer();
    //     for (int j = 1; j < i * 500'000; ++j)
    //     {
    //         sum += sqrt(sqrt(sqrt(sqrt(sqrt(sin(cos(100)))))));
    //     }
    //     collector.addSample(i, collector.stopTimer());
    //     std::cout << sum << "\n";
    // }                

    // collector.saveResult("./output.txt");

    return 0;
}