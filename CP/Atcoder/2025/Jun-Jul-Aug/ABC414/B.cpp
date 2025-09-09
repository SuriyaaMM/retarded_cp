#include <cstdint>
#include <iostream>
#include <string>

void solve() {

    int64_t n = 0;
    std::cin >> n;
    char ci = 0;
    int64_t li = 0;
    int64_t length = 0;
    std::string answer = "";
    bool too_long = false;
    for (int64_t i = 0; i < n; ++i) {
        std::cin >> ci >> li;

        if (length + li > 100) {
            too_long = true;
        }

        if (!too_long) {
            int64_t safe_len = std::min(int64_t(100 - length), li);
            answer.append(safe_len, ci);
            length += li;
        } else {
            length += li;
        }
    }
    if (too_long) {
        std::cout << "Too Long" << std::endl;
    } else {
        std::cout << answer << std::endl;
    }
}

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    solve();
    return 0;
}