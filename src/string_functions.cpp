#include "string_functions.h"
#include <algorithm>
#include <cctype>

std::string reverseString(const std::string& input) {
    std::string reversed = input;
    std::reverse(reversed.begin(), reversed.end());
    return reversed;
}

std::string concatenateStrings(const std::string& str1, const std::string& str2) {
    return str1 + str2;
}

std::string toUpperCase(const std::string& input) {
    std::string uppercased = input;
    std::transform(uppercased.begin(), uppercased.end(), uppercased.begin(), ::toupper);
    return uppercased;
}

std::string toLowerCase(const std::string& input) {
    std::string lowercased = input;
    std::transform(lowercased.begin(), lowercased.end(), lowercased.begin(), ::tolower);
    return lowercased;
}
