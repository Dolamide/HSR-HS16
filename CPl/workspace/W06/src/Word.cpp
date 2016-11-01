/*
 * Word.cpp
 *
 *  Created on: Oct 28, 2016
 *      Author: rzi
 */

#include "Word.h"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <stdexcept>

namespace testat {

Word::Word(){

}

Word::Word(std::string in){
	if(!isValid(in)){
		throw std::out_of_range("Given string contains invalid characters!");
	}
	value = in;
}

bool Word::isValid(std::string test) const {
	if(test.size() == 0){
		return false;
	}
	bool valid{true};
	for_each(test.cbegin(), test.cend(), [&valid](char c){
		if(!std::isalpha(c)){
			valid = false;
		}
	});
	return valid;
}

bool Word::operator <(Word const & other) const{
	std::string myValue = value;
	std::string otherValue = other.value;
	std::transform(myValue.begin(), myValue.end(), myValue.begin(), ::tolower);
	std::transform(otherValue.begin(), otherValue.end(), otherValue.begin(), ::tolower);
	return myValue < otherValue;
}


std::ostream & Word::print(std::ostream & out) const{
	copy(value.cbegin(), value.cend(), std::ostream_iterator<char>{out});
	return out;
}

std::istream & Word::read(std::istream & in){
	char c{};
		std::string parsed{};
		while(in.get(c)){
			if(std::isalpha(c)){
				parsed += c;
			}else if(parsed.size() > 0) {
				break;
			}
		}

		// Do not override anything if nothing could be read.
		// isValid could be called here - but it would be too redundant
		if(parsed.size() == 0){
			return in;
		}
		value = parsed;
		return in;
}

std::istream & operator>>(std::istream & in, Word & word){
	return word.read(in);
}

std::ostream & operator<<(std::ostream & out, Word & word){
	return word.print(out);
}

std::set<Word> wlist(std::istream & in){
	using input = std::istream_iterator<std::string>;
	input in_iterator{in};
	input eof{};
	std::vector<Word> allwords { in_iterator, eof };

	// contains a **sorted set ** of unique objects of type Key.
	std::set<Word> uniqueWords { allwords.begin(), allwords.end() };

	return uniqueWords;
}


} /* namespace testat */
