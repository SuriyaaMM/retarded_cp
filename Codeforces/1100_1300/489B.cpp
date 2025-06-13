// https://codeforces.com/problemset/problem/489/B

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int64_t n = 0UL, m = 0UL;
    std::cin >> n;
    std::vector<int64_t> a(n);

    for (int64_t i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    std::cin >> m;
    std::vector<int64_t> b(m);
    for (int64_t i = 0; i < m; ++i) {
        std::cin >> b[i];
    }

    // sort both the arrays
    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());
    // our answer
    size_t num_pairs = 0UL;
    // pointers for traversing a and b
    int64_t ap = 0UL, bp = 0UL;
    while (ap < n && bp < m) {

        // if the difference is atmost one, then we can pair them up, check for bigger one first
        if (std::abs(a[ap] - b[bp]) <= 1) {
            ++ap;
            ++bp;
            ++num_pairs;
        } else {
            if (a[ap] > b[bp]) {
                ++bp;
            } else {
                ++ap;
            }
        }
    }

    std::cout << num_pairs << std::endl;

    return 0;
}