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
