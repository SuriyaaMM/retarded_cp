#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <unordered_map>
#include <vector>

int main(int, char**) {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t t = 0UL;
    std::cin >> t;

    std::vector<std::vector<size_t>> a(t);

    for (size_t i = 0; i < t; ++i) {

        size_t n = 0UL;
        std::cin >> n;

        std::vector<size_t> b(n + 2, 0);
        for (size_t j = 0; j < n + 2; ++j) {

            std::cin >> b[j];
        }

        // solution

        // sort b O(nlogn)
        std::sort(b.begin(), b.end());
        // stores prefix sum by index
        std::unordered_map<size_t, size_t> prefix_sum_index_map = {};
        // O(n)
        size_t sum = 0UL;
        for (size_t j = 0; j < n + 2; ++j) {
            sum += b[j];
            prefix_sum_index_map[sum] = j;
        }
        // we calculate the difference which is sum - b[n] - b[n+1]
        // if that difference is in our prefix sum map, then we can construct a, or else
        // we cant
        // O(1)
        size_t diff = sum - b[n] - b[n + 1];
        if (prefix_sum_index_map.count(diff)) {

            a[i] = std::vector<size_t>(b.begin(), b.begin() + n);
        } else {
            a[i] = std::vector<size_t>(0);
        }

        // O(n) + O(nlogn) + O(1) = O(nlogn)
    }

    for (std::vector<size_t>& answer : a) {

        if (answer.size() != 0) {
            for (size_t j = 0; j < answer.size(); ++j) {

                std::cout << answer[j] << " ";
            }
            std::cout << std::endl;
        } else {
            std::cout << -1 << std::endl;
        }
    }
}