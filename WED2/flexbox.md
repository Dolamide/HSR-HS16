# Flexbox

## Motivation
* Unterschiedlichste devices - vom Laptop über Smartphone bis Uhr - keine standardisierten grössen.
* User Experience sollte trotzdem auf Device optimiert werden
* Keine separaten Seiten pfelgen
* SEO ranking
* Keine horizontalen Scrollbars.


Flexibles Layout
: Dynamisches (grössenadaptives) Layout welches sich ohne Media-Queries umsetzen lassen
: Alterative Begriffe: Flexible Design, Adaptive Layout/Design, Fluides Layout/Design

Responsives Layout
: Dynamisches Layout welches für unterschiedliche Geräte, Bereiche von Display-Grössen und unterschiedliche Medien separates Layouts definiert.
: Jedes dieser separaten Layout kann ein flexibles Layout sein. D.h. Responsive Layouts beinhalten meist auch flexible Layouts. Umsetzung mit Media Queries (nächste Woche)

### CSS-Properties

overflow: visible; (default)
: Text darf aus der Box fliessen

overflow: scroll
: Scrollbar falls nötig anzeigen

overflow: hidden
: Überschüssiger Inhalt nicht sichtbar.


## Das Flexbox Modell

FlexBox ermöglicht vielseitige positionierung. Zudem kann es sich anpassen (wachsen, schrumpfen) wenn zu viel oder zu wenig Platz vorhanden ist.

`flex` bzw. `flex-inline` kann als Wert für das CSS-Attribut `display` gesetzt werden.
`flex` verhält sich dann wie ein Block-Element - mit dem Wert `flex-inline` ensprechend wie ein Inline-Block-Element.

Alle Kinder des Elements (flex-items) sind automatisch betroffen. Diese verhalten sich dann ähnlich wie Inline-Elemente.

Die Elemente ordnen sich entweder entlang der Main-Achse oder der Cross-Achse an (wobei die Main-Achse nicht zwingend horizontal sein muss.)

![](https://cdn.css-tricks.com/wp-content/uploads/2011/08/flexbox.png)
: flex-flow directions - aus [A Complete Guide to Flexbox](https://css-tricks.com/snippets/css/a-guide-to-flexbox/)

Main axis
: Die Primärachse, an welche die flex Elemente angeordnet werden. *Nicht unbedingt horizontal!* - hängt von der flow-direction ab.

main-start, main-end
: elemente werden im Container am Anfang bzw. ende der Main-Achse platziert.

main-size
: Entweder die Höhe oder die Breite des Containers.

cross-axis
: die Achse, die senkrecht zur Main-Achse liegt.

## Attribute auf dem Container
* `display: flex;` oder `display: inline-flex;`
* `flex-direction: row | row-reverse | column | column-revere` legt die Ausrichtung fest
* `flex-wrap: nowrap | wrap | wrap-reverse;` Wrap ermöglicht, dass Elemente umgebrochen werden (default: alles auf eine Zeile.).
* `flex-flow: [flex-direction] [flex-wrap]` (shorthand)
* `justify-content: flex-start | flex-end | center | space-between | space-around`: Definiert, wie die Elemente entlang der Main-Achse verteilt werden.
* `align-items: flex-start | flex-end | center | space-between | space-around` Analog zu `justify-content` für die Cross-Achse

## Attribute auf den Elementen
* `order: <integer>`: Ändert die Sortierung der Elemnte (default: Wie im Code)
* `flex-grow: <integer>` Gewichtung, wie und ob gewachsen werden soll.
* `flex-grow: <integer>` Gewichtung, wie und ob geschrumpft werden soll.
* `flex-basis: ` Grösse des Elements - kann in beliebiger Einheit (%, rem, usw) angegeben werden (auto ist erlaubt)
* `flex: [flex-grow] [flex-shrink] [ flex-basis]` (shorthand)
* `align-self: ` damit kann der  `align-items`-Wert vom Parent überschrieben werden

!!! seealso

    * [Simple Flexbox Demo](http://codepen.io/raphiz/pen/gwddjE)

## Legacy

Da noch lange nicht alle Browser flex unterstützen, gibt es verschiedene Ansätze, wie auch damit umgegangen werden kann.


Progressive Enhancement
Mobile First
: Start mit Grundfunktionalität (Annahme: kein JS, keine Media Queries)
: Zusatzfunktionalität mit zusätzlichem CSS und unobtrusive JavaScript

Graceful Degradation
: Alle modernen Features werden genutzt. Für alte Brower werden Polyfills (auch Shim / Fallback) eingesetzt oder es muss dem Nutzer eine sinnvolle Alternative geboten.
