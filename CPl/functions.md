# Functions

Gute funktion:

* Tut genau etwas
* Guter name
* <=3 bzw 5 Parameter
* Möglichs wiederverwertbar

Function declarations in .h and definitions in .cpp files.

!!! todo

    Ausnahme: deduced ()
    deduced
    https://wiki.ifs.hsr.ch/CPlusPlus/files/C++chapter3.pdf
    inline keyword avoids ODR violation?

    member functions (are directly implemented ) & template functions
     -> are implicitly inline

## Scopes

Analog zu java - blöcke mit {} erstellen
können variablen aus parent scope überdecken (shadowing) - wäre in Java nicht möglich!

Closing bracket `}` = "collects garbage"

* stack wird aufgeräumt
* block wird aufgeräumt
* auf objekten wird desktruktor aufgerufen

(mehr dazu später)

## Namespaces

Zweck: Namensräume um kollisionen mit gleichen Namen (ODR) zu vermeiden. (bsp: ``std``)

`::` gibt den globalen präfix zurück. Folglich ist `::std::cout` identisch zu `std::cout`

Namespaces können verschachtelt werden.

```c++
namespace demo{
    void foo(); // 1
    namespace sub {
        void foo(){/*2*/}; // 2 (with definition)
    }
}
namespace demo {
    void bar(){
        foo(); // 1
        sub::foo(); // 2
    }
}

void demo::foo(/*1*/); // definition

int main(){
    using demo::sub::foo;
    foo(); //2
    {
        using namespace demo::sub;
        foo(); // 2
    }
    demo::foo(); //1
    demo::bar();
}
```

!!! tipp

    using std::string; // aber nicht in header files!
    string s{"no std:: prefix required...."}

    using str=std::string
    str t{"short alias"}


Anonymous Namespace:

* Nur für Spezialfälle (und legacy)
* Um code zu verstecken

```c++
    #include <iostream>
    namespace {
        void doit(){
            std::cout << "doit called\n";
        }
    }
    void caller(){
        void print(); // declare print
        print(); // print is called
    }

```
Alternativ: special case: inline namespace

## References

Pass by value: `f(type par)`

Pass by const-ref.: `f(type const &par)`

Pass by reference: `f(type &par)`

return by value: `type f()`

return by reference: `type &f();` `type const &g()`

*Vorsicht: dangeling references - sprich referenz auf lokale variable*

Referenzen nur dann zurückgeben, wenn auch argument - bzw. garantierter laufzeit!

const reference? bedeutet: wir dürfen den Wert nicht verändern!

keine null reference!

**lvalue reference**: Bsp. `std::ostream &out` - für parameter mit side effects

**const references**: `std::vector<int> const &v` für grosse parameter ohne seiteneffekte

**rvalue references**: `std::vector<int> &&` für move und perfect forwarding?!


```c++
std::ostream &print(std::ostream &out){
    return out;
}
```

!!! seealso

    Folien #20ff


## Function Overloading

Der Compiler entscheided, welche signatur verwendet wird!

```c++
void incr(int& var);
void incr(int& var, unsigned delta);
```

Typ muss identisch sein

**Overloading Ambiguity**

```c++
int factorial(int n);
int factorial(double n);

factorial(10u); // ambiguous
factorial(1e1l); // ambiguous
```

Folge: Compilerfehler!

### Default Arguments

Bei der definition! (keine repetition!)

```c++
void incr(int& var, unsigned delta=1);
```

## Functions as Parameters

```c++
void printfunc(double x, double f(double)){
    std::cout << x << ' ' << f(x) << '\n';
}
```

besser:

```c++
void printfunc(double x, std::function<double(double)> f){
    std::cout << x << ' ' << f(x) << '\n';
}
```
