# Template Function

Template Functions ermöglichen Typsichere Container und Funktionen ähnlich wie Generics in Java. Dies ermöglicht, Funktionen und Typen für Typen wiederzuverwenden, welche erst später definiert werden (Bsp. `std::vector` wurde von `MyClass` geschrieben, kann aber trotzdem zusammen verwendet werden: `std::vector<MyClass>`)

Im Gegensatz zu Generics in Java wird der Typenname implizit bei der Benützung bestimmt.

In der Vergangenheit gab es Probleme wie verwirrende Compiermeldungen. Diese Probleme sind heute aber behoben.

## Kontext (Lambdas)

Lambdas können Definiert werden, ohne dass ein Typ für die Parameter oder den Rückgabewert angegeben werden muss. Alle Werte werden am "Ort des Geschehens" zur Laufzeit bestimmt.

```c++
[x=1](auto y){return x*y;}
```

## Definition

Eine Template-Funktion wird einmal definiert und kann beliebig oft mit unterschiedlichen typen instantiiert werden.

Für die Definition wird das Keyword `template` zusammen mit Eckigen Klammern verwendet `<>`. Oft werden Template-Funktionen inline definiert.

!!! todo

    Warum inline?

```c++
namespace MyMin{
template <typename T>
// inline definition!
T const& min(T const& a, T const& b){
    return (a < b)? a : b ;
}
}
```


## Verwendung

template argument deduction
: T wird automatisch beim Funktionsaufruf anhand der argumente bestimmt (zur Compiletime!)

Um die definierte Template-Funktion zu Verwenden, kann diese einfach mit den ensprechenden Typen aufgerufen werden. Die Template-Function wird bei der Verendung für die gegebenen Argumente instantiiert.

```c++
#include "MyMin.h"
#include <string>

int main(int argc, char **argv) {
    using MyMin::min;
    const int i{88};
    min(i, 42); // min<int>()

    const double pi{3.1415};
    const double e{2.7182};
    min(pi, e); // min<double>()
    min(2, pi); // Compile error!
    min(static_cast<double>(2),pi); // min<double>()

    std::string s1{"Hello"};
    std::string s2{"Hello World"};
    min(s1, s2); // Compilererror: min ist mehrdeutig (*)
    MyMin::min(s1, s2);  // MyMin::min<string>()

    min("Pete","Toni"); // Result: "Toni" (**)
    min<std::string>("Pete", "Toni"); //Result: "Pete"
    min("Pete"s, "Toni"s); //Result: "Pete"
}
```

*: TODO

**: String-Literals sind `char arrays`! Darum wird hier der Pointer mitgegeben - und dann werden die Pointer verglichen - daher das falsche Resultat.

!!! todo

    * Warum ist min(s1, s2) mehrdeutig?

## Concepts

**Anforderungen** an Template-Typen werden implizit bei dern Verwendung evaluiert.

Im Falle von `min` sind die Concepts:

* `operator<(T, T)` muss auf `T` definiert sein.
* Rückgabewert muss in `bool` konvertierbar sein - Bsp. `void` ist nicht möglich.

!!! todo

    Was für andere Kozepte für `max`?!
    ➪ Muss kopierbar / "movebar" sein. (Rückgabetyp)
    Folie 11

## Overloading

Funktion-Overlading ist möglich - wobei immer die spezifischste Funktion gewinnt.

* Overloading sollte im allgemeinen vermieden werden.
* Die Sichtbarkeit der Overloads muss gleich sein
* Alle Deklarationen sollten in einen gemeinsamen Header

```c++
namespace MyMin{
template <typename T>
T const& min(T const& a, T const& b){
    return (a < b)? a : b ;
}

// Funktioniert, da spezifischer!
char const * min(char const* a, char const * b){
    // TODO: Don't do this inline - avoid std::string in header!
    return std::string(a) < std::string(b)? a:b;
}
}
```

## Variadic
Ermöglicht 0..n Argumente mitzugeben.

```c++
template <typename...ARGS>
void variadic(ARGS...args){
    println(std::cout,args...); // println is also a variadic template function
}
```

Wenn explizit minimal ein Argument benötigt wird, muss dies zusätzlich angegeben werden:

```c++
void println(std::ostream &out)
{
    out << "\n";
}

template<typename HEAD, typename... Tail>
void println(std::ostream &out, Head const& head, Tail const& ....tail){
    out << head;
    if(sizeof...(tail)){
        out << ", ";
    }
    println(out, tail...); // recursive call
}
```

```
out, x, [y, z]
out, y, [z]
out, z, []<- Tail ist leer
out
```

!!! todo

    * Aber head und Tail sind nicht identisch!
    * Wo ist nun der Head?!
    * Das kann aber nicht gut gehen...?! Keine Abbruchbedinnung
