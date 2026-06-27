#include <bits/stdc++.h>
#include <queue>

void solve() {
    std::int32_t n = 0;
    std::cin >> n;

    std::vector<std::int64_t> a(n + 1, 0);
    for (std::int32_t i = 1; i <= n; ++i) std::cin >> a[i];

    std::vector<std::int64_t> aux(n + 1,
                                  std::numeric_limits<std::int64_t>::max());

    std::map<std::int32_t, std::vector<std::int32_t>> m;
    for (std::int32_t i = 1; i <= n; ++i) {
        aux[i] = a[i] + i - 1;
        m[aux[i]].emplace_back(i);
    }
    std::sort(aux.begin(), aux.end());

    std::set<std::int64_t> v;
    v.emplace(n);
    std::priority_queue<std::int64_t> q;
    q.emplace(n);

    std::int64_t answer = n;

    while (!q.empty()) {
        auto a_size = q.top();
        q.pop();

        auto it = std::lower_bound(aux.begin(), aux.end(), a_size);

        if (it == aux.end()) { continue; }
        if (*it != a_size) { continue; }

        for (const auto &i : m[a_size]) {
            std::int64_t next_a_size = a_size + i - 1;
            answer = std::max(next_a_size, answer);
            if (m.count(next_a_size) && next_a_size != a_size &&
                v.find(next_a_size) == v.end()) {
                v.emplace(next_a_size);
                q.emplace(next_a_size);
            }
        }
    }

    std::cout << answer << "\n";
}


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::int32_t t = 1;
    std::cin >> t;

    while (t--) { solve(); }
}