#ifndef SEVENSEGMENTS_CPP_
#define SEVENSEGMENTS_CPP_

#include <iosfwd>

void printLargeNumber(int const i, std::ostream &out, unsigned const scale=1, unsigned maxWidth=0);
void printError(std::ostream &out, unsigned const scale=1);
void printLargeDigit(int const i, std::ostream &out);

#endif /* SEVENSEGMENTS_CPP_ */
