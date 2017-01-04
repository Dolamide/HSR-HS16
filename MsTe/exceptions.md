# Exceptions

Sehr analog zu Java, also

* Sequenzielle abarbeitung
* Genau ein Block, der ausgeführt wird
* Exceptions müssen von System.Exception ableiten

Als Parameter kann eine String und als zweiter Parameter die "inner-Exception" übergeben werden.

Wichtige Attribute sind `InnerException`, `Message`, `Source`, `StackTrace` und `TargetSite`.

!!! warning

    Alle Exceptions sind unchecked

```csharp
FileStream s = null;
try {
    s = new FileStream(@"C:\Temp\Test.txt", FileMode.Open);
    /* ... */
} catch (FileNotFoundException e) {
    Console.WriteLine("{0} not found", e.FileName);
}
// Variable kann weggelassen weden - falls nicht benötigt
catch (IOException) {
    Console.WriteLine("IO exception occurred");
}
// Catch 'em all! (= catch(System.Exception))
catch {
    Console.WriteLine("Unknown error occurred");
} finally {
    if (s != null) s.Close();
}
```

Wird bei einem Multicast-Delegates eine Exception ausgeführt, so wird
die Ausführung weiterer Delegates unterbrochen!

## Exception Filters (C# 6)
```csharp
try
{
  /* ... */
  int i = 0;
  int x1 = 12 / i;
}
catch (Exception e) when (DateTime.Now.Hour < 18) { }
catch (Exception e) when (DateTime.Now.Hour >= 18) { }
```
