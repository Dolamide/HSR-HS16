#ifndef WORDTOOLS_H_
#define WORDTOOLS_H_

#include <string>
#include <set>

bool is_palindrome(std::string input);
std::set<std::string> generate_annagrams(std::string input);
bool is_annagram(std::string a, std::string b);

#endif