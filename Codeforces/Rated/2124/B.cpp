#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>

void solve() {

    int64_t n = 0;
    std::cin >> n;

    std::vector<int64_t> a(n, 0);
    for (int64_t i = 0; i < n; ++i)
        std::cin >> a[i];

    int64_t sum = std::min(a[1], a[0]) + a[0];

    std::cout << sum << std::endl;
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