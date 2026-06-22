#include <bits/stdc++.h>


void solve() {
    std::int32_t n = 0;
    std::cin >> n;

    std::vector<std::int32_t> a(n, 0);
    for (auto &ai : a) std::cin >> ai;

    std::priority_queue<std::pair<std::int32_t, std::int32_t>> pq;
    for (int32_t i = 0; i < n; ++i) pq.emplace(std::make_pair(a[i], i + 1));

    std::vector<std::pair<std::int32_t, std::int32_t>> pairs;

    int64_t answer = 0;
    while (!pq.empty()) {
        auto [top, topi] = pq.top();
        pq.pop();

        if (top == 0) break;

        if (!pq.empty()) {
            auto [top2, top2i] = pq.top();
            pq.pop();

            if (top2 != 0) {
                pairs.emplace_back(std::make_pair(topi, top2i));
                --top2;
                --top;
                ++answer;
            } else {
                break;
            }

            pq.emplace(std::make_pair(top2, top2i));
            pq.emplace(std::make_pair(top, topi));
        } else {
            break;
        }
    }

    std::cout << answer << "\n";
    for (const auto &[u, v] : pairs) std::cout << u << " " << v << "\n";
}


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::int32_t t = 1;
    std::cin >> t;

    while (t--) { solve(); }
}