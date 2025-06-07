#include <algorithm>
#include <cstddef>
#include <iostream>
#include <map>
#include <vector>

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    size_t n = 0UL;
    std::cin >> n;

    std::vector<size_t> a(n);

    for (size_t i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    std::sort(a.begin(), a.end());

    size_t max_x_candidate = 0;
    if (n > 0) {
        max_x_candidate = std::min(n, a[n - 1]);
    }

    for (size_t x_candidate = max_x_candidate;; --x_candidate) {

        auto it = std::lower_bound(a.begin(), a.end(), x_candidate);
        size_t count_greater_equal_x = std::distance(it, a.end());

        if (count_greater_equal_x >= x_candidate) {
            std::cout << x_candidate << std::endl;
            return 0;
        }
        if (x_candidate == 0) {
            break;
        }
    }

    return 0;
}