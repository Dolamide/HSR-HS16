# Design Patterns

!!! todo

    https://moodle.hsr.ch/pluginfile.php/47132/mod_resource/content/2/uebung-design-patterns-loesung.pdf

→ Recap Head-First "Wichtige Lessons learned"

Zweck: Kummunikation & Best Practices

## Strategy

Umsetzung:

* Verhalten austauschbar auslagern.
* Abstraktion mit Interfaces/Abstrakter Klasse
* Spezifische Implementation in Subklassen

Zweck:
* Loose Koppelung
* Details der Schnittstelle in der Basisklasse kapseln
* Implementationsdetails in abgeleitete Klassen

![](https://sourcemaking.com/files/v2/content/patterns/Strategy_.svg)
: Strategy Pattern - by [sourcemaking.com](https://sourcemaking.com/design_patterns/strategy)





## Decorator Pattern
→ Alle varianten gibt extren viele Klassen


http://www.vincehuston.org/images/gof9.jpg
>- recursive composition
>- 1-to-1 "has a" up the "is a" hierarchy
>- a single core object wrapped by possibly many optional objects
>- user configuration of optional features to an existing class

Bsp. java.io

!!! todo

    Simple Code sample

## Composite
Bsp. Swing
http://www.vincehuston.org/images/gof8.jpg

> - recursive composition
> - 1-to-many "has a" up the "is a" hierarchy
> - examples:
>   - file system hierarchy
>   - GUI (menus, layout managers)

## Factory Method
Komplexe Erzeugungslogik.

> Abstract Factory
> - a level of indirection that provides creation services
>- supports a "family" of products
>- supprts many creation strategies: choice of derived class, reusing cached objects,
>  distributed creation, choice of platform or address space
>- the "new" statement considered harmful
> http://www.vincehuston.org/images/gof1.jpg

## Command

http://www.vincehuston.org/images/gof14.jpg
>- object-oriented callback
>- a magic cookie that encapsulates a "method invocation"
>- "execute"

## State



→ Folien?
## Template Method
➪ Inversion of control

- configure steps of an algorithm
- placeholders specified in base class, implemented in derived classes

## MVC
Wenn mit Observer: Controller kennt die View nicht ➪ Mehrere Views. Ermöglicht Änderungen, welche der Observer nicht mitbekommt zu aktuallisieren.

Wenn ohne Observer: Der Observer muss die View kennen und sowohl die View als auch das Model updaten. ➪ GENAU EIN Observer. Geht nur, wenn niemand anders als der Controller (und nur ein User) die Daten ändern kann.


## Observer
http://www.vincehuston.org/images/gof19.jpg
- wrapper/delegate structure
  - wrapper encapsulates the core business logic
  - each delegate provides user-configurable, optional functionality
- example:
  - a data presentation application with graph, bar chart, pie chart, and table views
  -
## Null Object

## (X) Use Case/Session/Application Controller
## (X) Singleton
> - enforces a fixed number of instances of a class
> - lazy initialization
> - global access
## (X) Adapter
http://www.vincehuston.org/images/gof6.jpg
>- wrap an existing class with a new interface
>- impedance match an old component with a new system
>- wrapper/delegate structure


→ Proxy ist ein Adapter, der caching kann.

## (X) Facade
http://www.vincehuston.org/images/gof10.jpg
