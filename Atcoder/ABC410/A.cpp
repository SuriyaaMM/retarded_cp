#include <cstddef>
#include <iostream>
#include <vector>

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    size_t n = 0UL, k = 0UL;
    std::cin >> n;
    std::vector<size_t> a(n);

    for (size_t i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    std::cin >> k;

    size_t ans = 0UL;
    for (size_t i = 0; i < n; ++i) {
        if (k <= a[i]) {
            ++ans;
        }
    }

    std::cout << ans << std::endl;

    return 0;
}