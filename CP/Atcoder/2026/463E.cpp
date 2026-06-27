#include <bits/stdc++.h>
#include <limits>
#include <queue>


void solve() {
    std::int32_t n = 0, m = 0, y = 0;
    std::cin >> n >> m >> y;

    using t2 = std::tuple<std::int64_t, std::int64_t>;
    using v2 = std::vector<std::vector<t2>>;

    v2 adjlist(n + 2);

    for (std::int32_t i = 0; i < m; ++i) {
        std::int32_t u = 0, v = 0;
        std::int64_t w = 0;
        std::cin >> u >> v >> w;
        u--;
        v--;

        adjlist[u].emplace_back(std::make_tuple(v, w));
        adjlist[v].emplace_back(std::make_tuple(u, w));
    }

    std::vector<std::int64_t> x(n, 0);
    for (std::int32_t i = 0; i < n; ++i) {
        std::int64_t xi = 0;
        std::cin >> xi;

        adjlist[i].emplace_back(std::make_tuple(n, xi));
        adjlist[n + 1].emplace_back(std::make_tuple(i, xi));
    }
    adjlist[n].emplace_back(n + 1, y);
    // adjlist[n + 1].emplace_back(n, y);

    std::vector<std::int64_t> d(n + 2,
                                std::numeric_limits<std::int64_t>::max());

    std::priority_queue<t2, std::vector<t2>, std::greater<>> pq;
    pq.emplace(std::make_tuple(0, 0));
    d[0] = 0;

    while (!pq.empty()) {
        auto [cdist, u] = pq.top();
        pq.pop();

        if (cdist > d[u]) continue;

        for (auto &[v, w] : adjlist[u]) {

            if (d[v] > cdist + w) {
                d[v] = cdist + w;
                pq.emplace(std::make_tuple(d[v], v));
            }
        }
    }

    for (std::int32_t i = 1; i < n; ++i) { std::cout << d[i] << " "; }
    std::cout << "\n";
}


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::int32_t t = 1;
    // std::cin >> t;

    while (t--) { solve(); }
}