#include <algorithm>
#include <cstddef>
#include <iostream>
#include <vector>

int main(int, char**) {

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t n = 0UL, m = 0UL;
    std::cin >> n >> m;

    // THIS IS O(nxm) which might fail for the given constraints
    // // keeps track of how many turrents are guarding certain wall k
    // // so we need one for each wall so initialize it with
    // std::vector<size_t> map(n);

    // for (size_t i = 0; i < m; ++i) {

    //     size_t li = 0UL, ri = 0UL;

    //     std::cin >> li >> ri;

    //     for (size_t j = li - 1; j < ri; ++j) {
    //         ++map[j];
    //     }
    // }
    //
    // std::cout << *std::min_element(map.begin(), map.end()) << std::endl;

    std::vector<size_t> pre_prefix_sum(n + 1, 0);

    for (size_t i = 0; i < m; ++i) {

        size_t li = 0UL, ri = 0UL;
        std::cin >> li >> ri;

        ++pre_prefix_sum[li - 1];
        --pre_prefix_sum[ri];
    }

    size_t min_guarded_wall = pre_prefix_sum[0];
    size_t current_guarded_count = pre_prefix_sum[0];

    for (size_t i = 1; i < n; ++i) {

        current_guarded_count += pre_prefix_sum[i];
        min_guarded_wall = std::min(min_guarded_wall, current_guarded_count);
    }

    std::cout << min_guarded_wall << std::endl;

    return 0;
}