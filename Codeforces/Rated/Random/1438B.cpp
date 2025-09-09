#include <algorithm>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <numeric>
#include <vector>

int main(int, char**) {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t t = 0UL;
    std::cin >> t;

    std::vector<std::string> results(t);

    for (size_t i = 0; i < t; ++i) {

        size_t n = 0UL;
        std::cin >> n;

        std::vector<size_t> a(n);

        for (size_t j = 0; j < n; ++j) {
            std::cin >> a[j];
            a[j] = 1 << a[j];
        }

        // solution
        // first SORT a
        std::sort(a.begin(), a.end());

        size_t backward = n - 2, forward = 1UL;
        size_t sum_backward = a[n - 1], sum_forward = a[0];

        std::string result = "NO";

        while (backward != forward) {

            if (sum_backward > sum_forward) {
                sum_forward += a[forward];
                ++forward;
            } else {
                sum_backward += a[backward];
                --backward;
            }
            if (sum_forward == sum_backward) {
                result = "YES";
                break;
            }
        }

        results[i] = result;
    }

    for (std::string& result : results) {
        std::cout << result << std::endl;
    }

    return 0;
}