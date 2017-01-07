# Testat 1
## main.cpp
```c++
#include "pocketcalculator.h"
#include <iostream>
#include <string>

int main(int const argc, char* const argv[]) {
	// First argument is scale, second is maxWidth
	unsigned scale{1};
	unsigned maxWidth{0};
	switch(argc){
		case 3:
			maxWidth = std::stoi(argv[2]);
		case 2:
			scale = std::stoi(argv[1]);
			break;
	}

	pocketcalculator(std::cin, std::cout, scale, maxWidth);
	std::cout << "Bye\n";
	return 0;
}
```
## calc.h
```c++
#ifndef CALC_H_
#define CALC_H_

#include <iosfwd>

int calc(int lhs, int rhs, char op, bool & error);
int calc(std::istream & in, bool & error);


#endif /* CALC_H_ */
```
## calc.cpp
```c++
#include "calc.h"

#include <sstream>
#include <string>
#include <istream>

int calc(int lhs, int rhs, char op, bool & error) {
	error = false;
	switch (op) {
		case '+':
			return lhs + rhs;
		case '-':
			return lhs - rhs;
		case '*':
			return lhs * rhs;
		case '/':
			if(rhs == 0){
				error = true;
				return -1;
			}
			return lhs / rhs;
		case '%':
			if(rhs == 0){
				error = true;
				return -1;
			}
			return lhs % rhs;
		default:
			error = true;
			return -1;
	}
}

int calc(std::istream & in, bool & error){
	int lhs{-1};
	char op {};
	int rhs{-1};

	std::string line{};
	getline(in, line);
	std::istringstream is{line};

	if(is >> lhs >> op >> rhs){
		return calc(lhs,rhs, op, error);
	}

	error = true;
	return -1;
}
```
## pocketcalculator.h
```c++
#ifndef POCKETCALCULATOR_H_
#define POCKETCALCULATOR_H_

#include <iosfwd>

void pocketcalculator(std::istream & in, std::ostream & out, unsigned const scale=1, unsigned const maxWidth=0);

#endif /* POCKETCALCULATOR_H_ */
```
## pocketcalculator.cpp
```c++
#include "pocketcalculator.h"
#include "sevensegment.h"
#include "calc.h"

#include <istream>
#include <ostream>
#include <exception>


void pocketcalculator(std::istream & in, std::ostream & out, unsigned const scale, unsigned const maxWidth){
	while(in){
		bool error{false};
		int result = calc(in, error);
		if(!in.eof()){
			if(error){
				printError(out, scale);
			}else{
				printLargeNumber(result, out, scale, maxWidth);
			}
		}
	}
}
```

## sevensegment.h
```c++
#ifndef SEVENSEGMENTS_H_
#define SEVENSEGMENTS_H_

#include <iosfwd>

void printLargeNumber(int const i, std::ostream & out, unsigned const scale=1, unsigned maxWidth=0);
void printError(std::ostream & out, unsigned const scale=1);
void printLargeDigit(int const i, std::ostream & out);

#endif /* SEVENSEGMENTS_H_ */
```
## sevensegment.cpp
```c++
#include "sevensegment.h"
#include <ostream>
#include <iterator>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
std::vector<std::vector<std::string>> const DIGITS {
		{" - ", "   ", " - ", " - ", "   ", " - ", " - ", " - ", " - ", " - ", " - ", "   ", "   "},
		{"| |", "  |", "  |", "  |", "| |", "|  ", "|  ", "  |", "| |", "| |", "|  ", "   ", "   "},
		{"   ", "   ", " - ", " - ", " - ", " - ", " - ", "   ", " - ", " - ", " - ", " - ", " - "},
		{"| |", "  |", "|  ", "  |", "  |", "  |", "| |", "  |", "| |", "  |", "|  ", "|  ", "| |"},
		{" - ", "   ", " - ", " - ", "   ", " - ", " - ", "   ", " - ", " - ", " - ", "   ", " - "},
	};
void doPrint(std::string s, std::ostream & out, unsigned const scale){
	unsigned index {0};
	for_each(cbegin(DIGITS), cend(DIGITS), [s, &out, &index, scale](auto line){
		++index;
		std::ostringstream buffer{};
		for_each(cbegin(s), cend(s), [line, &buffer, &index, scale](auto x){
			// TODO: aufsplitten
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
void printError(std::ostream & out, unsigned const scale){
	std::string s{"Error"};
	doPrint(s, out, scale);
}
void printLargeNumber(int const i, std::ostream & out, unsigned const scale, unsigned const maxWidth){
	auto s = std::to_string(i);
	if(maxWidth > 0 && s.length() > maxWidth){
		printError(out, scale);
	}else{
		doPrint(s, out, scale);
	}
}
void printLargeDigit(int const i, std::ostream & out) {
	for_each(cbegin(DIGITS), cend(DIGITS), [i, &out](auto x){
		out << x.at(i) << '\n';
	});
}
```
## Test.cpp
```c++
#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include "sevensegment.h"
#include "calc.h"
#include "pocketcalculator.h"
#include <sstream>

// ...
void testModuleZero(){
	bool error{false};
	auto result = calc(42, 0, '%', error);
	ASSERT_EQUAL(-1, result);
	ASSERT_EQUAL(error, true);
}

void testPocketCalculatorEmpty(){
	std::ostringstream out{};
	std::istringstream in{};
	pocketcalculator(in, out, 1, 1);
	std::string expected = "Bye\n";
	ASSERT_EQUAL(expected, out.str());
}

bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	s.push_back(CUTE(testSevenSegmentZeroDigit));
    //...
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner { cute::makeRunner(lis, argc, argv) };
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
```
