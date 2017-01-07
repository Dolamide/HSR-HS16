# Testat 2
## main.cpp
```c++
#include "kwic.h"
#include <iostream>

// Parameter optional - können weggelassen werden,
// da nicht gebraucht
int main(int const argc, char* const argv[]) {
	kwic::kwic(std::cin, std::cout);
}
```
## word.h
```c++
#ifndef WORD_H_
#define WORD_H_
#include <string>
#include <iosfwd>
#include <set>
#include <vector>
#include <iterator>
#include <algorithm>
namespace word {
class Word {
	std::string value;
public:
	Word() = default;
	Word(std::string const & value);

	std::ostream & print(std::ostream & os) const;
	std::istream & read(std::istream & is);

	bool operator<(Word const & word) const;
};
std::set<Word> wlist(std::istream & in);
inline std::ostream & operator<<(std::ostream & os, Word const & word) {
	return word.print(os);
}
inline std::istream & operator>>(std::istream & is, Word & word) {
	return word.read(is);
}
inline bool operator>(Word const & lhs, Word const & rhs) {
	return rhs < lhs;
}
inline bool operator>=(Word const & lhs, Word const & rhs) {
	return !(lhs < rhs);
}
inline bool operator<=(Word const & lhs, Word const & rhs) {
	return !(rhs < lhs);
}
// nicht effizient (std::equal)
inline bool operator==(Word const & lhs, Word const & rhs) {
    std::equal
	return !(lhs < rhs) && !(rhs < lhs);
}
inline bool operator!=(Word const & lhs, Word const & rhs) {
	return !(lhs == rhs);
}
// Besser in cpp implementieren, da so viele
// header Abhängigkeiten
inline std::ostream & operator<<(std::ostream & out, std::vector<Word>const & words) {
	std::ostream_iterator<Word> output{out, " "};
	std::copy(words.begin(), words.end(), output);
	return out;
}
}
#endif /* WORD_H_ */
```
## word.cpp
```c++
#include "word.h"
/// #include <string>, <istream>, <ostream>, <iterator>, <algorithm>, <vector>, <set>, <cctype>, <stdexcept>
namespace word {
void validate(std::string const & word) {
	if(word.empty()) {
		throw std::invalid_argument{"cannot create empty word"};
	}
	bool hasValidChars = std::all_of(word.begin(), word.end(), [](char const c){
		return std::isalpha(c);
	});
	if (!hasValidChars) {
		throw std::invalid_argument{"invalid char in word"};
	}
}
Word::Word(std::string const & word) : value{word} {
	validate(word);
}
std::ostream & Word::print(std::ostream & os) const {
	os << value;
	return os;
}
std::istream & Word::read(std::istream & is) {
	std::string tempWord{};
	char c{};
	//skip first invalid chars
	while(!std::isalpha(is.peek()) && !is.eof()) {
		is.get(c);
	}
	if(is.eof()) {
		is.setstate(std::ios::failbit | is.rdstate());
	} else {
		while(std::isalpha(is.peek()) && !is.eof()) {
			is.get(c);
			tempWord.push_back(c);
		}
		value = tempWord;
		is.clear();
	}
	return is;
}
bool Word::operator<(Word const & word) const {
	return std::lexicographical_compare(value.begin(), value.end(), word.value.begin(), word.value.end(),
			[](char const c1, char const c2) {
				return std::tolower(c1) < std::tolower(c2);
			}
	);
}
std::set<Word> wlist(std::istream & in) {
	using input = std::istream_iterator<std::string>;
	input in_iterator{in};
	input eof{};
	//set is per default sorted
	std::set<Word> uniqueWords { in_iterator, eof };
	return uniqueWords;
}
}
```
## kwic.h
```c++
#ifndef KWIC_H_
#define KWIC_H_
#include <iosfwd>
namespace kwic {
void kwic(std::istream & is, std::ostream & os);
}
#endif /* KWIC_H_ */
```
## kwic.cpp
```c++
#include "kwic.h"
#include "word.h"
#include <iterator>
#include <ostream>
#include <istream>
#include <sstream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>

namespace word {
std::ostream & operator<<(std::ostream & out, std::set<std::vector<Word>>const & wordLines) {
	std::ostream_iterator<std::vector<Word>> output{out, "\n"};
	std::copy(wordLines.begin(), wordLines.end(), output);
	return out;
}

}

namespace kwic {
using word::Word;

void rotateWordLine(std::vector<Word> const wordLine, std::set<std::vector<Word>> & wordLineList) {
	std::vector<Word> rotatedLine{wordLine};
	std::for_each(wordLine.begin(), wordLine.end(), [&wordLineList, &rotatedLine](Word const & w) {
		std::rotate(rotatedLine.begin(), rotatedLine.begin() + 1, rotatedLine.end());
		wordLineList.insert(rotatedLine);
	});
}
void kwic(std::istream & is, std::ostream & os) {
	std::set<std::vector<Word>> wordLineList{};
	using input = std::istream_iterator<Word>;
	input eof{};
	std::string stringLine{};
	while(std::getline(is, stringLine)) {
		std::istringstream str{stringLine};
		input in{str};
		std::vector<Word> wordLine{in, eof};
		rotateWordLine(wordLine, wordLineList);
	}
	os << wordLineList;
}
}
```
## Test.cpp
```c++
void test_read_one_word() {
	Word w{};
	std::string expected{"abc"};
	std::istringstream is{"abc"};
	std::ostringstream resultStream{};
	is >> w;
	resultStream << w;
	ASSERT_EQUAL(expected, resultStream.str());
}
void test_cannot_create_empty_word() {
	ASSERT_THROWS(Word { "" }, std::invalid_argument);
}
void test_different_words_are_not_equal() {
	ASSERT_NOT_EQUAL_TO(Word{"Haskell"}, Word{"ML"});
}
void test_smaller_word_is_smaller() {
	ASSERT_LESS(Word { "Erlang" }, Word { "Fortran" });
}
void test_smaller_word_is_less_equal() {
	ASSERT_LESS_EQUAL(Word { "Algol" }, Word { "BCPL" });
}
void test_greater_word_with_capital_letters_is_greater() {
	ASSERT_GREATER(Word { "Lisp" }, Word { "brainfuck" });
}
```
