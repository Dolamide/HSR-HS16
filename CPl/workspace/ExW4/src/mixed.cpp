#include "mixed.h"

#include <iosfwd>
#include <string>
#include <iterator>
#include <vector>
#include <algorithm>
#include <iostream>

std::set<std::string> wlist(std::istream & in){
	using input = std::istream_iterator<std::string>;
	input in_iterator{in};
	input eof{};
	std::vector<std::string> allwords { in_iterator, eof };

	std::transform(allwords.begin(), allwords.end(), allwords.begin(), [](std::string c){
		// transform to lowercase
		std::transform(c.begin(), c.end(),c.begin(), ::tolower);
		return c;
	});

	// contains a **sorted set ** of unique objects of type Key.
	std::set<std::string> uniqueWords { allwords.begin(), allwords.end() };

	return uniqueWords;

}

int countingToLower(std::string& in) {
	int counter{0};
	std::transform(in.begin(), in.end(), in.begin(), [&counter](char it){
		char c = ::tolower(it);
		if(c != it){
			counter++;
		}
		return c;
	});
	return counter;
}


void printFunctionTable(std::ostream & out, double start, double step, int steps, double f(double)){
	std::vector<double> results(steps);
	double i { start };
	std::generate_n(results.begin(), steps,[&f, &i, &step](){
		double result = f(i);
		i += step;
		return result;
	});
}
//std::string -> #include <string>
//std::cin -> #include <iostream>
//std::istream -> #include <iosfwd>
//istream_iterator -> #include <iterator>
//std::vector -> #include <vector>