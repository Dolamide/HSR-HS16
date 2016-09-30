Prüfungsdetails
===============


Erlaubte Hilfsmittel
---------------------

* Open Book - also alles
* Notizen AD1
* Code Listings (Übungen)
    * BinarySearchTree.java (Übung 2)

Aufgabentypen
-------------

Einfügen/Löschen von Daten in eienn Binary Search Tree
.......................................................

* Übung 1/ Aufgabe 1,2,3
* Siehe :ref:`schema-bst`
* Löschen üben mit Folie 11 in `D_11_1_BinarySearchTrees.1.0.pdf`


Falls genügend Zeit
-------------------

* Übung 1 / Aufgabe 4:

.. code:: java

    public void add(int lower, int upper, int content) {
      if (lower == upper) { // we found the insert-position
        if (content >= arrayList.get(lower)) {
          arrayList.add(lower+1, content);
        } else {
          arrayList.add(lower, content);
        }
        return;
      }
      // we have to search further
      int middle = (lower + upper) / 2;
      if (content > arrayList.get(middle)) {
        add(middle+1, upper, content);
      } else {
        // check to not have -1 as lower (out of bound)
        add(lower == 0 ? 0 : lower-1, middle, content);
      }
    }
