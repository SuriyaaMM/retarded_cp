#include <bits/stdc++.h>

void solve() {
    std::uint32_t n = 0, m = 0;
    std::cin >> n >> m;

    std::vector<std::uint64_t> a(n, 0), b(m, 0), c(m, 0);
    for (auto &ai : a) std::cin >> ai;
    for (auto &bi : b) std::cin >> bi;
    for (auto &ci : c) std::cin >> ci;

    using t2 = std::pair<std::uint64_t, std::uint64_t>;

    std::multiset<std::uint64_t> swords(a.begin(), a.end());
    std::vector<t2> type1, type2;

    for (std::uint32_t i = 0; i < m; ++i) {
        if (c[i] > 0)
            type1.emplace_back(std::make_pair(b[i], c[i]));
        else
            type2.emplace_back(std::make_pair(b[i], c[i]));
    }

    std::sort(type1.begin(), type1.end());

    std::uint64_t kills = 0;
    for (const auto &[bi, ci] : type1) {
        auto it = swords.lower_bound(bi);
        if (it != swords.end() && *it >= bi) {
            swords.erase(it);
            swords.emplace(std::max(*it, ci));
            ++kills;
        }
    }

    for (const auto &[bi, _] : type2) {
        auto it = swords.lower_bound(bi);
        if (it != swords.end() && *it >= bi) {
            swords.erase(it);
            ++kills;
        }
    }

    std::cout << kills << "\n";
}


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::int32_t t = 1;
    std::cin >> t;

    while (t--) { solve(); }
}