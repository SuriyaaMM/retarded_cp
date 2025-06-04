// https://usaco.org/index.php?page=viewproblem2&cpid=663

#include <array>
#include <iostream>
#include <utility>

using pair_t = std::pair<size_t, size_t>;

int main(int, char**) {

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::array<pair_t, 4> pasture_coords;

    pair_t xi_yi = {};

    for (size_t i = 0; i < 4; ++i) {
        std::cin >> xi_yi.first >> xi_yi.second;
        pasture_coords[i] = xi_yi;
    }

    // find minimum and maximum x-coord
    size_t min_x = std::min(pasture_coords[0].first, pasture_coords[2].first);
    size_t max_x = std::max(pasture_coords[1].first, pasture_coords[3].first);
    // find minimum and maximum y-coord
    size_t min_y = std::min(pasture_coords[0].second, pasture_coords[2].second);
    size_t max_y = std::max(pasture_coords[1].second, pasture_coords[3].second);

    size_t a = std::max(max_x - min_x, max_y - min_y);

    std::cout << a * a << std::endl;

    return 0;
}