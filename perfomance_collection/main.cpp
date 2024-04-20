#include <math.h>

#include <perf.hpp>

#include <table.hpp>
#include <rational.hpp>
#include <lp_algs.hpp>


int main(int argc, char *argv[])
{
    obv::Perf collector{};

    for (int i = 1; i < 20; ++i) 
    {
        double sum = 0;
        std::cout << i << "  ";

        collector.startTimer();
        for (int j = 1; j < i * 500'000; ++j)
        {
            sum += sqrt(sqrt(sqrt(sqrt(sqrt(sin(cos(100)))))));
        }
        collector.addSample(i, collector.stopTimer());
        std::cout << sum << "\n";
    }

    collector.saveResult("./output.txt");

    return 0;
}