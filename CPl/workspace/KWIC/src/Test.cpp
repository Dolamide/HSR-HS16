#include "kwic.h"
#include "Word.h"

#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include <set>

void testKWICExerciseExample() {
	std::istringstream in{"this is a test\nthis is another test"};
	std::ostringstream out{};
	testat::kwic(in, out);
	std::string expected = "a test this is \nanother test this is \nis a test this \nis another test this \ntest this is a \ntest this is another \nthis is a test \nthis is another test \n";
	ASSERT_EQUAL(expected, out.str());
}

void demoFoo(){
	std::vector<int> myInt(12);
	ASSERT_EQUAL(0, myInt.size());
}

bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	//TODO add your test here
	s.push_back(CUTE(testKWICExerciseExample));
	s.push_back(CUTE(demoFoo));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner { cute::makeRunner(lis, argc, argv) };
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
