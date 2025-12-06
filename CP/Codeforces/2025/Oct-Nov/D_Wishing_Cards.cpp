#include <algorithm>
#include <cmath>
#include <cstdint>
#include <format>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

// reads the vector
#define read_vec(begin, end, vec) \
    for (int64_t i = begin; i < end; ++i) std::cin >> vec[i];

// reads the vector pair
#define read_vecp(begin, end, vec)        \
    for (int64_t i = begin; i < end; ++i) \
        std::cin >> vec[i].first >> vec[i].second;

// prints the vector
#define print_vec(begin, end, vec) \
    for (int64_t i = begin; i < end; ++i) std::cout << vec[i] << " ";

// infinity
constexpr const int64_t inf = std::numeric_limits<int64_t>::max();
// negative infinity
constexpr const int64_t ninf = std::numeric_limits<int64_t>::min();

// pair
using pair_t = std::pair<int64_t, int64_t>;
// generic pair
template <typename T1, typename T2>
using gpair_t = std::pair<T1, T2>;
// unweighted graph
using graph_t = std::vector<std::vector<int64_t>>;
// weighted graph
using wgraph_t = std::vector<std::vector<pair_t>>;

void solve() {
    int64_t n = 0LL, k = 0LL;
    std::cin >> n >> k;

    std::vector<int64_t> a(n, 0);
    read_vec(0, n, a);

    std::vector<pair_t> ca;
    int64_t pml = 0LL;
    for (int64_t i = 0; i < n; ++i) {
        if (a[i] > pml) {
            pml = a[i];
            ca.emplace_back(std::make_pair(i, a[i]));
        }
    }

    std::vector<std::vector<int64_t>> dp(k + 1,
                                         std::vector<int64_t>(k + 1, ninf));
    dp[0][0] = 0;

    int64_t nca = ca.size();
    for (int64_t i = 0; i < nca; ++i) {
        auto& [cfi, cfl] = ca[i];
        int64_t w = n - cfi;

        auto dp2 = dp;
        for (int64_t p = 0; p <= k; ++p) {
            int64_t u = 0LL, pmax = ninf;
            for (int64_t v = 1; v <= cfl; ++v) {
                if (p + v > k) break;
                while (u < v) {
                    if (dp[p][u] != ninf)
                        pmax = std::max(pmax, dp[p][u] - w * u);
                    u++;
                }
                if (pmax != ninf)
                    dp2[p + v][v] = std::max(dp2[p + v][v], pmax + w * v);
            }
        }
        dp = std::move(dp2);
    }

    int64_t ans = ninf;
    for (int64_t i = 0; i < k + 1; ++i)
        for (int64_t j = 0; j < k + 1; ++j) ans = std::max(ans, dp[i][j]);

    std::cout << ans << "\n";
}

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#define MT
#ifdef MT
    int64_t tt = 0L;
    std::cin >> tt;
    while (tt--) {
        solve();
    }
#else
    solve();
#endif

    return 0;
}