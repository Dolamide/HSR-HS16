/*
 * Date.h
 *
 *  Created on: Oct 28, 2016
 *      Author: rzi
 */

#ifndef SRC_DATE_H_
#define SRC_DATE_H_
#include <iosfwd>

namespace w6f {

enum Month {
	Jan=1, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec,
	January = Jan, February, March, April, June = Jun, July, September, October, November, December
};

class Date{
private:
public:
	int year, day;
	Month month;

public:
	void print(std::ostream& out) const;
	static bool isValidYear(int year);
	static bool isLeapYear(int year);
	static bool isValidDate(int year, Month month, int day);
	Date(int day, Month month, int year);
	Date(Month month, int day, int year);
	static int  endOfMonth(int year, Month month);
	void nextDay();
	bool operator <(Date const& rhs) const;

};


inline bool operator>(Date const& lhs, Date const& rhs){
	return rhs < lhs;
}
inline bool operator>=(Date const& lhs, Date const& rhs){
	return !(lhs < rhs);
}
inline bool operator<=(Date const& lhs, Date const& rhs){
	return !(rhs < lhs);
}

inline bool operator==(Date const& lhs, Date const& rhs){
	return !(lhs < rhs) && !(rhs < lhs) ;
}
inline bool operator!=(Date const& lhs, Date const& rhs){
	return !(lhs == rhs);
}
} /* namespace w6f */

#endif /* SRC_DATE_H_ */
