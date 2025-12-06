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
    int64_t n = 0LL;
    std::cin >> n;

    std::vector<std::vector<int64_t>> g(n, std::vector<int64_t>(n, 0));

    int64_t nn = 1LL;
    for (int64_t i = 0; i < n; ++i) {
        for (int64_t j = 0; j < n; ++j) {
            g[i][j] = nn;
            //std::cout << g[i][j] << " ";
            ++nn;
        }
        //std::cout << std::endl;
    }

    int64_t smax = ninf;
    for (int64_t i = 0; i < n; ++i) {
        for (int64_t j = 0; j < n; ++j) {
            int64_t ss = g[i][j];

            if (i + 1 < n) {
                ss += g[i + 1][j];
            }
            if (j + 1 < n) {
                ss += g[i][j + 1];
            }
            if (i - 1 >= 0) {
                ss += g[i - 1][j];
            }
            if (j - 1 >= 0) {
                ss += g[i][j - 1];
            }

            smax = std::max(ss, smax);
        }
    }

    std::cout << smax << "\n";
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