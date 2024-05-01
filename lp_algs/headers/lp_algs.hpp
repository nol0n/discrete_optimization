#pragma once

#include <cstdint>

#include <table.hpp>

namespace obv
{

    class lpalgs
    {
    private:
    public:
        static int simplexMethod(Table &);
        static int dualSimplexMethod(Table &);
        static int cuttingPlane(Table &);
        static int integerCuttingPlane(Table &);
    };

} // namespace nol0n
