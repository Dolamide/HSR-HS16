#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

#include <sstream>

#include "sevensegment.h"
#include "calc.h"
#include "pocketcalculator.h"

void testSevenSegmentZeroDigit() {
	std::ostringstream out{};
	printLargeDigit(0, out);
	std::string expected = " - \n"
						   "| |\n"
						   "   \n"
			    		   "| |\n"
						   " - \n";
	ASSERT_EQUAL(expected, out.str());
}

void testSevenSegmentOneDigit() {
	std::ostringstream out{};
	printLargeDigit(1, out);
	std::string expected = "   \n"
						   "  |\n"
						   "   \n"
			    		   "  |\n"
						   "   \n";
	ASSERT_EQUAL(expected, out.str());
}

void testSevenSegmentTwoDigit() {
	std::ostringstream out{};
	printLargeDigit(2, out);
	std::string expected = " - \n"
						   "  |\n"
						   " - \n"
			    		   "|  \n"
						   " - \n";
	ASSERT_EQUAL(expected, out.str());
}


void testSevenSegmentThreeDigit() {
	std::ostringstream out{};
	printLargeDigit(3, out);
	std::string expected = " - \n"
						   "  |\n"
						   " - \n"
			    		   "  |\n"
						   " - \n";
	ASSERT_EQUAL(expected, out.str());
}

void testSevenSegmentFourDigit() {
	std::ostringstream out{};
	printLargeDigit(4, out);
	std::string expected = "   \n"
						   "| |\n"
						   " - \n"
			    		   "  |\n"
						   "   \n";
	ASSERT_EQUAL(expected, out.str());
}

void testSevenSegmentFiveDigit() {
	std::ostringstream out{};
	printLargeDigit(5, out);
	std::string expected = " - \n"
						   "|  \n"
						   " - \n"
			    		   "  |\n"
						   " - \n";
	ASSERT_EQUAL(expected, out.str());
}

void testSevenSegmentSixDigit() {
	std::ostringstream out{};
	printLargeDigit(6, out);
	std::string expected = " - \n"
						   "|  \n"
						   " - \n"
			    		   "| |\n"
						   " - \n";
	ASSERT_EQUAL(expected, out.str());
}

void testSevenSegmentSevenDigit() {
	std::ostringstream out{};
	printLargeDigit(7, out);
	std::string expected = " - \n"
						   "  |\n"
						   "   \n"
			    		   "  |\n"
						   "   \n";
	ASSERT_EQUAL(expected, out.str());
}

void testSevenSegmentEightDigit() {
	std::ostringstream out{};
	printLargeDigit(8, out);
	std::string expected = " - \n"
						   "| |\n"
						   " - \n"
			    		   "| |\n"
						   " - \n";
	ASSERT_EQUAL(expected, out.str());
}

void testSevenSegmentNineDigit() {
	std::ostringstream out{};
	printLargeDigit(9, out);
	std::string expected = " - \n"
						   "| |\n"
						   " - \n"
			    		   "  |\n"
						   " - \n";
	ASSERT_EQUAL(expected, out.str());
}

void testSevenSegment134Number() {
	std::ostringstream out{};
	printLargeNumber(1234, out);
	std::string expected = "    -  -    \n"
						   "  |  |  || |\n"
						   "    -  -  - \n"
					 	   "  ||    |  |\n"
						   "    -  -    \n";
	ASSERT_EQUAL(expected, out.str());
}

void testSevenSegment42Number() {
	std::ostringstream out{};
	printLargeNumber(42, out);
	std::string expected = "    - \n"
						   "| |  |\n"
						   " -  - \n"
					 	   "  ||  \n"
						   "    - \n";
	ASSERT_EQUAL(expected, out.str());
}

void testSevenSegmentScaled42Number() {
	std::ostringstream out{};
	printLargeNumber(42, out, 3);
	std::string expected = "    - \n"
						   "| |  |\n"
						   "| |  |\n"
						   "| |  |\n"
						   " -  - \n"
					 	   "  ||  \n"
						   "  ||  \n"
						   "  ||  \n"
						   "    - \n";
	ASSERT_EQUAL(expected, out.str());
}
void testSevenSegmentError() {
	std::ostringstream out{};
	printError(out, 1);
	std::string expected = " -             \n"
   						   "|              \n"
						   " -  -  -  -  - \n"
						   "|  |  |  | ||  \n"
						   " -        -    \n";
	ASSERT_EQUAL(expected, out.str());
}
void testSevenSegmentScaledError() {
	std::ostringstream out{};
	printError(out, 3);
	std::string expected = " -             \n"
						   "|              \n"
						   "|              \n"
						   "|              \n"
						   " -  -  -  -  - \n"
						   "|  |  |  | ||  \n"
						   "|  |  |  | ||  \n"
						   "|  |  |  | ||  \n"
						   " -        -    \n";
	ASSERT_EQUAL(expected, out.str());
}

void testSevenSegmentOverflow() {
	std::ostringstream out{};
	printLargeNumber(144, out, 1, 2);
	std::string expected = " -             \n"
   						   "|              \n"
						   " -  -  -  -  - \n"
						   "|  |  |  | ||  \n"
						   " -        -    \n";
	ASSERT_EQUAL(expected, out.str());
}

void testOnePlusFourStream(){
	  std::istringstream iss {"1+4"};
	  bool error{false};
	  auto result = calc(iss, error);
	  ASSERT_EQUAL(5, result);
	  ASSERT_EQUAL(error, false);
}
void testOnePlusFourStreamWithSpaces(){
	  std::istringstream iss {"1        +4"};
	  bool error{false};
	  auto result = calc(iss, error);
	  ASSERT_EQUAL(5, result);
	  ASSERT_EQUAL(error, false);
}

void testIncompleteStream(){
	  std::istringstream iss {"1         +"};
	  bool error{false};
	  auto result = calc(iss, error);
	  ASSERT_EQUAL(-1, result);
	  ASSERT_EQUAL(error, true);
}

void testOnePlusOne() {
	bool error{false};
	auto result = calc(1, 1, '+', error);
	ASSERT_EQUAL(2, result);
    ASSERT_EQUAL(error, false);
}

void testFourMinusOne() {
	bool error{false};
	auto result = calc(4, 1, '-', error);
	ASSERT_EQUAL(3, result);
	ASSERT_EQUAL(error, false);
}

void testOneMinusFour() {
	bool error{false};
	auto result = calc(1, 4, '-', error);
	ASSERT_EQUAL(-3, result);
	ASSERT_EQUAL(error, false);
}

void testSeventeenModTwo() {
	bool error{false};
	auto result = calc(17, 2, '%', error);
	ASSERT_EQUAL(1, result);
	ASSERT_EQUAL(error, false);
}

void testSeventeenTimesFifteen() {
	bool error{false};
	auto result = calc(17, 15, '*', error);
	ASSERT_EQUAL(255, result);
	ASSERT_EQUAL(error, false);
}

void testSeventeenDividedByFifteen() {
	bool error{false};
	auto result = calc(17, 15, '/', error);
	ASSERT_EQUAL(1, result);
	ASSERT_EQUAL(error, false);
}

void testInvalidOperator(){
	bool error{false};
	auto result = calc(17, 15, '&', error);
	ASSERT_EQUAL(-1, result);
	ASSERT_EQUAL(error, true);
}

void testDivisionByZero(){
	bool error{false};
	auto result = calc(42, 0, '/', error);
	ASSERT_EQUAL(-1, result);
	ASSERT_EQUAL(error, true);
}

void testModuleZero(){
	bool error{false};
	auto result = calc(42, 0, '%', error);
	ASSERT_EQUAL(-1, result);
	ASSERT_EQUAL(error, true);
}


void testPocketCalculatorEmpty(){
	std::ostringstream out{};
	std::istringstream in{};
	pocketcalculator(in, out, 1, 1);
	std::string expected = "Bye\n";
	ASSERT_EQUAL(expected, out.str());
}

void testPocketCalculatorScenario(){
	std::ostringstream out{};
	std::istringstream in{"4&4\n4+4\n"};
	pocketcalculator(in, out, 1, 1);
	std::string expected = " -             \n"
   						   "|              \n"
						   " -  -  -  -  - \n"
						   "|  |  |  | ||  \n"
						   " -        -    \n"
						   " - \n"
						   "| |\n"
						   " - \n"
						   "| |\n"
						   " - \n"
						   "Bye\n";
	ASSERT_EQUAL(expected, out.str());
}

bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };


	s.push_back(CUTE(testSevenSegmentZeroDigit));
	s.push_back(CUTE(testSevenSegmentOneDigit));
	s.push_back(CUTE(testSevenSegmentTwoDigit));
	s.push_back(CUTE(testSevenSegmentThreeDigit));
	s.push_back(CUTE(testSevenSegmentFourDigit));
	s.push_back(CUTE(testSevenSegmentFiveDigit));
	s.push_back(CUTE(testSevenSegmentSixDigit));
	s.push_back(CUTE(testSevenSegmentSevenDigit));
	s.push_back(CUTE(testSevenSegmentNineDigit));
	s.push_back(CUTE(testSevenSegmentEightDigit));
	s.push_back(CUTE(testSevenSegment134Number));
	s.push_back(CUTE(testSevenSegment42Number));
	s.push_back(CUTE(testSevenSegmentScaled42Number));
	s.push_back(CUTE(testSevenSegmentError));
	s.push_back(CUTE(testSevenSegmentScaledError));

	s.push_back(CUTE(testFourMinusOne));
	s.push_back(CUTE(testOneMinusFour));
	s.push_back(CUTE(testSeventeenModTwo));
	s.push_back(CUTE(testOnePlusOne));
	s.push_back(CUTE(testOnePlusFourStreamWithSpaces));
	s.push_back(CUTE(testOnePlusFourStream));
	s.push_back(CUTE(testSeventeenTimesFifteen));
	s.push_back(CUTE(testSeventeenDividedByFifteen));
	s.push_back(CUTE(testInvalidOperator));
	s.push_back(CUTE(testIncompleteStream));
	s.push_back(CUTE(testModuleZero));
	s.push_back(CUTE(testDivisionByZero));
	s.push_back(CUTE(testSevenSegmentOverflow));
	s.push_back(CUTE(testPocketCalculatorEmpty));
	s.push_back(CUTE(testPocketCalculatorScenario));


	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner { cute::makeRunner(lis, argc, argv) };
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}