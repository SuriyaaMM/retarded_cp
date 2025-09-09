#include <cstddef>
#include <iostream>

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    float x = 0.0f;

    std::cin >> x;

    if (x >= 38.0) {
        std::cout << 1 << std::endl;
    } else if (x < 37.5) {
        std::cout << 3 << std::endl;
    } else if (x < 38.0 && x >= 37.5) {
        std::cout << 2 << std::endl;
    }

    return 0;
}