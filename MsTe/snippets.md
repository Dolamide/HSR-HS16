# Snippets

## Namespaces
```cs
// Namespace deklarieren
namespace A
{
    // namespace importieren
    using C;
    // alias:
    using Q = System.Windows.Forms;
}
```

## Enums
```cs
// Werte werden implizit mit dem Wert des Vorgängers+1 oder explizit gesetzt
// leitet by default von int32 ab
enum Days { Sunday = 10, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday };
            // 10        11        12       13          14        15        16
Days today = Days.Monday;
if (today == Days.Monday) { /* ... */ }
today = Days.Tuesday;

// Enums von Typen byte, sbyte, short, ushort, int, uint, long, ulong erlaubt
enum Days : byte { Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday };

// String wert -> ENUM parsen
Days day1 = (Days)Enum.Parse(typeof(Days), "Monday"); // Non-Generic
Days day2;

// VORSICHT out keyword! "The out keyword causes arguments to be passed by reference"
// out wird benötigt, da sonst pass-by-value!
Enum.TryParse("Monday", out day2); // Generic
```

## Arrays
```cs
int[] elements = new int[]{23, 9, 7};
elements[1]

// Mehrdimensional (rechteckig)
int[,] zelle = new int[4,3];
int[,,] elements = {
                 { {1,2,3,4},{3,4,5,6},{6,7,8,9}},
                 { {3,4,6,1},{6,19,3,4},{4,1,8,7}}
              };

//Mehrdimensional (Jagged)
int[][] jaggedArray = new int[6][];
jaggedArray[0] = new int[4] { 1, 2, 3, 4 };

// Grösse eines Arrays
Console.WriteLine(elements.Length);
```

## Switch
```cs
// geth für:
//sbyte, short, int, long (signed)
// byte, ushort, uint, ulong (unsigned)
// char, string
// enum
switch(Ausdruck) {
    case Konstante1 :
        ...
        break;
    case Konstante2 :
        ...
        break;
    default:
        ...
        break;
}
```
## for / foreach
```cs
// Normal For
for(int counter = 0; counter < 10; counter++) {
  Console.WriteLine("Zählerstand = {0}",counter);
  // break;
  // continue;
}

// For Each
int[] elements = {2,4,6,8};
foreach(int item in elements) {
  Console.WriteLine(item);
  // item = 4 ist hier unzulässig!
}

// Enums
foreach (string name in Enum.GetNames(typeof(Days))) {
    Console.WriteLine(name);
}
```

## Main
```cs
class Program {
  static void Main(string[] args) {

    // Prüfen, ob beim Programmaufruf eine oder mehrere

    // Zeichenfolgen übergeben worden sind

    if(args.Length > 0) {

      // die Zeichenfolgen an der Konsole anzeigen

      for(int i = 0; i < args.Length; i++)
        Console.WriteLine(args[i]);
      }
    else
      Console.WriteLine("Kein Übergabestring");
    Console.ReadLine();
  }
}
```

## Strings
```cs
// Länge des Strins
string.Length

string s1 = DateTime.Now + ": " + "Hello";
string s2 = string.Format("{0}: {1}", DateTime.Now, "Hello");

string s3 = $"{DateTime.Now}: {"Hello"}";
string s4 = $"{DateTime.Now}: {(DateTime.Now.Hour < 18 ? "Hello" : "Good Evening")}";

bool result1 = s1.Equals(s2);
// aber auch
bool result1 = s1 == s2;

bool result2 = string.ReferenceEquals(s1, s2);

@"c:\Docs\Source\a.txt"  // rather than "c:\\Docs\\Source\\a.txt"

@"""Ahoy!"" cried the captain." // "Ahoy!" cried the captain.
```

## GoTo
```cs
for (int i = 0; i < 10; i++) {
    if (i == 1) { continue; }
    if (i == 3) { goto myLabel; }
    if (i == 5) { break; }
    Console.WriteLine(i);
myLabel: ;
}
```
## Indexer
```cs
class MyClass {
    private string[] internalArr = new string[10];

    // int-indexer
    // int-Indexer mc[0] = "Hello";
    // string value1 = mc[0]; // Hello
    public string this[int index] {
        get { return internalArr[index]; }
        set { internalArr[index] = value; }
    }

    // string-Indexer
    // mc["0"] = "Hello"; <-- Compilerfehler - da read-only!
    // string value2 = mc["0"]; // Hello

    public string this[string index] {
        get { return internalArr[int.Parse(index)]; }
    }

    // 2-Dimensionaler Indexer
    // Bsp: string value3 = mc[0, 2];
    public string this[int i1, int i2] { /* ... */ } }
```

## Partials
```cs
// File1.cs
partial class MyClass {
    public void Test1() { }
}
// File2.cs
partial class MyClass {
    public void Test2() { }
}
// Verwendung
MyClass mc = new MyClass();
mc.Test1();
mc.Test2();
```

```cs
// File1.cs
partial class MyClass {
    public void Test1() {
        Test1Initialize();
        /* ... */
        Test1Cleanup();
    }
    // Deklaration!
    // Return-Type immer void!
    partial void Test1Initialize();
    partial void Test1Cleanup();
}
// File2.cs
partial class MyClass {
    // Implementation!
    // Return-Type immer void!
    public void Test2() { }
    partial void Test1Initialize()
    { /* */ }
}
```

## Konstruktor
-----------

```cs
public Book(string title, string author, bool available){}
public Book(string title, string author, bool available) : base(){}
public Book(string title, string author) : this(title, author, true) { }
public Book(string title) : this(title, "anonymous", true) { }
public Book() : this("untitled", "anonymous", true) { }
// ...
```

## Dispose Pattern

```cs
~DataAccess() { Dispose(false); }
public void Dispose()
{
    Dispose(true);
    System.GC.SuppressFinalize(this);
}

protected virtual void Dispose(bool disposing)
{
    if (disposing)
    {
            if (connection != null)
            {
                connection.Dispose();
            }
    } // Dispose unmanaged resources
}
```    

## Optionale Parameter

```cs
privat void Sort(int from=-1, int to=-1){};
```

## Operator-Overloading
```cs
class MyClass {
    private int x, y;
    public MyClass(int x, int y) {
        this.x = x;
        this.y = y;
    }
    // Rückgabetyp frei wählbar
    public static MyClass operator ~(MyClass a) {
        return new MyClass(a.x * -1, a.y * -1);
    }
    public static MyClass operator + (MyClass a, MyClass b) {
        return new MyClass(a.x + b.x, a.y + b.y);
    }

    // ...
    MyClass mcTotal = mc1 + mc2;
}
```

## Vererbung

```cs
class Base
{
    int a;
    public Base(){}
}
class Sub : Base
{
    public Sub(){}
}
```
