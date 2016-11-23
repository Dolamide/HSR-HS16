/*
 * MyMin.h
 *
 *  Created on: Nov 23, 2016
 *      Author: rzi
 */

#ifndef MYMIN_H_
#define MYMIN_H_

#include <string>

namespace MyMin {
template <typename T>
T const& min(T const & a, T const & b){
	return (a < b)?a : b;
}
char const * min(char const* a, char const * b){
    // TODO: Don't do this inline - avoid std::string in header!
    return std::string(a) < std::string(b)? a:b;
}
}


#endif /* MYMIN_H_ */
