/*
 * Date.cpp
 *
 *  Created on: Oct 28, 2016
 *      Author: rzi
 */

#include "Date.h"
#include <stdexcept>
#include <sstream>
#include <iomanip>

namespace w6f {

void Date::print(std::ostream& out) const {
	auto ch = out.fill('0');
	out << std::setw(2) << day << '.';
	out << std::setw(2) << month << '.';
	out << std::setw(4) << year;
	out.fill(ch);
}
bool Date::isValidYear(int year) {
	return year >= 1813 && year < 10000;
}
bool Date::isLeapYear(int year) {
	return !(year % 4) && ((year % 100)	|| !(year % 400));
}
bool Date::isValidDate(int year, Month month, int day) {
	if (! isValidYear(year) || day <=0 ) return false;
	switch (month){
	case Jan: case Mar: case May: case Jul: case Aug: case Oct:
	case Dec: return day <= 31;
	case Apr: case Jun: case Sep: case Nov: return day <= 30;
	case Feb: return day <=(isLeapYear(year)?29:28);
	}
	return false;
}
Date::Date(int day, Month month, int year)
:year{year},month{month},day{day}{
	if (! isValidDate(year,month,day))
		throw std::out_of_range{"invalid date"};
}
Date::Date(Month month, int day, int year) : Date(day, month, year){};

void Date::nextDay() {
	++day;
}

} /* namespace w6f */
