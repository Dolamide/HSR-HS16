#include <iostream>
#include <exception>

#include "sevensegment.h"
#include "calc.h"
#include "pocketcalculator.h"

void pocketcalculator(std::istream& in, std::ostream& out, unsigned const scale, unsigned const maxWidth){
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
	out << "Bye\n";

}