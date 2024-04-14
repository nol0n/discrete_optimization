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

    nol0n::rational ratRes1;
    nol0n::rational ratRes2 = num1;
    double res = 0.;
    switch (op)
    {
    case 1:
        ratRes1 = num1 + num2;
        ratRes2 += num2;
        res = (double(n1) / double(d1)) + (double(n2) / double(d2));
        if (true) {
            std::cout << num1 << " + " << num2 << " = " << ratRes1 << " (" << ratRes2 << ")\n(" << double(ratRes1) << " | " << res << ")\n\n";
        }
        break;
    case 2:
        ratRes1 = num1 - num2;
        ratRes2 -= num2;
        res = (double(n1) / double(d1)) - (double(n2) / double(d2));
        if (true) {
            std::cout << num1 << " - " << num2 << " = " << ratRes1 << " (" << ratRes2 << ")\n(" << double(ratRes1) << " | " << res << ")\n\n";
        }
        break;
    case 3:
        ratRes1 = num1 * num2;
        ratRes2 *= num2;
        res = (double(n1) / double(d1)) * (double(n2) / double(d2));
        if (true) {    
            std::cout << num1 << " * " << num2 << " = " << ratRes1 << " (" << ratRes2 << ")\n(" << double(ratRes1) << " | " << res << ")\n\n";
        }
        break;
    case 4:
        ratRes1 = num1 / num2;
        ratRes2 /= num2;
        res = (double(n1) / double(d1)) / (double(n2) / double(d2));
        if (true) {
            std::cout << num1 << " / " << num2 << " = " << ratRes1 << " (" << ratRes2 << ")\n(" << double(ratRes1) << " | " << res << ")\n\n";
        }
        break;
    }
}

int main(int argc, char* argv[]) {
    for (int i = 0; i < 1000; i++) {
        try {
            randomTest();
        } catch (const char* err) {
            std::cout << err;
        }
    }

    return 0;
}