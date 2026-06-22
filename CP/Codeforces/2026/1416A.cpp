#include <bits/stdc++.h>

void solve() {
    int32_t n = 0;
    std::cin >> n;

    std::vector<int32_t> a(n + 1, 0);
    for (int32_t i = 1; i <= n; ++i) std::cin >> a[i];

    constexpr const int32_t NINF = std::numeric_limits<int32_t>::min();

    // mnd = max neighbour distance of v = a[i]
    // pre = previous occurence of v = a[i]
    std::vector<int32_t> mnd(n + 2, NINF), pre(n + 2, 0);

    for (int32_t i = 1; i <= n; ++i) {
        const auto &v = a[i];
        mnd[v] = std::max(mnd[v], i - pre[v]);
        pre[v] = i;
    }
    for (int32_t i = 1; i <= n; ++i) {
        const auto &v = a[i];
        mnd[v] = std::max(mnd[v], n + 1 - pre[v]);
    }

    std::vector<int32_t> ans(n + 1, -1);
    for (int32_t v = 1; v <= n; ++v) {
        const auto &ws = mnd[v];
        if (ws != NINF && ws <= n)
            ans[ws] = (ans[ws] == -1) ? v : std::min(ans[ws], v);
    }

    for (int32_t k = 2; k <= n; ++k) {
        if (ans[k - 1] == -1) continue;
        ans[k] = (ans[k] == -1) ? ans[k - 1] : std::min(ans[k], ans[k - 1]);
    }

    for (int32_t k = 1; k <= n; ++k) { std::cout << ans[k] << " "; }
    std::cout << std::endl;
}


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int32_t t = 1;
    std::cin >> t;

    while (t--) { solve(); }
}