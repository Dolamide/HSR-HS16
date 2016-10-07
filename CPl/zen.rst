ZEN of this C++ Lecutre
========================

* Do NOT use global variables! (eg. std::cout) throughout your code
* Test ALL THE code
* Put everything into a library and call it from a "dumb" executable project
* Use const when ever possible
    * Also on member functions!
      .. code:: c++

        struct Hello {
            void sayHello() const;
        };
    * 

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
