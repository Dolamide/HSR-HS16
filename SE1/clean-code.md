# Clean code

> "Smart data structures and dumb code works a lot better
than the other way around." - Eric Raymond, The Cathedral and the Bazaar, Chapter 5

Design ist weder Wissenschaft noch Rezept - nicht die Methode sondern der Designer macht es aus.

Folgende Best-Practices sollen angestrebt werden - die Kunst besteht in der Umsetzung in der Praxis.

* Aufräumen Baustelle
    * leere Methode
    * TODOs
    * Auskommentierte stellen
    * Konsistentes Layout (einrücken)
* Coding Guidelines
    * Konvention, weil man nicht alleine unterwegs ist.
    * Team muss sich auf Richtlinien einigen.
* DRY
    * Doppelte Information - unnötig (Aufgeblähter Code)
    * Nicht wartbar
        * habe ich alles ersetzt
        * macht das überall sinn
        * subtile fehler
        * Welche Version ist die Neutste/Beste
        * ...
* Handhabbare Grössen
    * Abstrahieren
    * Beispiele
        * Bsp. Diagramm max. A3
        * 80 - 120 Zeichen je Zeile
        * Max 5 Verschachtlungstiefe
        * max 30 Zeilen je Methode
        * max 300 Zeile je Klasse
        * Keine Packages
        * Max 7 Schichten
        * Max 4 Tiers
        * ...
* No Errors, No Warnings
    * Jeder build muss ohne Compiler-Fehler und ohne Compiler-Warnings durchlaufen
    * Sobald einige Warnungen ignoriert werden verpasst man relevante neue Warnungen
    * Gleiches gilt für Checkstyle, Metrics, Findbugs
* Keep it Simple
* Positive Bedinnungen
    * Analog zu Whitelisting vs. Blacklisting
* Schneller Ausstieg (guard clauses)
    * wann immer möglich
    * geht nur wenn die Mengen komplimentär sind
* Kopplung und Kohäsion (!!!)
    * Kopplung = Aufrufe von einer Klasse bzw. Package zur anderen
    * Kohäsion = "warum sind wir zusammen, was ist der gemeinsame Zweck?"
    * Strebe loose/tiefe Kopplung an
    * Kohäsion soll gegeben sein, sonst gehören die Dinge nicht in eine Klasse/Package.
* Single Responsibility Principle
    * aka Separation of Concerns
    * Nur EINE Verantwortung: Bei Methoden (immer!) und Klassen
    * Sonst:
        * viele Kollisionen (Git/SVN)
        * Nicht testbar
        * Nebeneffekte
* Programmieren gegen interface
    * Dependency Inversion Principle
    * → Bsp. List
    * Nicht ultimativ!
* Isolate What Changes
    * Frage: "was brauche ich denn an Funktionen?"
    * Bsp. Datenspeicherung
* Programmieren für Menschen - nicht computer
    * Test mit Code Reviews
    * Visueller Lärm!
* Gute Namen
    * Kurze Namen nur bei kleinem Scope
    * Nicht abkürzen, wenn man nur 3 Buchstaben spart
    * Aussprechbar
    * nicht p1, p2 sondern previousPointer, nextPointer
* Keine anonyme Konstanten
    * Ausnahme: `0` und `1`
* Nützliche Kommentare
    * Nur wenn der Verständlichkeit dient
    * JavaDoc nur bei tieferliegenden Methoden - macht nicht sinn für setter und getter
    * Bessere Namen statt Kommentare
