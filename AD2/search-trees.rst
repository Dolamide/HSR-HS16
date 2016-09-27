Search Trees
=============
.. _schema-bst:

Binary-Search
-------------
**Binäre Suche** -> bei jedem Schritt die Anzahl der Kandidaten halbieren

Beispiel ``find(7)`` in einer Array-Basierten Multimap:

.. image:: images/binary-search-array.png


Varianten
..........

* Implementierung mittels **sortierten Sequenz**
    * ``find`` benötigt ``O(log n)``
    * ``insert`` benötigt ``O(n)``
    * ``remove`` benötigt ``O(n)``
    * => Nur bei kleinen Multimaps praktikabel, da shifting nötig (teuer)
* **Binary-Search-Tree** (Siehe unten)
    * Mit "Placeholders" (Guards/Sentinels)
    * Mit null

.. warning::

    Entscheidende Frage bei der Implementierung: Null-Terminiert oder mit Guards?


Binary-Search-Trees
--------------------
* Binärbäume kennen wir schon von AD1 (beispielsweise Heap)


.. image:: images/u_v_w.png


* **key(u) ≤ key(v) ≤ key(w)**
    * Keys welche im linken Subtree sind, sind kleiner gleich root
    * Keys welche im rechten Subtree sind, sind grösser als root
* **Inorder-Traversierung** gibt sortierte Reihenfolge aus
* Externe Knoten speichern keine Daten
* Die Blattknoten sind als "Placeholders" implementiert ("Guards" / "Sentinels")

.. seealso::

    * Data Structures & Algorithms in Java - Sexth Edition, Seite 425.
    * `Interactive Binary-Search-Tree visualization <https://www.cs.usfca.edu/~galles/visualization/BST.html>`_

Suche
......

* Ist der Key k gleich den key des Knotens => Suche beendet.
* Ist der Key k kleiner als der key des Knotens => Linker Subtree
* Ist der Key k grösser als der key des Knotens => Rechter Subtree
* Ist der Knoten ein Blattknoten, so wurde der Eintrag nicht gefunden
* Performance: ``O(h)``, wobei h die höhe ist.
    * ist der Baum balanciert: ``O(log n)``
    * Worst case: ``O(n)`` (entartet, wie bei LinkedList)

.. warning::

    Achte auf Grenzwerte! Wird bei bsp. 911 nach links fortgefahren, so kann kein Wert >= 911 vorkommen!

.. image:: images/broken_binary_tree.jpg

.. literalinclude:: code/BinaryTree.java
    :language: java
    :lines: 1-9


Einfügen
........

#. Suche nach den Key.
#. Falls der Key existiert, ersetze den Wert oder bei Multimap: suche weiter.
#. Wenn man in einem Blattknoten endet: In einen internen Knoten umwandeln.

.. literalinclude:: code/BinaryTree.java
    :language: java
    :lines: 11-23

Löschen
.......

Es gibt 3 mögliche Szenarien:

* Der zu löschende Knoten hat **zwei Blattkinder**
* Der zu löschende Knoten hat **ein Blattkind**
* Der zu löschende Knoten hat **keine Blattkinder**

Vorsicht:

-> Anhand von Grafik #11 nachspielen
-> #19/#20

#. Suche nach dem Key
#. Falls Knoten p gefunden:
    * max. 1 Blattkind: "Ersetze" den gefundenen Konten durch diesen Kindknoten (oder einen der Sentinels, falls nur externe Kindknoten)
    * Genau 2 Blattkinder:
        * Suche den grössten Knoten r im Subtree (immer rechts!)
        * Ersetze p mit r und r mit dessen linken Kindknoten (r hat ja keinen rechten Kindknoten)

Die Knoten werden nicht effektiv umgehängt - nur deren Werte!

.. literalinclude:: code/BinaryTree.java
    :language: java
    :lines: 25-60


Ausgabe inorder
................

.. literalinclude:: code/BinaryTree.java
    :language: java
    :lines: 62-68

ALV-Tree
---------
Performance von Binary-Search-Trees ist nicht immer ideal. Die Einfüge-Reihenfolge
ist entscheidend.

Ein ALV-Tree hat die gleichen eigenschaften wie ein Binary-Tree ("extends BinaryTree") aber die zusätzliche
Eigenschaft, dass sich **die Höhe der Kinder von v höchstens um 1 unterscheiden**.

Ein AVL-Tree ist "balanciert", wenn:

* ``b(k) = Höhe(links) – Höhe(rechts)``
* es muss gelten: ``b(k)`` ist ``–1``, ``0`` oder ``+1``

Höhenbeweis
...........

.. todo::

    Folgt in Vorlesung W3 (#3, #4)

Einfügen
.........

Beim Einfügen kann ``-2 ≤ b(x) ≤ 2`` gelten - was eine Verletzung der AVL-Balance ist!

.. image:: images/alv_insert_wrong.png

Man kann 4 generell mögliche Fälle unterscheiden

#. Einfügen in den linken Teilbaum des linken Sohnes
#. Einfügen in den rechten Teilbaum des linken Sohnes
#. Einfügen in den linken Teilbaum des rechten Sohnes
#. Einfügen in den rechten Teilbaum des rechten Sohnes

Vorgehen zur Wiederherstellung der AVL-Balance:

#. Wandere von neu eingefügten Knoten aus aufwärts und Prüfe bei jedem Koten, ob ALV_Balance verletzt wird
#. Tritt eine Verletzung ein, muss der Baum rotiert werden.
   Die betroffenen Knoten müssenn nun so umgehängt werden, dass die Inorder Reihenfolge gleich bleibt.

.. image:: images/alv_insert_rotate.png

Sobald das einmal gemacht wurde ist die ALV-Eingeschaft wiederhergestellt, denn
eine grössere Differenz als 2 ist je Einfügeoperation nicht möglich.


Splay-Tree
-----------
