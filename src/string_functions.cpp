#include "string_functions.h"
#include <algorithm>

std::string reverseString(const std::string& input) {
    std::string reversed = input;
    std::reverse(reversed.begin(), reversed.end());
    return reversed;
}

std::string concatenateStrings(const std::string& str1, const std::string& str2) {
    return str1 + str2;
}