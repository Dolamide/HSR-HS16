# Graphen

## Allgemein

Ein Graph besteht aus einem Set von **Vertizes** (=Node) und einer Liste von Vertizes-Paaren, den **Kanten** (=Edge). Sowohl die Vertizes als auch die Kanten können Nutzdaten speichern.

Einsatzgebiete

* Elektronische Schaltungen
* Transport-Netzwerke
* Computer-Netzwerke
* Datenbanken
* UML
* Garbage Collection
* ...

### Begriffe

gerichtete Kanten
: Ein geordnetes Paar von Vertizes (u,v), wobei u dem _Ursprung_ und v dem _Ziel_ entspricht.

ungerichtete Kanten
: Ein ungeordnetes Vertizes-Paar

gerichtete Graph
: alle Kanten sind erichtet

ungerichtete Graph
: alle Kanten sind ungerichtet

Gerichtete und ungerichtete Kanten könnten in einem Graph gemischt werden (Bsp. UML Klassendiagramm) - ist aber für AD2 aber nicht relevant.

<img src="images/example_graph.png" style="float: right; max-width: 30%;" >

End-Vertizes
: = Endpunkte. `U` und `V` sind Endpunkte der Kante `a`

Inzident
: = enden. `a`, `b` und `d` sind inzident in V

Adjazent
: = benachbart. `U` und `V` sind adjazent

Grad
Degree
: Anzahl inzidenter Kanten - `X` besitzt Grad 5. Egal ob gerichtete Kanten oder nicht - dann gibt es zusäzlich die Attribyute incomming/outgoing.

Parallele Kanten
: `h` und `i` sind paralelle Kanten

Schleife
: `j` ist eine Schleife

Pfad
: Sequenz von abwechselnden Vertizes und Kanten. **Beginnt** und **endet** mit einem **Vertex**. Beispiel `P=(U,c,W,e,X,g,Y,f,W,d,V)`

Einfacher Pfad
: Ein Pfad, so dass alle Vertizes und Kanten unterschiedlich sind.  Beispiel `P=(V,b,X,h,Z)`

(Einfacher) Zyklus
: Analog zu Pfad, wobei der Zyklus im Ausgangsvertex endet. Das Letzte Element in der Sequenz ist eine Kante. Beispiel `Z=(V,b,X,e,W,c,U,a)`

Subgraph
: Ein Subgraph S eines Graphen G ist ein Graph, so die Kanten und Vertizes von S eine Teilmenge der Kanten respektive Vertizes von G sind.

Spanning Subgraph
: Ein spanning (aufspannender) Subgraph A des Graphen G ist ein Subgraph, welcher alle Vertizes von G enthält.

Verbundener Graph
Connectivity
: Ein Graph ist verbunden, wenn zwischen **jedem Paar** ein Pfad besteht!

Baum
: Ein Verbundener ungerichteter Graph ohne Zykeln. Hat kein Root wie beim _Wurzelbaum_ da irelevant.

![](images/tree.png)
: Baum / Tree

Wald
: Ein Wald ist ein ungerichteter Graph ohne Zyklen

![](images/forest.png)
: Wald / Forest

Aufgespannter Baum
Spanning Tree
: Ein aufspannender Subgraph (also alle Vertizes, aber nur Teilmenge der Kanten), welcher auch ein Baum ist.

Anzahl Vretizes mit $$n$$, Anzahl Kanten mit $$m$$


### Eigenschaften

* Summe der Grade aller Vertizes ist immer 2m: $$\sum_v deg(v)=2m$$
* In einem ungerichteten, einfachen Graphen gilt: $$m \le n (n-1)/2$$

### Implementations-Varianten

#### Kanten-Listen Struktur

Diese Struktur nutzt zwei Sequenzen - eine für die Vertizes und eine für die Kanten. Diese Muss eigene Datenstruktur sein, da ein Backlink vorhanden ist. Dieser ermöglicht, dass schnell gelöscht werden kann.

Vorsicht: Die Vertizes haben **keine** Referenzen auf die Kanten!

![](images/graph_kls.png)
: Schema Kanten-Listen Struktur - Quelle: Goodrich, Tamassia

#### Adjazenz-Listen Struktur
Die Adjazenz-Listen Struktur ist analog zur Kanten-Listen Struktur, wobei es zustzlich für jeden Knoten eine Listen (Sequenz) von Kanten gibt.

![](images/graph_als.png)
: Schema Adjazenz-Listen Struktur - Quelle: Goodrich, Tamassia

#### Adjazenz-Matrix Struktur
Bei der Adjazenz-Matrix Struktur gibt es auch zwei Sequenzen - eine mit den Vertizes und eine mit den Kanten. Die Vertex Objekte haben zusätzlich einen Index.
Dieser wird in einer Matrix wird die "Verkabelung" abgelegt - bsp. Vertex mit Index `0` und Vertex mit Index `1` sind über die Kante `a` Verbunden.

![](images/graph_ams.png)
: Schema Adjazenz-Matrix Struktur - Quelle: Goodrich, Tamassia


### API

* `endVertices(e)`
* `opposite(v, e)`
* `areAdjacent(v, w)`
* `replace(v, x)` - Wert auf Vertex `v` mit `x` ersetzen
* `replace(e, x)` - Wert auf Kante `e` mit `x` ersetzen
* `insertVertex(o)` - Neuer Vertex mit Wert `o` erzeugen. Erzeugt "Insel"
* `insertEdge(v, w, o)` - Neue Kante zwischen Vertizes `v` und `w` einfügen
* `removeVertex(v)` - Alle incident (eingehenden) Kanten auch löschen.
* `removeEdge(e)`
* `incidentEdges(v)` - länge des Resultats enspricht dem Grad!
* `vertices()`
* `edges()`


### Performance

|                       | Kanten Liste | Adjazenz Liste | Adjazenz Matrix |
|-----------------------|---------|-------------------------|---------|
| space                 | $$n+m$$ | $$n+m$$                 | $$n^2$$ |
| `incidentEdges(v)`    | $$m$$   | $$deg(v)$$              | $$n$$   |
| `areAdjacent (v, w)`  | $$m$$   | $$min(deg(v), deg(w))$$ | 1       |
| `insertVertex(o)`     | 1       | 1                       | $$n^2$$ |
| `insertEdge(v, w, o)` | 1       | 1                       | 1       |
| `removeVertex(v)`     | $$m$$   | $$deg(v)$$              | $$n^2$$ |
| `removeEdge(e)`       | 1       | 1                       | 1       |

$$n$$ Anzahl Vertizes
$$m$$ Anzahl Kanten

Die Back-References in die Datenstruktur sowohl in der Adjazenz Liste als auch in der Adjazenz Matrix sind essentiel um gute Performance zu erreichen. Dies war auch schon in AD1 beim Heap der Fall.

## Depth-First Search (DFS)

Depth-First Search ist eine **Technik für die Traversierung** eines Graphen:

* Besucht alle Vertizes und Kanten
* Bestimmt, ob der Graph verbunden ist
* Findet die verbundenen Komponenten eines Graphen
* Berechnet einen aufgespannten Wald eines Graphen
* **Rekursiv**

Wenn es einen Pfad gibt, dann findet die Tiefensuche diesen garantiert, wobei dies nicht der Kürzeste sein muss!

Der Algorithmus verwendet verschiedene Labels, welche er auf den Vertizes und den Kanten setzt. Dies kann effizient mit bsp. einer Hash-Map implementiert werden.

Um den Algorithmus bsp. auf Papier auszuführen muss eine klare sortierung der Kanten/Vertizes beim Aufruf der Methoden `vertices`, `edges` und `incidentEdges`  definiert werden - bsp. aufsteigend sortiert. **Vorgehen:** Graph aufzeichen, Labels hinzufügen und durch den Code steppen.

```
Algorithm DFS(G)
        Input graph G
        Output labeling of the edges of G
            as discovery edges and
            back edges
    for all u ∈ G.vertices()
        setLabel(u, UNEXPLORED)
    for all e ∈ G.edges()
        setLabel(e, UNEXPLORED)
    for all v ∈ G.vertices()
        if getLabel(v) = UNEXPLORED
            DFS(G, v)

Algorithm DFS(G, v)
        Input graph G and a start vertex v of G
        Output labeling of the edges of G
            in the connected component of v
            as discovery edges and back edges
    setLabel(v, VISITED)
    for all e ∈ G.incidentEdges(v)
        if getLabel(e) = UNEXPLORED
            w ← opposite(v,e)
            if getLabel(w) = UNEXPLORED
                setLabel(e, DISCOVERY)
                DFS(G, w)
            else
                setLabel(e, BACK)
```

Das Ergebniss ist ein aufgespannter Baum. Die Kanten mit dem Label `Back` sind Zykeln ("im Baum zurückschauen") - also die "ausgeblendeten" Kanten.

!!! seealso

    Beispiel in den Folien 4-5

### Performance

* Setzen von Kanten/Vertex-Labels $$O(1)$$. (Mit Hash-Tabelle)
* Jeder Vertex wird 2x markiert (`unexpored`/`visited`)
* Jede Kante wird 2x markiert (`unexplored`, `discovery`/`back`)
* Methode `incidentEdges()` wird je Vertex 1x aufgerufen
* Mit _Adjazenzlisten-Struktur_ $$O(n+m)$$( _Adjazenzmatrix-Struktur_ wäre $$O(n^2)$$)

### Pfade finden
Mit einer adaptierung des "normalen" DFS Algorithmus kann ein Pfad (bsp. Labyrinth) gesucht werden.

Um diese Aufgabe auf Papier zu lösen am besten den Stack aufzeichnen werden.

```
Algorithm pathDFS(G, v, z)
    setLabel(v, VISITED)
    S.push(v)
    if v = z
        finish: result is S.elements()
    for all e ∈ G.incidentEdges(v)
        if getLabel(e) = UNEXPLORED
            w ← opposite(v,e)
            if getLabel(w) = UNEXPLORED
                setLabel(e, DISCOVERY)
                S.push(e)
                pathDFS(G, w, z)
                S.pop()
            else
                setLabel(e, BACK)
    S.pop()
```

### Zyklen finden
Mit einer adaptierung des "normalen" DFS Algorithmus können Zykeln gefunden werden.

Um diese Aufgabe auf Papier zu lösen am besten den Stack aufzeichnen werden.

```
Algorithm cycleDFS(G, v)
    setLabel(v, VISITED)
    S.push(v)
    for all e ∈ G.incidentEdges(v)
        if getLabel(e) = UNEXPLORED
            w ← opposite(v,e)
            S.push(e)
            if getLabel(w) = UNEXPLORED
                setLabel(e, DISCOVERY)
                cycleDFS(G, w)
                S.pop()
            else
                T ← new empty stack
                repeat
                    o ← S.pop()
                    T.push(o)
                until o = w
                finish: result is T.elements()
    S.pop()
```

## Breadth-First Search (BFS)
Depth-First Search ist eine **Technik für die Traversierung** eines Graphen:

* Besucht alle Vertizes und Kanten (wie DFS)
* Bestimmt, ob der Graph verbunden ist (wie DFS)
* Findet die verbundenen Komponenten eines Graphen (wie DFS)
* Berechnet einen aufgespannten Wald eines Graphen (wie DFS)
* **Iterativ** - arbeitet mit Listen.

Im Gegensatz zu DFS findet die BFS den kürzesten Pfad!

**Vorgehen:** Graph aufzeichen: Root zu oberst, dann alle Kindknoten usw.
![](images/bfs_skizze.png)



```
Algorithm BFS(G)
        Input graph G
        Output labeling of the edges
        and partition of the
        vertices of G
    for all u ∈ G.vertices()
        setLabel(u, UNEXPLORED)
    for all e ∈ G.edges()
        setLabel(e, UNEXPLORED)
    for all v ∈ G.vertices()
        if getLabel(v) = UNEXPLORED
            BFS(G, v)

Algorithm BFS(G, s)
    L{0} ← new empty sequence
    L{0}.insertLast(s)
    setLabel(s, VISITED)
    i←0

    while ¬ L{i}.isEmpty()
        L{i+1} ← new empty sequence
        for all v ∈ L{i}.elements()
            for all e ∈ G.incidentEdges(v)
                if getLabel(e) = UNEXPLORED
                    w ← opposite(v,e)
                    if getLabel(w) = UNEXPLORED
                        setLabel(e, DISCOVERY)
                        setLabel(w, VISITED)
                        L{i+1}.insertLast(w)
                    else
                        setLabel(e, CROSS)
        i ← i +1
```
Im Gegensatz zu DFS nicht *back* sonder *cross-edge*.


!!! seealso

    Beispiel in den Folien 4-6


## Digraphs

## Shortes Path

## Minimum Spanning Trees
