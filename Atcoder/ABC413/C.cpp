#include <cstdint>
#include <deque>
#include <iostream>
#include <utility>

void solve() {
    int64_t q;
    std::cin >> q;

    std::deque<std::pair<int64_t, int64_t>> dq;

    for (int64_t i = 0; i < q; ++i) {
        int64_t type;
        std::cin >> type;

        if (type == 1) {
            int64_t c, x;
            std::cin >> c >> x;
            // add c copies of x to the end of A
            dq.emplace_back(x, c);
        } else {
            int64_t k_to_remove;
            std::cin >> k_to_remove;

            int64_t current_sum = 0;

            while (k_to_remove > 0 && !dq.empty()) {
                auto& front_pair = dq.front();
                int64_t current_value = front_pair.first;
                int64_t current_count = front_pair.second;

                if (k_to_remove >= current_count) {

                    current_sum += current_value * current_count;
                    k_to_remove -= current_count;
                    dq.pop_front();
                } else {

                    current_sum += current_value * k_to_remove;
                    front_pair.second -= k_to_remove;
                    k_to_remove = 0;
                }
            }
            std::cout << current_sum << '\n';
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    solve();

    return 0;
}