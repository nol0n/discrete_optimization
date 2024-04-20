#include <iostream>
#include <chrono>
#include <fstream>
#include <iomanip>

#include <perf.hpp>

namespace obv
{

    Perf::Perf() : startTime(0) { }

    void Perf::startTimer() 
    {
        startTime = getCurrentTime();
    }

    long long Perf::stopTimer()
    {
        long long time = getCurrentTime() - startTime;
        startTime = 0;

        return time;
    }

    void Perf::addSample(int size, long long time)
    {
        std::pair<int, double> sample{};

        sample.first = size;
        sample.second = time;

        samples.push_back(sample);
    }

    int Perf::saveResult(const char path_to_file[])
    {
        std::fstream output(path_to_file, std::ios::out);

        if (!output)
        {
            std::cerr << "Perf::can't open output file\n\n";
            return 1;
        }
        else
        {
            std::cout << "Perf::output file opened\n\n";
        }

        output << std::fixed << std::setprecision(2);

        for (const auto& sample : samples)
        {
            output << sample.first << " " << sample.second / 1000 << "\n";            
        }
        samples.clear();

        output.close();
        return 0;
    }

    long long Perf::getCurrentTime()
    {
        auto now = std::chrono::high_resolution_clock().now();
        auto nowMS = std::chrono::time_point_cast<std::chrono::milliseconds>(now);

        return nowMS.time_since_epoch().count();
    }

} // namespace obv