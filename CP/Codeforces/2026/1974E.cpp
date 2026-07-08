#include <bits/stdc++.h>

inline void solve() {
    std::int32_t m = 0, x = 0;
    std::cin >> m >> x;

    std::vector<std::int32_t> h(m, 0), c(m, 0);
    for (std::int32_t i = 0; i < m; ++i) std::cin >> c[i] >> h[i];

    std::int32_t hmax = std::accumulate(h.begin(), h.end(), 0);

    std::vector<std::int64_t> f(hmax + 1, -1);
    f[0] = x;
    if (c[0] == 0) { f[h[0]] = x; }

    for (std::int32_t i = 1; i < m; ++i) {
        std::vector<std::int64_t> nf(hmax + 1, -1);

        if (c[i] == 0) { nf[h[i]] = x; }
        for (std::int32_t hi = 0; hi <= hmax; ++hi) {
            if (f[hi] != -1) {
                nf[hi] = std::max(nf[hi], f[hi] + x);
                if (c[i] <= f[hi]) {
                    nf[hi + h[i]] = std::max(nf[hi + h[i]], f[hi] - c[i] + x);
                }
            }
        }
        f = std::move(nf);
    }

    std::int32_t answer = 0;
    for (std::int32_t hi = 0; hi <= hmax; ++hi) {
        if (f[hi] != -1) { answer = std::max(answer, hi); }
    }
    std::cout << answer << "\n";
}

int main(int, char **) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    std::int64_t t = 1;
    std::cin >> t;
    while (t--) { solve(); }
    return 0;
}