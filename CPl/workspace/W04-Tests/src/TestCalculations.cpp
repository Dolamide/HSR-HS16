#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

#include "calculations.h"
#include "counting.h"
#include "sum.h"
#include "table.h"


// Tests for A2

void testCountNonWhiteSpace() {
	std::istringstream in {"The world is beautiful"};
	ASSERT_EQUAL(19, chcount(in));
}

void testCountAllCharacters() {
	std::istringstream in {"The world is beautiful"};
	ASSERT_EQUAL(22, chacount(in));
}

void testCountWords() {
	std::istringstream in {"The world is beautiful"};
	ASSERT_EQUAL(4, wcount(in));
}

void testACount() {
	std::istringstream in {"all apes are awesome!"};
	ASSERT_EQUAL(4, acount(in));
}
void testLineCount() {
	std::istringstream in {"all apes\n are \n\n\n awesome!\n"};
	ASSERT_EQUAL(5, lcount(in));
}

// Self study
void testSumi() {
	std::istringstream in {"1 22 9412"};
	ASSERT_EQUAL(9435, sumi(in));
}

void testSumd() {
	std::istringstream in {"1.12 22.73 9412.1122"};
	ASSERT_EQUAL_DELTA(9435.9622, sumd(in), 0.0005);
}

void testTable() {
	std::ostringstream os {};
	multab(os);
	ASSERT_EQUAL("NEVER", os.str());
}

bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };


	s.push_back(CUTE(testCountNonWhiteSpace));
	s.push_back(CUTE(testCountAllCharacters));
	s.push_back(CUTE(testCountWords));
	s.push_back(CUTE(testACount));
	s.push_back(CUTE(testLineCount));
	s.push_back(CUTE(testScaled42Number));
	s.push_back(CUTE(testSumi));
	s.push_back(CUTE(testSumd));
	s.push_back(CUTE(testTable));

	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner { cute::makeRunner(lis, argc, argv) };
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
