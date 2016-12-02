# Prüfungsdetails


## Erlaubte Hilfsmittel

* Beliebige Papierunterlagen erlaubt
* Ausnahme: Alte Prüfungen

## Aufgabentypen

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

## Vorbereitung
* [Optional exercises](https://wiki.ifs.hsr.ch/CPlusPlus/ExW2)
* [Extra Exercises W4](https://wiki.ifs.hsr.ch/CPlusPlus/ExW4)
* [Extra Exercises W5](https://wiki.ifs.hsr.ch/CPlusPlus/ExW5)
