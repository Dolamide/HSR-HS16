#include "MyMin.h"
#include <string>
#include <iostream>

int main(int argc, char **argv) {
    using MyMin::min;
    const int i{88};
    min(i, 42); // min<int>()

    const double pi{3.1415};
    const double e{2.7182};
    min(pi, e); // min<double>()
//    min(2, pi); // Compile error!

    std::string s1{"Hello"};
    std::string s2{"Hello World"};
    std::min(s1, s2); // Compileerror: min ist mehrdeutig
    MyMin::min(s1, s2);  // MyMin::min<string>()
    std::cout << min("Pete","Toni"); // Result: "Toni" (**)
    std::cout << '\n';
    std::cout << min<std::string>("Pete", "Toni"); //Result: "Pete"

}
