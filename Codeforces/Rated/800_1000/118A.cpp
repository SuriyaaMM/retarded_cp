// https://codeforces.com/problemset/problem/118/A

#include <algorithm>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::string s = "", processed = "";
    // y is also a vowel according to the problem
    std::vector<char> vowels = {'a', 'e', 'i', 'o', 'u', 'y'};

    std::cin >> s;

    for (size_t i = 0; i < s.size(); ++i) {

        char lower = std::tolower(s[i]);

        // if it is a vowel, we remove it
        if (std::find(vowels.begin(), vowels.end(), lower) != vowels.end()) {
            continue;
        }
        // if it is a consonant,
        else {
            processed.push_back('.');
            processed.push_back(lower);
        }
    }

    std::cout << processed << std::endl;

    return 0;
}