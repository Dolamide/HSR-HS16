#include "calculations.h"
#include <iosfwd>
#include <iterator>
#include <vector>
#include <string>
#include <algorithm>


std::vector<std::vector<std::string>> const DIGITS {
		{" - ", "   ", " - ", " - ", "   ", " - ", " - ", " - ", " - ", " - " },
		{"| |", "  |", "  |", "  |", "| |", "|  ", "|  ", "  |", "| |", "| |"},
		{"   ", "   ", " - ", " - ", " - ", " - ", " - ", "   ", " - ", " - "},
		{"| |", "  |", "|  ", "  |", "  |", "  |", "| |", "  |", "| |", "  |"},
		{" - ", "   ", " - ", " - ", "   ", " - ", " - ", "   ", " - ", " - "},
	};

void printLargeNumber(int i, std::ostream &out){
	printLargeNumber(i, out, 1);
}

void printLargeNumber(int i, std::ostream &out, const int scale){
	auto s = std::to_string(i);
	int counter {0};
	for_each(cbegin(DIGITS), cend(DIGITS), [s, &out, &counter, scale](auto line){
		++counter;
		const int repetitions {(counter == 2 || counter == 4) ? scale : 1};
		for (int var = 0; var < repetitions; ++var) {
			for_each(cbegin(s), cend(s), [line, &out, &counter, scale](auto x){
				int num = (x - '0');
				out << line.at(num);
			});
			out << '\n';
		}
	});
}

void printLargeDigit(int i, std::ostream &out) {
	for_each(cbegin(DIGITS), cend(DIGITS), [i, &out](auto x){
		out << x.at(i) << '\n';
	});
}
