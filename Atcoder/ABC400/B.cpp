#include <cstddef>
#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    size_t n = 0UL, m = 0UL;
    std::cin >> n >> m;

    size_t limit = 1000000000;

    size_t x = 1UL, previous_n = 1UL;
    bool inf = false;

    for (size_t i = 1; i <= m; ++i) {
        x += n * previous_n;
        previous_n = n * previous_n;

        if (x > limit) {
            std::cout << "inf" << std::endl;
            inf = true;
            break;
        }
    }

    if (!inf) {
        std::cout << x << std::endl;
    }

    return 0;
}