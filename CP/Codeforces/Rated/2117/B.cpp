#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    size_t t = 0UL, n = 0UL;
    std::cin >> t;
    while (t--) {

        std::cin >> n;

        std::vector<size_t> a(n);

        int64_t left = 0LL, right = static_cast<int64_t>(n - 1);

        bool fill_left = true;
        size_t i = 0UL;
        while (left <= right) {
            if (fill_left) {
                a[left++] = ++i;
                fill_left = !fill_left;
            } else {
                a[right--] = ++i;
                fill_left = !fill_left;
            }
        }

        for (size_t i = 0; i < n; ++i) {
            std::cout << a[i] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}