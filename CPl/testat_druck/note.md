```c++
#ifndef MODULE_H_
#define MODULE_H_

#include <memory>
#include <vector>
#include <algorithm>
#include <iosfwd>
#include <map>
#include <string>

struct module;

using module_ptr = std::shared_ptr<module>;
using modules = std::vector<module_ptr>;
using module_catalog = std::map<std::string, module_ptr>;

struct module : std::enable_shared_from_this<module> {
	module() = default;
	explicit module(std::string const & name) : name {name}{};

	void add_predecessor(module_ptr predecessor) {
		_predecessors.push_back(predecessor);
		predecessor->_successors.push_back(shared_from_this());
	}

	bool has_predecessor() const { return !_predecessors.empty(); }

	void update_earliest_semester(unsigned newEarliestSemester) {
		earliest_semester = std::max(newEarliestSemester, earliest_semester);
	}

	unsigned get_earliest_semester() const {  return earliest_semester;	}

	modules successors() const { return _successors;}

	modules predecessors() const { return _predecessors;}

	std::string const name;

private:
	unsigned earliest_semester{0};
	std::vector<module_ptr> _predecessors{};
	std::vector<module_ptr> _successors{};
};


inline std::ostream & operator<<(std::ostream& out, module_ptr m) {
	out << m->name;
	return out;
}

module_catalog read_modules(std::istream & input);

template<typename M>
inline std::vector<typename M::mapped_type> values(M const& catalog) {
	std::vector<typename M::mapped_type> values{};
	std::transform(std::begin(catalog), std::end(catalog), std::back_inserter(values),[](typename M::value_type const & pair){
		return pair.second;
	});
	return values;
}
#endif /* MODULE_H_ */
```

```c++
str1.erase(std::remove(str1.begin(), str1.end(), ' '),
           str1.end());
```

```c++
// Iterator constructor
template <typename Iterator>
vectorset(Iterator begin, Iterator end) {
    std::copy(begin, end, std::back_inserter(*this));
}
```

## Merke:
* `const` immer rechts vom Typ
* `const` Member gelten nicht für Member-Referenzen (eg. `std::ostream const & out;`)
* Statischer Member aufrufen: `vectorset<char>::demo();` oder direkt auf instantz wie "normal"
* Statische Member können nicht `const` sein.
* `++*foo` -> `++(*foo)` - Operator Rangordnung spielt keine Rolle!
