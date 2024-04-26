#pragma once

#include <iostream>
#include <string>

#include <BigInt.hpp>

namespace obv
{

	class rational
	{
	private:
		BigInt numerator;
		BigInt denominator;

		BigInt GreatestCommonDivisor(BigInt, BigInt);
		void reduction();
		static bool isInt(std::string &);

	public:
		rational();
		rational(const long long &, const long long &);
		rational(const long long &);
		rational(const BigInt &, const BigInt &);
		rational(const BigInt &);
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

		friend std::istream &operator>>(std::istream &, rational &);
		friend std::ostream &operator<<(std::ostream &, const rational &);
	};

} // namespace obv
