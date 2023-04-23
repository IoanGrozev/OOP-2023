#include "Date.h"
Date::Date() : Date(1, 1, 2000)
{


}



bool isLeapYear(unsigned int year)
{
	if (year <= 1916)
	{
		return year % 4 == 0;
	}
	return ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
}

Date::Date(unsigned int day, unsigned int month, unsigned int year)
{
	update(day, month, year);
}

unsigned int Date::getDayOfWeek() const
{
	if (!isModified)
	{
		return dayOfWeek;
	}

	// Calculate the day of week using Zeller's Congruence
	int q = day;
	int m = month;
	int y = year;
	if (m < 3)
	{
		m += 12;
		y--;
	}
	int h = (q + (13 * (m + 1)) / 5 + y + y / 4 - y / 100 + y / 400) % 7;

	
	h = (h + 5) % 7;

	
	dayOfWeek = h + 1;
	isModified = false;

	return dayOfWeek;
}

bool Date::isEqualTo(const Date& other) const
{
	return year == other.year && month == other.month && day == other.day;
}

void Date::goNextDay()
{
	if (isEqualTo(Date(31, 3, 1916)))
	{
		setDay(14);
		setMonth(4);
		return;
	}

	setDay(day + 1);

	if (day == 1)
	{
		setMonth(month + 1);
		if (month == 1)
		{
			setYear(year + 1);
		}
	}
}

void Date::update(unsigned int day, unsigned int month, unsigned int year)
{
	setYear(year);
	setMonth(month);
	setDay(day);

	isModified = true;
}

void Date::setYear(unsigned int year)
{
	if (isLeapYear(year))
	{
		maxDays[1] = 29; // February
	}
	else
	{
		maxDays[1] = 28;
	}

	this->year = year;
	isModified = true;
}
void Date::setMonth(unsigned int month)
{
	if (month == 0 || month > 12)
	{
		month = 1;
	}

	this->month = month;
	isModified = true;
}
void Date::setDay(unsigned int day)
{
	if (day == 0 || day > maxDays[month - 1])
	{
		day = 1;
	}
	if (year == 1916 && month == 4 && day < 14)
	{
		day = 14;
	}

	this->day = day;
	isModified = true;
}

unsigned int Date::getYear() const
{
	return year;
}
unsigned int Date::getMonth() const
{
	return month;
}
unsigned int Date::getDay() const
{
	return day;
}

void Date::print() const
{
	std::cout << std::setw(2) << std::setfill('0') << day << '.' << std::setw(2) << std::setfill('0') << month << '.';
	std::cout << std::setw(4) << std::setfill('0') << year;
}