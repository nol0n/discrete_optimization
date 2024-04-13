#include <math.h>
#include <rational.hpp>

namespace nol0n
{

rational::rational() {
	numerator = 0;
	denominator = 1;
}

rational::rational(const int &a, const int &b) {
	if (b > 0) {
		numerator = a;
		denominator = b;
	}
	else {
		throw "rational.cpp::rational::rational(int a, int b) denominator must be greater than 0\n";
	}
	this->reduction();
}

rational::rational(const int &a) : numerator(a), denominator(1) {}

rational::rational(const rational &num) {
	numerator = num.numerator;
	denominator = num.denominator;
}

int rational::GreatestCommonDivisor(int A, int B) {
	int a = abs(A); int b = abs(B);
	while (a != 0 && b != 0) {
		if (a > b) {
			a = a % b;
		}
		else {
			b = b % a;
		}
	}
	return a + b;
}

void rational::reduction() {
	int divider = GreatestCommonDivisor(numerator, denominator);
	numerator /= divider;
	denominator /= divider;
}

bool rational::isInt(std::string &str) {
	bool is_number = true;
	int negative = 0;
	if (str[0] == '-') negative = 1;
	if (str[negative] == '0' && str.size() >= (unsigned int)(2 + negative)) {
		is_number = false;
	}
	if (is_number && str[0 + negative] > 47 && str[0 + negative] < 58) {
		for (unsigned int i = negative; i < str.size() - 1; i++) {
			if (str[i] <= 47 || str[i] >= 58) {
				is_number = false;
				break;
			}
		}
	}
	else {
		is_number = false;
	}
	return is_number;
}

rational rational::operator+(rational const& num) {
	rational res;
	if (num.denominator == denominator) {
		res.numerator = num.numerator + numerator;
		res.denominator = denominator;
	}
	else {
		res.denominator = num.denominator * denominator;
		res.numerator = denominator * num.numerator + num.denominator * numerator;
	}
	res.reduction();
	return res;
}

rational rational::operator-(rational const& num) {
	rational res;
	if (num.denominator == denominator) {
		res.numerator = num.numerator - numerator;
		res.denominator = denominator;
	}
	else {
		res.denominator = num.denominator * denominator;
		res.numerator = num.denominator * numerator - num.numerator * denominator;
	}
	res.reduction();
	return res;
}

rational rational::operator*(rational const& num) {
	rational res;
	res.numerator = numerator * num.numerator;
	res.denominator = denominator * num.denominator;
	res.reduction();
	return res;
};

rational rational::operator/(rational const& num) {
	rational res;
	if (num.numerator != 0) {
		res.numerator = numerator * num.denominator;
		res.denominator = denominator * num.numerator;
		res.reduction();
		return res;
	}
	else {
		throw "rational.cpp::rational::rational::operator/(rational const& num) num numinator must be not equal 0\n";
	}
};

bool rational::operator==(rational const& num) const {
	int a = numerator * num.denominator, b = num.numerator * denominator;
	if (a == b) {
		return true;
	}
	else {
		return false;
	}
}

bool rational::operator!=(rational const& num) const {
	return !(*this == num);
}

bool rational::operator>=(rational const& num) const {
	if (*this == num || *this > num) {
		return true;
	}
	else {
		return false;
	}
}

bool rational::operator<=(rational const& num) const {
	if (*this == num || *this < num) {
		return true;
	}
	else {
		return false;
	}
}

bool rational::operator>(rational const& num) const {
	int a = numerator * num.denominator, b = num.numerator * denominator;
	if (a > b) {
		return true;
	}
	else {
		return false;
	}
}

bool rational::operator<(rational const& num) const {
	return !(*this > num);
}

rational::operator double() const {
	return double((double)this->numerator / (double)this->denominator);
}

std::istream& operator>>(std::istream& ins, rational& num) {
	std::string a = "a";
	int entered = 0;
	while (!entered) {
		std::cout << "enter numerator: ";
		ins >> a;
		if (!num.isInt(a)) {
			std::cout << "enter natural number\n";
			continue;
		}
		try {
			num.numerator = std::stoi(a);
			entered = 1;
		}
		catch (std::out_of_range const&) {
			std::cout << "value must be in range from -2,147,483,648 to 2,147,483,647\n";
		}
	}

	entered = 0;
	num.denominator = 0;

	while (!entered) {
		std::cout << "enter denominator: ";
		ins >> a;
		if (!num.isInt(a)) {
			std::cout << "enter natural number\n";
			continue;
		}
		try {
			num.denominator = std::stoi(a);
			if (num.denominator < 1) throw "rational.cpp::std::istream& operator>>(std::istream& inputStream, rational& num) value must be a natural number\n";
			entered = 1;
		}
		catch (std::out_of_range const&) {
			std::cout << "value must be in range from 1 to 2,147,483,647\n";
		}
		catch (const char* exception) {
			std::cout << exception;
		}
	}
	num.reduction();
	return ins;
}

std::ostream& operator<<(std::ostream& outs, const rational& num) {
	outs << num.numerator;
	if (num.numerator != 0 && num.denominator != 1) std::cout << "/" << num.denominator;
	return outs;
}

} // namespace nol0n
