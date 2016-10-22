#include <iosfwd>
#include <iterator>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

#include "sevensegment.h"

std::vector<std::vector<std::string>> const DIGITS {
		{" - ", "   ", " - ", " - ", "   ", " - ", " - ", " - ", " - ", " - ", " - ", "   ", "   "},
		{"| |", "  |", "  |", "  |", "| |", "|  ", "|  ", "  |", "| |", "| |", "|  ", "   ", "   "},
		{"   ", "   ", " - ", " - ", " - ", " - ", " - ", "   ", " - ", " - ", " - ", " - ", " - "},
		{"| |", "  |", "|  ", "  |", "  |", "  |", "| |", "  |", "| |", "  |", "|  ", "|  ", "| |"},
		{" - ", "   ", " - ", " - ", "   ", " - ", " - ", "   ", " - ", " - ", " - ", "   ", " - "},
	};

void doPrint(std::string s, std::ostream &out, unsigned const scale){
	unsigned index {0};
	for_each(cbegin(DIGITS), cend(DIGITS), [s, &out, &index, scale](auto line){
		++index;

		std::ostringstream buffer{};
		for_each(cbegin(s), cend(s), [line, &buffer, &index, scale](auto x){
			switch(x){
				case 'E':
					buffer << line.at(10);
					break;
				case 'r':
					buffer << line.at(11);
					break;
				case 'o':
					buffer << line.at(12);
					break;
				default:
					int num{x - '0'};
					buffer << line.at(num);
			}
		});

		const unsigned repetitions {(index == 2u || index == 4u) ? scale : 1u};
		for (unsigned var = 0; var < repetitions; ++var) {
			out << buffer.str();
			out << '\n';
		}
	});
}

void printError(std::ostream &out, unsigned const scale){
	std::string s{"Error"};
	doPrint(s, out, scale);
}

void printLargeNumber(int const i, std::ostream &out, unsigned const scale, unsigned const maxWidth){
	auto s = std::to_string(i);
	if(maxWidth > 0 && s.length() > maxWidth){
		printError(out, scale);
	}else{
		doPrint(s, out, scale);
	}
}

void printLargeDigit(int const i, std::ostream &out) {
	for_each(cbegin(DIGITS), cend(DIGITS), [i, &out](auto x){
		out << x.at(i) << '\n';
	});
}
