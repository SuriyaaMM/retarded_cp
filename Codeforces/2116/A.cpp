#include <algorithm>
#include <array>
#include <cstddef>
#include <iostream>

void solve() {

    std::array<size_t, 4> game;
    std::cin >> game[0] >> game[1] >> game[2] >> game[3];

    if (std::min(game[0], game[2]) >= std::min(game[1], game[3])) {
        std::cout << "Gellyfish" << std::endl;
    } else {
        std::cout << "Flower" << std::endl;
    }
}

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    size_t t = 0UL;
    std::cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}