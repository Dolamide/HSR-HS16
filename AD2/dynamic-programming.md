# Dynamic Programming

* Ist ein Design-Paradigma (auf "gleicher Ebene" wie Divide & Conquer etc)

## Rucksack Problem (Knapsack-Problem)

* Ansatz mit Brute force: ➪ $$O(2^n)$$ (ist *nicht* Fakultät, da die Position keine Rolle spielt)
* Ansatz Greedy: Nimm wiederholend den Gegenstand mi grössten Verhältnis von Wert/Gewicht ➪ Kann misslingen → bsp. Wechselgeld

Mit Dynamischer Programmierung

* Zerlegung in Subprobleme ("Was ist der grösstmögliche Wert für die ersten beiden Gegenstände 1/1 und 4/3 bei einer Gewichtslimite von 3 kg ?")
* Die Tabelle lässt sich in O(gegenstände * gewichte) aufbauen!

!!! todo

    * Tabelle
    * [Verstehen mit Videos](https://www.youtube.com/results?search_query=dynamic+programming+knapsack&page=&utm_source=opensearch)


    6
    Iterieren über die Items(wert/kg)
        Iterieren über kg
            Falls [Wenn gewicht kg kleiner ist als das Gewicht des Items(wert/kg)], Kopiere Parent Wert "Vererbung" - Zugriff auf letztes Subproblem
            **else: Nächste Woche**


## Text Similarity Testing
