# Boost Operators

```c++
nclude <boost/operators.hpp>
#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>

#include <tuple>

struct Date
: private boost::less_than_comparable<Date>,
  boost::equality_comparable<Date> {
	Date(int day, int month, int year): day{day}, month{month}, year{year}{}
	bool operator<(Date const & rhs) const{
		return std::tie(year, month, day) < std::tie(rhs.year, rhs.month, rhs.day);
	}
	bool operator==(Date const & rhs) const{
		return std::tie(year, month, day) == std::tie(rhs.year, rhs.month, rhs.day);
	}
private:
	int day, month, year;
};

int main(){
	Date janFirst{1, 1, 2017};
	Date febFirst{1, 2, 2017};

	std::cout << (janFirst < febFirst) << '\n'; // 1 - true
	std::cout << (febFirst < janFirst) << '\n'; // 0 - false

	std::cout << (janFirst > febFirst) << '\n'; // 0 - false
	std::cout << (febFirst > janFirst) << '\n'; // 1 - true

	std::cout << (janFirst == febFirst) << '\n'; // 0 - false
	std::cout << (janFirst != febFirst) << '\n'; // 1 - true
	std::cout << (janFirst == janFirst) << '\n'; // 1 - true

}
```
