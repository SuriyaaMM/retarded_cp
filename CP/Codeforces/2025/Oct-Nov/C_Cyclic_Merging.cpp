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

    std::vector<int64_t> a(n, 0);
    read_vec(0, n, a);

    std::vector<int64_t> l(n), r(n);
    for (int64_t i = 0; i < n; ++i) {
        l[i] = (i == 0) ? n - 1 : i - 1;
        r[i] = (i == n - 1) ? 0 : i + 1;
    }
    std::vector<bool> alv(n, true);

    std::priority_queue<pair_t, std::vector<pair_t>, std::greater<pair_t>> pq;
    for (int64_t i = 0; i < n; ++i) {
        int64_t cost = std::max(a[i], a[r[i]]);
        pq.push({cost, i});
    }

    int64_t cc = 0LL, md = 0LL;
    while (md < n - 1) {
        auto [ci, i] = pq.top();
        pq.pop();

        if (!alv[i]) continue;

        int64_t j = r[i];
        if (ci != std::max(a[i], a[j])) continue;

        cc += ci;
        ++md;
        a[i] = ci;

        int64_t loi = l[i], roj = r[j];
        r[i] = roj;
        l[roj] = i;
        alv[j] = false;
        pq.push({std::max(a[i], a[roj]), i});
        pq.push({std::max(a[loi], a[i]), loi});
    }

    std::cout << cc << "\n";
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