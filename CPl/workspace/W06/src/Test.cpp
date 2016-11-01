#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include "Word.h"
#include "Button.h"
#include <stdexcept>
#include <set>


void testSimpleWord(){
	std::istringstream in {"Hello World"};
	testat::Word w{};
	std::ostringstream out{};
	in >> w;
	out << w;
	ASSERT_EQUAL("Hello", out.str());
}

void testEmptyWordConstructor(){
	ASSERT_THROWS(testat::Word{""}, std::out_of_range);
}
void testInvalidWordConstructor(){
	ASSERT_THROWS(testat::Word{"Hello World"}, std::out_of_range);
}

void testValidWordConstructor(){
	testat::Word w{"HelloWorld"};
	std::ostringstream out{};
	out << w;
	ASSERT_EQUAL("HelloWorld", out.str());
}

void testEmptyWord(){
	std::istringstream in {""};
	testat::Word w{};
	std::ostringstream out{};
	in >> w;
	out << w;
	ASSERT_EQUAL("", out.str());
}

void testBrokenInStream(){
	std::istringstream in {"..."};
	in.fail();
	testat::Word w{};
	std::ostringstream out{};
	in >> w;
	out << w;
	ASSERT_EQUAL("", out.str());
}

void testWordComplexSeuence() {

	std::istringstream in {R"(compl33tely ~ weird !!??!! 4matted in_put)"};
	std::ostringstream out{};
	testat::Word w{};
	in >> w;
	out << w;
	ASSERT_EQUAL("compl", out.str());
	in >> w;
	out.str(""); // reuse out
	out << w;
	ASSERT_EQUAL("tely", out.str());
	in >> w;
	out.str(""); // reuse out
	out << w;
	ASSERT_EQUAL("weird", out.str());
	in >> w;
	out.str(""); // reuse out
	out << w;
	ASSERT_EQUAL("matted", out.str());
	in >> w;
	out.str(""); // reuse out
	out << w;
	ASSERT_EQUAL("in", out.str());
	in >> w;
	out.str(""); // reuse out
	out << w;
	ASSERT_EQUAL("put", out.str());
	in >> w;
	out.str(""); // reuse out
	out << w;
	ASSERT_EQUAL("put", out.str());
}

void testWordComparisonEquals(){
	testat::Word w1{"aaa"};
	testat::Word w2{"aaa"};
	ASSERT(w1 == w2);
	ASSERT(w1 >= w2);
	ASSERT(w1 <= w2);
}


void testWordComparisonUnequal(){
	testat::Word w1{"aaa"};
	testat::Word w2{"bbb"};
	ASSERT(w1 != w2);
}

void testWordComparisonLowerGreater(){
	testat::Word w1{"aaa"};
	testat::Word w2{"bbb"};
	ASSERT(w1 < w2);
	ASSERT(w2 > w1);
	ASSERT(w1 <= w2);
	ASSERT(w2 >= w1);
}

void testWList(){
	std::stringstream in {"These are a lot of words"};
	std::set<testat::Word> wlist{testat::wlist(in)};
	ASSERT_EQUAL(6, wlist.size());

	auto it = wlist.begin();
	std::ostringstream out{};
	testat::Word w = *it;
	out << w;
	ASSERT_EQUAL("a", out.str());

	w = *(++it);
	out.str("");
	out << w;
	ASSERT_EQUAL("are", out.str());

	// no further test, since this would only verify the behaviour uf std::set
}


void testButton(){
	w6f::Button btn {};
	ASSERT(!btn.isBlinking());
	ASSERT(!btn.isOn());
	btn.pressButton();
	ASSERT(!btn.isBlinking());
	ASSERT(btn.isOn());
	btn.pressButton();
	ASSERT(btn.isBlinking());
	ASSERT(btn.isOn());
	btn.pressButton();
	ASSERT(!btn.isBlinking());
	ASSERT(!
			btn.isOn());
}

bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	s.push_back(CUTE(testWordComplexSeuence));
	s.push_back(CUTE(testSimpleWord));
	s.push_back(CUTE(testEmptyWord));
	s.push_back(CUTE(testBrokenInStream));
	s.push_back(CUTE(testValidWordConstructor));
	s.push_back(CUTE(testEmptyWordConstructor));
	s.push_back(CUTE(testInvalidWordConstructor));
	s.push_back(CUTE(testWordComparisonEquals));
	s.push_back(CUTE(testWordComparisonUnequal));
	s.push_back(CUTE(testWordComparisonLowerGreater));
	s.push_back(CUTE(testWList));
	s.push_back(CUTE(testButton));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner { cute::makeRunner(lis, argc, argv) };
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
