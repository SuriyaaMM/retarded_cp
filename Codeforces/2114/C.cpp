#include <cmath>
#include <iostream>
#include <string>
#include <vector>

int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t t = 0UL;
    std::cin >> t;

    std::vector<size_t> results(t, 0);

    for (size_t i = 0; i < t; ++i) {

        size_t n = 0UL;
        std::cin >> n;

        std::vector<size_t> a(n, 0);

        for (size_t j = 0; j < n; ++j) {
            std::cin >> a[j];
        }

        // solution
        size_t last_picked_element = a[0], max_arrays = 1UL;

        for (size_t j = 1; j < n; ++j) {

            if (last_picked_element + 1 < a[j]) {
                last_picked_element = a[j];
                ++max_arrays;
            }
        }

        results[i] = max_arrays;
    }

    for (size_t& result : results) {

        std::cout << result << std::endl;
    }

    return 0;
}