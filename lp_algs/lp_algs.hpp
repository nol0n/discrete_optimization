#pragma once

#include <cstdint>

#include <table.hpp>

namespace obv
{

    class lpalgs
    {
    private:
    public:
        static int simplexMethod(Table &, bool = false);
        static int cuttingPlane(Table &, bool = false);
        static void integerCuttingPlane(Table &, bool = false);
    };

} // namespace nol0n
