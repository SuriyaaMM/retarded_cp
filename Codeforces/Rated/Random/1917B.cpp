#include <cstddef>
#include <iostream>
#include <string>
#include <unordered_set>

size_t solve(std::string& substring, std::unordered_set<std::string>& unique) {
    // if we have that substring, then return 0
    if (unique.find(substring) != unique.end()) {
        return 0;
    }
    // return 0 for 1 sized substring
    if (substring.size() == 2) {
        return 2;
    }
    if (substring.size() == 1) {
        return 1;
    }
    if (substring.size() < 1) {
        return 0;
    }

    unique.insert(substring);
    std::string path1_substring = substring.substr(1);
    std::string path2_substring = substring.substr(0, 1) + substring.substr(2);

    size_t path1 = solve(path1_substring, unique);
    size_t path2 = solve(path2_substring, unique);

    return path1 + path1;
}

int main(int, char**) {

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    size_t t = 0UL;
    std::cin >> t;

    while (t--) {

        size_t n = 0UL;
        std::cin >> n;
        std::string a = "";
        std::cin >> a;

        std::unordered_set<std::string> unique;
        std::cout << solve(a, unique) << std::endl;
    }

    return 0;
}