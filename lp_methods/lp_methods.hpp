#pragma once

class lp_methods {
public:
    static double_t simplex_method(const char path_to_file[], bool debug = false);
private:
    static int32_t matrix_transfrom(double_t **matrix, int32_t constarints, int32_t variables, bool debug = false);
    static bool equals(double_t value_1, double_t value_2);
    static int32_t find_row(double_t* ratios, int32_t size, int32_t* basic_vars);
};