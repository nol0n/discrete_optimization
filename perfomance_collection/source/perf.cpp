#include <iostream>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <random>

#include <perf.hpp>

namespace obv
{

    Perf::Perf() : startTime(0) { }

    /// @brief начинает отсчет, устанваливая значение внутреннего поля равное текущему времени
    void Perf::startTimer() 
    {
        startTime = getCurrentTime();
    }

    /// @brief завершает замер времени
    /// @return возвращает разницу меджу началом отсчета и текущим временем
    long long Perf::stopTimer()
    {
        long long time = getCurrentTime() - startTime;
        startTime = 0;

        return time;
    }

    /// @brief запоминает результат во внутренний массив пар <значение, время>
    /// @param size значение замера
    /// @param time время
    void Perf::addSample(int size, long long time)
    {
        std::pair<int, double> sample{};

        sample.first = size;
        sample.second = time;

        samples.push_back(sample);
    }

    /// @brief записывает результат в файл парами "значение время"
    /// @param path_to_file 
    /// @return 1 - не удалось записать результат 0 - результат записан
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

    /// @brief
    /// @return текущее вермя в виде long long 
    long long Perf::getCurrentTime()
    {
        auto now = std::chrono::high_resolution_clock().now();
        auto nowMS = std::chrono::time_point_cast<std::chrono::milliseconds>(now);

        return nowMS.time_since_epoch().count();
    }

    /// @brief получить случайные целочсиленные значения в заданном диапазоне
    /// @param min 
    /// @param max 
    /// @param count кол-во значений 
    /// @return std::vec заполенный числами
    std::vector<int> Perf::getInt(const int & min, const int & max, const int &count) 
    {
        std::random_device dev{};
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> dist(min, max);

        std::vector<int> values;
        values.reserve(count);
        for (int i = 0; i < count; ++i)
        {
            values.push_back(dist(rng));
        }

        return values;
    }

} // namespace obv