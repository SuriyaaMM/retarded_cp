#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <system_error>
#include <unordered_map>
#include <vector>

int main(int, char**) {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t t = 0UL;
    std::cin >> t;

    std::vector<size_t> results(t, 0);

    for (size_t i = 0; i < t; ++i) {

        size_t n = 0UL;
        std::cin >> n;

        std::vector<int64_t> a(n);

        for (size_t j = 0; j < n; ++j) {

            std::cin >> a[j];
        }

        // solution
        // calculate f, where f[i] = a[i] - i, O(n)
        for (size_t j = 0; j < n; ++j) {
            a[j] = a[j] - j;
        }

        // now the answer will be sum of forming two pairs of all the elements
        // effectively a[i]C2 for each i and their sum will be the answer
        // this can be done effectively using hashmap because we know
        // (n+1)C2 - (n)C2 = n

        // construct a map to store frequency
        std::unordered_map<int64_t, size_t> frequency_map = {};
        // feasible_pairs is the answer
        size_t feasible_pairs = 0UL;

        // O(n)[traversing vector and inserting into map] + O(1)[lookup in hashmap]
        for (size_t j = 0; j < n; ++j) {

            if (frequency_map.count(a[j]))
                feasible_pairs += frequency_map[a[j]];

            ++frequency_map[a[j]];
        }

        // overall O(n) + O(n) + O(1) = O(n)
        results[i] = feasible_pairs;
    }

    for (size_t& feasible_pair : results) {
        std::cout << feasible_pair << std::endl;
    }

    return 0;
}