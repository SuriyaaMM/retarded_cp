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

int64_t abs_i64(int64_t x) {
    if (x > 0)
        return x;
    else
        return -x;
}

void solve() {
    int64_t n = 0LL;
    std::cin >> n;

    std::vector<int64_t> a(n, 0);
    read_vec(0, n, a);

    if (n == 1 || n == 2) {
        std::cout << 0 << "\n";
        return;
    }

    int64_t ri = -1LL, md = 0LL;
    int64_t ss = 0LL;
    for (int64_t i = 0; i < n - 1; ++i) {
        ss += abs_i64(a[i + 1] - a[i]);
    }
    for (int64_t i = 1; i < n - 1; ++i) {
        int64_t cd = abs_i64(a[i + 1] - a[i]) + abs_i64(a[i] - a[i - 1]) -
                     abs_i64(a[i + 1] - a[i - 1]);
        if (cd > md) {
            md = cd;
            ri = i;
        }
    }
    if (abs_i64(a[1] - a[0]) > md) {
        md = abs_i64(a[1] - a[0]);
        ri = 0;
    }
    if (abs_i64(a[n - 2] - a[n - 1]) > md) {
        md = abs_i64(a[n - 2] - a[n - 1]);
        ri = n - 1;
    }

    std::cout << ss - md << "\n";
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