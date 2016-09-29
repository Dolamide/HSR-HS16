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
