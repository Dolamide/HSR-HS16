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
function concatFunction(s1: string, s2: string): string { return s1+s2; } numberApplicator([1, 2, 3, 4], concatFunction);
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

        constructor(public x: number, public y: number, description: string, public likes?:number) {
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
