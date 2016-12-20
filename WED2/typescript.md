# TypeScript
## Motivation & Grundlagen
> Vorteile der Nutzung von TS in Beispielkontext erklären

TypeScript ist ein Precompiler (analog zu SASS bei CSS), welche ermöglicht, ein Superset der JavaScript-Syntax zu definieren.

TypeScript führt statisches typing in die Synatx ein, welches unter umständen (Typen-)Fehler frühzeitig erkennen kann, die bei rein dynamischen typing nur mit Erfahrung oder zur Runtime erkannt werden. Zudem ermöglicht die statische typisierung von TypeScript "Intellisense" in einer IDE.

## Typen und Syntax-Module
> typescript code lesen und Vorhersagen zur Identifikation von Typenfehlern machen
> TypeScript Klassendefinitionen lesen und in ES6 bzw ES5 konvertieren.
> Unterschied von Klassen, Interfaces und "Structural Typings"

### Variablendeklarationen: Basistypen

* Keine Typendeklaration notwendig - aber möglich. Falls keiner angegeben nutzt TypeScript Type-Inferenz um den Typ der Variable zu bestimmen.

    ```typescript
    let myInferedNumVar1 = 1;
    let myNumberVar: number = 1;
    let myStringVar: string = 'cdef';
    ```

* Mit `any` deklarierte Variablen dürfen beliebige Werte annehmen

    ```typescript
    let myAnyVar1: any = 1;
    myAnyVar1 = 'hi';

    // NOT allowed!
    let myInferedNumVar1 = 1;
    myInferedNumVar1 = 'hi';
    ```

* Mit `delcare let` kann dem angegeben werden, dass es eine weitere Variable gibt (Bsp. `window`) - ohne diese Definieren zu müssen.
* Basis-Typen sind `boolean`, `number`, `string`, `null` und `undefined`

### Variablendeklarationen: komplexen Typen

* Definition Arrays und Tupels

    ```typescript
    let inferredNumArray = [1, 2, 3];
    let notInferredTupel = [1, 'abcd'];
    let numArray:number[] = [1, 2, 3];
    let tupel: [number, string] = [1, 'abcd']
    ```

* Enums können wie Basistypen genutzt werden

    ```typescript
    enum Color {Red, Green, Blue};
    let c: Color = Color.Green;
    let myTupel2: [Color, number] = [Color.Green, 1];
    ```

### Funktionsdeklarationen

Mit TypeScript _können_ folgende Dinge auf bei der Funktionsdeklaration festgelegt werden

* Typen von Parametern
* Rückgabetyp
* Optionale Parameter
* Mehr als eine Signatur je Funktion

```typescript
function sumFunction(n1: number, n2: number): number {
    return n1+n2;
}

function combineFunction2(sn: number|string ='' , ns?: number|string): string {
    return sn.toString() + (ns || '').toString();
}

// allowed
let myNum: number = sumFunction(1, 2);

// not allowedlet
myStr: string = sumFunction(1, 2);
sumFunction(1, 'hi');
```

### Funktionsdeklarationen: Funktionen als Parameter

```typescript
function numberApplicator (numArray: number[],
        numFun: (prevRes: number, current: number) => number): number {
            return numArray.reduce(numFun);
}

// OK (Siehe vorheriges Kapitel für definition von sumFunction )
let myNum2: number = numberApplicator(
    [1, 2, 3, 4], sumFunction);

// VERBOTEN
myStr: string = sumFunction(1, 2);
sumFunction(1, 'hi');
function concatFunction(s1: string, s2: string): string { return s1+s2; }
numberApplicator([1, 2, 3, 4], concatFunction);
```

### Komplexe Typen: Klassen

Erweiter ES6-Syntax um:

* static
* private
* readonly

```typescript
class Counter {
    private _doors: number;
    public static readonly WOOD_FACTORS = {'oak': 80, 'pine': 20};

    constructor({doors = 2}: {doors?: number} = {}) {
        this.doors = doors;
    }

    set doors(newDoorCount: number) {
        throw `Counter can only have ... `;
    }
    get doors() {
        return this._doors;
    }
}
```

### Klassen und Interfaces

* Wird die Visibility in der Konstruktor-Argumentenliste angegeben, so kann man sich die `this.foo = foo` statements sparen (Analog zu Initialisierungsliste);

```typescript
class DescribableItem {
    constructor(public description: string){ }
}
// Kompiliert zu
var DescribableItem = (function () {
    function DescribableItem(description) {
        this.description = description;
    }
    return DescribableItem;
}());
```

* Vererbung und implementierung von Interfaces ist ziemlich "straight forward"

```typescript
interface Point {
    readonly x: number;
    readonly y: number;
}

interface LikableItem {
    likes?: number;
}

class DescribableItem {
    constructor(public description: string){ }
}
class PointOfInterest extends DescribableItem
    implements Point, LikableItem {

        constructor(public x: number, public y: number,
                    description: string, public likes?:number) {
            super(description);
        }
}
```

### Module in Typescript

* Orientiert sich an ES6-Modul Syntax.
* Wird je nach Einstellungen in der `config.ts` nach require.js oder CommonJS umgewandelt.
* Nutzung von nicht-typisierten Modulen möglich - damit geht aber die Typensicherheit verlohren -> Nutzen von Type-Definition files.

```typescript
// File Counter.ts
export default class Counter

// counterDetails.ts
import Counter from './Counter';
```

Auf prototyp des konstruktors kommen alle properties, auf die quasi mit `this` zugegriffen werden soll. Static Properties werde auf dem Konstruktor gesetzt....

```typescript
class Counter {
  private _doors: number;
  private _wood: string;
  private _basePrice: number;
  public static readonly WOOD_FACTORS = {'oak': 80, 'pine': 20,
                                        'beech': 50, 'maple': 60,
                                        'walnut': 90, 'cherry': 100};
  public static readonly DOOR_FACTOR = 2;
  public static readonly MIN_DOOR_COUNT = 2;
  public static readonly MAX_DOOR_COUNT = 7;

  constructor({doors = 2, wood = 'oak', basePrice = 40}:
              {doors?: number, wood?: string,
              basePrice?: number} = {}) {
    this.doors = doors;
    this.wood = wood;
    this._basePrice = basePrice;
  }

  set wood(newWood: string) {
    if (Counter.WOOD_FACTORS[newWood]) {
      this._wood = newWood;
    } else {
      throw "Counters not avaiable with wood=" + newWood;
    }
  }

  get wood() {
    return this._wood;
  }
  set doors(newDoorCount: number) {
    if (newDoorCount >= Counter.MIN_DOOR_COUNT
        && newDoorCount <= Counter.MAX_DOOR_COUNT) {
      this._doors = newDoorCount;
    } else {
      throw `Counter can only have between ${Counter.MIN_DOOR_COUNT}
               and ${Counter.MAX_DOOR_COUNT} not
               supported ${newDoorCount}`;
    }
  }
  get doors() {
    return this._doors;
  }
  get price() {
    let priceFactor = Counter.WOOD_FACTORS[this.wood] * Counter.DOOR_FACTOR
                        * this.doors / 100;
    return priceFactor * this._basePrice;
  }
}
```

Kompiliert zu


```javascript
var Counter = (function () {
    function Counter(_a) {
        var _b = _a === void 0 ? {} : _a, _c = _b.doors,
		 doors = _c === void 0 ?
 		 2 : _c, _d = _b.wood, wood = _d === void 0 ?
 		'oak' : _d, _e = _b.basePrice,
 		basePrice = _e === void 0 ? 40 : _e;
        this.doors = doors;
        this.wood = wood;
        this._basePrice = basePrice;
    }
    Object.defineProperty(Counter.prototype, "wood", {
        get: function () {
            return this._wood;
        },
        set: function (newWood) {
            if (Counter.WOOD_FACTORS[newWood]) {
                this._wood = newWood;
            }
            else {
                throw "Counters not avaiable with wood=" + newWood;
            }
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(Counter.prototype, "doors", {
        get: function () {
            return this._doors;
        },
        set: function (newDoorCount) {
            if (newDoorCount >= Counter.MIN_DOOR_COUNT
		&& newDoorCount <= Counter.MAX_DOOR_COUNT) {
                this._doors = newDoorCount;
            }
            else {
                throw "Counter can only have between " +
			Counter.MIN_DOOR_COUNT + " and " +
			Counter.MAX_DOOR_COUNT + 
			" not supported "+ newDoorCount;
            }
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(Counter.prototype, "price", {
        get: function () {
            var priceFactor = Counter.WOOD_FACTORS[this.wood]
			    * Counter.DOOR_FACTOR * this.doors / 100;
            return priceFactor * this._basePrice;
        },
        enumerable: true,
        configurable: true
    });
    return Counter;
}());
Counter.WOOD_FACTORS = { 'oak': 80, 'pine': 20, 'beech': 50,
			 'maple': 60, 'walnut': 90, 'cherry': 100 };
Counter.DOOR_FACTOR = 2;
Counter.MIN_DOOR_COUNT = 2;
Counter.MAX_DOOR_COUNT = 7;
```