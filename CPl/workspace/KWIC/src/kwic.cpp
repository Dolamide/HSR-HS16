#include "kwic.h"

#include <istream>
#include <string>
#include <iterator>
#include <vector>
#include <set>
#include <sstream>
#include <algorithm>

namespace testat{

void kwic(std::istream & in, std::ostream & out){
	std::set<std::vector<Word>> result{};
	const Word emptyWord{};

	while(in){
		std::vector<Word> wordLine;

		std::string lineString{};
		getline(in, lineString);
		std::stringstream lineStream{lineString};

		while(lineStream){
			Word w{};
			lineStream >> w;
			if(w != emptyWord){
				wordLine.push_back(w);
			}
		}

		if(wordLine.size() > 0){
			result.insert(wordLine);

			std::vector<Word> rotatedLine{};
			std::rotate_copy(wordLine.cbegin(), wordLine.cbegin() + 1, wordLine.cend(), std::back_inserter(rotatedLine));
			while(rotatedLine != wordLine){
				result.insert(rotatedLine);
			    std::rotate(rotatedLine.begin(), rotatedLine.begin() + 1, rotatedLine.end());
			}
		}
	}


	for(std::vector<Word> line : result){
		for(auto word: line){
			out << word << ' ';
		}
		out << '\n';
	}
}
}
