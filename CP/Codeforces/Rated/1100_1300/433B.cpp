// https://codeforces.com/problemset/problem/433/B

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <vector>

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    size_t n = 0UL;
    std::cin >> n;

    std::vector<size_t> v(n, 0);

    for (size_t i = 0; i < n; ++i) {
        std::cin >> v[i];
    }

    // calculate prefix sum
    std::vector<size_t> prefix(n, 0);
    prefix[0] = v[0];

    for (size_t i = 1; i < n; ++i) {
        prefix[i] = v[i] + prefix[i - 1];
    }

    // sort the array and calcuate prefix sum
    std::sort(v.begin(), v.end());

    std::vector<size_t> prefix_sorted(n, 0);
    prefix_sorted[0] = v[0];

    for (size_t i = 1; i < n; ++i) {
        prefix_sorted[i] = v[i] + prefix_sorted[i - 1];
    }

    // now we are ready to process the queries

    size_t m = 0UL, type = 0UL, l = 0UL, r = 0UL;
    std::cin >> m;

    for (size_t i = 0; i < m; ++i) {
        std::cin >> type >> l >> r;

        // for 0-based indexing
        --l;
        --r;

        if (type == 1) {
            // if l == 0, then we need to print only prefix upto r which is out answer
            if (l == 0) {
                std::cout << prefix[r] << std::endl;
            }
            // else the difference of l-1 and r
            else {
                std::cout << prefix[r] - prefix[l - 1] << std::endl;
            }
        }
        // for type 2 queries we print from our sorted prefix counter part
        else {
            if (l == 0) {
                std::cout << prefix_sorted[r] << std::endl;
            } else {
                std::cout << prefix_sorted[r] - prefix_sorted[l - 1]
                          << std::endl;
            }
        }
    }

    return 0;
}