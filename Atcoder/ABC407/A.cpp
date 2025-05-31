// https://atcoder.jp/contests/abc407/tasks/abc407_a

#include <cmath>
#include <cstddef>
#include <iostream>

int main(int, char**) {

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t A = 0UL, B = 0UL;

    std::cin >> A >> B;

    double div = (double)(A) / (double)(B);
    double floor = std::floor(div);

    double diff = div - floor;

    if (diff > 0.5) {
        std::cout << static_cast<size_t>(std::ceil(div)) << std::endl;
    } else {
        std::cout << static_cast<size_t>(floor) << std::endl;
    }

    return 0;
}