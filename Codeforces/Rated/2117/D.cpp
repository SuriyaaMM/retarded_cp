#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>

void solve() {

    size_t n = 0UL;
    std::cin >> n;

    std::vector<int64_t> a(n);

    for (size_t i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    if ((2 * a[0] - a[1]) % (n + 1) != 0) {
        std::cout << "No";
        return;
    }

    int64_t y = (2L * a[0] - a[1]) / (n + 1UL);
    int64_t x = a[1] - a[0] + y;

    if (x < 0 || y < 0) {
        std::cout << "No" << std::endl;
        return;
    }

    for (size_t i = 0; i < n; ++i) {
        a[i] -= ((i + 1) * x);
        a[i] -= ((n - i) * y);
    }

    for (size_t i = 0; i < n; ++i) {
        if (a[i] != 0) {
            std::cout << "No" << std::endl;
            return;
        }
    }

    std::cout << "Yes" << std::endl;
}

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    size_t t = 0UL;
    std::cin >> t;

    while (t--)
        solve();

    return 0;
}