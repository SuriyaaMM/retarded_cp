#include <cstddef>
#include <cstdint>
#include <iostream>

void solve() {

    int64_t n = 0LL, m = 0LL, ai = 0LL;
    std::cin >> n >> m;
    int64_t sum = 0LL;
    for (int64_t i = 0; i < n; ++i) {
        std::cin >> ai;
        sum += ai;
    }

    if (sum <= m) {
        std::cout << "Yes" << std::endl;
    } else {
        std::cout << "No" << std::endl;
    }
}

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    solve();
    return 0;
}