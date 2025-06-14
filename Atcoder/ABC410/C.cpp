#include <cstddef>
#include <iostream>
#include <vector>

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    size_t n = 0UL, q = 0UL;
    std::cin >> n >> q;

    std::vector<size_t> a(n, 0);
    for (size_t i = 0; i < n; ++i) {
        a[i] = i + 1;
    }

    size_t begin = 0UL;
    for (size_t i = 0; i < q; ++i) {
        size_t type = 0UL, p = 0UL;
        std::cin >> type;

        if (type == 1) {
            size_t x = 0UL;
            std::cin >> p >> x;

            size_t actual_index = (begin + (p - 1)) % n;
            a[actual_index] = x;

        } else if (type == 2) {
            std::cin >> p;
            size_t actual_index = (begin + (p - 1)) % n;
            std::cout << a[actual_index] << std::endl;
        } else {
            size_t k = 0UL;
            std::cin >> k;
            begin = (begin + k) % n;
        }
    }

    return 0;
}