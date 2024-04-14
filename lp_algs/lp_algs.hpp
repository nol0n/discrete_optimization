#pragma once

#include <cstdint>

#include <table.hpp>

namespace nol0n
{

    class lpalgs 
    {
    private:

    public:
        static int simplexMethod(Table&, bool = false);
        static void cuttingPlane(Table&);
        static void integerCuttingPlane(Table&);
    };

} // namespace nol0n
