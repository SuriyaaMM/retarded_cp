#include <cctype>
#include <cstddef>
#include <iostream>
#include <string>
#include <unordered_map>

void solve() {
    std::string s = "", t = "";
    std::cin >> s >> t;

    std::unordered_map<char, bool> is_in_t;
    for (size_t i = 0; i < t.size(); ++i) {
        is_in_t[t[i]] = true;
    }

    for (size_t i = 1; i < s.size(); ++i) {
        if (std::isupper(s[i])) {
            if (!is_in_t.count(s[i - 1])) {
                std::cout << "No" << std::endl;
                return;
            }
        }
    }

    std::cout << "Yes" << std::endl;
}

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    solve();

    return 0;
}