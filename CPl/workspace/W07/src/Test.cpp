#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

#include "Field5.h"

void testSimpleField5SubstractionWithSelf() {
	Field5 a{12};
	Field5 result = a-a;
	ASSERT_EQUAL(0, result.value());
}

void testSimpleField5Substraction3Minus4() {
	Field5 f3{3};
	Field5 f4{4};
	Field5 result = f3-f4;
	ASSERT_EQUAL(4, result.value());
}


void testSimpleField5MutationSubstraction3Minus4() {
	Field5 a{3};
	Field5 b{4};
	a -= b;
	ASSERT_EQUAL(4, a.value());
}

void testSimpleField5Inverse() {
	Field5 a{3};
	Field5 b{3};

	Field5 result = a + (a);
	ASSERT_EQUAL(4, result .value());
}


void testSimpleField5Addition4Plus4() {
	Field5 a{4};
	Field5 b{4};
	Field5 result = a+b;
	ASSERT_EQUAL(3, result.value());
}

bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	//TODO add your test here
	s.push_back(CUTE(testSimpleField5SubstractionWithSelf));
	s.push_back(CUTE(testSimpleField5Substraction3Minus4));
	s.push_back(CUTE(testSimpleField5Addition4Plus4));
	s.push_back(CUTE(testSimpleField5MutationSubstraction3Minus4));
	s.push_back(CUTE(testSimpleField5Inverse));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner { cute::makeRunner(lis, argc, argv) };
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
