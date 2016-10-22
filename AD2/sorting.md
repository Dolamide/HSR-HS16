# Sorting

![Sorting Übersicht](images/sorting_sumary.png)

## Merge-Sort

Divide
: Teile Input-Daten in zwei Teilmengen auf

Recur
: Wiederholen mit s1 bzw. s2: Verankerung, sobald inputgrösse 1 oder 0 ist.

conquery
: Lösungen von s1 und s2 vereinen

* Nutzt **Comparator**
* Laufzeit: ``O(n log n)``

!!! todo

    * code Beispiele (Pseudo Code #4)
    * Inplace insertion sort #14

Rekursion kann als Baum Dargestellt werden (Folien 5-15)

Auch Nicht-Rekursiv möglich (Im Array - in und out wird vertauscht)

* Halbiert immer -> immer garantierter balancierter baum

## Quick-Sort
* Auch Grundprinzip *Divide-and-Conquer*
* x ist pivot
* e -> equal sequenz
* l -> Less sqeuenz
* g -> greater sequenz
* pseudocode #3
* Img Ausführungsbeispiel

Merge sort: vergleicht sequenzen und pickt grösseres .. beim Quick-Sort dagegen passiert das bei der partitionierung.

![Quick sort Sequenzen](images/quick_sort_sequences.png)

Ist gut inplace sortierbar: Pseudocode #15

!!! todo

    Erwartete Laufzeit 13, 14

    * Worst case: entarteter aum! -> $$O(n^2)$$
    * pivot ist im Idealfall der *Median*

    Good call
    : die Länge von L und G sind beide kleiner als 3s/4

    Bad call
    : entweder L oder G ist länger als 3s/4


Gute Pivot wahl:

* Median wäre ideal - aber aufwändig zu berechnen
* Mögliche lösung: Median der letzten d elemente (wobei d >= 3) - statistische Stichprobe
* Ein element möglichst am Anfang/Ende als Pivot zu wählen ist keine gute idee

!!! todo

    Inline Quicksort: Warum nicht stabil?

## Sorting Lower Bound

tree #4 ...

$$n^n > n! > (n/2)^(n/2)$$ -> Jeder vergleichsbasierte Algorithmus hat eine min. Laufzeit von $$log(n!)$$, also folglich $$(n/2) log(n/2)$$
-> alternativ Stirling-Approximation #5

## Bubble sort

```java
public static <T extends Comparable<? super T>> void bubbleSort1(T[] sequence) {
    boolean swapped = true;
    while(swapped) {
      swapped = false;
      for(int i = 1; i < sequence.length; i++){
        if(sequence[i-1].compareTo(sequence[i]) > 0){
          T tmp = sequence[i-1];
          sequence[i-1] = sequence[i];
          sequence[i] = tmp;
          swapped = true;
        }
      }
    }
}
```
Laufzeit Best-Case: $$O(n)$$

Laufzeit Worst-Case $$O(n^2)$$

Lässt sich optimieren, in dem die länge bei jeder iteration um 1 verkleinert wird (das grösste Element ist garantiert an das letzten Position).

```java
public static <T extends Comparable<? super T>> void bubbleSort2(T[] sequence) {
    boolean swapped = true;
    int lenght = sequence.length;
    while(swapped) {
      swapped = false;
      for(int i = 1; i < lenght; i++){
        if(sequence[i-1].compareTo(sequence[i]) > 0){
          T tmp = sequence[i-1];
          sequence[i-1] = sequence[i];
          sequence[i] = tmp;
          swapped = true;
        }
      }
      lenght -= 1;
    }
}
```
Die optimierung hat aber kein Einfluss auf das Laufzeitverhalten (nur auf die Versteckten Faktoren...)

$$\sum_i^{n-1} i = \frac{n(n-1)}{2} \in O(n^2)$$

## Bucket-Sort

!!! todo

    * Pseudo code usw.

hat O(n+N)!

Bsp: PLZ -> N: 1000 - 9999 -> approx N: 9000

Bsp. mit 10'000 einträgen -> n+N -> 19'000 vs. O(n*log n) -> 10'000 * 14 = 140'000


Bucket sort ist NICHT vergleichsbasiert! Hat folglich eine bessere Performance - aber hat halt ensprechende einschränkunen.

## Radix-Sort
