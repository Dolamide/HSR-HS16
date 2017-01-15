# Prüfungsdetails

* Dauer: 2 Stunden

## Erlaubte Hilfsmittel

* Beliebige Papierunterlagen erlaubt
* Ausnahme: Alte Prüfungen

## Prüfungsbesprechung

* Iterator-Typen (vgl. Prüfung HS13 - Aufgabe 2b)
    * Testate Drucken (mit Syntax Highlighting!): http://jaredpetersen.github.io/codeprinter/index.html
* Safely read ints?
* Übungen Drucken - wie bsp. Topological Sort!
* rvalue / lvalue und temporaries (created by an expression eg foo(baa{x}) -> Einfach links und rechts :/
* ambiguous mit unsigned und double parameter? -> Regel? (Kapitel 3 - Seite 83)
* Was ist multipass iterator?
* `fill()` Funktion auf streams -

Er IST multipass - bsp. input iterator geht nicht - aber forward oder sonst **besser** ist ist mutlipass - kann also kopiert und mehrfach verwendet werden.
Darf mehrfach dereferenziert werden...Man kann mehrfach zugreiffen und dann weiter gehen. Wenn man vorwärts geht werden alle anderen referenzen/kopien invalidiert.

=> Testat review - Folie 16!

"Wenn Sie es so machen wie es durchgestrichen ist, dann sind Sie auf der richtigen Seite" (Errata Folien fett rot durchgestrichen)

```c++
std::vector<int> original{1,2,3};
std::vector<int> moved_to(std::move(original));
original.size(); // 0 - aber micht zwingend! orignal soll nicht mehr als rvalue verwendet werden!
moved_to(); // 3
```

move kann gehen - muss aber nicht (bsp. int move = kopie)

bind obsolet wegen lambdas :)

http://devdocs.io/cpp/io/basic_ios/fill -> für "used to pad the output conversions to the specified field width"


*(it++) -> inkrementiert den iterator
(*it)++ -> erhöht den dereferenzierter Wert (aber bei input iterator nicht, weil rvalue) und rvalue (was const ist) kann nicht verändert werden eg. `3++` geht nicht.

unäre operatoren sind rechts-assotiativ.

Prüfungsrelevant

* Vererbung
* Const-ness
* Alles was in Testat-Aufgaben geübt.
    * Algorithmen, lambdas, templates, operatoren usw.
    * Algoritmen speziell
    * operator overloading etc.
* **TEMPLATES**
* const = andere Signatur -> darum wird entsprehend nie die subklasse aufgerufen.


## Aufgabentypen

### Iteratoren
* Tabellarisches Schema aufschreiben!


* rvalue und lvalue
* Welche headers? (W11, F8)
* Element type as const as possible !!!! (garantiert Frage)
* Don't use Loops - use algorithms
* ADL:
```c++
// adl.h
namespace one {
    struct type_one{};
    void f(type_one){/*...*/}
}
namespace two {
    struct type_two{};
    void f(type_two) {/*...*/}
    void g(one::type_one) {/*...*/}
    void h(one::type_one) {/*...*/}
}
void g(two::type_two) {/*...*/}

// adl.cpp
#include "adl.h"
int main() {
    one::type_one t1{};
    f(t1);                  // one:f(t1)
    two::type_two t2{};
    f(t2);                  // two:f(t2)
    h(t1);                  // Compile-feherl
    two::g(t1);             // explizit → namespace two
    g(t1);                  // Typ passt nicht!
    g(t2);                  // Global
    ::g(t2);                  // explizit global
}
```
* "Konzepte braucht T" - für template functions/classes

## Vorbereitung
* [Optional exercises](https://wiki.ifs.hsr.ch/CPlusPlus/ExW2)
* [Extra Exercises W4](https://wiki.ifs.hsr.ch/CPlusPlus/ExW4)
* [Extra Exercises W5](https://wiki.ifs.hsr.ch/CPlusPlus/ExW5)
