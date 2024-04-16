#include <math.h>
#include <rational.hpp>

namespace obv
{

	rational::rational()
	{
		numerator = 0;
		denominator = 1;
	}

	rational::rational(const int &a, const int &b)
	{
		if (b > 0)
		{
			numerator = a;
			denominator = b;
		}
		else
		{
			throw "rational.cpp::rational::rational(int a, int b) denominator must be greater than 0\n";
		}
		this->reduction();
	}

	rational::rational(const int &a) : numerator(a), denominator(1) {}

	rational::rational(const rational &num)
	{
		numerator = num.numerator;
		denominator = num.denominator;
	}

	int rational::GreatestCommonDivisor(int A, int B)
	{
		int a = abs(A);
		int b = abs(B);
		while (a != 0 && b != 0)
		{
			if (a > b)
			{
				a = a % b;
			}
			else
			{
				b = b % a;
			}
		}
		return a + b;
	}

	void rational::reduction()
	{
		int divider = GreatestCommonDivisor(numerator, denominator);
		numerator /= divider;
		denominator /= divider;
	}

	bool rational::isInt(std::string &str)
	{
		bool is_number = true;
		int negative = 0;
		if (str[0] == '-')
			negative = 1;
		if (str[negative] == '0' && str.size() >= (unsigned int)(2 + negative))
		{
			is_number = false;
		}
		if (is_number && str[0 + negative] > 47 && str[0 + negative] < 58)
		{
			for (unsigned int i = negative; i < str.size() - 1; i++)
			{
				if (str[i] <= 47 || str[i] >= 58)
				{
					is_number = false;
					break;
				}
			}
		}
		else
		{
			is_number = false;
		}
		return is_number;
	}

	rational rational::operator+(rational const &num) const
	{
		rational res;
		if (num.denominator == denominator)
		{
			res.numerator = num.numerator + numerator;
			res.denominator = denominator;
		}
		else
		{
			res.denominator = num.denominator * denominator;
			res.numerator = denominator * num.numerator + num.denominator * numerator;
		}
		res.reduction();
		return res;
	}

	rational rational::operator-(rational const &num) const
	{
		rational res;
		if (num.denominator == denominator)
		{
			res.numerator = numerator - num.numerator;
			res.denominator = denominator;
		}
		else
		{
			res.denominator = num.denominator * denominator;
			res.numerator = num.denominator * numerator - num.numerator * denominator;
		}
		res.reduction();
		return res;
	}

	rational rational::operator*(rational const &num) const
	{
		rational res;
		res.numerator = numerator * num.numerator;
		res.denominator = denominator * num.denominator;
		res.reduction();
		return res;
	};

	rational rational::operator/(rational const &num) const
	{
		rational res;
		if (num.numerator != 0)
		{
			res.numerator = numerator * num.denominator;
			res.denominator = denominator * num.numerator;

			if (res.denominator < 0)
			{
				res.numerator *= -1;
				res.denominator *= -1;
			}

			res.reduction();
			return res;
		}
		else
		{
			throw "rational.cpp::rational::rational::operator/(rational const& num) num numinator must be not equal 0\n";
		}
	};

	rational &rational::operator+=(rational const &num)
	{
		if (num.denominator == denominator)
		{
			numerator += num.numerator;
		}
		else
		{
			numerator = denominator * num.numerator + num.denominator * numerator;
			denominator *= num.denominator;
		}

		reduction();

		return *this;
	}

	rational &rational::operator-=(rational const &num)
	{
		if (num.denominator == denominator)
		{
			numerator -= num.numerator;
		}
		else
		{
			numerator = numerator * num.denominator - num.numerator * denominator;
			denominator *= num.denominator;
		}

		reduction();

		return *this;
	}

	rational &rational::operator*=(rational const &num)
	{
		numerator *= num.numerator;
		denominator *= num.denominator;

		reduction();

		return *this;
	};

	rational &rational::operator/=(rational const &num)
	{
		if (num.numerator != 0)
		{
			numerator *= num.denominator;
			denominator *= num.numerator;

			if (denominator < 0)
			{
				numerator *= -1;
				denominator *= -1;
			}

			reduction();

			return *this;
		}
		else
		{
			throw "rational.cpp::rational::rational::operator/(rational const& num) num numinator must be not equal 0\n";
		}
	};

	bool rational::operator==(rational const &num) const
	{
		int a = numerator * num.denominator, b = num.numerator * denominator;
		if (a == b)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool rational::operator!=(rational const &num) const
	{
		return !(*this == num);
	}

	bool rational::operator>=(rational const &num) const
	{
		if (*this == num || *this > num)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool rational::operator<=(rational const &num) const
	{
		if (*this == num || *this < num)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool rational::operator>(rational const &num) const
	{
		int a = numerator * num.denominator, b = num.numerator * denominator;
		if (a > b)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool rational::operator<(rational const &num) const
	{
		int a = numerator * num.denominator, b = num.numerator * denominator;
		if (a < b)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool rational::isInteger() const
	{
		return denominator == 1;
	}

	rational rational::absValue() const
	{
		rational result = (*this);

		if (result < rational(0)) 
		{
			result *= -1;
		}

		return result;
	}

	rational rational::floor() const 
	{
		rational result;

		if ((*this) < rational(0) && !(*this).isInteger()) 
		{
			result = rational((this->numerator - this->denominator) / this->denominator);
		}
		else 
		{
			result = rational(this->numerator / this->denominator);
		}

		return result;
	}

	rational rational::fractional() const
	{
		rational result = (*this) - (*this).floor();

		return result;
	}

	rational::operator double() const
	{
		return double((double)this->numerator / (double)this->denominator);
	}

	std::istream &operator>>(std::istream &ins, rational &num)
	{
		std::string a{};

		ins >> a;
		if (!num.isInt(a))
		{
			throw("enter natural number\n");
		}
		try
		{
			num.numerator = std::stoi(a);
		}
		catch (std::out_of_range const &)
		{
			throw("value must be in range from -2,147,483,648 to 2,147,483,647\n");
		}
		num.denominator = 1;

		num.reduction();
		return ins;
	}

	std::ostream &operator<<(std::ostream &outs, const rational &num)
	{
		outs << num.numerator;
		if (num.numerator != 0 && num.denominator != 1)
			std::cout << "/" << num.denominator;

		// outs << num.numerator << "/" << num.denominator;

		return outs;
	}

} // namespace obv
