#include <iostream>
#include <fstream>
#include <cstring>
#include <lp_methods.hpp>

double_t lp_methods::simplex_method(const char path_to_file[], bool debug) {
    int32_t variables  = 0;
    int32_t constraints = 0;
    double_t **matrix;

    // чтение условия из файла
    std::fstream task(path_to_file);

    if (!task) {
        std::cerr << "can't open file\n";
        return 0.0;
    } else {
        std::cout << "file opened\n";
    }

    // установка размерности целевой функции и кол-ва ограничений
    task >> variables >> constraints;

    // запись условия задачи
    matrix = new double*[constraints + 1];

    for (int32_t i = 0; i < constraints + 1; i++) {
        matrix[i] = new double[variables + constraints + 1]();
    }

    for (int32_t i = 0; i < variables; i++) {
        task >> matrix[0][i];
    }

    for (int32_t i = 1; i < constraints + 1; i++) {
        for (int32_t j = 0; j < variables; j++) {
            task >> matrix[i][j];
        }
        matrix[i][variables + i - 1] = 1.0;
        task >> matrix[i][variables + constraints]; 
    }

    // печать полученных условий
    if (debug) {
        std::cout << variables << " " << constraints << std::endl;
        for (int32_t i = 0; i < constraints + 1; i++) {
            for (int32_t j = 0; j < variables + constraints + 1; j++) {
                std::cout << matrix[i][j] << "\t";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    // применение симплекс метода
    int32_t result = matrix_transfrom(matrix, constraints, variables, true);

    switch (result) {
        case 1:
            std::cout << "OK\n";
            break;
        case -1:
            std::cout << "not OK\n";
            return 0.0;
            break;
    }

    return -matrix[0][variables + constraints];

    for (int32_t i = 0; i < constraints + 1; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

/// @brief применение симплекс метода к задаче, которая приведена к конанической форме
/// @param matrix 
/// @param constraints 
/// @param variables 
/// @param test печать промежуточных этапов
/// @return "1" - найден оптимальный план "-1" - оптимального плана не сущесвует 
int32_t lp_methods::matrix_transfrom(double_t **matrix, int32_t constraints, int32_t variables, bool debug) {    
    int32_t *basic_vars = new int32_t[constraints]();
    double_t *ratios = new double_t[constraints]();

    for (int32_t i = 0; i < constraints; i++) {
        basic_vars[i] = variables + 1 + i;
    }

    int32_t column = -1;
    int32_t row = -1;
    while (true) {
        // выбор столбца
        for (int32_t i = 0; i < variables + constraints; i++) {
            if (matrix[0][i] > 0.0) {
                column = i;
                break;
            } 
        }
        // не найдено положительного элемента в строке целевой функции
        // алгоритм завершен, найден оптимальный план
        if (column == -1) return 1;

        // выбор строки

        // вычисление отношений
        for (int32_t i = 1; i < constraints + 1; i++) {
            // исключаем деление на ноль
            if (equals(matrix[i][column], 0.0)) {
                ratios[i - 1] = -1.0;
                continue;
            }

            // обработка нуля в столбце правой части
            if (equals(matrix[i][variables + constraints], 0.0)) {
                if (matrix[i][column] > 0.0) {
                    ratios[i - 1] = 0.0;
                } else {
                    ratios[i - 1] = -1.0;
                }
                continue;
            }

            ratios[i - 1] = matrix[i][variables + constraints] / matrix[i][column];
        }

        row = find_row(ratios, constraints, basic_vars);
        // если не нашлось отношений больше или равных нулю 
        // алгоритм заверешн, определно, что оптимального плана
        // не сущесвтует
        if (row == -1) return -1;
        else row++;

        // замена базисной переменной
        basic_vars[row] = column;

        // деление выбранной строки на ведущий элемент
        double_t lead_element = matrix[row][column];
        for (int32_t i = 0; i < variables + constraints + 1; i++) {
            matrix[row][i] /= lead_element; 
        }

        // преобразование строк
        for (int32_t i = 0; i < constraints + 1; i++) {
            if (i == row) continue;

            double_t div_coeff = matrix[i][column];
            for (int32_t j = 0; j < variables + constraints + 1; j++) {
                matrix[i][j] -= matrix[row][j] * div_coeff;
            } 
        }

        // печать этапов
        if (debug) {
            for (int32_t i = 0; i < constraints; i++) {
                std::cout << ratios[i] << "\t";
            }
            std::cout << "\n\n";

            std::cout << variables << " " << constraints << std::endl;
            for (int32_t i = 0; i < constraints + 1; i++) {
                for (int32_t j = 0; j < variables + constraints + 1; j++) {
                    std::cout << matrix[i][j] << "\t";
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }

        memset(ratios, 0, sizeof(double_t) * constraints);
        column = -1;
        row = -1;    
    }

    delete[] basic_vars;
    delete[] ratios;
}

bool lp_methods::equals(double_t value_1, double_t value_2) {
    return (fabs(value_1 - value_2) < 0.000001);
}

int32_t lp_methods::find_row(double_t* ratios, int32_t size, int32_t* basic_vars) {
    double_t min_value = -1.0;
    int32_t min_row = -1;

    for (int32_t i = 0; i < size; i++) {
        // пока не найдена хотя бы одна подходящая строка
        if (min_value < 0 && ratios[i] >= 0.0) {
            min_value = ratios[i];
            min_row = i;
            continue;
        }
        
        // если значение отношения >= нуля и меньше нынешнего
        if (ratios[i] >= 0 && ratios[i] < min_value) {
            min_value = ratios[i];
            min_row = i;
            continue;
        }

        // если значения совпадают, выбирается та строка, которой
        // соотвествует переменная с меньшим индексом
        if (equals(min_value, ratios[i]) && basic_vars[min_row] > basic_vars[i]) {
            min_value = ratios[i];
            min_row = i;
        }
    }

    return min_row;
}