#ifndef POCKETCALCULATOR_H_
#define POCKETCALCULATOR_H_

#include <iosfwd>

void pocketcalculator(std::istream& in, std::ostream& out, unsigned const scale=1, unsigned const maxWidth=0);

#endif /* POCKETCALCULATOR_H_ */