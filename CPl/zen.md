# ZEN of this C++ Lecutre

* Do NOT use global variables! (eg. std::cout) throughout your code
* Test ALL THE code
* Put everything into a library and call it from a "dumb" executable project
* Variablen mit geschweiften Klammern `Date nice{};` initalisieren (weglassen und runde Klammern funktioniert nicht immer, bsp. `Date default();` ist eine Funktionsdeklaration)
* Use const when ever possible
    * Also on member functions!
      ```c++
      struct Hello {
          void sayHello() const;
      };
      ```
    * Const to the right:
        ```c++
        int const theAnswer{42}; // Read: set 42 as theAnswer of constant type int
        ```
    * const means constant and ≠ final in Java (where the object can change)
    * Gehört zur "natur"/Signatur einer Funktion (also bsp. in Klasse)
    * Use `const &` for potentially big Data (eg. Strings)
* Define variables **as local as possible**
* Don't use Friends!


## Just good style

* Include your header files first
* Use ``#include <>`` for libraries from the stdlib and ``#include "..."`` otherwise
* Never forget the semicolon after a class declaration.

## General C++ Zen

* All entities in a C++ program must be declared before they can be used
    => Put all declarations for a module exported functionality into a coresponsing header file
* Only One Definition is allowed (but multiple deklaration) - therefore use Guards in the header files.
* The range of values of int, long usw. is *implementation defined*
* Be aware of undefined behaviour and stay away from it!

## Undefined Behaviour

* Mehrere funktionsaufrufe als Parameter für einen Funtionsaufruf - Reihenfolge ist nicht garantiert!:
    ```c++
    foo(baa(1), baa(2), baa(3));
    ```


## Testat Review
* Eigene Includes ("") vor System includes (<>)

```c++
// Eigene Headers
#include "my-header.h"
// ...
// System Includes
#include <system-headers>
// ...

```

* Include <iostream> sollte nur für die main()-Funktion verwendet werden - sonst reicht typischerweise `<istream>` und/oder `<ostream>`

## Konstruktoren

Default Konstruktoren mit `default`-Keyword angeben

```c++
class Word {
public:
    Word() = default;
    explicit Word(std::string const & value);
};
```

Wann immer möglich die **Initialisierungsliste** nutzen. Vorsicht: Die Initialisierunsreihenfolge ist gleich der Reihenfolge der Member (oben nach unten) in der Klasse!


Das `explicit` verhindert implizite umwandlung

## Wann inline?

Inline immer dann verwenden, wenn:

* Kurz/offensichtlich (Bsp. `!=` mit `!(x == y)`)
* Keine Includes benötigt werden
* Wenn Templates verwendet werden

!!! todo

    Wann implizit `inline`?

## Wo operatoroverloading definieren


!!! todo

    ...?

## Snippets

```c++
bool Word::isValidWord(std::string const & value) {
    return !value.empty() &&
        std::all_of(
            std::begin(value),
            std::end(value), static_cast<int(*)(int)>(std::isalpha));
}

bool Word::operator <(Word const & rhs) const {
    return std::lexicographical_compare(
        std::begin(value),
        std::end(value),
        std::begin(rhs.value),
        std::end(rhs.value), [](char l, char r) {
            return std::tolower(l) < std::tolower(r);
        });
}

bool Word::operator ==(Word const & rhs) const {
    return std::equal(
        std::begin(value),
        std::end(value),
        std::begin(rhs.value),
        std::end(rhs.value),
        [](char l, char r) {
            return std::tolower(l) == std::tolower(r);
        });
}
```
