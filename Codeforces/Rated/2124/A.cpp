#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <limits>
#include <vector>

void solve() {

    int64_t n = 0UL;
    std::cin >> n;
    std::vector<int64_t> a(n, 0);

    for (int64_t i = 0; i < n; ++i)
        std::cin >> a[i];

    std::vector<int64_t> b = a;
    std::sort(b.begin(), b.end());

    int64_t masked = 0LL;
    for (int64_t i = 0; i < n; ++i) {
        if (a[i] == b[i]) {
            a[i] = std::numeric_limits<int64_t>::min();
            ++masked;
        }
    }

    if (b.size() - masked == 0) {
        std::cout << "No" << std::endl;
        return;
    }
    std::cout << "Yes" << std::endl;
    std::cout << b.size() - masked << std::endl;
    for (int64_t i = 0; i < n; ++i) {
        if (a[i] != std::numeric_limits<int64_t>::min()) {
            std::cout << a[i] << " ";
        }
    }
    std::cout << std::endl;
}

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    size_t t = 0UL;
    std::cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}