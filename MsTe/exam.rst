Prüfungsdetails
===============


Erlaubte Hilfsmittel
---------------------

* Open Book: Alles erlabut
* Ausnahme: Alte Prüfungen / Probeprüfungen

Aufgabentypen
-------------

Typ A
.....

* Übung X/ Aufgabe Z
* Unterrichtsnotizen vom XY
* Verweis auf Lösungsschema in diesem Dokument


Boxing / Referenzen
...................

Was ist die Ausgabe des folgenden Programms?

.. code:: c#

    public static void Print(ArrayList list) {
        foreach (object o in list) {
            Console.Write("{0}", o);
        }
    }

    public static void Test() {
        ArrayList myList = new ArrayList();
        object o1 = 1;
        object o2 = 2;
        myList.Add(o1);
        myList.Add(o2);
        Print(myList);

        o1 = 4;
        Print(myList);
    }

Lösung:
.. code::

    1 2
    1 2

Grund: Bei den Zuweisungen von o1 und o2 wird geboxt.
Wird o1 auf 4 gesetzt, dann bleibt die referenz in myList unverändert auf 1.
