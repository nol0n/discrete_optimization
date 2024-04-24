#include <math.h>

#include <rational.hpp>
#include <table.hpp>
#include <lp_algs.hpp>
#include <perf.hpp>

obv::Table generateTable (const int& variables, const int& constraints)
{
    obv::Table table(variables, constraints);

    return table;
}

int main(int argc, char *argv[])
{
    int* nums = obv::Perf::getInt(0, 10, 10);

    for (int i = 0; i < 10; i++)
    {
        std::cout << nums[i] << " ";
    }
    delete[] nums;
    
    // создание матриц 


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