# Functors and Parameterizing STL

**Lambdas sind Funktoren** - der C++ Compiler mapt intern die lambdas auf Funktoren mit einem versteckten/unerreichbaren Klassennamen


Predicate
: Eine Funktion oder Lambda, welches 1 (unary), 2 (binary) oder n Parameter nimmt und ein boolean zurückliefert.

UnaryFunction
: Funktion, die genau einen Parameter akzeptiert

BinaryFunction
: Funktion, die genau zwei Parameter akzeptiert


Ein Funktor ist ein Typ (Klasse), welche "callable" ist.
Dies kann mit der `operator()(...)`-Methode erreicht werden:

Ein Funktor ist ein Typ (Klasse), welche den call-Operator implementiert.

Operator kann beliebig überladen werden - je nach Bedüfnis
→ Operator = aufruf mit `()` → S Bsp. `average`


## Function Objects (Funktoren)
```c++
struct donothingfunctor {
    void operator()()const{};
}

int main(){
	donothingfunctor const f{};
	f();
	donothingfunctor{}();
}
```

## Generator Functions
Algorithmus, welcher eine neue werte generiert.
Benötigt "memory" um unterschiedliche werte generiern zu können.

```c++
std::vector<int> v{0};
int x{}; // memory for lambda below
generate_n(std::back_inserter(v),10,[&x](){
    ++x; return x*x;
});
// v contains now 0, 1, 4, 9, 16, 25, 36, ..., 100
```


## Standard Functoren

Können für bessere lesbarkeit und wartbarkeit anstelle von Lambdas für einfache Aktionen/Transformationen verwendet werden.
Beispielswiese enspricht `std::negate<int>{}` in etwa `[](int x){return -x;}`.

Binäre functor klassen

* `plus<>`
* `minus<>`
* `divides<>`
* `multiplies<>`
* `modulus<>`
* `locical_and<>`
* `locical_or<>`
* `less<>`
* `less_equal<>`
* `equal_to<>`
* `greater_equal<>`
* `greater<>`
* `not_equal_to<>`

Unäre functor klassen

* `negate<>`
* `logical_not<>`

```c++
#include <functional>

std::transform(v.begin(), v.end(), v.begin(), std::negate<int{});
// parameter type deduced
std::sort(v.begin(),v.end(),std::greater<>{});
```

## Parameterized Associative Containers

Standard functor Klassen können auch für die Parameterisierung über Template argumente für Vergleichsoperationen in Containern verwendet werden.

```c++
std::set<int, std::greater<>> reverse_int_set{};
```

```c++
struct caseless{
	using string=std::string;
	bool operator()(string const &l, string const &r){
		return std::lexicographical_compare(
				l.begin(),l.end(),r.begin(),r.end(),
				[](char l,char r){
			return std::tolower(l) < std::tolower(r);
		});
	}
};
int main(){
    std::set<int,std::greater<>> reverse_int_set{};
    using in=std::istream_iterator<std::string>;

    std::multiset<std::string,caseless> wlist{in{std::cin},in{}};

    // Print it
    std::ostream_iterator<std::string> out{std::cout,"\n"};
    copy(wlist.begin(),wlist.end(),out);
}
```

## Funktionen als Parameter

(Via Template Typenname → Später)

Way to go:

`foo(double f(double));` → Geht mit Funktionen und Lambdas - nicht aber mit Funktoren!

Darum `std::function<double(double)>` verwenden. Lambdas, Funktoren und Funktionen können in diesen Typ _umgewandelt_ werden bzw. erfüllen diesen typ.

Ist Zudem sehr gut lesbar

!!! warning

    Include nicht vergessen! `#include <functional>`

```c++
void apply_and_print(std::ostream& out, std::function<bool(int)> apredicate) {
	if (apredicate) { // implicit bool conversion, true if apredicate is not empty
		out << "pred(42) is " << apredicate(42) << '\n';
	} else {
		out << "empty function holder\n";
    }
}

int main(){
    using std::cout;
    cout << std::boolalpha;

    // Aufruf mit std::function. Default ist empty
    std::function<bool(int)> apredicate { };
    apply_and_print(cout,apredicate);
    // "empty function holder"

    // Aufruf mit lambda
    apredicate = [](int i){return i%2;};
    apply_and_print(cout,apredicate);
    // pred(42) is false

    // Aufruf mit funktion
    apredicate = std::not1(apredicate);
    apply_and_print(cout,apredicate);
    // pred(42) is true

    // nullptr wird zu einer leeren funktion
    apredicate = nullptr;
    apply_and_print(cout,apredicate);
    // "empty function holder"
}
```

## Member(-Funtion) Pointer
Folie 20 (std::function with member functions)

Member(-Funtion) Pointers waren vor der Einführung von Lambdas in C++ das ensprechende Instrument.

Dabei wurde beim Funktionsaufruf die `this` Referenz als auch  ein Pointer auf eine Member-Funktion mitgegeben.

```c++
struct X {
    void foo() const { std::cout << a << " foo\n"; }
    int a;
}

void doit(void (X::*memberfunc)() const, // Function pointer
           X const &x){                 // this
    (x.*memberfunc)();                  // Call function on this
}

int main() {
    X x{1,2};
    doit(&X::foo, x); // 1 foo
}

```
