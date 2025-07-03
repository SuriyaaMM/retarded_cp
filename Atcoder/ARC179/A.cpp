// https://atcoder.jp/contests/arc179/tasks/arc179_a

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <iostream>
#include <vector>

void solve() {
    size_t n = 0UL;
    int64_t k = 0UL;
    std::cin >> n >> k;

    // 1-based indexing
    std::vector<int64_t> a(n + 1);
    int64_t sigma_a = 0LL;
    for (size_t i = 1; i < n + 1; ++i) {
        std::cin >> a[i];
        sigma_a += a[i];
    }

    if (k >= 1) {
        std::sort(a.begin() + 1, a.end());
        std::cout << "Yes" << "\n";
        for (auto it = a.begin() + 1; it != a.end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << "\n";
    } else {
        if (sigma_a >= k) {
            std::sort(a.begin() + 1, a.end(), std::greater<>());
            std::cout << "Yes" << "\n";
            for (auto it = a.begin() + 1; it != a.end(); ++it) {
                std::cout << *it << " ";
            }
            std::cout << "\n";
        } else {
            std::cout << "No" << "\n";
        }
    }
}

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    solve();

    return 0;
}