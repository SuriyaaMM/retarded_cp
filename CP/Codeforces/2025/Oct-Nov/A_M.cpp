#include <cstdint>
#include <iostream>

void solve() {
    int64_t n = 0LL;
    std::cin >> n;

    int64_t mid = (n - 1) / 2;
    int64_t vrows = (n + 1) / 2;
    int64_t vcols = 1LL;

    for (int64_t r = 0; r < n; ++r) {
        for (int64_t c = 0; c < n; ++c) {
            if (c == 0 || c == n - 1) {
                std::cout << '#';
                continue;
            }
            if (r == vrows - 1 && c == mid) {
                std::cout << '#';
                continue;
            }
            if (r >= 1 && r < vrows && (vcols == c || vcols == n - c - 1)) {
                std::cout << '#';
                if (vcols == n - c - 1) vcols++;
                continue;
            }
            std::cout << '.';
        }
        std::cout << "\n";
    }
}

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#define MT
#ifdef MT
    int64_t tt = 0L;
    std::cin >> tt;
    while (tt--) {
        solve();
    }
#else
    solve();
#endif

    return 0;
}