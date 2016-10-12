#include "table.h"
#include <algorithm>
#include <iterator>
#include <numeric>
#include <vector>
#include <string>

void multab(std::ostream &out){
	// Create & fill vector with values from 1 to 20
    std::vector<int> v(20);
	iota(begin(v), end(v), 0);
	using ot = std::ostream_iterator<int>;


	for_each(begin(v),end(v), [&out, &v](int line){
		int c = 0;
		transform(begin(v),end(v), begin(v), [&out, line, &c](int x){
			return x+(++c);
		});
		copy(begin(v),end(v), ot{out, "\t "});
		out << '\n';

	});

}