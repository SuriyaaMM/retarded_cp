#include <cstddef>
#include <iostream>
#include <vector>

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    size_t n = 0UL;
    std::cin >> n;

    std::vector<size_t> d(n - 1);
    for (size_t i = 0; i < n - 1; ++i)
        std::cin >> d[i];

    for (size_t i = 0; i < n - 1; ++i) {
        size_t sum = 0UL;
        for (size_t j = i; j < n - 1; ++j) {
            sum += d[j];
            std::cout << sum << " ";
        }
        std::cout << "\n";
    }

    return 0;
}