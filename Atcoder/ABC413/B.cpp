#include <cstdint>
#include <iostream>
#include <set>
#include <string>
#include <unordered_set>
#include <vector>

void solve() {

    int64_t n = 0LL;
    std::cin >> n;

    std::vector<std::string> s(n, "");
    for (int64_t i = 0; i < n; ++i) {
        std::cin >> s[i];
    }

    std::unordered_set<std::string> unique_strings;
    for (int64_t i = 0; i < n; ++i) {
        for (int64_t j = 0; j < n; ++j) {
            if (i != j)
                unique_strings.insert(s[i] + s[j]);
        }
    }

    std::cout << unique_strings.size() << std::endl;
}

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    solve();

    return 0;
}