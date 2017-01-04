# Prüfungsdetails


## Erlaubte Hilfsmittel

* Open Book: Alles erlabut
* Ausnahme: Alte Prüfungen / Probeprüfungen

# MERKE

* Structs können nicht null sein! Bsp. Array von Structs
* NullpointerException in C# heisst **NullReferenceExcepiton**
* VERERBUNG
* Ergänzen zu Reflection (Folien durchgehen!)

    ```csharp
    var ass=Assembly.LoadFrom("Tiere.dll");
    var t = ass.GetType("Tiere.Katze");
    var k = Activator.CreateInstance(t, new object[] {"Mitzi"});
    var m = t.GetMethod("MausFangen");
    m.Invoke(k, new object[]{});
    ```

Todo:
* LINQ üben
* Prüfungslösnugen nochmals durchgehen
* Folien Drucken

# Aufgabentypen

* Bei Zeit und Bedarf: Übung 2 - Aufgabe 2 (Rekursion)

### Überschreiben

Car - welche methode wird ausgeführt. Siehe Folien **Repetiton Vererbung**.

=> Repetitionsfolien!!

### Boxing / Referenzen

Was ist die Ausgabe des folgenden Programms?

```csharp
public static void Print(ArrayList list) {
    foreach (object o in list) {
        Console.Write("{0}", o);
    }
}

public static void Test() {
    ArrayList myList = new ArrayList();
    object o1 = 1;
    object o2 = 2;
    myList.Add(o1);
    myList.Add(o2);
    Print(myList);

    o1 = 4;
    Print(myList);
}
```
Lösung:

```
1 2
1 2
```

Grund: Bei den Zuweisungen von o1 und o2 wird geboxt. Wird o1 auf 4 gesetzt, dann bleibt die referenz in myList unverändert auf 1.

## Nullable Generics
→ Übungen Woche 6 - Aufgabe 1.3


## Aufgaben zu WCF
An der Prüfung müssen diese Annotationen gesetzt werden (Siehe beispielcode im Kapitel WCF.)

## Weiteres

* Mehr zu Generics in den Zusatzaufgaben der Woche 6.

## Ausgelassen

Vorlesung W3:

* Arithmetische Operatoren
* Vergleichsoperatoren
* Logische Operatoren
* Bit Operatoren
* Boolsche Ausdrücke
* Overflow-Checks
* typeof / sizeof
