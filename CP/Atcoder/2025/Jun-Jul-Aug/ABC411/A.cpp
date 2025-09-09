#include <cstddef>
#include <iostream>
#include <string>

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::string p = "";
    size_t l = 0UL;

    std::cin >> p >> l;

    if (l <= p.size()) {
        std::cout << "Yes" << "\n";
    } else {
        std::cout << "No" << "\n";
    }

    return 0;
}