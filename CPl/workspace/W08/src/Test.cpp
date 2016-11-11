
#include "wordtools.h"
#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

#include <fstream>
#include <set>
#include <string>

void testInvalidPalindrome() {
	ASSERT(!is_palindrome("test"));
}

void testSimplePalindrome() {
	ASSERT(is_palindrome("otto"));
}

void testPalindromeWithSpacesAndSymbols() {
	ASSERT(is_palindrome("Are we not pure? “No, sir!” Panama’s moody Noriega brags. “It is garbage!” Irony dooms a man—a prisoner up to new era."));
}

void testFindAllFromDict(){

	std::ifstream in("/usr/share/dict/words");
    std::string word;
	int counter{0};
    while(in >> word) {
    	if(is_palindrome(word)){
    		counter++;
    	}
	}
	ASSERT_EQUAL(199, counter);
}

void testFindSimpleAnnagrams(){
	std::string input{"Lord"};
	std::set<std::string> expected{"Ldor", "Ldro", "Lodr", "Lord", "Lrdo", "Lrod", "dLor",
								   "dLro", "doLr", "dorL", "drLo", "droL", "oLdr", "oLrd",
								   "odLr", "odrL", "orLd", "ordL", "rLdo", "rLod", "rdLo",
								   "rdoL", "roLd", "rodL"};
	std::set<std::string> annagrams = generate_annagrams(input);
	ASSERT_EQUAL(expected, annagrams);
}

void testIsAnnagram(){
	std::string a{"Vacation time"};
	std::string b{"I am not active"};
	ASSERT(is_annagram(a, b));
}

void testIsNotAnnagram(){
	std::string a{"Foo"};
	std::string b{"Baa"};
	ASSERT(!is_annagram(a, b));
}


bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	//TODO add your test here
	s.push_back(CUTE(testInvalidPalindrome));
	s.push_back(CUTE(testSimplePalindrome));
	s.push_back(CUTE(testPalindromeWithSpacesAndSymbols));
	s.push_back(CUTE(testFindAllFromDict));
	s.push_back(CUTE(testFindSimpleAnnagrams));
	s.push_back(CUTE(testIsAnnagram));
	s.push_back(CUTE(testIsNotAnnagram));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner { cute::makeRunner(lis, argc, argv) };
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
