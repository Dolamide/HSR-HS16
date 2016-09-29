#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include "calculator.h"

void test_one_plus_4_stream(){
	  std::istringstream iss {"1+4"};
	  auto result = calc(iss);
	  ASSERT_EQUAL(5, result);
}
void test_one_plus_4_stream_with_spaces(){
	  std::istringstream iss {"1        +4"};
	  auto result = calc(iss);
	  ASSERT_EQUAL(5, result);
}

void test_incomplete_stream(){
	  std::istringstream iss {"1         +"};
	  auto result = calc(iss);
	  ASSERT_EQUAL(-1, result);
}

void test_one_plus_one() {
	auto result = calc(1, 1, '+');
	ASSERT_EQUAL(2, result);
}

void test_four_minus_one() {
	auto result = calc(4, 1, '-');
	ASSERT_EQUAL(3, result);
}

void test_one_minus_four() {
	auto result = calc(1, 4, '-');
	ASSERT_EQUAL(-3, result);
}

void test_seventeen_mod_two() {
	auto result = calc(17, 2, '%');
	ASSERT_EQUAL(1, result);
}

void test_seventeen_times_fifteen() {
	auto result = calc(17, 15, '*');
	ASSERT_EQUAL(255, result);
}

void test_seventeen_divided_by_fifteen() {
	auto result = calc(17, 15, '/');
	ASSERT_EQUAL(1, result);
}

void test_invalid_operator(){
	auto result = calc(17, 15, '&');
	ASSERT_EQUAL(-1, result);
}

void test_division_by_zero(){
	auto result = calc(42, 0, '/');
	ASSERT_EQUAL(-1, result);
}

void test_module_zero(){
	auto result = calc(42, 0, '%');
	ASSERT_EQUAL(-1, result);
}

bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };

	s.push_back(CUTE(test_four_minus_one));
	s.push_back(CUTE(test_one_minus_four));
	s.push_back(CUTE(test_seventeen_mod_two));
	s.push_back(CUTE(test_one_plus_one));
	s.push_back(CUTE(test_one_plus_4_stream_with_spaces));
	s.push_back(CUTE(test_one_plus_4_stream));
	s.push_back(CUTE(test_seventeen_times_fifteen));
	s.push_back(CUTE(test_seventeen_divided_by_fifteen));
	s.push_back(CUTE(test_invalid_operator));
	s.push_back(CUTE(test_incomplete_stream));
	s.push_back(CUTE(test_module_zero));
	s.push_back(CUTE(test_division_by_zero));

	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner { cute::makeRunner(lis, argc, argv) };
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
