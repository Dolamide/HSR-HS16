# Streams

Mit dem Shifting Operatoren kann in in ein Stream geschrieben
bzw. gelesen werden. Nicht Signifikante Zeichen (Spaces etc) werden
beim lesen übersprungen.

```c++
std::cin >> x;
std::cout << x;
```

Dabei ist es auch möglich, mehrere Werte auf einmal zu lesen
bzw. zu schreiben:

```c++
std::cout << "the value is " << x << '\n';

// Read number (left), operator and number (right)
int lhs{-1};
char op {};
int rhs{-1};
if(in >> lhs >> op >> rhs){
	return calc(lhs,rhs, op);
}
// äquivalent zu:

in >> lhs
in >> op
in >> rhs
```

Es gibt auch die methoden ``get`` und ``put`` mit
denen ein einzelnes Zeichen gelesen werden kann.
Dabe werden auch Leerzeichen gelesen

## State

Streams haben state - Wenn der State nicht good ist
muss der Stream clear (falls möglich) "repariert" werden,

Es gibt das Fail-, Eof- und Bad-Bit (wobei Bad selten vorkommt.)


### Robustes einlesen von int-values

```c++
int inputAge(std::istream& in) {
    while(in){
        std::string line{};
        getline(in, line);
        std::istringstream is{line};
        int age{-1};
        if (is >> age)
            return age;
    }
    return -1;
}
```

oder

```c++
int inputAge(std::istream& in) {
    while(in) {
        int age{-1};
        if(in >> age)
            return age;
        in.clear(); // remove fail flag
        in.ignore(); // skip one char
    }
    return -1;
}
```

IO Manipulator
--------------

Dienen dazu, den Output zu formatieren.

```c++
std::cout << 42 << '\t'
          << std::oct << 42 << '\t'
          << std::hex << 42 << '\n';
std::cout << 42 << '\t' // std::hex is sticky
          << std::dec << 42 << '\n';
std::cout << std::setw(10) << 42
          << std::left<< std::setw(5)<< 43 << "*\n";
std::cout << std::setw(10) << "hallo"<<"*\n";

double const pi{std::acos(0.5) * 3};

std::cout << std::setprecision(4) << pi << '\n';
std::cout << std::scientific << pi <<  '\n';
std::cout << std::fixed << pi*1e6 << '\n';
```

!!! warning

    Alle Manipulatoren ohne Parameter haben eine permanente Wirkung (bsp. left, oct, hex)!
    Diejenigen mit Parameter dagegen (``setw(10)``) gelten nur einmal


!!! todo

    Study the `Input/output manipulators <http://en.cppreference.com/w/cpp/io/manip>`_

    How can you read a std::string name with the code std::cin >> name; if the name provided consists of several words? How can you read the rest of the input into the string variable?
    Look at declaration of std::getline() function and explain its parameter passing. Why is the std::string parameter passed as reference?
    (ex. https://wiki.ifs.hsr.ch/CPlusPlus/ExW2)
