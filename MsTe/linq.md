# Lambda Expressions

In c# sind lambdas anonyme Methoden.
Werden im Hintergrund in delegates konvertiert.

Typ ist optional
Klammern auch - wenn nur ein parameter

Geschweifte Klammern & Return können bei nur einem Statement weggelassen werden.

* Lambda Expression kann auf äussere Variablen Zugreifen
* Variablen in Lamda Expressions sind für äussere Methoden nicht sichtbar
* Zugriff auf "out" und ref Parameter nicht erlaubt
* whoopwhoop



```csharp
// Letzter Parameter ist return type!
Func<bool> p01;
Func<int, bool> p02;
Func<int, int, bool> p03;
Func<int, int, int, bool> p04;

p01 = () => true;          // 0 Parameters
p02 = a => true;           // 1 Parameter
p02 = (a) => true;         // 1 Parameter
p03 = (a, b) => true;      // 2 Parameters
p04 = (a, b, c) => true;   // 3 Parameters
                         // ...

p01 = () => true;                    // 0 Parameters
//p02 = int a => true;                 // Compilerfehler
p02 = (int a) => true;               // 1 Parameter
p03 = (int a, int b) => true;        // 2 Parameters
p04 = (int a, int b, int c) => true; // 3 Parameters
                                   // ...

// Staements (ohne {})
Func<int, int> e1;
e1 = a => a * a;
e1 = a => Square(a);

Func<int, int, int> e2;
e2 = (a, b) => a * b;
e2 = (a, b) => Multiply(a, b);

Action<int> e3;
e3 = a => Console.WriteLine(a);
e3 = a => a++;
}

// n-Statements mit {}
Func<int, int> e1;
e1 = a => { return a * a; };
e1 = a => { return Square(a); };
e1 = a =>
{
    int sum = 0;
    for (int i = 1; i <= a; i++)
        sum += i;
    return sum;
};
```


## behind the scenes
(via http://stackoverflow.com/questions/25603965/why-do-some-c-sharp-lambda-expressions-compile-to-static-methods)
```csharp
int age = 25;
Action<string> withClosure = s => Console.WriteLine("My name is {0} and I am {1} years old", s, age);
Action<string> withoutClosure = s => Console.WriteLine("My name is {0}", s);
Console.WriteLine(withClosure.Method.IsStatic);
Console.WriteLine(withoutClosure.Method.IsStatic);
```

```csharp
private class <Main>b__0
{
    public int age;
    public void withClosure(string s)
    {
        Console.WriteLine("My name is {0} and I am {1} years old", s, age)
    }
}

private static class <Main>b__1
{
    public static void withoutClosure(string s)
    {
        Console.WriteLine("My name is {0}", s)
    }
}

public static void Main()
{
    var b__0 = new <Main>b__0();
    b__0.age = 25;
    Action<string> withClosure = b__0.withClosure;
    Action<string> withoutClosure = <Main>b__1.withoutClosure;
    Console.WriteLine(withClosure.Method.IsStatic);
    Console.WriteLine(withoutClosure.Method.IsStatic);
}
```

# Object Initializers  / Collection Initializers

Auch reine Compiler-Technologie

```csharp
Student s1 = new Student("John") {
    Id = 2009001,
    Subject = "Computing"
};
// wird zu
Student s1 = new Student("John");
s1.Id = 2009001;
s1.Subject = "Computing";
```

praktisch in kombination

```csharp
int[] ids = { 2009001, 2009002, 2009003 };
IEnumerable<Student> students = ids
    .Select(n => new Student { Id = n });
```

gitbs auch für collections

```csharp
List<int> l1 = new List<int>{ 1, 2, 3, 4 };

Dictionary<int, string> d1 = new Dictionary<int, string>
{
   { 1, "a" },
   { 2, "b" },
   { 3, "c" }
};

d1 = new Dictionary<int, string>
{
   [1] = "a",
   [2] = "b",
   [3] = "c"
};

```
# Anonymous Types
Im Hintergrund wird eine neue `internal seald class` erstellt, welche die gleichen Properties wie.

```csharp
var a = new { Id = 1, Name = "John" };
var b = new { a.Id, a.Name };
var studentList = new List<Student>();
var q = studentList
        .GroupBy(s => s.Subject)
        .Select(
            grp => new {
                    Subject = grp.Key,
                    Count = grp.Count()
            });

// Compiler magic
internal sealed class < > f__AnonymousType0<< Id > j__TPar, < Name > j__TPar > {
 private readonly < Id > j__TPar < Id > i__Field;private readonly < Name > j__TPar < Name > i__Field;public < Id > j__TPar Id {
  get {
   return this. < Id > i__Field;
  }
 }
 public < Name > j__TPar Name {
  get {
   return this. < Name > i__Field;
  }
 }
 public < > f__AnonymousType0( < Id > j__TPar Id, < Name > j__TPar Name) {
  this. < Id > i__Field = Id;
  this. < Name > i__Field = Name;
 }
 public override bool Equals(object value) {}
 public override int GetHashCode() {}
 public override string ToString() {}
}
```

# LINQ

!!! todo

    BEISPIELE AUS MUSTERLÖSUNG DER ÜBUNGEN

* Language integrated Query
* Reine Compiler-Technologie
* Erlaubt Funktionale Programmierung mittels Lambda Expressions
* Redundante Typ-Informationen können beim Programmieren weggelassen werden
* Implementiert über Extension Methods `using System.Linq;`

!!! warning

    Ohne `using System.Linq;` läuft nix!


```csharp
string[] cities = { "Bern", "Basel", "Zürich", "Rapperswil", "Genf" };

// Query 2
IEnumerable<string> q2 = from c in cities
                      where c.StartsWith("B")
                      orderby c
                      select c;
// Wird zu
IEnumerable<string> l2 = cities
 .Where(c => c.StartsWith("B"))
 .OrderBy(c => c);
// `Where` und `OrderBy` sind ExtensionMethods
foreach (string c in citiesB) { /* ... */ }

cities[0] = "Luzern";
// Ausführung: 1 Stadt (Basel)
foreach (string c in citiesB) { /* ... */ }

```

Queries können beliebig oft ausgeführt werden
→  Resultate können jedesmal unterschiedlich sein


sofortige ausführung

```csharp
// Ausführung
List<string> citiesB = cities
                        .Where(c => c.StartsWith("B"))
                        .ToList();
// Ausführung
int citiesEndL = cities
                 .Where(c => c.EndsWith("l"))
                 .Count();
```


```
from     Definiert eine Range-Variable und eine Datenquelle
where    Filter
orderby  Sortierung
select   Projektion auf einen Elementtypen
group    Gruppierung in eine Sequenz von Guppen-Elementen
join     Verknüpfung zweier Datenquellen
let      Definition von Hilfsvariablen
```

```
from s in Students
join m in Markings on s.Id equalsm.StudentId
group s by s.Subject into g
select g;
```

```csharp
var q1 = from s in Students             // Variable
         where s.Subject == "Computing"
         orderby s.Name
         select new { s.Id, s.Name };
// Compiler-Output
var q2 = Students
            .Where(s => s.Subject == "Computing")
            .OrderBy(s => s.Name)
            .Select(s => new { s.Id, s.Name });
```
