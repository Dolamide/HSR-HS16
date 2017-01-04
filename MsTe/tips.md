# Tips

## Konsolenfester offen halten
```csharp
Console.ReadLine(); // weiter mit \n
Console.ReadLine(); // weiter mit beliebiger Taste
```

## @ Quote Strings

* Backslash `\` wird nicht mehr als Escape-Sequenz interpretiert
* Double-Quotes " müssen mit einem zweiten Double-Quote escaped werden
* String darf mehrere Zeilen umfassen

```
// file
// "C:\sample.txt"

str =
@"file
""C:\sample.txt""";
```
