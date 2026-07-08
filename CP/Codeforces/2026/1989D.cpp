#include <bits/stdc++.h>

constexpr std::int32_t _maxa = 1e6 + 1;
constexpr std::int32_t _n = 1e6 + 1;

using t = std::tuple<std::int32_t, std::int32_t>;

std::unordered_map<std::int64_t, std::int64_t> cache2;
std::array<std::int64_t, _maxa> cache;
std::array<std::int32_t, _maxa> ma;
std::array<std::int32_t, _n> a, b;
std::array<std::int64_t, _n> c;
std::array<t, _n> d;

inline void solve() {
    std::int32_t n = 0, m = 0;
    std::cin >> n >> m;

    for (std::int32_t i = 0; i < n; ++i) std::cin >> a[i];
    for (std::int32_t i = 0; i < n; ++i) std::cin >> b[i];
    for (std::int32_t i = 0; i < m; ++i) std::cin >> c[i];
    for (std::int32_t i = 0; i < n; ++i)
        d[i] = std::make_tuple(a[i] - b[i], a[i]);

    std::sort(d.begin(), d.begin() + n);

    std::int32_t maxa = *std::max_element(a.begin(), a.begin() + n);

    for (std::int32_t i = 0; i < n; ++i) {
        std::int32_t ai = std::get<1>(d[i]);
        if (ma[ai] == 1e9) { ma[ai] = i; }
    }
    for (std::int32_t i = 1; i <= maxa; ++i) {
        ma[i] = std::min(ma[i], ma[i - 1]);
    }

    cache[0] = 0;
    for (std::int32_t i = 1; i <= maxa; ++i) {
        const std::int32_t j = ma[i];
        if (j == 1e9)
            cache[i] = 0;
        else {
            const std::int32_t dd = std::get<0>(d[j]);
            const std::int32_t aa = std::get<1>(d[j]);
            const std::int64_t k = (i - aa) / (dd) + 1;
            cache[i] = 2 * k + cache[i - k * dd];
        }
    }

    std::int64_t answer = 0;

    for (std::int32_t j = 0; j < m; ++j) {
        std::int64_t cj = c[j];

        if (cj <= maxa) {
            answer += cache[cj];
            continue;
        } else {
            const std::int32_t dd = std::get<0>(d[0]);
            const std::int32_t aa = std::get<1>(d[0]);
            const std::int64_t k = (cj - aa) / (dd) + 1;
            answer += 2 * k + cache[cj - k * dd];
        }
    }
    std::cout << answer << "\n";
}

int main(int, char **) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    std::fill(cache.begin(), cache.end(), -1);
    std::fill(ma.begin(), ma.end(), 1e9);

    std::int64_t t = 1;
    // std::cin >> t;
    while (t--) { solve(); }
    return 0;
}