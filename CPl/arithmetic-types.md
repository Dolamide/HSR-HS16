# Arithmetische Typen
## Beispiel: Ring5

Ring5 = $$k \mod 5$$, also die invariant, dass der Wert immer zwischen 0 und 4 liegt.

Arithmetische Typen müssen auf Gleichheit geprüft werden können! Speziell wichtig für Testbarkeit (`ASSERT_EQUAL`-Makro).

Wenn der Output-Shifting-Operator (`<<`) überschrieben wird, gibt CUTE einen schöneren Output.

Das `constexpr`-Schlüsselwort garantiert, dass der Compiler die Funktion evaluiert.

```c++
#ifndef RING5_H_
#define RING5_H_
#include <iosfwd>
#include <boost/operators.hpp>

struct Ring5 :
    boost::equality_comparable<Ring5>,  // Nutze boost für `!=` Vergleich  
    boost::addable<Ring5>               // += und -= operatoren mit boost
{
private:
    unsigned val;
public:
    explicit constexpr Ring5(unsigned x = 0u)
        : val{x % 5}{
    }

    // Getter for the value
    unsigned value() const {
        return val;
    }

    bool operator==(Ring5 const & r) const {
        return val == r.val;
    }
    Ring5 operator+=(Ring5 const & r) {
        val = (val + r. val) % 5;
        return *this;
    }
    Ring5 operator*=(Ring5 const & r) {
        val = (val * r. val) % 5;
        return *this;
    }
    //...
};

// Multiplication with two Ring5 Values
inline Ring5 operator*(Ring5 l, Ring5 const &r) {
	l *= r;
	return l;
}

// Output shifting operator
inline std::ostream & operator<<( std::ostream & out, Ring5 const & r) {
    out << "Ring5{" << r.value() << '}';
    return out;
}
#endif /* RING5_H_ */
```
