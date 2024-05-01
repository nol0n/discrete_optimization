#pragma once

#include <cstdint>

#include <table.hpp>

namespace obv
{

    class lpalgs_dev
    {
    private:
    public:
        static int simplexMethod(Table &, bool = false);
        static int dualSimplexMethod(Table &, bool = false);
        static int cuttingPlane(Table &, bool = false);
        static int integerCuttingPlane(Table &, bool = false);
    };

} // namespace nol0n
