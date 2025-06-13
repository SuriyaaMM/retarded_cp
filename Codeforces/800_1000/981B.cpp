// https://codeforces.com/problemset/problem/981/B

#include <cstddef>
#include <iostream>
#include <unordered_map>

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    size_t n = 0UL, m = 0UL;
    std::cin >> n;

    std::unordered_map<size_t, size_t> a;

    size_t xi = 0UL, ai = 0UL;

    // insert the elements of a in unordered map
    for (size_t i = 0; i < n; ++i) {
        std::cin >> ai >> xi;
        a[ai] = xi;
    }

    std::cin >> m;
    // when inserting elements of bi, if that element is already in the map
    // then insert the one with largest value of money, this way we can maximize the money
    for (size_t i = 0; i < m; ++i) {
        std::cin >> ai >> xi;
        if (a.count(ai)) {
            if (a[ai] < xi) {
                a[ai] = xi;
            }
        } else {
            a[ai] = xi;
        }
    }

    size_t total_money = 0UL;
    for (auto& [index, money] : a) {
        total_money += money;
    }
    std::cout << total_money << std::endl;

    return 0;
}