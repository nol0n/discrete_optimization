#pragma once

#include <vector>
#include <utility>

namespace obv
{

    class Perf
    {
    public:
        Perf();

        void startTimer();
        long long stopTimer(); 
        void addSample(int, long long);
        int saveResult(const char*);

        static long long getCurrentTime();
    private:
        long long startTime;
        std::vector<std::pair<int, double>> samples;
    };

} // namespace obv
