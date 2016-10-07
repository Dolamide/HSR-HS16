#include "sum.h"

#include <iterator>
#include <iostream>
#include <algorithm>

int sumi(std::istream &in){
	using it =std::istream_iterator<int>;
	int sum = 0;
	for_each(it{in}, it{}, [&sum](auto item){
		sum += item;
	});
 	return sum;
}

double sumd(std::istream &in){
	using it =std::istream_iterator<double>;
	double sum = 0;
	for_each(it{in}, it{}, [&sum](auto item){
		sum += item;
	});
 	return sum;

}

