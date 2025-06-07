#include <algorithm>
#include <cstddef>
#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::vector<size_t> possible_a = {5, 25, 50, 100, 200, 400};

    size_t a = 0UL;
    std::cin >> a;

    bool found = false;

    for (size_t i = 1; i <= 400; ++i) {

        if (a * i == 400) {
            std::cout << i << std::endl;
            found = true;
            break;
        }
    }

    if (!found) {
        std::cout << -1 << std::endl;
    }

    // if (std::find(possible_a.begin(), possible_a.end(), a) ==
    //     possible_a.end()) {
    //     std::cout << -1 << std::endl;
    // } else {
    //     std::cout << 400UL / a << std::endl;
    // }

    return 0;
}