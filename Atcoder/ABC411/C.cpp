#include <cstddef>
#include <iostream>
#include <vector>

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    size_t n = 0UL, q = 0UL;
    std::cin >> n >> q;

    std::vector<bool> squares(n + 2, false);
    size_t interval_count = 0UL;

    for (size_t i = 0; i < q; ++i) {
        size_t a = 0UL;
        std::cin >> a;

        bool left_black = squares[a - 1];
        bool right_black = squares[a + 1];
        bool current_black = squares[a];

        if (current_black) {
            // Currently black, flipping to white
            if (left_black && right_black) {

                interval_count += 1;
            } else if (left_black || right_black) {

                interval_count += 0;
            } else {

                interval_count -= 1;
            }
        } else {
            // Currently white, flipping to black
            if (left_black && right_black) {

                interval_count -= 1;
            } else if (left_black || right_black) {

                interval_count += 0;
            } else {

                interval_count += 1;
            }
        }

        squares[a] = !squares[a];
        std::cout << interval_count << "\n";
    }

    return 0;
}