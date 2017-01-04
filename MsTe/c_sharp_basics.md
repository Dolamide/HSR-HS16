# C# Basics

## Naming Guidelines

![Naming conventions in c#](images/naming_conventions.png)

## Identifiers

* Unicode und Unicode Escape Sequenzen (`\u03c0`)
* Keywords mit `@` prefix - `@if` ist ein identifier

## Kommentare

Es gibt Single Line `//` und Multi-Line `/* ... */` Kommentare.

Zudem existieren [Spezielle Dokumentationsstrings](http://www.codeproject.com/Articles/3009/C-Documenting-and-Commenting) (XML) `///` (mit XML)


## Primitive Datentypen

![](images/primitives.png)

Für Literale werden folgende Typen verwendet:

* Ohne Suffix wir der kleinste type aus int, uint, long, ulong
* u Suffix -> kleinster aus uint, ulong
* suffix l -> kleinster aus l und ul

!!! warning

    * String ist kein Primitivtyp
    * String ist kein Struct

### Typ-Kompatibilität

![](images/type-compatibility.png)

## Struct vs. Object

Ein Struct ist keine Referenz, es lebt direkt auf dem Stack.

**STRUCT KANN FOLGLICH NICHT NULL SEIN**

## Sichtbarkeitsattribute


<img src="images/visibility.png" style="max-width: 80%;" />

Defaults:

<img src="images/default-visibility.png" style="max-width: 80%;" />

## Operator Rangfolge

<img src="images/operator-rang.png" style="max-width: 80%;" />

<img src="images/operator-rang2.png" style="max-width: 80%;" />
