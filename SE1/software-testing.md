# Software Testing

!!! todo

    Kapitel 21. Test-Driven Development and Refactoring (19S)

Oberstes Ziel von Testing ist **Fehler zu finden** und sicher zu stellen, dass die Vorgaben erfüllt sind.
Testing kann aber keine Fehlerfreiheit garantieren!

Tests müssen **systematisch und wiederholbar**. Folglich müssen Tests geplant sein (wer, was, wann, wie?).

Testspezifikation
: Systematische Spezifikation von Tests. Bsp. der effektiver Code eines jUnit-Tests.

Testprotokoll
: Resultate festehalten. Bsp. die XML-Date mit den Resultaten bei jUnit.

Verifikation
: Überprüft Work Products *während der Entwicklung*, ob sie ihre Vorgaben erfüllen. Statische Techniken wie Code-Reviews, Coding-Guidelines usw. oder dynamische Techniken wie Testen, Bounds Check.

Validierung
: Überprüft, ob das *Endprodukt* die Anforderungen des Auftraggebers erfüllt


Validierung:
## Arten von Tests
Funktionale Anforderungen können mit funktionalen Tests verfiziert werden.

Nichtfunktionale Anforderungen wie Leistung und Usability sind schwerer zu testen - bsp. Usuability Tests.

Je nach Abstraktionsebene gibt es andere Tests:

* Anforderungen → Abnahmetest (Validierung)
* Architektur → Systemtest
* Entwurf → Integrationstest
* Detailentwurf/Implementation → Modultest (Unit Test)

Je nach Ebene sind auch andere Tester am Werk - so können bsp. Abnahmetest vom Kunden durchgeführt werden.

## Testmethoden für funktionale Tests

* Black-Box Tests mit *Äquivalenzklassen*, *Grenzwertanalyse* und *Zustand -basiertes Testen*
* White-Box-Tests mit *Kontrollfluss-orientiertes Testen* und *Testüberdeckung*

### Äquivalenzklassen

Äquivalenzklassen sind Wertebereiche von Eingabegrössen,
für welche der Prüfling voraussichtlich das gleiche Verhalten zeigt.

Beispiel Steuerberechnung: "für einkommensklasse von 80'000 bis 110'000 sei der Steuersatz 25%, darunter 20% und darüber 30%. Negative Einkommen gibt es nicht".

→ 4 Äquivalenzklassen: ungültig (<1, 0-80'000, 80'000-110'000 und >110'000). Aus den ensprechenden Äquivalenzklassen kann ein beliebiger Wert zum testen genommen werden.

Vorsicht: Oft Fehler am Rand von Äquivalenzklassen → Grenzwertanalyse.

Zustände sind eine Art von Äquivalenzklassen!

### Grenzwertanalyse
Bei der Grenzwertanalyse werden die Testwerte genau auf der Grenze, knapp darüber oder knapp darunter der
Äquivalenzklassen gewählt.

Im beispiel der Steuerrechnung wären diese:
0, 1, 79'999, 80'000, 80'001 109'999, 110'000, 111'001 und Long.MAX_VALUE

### Kontrollfluss-orientiertes Testen

Kenntnis der Kontrollstrukturen als Basis für Testfälle

### Testüberdeckung
* Anweisungsüberdeckung (statement coverage): Prozentualer Anteil der Anweisungen, die in Test ausgeführt werden.
* Zweigüberdeckung (branch coverage): Prozentualer Anteil der Kanten (Zweige wie If-Statements), die in Test durchlaufen werden.
* Pfadüberdeckung (path coverage): Ein Pfad ist ein möglicher Weg durch den Kontrollgraph. Nur mit kleinen Programmen oder solche ohne Schleifen praktikabel.

### Funktionsüberdeckung

Spezifikationsorientiertes Testen, denn Grundsätzlich gilt: Use Cases sind Test Cases!

<img src="images/uc-test-case.png" style="max-width: 80%" />

## Testautomatisierung

Wiederholbarkeit ist bei (guten) Automatisierten Tests garantiert - zudem ist die Spezifikation eindeutig.

Code für Tests muss geschrieben und gepflegt werden. Garantiert trotzdem nicht, dass alles getestet wird.

## Testprinzipien

* Test early → TDD
* Test often
* Test systematic
* Test automatic
* Test anything that might break
* Test anything that does break
* New code is guilty until proven innocent
* Write at least as much test code as production code
* Run all tests before check - in to repository

### A TRIP
* Automatic
* Thorough
* Repeatable
* Independent
* Professional (Auch die Tests überprüfen)


## Notizen: "Microtesting"

Code Smells → Identify hazards in code
Refactoring → Improve the design of existing code
**Microtesting → Test effectively at the object level**
Test-Driven Development → Design code by starting with tets
Faking & Mocking → Handle awkward collaborations
Legacy Code → Work with pre-existing code


Microtesting
: **writing (automated) unit tests** at the object level.
: A microtest is a short, simple, automated test that probes **one behavior** of **a single object**.

Kurz (<10-20 Zeilen!) und Präzise (macht genau etwas, hat ensprechender name und asserts und führt nur den minimal benötigten code aus.)

> In microtesting, we never reach (but look) inside the box (encapsulate)

> Tests should not depend on data from other tests.
→ avoid persistent state entirely - if not possible, clean it all up!
→ Keep the tests crips

Code *Safety Net* = "This is how I expect it to work"

Increase productivity and confidence

Mehrere Dimensionen

* Complexity (easy/hard)
* Collaboration (solo/group) (solo = classes work largely alone, and have no awkward collaborations that we have to work with)
* Timing (before/after)  (after means we're going to microtest classes that are already written.)

Training focuses on easy, solo, after!

### "Standard Micro Test"

1. Happy Path: "callWilma" → testcallWilma() "default condition"
2. Test Execution Paths: Check for conditionals → testCallWillmaPhoneBusy()

Using expressive names helps to focus on on small, isolated behaviour - and is almost a table of contents.

#### AAA-Structure

* **Arrange** the data and context. Objekte, die getestet werden sollen initialisieren und zusammenhängen. Hier werden auch Werte gesetzt, welche den Execution Path beeinflussen
* **Act** on the code. Hier wird einfach die Methode, welche getestet wird aufgerufen.
* **Assert** that the reuslts are as expected

Am Schluss sollte (falls nötig) noch der kontext aufgeräumt werden - bsp. Datenbankverbindungen oder Dateien.

```java
@Test
public void testSaleWithSingleItemAndMultipleQuantity() {
   // arrange
   Sale sale = new Sale();
   Money total = new Money(42);
   Money price = new Money(6);
   Item item = new Item("Toy");
   int quantity = 3;
   // Act
   sale.addItem(item, price, quantity)

   // Assert
   assertEquals(sale.getTotal(), total);
   assertEquals(sale.getItems().size(), 1);
   // Teardown
   // No teardown required...
}
```

### "Intersting" things to test
test all interesting paths through a class ≠ 100% Test Coverage
interesting = Worth investing time and energy

* Basic code that's used everywhere
* Things that can have potential damage(calculate bill amount)
* Not fully confident
* Complex operations
* Anything we might break while coding elsewhere
* ...

100% Coverage does not say anything about what is tested and weather it actually works

One-to-one mapping from methods to tests isn't a good idea as well - we don't care about methods but about *functionallity* and *behaviour*

Not only execution path matters - but also the "Data Context" (data) which are tested

### jUnit

* Don't forget the `@Test` annotation
* Test methods can throw Exceptions - but take no arguments.
* additional failure message that explains the mismatch between actual and expected values (First Argument!)

Test with floating-comma values:

```java
@Test
public void doubleEquality() {
   double expected  = 10.01;
   double actual    = 10.01;
   double precision = 0.000001;
   assertEquals(expected, actual, precision);
}
```

Test for same reference:
```java
@Test
public void objectsSame() {
    Integer anObject = new Integer(1);
    Integer sameObject = anObject;
    assertSame(anObject, sameObject);
    assertNotSame(anObject, sameObject);
    assertNull(null);
    assertNotNull(anObject);
}
```

Expected Exceptions
```java
@Test(expected=NumberFormatException.class)
public void parseIntThrowsException() {
   Integer.parseInt("trying to parse text instead of numbers");
}
```


"Shared Setup"
```java
// Before and after every test
@Before
public void before() {
    doStuff();
}
@After
public void after() {
    undoStuff();
}

// Before and after class
@BeforeClass
// ...
@AfterClass
// ...
```
#### Outcomes

Failture
: one of the assertions fails because different value

Error
: An Exception is thrown but not caught and handled properly

Pass
: No faliture and error
