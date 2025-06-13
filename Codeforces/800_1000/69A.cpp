// https://codeforces.com/problemset/problem/69/A

#include <array>
#include <atomic>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    size_t n = 0UL;
    int64_t x = 0UL, y = 0UL, z = 0UL;
    std::cin >> n;

    std::vector<std::array<std::int64_t, 3>> forces(n);

    for (size_t i = 0; i < n; ++i) {
        std::cin >> x >> y >> z;
        forces[i] = {x, y, z};
    }

    x = 0LL;
    y = 0LL;
    z = 0LL;

    for (size_t i = 0; i < n; ++i) {
        x += forces[i][0];
        y += forces[i][1];
        z += forces[i][2];
    }

    if (x == 0 && y == 0 && z == 0) {
        std::cout << "YES" << std::endl;
    } else {
        std::cout << "NO" << std::endl;
    }

    return 0;
}