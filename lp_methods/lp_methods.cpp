#include <iostream>
#include <fstream>
#include <cstring>
#include <math.h>
#include <lp_methods.hpp>

void lp_methods::simplex_method(const char path_to_file[], bool debug)
{
    int32_t variables = 0;
    int32_t constraints = 0;
    double **matrix;

    // чтение условия из файла
    std::fstream task(path_to_file);

    if (!task)
    {
        std::cerr << "can't open file\n\n";
    }
    else
    {
        std::cout << "file opened\n\n";
    }

    // установка размерности целевой функции и кол-ва ограничений
    task >> variables >> constraints;

    // запись условия задачи
    matrix = new double *[constraints + 1];

    for (int32_t i = 0; i < constraints + 1; i++)
    {
        matrix[i] = new double[variables + constraints + 1]();
    }

    for (int32_t i = 0; i < variables; i++)
    {
        task >> matrix[0][i];
    }

    for (int32_t i = 1; i < constraints + 1; i++)
    {
        for (int32_t j = 0; j < variables; j++)
        {
            task >> matrix[i][j];
        }
        matrix[i][variables + i - 1] = 1.0;
        task >> matrix[i][variables + constraints];
    }

    // печать полученных условий
    if (debug)
    {
        for (int32_t i = 0; i < constraints + 1; i++)
        {
            for (int32_t j = 0; j < variables + constraints + 1; j++)
            {
                std::cout << matrix[i][j] << "\t";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    // применение симплекс метода
    int32_t result = matrix_transfrom(matrix, constraints, constraints, variables, true);

    switch (result)
    {
    case 1:
        std::cout << "found optimal solution: " << -matrix[0][variables + constraints] << "\n";
        break;
    case -1:
        std::cout << "function doesn't have optimal solution\n";
        break;
    }

    for (int32_t i = 0; i < constraints + 1; i++)
    {
        delete[] matrix[i];
    }
    delete[] matrix;
}

void lp_methods::two_phase_method(const char path_to_file[], bool debug)
{
    int32_t variables = 0;
    int32_t constraints = 0;
    double **matrix;

    uint32_t img_vars = 0;
    double *func_coeff;
    char *sign = new char[2]();

    // чтение условия из файла
    std::fstream task(path_to_file);

    if (!task)
    {
        std::cerr << "can't open file\n\n";
    }
    else
    {
        std::cout << "file opened\n\n";
    }

    // установка размерности целевой функции и кол-ва ограничений
    task >> variables >> constraints;

    // запись условия задачи
    matrix = new double *[constraints + 1];
    func_coeff = new double[constraints + 1];

    // в матрице выделяются столбцы для искусственых переменных
    for (int32_t i = 0; i < constraints + 1; i++)
    {
        matrix[i] = new double[variables + constraints * 2 + 1]();
    }

    // чтение целевой функции
    for (int32_t i = 0; i < variables; i++)
    {
        task >> func_coeff[i];
    }

    // заипсь ограничений в таблцу
    for (int32_t i = 1; i < constraints + 1; i++)
    {
        for (int32_t j = 0; j < variables; j++)
        {
            task >> matrix[i][j];
        }

        // проверка знака, если будет >=, то
        // мы вводит искусственнуб переменную
        // и тут мы сразу преобразовываем таблицу
        task >> sign;
        task >> matrix[i][variables + constraints * 2];
        if (sign[0] == '>')
        {
            matrix[i][variables + i - 1] = -1.0;
            for (int32_t k = 0; k < variables + constraints * 2 + 1; k++)
            {
                matrix[0][k] += matrix[i][k];
            }
            matrix[i][variables + constraints + i - 1] = 1.0;
            img_vars++;
        }
        else
        {
            matrix[i][variables + i - 1] = 1.0;
        }
    }

    std::cout << "first phase\n\n";

    // печать полученных условий
    if (debug)
    {
        for (int32_t i = 0; i < constraints + 1; i++)
        {
            for (int32_t j = 0; j < variables + constraints * 2 + 1; j++)
            {
                std::cout << matrix[i][j] << "\t";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    // первая фаза
    int32_t result = matrix_transfrom(matrix, constraints, constraints * 2, variables, true);

    // если удлось найти оптимальное решение (вернулась 1 после первой фазы),
    // то мы переходим ко второй фазе
    if (result == -1)
    {
        std::cout << "haven't been able to find a feasible solution\n";
    }

    std::cout << "second phase\n\n";

    // заменяем целевую функцию и запускаем вторую фазу
    for (int i = 0; i < variables; i++)
    {
        matrix[0][i] = func_coeff[i];
    }
    for (int i = variables; i < variables + constraints * 2 + 1; i++)
    {
        matrix[0][i] = 0.0;
    }

    // применение симплекс метода для второй фазы
    for (int i = 0; i < constraints + 1; i++)
    {
        matrix[i][variables + constraints] = matrix[i][variables + constraints * 2];
    }

    if (debug)
    {
        for (int32_t i = 0; i < constraints + 1; i++)
        {
            for (int32_t j = 0; j < variables + constraints + 1; j++)
            {
                std::cout << matrix[i][j] << "\t";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    result = matrix_transfrom(matrix, constraints, constraints, variables, true);

    switch (result)
    {
    case 1:
        std::cout << "found optimal solution: " << -matrix[0][variables + constraints] << "\n";
        break;
    case -1:
        std::cout << "function doesn't have optimal solution\n";
        break;
    }

    for (int32_t i = 0; i < constraints + 1; i++)
    {
        delete[] matrix[i];
    }
    delete[] matrix;
}

/// @brief применение симплекс метода к задаче, которая приведена к конанической форме
/// @param matrix
/// @param amount of constraints
/// @param amount of variables
/// @param test печать промежуточных этапов
/// @return "1" - найден оптимальный план "-1" - оптимального плана не сущесвует
int32_t lp_methods::matrix_transfrom(double **matrix, int32_t rows, int32_t constraints, int32_t variables, bool debug)
{
    int32_t *basic_vars = new int32_t[rows]();
    double *ratios = new double_t[constraints]();

    find_basis(matrix, rows + 1, variables + constraints, basic_vars);

    int32_t column = -1;
    int32_t row = -1;
    int32_t prev_column = 0;
    while (true)
    {
        // выбор столбца
        for (int32_t i = 0; i < variables + constraints; i++)
        {
            if (matrix[0][i] > 0.0)
            {
                column = i;
                break;
            }
        }
        // не найдено положительного элемента в строке целевой функции
        // алгоритм завершен, найден оптимальный план
        if (column == -1)
        {
            // если базисная переменная присутствует в целевой строке
            // она убиратеся из строки путем преобразований над таблицей
            for (int i = 0; i < rows; i++)
            {
                if (!equals(matrix[0][basic_vars[i]], 0.0))
                {
                    double ratio = matrix[0][basic_vars[i]];
                    for (int j = 0; j < variables + constraints + 1; j++)
                    {
                        matrix[0][j] -= matrix[i + 1][j] * ratio;
                    }

                    // печать этапов
                    if (debug)
                    {
                        std::cout << "removed basic variable from function:\n";
                        for (int32_t i = 0; i < rows + 1; i++)
                        {
                            for (int32_t j = 0; j < variables + constraints + 1; j++)
                            {
                                std::cout << matrix[i][j] << "\t";
                            }
                            std::cout << std::endl;
                        }
                        std::cout << std::endl;
                    }
                }
            }
            return 1;
        }

        // выбор строки

        // вычисление отношений
        for (int32_t i = 1; i < rows + 1; i++)
        {
            // исключаем деление на ноль
            if (equals(matrix[i][column], 0.0))
            {
                ratios[i - 1] = -1.0;
                continue;
            }

            // обработка нуля в столбце правой части
            if (equals(matrix[i][variables + constraints], 0.0))
            {
                if (matrix[i][column] > 0.0)
                {
                    ratios[i - 1] = 0.0;
                }
                else
                {
                    ratios[i - 1] = -1.0;
                }
                continue;
            }

            ratios[i - 1] = matrix[i][variables + constraints] / matrix[i][column];
        }

        row = find_row(ratios, rows, basic_vars);
        // если не нашлось отношений больше или равных нулю
        // алгоритм заверешн, определно, что оптимального плана
        // не сущесвтует
        if (row == -1)
            return -1;
        else
            row++;

        // замена базисной переменной
        basic_vars[row - 1] = column;

        // деление выбранной строки на ведущий элемент
        double lead_element = matrix[row][column];
        for (int32_t i = 0; i < variables + constraints + 1; i++)
        {
            matrix[row][i] /= lead_element;
        }

        // преобразование строк
        for (int32_t i = 0; i < rows + 1; i++)
        {
            if (i == row)
                continue;

            double div_coeff = matrix[i][column];
            for (int32_t j = 0; j < variables + constraints + 1; j++)
            {
                matrix[i][j] -= matrix[row][j] * div_coeff;
            }
        }

        // печать этапов
        if (debug)
        {
            std::cout << "relations: \t";
            for (int32_t i = 0; i < rows; i++)
            {
                std::cout << ratios[i] << "\t";
            }
            std::cout << "\n\n";

            for (int32_t i = 0; i < rows + 1; i++)
            {
                for (int32_t j = 0; j < variables + constraints + 1; j++)
                {
                    std::cout << matrix[i][j] << "\t";
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }

        memset(ratios, 0, sizeof(double) * constraints);
        prev_column = column;
        column = -1;
        row = -1;
    }

    delete[] basic_vars;
    delete[] ratios;
}

bool lp_methods::equals(double value_1, double value_2)
{
    return (fabs(value_1 - value_2) < 0.000001);
}

int32_t lp_methods::find_row(double *ratios, int32_t size, int32_t *basic_vars)
{
    double min_value = -1.0;
    int32_t min_row = -1;

    for (int32_t i = 0; i < size; i++)
    {
        // пока не найдена хотя бы одна подходящая строка
        if (min_value < 0 && ratios[i] >= 0.0)
        {
            min_value = ratios[i];
            min_row = i;
            continue;
        }

        // если значение отношения >= нуля и меньше нынешнего
        if (ratios[i] >= 0 && ratios[i] < min_value)
        {
            min_value = ratios[i];
            min_row = i;
            continue;
        }

        // если значения совпадают, выбирается та строка, которой
        // соотвествует переменная с меньшим индексом
        if (equals(min_value, ratios[i]) && basic_vars[min_row] > basic_vars[i])
        {
            min_value = ratios[i];
            min_row = i;
        }
    }

    return min_row;
}

void lp_methods::find_basis(double **matrix, int32_t rows, int32_t columns, int32_t *basic_vars)
{
    int32_t count_1 = 0;
    int32_t count_0 = 0;
    int32_t row = 0;

    for (int32_t i = 0; i < columns; i++)
    {
        for (int32_t j = 1; j < rows; j++)
        {
            if (equals(matrix[j][i], 1))
            {
                count_1++;
                row = j;
            }
            else if (equals(matrix[j][i], 0))
            {
                count_0++;
            }
        }
        if (count_1 == 1 && count_0 == rows - 2)
        {
            basic_vars[row - 1] = i;
        }
        count_1 = 0;
        count_0 = 0;
    }
}

void lp_methods::backpack_max(const char path_to_file[], bool debug)
{
    int32_t capacity = 0;
    int32_t items = 0;
    int32_t *weights;
    int32_t *prices;
    int32_t **m;
    int32_t *ans;

    // чтение условия из файла
    std::fstream task(path_to_file);

    if (!task)
    {
        std::cerr << "can't open file\n\n";
    }
    else
    {
        std::cout << "file opened\n\n";
    }

    // установка размерности целевой функции и кол-ва ограничений
    task >> items >> capacity;

    // запись условий
    prices = new int32_t[items]();
    for (int32_t i = 0; i < items; i++)
    {
        task >> prices[i];
    }

    weights = new int32_t[items]();
    for (int32_t i = 0; i < items; i++)
    {
        task >> weights[i];
    }

    // вектор с ответом
    ans = new int32_t[items]();

    // запись таблицы
    m = new int32_t *[items + 1]();
    for (int32_t i = 0; i < items + 1; i++)
    {
        m[i] = new int32_t[capacity + 1]();
    }

    for (int32_t i = 1; i <= items; i++)
    {
        for (int32_t j = 1; j <= capacity; j++)
        {
            if (j < weights[i - 1])
            {
                m[i][j] = m[i - 1][j];
                continue;
            }

            if ((m[i][j - weights[i - 1]] + prices[i - 1]) > m[i - 1][j])
            {
                m[i][j] = m[i][j - weights[i - 1]] + prices[i - 1];
            }
            else
            {
                m[i][j] = m[i - 1][j];
            }
        }
    }

    // печать матрицы
    if (debug)
    {
        for (int32_t i = 1; i <= items; i++)
        {
            for (int32_t j = 1; j <= capacity; j++)
            {
                std::cout << m[i][j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    // определение предметов
    int32_t cur_item = items;
    int32_t cur_capacity = capacity;
    while (cur_capacity != 0)
    {
        while (m[cur_item][cur_capacity] == m[cur_item - 1][cur_capacity])
        {
            cur_item -= 1;
            if (m[cur_item][cur_capacity] == 0)
                break;
        }
        ans[cur_item - 1]++;
        cur_capacity -= weights[cur_item - 1];
    }

    // печать ответа
    for (int32_t i = 0; i < items; i++)
    {
        std::cout << ans[i] << "*x" << i + 1 << " ";
    }
    std::cout << std::endl
              << m[items][capacity] << std::endl
              << std::endl;
}
