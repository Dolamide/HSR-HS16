Ist std::string ein value type?
Ja

unsigned zahlen haben ...
* nur positive Zahlen (X)
* ein vorzeichen

Sind overflows mit unsigned int möglich?
Nein -> sind als modulo 2^n deifiniert (n = implementationsgrösse)
     -> falls kein plats: max möglicher wert.

Wie können strings 2 ints geparsed werden?
#include <string>
std::stoi("4");
