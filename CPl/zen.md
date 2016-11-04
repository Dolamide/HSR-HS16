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
* Define variables **as local as possible**


Just good style
----------------
* Include your header files first
* Use``#include <>`` for libraries from the stdlib and ``#include "..."`` otherwise
* Never forget the semicolon after a class declaration.

General C++ Zen
----------------
* All entities in a C++ program must be declared before they can be used
    => Put all declarations for a module exported functionality into a coresponsing header file
* Only on Definition is allowed (but multiple deklaration) - therefore use Guards in the header files.
* The range of values of int, long usw. is *implementation defined*
* Be aware of undefined behaviour and stay away from it!

Undifined Behaviour
--------------------
* Mehrere funktionsaufrufe als Parameter für einen Funtionsaufruf:
    ```c++
    foo(baa(1), baa(2), baa(3));
    ```


### Testat Review
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
