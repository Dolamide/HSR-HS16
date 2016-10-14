#include <sstream>
#include <string>
#include <iostream>

#include "calc.h"

int calc(int lhs, int rhs, char op, bool& error) {
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

int calc(std::istream& in, bool& error){
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
