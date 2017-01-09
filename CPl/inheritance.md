# Inheritance and dynamic Polymorphism

## Gründe für Vererbung

* Funktionallität erben
    * Mix-in's von leeren Basisklassen
    * Oft kombiniert mit Templates `boost::equality_comparable<T>`
* Anpassung einer Basisklasse mit einer "Datenlosen" Subklasse
    * Siehe Kapitel [Dynamic Heap Memory Management](heap.html) (Bsp. `IndexableAdapter<T>`)
    * Objektadapter ist oft besser als Klassenadapter
* Vererbung für dynamic binding
    * Funktionalliät zur Laufzeit auswechseln (Bsp. Objektadapter auswechseln zur Laufzeit, Stretegy, Composite)
    * **Static-Binding mit Templates** - nicht mit Vererbung
    * Gemeinsame Schnittstelle. (Interfaces: Alle Members mit `0` initialisieren)

## Probleme mit Vererbung

* Stärkste mögliche Kopplung!
* 100% der Basisklasse muss für Subklasse gelten
* Object Slicing bei Pass by Value (Nur Basis Klassen Member werden transferiert)
* Shadowing / Member Hiding

```c++
struct Base {
    void foo(int i) const {};
}
struct Derived:Base {
    void foo() const {}; // Hides `foo(int i)`!
    // Workaround:
    using Base::foo;
}
```

## Syntax
```c++
class Parent {};
class Sub : public Parent {};
struct Sub : Parent {};
```

`Sub` erbt fast alles - was aber fehlt sind Konstruktoren.

Konstruktoren können geerbt & aufgerufen werden. Ein Konstrukt wie `super` existiert nicht.

```c++
class Sub : public Parent {
public:
    using Parent::Parent;

    // Base{} ist Aufruf von Super-Konstruktor
    // Base{} MUSS (wenn Angegeben) immer erster Aufruf sein
    Sub(int i) : Base{}, myvar{i}
    {
    }

    // Konstruktoraufruf delegieren
    Sub() : Sub{42} {}
};
```

* Für Interface-Inheritance muss die Basisklasse `public` sein - wenn Private sind nur mix-in Klassen sinnvoll.
* Sichtbbarkeit: `public` und `protected` in Subklasse sichtbar aber Vorsicht: Shadowing ist möglich!


(Bei Mehrfachvererbung ist die Reihenfloge entscheidend. Aufzählung mit `,` separiert.)

(Klassendefinition ist Typendefinition - darum ist `;` entscheidend. Man könnte einen Variablennamen direkt hinten anfügen, wie bei `int x;`.)

`virtual`-Keyword ermöglicht, dass Subklasse Funktion überschreibt - natürlich muss die Funktionssignatur auch identisch sein (Vorsicht `const`! F19). Override-Keyword ist Optional aber gut - denn es gibt einen Compile-Fehler. Virtual wird "vererbt" (muss nicht explizit angegeben werden).

`virtual` legt eine [Tabelle (vtable)](https://de.wikipedia.org/wiki/Tabelle_virtueller_Methoden) im Hintergrund an, welche den Dynamic Dispatch macht. Darum muss dies explizit angegeben werden.


!!! warning

    Fehlendes `virtual` = kein Dynamic Dispatch!

!!! warning

    Wenn eine Funktion mit und ohne `const` definiert sind müssen(können) beide überladen werden, da unterschiedliche Signatur.

## Abstrakte Basisklassen / "Interfaces"
Abstract-Funktionen mit 0 initialisieren

```c++
struct AbstractBase {
    virtual ~AbstractBase(){}
    virtual void doitnow()=0;
};
```

Vorsicht: basisklassen mit virtuellen Members benötigen virtual destructor wenn Speicher auf dem Heap ohne `shared_ptr` alloziert wird (you shouldn't do that anyway)!

## Best Pracitce von Polymorphen Klassen

* Immer pass-by-reference (Pass-by-value: Object Slicing)
* Virtual Keyword nur dann wenn nötig
* Low Coupling: Minimale Abhängigkeiten
* High Cohesion: Nur Etwas aber etwas Gut
* SOLID:
    * Single Responsibility Principle
    * Open Closed Principle (open for extension but should be closed for modification)
    * Liskov Substitution Principle (the derived classes should be perfectly substitutable for their base classes)
    * Interface Segregation Principle: no clients should be forced to implement methods which it does not use
    * Dependency Inversion Principle

## Fallstudie (15 Punkte Aufgabe in Prüfung!)

```c++
#include <iostream>

using std::cout;
struct Animal {
    void  makeSound() { cout << "---\n";}
    virtual void move() { cout << "---\n";}
    Animal() { cout << "animal born\n";}
    ~Animal() { cout << "animal died\n";}
};
struct Bird : Animal {
    virtual void makeSound() { cout << "chirp\n";}
    void move() { cout << "fly\n";}
    Bird() { cout << "bird hatched\n";}
    ~Bird() { cout <<"bird crashed\n";}
};
struct Hummingbird : Bird {
    void makeSound() { cout << "peep\n";}
    virtual void move() { cout << "hum\n";}
    Hummingbird() { cout << "hummingbird hatched\n";}
    ~Hummingbird() { cout <<"hummingbird died\n";}
};

int main(){
    cout << "(a)----------------------------\n";
    Hummingbird hummingbird;
    Bird bird = hummingbird;
    Animal & animal = hummingbird;

    cout << "(b)-----------------------------\n";
    hummingbird.makeSound();
    bird.makeSound();
    animal.makeSound();

    cout << "(c)-----------------------------\n";
    hummingbird.move();
    bird.move();
    animal.move();

    cout << "(d)-----------------------------\n";
}

```

Vorsicht im a)

* Impliziter Aufruf des Default Konstruktors des Parents
* Kopie mit Slicing -> **KEIN Output - weil Copy-Konstruktor!**

Vorsicht im b)

* Aufruf über Animal -> Weil nicht `virtual`!

Vorsicht d)

* Destruktoren werden aufgerufen!
* Werden von unten nach oben destruiert.


`virtual` von `move` bei `Hummingbird` ist unnötig.

Probleme:

* virtual nicht in Basisklasse: Function Hiding / Kein Dynamic Dispatch
* slicing
* (destruktor `virtual` (wenn virtual member hat ist))
* Initialisierung von Hummingbird nicht offensichtlich - weil geschweifte Klammern fehlen.
* Output nur im Default-Konstruktor - nicht aber im Copy-Konstruktor!
* Funktionen, die auf dem Objekt selber nichts ändern sollten `const` sein!

!!! warning

    `auto x = a;` erzeugt immer eine Kopie. Kann mit `auto & x = a;` "Java-Style" verwendet werden. -> `&` IMMER BRAUCHEN für dynamic Polymorphism!


```
(a)-----------------------------
animal born
bird hatched
humminbird hatched
(b)-----------------------------
peep
chirp
(c)-----------------------------
hum
fly
hum
(d)-----------------------------
bird crashed
animal died
humminbird died
bird crashed
animal died
```

## Übungsaufgaben

Frage:
How can you store shapes (shape is the base class an can have derived classes like square and diamond, see exercise below) in a std::vector without producing memory leaks or object slicing?
 > Shared Pointer in den Vektor!

Slicing verhindern → Copy-Konstruktor löschen.
