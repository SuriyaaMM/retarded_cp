#include <cstddef>
#include <iostream>
#include <unordered_map>
#include <vector>

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    size_t n = 0UL, l = 0UL;
    std::cin >> n >> l;

    std::vector<size_t> a(n - 1);

    for (size_t i = 0; i < n - 1; ++i) {
        std::cin >> a[i];
    }

    std::unordered_map<size_t, size_t> position;

    size_t current_position = 0UL;
    ++position[current_position];

    for (size_t i = 0; i < n - 1; ++i) {

        current_position = (current_position + a[i]) % l;
        ++position[current_position];
    }

    size_t num_triangles = 0UL;

    size_t side_length = l / 3;

    for (auto it = position.begin(); it != position.end(); ++it) {

        size_t position_1 = (it->first + side_length) % l;
        size_t position_2 = (it->first + 2 * side_length) % l;

        if (position.count(position_1) && position.count(position_2)) {
            long long count2 = position.at(position_1);
            long long count3 = position.at(position_2);

            num_triangles += (it->second * count2 * count3);
        }
    }

    if (l % 3 != 0) {
        std::cout << 0 << std::endl;
    } else {
        std::cout << num_triangles / 3 << std::endl;
    }
    return 0;
}