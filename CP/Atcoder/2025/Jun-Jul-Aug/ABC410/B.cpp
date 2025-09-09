#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <iterator>
#include <vector>

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    size_t n = 0UL, q = 0UL;
    std::cin >> n >> q;

    std::vector<size_t> x(q);
    for (size_t i = 0; i < q; ++i) {
        std::cin >> x[i];
    }

    std::vector<size_t> box_count(n + 1, 0);
    std::vector<size_t> result(q);

    for (size_t i = 0; i < q; ++i) {
        if (x[i] >= 1 && x[i] <= n) {
            result[i] = x[i];
            ++box_count[x[i]];
        } else {

            size_t min_count = box_count[1];
            size_t best_box = 1;

            for (size_t j = 2; j <= n; ++j) {
                if (box_count[j] < min_count) {
                    min_count = box_count[j];
                    best_box = j;
                }
            }

            result[i] = best_box;
            ++box_count[best_box];
        }
    }

    for (size_t i = 0; i < q; ++i) {
        std::cout << result[i];
        if (i < q - 1)
            std::cout << " ";
    }
    std::cout << std::endl;

    return 0;
}