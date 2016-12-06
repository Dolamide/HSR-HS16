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


Im Gegensatz zum BFS können mit dem DFS Biconnected Komponenten gefunden werden ("Single Point of failture")

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

Für jeden Vertex v in L gilt:

* der Pfad in _aufgespannten Baum_ von s nach v besitzt i Kanten.
* jeder Pfad von s nach v _im Graph_ besitzt mindestens i Kanten.

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

### Performance
Identisch zu DFS!

* Setzen von Kanten/Vertex-Labels $$O(1)$$. (Mit Hash-Tabelle)
* Jeder Vertex wird 2x markiert (`unexpored`/`visited`)
* Jede Kante wird 2x markiert (`unexplored`, `discovery`/`cross`)
* * Jeder Vertex wird einmal in eine Sequenz eingetragen.
* Methode `incidentEdges()` wird je Vertex 1x aufgerufen
* Mit _Adjazenzlisten-Struktur_ $$O(n+m)$$

### Anwendung

* bestimmen der verbundenen Komponenten in einem Graph
* bestimmen eines aufspannenden Waldes in einem Graph
* bestimmen eines einfachen Zyklus in einem Graph
* bestimmen, ob ein Graph ein Wald ist.
* Mit zwei Vertizes eines Graph G: finden eines Pfades in G zwischen den beiden Vertizes mit **minimaler Anzahl Kanten** oder bestimmen, **ob** ein solcher **Pfad existiert**.

## Digraphs

Digraphs = Directed Graphs = Gerichteter Graph.
In AD2 arbeiten wir nur mit Graphen, wo **alle** Kanten gerichtet sind.

Eine mögliche Anwendungen ist u.a. Task Scheduling: Ein Task muss nach einem Anderen ausgführt werden - vgl. Systemd startup. Ein Anderes Beispiel ist eine Vererbungsstruktur in OO-Sprachen (Zykeln erkennen).

### Eigenschaften
* In einem ungerichteten, einfachen Graphen gilt: $$m \le n(n-1)$$ - kann also im Gegensatz zum ungerichteten Graphen Doppelt so viele Kanten haben (`/2` fällt weg).
* Tiefensuche kennt nebst `discovery`, `back` und `cross` auch `forward` - eine Verbindung zu einem Nachfolger im Baum.
* Der aufgebaute DFS-Baum ist je nach Anfangsknoten **unterschiedlich**!

![](images/digraph-labels.png)
: Neu *cross!* (D → C) und **back** (C → A) und **forward** (A → D) - Quelle: AD2-Vorlesung (HSR)

Bei einem Digraph ergibt sich ein wesentlich anderer Tree (Bsp. mit DFS) im vergleich zum ungerichteten Graph.

Erreichbarkeit
: Vertizes im DFS Baum vom Wurzelknoten v sind durch gerichtete Pfade erreichbar.

### Implementierung
Adjazenzliste neu mit 2 Listen: Einmal für Incomming und einmal für Outgoing.

### Strong Connectivity

Strong Connectivity
: In einem Graphen sind von jedem Vertex aus alle anderen Vertizes erreichbar - es ist also bei bsp. DFS egal, welcher Anfangsknoten genommen wird.

Strong connected component
: Ein Subgraph, der Streng verbunden ist.

* 1x Teifensuche ab irgend einem Knoten
* Wenn es keine nicht besuchten Vertizes gibt: Neuer Graph "erstellen" mit gleichen Vertizes aber umgekehrten Kanten
* Wenn es keine nicht besuchten Vertizes gibt: Graph ist Strong connected.

Laufzeit $$O(n+m)$$

NB: "Wenn es keine nicht besuchten Vertizes gibt" kann in der for schleife der `DFS(G)` Methode evaluiert werden.

### Transitiver Abschluss
Transitiver Abschluss von G ist ein Graph G*, der _zusätzlich direkte Verbindungen_ zu allen Knoten hat, die transitiv erreichbar sind.

**Ist nichts anderes als eine Performance Verbesserung** bei der Nutzung.

Berechnung mit Floyd-Warshall: Idee Wenn vi und vk und vk und vj verbunden sind, so verbinde vi und vj (Dynamische Programmierung)

Laufzeit:  $$O(n^3)$$ (FALLS: `areAdjacent` mit $$O(1)$$ läuft!). Dies ist nicht weniger Effizient als DFS im gerichteten Graph - das Ergebnis ist aber eine sehr effiziente Struktur $$(O(n(n+m))$$ mit m durch n ausgedrückt →  $$O(n(n+(n^2))) = O(n^3)$$

```
Algorithm FloydWarshall(G)
    Input digraph
    G Output transitive closure G* of G
    i←1
    for all v ∈ G.vertices()
        denote v as vi
        i←i+1
    G{0} ← G
    for k ← 1 to n do
        G{k} ← G{k−1}
        for i ← 1 to n (i ≠ k) do
            if G{k} − 1.areAdjacent(v{i}, v{k})
                for j ← 1 to n (j ≠ i, k) do

                  if G{k} − 1.areAdjacent(v{k}, v{j}) ∧
                     ¬G{k}.areAdjacent(v{i}, v{j})

                     G{k}.insertDirectedEdge(v{i}, v{j} , k)
    return Gn
```

Vorgehen: Papierpfeile i, k, k ➪ Kann sofort abbrechen, wenn 1. Bedinung nicht erfüllt. Check: Keine Gegenpfeile in Gegenrichtung.


### DAGs & topologische Ordnung

DAG
Directed Acyclic Graph
: Gerichteter Graph ohne Zykeln =  Gute Situation (Bsp. OO Vererbung: Wenn Zyklus → CompileError)

Topologische Ordnung
: Vertizes Nummeriern, so dass die Zahl der Startvertizes kleiner als die Endvertizes sind. Oft sind mehrere Lösungen möglich.

Bsp. Buildtools wie Make, Maven usw. müssen topoligische Ordnung haben.

```
Algorithm topologicalDFS(G)
    Input dag G
    Output topological ordering of G
    n ← G.numVertices()
    for all u ∈ G.vertices()
        setLabel(u, UNEXPLORED)
    for all e ∈ G.edges()
        setLabel(e, UNEXPLORED)
    for all v ∈ G.vertices()
        if getLabel(v) = UNEXPLORED
            topologicalDFS(G, v)

Algorithm topologicalDFS(G, v)
    Input graph G and a start vertex v of G
    Output labeling of the vertices of G
        in the connected component of v
    setLabel(v, VISITED)
    for all e ∈ G.outgoingEdges(v)
        if getLabel(e) = UNEXPLORED
            w ← opposite(v,e)
            if getLabel(w) = UNEXPLORED
                setLabel(e, DISCOVERY)
                topologicalDFS(G, w)
            else
                {e is a forward or cross edge}

    Label v with topological number n    <- HIER
    n←n-1
```
Laufzeit $$O(n+m)$$

!!! seealso

    Beispiel Folie 26ff


## Shortes Path

## Minimum Spanning Trees
