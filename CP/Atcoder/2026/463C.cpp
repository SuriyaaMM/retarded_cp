#include <bits/stdc++.h>

void solve() {
    std::int32_t n = 0;
    std::cin >> n;

    using t2 = std::tuple<std::int64_t, std::int64_t>;

    std::vector<t2> t(n, {0, 0});
    for (auto &[li, hi] : t) std::cin >> hi >> li;

    std::ranges::sort(t);

    std::vector<std::int64_t> smax(n, 0);
    smax[n - 1] = std::get<1>(t[n - 1]);

    for (std::int32_t i = n - 2; i >= 0; --i)
        smax[i] = std::max(smax[i + 1], std::get<1>(t[i]));

    std::map<std::int64_t, std::int64_t> tmap;
    for (std::int32_t i = 0; i < n; ++i) {
        if (!tmap.count(std::get<0>(t[i]))) {
            tmap[std::get<0>(t[i])] = smax[i];
        }
    }

    std::int32_t q = 0;
    std::cin >> q;
    for (std::int32_t i = 0; i < q; ++i) {
        std::int64_t ti = 0;
        std::cin >> ti;
        std::cout << tmap.lower_bound(ti + 1)->second << "\n";
    }
}


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::int32_t t = 1;
    // std::cin >> t;

    while (t--) { solve(); }
}