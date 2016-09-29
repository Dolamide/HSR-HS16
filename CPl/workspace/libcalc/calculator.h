#ifndef CALCULATOR_H_
#define CALCULATOR_H_

#include <iosfwd>

int calc(std::istream& in);

int calc(int lhs, int rhs, char op);

#endif /* CALCULATOR_H_ */