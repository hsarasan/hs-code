#include <iostream>

int main() {
#if defined(__GNUC__) && !defined(__clang__)
#if __GNUC__ >= 11
	constexpr const char* highest_standard = "C++23";
#elif __GNUC__ >= 10
	constexpr const char* highest_standard = "C++20";
#elif __GNUC__ >= 8
	constexpr const char* highest_standard = "C++17";
#elif __GNUC__ >= 5 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 9)
	constexpr const char* highest_standard = "C++14";
#elif __GNUC__ >= 4
	constexpr const char* highest_standard = "C++11";
#else
	constexpr const char* highest_standard = "C++98/03";
#endif

	std::cout << "GCC " << __GNUC__ << '.' << __GNUC_MINOR__
			  << " supports up to " << highest_standard << '\n';
#else
	std::cout << "This program currently detects GCC only.\n";
#endif
}
 