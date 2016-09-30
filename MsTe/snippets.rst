Snippets
=========

Namespaces
----------
.. code:: c#

    // Namespace deklarieren
    namespace A
    {
        // namespace importieren
        using C;
        // alias:
        using Q = System.Windows.Forms;
    }

Enums
-----

.. code:: c#

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
    Enum.TryParse("Monday", out day2); // Generic

Arrays
------

.. code:: c#

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

Switch
------
.. code:: c#

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

for / foreach
--------------
.. code:: c#

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

Main
----
.. code:: c#

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

Strings
-------
..code:: c#

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


GoTo
----

.. code:: c#

    for (int i = 0; i < 10; i++) {
        if (i == 1) { continue; }
        if (i == 3) { goto myLabel; }
        if (i == 5) { break; }
        Console.WriteLine(i);
    myLabel: ;
    }
