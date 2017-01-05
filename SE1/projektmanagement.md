# Projektmanagement

* Tätigkeiten F3
* Tugenden von Projektleiter: F4
    * mehrere Listen führen (Backlog, Todos usw.)
    * Kommunikation: Team, Kunden, Unterlieferanten
    * "Keeper of the scope" Funktionsumfang nicht aus dem Ruder laufen lassen
    * Unsichtbares Sichtbar machen: Konzepte, Fortschritt
    * Adapt/Inspect: Puls fühlen, Daten sammel, reagieren

## Zwölf Regeln für Software

1. Nichts vergessen dank Listen
    * Arbeitspakete in Issue Tracker
    * Hindernisse als todo-Liste (Hindernisse, die weg müssen)
    * Weitere Aufgaben (Stunden aufschreiben, Fragen, Termine finden)
    * 3 Prioritäten: unbedingt/dringend unbedingt/nicht-dringend, nice-to-have
2. Keeper of the Scope: Projektumfang im Zaum halten,
    * Scope != Details und != Kosten
    * Scope = Hauptfunktionen = Use Cases
    * Neuer Wunsch: Erweitert dies den Scope oder nicht?
    * Neuer Wunsch: Hat Auswirkungen auf Architektur?
    * Wachsende Spezifikation, Anzahl UCs und Function Points sind ein Indikator für wachsenden Scope.
    * 2% "Scope Creep" = schleichende Erweiterungen des gewünschten Funktionsumfangs.
    * Keine Projekte > 9 Monate - dann in kleinere Projekte aufteilen (mehr dazu in SE2)
* Software ist Kommunikations-intensiv
    * Muttersprache - wann möglich
    * An einem Ort wann möglich
3. Jeden Tag auf die Baustelle gehen
    * Code: Primär in VCS
         * Problematischer Code
    * Issue Tracker
    * Tests
    * Entwürfe
    * Dokumentation
4. Entfernung ist teuer!
    * Ideal im gleichen Stockwerk - im gleichen Haus, gleiche Ortschaft usw. +10%.
    * +20% wenn Kommunikationssprache != Muttersprache.
5. Übergaben sind sehr teuer
6. Sichtbar machen
    * Diagramme (UML) mit Farben!
    * Metaphern, Analogien
    * Fortschritt: Burn-down chart, Bug count, Build breaks usw., Time to fix a bug.
7. Immer iterativ vorgehen.
    * Siehe UP/Scrum
    * Feedback vom Kunden anhören!
8. Inspect - Adapt
    * Wie beim Reisen (Verspätungen, Wechselkurs usw.), immer neu ausrichten und reagieren
    * Management by walking around.
    * Kein Abtauchen
    * "Hot Spots" identifizieren (Story macht niemand, Code wird dauern angefasst) => Ansprechen und Handeln
    * Geschichtsschreibung: Meilensteine (erreicht, verpasst), Anzahl Mitarbeiter, Kosten, Probleme, besondere Vorfälle, Screenshots, VCS/Ticket Export, Meteting-Protokolle.
        * Cover my Ass
        * Aus Erfahrungen lernen
    * Projekt Review: Lessons learnd, soll-ist Vergleich (Zeit, Geld, Qualität), Zufriedenheit (Kunde, Mutarbeiter), Fehlerquellen.
9. Daily Build und Branches
    * Anzahl Branches: Übersichtlich behalten.
    * Short running branches.
10. Verstehen, was der Kunde will.
    * Prototypen
    * Grafische Entwüfe
    * Abgrenzung
    * Endkunde - nicht Proxy!
    * VERSTEHEN ("Hundefutter wird nicht vom Hund gekauft!")
11. So früh wie möglich so formal wie möglich.
    * Domain Model
    * Halb-formale Texte für UCs, Risiken
    * Grad der Schriftlichkeit hängt von Teamgrösse ab - dann muss nicht viel aufgeschrieben werden
    * Eingefrorene Spezifikationen gibt es praktisch nicht
12. 4 Projekt-Variablen messen und verstehen
    * Kosten / Aufwand
    * Zeit
    * Funktionalität (schwer)
    * Qualität (sehr schwer)
    * Wenn überbestimmt (in dieser Reihenfolge)
        * Funktionallität reduzieren
        * Zeitlplan verlängern
        * Mehr Leute - funktioniert nur selten (Brooks-Law)
        * Kompromisse bei Qualität loht sich nie.
