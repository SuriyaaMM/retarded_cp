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
    int64_t n = 0LL, q = 0LL;
    std::cin >> n >> q;

    std::vector<int64_t> a(n, 0);
    read_vec(0, n, a);

    std::vector<int64_t> prefix(n, 0), rmax(n, 0);
    prefix[0] = a[0];
    rmax[0] = a[0];
    int64_t rmaxx = rmax[0];
    for (int64_t i = 1; i < n; ++i) prefix[i] = prefix[i - 1] + a[i];
    for (int64_t i = 1; i < n; ++i) {
        rmax[i] = std::max(rmaxx, a[i]);
        rmaxx = std::max(rmaxx, rmax[i]);
    }

    for (int64_t i = 0; i < q; ++i) {
        int64_t ki = 0LL;
        std::cin >> ki;

        if (ki == 0) {
            std::cout << 0 << " ";
            continue;
        }

        auto fo_it = std::upper_bound(rmax.begin(), rmax.end(), ki);
        if (fo_it == rmax.end()) {
            std::cout << prefix.back() << " ";
            continue;
        }
        int64_t si = std::distance(rmax.begin(), fo_it) - 1;
        if (si < 0) {
            std::cout << 0 << " ";
            continue;
        }
        if (si > n) {
            std::cout << prefix.back() << " ";
        }
        std::cout << prefix[std::distance(rmax.begin(), fo_it) - 1] << " ";
    }
    std::cout << std::endl;
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