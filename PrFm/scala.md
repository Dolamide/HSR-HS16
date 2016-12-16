# Scala

* Verschiedene Backends - typ. Java
* Wenn auf JVM mit Java interoperabel.
* "Scalable" mit Problem und Entwickler
* OO + Funktional
* Statisch typisiert
* Sparsame Syntax (Typ-Inferenz)
* Keine Semikolons
* Mehrheitlich Expressions (F20)
* Letzte Expression = automatisch Rückgabewert.
* Tail-Recursion optimiert Compiler weg :tada:
* Composable - Sprachelemente flexibel kombinieren wie bsp. Funktionen in Funktionen definieren.


Recap: Expression gibt Wert zurück
Statement - Seiteneffekt

## OO vs. funktional

OO:

* Alles ist ein Objekt (Klassen, Funktionen)
* Objekte kommunizieren miteinander
* Objekte sind Instanzen von Klassen (Klassen repräsentieren Gruppierungen)
* Klasse definiert das Verhalten des Objekts & Vererbung
* Objekt beinhalten Daten und Verhalten
* Expression Problem: Neue Klassen einfach, neue Methoden schwierig
* Viele Statements

Funktional

* execute & evaluate expressions
* avoid mutable state
* first-class functions
* Daten und Funktion getrennt
* Expression Problem: Neue Datentypen schwierig, neue Funktionen einfach.
* (fast) nur Expressions

(evtl. F13)

Wann was F17 - ist aber kein entweder-oder F18

## Strict vs. lazy evaluation


## Crashkurs
> Sie können Programme in Scala schreiben die ADTs konstruieren und mit Pattern-Matching ...

Grundsätzlich viel gleich wie in Java...

### Datentypen

* Keine primitiven Datentypen (`1.toFloat`)
* Erweitertes API (Bsp. `"42".toInt`)
* Mehrzeilige Strings mit `"""` und String-Interpolation `s"my ${foo(10)}"`
* Kein `void` - sondern Typ Unit (`()` = "Leeres Tupel")

### Typhierarchie

![](images/scala_class_hierarchy.png)

Null & Nothing (Wenn bsp. Methode immer Exception wirft) - relevant für Typ Inferenz.
### Listen, Tupel und andere Datenstrukturen

* Liste ist konkrete Implementation
* immutable -> Ermöglicht gute Performance

```scala
val list1 = "Willkommen" :: "zu" :: "Scala" :: Nil
val list2 = List("Willkommen", "zu", "Scala")
list1.head            evaluiert zu            "Willkommen"
list1.tail             evaluiert zu            "zu" :: "Scala" :: Nil
list1(2)             evaluiert zu            "Scala"

val tupel2 = (1, "String")
val triple = ("key", "value", "?")
val pair = "key" -> "value"
```

Viel mehr (Map, Set, Range, Vector, Trees, Queues, ...)

### Variablen
* `val` vs. `var` (`val` = `final`)
* Typangabe ist optional
* `lazy` Keyword  (`lazy val foo = complexComputation()`)

### Kontrollstrukturen
* `val max = if (a >= b) a else b `
* for-Comprehensions
* Keine Checked-Exceptions

### Methoden


### Pattern Matching
* Etwas wie "Switch-Case" aber mit beliebigen Typen und eigenen Extraktoren
* Kein Fall-through
* Reihenfolge relevant!


```scala                  
// Basic Example
def patternMatching(i: Int) = {
  i match {
    case 0 => "Null"
    case 1 => "Eins"
    case _ => "?" // Default case
  }
}

// With Types & Conditions
def patternMatching(any: Any) = {
    any match {
     case i: Int               => "Int: " + i
     case f: Float if f > 10.0 => "Float: " + f
     case "s"                  => "String: s"
     case (s: String, _)       => "String: " + s
     case head :: tail         => "Non-empty list"
     case any                  => any.toString
    }
}

// with Classes
case class Person(name: String, alter: Int)

def matchAPerson(person: Person) = {
  person match {
    case Person("Mirko", 32)           => "Found Mirko!"
    case Person(name, age) if age < 18 => s"Minor: $name"
    case Person(name, _)               => s"Adult: $name"
  }
}

// Regex
val Chf = new Regex("""([0-9]+)\.([0-9][05])""") // Mit """ kein doppeltes escaping
"1.50" match {
  case Chf(franken, rappen) => // Regex Gruppen extrahieren
    println(s"$franken Franken und $rappen Rappen")
  case _ =>
    println("Ungültiger Betrag")
}
```

### Methoden
* Named Parameter
* Default-Werte
* Methoden mit mehreren Parameterlisten - ermöglicht Partial Application (Currying)

    ```scala
    def add(m: Int)(n: Int) = m + n
    
    val addToTen = add(10) _
    addToTen(5)
    ```

* Alles Pass-By-Value
* Kann by-name übergeben werden - Lazy (wenn bsp. sehr teuer). Wird jedes Mal neu ausgewertet. Könnte auch mit Funktionen abgebildet werden.

    ```scala
    def unless(condition: Boolean, then: => Any) = {
        if (!condition) {
            then
        }
    }
    
    unless(1 + 2 == 3, throw new RuntimeException("VM Kaputt!"))
    ```
### Funktionen

* Funktionen sind Values, also Objekt-Instanzen (Aus Sicht der VML)
* Methoden werden zu Funktionen umgewandelt falls nötig

```scala
val add = (m: Int, n: Int) => m + n

val people = List(new Person( ... ))
val istVolljährig = (p: Person) => p.age >= 18

people.filter(istVolljährig)
people.filter((p: Person) => p.age >= 18)
people.filter(p => p.age >= 18)
```

### Operatoren


* Kein spezielles Konzept von Operatoren - Eigentlich Methodenaufrufe 
    * `10 / 2` ist eigentlich `10./(2)`
    * `p.age >= 18` ist eigentlich `p.age.>=(18)`
* `.` und Klammern können auch so weggelassen werden (`0 to 200 by 5` = `0.to(1000).by(5)`) **NUR** wenn expliziter Empfänger und ein Argument.
* Bsl. `->` ist auch Methodenname.

### Klassen


### Objekte

