#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <unordered_map>
#include <vector>

int main(int, char**) {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t t = 0UL;
    std::cin >> t;

    std::vector<std::string> results(t);

    for (size_t i = 0; i < t; ++i) {

        size_t n = 0UL, k = 0UL;
        std::cin >> n >> k;

        std::string s = "";
        std::cin >> s;

        // solution
        size_t count_0 = 0UL, count_1 = 0UL;

        for (size_t j = 0; j < n; ++j) {
            if (s[j] == '0')
                ++count_0;
            else
                ++count_1;
        }

        size_t min_good_pairs = 0UL;
        if (count_0 > count_1) {
            min_good_pairs = (count_0 - count_1) / 2;
        } else {
            min_good_pairs = (count_1 - count_0) / 2;
        }

        size_t max_good_pairs = (count_0 / 2) + (count_1 / 2);

        if (k < min_good_pairs || k > max_good_pairs) {
            results[i] = "NO";
        } else {

            if ((k - min_good_pairs) % 2 == 0) {
                results[i] = "YES";
            } else {
                results[i] = "NO";
            }
        }
    }

    for (std::string& result : results) {
        std::cout << result << std::endl;
    }

    return 0;
}