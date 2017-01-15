# Tips & Tricks

## Imports
```
std::string         // #include <string>
std::cin            // #include <iostream>
std::istream        // #include <iosfwd> in *.h, sonst istream
std::ostream        // #include <iosfwd> in *.h, sonst ostream
std::istream_iterator    // #include <iterator>
std::vector         // #include <vector>
std::setw(2)        // #include <iomanip>
std::isalpha        // #include <cctype>
std::toupper        // #include <cctype>
std::lexicographical_compare // #include <algorithm>
std::begin / std::end   // #include <iterator>
std::multiset       // #include <set>

```

## Algorithms-Headers
`<algorithm>`
: Gut für die miesten Algorithmen - bsp. `all_of`, `for_each`, `transform`, `rotate` usw.

`<functional>`
: Standard funktoren, beispielsweise `plus`, `negate`, `logical_or` uder `less`, `equal_to` usw.


`<numeric>`
: Für generische numerische Funktionen (wobei einige funktionen auch auf nicht-numerischer context angewant werden kann - bsp. accumulate auf `std:string`) `accumulate`, `inner_product`, `partial_sum`, `adjacent_difference`, `iota`
## Stream-Headers

`<iosfwd>`
: Schlanker Header, welcher für "Deklaration" verwendet werden kann/soll - also in Header-Files. Definiert nur, dass es streams gibt.

`<ostream>`
: Header, welcher eingebunden werden soll, wenn effektiv in der implementation mit Outputstreams gearbeitet wird.

`<istream>`
: Header, welcher eingebunden werden soll, wenn effektiv in der implementation mit Inputstreams gearbeitet wird.

`<iostream>`
: Bringt gleiche Funktionalität wie `<ostream>` und `<istream>` - aber zusätzlich die Konstanten `std::cin` und `std::cout`


## String Stream

Zweck: Bsp. Testing

```c++
std::istringstream iss {"1  +4"};
```

## String aus stream lesen

```c++
std::string name{}
in >> name;
```

## Sequence ausgeben

```c++
#include <iterator> // for ostream_iterator
#include <algorithm> // for copy
#include <iostream> // if using std::cout

using out_itr = std::ostream_iterator<int>;
// using out_itr = std::ostreambuf_iterator<int>;
std::copy(v.begin(), v.end(), out_itr{std::cout, ", "}); // TRAILING DELIMITER!
                                    // `ist x, y, z, `
```

## Elemente zählen
Um die Elemente einer Sequence zu zählen kann der Algorithmus `distance` verwendet werden.

```c++
    // Kurz und knackig
return std::distance(std::istream_iterator<Word>(in), std::istream_iterator<Word>());

// Macht das gleiche - aber nicht so schön!
int target = 0;
for_each(std::istream_iterator<Word>(in), std::istream_iterator<Word>(), [&target](auto workd){target++;});
return target;
```

## Elemente aus stream in vektor/set einlesen (inserter)
Einer Sequence können bequem Iteratoren mitgegeben werden um diese mit diesen Werten zu initialisieren:

```c++
std::set<Word> words{std::istream_iterator<Word>(in), std::istream_iterator<Word>()};

// gleich wie die folgende unschöne Variante
std::set<Word> result{};
copy(std::istream_iterator<Word>(in), std::istream_iterator<Word>(),
     std::inserter(result, result.begin()));
```

## diverses zu `const`

```c++
void demo() {
	const int x{1};
	// is equal to
	int const y{1}; // Prefere THIS notation!
}

// Non-Member function is allways const
// the function below therefore can not have a const modifier
//int a() const{
//	return 1;
//}

// This is valid however, because it returns a `const int`
// BUT DON'T DO IT THAT WAY!
const int b1() {
	return 1;
}

// do it that way!
int const b2() {
	return 1;
}
// Parameters can be const as well
const int c(const int x, int const y) {
	return x + y;
}
// Reference Parameters can be const
const int d(const int & x, int const & y) {
	return x + y;
}

struct Class1
{
	int const cval;
	int val;

	int m1() const{
		// "Writing" is forbidden
		// this->val = 14;
		// But "reading" is OK - both, for const and nonconst memebers.
		return this->val;
	}
	void m2(int x){
		this->val = x;
	}
	// Const members can not call other non-const members
	void m3(int x) const{
		m2(x);
	}
	// Const Members must be initialized in the
	// member initializer lists
	Class1(int x) : cval{x}{
		// val can also be initialized here
		val = x;
	}
};
// Const is valid here - because const is part
// of the variable declaration and not part
// of the class definition
class Class2 {} const x{};
//class Class2 {} x{} const; does not compile

void e(Class1 const & c){
	c.m1(); // OK, since m1 is const
	//c.m2(); // ERROR: Is not const
}
```

## Iteratoren navigieren mit next und prev

Wenn iteratoren **const** sind, dann kann man bsp. nicht `--it` machen. Dafür gibt es die Methoden `next` und `prev` in der stdlib.

```c++
std::multiset<int> s{1,2,3,4, 5, 6, 7};
auto const it = end(s);
std::cout << *std::prev(it); // 7
std::cout << *std::prev(it, 3); // 5
```

!!! note

    `advance` geht leider auch nicht mit const iteratoren. Hat keinen return wert - sondern ruft einfach n mal `--` bzw. `++` auf dem iterator auf.

## Was für ein iterator?

Es gibt `iterator`, `reverse_iterator`, `const_iterator` und `const_reverse_iterator`. Ist ein objekt `const` bsp `std::string const myString{"abc"}` und man ruft `begin(myString)` auf, so bekommt man ein const iterator zurück. mit rbegin bzw. rend einen `...reverse_iterator`

## auto conversion

```c++
explicit operator std::multiset<T, COMPARE>() const{
	return std::multiset<T, COMPARE>{this->cbegin(), this->cend()};
}
```

## Find with comparator
```c++
// alternativ zu auto: const_iterator
// dann wird aber 	using const_iterator = typename Base::const_iterator; benötigt!
auto find(T const elm) const {
    return std::find_if(this->cbegin(), this->cend(), [&elm](auto const x){
        return !COMPARE{}(elm, x) && !COMPARE{}(x, elm);
    });
}
// std::copy(vs.find('H'), vs.cend(), out{cout, ' '}); // works! BUT note *c*end!
```

!!! note

    Comperatoren sind **nicht reflexiv** (es gilt also nicht `COMP{}(x,x) == true`), aber **transitiv** (`COMP{}(x, y) && COMP{}(y, z)` → `COMP{x, z}`). Auf **Gleichheit** kann mit `!COMPARE{}(elm, x) && !COMPARE{}(x, elm);` geprüft werden.  Es gilt eine **asymmetrische Relation**, also ``!COMPARE{}(elm, x) == COMPARE{}(elm, x)``


## Copy in OS
```c++
using out=std::ostream_iterator<int>;
set<int> s{1, 2, 3, 4};
std::copy(s.begin(), s.end(), out{cout, "-"});
```
→ OUTPUT IST: `1-2-3-4-` mit trailing `-`
