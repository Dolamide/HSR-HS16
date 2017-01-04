# Pitfalls

## Klassendeklaration

```csharp
// Initialisiert nur kreis 3!
Circle kreis1, kreis2, kreis3 = new Circle();
```

## Properties
Wenn die Default-Implementierung für Properties verwendet wird, also einfach `get;set;`, so wird kein *Backing-Property* benötigt.

```csharp
public string MyProperty {get;set;} 
```

Falls aber für den Setter/Getter eine spezifische Implementierung verwendet wird muss ein *Backing-Property* eingeführt werden.

```csharp
private string _myProperty;
public string MyProperty
{
    get { return _myProperty; }
    set { _myProperty = value; }
}
```
