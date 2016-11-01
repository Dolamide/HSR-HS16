/*
 * wlist.h
 *
 *  Created on: Oct 24, 2016
 *      Author: rzi
 */

#ifndef SRC_MIXED_H_
#define SRC_MIXED_H_

#include <functional>
#include <iosfwd>
#include <set>
#include <string>

std::set<std::string> wlist(std::istream & in);
int countingToLower(std::string & in);

void printFunctionTable(std::ostream & out, double begin, double end, int steps, double f(double));

#endif /* SRC_MIXED_H_ */