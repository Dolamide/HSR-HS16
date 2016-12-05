# JS Module

Lernziele: 

* Vorteile von Modulen (erläutern an Beispiel in gegebenem Kontext)
* Unterschied von Modulen und ähnlichen Begriffen erklären (in Kontext analysieren und entscheiden, ob es sich um ein Modul handelt)
* NodeJS Module:
    * CommonJS Module in NodeJS definieren
    * CommonJS Module in NodeJS nutzen
    * Funktionsweise des CommonJS Modul-Systems.
    * Fehler in CommonJS identifizieren & Korrigieren.
* Code-Module für die Nutzung im Browser auf 3 verschiedene Arten erstellen und einbinden:
    * Revealing Module Pattern
    * Nutzung von RequireJS 
    * ES6 Import/Export Syntax (Warum Babel und WebPack nötig?!)
    
## Definition Modul

Ein JS-Modul ...

* ist eine Gruppierung von Programm-Code
* wird in einer Datei verwaltet
* hat einen eigenen Scope (Namenskonflikte vermeiden)
* Hat eine öffentliche Schnittstelle, um Nutzern Funktionen/Objekte zur Verfügung zu stellen.
* Kann separat von Programm geladen werden (bei Bedarf)

im JS-Umfeld gilt:

* 1 Datei = 1 Modul = 1 Unit
* 1 Ordner = 1 Package = Sammlung von zusammengehörenden Module

### Abgrenzungen

File, Folder, Tier: Physikalische Aufteilung/Zusammenfassung

Modul, Package, Klasse, Objekt, Layer, Unit, Komponente: Logische Aufteilung / Zusammenfassung (typischerweise für Information hiding)

Model, View, Controller, Service: Beschreibung der Funktion einer Gruppe von Code.

## Vorteile
* Kapselung von wiederverwendbarer Funktionalität (hohe Kohäsion, tiefe Koppelung)
* Ermöglicht vereinfachte parallele Entwicklung
* Ermöglicht Lazy Loading von Code bei Bedarf

## Module auf dem Server mit CommonJS

CommonJS definiert ein Modulformat. Dabei entspricht ein **Module** einer Datei auf dem Server.

Einbinden über bekannte Syntax:

```js
const myModuleName = require('./myModule.js');
```

Definition eines Server-Moduls:

```js
module.exports = { fn1, fn2, fn3 };
```

Module haben ihren eigenen Scope, daher ist *global namespace pollution* kein Problem. Zu exportierende Elemente werden einfach über das `module`-Objekt zugewiesen.


## Module im Browser
Leider eignet sich CommonJS nicht direkt zur Verwendung im Browser, weil:

* Kein eigener Scope je Modul im Browser definiert ist
* Synchron Konzipiert - während dies Browser nicht praktikabel ist. 

### Revealing Module Pattern
Laden von Dateien ohne *global namespace pollution*.

* Reguläres laden über `script`-Tag (Bsp. `scr="scripts/Counter.js"`)
* Nach **Konvention** legt das Modul ein globales Objekt mit dem eigenen Modulnamen an (Bsp. `window.Counter`) 

```js
(function () {
   class Counter { ... }
   window.Counter = Counter;
})();
```

Problem: Namenskonflikte im Globalen Namespace! Abhilfe mit **Package-Objekten**:

* Reguläres laden über das `script`-Tag (Bsp. `src="scripts/game/Counter.js"`)
* Nach **Konvention** fügt sich das Modul auf dem Package-Objekt auf dem globalen Namespace hinzu (also bsp. `window.game.Counter` statt `window.Counter`)

```js
(function () {
     class Counter { ... }
     window.game = window.game || {}; window.game.Counter = Counter;
}) ();
```

### Require-JS

RequireJS ladet Code im Browser asynchron nach und implementiert die **AMD** (Asynchronous Module Defnition) Spezifikation.

* Definieren genau eines `script`-Tags, welches `require.js` lädt. 
* Auf dem `script`-Tag wird zusätzlich mit dem Attribut `data-main` der Pfad zum Eintrittspunkt in die Applikation angegeben: `<script data-main="scripts/main" src="scripts/require.js" />`
* Im Main-File können asynchron Module nachgeladen werden:

```js
require(['./game/Counter'],
    function (Counter) {
        const counter = new Counter();
        ...
```

* Auch hier Ziel: Laden von Dateien ohne *global namespace pollution*
* Definition mit `define`, wobei der erste Parameter eine Liste der benötigten Module ist.

```js
define([], function () {
    class Counter { ... }
    return Counter;
});
```

* NB: Problem: DOM schon aufgebaut? Lösung: Auslagern in eine Funktion und bei komplet geladenem DOM sofort ausführen (ohne onload-Hanlder zu registrieren)

```js
function initPage () { ... };

if (document.readyState === 'complete') {
    initPage();
}else{
    window.addEventListener('load', initPage);
}
```

### ES6 Imports/Exports
* ES6 definiert eine Syntax für die Definition von Modul-Exports/Imports.
* Einbinden mit `import`-Statement `import name from "module-name";` (Beispiel: `import Counter from ./Counter`)
* Export über `export`-Statement `export default OBJECT_OR_FUNCTION;` (Beispiel: `export default Counter;`)
* Problem: Kein guter Browser-Support!
Pre-Compiler ermöglichen Nutzung (Bsp. mit WebPack + Babel (Build-Tool))
* Nicht absehbar, wann in Browser/NodeJS effektiv verwendbar :disappointed:
