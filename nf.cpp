#include <bits/stdc++.h>

void solve() {
    std::int32_t n = 0, m = 0;
    std::cin >> n >> m;

    std::vector<std::vector<std::int32_t>> adj(n);

    std::map<std::pair<std::int32_t, std::int32_t>, std::int32_t> mapping;

    for (std::int32_t i = 0; i < m; ++i) {
        std::int32_t u = 0, v = 0;
        std::cin >> u >> v;

        --u, --v;

        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
        mapping[std::make_pair(std::min(u, v), std::max(u, v))] = i;
    }

    std::vector<std::int32_t> s(n, 0);
    for (auto &si : s) {
        std::cin >> si;
        --si;
    }

    if (s[0] != 0) {
        std::cout << "impossible\n";
        return;
    }

    std::vector<std::int64_t> w(m, -1);

    std::int64_t maxw = 1e9;
    std::int32_t i = 0;

    while (i + 1 < n) {
        std::int32_t next = i + 1;
        bool f1 = false;
        while (true) {
            std::int32_t u = std::min(s[i], s[next]);
            std::int32_t v = std::max(s[i], s[next]);
            auto edge = std::make_pair(u, v);

            std::cout << "u = " << s[i] + 1 << std::endl;
            std::cout << "v = " << s[next] + 1 << std::endl;

            if (mapping.count(edge)) {
                f1 = true;
                w[mapping[edge]] = maxw;
                std::cout << "w maxed" << std::endl;
                maxw--;
                ++next;
            } else {
                if (f1 == false) {
                    std::cout << "impossible\n";
                    return;
                }
                f1 = false;
                i = next - 1;
                maxw = 1e9;
                break;
            }
        }
    }

    for (auto &wi : w) {
        if (wi == -1) {
            std::cout << 1 << " ";
        } else {
            std::cout << wi << " ";
        }
    }
    std::cout << "\n";
}

int main(int, char **) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    std::int64_t t = 1;
    // std::cin >> t;
    while (t--) { solve(); }
    return 0;
}
