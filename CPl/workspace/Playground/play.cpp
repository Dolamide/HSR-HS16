#include <iostream>
#include <sstream>

int main(int argc, char **argv) {
    char c1, c2, c3;
	std::istringstream("a b c") >> std::noskipws >> c1 >> c2 >> c3;
	std::cout << "noskipws behavior: c1 = " << c1 << " c2 = " << c2 << " c3 = " << c3 << '\n';
	std::istringstream("a b c") >> c1 >> c2 >> c3;
	std::cout << "sticky behavior?: c1 = " << c1 << " c2 = " << c2 << " c3 = " << c3 << '\n';
}
