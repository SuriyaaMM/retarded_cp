#include <cstdint>
#include <iostream>

void solve() {

    int64_t n = 0, l = 0, r = 0, xi = 0, xj = 0;
    std::cin >> n >> l >> r;

    int64_t answer = 0;
    for (int i = 0; i < n; ++i) {
        std::cin >> xi >> xj;
        if (xi <= l && xj >= r) {
            ++answer;
        }
    }

    std::cout << answer << std::endl;
}

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    solve();
    return 0;
}