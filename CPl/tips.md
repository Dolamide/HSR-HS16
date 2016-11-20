# Tips

## Imports
```
std::string         // #include <string>
std::cin            // #include <iostream>
std::istream        // #include <iosfwd>
istream_iterator    // #include <iterator>
std::vector         // #include <vector>
std::setw(2)        // #include <iomanip>
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
