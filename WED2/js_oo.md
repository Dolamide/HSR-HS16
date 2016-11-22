# Javascript OO

Lexical Scope
: Lexical Scoping definiert wie variablen namen in verschachtelten funktionen aufgelöst werden: Innere Fuktionen beinhalten auch die Variablen des Parent-Scopes - auch wenn die Parent-Funktion bereits terminiert ist.

Closure
: Innerer (nested) Scope kann auf Elemente des äusseren Scopes zugreiffen.


!!! todo

    [You Don't Know JS: Scope & Closures lesen](https://github.com/getify/You-Dont-Know-JS/blob/master/scope%20&%20closures/README.md#you-dont-know-js-scope--closures)


## Repetition: `this`

> [..] `this` is neither a reference to the function itself, nor is it a reference to the function's lexical scope. `this` is actually **a binding that is made when a function is invoked**, and what it references is **determined entirely by the call-site** where the function is called. [..]
>
> <cite> You Don't Know JS: Scope & Closures - By Kyle Simpson</cite>

> [..] four rules can be applied to the call-site, in this order of precedence:
>
> 1. Called with `new`? Use the newly constructed object.
> 2. Called with `call` or `apply` (or `bind`)? Use the specified object.
> 3. Called with a context object owning the call? Use that context object.
> 4. Default: undefined in strict mode, global object otherwise.
>
> <cite> You Don't Know JS: Scope & Closures - By Kyle Simpson</cite>

## Repetition Datentypen

Primitive Datentypen sind:

* Immutable
* Copy by value
* Call by value
* Compared by value

Referenztypen sind:

* Copy by reference
* Call by reference
* Compared by reference

Es gibt Wrapper-Objekte für primitive Typen

* new Boolean()
* new Number()
* new String()
* ...


## Vorteile OO in JS

* Erlaubt erhöhte Kohäsion
* Erlaubt erhöhte Konsistenz bei der Nutzung von Properties und Methoden
* Bessere Ordnung


## Objekte definieren

## Konstruktoren

* Konstruktoren werden nach Konvention gross geschrieben
* Konstruktoren dürfen (sollten) nur zusammen mit `new` genutzt werden

→ Recap: `this` ist hier ein neues, leeres Objekt

```js
// JS Konstruktor
const Counter = function (initDelta, initCount){
    let delta = initDelta || 1;
    this.count = initCount || 0;
    this.countUp = function (){ this.count=this.count+delta };
    this.countDown = function () { this.count=this.count-delta };
};

let x = new Counter(1, 0);

// Alternative: Factory-Funktion
function newDeltaCounter(cInit, dInit) {
    return { count: cInit || 0, delta: dInit || 1 };
}

let y = newDeltaCounter(cInit, dInit);
```

## Mehrstufige Vererbung

!!! todo

    * Nachlesen
    * Object.Create(prototype) Umgeht die Initialisierung durch den Konstuktor?!


### Prototype?!

!!! todo

    * Nachlesen
    * Jeder Funktion (auch Nicht-Konstruktoren) wird bei bei der Erstellung ein leeres ‘Prototyp‘- Objekt zugeordnet
    * Jedes mittels Konstruktor erstelltes Objekt hat einen Pointer auf ein ‘Prototyp‘-Objekt
    * Wird eine Methode (oder Property) mittels .Operator oder [ ] vom Objekt angefordert, und nicht gefunden, dann wird die Suche beim Prototyp‘-Objekt weitergeführt.
    * Bei der Ausführung von beim Prototyp gefundenen Methoden wird ‘this‘ auf das originale Objekt gesetzt.
