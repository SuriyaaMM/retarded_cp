#include <iostream>
#include <vector>
#include <string>

int main() {
    size_t t;
    std::cin >> t;

    std::vector<size_t> length;
    std::vector<std::string> strings;

    for (size_t i = 0; i < t; ++i) {
        size_t n;
        std::cin >> n;

        std::string s;
        std::cin >> s;

        length.emplace_back(n);
        strings.emplace_back(s);
    }

    for (size_t i = 0; i < strings.size(); ++i) {
        const std::string& s = strings[i];
        size_t l = 0, r = s.size() - 1;

        while (l < r && s[l] != s[r]) {
            ++l;
            --r;
        }

        std::cout << (r - l + 1) << "\n";
    }

    return 0;
}
