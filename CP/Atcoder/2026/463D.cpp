#include <bits/stdc++.h>

bool f(
    std::int64_t m, std::int32_t k,
    std::vector<std::pair<std::int64_t, std::int64_t>> &__restrict__ clothes) {

    std::int32_t n_chosen = 1;
    std::int64_t next = clothes[0].second + m;

    for (std::int32_t i = 1; i < (std::int32_t)clothes.size(); ++i) {
        if (clothes[i].first >= next) {
            next = clothes[i].second + m;
            n_chosen++;

            if (n_chosen >= k) return true;
        }
    }

    return n_chosen >= k;
}

void solve() {
    std::int32_t n = 0, k = 0;
    std::cin >> n >> k;

    std::vector<std::pair<std::int64_t, std::int64_t>> clothes(n, {0, 0});
    for (auto &[li, ri] : clothes) std::cin >> li >> ri;

    std::ranges::sort(clothes, [](const auto &a, const auto &b) {
        if (a.second == b.second)
            return a.first < b.first;
        else
            return a.second < b.second;
    });

    std::int64_t l = 1, h = 2e18, answer = -1;
    while (l <= h) {
        std::int64_t m = l + (h - l) / 2;
        if (f(m, k, clothes)) {
            l = m + 1;
            answer = m;
        } else {
            h = m - 1;
        }
    }

    std::cout << answer << "\n";
}


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::int32_t t = 1;
    // std::cin >> t;

    while (t--) { solve(); }
}