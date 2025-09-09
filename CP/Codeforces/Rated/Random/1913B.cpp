#include <cstddef>
#include <iostream>
#include <string>

int main(int, char**) {

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    size_t t = 0UL;
    std::cin >> t;

    for (size_t i = 0; i < t; ++i) {

        std::string s = "";
        std::cin >> s;

        size_t zeroes = 0UL, ones = 0UL, num_deletions = 0UL;

        for (size_t j = 0; j < s.size(); ++j) {

            if (s[j] == '0')
                ++zeroes;
            else if (s[j] == '1')
                ++ones;
        }

        for (size_t j = 0; j < s.size(); ++j) {

            if (s[j] == '0' && ones > 0) {
                --ones;
                ++num_deletions;
            } else if (s[j] == '1' && zeroes > 0) {
                --zeroes;
                ++num_deletions;
            } else {
                break;
            }
        }

        std::cout << s.size() - num_deletions << std::endl;
    }

    return 0;
}