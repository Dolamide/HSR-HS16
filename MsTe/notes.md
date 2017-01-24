# Siehe Dokument Skripteserver

Sicher was zu GC oder deterministic finalization

ca 80% für 6er - 50% für 4er - hat wohl nicht zeit für alles. -> Nicht von vorne nach hinten sondern **Themen, die im Griff**.


```csharp
delegate Func<T>(T param1);

public class MyClass{

   public Func<int> f;
   // Delegate alles public - event kapselt und mach priate
   public int foo(){
     return 1;
   }
   
   public MyClass(){
      f = this.foo;
   }
}
```

Func inst delegate aus .NET. das hier ist eine Deklaration als Member.


Delegate -= doo
-> -= retourniert neues Delegate objekt. -> Übung Grundlagen C# A



* LINQ
* Repetitionen
