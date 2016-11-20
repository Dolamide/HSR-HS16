# Algorithms

Algorhtmen nehmen ein oder mehrere Ranges in der Form von Iteratoren entgegen und führen darauf eine oder mehrere Aktionen wie Sortierung, Transformation, Ausgabe in einen Stream etc. aus.

Der Vorteil von Algorithmen im Gegensatz zu klassischen For/While-Schleifen sind primär:

* Minimieren von Fehlern (bsp. bei swap)
    * Vermeiden von OutOfBound ("one off error")
* Lesbarkeit
* Effizientere Implementiernug als wenn "von hand" - da diese auf bestimmte Iteratoren optimiert sind.

Recap: Last zeigt nicht auf das letzte, sondern das "beyond last" Element

## Exkurs: Funktor
Ein Funktor ist ein Typ (Klasse), welche "callable" ist.
Dies kann mit der `operator()(...)`-Methode erreicht werden:

```c++
struct Accumulator {
    int count{0};
    int accumulated_value{0};

    void operator()(int value) {
        count++;
        accumulated_value += value;
    }

    int average() const;
    int sum() const;
};
int average(std::vector<int> values) {
    Accumulator acc{};
    for(auto v : values) {
        acc(v);
    }
    return acc.average();
}
```

Lambdas werden im hintergrund in funktoren abgebidet

## Streams & Algorithmen
Um Streams und Algorithms zu kombinieren, müssen die Streams gewrapt werden:

```c++
void redirect(std::istream & in, std::ostream & out) {
    using in_iter = std::istream_iterator<char>;
    using out_iter = std::ostream_iterator<char>;
    in_iter eof{};
    std::copy(in_iter{in}, eof, out_iter{out});
}
```

## Häufig verwendete Algorithmen
### for_each

* Die übergebene Operation ist eine Funktion ein Lambda oder ein Funktor.
* Die übergebene Operation wird für jedes Element aufgerufen.
* Der Rückgabewert von `for_each` ist die Übergebene Operation.

```c++
std::vector<unsigned> values{3, 0, 1, 4, 0, 2};
auto f = [](unsigned v) {};
std::for_each(begin(values), end(values), f);
// oder inline
std::for_each(begin(values), end(values), [](unsigned v) {});
```
### transform

* Analog zu `map` in python
* Die übergebene Operation ist eine Funktion ein Lambda oder ein Funktor.

```c++
std::vector<int> counts{3, 0, 1, 4, 0, 2};
std::vector<char> letters{'g','a','u','y','f','o'};
std::vector<std::string> combined{};
auto times = [](int i, char c){return std::string(i, c);};
std::transform(begin(counts), end(counts), begin(letters),
               std::back_inserter(combined), times);
```

### merge

* Vereint zwei **sortiert** ranges

```c++
std::vector<int> r1{9, 12, 17, 23, 54, 57, 85, 95};
std::vector<int> r2{2, 30, 32, 41, 49, 63, 72, 88};
std::vector<int> d(r1.size() + r2.size(), 0);
```

### remove_if

* `std::remove_if` entfernt die Elemente nicht, sondern verschiebt die Elemente intern.
* Mit *Erase-Remove-Idiom* kann der container anschliessend auf dir korrekte grösse reduziert werden.

```c++
std::vector<unsigned> values{54, 13, 17, 95, 2, 57, 12, 9};
auto is_prime= [](unsigned u) {/*...*/};
auto removed = std::remove_if(begin(values), end(values), is_prime);
values.erase(removed, values.end());
```

### `accumulate`

* Ist eigentlich für numerische Werte geadcht - geht aber auch bsp. mit Strings
* Benötigt immer einen Start-Wert

```c++
std::vector<std::string> long_months{"Jan", "Mar", "May", "Jul", "Aug", "Oct", "Dec"};
std::string accumulated_string = std::accumulate(
    begin(long_months) + 1, //Second element
    end(long_months), //End
    long_months.at(0), //First element, usually the neutral element
    [](std::string const & acc, std::string const & element) {
            return acc + ", " + element;
    }); //Jan, Mar, May, Jul, Aug, Oct, Dec
```
### Heap
Mit den Heap-Algorithmen kann auf einem Random-Access-Iterator ein Heap simuliert werden - bsp. für PriorityQueue.

Garantiert:

* Das erste Element ist immer dsa grösste (max)
* Garantierte Performance-Garantien
    * `make_heap` $$3N$$ Vergleiche
    * `pop_heap` $$2 \cdot log(N)$$ Vergleiche
    * `push_heap` $$log(N)$$ Vergleiche
    * `sort_heap` $$N*log(N)$$ Vergleiche

!!! warning

    `pop_back` verhält sich gleich wie `std::remove_if` - die Elemente werden also nicht wirklich gelöscht sondern die Elemente rücken nach. Um die Elemente dann komplett zu löschen kann die Operation `pop_back()` verwendet werden.

```c++
std::vector<int> v{3,1,4,1,5,9,2,6};
make_heap(v.begin(),v.end());
pop_heap(v.begin(),v.end()); // Wird nicht wirklich entfernt
v.pop_back(); // Nun ist der Heap sauber aufgeräumt
v.push_back(8); // Neues Elemente an Ende Hinzufügen
push_heap(v.begin(),v.end()); // Heap sortiert das letzte element ein
sort_heap(v.begin(),v.end()); // sortiert den heap in aufsteigender reihenfolge
// Daimt geht die heap eigenschaft verlohren
```

### Weitere

Non-Modifying Sequence Operations

* condition checking
    * `all_of`
    * `any_of`
    * `none_of`
* finding elements
    * `find`, `find_if`, `find_if_not`
    * `find_end`
    * `find_first_of`
    * `adjacent_find`
    * `count`, `count_if`
    * `search`, `search_n`
* comparing ranges
    * `mismatch`
    * `equal`
    * `is_permutation`
* Andere
    * `for_each`
    * `is_permutation`

Mutating sequence operations

* `copy`, `copy_n`, `copy_if`, `copy_backward`
* `move`, `move_backward`
* `swap_ranges`
* `transform`
* `replace`, `replace_if`, `replace_copy`, `replace_copy_if`
* `fill`, `fill_n`
* `generate`, `generate_n`
* `remove`, `remove_if`, `remove_copy`, `remove_copy_if`
* `unique`, `unique_copy`
* `reverse`, `reverse_copy`
* `rotate`, `rotate_copy`
* `shuffle`
* `is_partitioned`, `partition`, `stable_partition`, `partition_copy`, `partition_point`

Sorting and Related Operations

* `sort`, `stable_sort`, `partial_sort`, `partial_sort_copy`
* `is_sorted`
* `nth_element`
* `lower_bound`, `upper_bound`, `equal_range`
* `binary_search`
* `merge`, `inplace_merge`
* `includes`, `set_union`, `set_intersection`, `set_difference`, `set_symmetric_difference`

Nach Suffix

* `_if`-Suffix: Es gibt viele Algorithmen mit if suffix:
    * `count_if`
    * `copy_if`
    * `replace_if`
    * `find_if`
    * `remove_if`
    * `replace_copy_if`
    * `find_if_not`
    * `remove_copy_if`
* `_n`-Suffix
    * `search_n`
    * `fill_n`
    * `for_each_n` (C++17)
    * `copy_n`
    * `generate_n`
