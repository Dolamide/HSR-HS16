# Tips

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

## Elemente aus stream in vektor/set einlesen
Einer Sequence können bequem Iteratoren mitgegeben werden um diese mit diesen Werten zu initialisieren:

```c++
std::set<Word> words{std::istream_iterator<Word>(in), std::istream_iterator<Word>()};

// gleich wie die folgende unschöne Variante
std::set<Word> result{};
copy(std::istream_iterator<Word>(in), std::istream_iterator<Word>(), std::inserter(result, result.begin()));
```

## Const

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
// This is valid however
const int b() {
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
