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

### Prototype

Jedes Objekt hat einen Link auf eine Prototyp instanz. Dies ist also eine Art Linked-List. Wird eine Funktion oder ein Property nicht auf der Objektinstanz gefunden, so wird automatisch auf dem Prototype gesucht usw.
Bei der Ausführung von beim Prototyp gefundenen Methoden wird this auf das originale Objekt gesetzt. Dies ermöglicht, Funktionallität, welche identisch ist für verschiedene Instanzen auf eine Art Elternobjekt auszulagern.

## Mehrstufige Vererbung

```js
function Animal()  {/* ... */ }
Animal.prototype.foodRequired = function () {/* ... */ };
Animal.prototype.toString = function () {/* ... */ };
Animal.prototype.feed = function () {/* ... */ };

function Panda(name) { /* ... */ }
Panda.prototype = new Animal();
Panda.prototype.constructor = Panda;

function Lion(name) { /* ... */ }
Lion.prototype = new Animal();
Lion.prototype.constructor = Lion;
Lion.prototype.feed =function () { /* ... */ };

// Factory-Funktionen
function createLion(name) {
    return new Lion(name);
}

function createPanda(name) {
    return new Panda(name);
}
```

```js
function Animal() {
    this.isDead = false;
    this.name = "";
    this.compatibleFood = [ ];
}
function Panda(name) {
    this.name = name;
    this.compatibleFood = [{name:"bambus", amount: 1, timeToNextFood : 1}];
}
Panda.prototype = new Animal();
Panda.prototype.constructor = Panda;

Animal.prototype.foodRequired = function () {
    return !this.isDead && this.isFoodRequired(this);
};
```


## ES6 / Ecmascript 2015
> ... kennen die vorgestellten ES6 Spracherweiterungen und können diese in gegebenen Aufgaben anwenden, bzw. Fehler in der Anwendung identifizieren und korrigieren.

* ES6 breeits gut unterschtüzt auf Desktopbrowsern - nicht aber auf mobile!
* **Default Initialisierung** - dabei müssen diejenigen Parameter, welche default initialisiert werden sollen als *undefined* mitgegeben werden um sie nicht zu überschreiben.

    ```js
    function paddedText(text = '-', padding = '***') {
        return padding + ' ' + text + ' ' + padding;
    }
    paddedText(null); // *** null ***
    paddedText(undefined); // *** - ***
    ```

* Dank **destructuring** lassen sich named parameters wie in Python implementieren

    ```js
    function carFactory({ brand = 'Volkswagen', year = 1999 } = {}) {
        return { brand, year, };
    }
    carFactory({ year: 2012 }); // {brand='Volkswagen', year=2012}
    ```

* Destrukturierung kann auch generell bei allen Variablendeklarationen verwendet werden.

    ```js
    function carFactory3(optionsObj = {}) {
        const { brand = 'Volkswagen', year = 1999 } = optionsObj;
        return { brand, year, };
    }
    ```

* **Rest-Parameter** liefert ein vollwertiges Array (im gegensatz zu `arguments`)

    ```js
    function sumAll(...numbers) {
        return numbers.reduce((total, next) => total + next);
    }
    sumAll(1, 2, 3); // 6
    ```

* Mit dem **Spread-Operator** können die Elemente eines Arrays als Parameterliste mitgegeben werden.

    ```js
    function printNameAndSum(name, ...numbers){
        return name + ' '  + numbers.reduce((total, next) => total + next);
    }
    const args = ["Peter", 1,2,3];
    printNameAndSum(...args); // Peter 6
    // identisch zu
    sumAll("Peter", 1,2,3); // Peter 6
    ```

* `var` sollte nicht mehr verwendet werden
    * Hoisting - zugriff vor initialisierung OK
    * `cont` und `let` werfen Exception!
* Variablem möglichst mit `const` deklarieren. `const` verhält sich analog zu `final` in Java.
* Falls const nicht möglich `let` verwenden

    ```js
    function hoistedVAR(){
        console.log(x);
        var x = 1;
    }
    hoistedVAR(); // undefined
    function hoistedLET(){
        console.log(x);
        let x = 1;
    }
    hoistedLET(); // RefrenceError:
    // can't access lexical declaration `x' before initialization
    function hoistedCONST(){
        console.log(x);
        let x = 1;
    }
    hoistedCONST(); // RefrenceError:
    // can't access lexical declaration `x' before initialization
    ```

* **Kurzschreibweise von Properties und Werten**

    ```js
    const x = true;
    const y = 'str2';
    const z = -23.8;
    console.log( { x, y, z } ); // { x: true, y: 'str2', z: -23.8 }
    ```

* Variable als key bei Object Literals

    ```js
    function createEntryES6(name, keyValue, keyName = 'key') {
        return { name, [keyName]: keyValue };
    }
    const entryES6 = createEntryES6('markus', 54, 'age')
    // ES5 Version
    function createEntryES5(name, keyValue, keyName) {
        var keyN = keyName || 'key';
        var newEntry = { name: name };
        newEntry[keyN] = keyValue;
        return newEntry;
    }
    ```

* Template Strings

    ```js
    log('simple template string', `The result of 2+3 equals ${2 + 3}`);
    ```

* Object literal getters & setters

    ```js
    let myCount = initCount;
    let obj = {
        get count() {
            return myCount;
        },
        set count(newCount) {
            myCount = newCount;
        }
    };
    // ES5:
    Object.defineProperty(obj, 'count', {
        get() { return count; },
        set(newCount) { count = newCount; }
    });
    ```

!!! seealso

    [Parameter Handling - Exploringjs.com](http://exploringjs.com/es6/ch_parameter-handling.html)

### OO mit ES6
> ... können objekt-orientierte Programmkonzepte auf den ES6 JavaScript Syntax übertragen sowie “manuell“ für einfache Beispiele zwischen ES6 Syntax und ES5 Syntax in beide Richtungen übersetzen, bzw. Fehler in einer Übersetzung finden (2 Klassen mit Vererbung mit öffentlichen Properties, Gettern und Settern und Methoden)

* Definiert JS-Konstriktor mit speziellen Eigenschaften
    * Aufruf ohne new führt zu einem Type-Error
    * Die Deklaration wird nicht angehoben (wie bei `let` oder `const`)
* Properties werden enumerable auf der Instanz gespeichert
* Methoden werden nicht-enumerable auf dem gemeinsamen Prototyp-Objekt für alle Instanzen zugreiffbar abgelegt.
* Kein colsure auf umgebener scope möglich.
* ➪ ES6-Klassen sind etwas mehr als ES5 Konstruktoren mit "Syntactic Sugar"
* Vereinfacht Unterklassen
    * Zugriff auf parent mit `super` bzw. `super.methodenname`

```js
class Counter {
    constructor({ start: start = 0, step: step = 1 } = {}){
        this._count = start;
        this._step = step;
    }
    get count() {
        return this._count;
    }
    inc(step = this._step) {
        this._count += step;
    }
    dec(step = this._step) {
        this._count -= step;
    }
}
class DoubleCounter extends Counter {
    constructor({ start: start = 0, step: step = 1 } = {}) {
        super({ start, step });
        this._step = this._step * 2;
    }
}
```

## Functional JS
> ... können ein einfaches funktionales JS Programm mit Chaining von bis zu 4 Array- und String- Funktionen analysieren und das Resultat vorhersagen.

* `Array.from(Iterable)` generiert einen Array z.B. aus einem String
* `Array.filter(callback(element, index, array)[, thisArg])` Filtert anhand von `callback`
* `Array.map(callback(element, index, array)[, thisArg])` Wendet `callback` auf jedes Element des Arrays an
* `Array.join(separator)`  Konkateniert alle Elemente eine Arrays in einen String
* `Array.reduce(callback(prevResult, element, index, array), startValue)` -> Kombiniert Schritt-für-Schritt paarweise das jeweils aktuelle Element mit dem bisherigen Resultat

```js
const str1 = 'hallo hallo';
const str2 = Array.from(str1)
     // ['h', 'a', 'l', 'l', 'o', ' ', 'h', 'a', 'l', 'l', 'o']
    .filter(c => 'abcdefgh'.indexOf(c) < 0)
    // ['l', 'l', 'o', ' ', 'l', 'l', 'o']
    .map(c => c + c)
    // ['ll', 'll', 'oo', '  ', 'll', 'll', 'oo']
    .join('');
    // 'lllloo  lllloo'

// Same, using reduce
const str3 = Array.from(str1)
    // ['h', 'a', 'l', 'l', 'o', ' ', 'h', 'a', 'l', 'l', 'o']
    .filter(c => 'abcdefgh'.indexOf(c) < 0)
    // ['l', 'l', 'o', ' ', 'l', 'l', 'o']
    .map(c => c + c)
    // ['ll', 'll', 'oo', '  ', 'll', 'll', 'oo']
    .reduce((resString, c) => resString + c, '');
    // 'lllloo  lllloo'

function duplicateEncode(word){
    return word.toLowerCase()
            .split('')  // String in ein Array
            // Wenn einmal in string: 1, sonst n
            .map(function (element, index, array) { 
                return array.indexOf(element) == 
			array.lastIndexOf(element) ? '1' : 'n'
            })
            .join(''); // In String konkatinieren
}
duplicateEncode("Foo"); // 1nn
```

## JS Coding Styleguides
> ... haben an ihrem eigenen Code ESLint mit dem AirBnb Ruleset ausprobiert und können generell den Nutzen von JS-Styleguides erklären, sowie die wichtigsten Regeln des AirBnb Styleguides erklären.

Nutzen von JS-Styleguides

* Best pracitce
* Gemeinsamer Stil

Wichtigsten Regeln des AirBnb Styleguides

* Use const for all of your references; avoid using var
* Use the literal syntax for object creation - no constructors
* Use ES6 features (property value shorthand, computed property names usw.)
