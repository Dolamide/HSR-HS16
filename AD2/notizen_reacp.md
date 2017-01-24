# Tree

* Kann sowohl map wie auch Multimap seini (F9) -> Bei Gleichheit mehrere Varianten möglich. Für Prüfung relevant F10.
* Binary-Search Tree: Null terminiert oder hat er Blattknoten?
* Löschen wiederholt sich bei avl und splay. F14: **Nicht der Knoten wird gelöscht**, sondern der Inhalt wird kopiert (Knoten 5 wird gelöscht und 3 damit überschriben).
    * Vgl. Splay: Welcher knoten wird gesplayed
* erkennen, ob Leaf nodes oder null terminiert: Tree root kann nicht null sein. -> Also "Wie sieht der leere Baum aus"?

* AVL ist binärer Suchbaum - also AVL extends BST
* Doppelrotation: F15
    * Gut Lesen, was alles aufgeschrieben werden muss!
    * Bei zeit mit cut/link verifizieren
* Beim löschen
    * in grösseren Teilbaum runtergehen
    * Evtl. Mehrere Umstrukturierungen nötig -> Weiter in Root scahuen. Bei Einfügen dagegen nur eine Rotation nötig.
* CHeck mit Inorder-Traversierung

* **Splay Baum** extends Binary Search Tree
* TODO: Recap!
* F2 Multimap
* Check mit Inorder-Traversionerung
* Splay-Fälle (zig-zig, zig-zag, zig)
   * ZWISCHENFÄLLE!
* Tiefster intern zugegriffener Konten wird gesplayed (F12/11/13?)

* Merge sort -> Bsp. partition
* F18 nicht inplace (Inpace = Memory ist braucht nicht zusätzlich in Abhängigkeit zu n speicherplatz)
* Mergesort vs. quicksort usw.vergleichen ablauf.
* Vorsicht: Gute Pivot Wahl


* Stirling Approximation: "Untere Grenze"
* Bucket-Sort: Bessere Performance, aber ohne vergleiche

* Substring definition inkusive oder exklusive?
* Boyer-Moore: Nur Strategie mit +1 ! (Heuristiken F11/F12 kommen NICHT) F16
* Aber F7

* Tries -> Ganzer Text anschauen (nur wenn text statisch)
* Komprimierung
* Suffix geht auch -> F9 (`O(n)` nicht herleiten - zu komplex!)

* Dynamic Programming
* LCS: Mehrere Varianten: Springen wenn geht oder wie war das? Siehe Notizen (oder Robin :)).

* Graphen: DFS ist auch "grundalgorithmus" -> Darum nochmals gut recap
* incidentEdges bzw. vertizes immer Relevant! Wird immer Alphanumerisch sortiert sein.
* Biconnected Komponenten "vergessen" (verstehen)
* Alle, die nicht forward oder back sind cross
* Floyd (mit dynamischer Programmierung)
* Recap topologische sortierung (im Graph)
* Bellman Ford geht mit negativ - aber viel schlechter. Mit DAG viel effizienter.

* Minimum spanning trees!!! (Bei hoher vermaschung Prim-Jarnick sonst Kruskal)
* Boruvka (in Praxis nie - mehr historisch)


* Vorsicht: Expected vs. garantiert
* Annahmen aufschrieben (nachvollziehbar!)
* Wie immer gut lesen (und markieren)
* "Was ist komplexität dieses Algorithmus" "herleiten" können -> Spick AD1?
* Evlt. Folien analog zu MsTe Drucken. => Kläberli!
* Ein Punkt = ca. 0.5 Min!
* Code der Übungen Drucken!
