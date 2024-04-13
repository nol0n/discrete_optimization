#pragma once

#include <iostream>
#include <string>

namespace nol0n
{

	class rational
	{
	private:
		int numerator;
		int denominator;

		int GreatestCommonDivisor(int a, int b);
		void reduction();
		static bool isInt(std::string &str);

	public:
		rational();
		rational(const int &a, const int &b);
		rational(const int &a);
		rational(const rational &num);

		rational operator+(const rational &num) const;
		rational operator-(const rational &num) const;
		rational operator*(const rational &num) const;
		rational operator/(const rational &num) const;

		rational& operator+=(const rational &num);
		rational& operator-=(const rational &num);
		rational& operator*=(const rational &num);
		rational& operator/=(const rational &num);

		bool operator==(const rational &num) const;
		bool operator!=(const rational &num) const;
		bool operator>=(const rational &num) const;
		bool operator<=(const rational &num) const;
		bool operator>(const rational &num) const;
		bool operator<(const rational &num) const;

		operator double() const;

		friend std::istream &operator>>(std::istream &ins, rational &num);
		friend std::ostream &operator<<(std::ostream &outs, const rational &num);
	};

} // namespace nol0n
