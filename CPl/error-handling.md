# Error Handling

Fehler wenn: Precondition falsch (bsp. negativer index) oder Postcondition (bsp. datei existiert nicht)
"Contract can not be fulfilled"

Möglichkeiten zur Feherbehandliung

1. ignorieren
2. Standard resultat
3. Error-Code
4. Error status (seiteneffekt)
5. throw Exception

## Cover Error with a Standard Result

```c++
std::string inputName(std::istream &in, std::string const &def="anonymous") {
    std::string name{};
    in >> name;
    return name.size()?name:def;
}
```


## Exceptions

**throw by value, catch by const reference**

Immer unchecked - also müsen/können nicht spezifiziert werden
Keine Meta-info verfügbar (kein stack trace usw.)

```c++
try {

    throw value; // ANY copyable can be thrown!
} catch(type const &e){ // catch by const reference
    // ...
} catch (...){ // ... fängt alles - catch 'em all!

}
```

In <stdexcept> der stdlib gibt es eineige vordefinierte Exceptions, die abgefangen werden können.
Bsp: logic_error, invalid_argument, out_of_range - bsp. `throw std::invalid_argument{"too small"};`

```c++
try {
    throw std::logic_error("That is not logical!")
} catch(std::logic_error const & e){
    std::cout << e.what()
}
```


### Testing for Exceptions

```c++

void testSquareRootNegativeThrows(){
    ASSERT_THROWS(square_root(-1.0),std::invalid_argument);
}
void testSquareRootNegativeThrows2(){
    try {
        square_root(-1.0);
        FAILM("expected Exception!")
    }catch(std::invalid_argument const&){
        // expected
    }
}
```
