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

		int GreatestCommonDivisor(int, int);
		void reduction();
		static bool isInt(std::string &);

	public:
		rational();
		rational(const int &, const int &);
		rational(const int &);
		rational(const rational &num);

		rational operator+(const rational &) const;
		rational operator-(const rational &) const;
		rational operator*(const rational &) const;
		rational operator/(const rational &) const;

		rational &operator+=(const rational &);
		rational &operator-=(const rational &);
		rational &operator*=(const rational &);
		rational &operator/=(const rational &);

		bool operator==(const rational &) const;
		bool operator!=(const rational &) const;
		bool operator>=(const rational &) const;
		bool operator<=(const rational &) const;
		bool operator>(const rational &) const;
		bool operator<(const rational &) const;

		bool isInteger() const;
		rational absValue() const;
		rational floor() const;
		rational fractional() const;
		operator double() const;

		friend std::istream &operator>>(std::istream &, rational &);
		friend std::ostream &operator<<(std::ostream &, const rational &);
	};

} // namespace nol0n
