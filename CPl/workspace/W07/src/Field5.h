#ifndef FIELD5_H_
#define FIELD5_H_
#include <iosfwd>
#include <iostream>

struct Field5 {
	explicit constexpr Field5(unsigned x = 0u) :
			val { x % 5 } {
	}
	constexpr unsigned value() const {
		return val;
	}
	constexpr operator unsigned() const {
		return val;
	}
	constexpr bool operator==(Field5 const &r) const {
		return val == r.val;
	}
	constexpr bool operator!=(Field5 const &r) const {
		return !(*this == r);
	}
	constexpr Field5 operator+=(Field5 const &r) {
		val = (val + r.value()) % 5;
		return *this;
	}
	constexpr Field5 operator-=(Field5 const &r) {
		val = (5+(val - r.value())) % 5;
		return *this;
	}

	constexpr Field5 operator*=(Field5 const&r) {
		val = (val * r.value()) % 5;
		return *this;
	}
	constexpr Field5 operator+(Field5 const &r) const {
		return Field5 { val + r.val };
	}
	constexpr Field5 operator-(Field5 const &r) const {
		int result{static_cast<int>(val) - static_cast<int>(r.val)};
		if(result < 0){
			result = 5 + (result % 5);
		}
		return Field5 { static_cast<unsigned>(result)};
	}
	constexpr Field5 operator*(Field5 const &r) const {
		return Field5 { val * r.val };
	}
	constexpr Field5 operator/=(Field5 const &r) const {
		Field5 self = *this;
		self *= r;
		return self;
	}
private:
	unsigned val;
	Field5 inverse() const{
			if (val==2) return Field5{3};
			if (val==3) return Field5{2};
			return *this; // not exaclty right for 0
	}
};

namespace F5 {
constexpr Field5 operator"" _F5(unsigned long long v) {
	return Field5 { static_cast<unsigned>(v % 5) };
}
}
std::ostream& operator <<(std::ostream& out, const Field5& r);

#endif /* FIELD5_H_ */

