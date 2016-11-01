/*
 * Word.h
 *
 *  Created on: Oct 28, 2016
 *      Author: rzi
 */

#ifndef SRC_WORD_H_
#define SRC_WORD_H_
#include <string>
#include <iosfwd>
#include <vector>
#include <set>

namespace testat {

class Word {
std::string value;

bool isValid(std::string test) const;
public:
	Word();
	Word(std::string in);
	std::ostream & print(std::ostream & out) const;
	std::istream & read(std::istream & in);

	bool operator<(Word const & otherWord) const;
};


std::set<Word> wlist(std::istream & in);

std::istream & operator>>(std::istream & in, Word & word);
std::ostream & operator<<(std::ostream & out, Word & word);

inline bool operator>(Word const & lhs, Word const & rhs) {
    return rhs < lhs;
}
inline bool operator>=(Word const & lhs, Word const & rhs) {
    return !(lhs < rhs);
}
inline bool operator<=(Word const & lhs, Word const & rhs) {
    return !(rhs < lhs);
}
inline bool operator==(Word const & lhs, Word const & rhs) {
    return !(lhs < rhs) && !(rhs < lhs);
}
inline bool operator!=(Word const & lhs, Word const & rhs) {
    return !(lhs == rhs);
}


}

#endif /* SRC_WORD_H_ */
