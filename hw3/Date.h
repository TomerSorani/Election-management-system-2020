#pragma once
#include <iostream>
#include <fstream>
#include <string>
#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

namespace elections
{
	class Date
	{
	private:
		static const int _maxDayPerMonthArr[13];
		int _day;
		int _month;
		int _year;
	public:
		Date(int day = 1, int month = 1, int year = 1900);
		bool setDay(int day);
		bool setMonth(int month);
		bool setYear(int year);
		int getDay() const { return this->_day; }
		int getMonth() const { return this->_month; }
		int getYear() const { return this->_year; }

		//this function print the date dd//mm//yy
		void printDate()const;

		bool save(std::ostream& out) const;
		bool load(std::istream& in);
		void checkFile(std::istream& file);
		void checkFile(std::ostream& file)const;
	};
}