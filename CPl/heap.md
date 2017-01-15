# "Naked" Arrays
Nakte Arrays = nakter Pointer auf das erste Element wie in C. Dies ist Problematisch, da gleich wie in C die Dimension verloren geht (Bsp. `int a[5]`). Folglich muss die Dimension spearat (Bsp. `argc` bei `main`) bergeben werden - oder eine Konvention etablieren, wann ein Array "zu Ende ist" (bsp. `\0`).

Die Dimension eines Arrays kann auch mit Hilfe von Templates herausgefunden werden:

```c++
template <typename T, unsigned N>
void printArray(stD::ostream & out, T const ( & x )[N]){
    copy(x, x+N, std::ostream_iterator<T>{out, ", "});
}
// ...
int a[]={1,2,3};
printArray(std::cout,a);
```

Array-Pointers sind Random-access Iteratoren:

```c++
// Echo implementation
int main(int argc, char * argv[]){
    copy(argv+1 // second element (Like "echo")
        argv+argc // first element + dimension = past-the-end,
        std::ostream_iterator<std::string>{std::cout, " "});
    )
}
```
In C++ sollten "nakte" Arrays wann immer möglich vermieden werden und alternativ `std::vector<int>` oder `std::array<int, 5>` verwendet werden.
Die wohl einzige Ausnahme ist die `main`-Methode.
Grund: Zugriff Kann mit falscher Grösse = Undefined Behaviour

!!! warning

    * Arrays ohne initializer `{}` = Undefined behaviour
    * Zugriff auf multidimensionale Arrays mit mehreren Klammern: `m[0][1]` und **nicht **mit Komma

# Die Main-Methode
Die Main-Funktion in C++ nutzt "Nakte" Arrays (`int main(int argc, char *argv[])`) und ist ein Erbstück aus C.

`argv` beinhaltet Pointer auf Strings der einzelnen Aufrufparameter (`argv[0]` ist das executable, `argv[1]` der erste Parameter usw.)

`argc` gibt die Anzahl der Parameter an.

# Dynamic Heap Memory Management

Glücklicherweise wird Heap-Management nur selten benötigt aber manchmal halt doch. Referenzparameter oder plain member objects/containers sollten wann immer bevorzugt werden!

Mögliche Anwendungsfälle sind u.a.

* Factory Methoden, welche eine Instanz retournieren
* Eigene Object-Networks.
* Laufzeit Polymorphismus
* Class-Members, die nicht pass by reference übergeben werden können


Heap-Management muss manuell gemacht werden - geht sehr schnell schief!

* memory leaks
* dangling pointers
* double deletes

Darum: `new` und `delete` **nicht** brauchen sondern Hilfskonstrukte der Std-Lib (oder anderen Bibliotheken) nutzen:

* `std::unique_ptr<T>`
    * **nicht kopierbar**
    * only returned by value
    * Für eine polymorphistische Referenz bei einer Klasse
    * can not transfer ownership -> can not leak!
    * Erstellen mit `make_unique<T>(param1, param2)` wobei die Parameter demjenigen des Public-Konstruktors von T ensprechen
* `std::shared_ptr<T>` kopierbar
    * Mehr wie Javas Referenzen
    * Können Kopiert werden
    * Letzte existierende Referenz löscht das objekt.
    * Erstellen mit `make_shared<T>(param1, param2)` wobei die Parameter demjeniged des Public-Konstruktors von T ensprechen
    * Zykeln möglich → Dann `weak_ptr` nutzen!
        * Inkrementiert den Counter nicht - kann also auf ein gelöschtes Objekt zeigen. - Check mit bsp. `if(!myWeakPtr.expired()){ ... }`
        * Für zugriff auf darunterliegender `shared_ptr` muss `lock()` aufgerufen werden:

        ```c++
        auto realfather = father.lock();
        if(realfather){
            out << realfather;
        }else{
            out << "expired";
        }
        ```


!!! warning

    `#include <memory>` nicht vergessen!

## Beispiel

* Rekursive Definition (Attribut Person auf Klasse Person) geht nicht (`incomplete`)
* Vorwärtsdeklaration von Person - für PersonPtr

```c++
#include <memory>
#include <string>
#include <ostream>
#include <vector>
#include <algorithm>

using NodePtr=std::shared_ptr<class Node>;

class Node {
	std::string moduleName;
	std::vector<NodePtr> dependencies;

public:
	Node(std::string moduleName) : moduleName{moduleName}{}
	void addDependency(NodePtr ptr) {
		dependencies.push_back(ptr);
	}

	void removeDependency(NodePtr ptr) {
		auto removed = std::remove(dependencies.begin(), dependencies.end(), ptr);
		if(removed != dependencies.end()){
			dependencies.erase(removed);
		}
	}

	bool hasDependencies() const {
		return !dependencies.empty();
	}

static NodePtr makeNode(std::string moduleName){
	return std::make_shared<Node>(moduleName);
}
};

// Usage
NotePtr module = Node::makeNode(moduleName);
module->addDependency(anotherModule);
```

## Übungsfragen HEAP
Which C++ mechanism can you use to deduce a dimension of an array passed as function parameter?
→ Templates

```c++
template <typename T, unsigned N>
void printArray(stD::ostream &out, T const (&x)[N]){
    copy(x, x=N, std::ostream_iterator<T>{out, ", "});
}
```

How do you create an instance of the default-constructible type Block on the heap? with `std::make_unique<Block>();`

How do you delete the instance created on the heap? It will be removet automagically when not referenced anymore (With `}`)

What problem arises if you have loops in your object structure and how do you solve this?

It works, but not with references. E.g. a vector of `Person` on the Object `Person` contains the objects themselfes - not their references. To use references, (shared) Pointers can be used.

 How can you access to a shared pointer from within the this object? `this->pointer`!?
