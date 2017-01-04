# Iteratoren

## foreach-Loop
```cs
foreach (ElementType elem in collection) { statement }
```
→ "Collection" muss `IEnumerable<T>` bzw `IEnumerable` implementieren.

* collection hat Methode GetEnumerator() mit Rückgabewert e
* e hat eine Methode `MoveNext()` mit Rückgabewert bool
* e hat ein Property "Current"

```cs
int[] list = new int[] { 1, 2, 3, 4, 5, 6 };
foreach (int i in list)
{
    if (i == 3) continue;
    if (i == 5) break;
    Console.WriteLine(i);
}

// Compiler Output
IEnumerator enumerator = list.GetEnumerator();
try
{
    while (enumerator.MoveNext())
    {
        int i = (int)enumerator.Current;

        if (i == 3) continue;
        if (i == 5) break;
        Console.WriteLine(i); ;
    }
}
finally
{
    IDisposable disposable = enumerator as System.IDisposable;
    if (disposable != null) disposable.Dispose();
}   
```

## Iteratoren

!!! warning

    Vorsicht: **IEnumerator** vs. **IEnumerable**
    Bsp: `public IEnumerator<string> GetEnumerator(){...}`
    vs. `public IEnumerable<string> Reverse { get{...}}`

    IEnumerable<T> benötigt `using System.Collections.Generic;`

* `IEnumerable` analog zu Javas `Iterator`
* Mehrere aktive Iteratoren zur gleichen Zeit erlaubt
* Enumerator-Objekt muss Zustand vollständig kapseln
* Darf collection nicht verändern!

## Iterator-Methoden

* "yield return" Statement
* Analog python generators?
* yield break

```cs
class MyIntList
{
   public IEnumerator<int> GetEnumerator()
   {
       yield return 1;
       yield return 2;
       yield return 3;
   }
}
```

## Spezifische Iteratoren
```cs
class MyIntList
{
    //...
    // Spezifische Iterator-Methode
    public IEnumerable<int> Range(int from, int to)
    {
        for (int i = from; i < to; i++)
            yield return data[i];
    }
    // Spezifisches Iterator-Property
    public IEnumerable<int> Reverse
    {
        get
        {
            for (int i = data.Length - 1; i >= 0; i--)
                yield return data[i];
        }
    }
    // ...
}

// Spezifischer Iterator aufrufen
MyIntList list = new MyIntList();
foreach (int elem in list.Range(2, 7)) {}
foreach (int elem in list.Reverse) {}
```


## Erweiterungsmethoden
Bestehende Klasse erweitern *aus Anwendersicht*.
Signatur der Klasse wird nicht verändert Aufruf, es sieht jedoch so aus, als wäre es eine Methode auf der Klasse.

Anwendung bsp. für Method Chaining/Fluent APIs.

Muss zwingend:

* Statisch sein
* Erster parameter mit `this` Schlüsselwort.
* Die Angegebene Klasse (inklusive Subklassen) wird "erweitert"

Regeln:

* Kein Zugriff auf internas aus der Extension Methode
* Geht nur, wenn ensprechender Namespace importiert
* Hätte "object" eine Methode mit gleicher Signatur, würde immer diese aufgerufen
* Anwendbar auf Klassen / Structs, Interfaces, Delegates, Enumeratoren, Arrays

```cs
public static class ExtensionMethods
{
    // **static** und **this**
    static string ToStringSafe(this object obj)
    { return obj == null ? string.Empty : obj.ToString(); }

    public static void Test()
    {
        int myInt = 0;
        object myObj = new object();
        // Objects not null
        myInt.ToString();

        myInt.ToStringSafe();
        // Compiler-Output des obigen aufrufs wäre
        ExtensionMethods.ToStringSafe(1);

        // Object is null
        myObj = null;
        myObj.ToString(); // Error
        myObj.ToStringSafe(); // Works
    }
}
```
## Deferred Evaluation
→ GetEnumeration ist ja "lazy-evaluated"

Kann genutzt werden - für bsp. Query-Operationen - analog zu Java Streams.

```cs
static class HsrExtensions
{
    public static IEnumerable<T> HsrWhere<T>(
        this IEnumerable<T> source,
        Predicate<T> predicate)
        {
            foreach (T item in source)
            {
                if (predicate(item))
                    yield return item;
            }
        }
}

// ...
int[] list = { 4, 3.5, 3, 4.5, 6 };
IEnumerable<int> res = list.HsrWhere(delegate (int k) { return k % 2 == 0; });
// Bis hier wurde noch kein einziger `next` auf einem iterator IEnumerable aufgerufen.
foreach (int i in res) {
    Console.WriteLine(i);
}
```
## Beispiele
### Fibonacci
```cs
public static IEnumerable<int> Fibonacci(int n)
{
   int prev = -1;
   int next = 1;
   for(int i = 0; i < n; i++)
   {
       int sum = prev + next;
       prev = next;
       next = sum;
       yield return sum;
   }
}
```

```cs
public static IEnumerable<T> HsrWhere<T>(this IEnumerable<T> source, Predicate<T> predicate)
{
   foreach (T x in source)
   {
       if (predicate(x))
       {
           yield return x;
       }
   }
}

// Aufruf
IEnumerable<string> filtered = cities.HsrWhere(delegate (string s) { return s.Contains("e"); })
                                     .HsrWhere(delegate (string s) { return s.Length >= 5; });
foreach (string s in filtered) { Console.WriteLine(s); }

```
