#include <bits/stdc++.h>


void solve() {
    std::int32_t n = 0, q = 0;
    std::cin >> n >> q;

    std::deque<std::pair<std::int32_t, std::int32_t>> line;

    std::int32_t max_strength_index = -1;
    for (std::int32_t i = 0; i < n; ++i) {
        std::int32_t ai = 0;
        std::cin >> ai;

        if (ai == n) max_strength_index = (i + 1);
        line.emplace_back(std::make_pair(ai, i + 1));
    }

    std::vector<std::vector<std::int32_t>> v(n + 1,
                                             std::vector<std::int32_t>());
    std::int32_t n_saturation = 0, round_index = 1;
    while (!line.empty()) {
        auto [strength_1, i_1] = line.front();
        line.pop_front();
        auto [strength_2, i_2] = line.front();
        line.pop_front();

        if (strength_1 == n) {
            break;
        } else {
            if (strength_1 > strength_2) {
                v[i_1].emplace_back(round_index);
                line.emplace_front(std::make_pair(strength_1, i_1));
                line.emplace_back(std::make_pair(strength_2, i_2));
            } else {
                v[i_2].emplace_back(round_index);
                line.emplace_back(std::make_pair(strength_1, i_1));
                line.emplace_front(std::make_pair(strength_2, i_2));
            }
        }
        ++round_index;
        ++n_saturation;
    }

    for (std::int32_t i = 0; i < q; ++i) {
        std::int32_t id = 0, k = 0;
        std::cin >> id >> k;

        std::int32_t answer =
            std::upper_bound(v[id].begin(), v[id].end(), k) - v[id].begin();

        if (id == max_strength_index && k > n_saturation)
            answer += (k - n_saturation);

        std::cout << answer << "\n";
    }
}


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::int32_t t = 1;
    std::cin >> t;

    while (t--) { solve(); }
}