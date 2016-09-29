Pitfalls
========

Undefined behaviour
--------------------

* Division durch 0:
  * Modulo 0 ``5%0``

Operator Rangordnung
--------------------

Beispiel:
.. code:: c++
  #include <iostream>
  int main() {
  	int a {4};
      // odd, da ! stärker indet als %
  	std::cout << (!a % 2 ? "even": "odd");
  }

  #include <iostream>

  int main() {
      bool cond{};
      // ausgabe ist 0! Da << stärker bindet als ?
      std::cout << cond ? "Hello" : "Peter";
  }



Floating points
----------------
* NaN ist weder grösser, noch kleiner noch gleich etwas anderes
* Kein == zum vergleich (analog zu Java). In Unittests: ``ASSERT_EQUAL_DELTA(EXP, ACT, DELTA)``

..todo::

  http://en.cppreference.com/w/cpp/language/operator_precedence

Referenzen auf Lokale Variable zurückgeben
------------------------------------------
Nie Referenzen auf lokale Variablen zurückgeben!
Grund: Pointer auf Adresse im Stack - wobei das betreffende
Frame vom Stack abgebaut wurde ("dangeling reference" -> "undefined behaviour")

.. code:: c++

    bsp:
    int& foo(){
    int i = 12;
    return i;
    }

Evaluierung von Rechts nach Links
----------------------------------

.. code:: c++

    // Just a helper method to read a string
    std::string inputName(std::istream &in){
        std::string name{};
        in >> name;
        return name;
    }

    // !!
    sayGreeting(inputName(std::cin), inputName(std::cin));
    // input: a b
    // -> 1. Parameter = b, 2. Parameter = a
