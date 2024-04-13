#pragma once

#include <cstdint>

class lp_methods
{
public:
    static void simplex_method(const char path_to_file[], bool debug = false);
    static void two_phase_method(const char path_to_file[], bool debug = false);
    static void backpack_max(const char path_to_file[], bool debug = false);
    static void backpack_min(const char path_to_file[], bool debug = false);

private:
    static int32_t matrix_transfrom(double **matrix, int32_t rows, int32_t constarints, int32_t variables, bool debug = false);
    static bool equals(double value_1, double value_2);
    static int32_t find_row(double *ratios, int32_t size, int32_t *basic_vars);
    static void find_basis(double **matrix, int32_t rows, int32_t columns, int32_t *basic_vars);
    static void print_table(double *matrix, int32_t constraints, int32_t variables);
};