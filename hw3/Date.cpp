#define _CRT_SECURE_NO_WARNINGS
#include "Date.h"
namespace elections
{
	Date::Date(int day, int month, int year)
	{
		if(year<=0)
			throw std::invalid_argument("Invalid year");
		if (month <= 0 || month>12)
			throw std::invalid_argument("Invalid month");
		if (day <= 0 || day > 31)
			throw std::invalid_argument("Invalid day");
		_day = day;
		_month = month;
		_year = year;
	}
	bool Date::setDay(int day)
	{
		_day = day;
		return true;
	}
	bool Date::setMonth(int month)
	{	
		_month = month;
		return true;
	}
	bool Date::setYear(int year)
	{
		_year = year;
		return true;
	}
	void Date::printDate()const
	{
		std::cout << " " << _day << "/" << _month << "/" << _year << std::endl;
	}
	bool Date::save(std::ostream& out)const
	{
		try {
			out.write(rcastcc(&_day), sizeof(_day));
			checkFile(out);
			out.write(rcastcc(&_month), sizeof(_month));
			checkFile(out);
			out.write(rcastcc(&_year), sizeof(_year));
			checkFile(out);

			return out.good();
		}
		catch (std::string str) { std::cout << str << std::endl; exit(-1); }
	}
	bool Date::load(std::istream& in)
	{
		try {
			in.read(rcastc(&_day), sizeof(_day));
			checkFile(in);
			in.read(rcastc(&_month), sizeof(_month));
			checkFile(in);
			in.read(rcastc(&_year), sizeof(_year));
			checkFile(in);

			return  in.good();
		}
		catch (std::string str) { std::cout << str << std::endl; exit(-1); }
	}
	void Date::checkFile(std::istream& file)
	{
		if (!file.good())
			throw "Error reading";
	}
	void Date::checkFile(std::ostream& file)const
	{
		if (!file.good())
			throw "Error saving";
	}
}