# Values

Variablen definieren:

```c++
// <type> <name> {<value>};
int anAnswer{42};
int const zero{}
```

* lokale variablen nicht ohne initialisierung verwenden
* default werte mit geschweiften klammern!
* ohne {} → undefined behaviour
  Folglich: Nutze geschweifte klammern!!

## const

Java *final*: Variable ist unveränderlich - nicht neu zuweisbar
(aber Werte können verändert werden)

C++ *const*: Zustand bleibt genau so bestehen - also *imutable*

Const sollte wann immer möglich verwendet werden, da

* Verhindert bad practices
* Sicherer code

### const on member

```c++
struct Hello {
    void sayHello(std::ostream &out) const;
};
```

Zweck hier: Bezieht sich auf ``this`` - damit wird garantiert, dass
der Inhalt von ``this`` nicht verändert wird (beispielsweise die
``getSize()`` auf eim Listen Objekt)

* Für const ist initialisierung pflicht!
* Style: const immer Rechts vom Typ

```c++
int const theAnswer{6*7};
```

### constexpr

Mit dem keyword constexpr wird der Wert zur Compile-Zeit berechnet!

```c++
double constexpr pi{3.14};
```

## Konventionen

Zu Namen von Variablen...

* start mit lowercase letter
* keine abkürzungen
* gute Benennung
* kurze namen wie i nur für kleiner kontext wie bsp. iterationen verwenden.

Weiteres

* Variablen erst dort deklarieren wo benötigt (ermöglicht auch die verwendung von const)
* Namen nicht überdecken (in unterblock variable mit gleichem Namen verwenden)
* keine namen von globals (std etc) verwenden


## Typen

* bool und char werden als integral numbers (ganzzahlen) verwendet
* string/vector können erst nach dem ensprechenden #include genutzt werden
* Merke: Keine fixen Grössen für die Typen (bsp. int) garantiert!

Typische Typen:

* bool
* char, unsigned char, wchar_t, char16_t, char32_t: ``'a', '\n', '\x0a'``
* short, int, long, long long
* unsigned short, unsigned, unsigned long, unsigned long long
* float, double, long double (there are no "unsigned" floating points)

!!! todo

    Tabelle mit typen erstellen
    → unsigned short, unsigned, unsigned long, unsigned long long
      können alle OPTIONAL von int gefolgt werden;
      bsp. unsigned a{4}; ist identisch zu unsigned int a{4};
    Merke: Deren grösse muss nicht gleich sein → implementation defined

    → signed char, short, int, long, long long: optional (unnötig) signed vorergehend

    Tabelle:
    typ     Literal     Typical Bit Width    Typical Range
    int     42 (dec)
            052 (oct)
                hex
    unsigned    123u    ...

    → https://www.tutorialspoint.com/cplusplus/cpp_data_types.htm

Literals:

```c++
1 // int
42L // long
5LL // long long
int{} // int
0x14 // 31 int
1u // unsigned int
42ul // unsigned long int
0.4f // float
.33 // double
```

Die Suffixe können gross oder klein geschrieben werden - je nach dem sollten andere
verwendet werden:

* .31 vs .3l
* 0XFULL vs 0xFull
* "String literal" sind **nicht vom Typ std::string**, sondern Character Arrays (legacy)
* Mit dem s-Suffix ("Real string"s) wird ein String literal der Klasse ein std::string{} erstellt.
* *Raw-String-Literal*: R"(\root.hsr\skripte\)" (Runde klammern zwingend!)
  alternativ mit dientifier R"kqqkqq(\root.hsr\skripte\)kqqkqq"

## Expressions

Arithmetisch:

* binär: ``+`` ``-`` ``*`` ``/`` ``%``
* unär: ``+`` ``-`` ``++`` ``--``

Logisch

* tertiär: ``?:``
* binär: ``&& ``and`` ``||`` ``or``
* unär: ``!`` ``not``

!!! remember

    Shortcut Evaluation (ausdrücke werden nur solange ausgewertet, bis das Ergebniss fest steht)

Bit-Operatoren

* binär: ``&`` ``|`` ``^`` ``<<`` ``>>``
* unär: ``~`` ``compl``

→ shortcut evaluation - sobald also klar ist wird abgebrochen

```c++
auto x = (5 + 10 * 3 – 7 / 2) // = (5 + 30 - 3 = 32)
auto y = x % 2 ? 1 : 0; // 1
```

Automatische Typkonvertierung
------------------------------

= Integer Promotion

C++ konvertiret die Typen automatisch in einer Expression.
Aber Vorsicht: Bei der Zuweisung erfolgt die Konvertierung erst
im Nachhinein:

```c++
double x = 45/8; // =5.0, da konvertierung erst nachher
```

!!! warning

    Divison durch null ist **undefined behavior**
    Modulo null ist auch division durch null!

    String sind value containers!

## Strings

String Literals sind (wegen legacy) char arrays.

```c++
auto s = "hello"; // array
```

Mit ``s``-Suffix (benötigt namespace!) oder Zuweisung in Klasse ``std::string`` umwandeln.

```c++
// Explizite Zuweisung
std::string = "foo";
// s-Suffix
using namespace std::literals;
auto s = "hello"s;
```

Kein unicode support

## Vectors

Vector ist etwas analog zur ArrayList in Java, mit dem
entscheidenden unterschied, dass eine Kopie des Objekts
im Vektor abgelegt wird (während in Java die Referenz abgelegt
wird)

## Referenzen vs. Values

Werte werden typischerweise kopiert (eg. String titanic bsp)

Für Streams etc. wo kopieren keine option ist, kann die Referenz
mittels &name übergeben werden:

```c++
// declaration ...
void askForName(std::ostream &out);
// out wird nicht Kopiert (geht nicht), sondern
// es wird die Referenz übergeben (analog zu Java)
```
