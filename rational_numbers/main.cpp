#include <iostream>
#include <iomanip>
#include <vector>
#include <random>

#include <rational.hpp>

int getInt() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> int_dist(-2000, 2000);
    
    return int_dist(gen);
}

int getPositiveInt() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> int_dist(1, 20);
    
    return int_dist(gen);
}

int getOp() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> int_dist(0, 3);
    
    return int_dist(gen);
}

void randomTest() {
    int n1 = getInt();
    int n2 = getInt();
    int d1 = getPositiveInt();
    int d2 = getPositiveInt();

    nol0n::rational num1(n1, d1);
    nol0n::rational num2(n2, d2);

    char op = getOp();

    nol0n::rational ratRes;
    double res = 0.;
    switch (op)
    {
    case 1:
        ratRes = num1 + num2;
        res = (double(n1) / double(d1)) + (double(n2) / double(d2));
        std::cout << num1 << " + " << num2 << " = " << ratRes << " (" << double(ratRes) << " | " << res << ")\n";
        break;
    case 2:
        ratRes = num1 - num2;
        res = (double(n1) / double(d1)) - (double(n2) / double(d2));
        std::cout << num1 << " - " << num2 << " = " << ratRes << " (" << double(ratRes) << " | " << res << ")\n";
        break;
    case 3:
        ratRes = num1 * num2;
        res = (double(n1) / double(d1)) * (double(n2) / double(d2));
        std::cout << num1 << " * " << num2 << " = " << ratRes << " (" << double(ratRes) << " | " << res << ")\n";
        break;
    case 4:
        ratRes = num1 / num2;
        res = (double(n1) / double(d1)) / (double(n2) / double(d2));
        std::cout << num1 << " / " << num2 << " = " << ratRes << " (" << double(ratRes) << " | " << res << ")\n";
        break;
    }
}

int main(int argc, char* argv[]) {
    // std::vector<nol0n::rational> numbers;

    // numbers.reserve(100);
    // for (int i = 0; i < 100; i++) {
    //     try {
    //         nol0n::rational tmp(getInt(), getPositiveInt());            
    //         std::cout << tmp << "\n";      
    //         numbers.emplace_back(tmp);
    //     } catch (const char* err) {
    //         std::cout << err;
    //     }
    // }

    for (int i = 0; i < 100; i++) {
        try {
            randomTest();
        } catch (const char* err) {
            std::cout << err;
        }
    }

    return 0;
}