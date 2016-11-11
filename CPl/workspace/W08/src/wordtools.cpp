#include "wordtools.h"

#include <string>
#include <set>
#include <vector>
#include <iterator>
#include <algorithm>
#include <cctype>

bool is_palindrome(const std::string input){

	std::vector<char> src{};
	std::copy_if(cbegin(input), cend(input), std::back_inserter(src), [](char c){
		return std::isalpha(c);
	});
	std::transform(cbegin(src), cend(src), begin(src), [](char c){
		return std::tolower(c);
	});


	std::vector<char> reversed{};
	std::copy(crbegin(src), crend(src), std::back_inserter(reversed));

	return reversed == src;
}

bool is_annagram(std::string a, std::string b){
	// reduce a to 'a-z' in lowercase
	std::vector<char> va{};
	std::copy_if(cbegin(a), cend(a), std::back_inserter(va), [](char c){
		return std::isalpha(c);
	});
	std::transform(cbegin(va), cend(va), begin(va), [](char c){
		return std::tolower(c);
	});

	// reduce b to 'a-z' in lowercase
	std::vector<char> vb{};
	std::copy_if(cbegin(b), cend(b), std::back_inserter(vb), [](char c){
		return std::isalpha(c);
	});
	std::transform(cbegin(vb), cend(vb), begin(vb), [](char c){
		return std::tolower(c);
	});

	// Sort a & b
    std::sort(begin(va), end(va));
	std::sort(begin(vb), end(vb));

	return va == vb;
}

std::set<std::string> generate_annagrams(std::string input){
	std::set<std::string> annagrams{};

    std::sort(input.begin(), input.end());
    do {
    	annagrams.insert(input);
    } while(std::next_permutation(input.begin(), input.end()));


	return annagrams;
}

