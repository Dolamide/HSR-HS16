# Pitfalls

* Value Range is *implementation defined*!

## Strings

* string literals sind nicht vom typ std::string (but it's usually converted properly when needed)
    * kann mit s suffix erreicht werden (``using namespace std::string_literals`` nicht vergessen)
* trigraphs: eg. "huu??!"; wird zu "huu|". Lösung: raw string: R"(huu??!)"

## Boolean Integral Promotion

Unbedingt auf klammern achten, da sonst bool werte als 0(false) bzw. 1(true) behandelt werden.

x != 0 & 42 % x;

## Undefined behaviour

* Integer Division durch 0:
  * Auch Modulo 0 ``5%0``

## Operator Rangordnung

Beispiel:

```c++
#include <iostream>
int main() {
	int a {4};
  // odd, da ! stärker indet als %
	std::cout << (!a % 2 ? "even": "odd");
}

#include <iostream>

int main() {
  bool cond{};
  // ausgabe ist 0! Da << stärker bindet als ?
  std::cout << cond ? "Hello" : "Peter";
}
```


## Whitespace mit Shift-Operator

```c++
#include <string>
#include <iostream>
int main() {
    std::string name{};
    std::cin >> name;
    std::cout << name;
}

// Besser:
int main() {
    std::string name{};
    std::getline(std::cin, name);
    std::cout << name;
}
```

## Floating points

* NaN ist weder grösser, noch kleiner noch gleich etwas anderes
* Kein == zum vergleich (analog zu Java). In Unittests: ``ASSERT_EQUAL_DELTA(EXP, ACT, DELTA)``

!!! todo

    [Operator Precedence auf cppreference.com](http://en.cppreference.com/w/cpp/language/operator_precedence)

## Referenzen auf Lokale Variable zurückgeben

Nie Referenzen auf lokale Variablen zurückgeben!
Grund: Pointer auf Adresse im Stack - wobei das betreffende
Frame vom Stack abgebaut wurde ("dangeling reference" -> "undefined behaviour")

```c++
int& foo(){
    int i = 12;
    return i;
}
```

## Evaluierung von Rechts nach Links

```c++
// Just a helper method to read a string
std::string inputName(std::istream &in){
    std::string name{};
    in >> name;
    return name;
}

// !!
sayGreeting(inputName(std::cin), inputName(std::cin));
// input: a b
// -> 1. Parameter = b, 2. Parameter = a
```

## Ungleiches Iteratoren-Paar

➪ undefined behaviour!
```c++
std::for_each(begin(values1), end(values2), f);
```

## Zu wenig speicher reserviert

```c++
std::set<unsigned> numbers{1, 2, 3, 4, 5, 6, 7, 8, 9};
std::vector<unsigned> primes{};
auto is_prime = [](unsigned u) {/*...*/};
std::copy_if(begin(numbers), end(numbers), begin(primes), is_prime); // Pfui!
```

`begin()` zeigt irgendwo in den Speicher.

Der Speicher sollte entweder direkt alloziert werden (wenn bekannt wie viele Elemente) oder ein inserter (back_inserter/front_inserter/inserter) verwenden.

```c++
std::copy_if(begin(numbers), end(numbers), back_inserter(primes), is_prime);
// Bsp. Vektor mit 5 Elementen default initialisieren
std::vector<int> myInt(5);
std::copy_if(begin(numbers), end(numbers), begin(top5), in_top5);
```

## Input invalidation
Ändert sich die `size()` zu einem wert grösser als `capacity()`, so wird der iterator (inkl. Referenzen) invalidiert!

```c++
std::vector<unsigned> values{3, 0, 1, 4, 0, 2};
// BÖSE! CONTAINER WIRD WÄHREND DEM DRÜBER ITERIERT WIRD VERÄNDERT
// und damit ungültig
auto f = [&values](unsigned v) { values.push_back(v); };
std::for_each(begin(values), end(values), f);
```
