# Testat 3
## indexableSet.h
```c++
#ifndef INDEXABLESET_H_
#define INDEXABLESET_H_

#include <set>
#include <stdexcept>
#include <functional>
#include <string>

template<typename T, typename COMPARE=std::less<T>>
class indexableSet : public std::set<T, COMPARE>{
	using Base=std::set<T, COMPARE>;
public:
	using std::set<T, COMPARE>::set;
	T const & at(int const t) const {
// 		Alternative (t darf dann nicht const sein)
//		if (t<0) t = this->size()+t;
//		// dann check of out of range < 0 >= size
//		return *next(this->begin(),t);

		const unsigned absolute = std::abs(t);
		if(absolute > this->size() || (t >= 0 && absolute == this->size())){
			throw std::out_of_range{"Given index is out of range"};
		}
		if(t < 0){
			return *prev(this->end(), absolute);
		}
		return *next(this->begin(), absolute);
	}
	T const & operator[](int index) const {
		return this->at(index);
	}
	T const & front() const{
		return this->at(0);
	}
	T const & back() const{
		return this->at(-1);
	}
};
#endif /* INDEXABLESET_H_ */
```
## Test.cpp
```c++
struct caselessCompare {
	bool operator()(std::string first, std::string second) const {
		return std::lexicographical_compare(first.begin(), first.end(), second.begin(),
				 second.end(), [](auto c1, auto c2) {
			 return std::tolower(c1) < std::tolower(c2);
		});
	}
};
void test_elements_in_iterator_range_with_caseless_comparator() {
	indexableSet<std::string, caselessCompare> champions { "yankees", "Giants", "cardinals", "Sox", "Royals", "CUBS" };
	std::vector<std::string> expected { "cardinals", "CUBS", "Giants", "Royals", "Sox", "yankees" };
	std::vector<std::string> actual { std::begin(champions), std::end(champions) };
	ASSERT_EQUAL(expected, actual);
}
```
