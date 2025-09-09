#include <cstddef>
#include <iostream>

int main(int, char**) {

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    size_t t = 0UL;
    std::cin >> t;

    while (t--) {

        size_t n = 0UL;
        std::cin >> n;

        size_t current_state = 0UL, next_balanced_state = 0UL,
               num_actions = 0UL;

        while (current_state < n) {

            next_balanced_state = 2 * current_state + 1;
            num_actions += 3;
            if (next_balanced_state >= n) {
                break;
            }
            current_state = next_balanced_state;
        }

        std::cout << num_actions << std::endl;
    }

    return 0;
}