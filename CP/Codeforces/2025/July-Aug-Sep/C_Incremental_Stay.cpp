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

// disjoint set union by  & path compression
struct dsur_t {
    std::vector<int64_t> parent, rank;

    dsur_t(int64_t n) {
        // O(n)
        parent.resize(n + 1);
        // O(n)
        rank.resize(n + 1, 0);

        for (int64_t i = 1; i <= n; ++i) {
            parent[i] = i;
        }
    }
    // O(1)
    int64_t find_parent(int64_t x) {
        if (parent[x] != x) parent[x] = find_parent(parent[x]);
        return parent[x];
    }

    void unite(int64_t u, int64_t v) {
        u = find_parent(u);
        v = find_parent(v);

        if (v == u) return;

        if (rank[u] < rank[v]) std::swap(u, v);

        parent[v] = u;
        if (rank[u] == rank[v]) ++rank[u];
    }
};

void solve() {
    int64_t n = 0LL;
    std::cin >> n;

    std::vector<int64_t> a(2 * n);
    for (int i = 0; i < 2 * n; ++i) {
        std::cin >> a[i];
    }

    std::vector<int64_t> ans(n, 0);
    int64_t sfn = 0;
    for (int i = 0; i < n; ++i) {
        sfn += a[i];
    }

    int64_t sln = 0;
    for (int i = n; i < 2 * n; ++i) {
        sln += a[i];
    }

    ans[n - 1] = sln - sfn;

    if (n == 1) {
        std::cout << ans[0] << std::endl;
        return;
    }

    std::vector<int64_t> d(2 * n - 1, 0);
    for (int i = 0; i < 2 * n - 1; ++i) {
        d[i] = a[i + 1] - a[i];
    }

    std::vector<int64_t> pse(n, 0);
    std::vector<int64_t> pso(n, 0);

    if (d.size() > 0) pse[0] = d[0];
    for (size_t i = 1; i < n; ++i) {
        pse[i] = pse[i - 1] + (2 * i < d.size() ? d[2 * i] : 0);
    }

    if (d.size() > 1) pso[0] = d[1];
    for (size_t i = 1; i < n; ++i) {
        pso[i] = pso[i - 1] + (2 * i + 1 < d.size() ? d[2 * i + 1] : 0);
    }

    auto query_sum = [&](int64_t start_idx, int64_t end_idx) {
        if (start_idx > end_idx) return (int64_t)0;
        if (start_idx % 2 == 0) {
            int64_t p_end_idx = end_idx / 2;
            int64_t p_start_idx = start_idx / 2;
            return pse[p_end_idx] -
                   (p_start_idx > 0 ? pse[p_start_idx - 1] : 0);
        } else {
            int64_t p_end_idx = end_idx / 2;
            int64_t p_start_idx = start_idx / 2;
            return pso[p_end_idx] -
                   (p_start_idx > 0 ? pso[p_start_idx - 1] : 0);
        }
    };

    for (int64_t k = n; k > 1; --k) {
        int64_t start_peak_d_idx = k - 1;
        int64_t end_peak_d_idx = 2 * n - k - 1;

        int64_t d_sum_for_peaks = query_sum(start_peak_d_idx, end_peak_d_idx);
        int64_t loss = 2 * d_sum_for_peaks;
        ans[k - 2] = ans[k - 1] - loss;
    }

    for (int64_t i = 0; i < ans.size(); ++i) {
        std::cout << ans[i] << (i == ans.size() - 1 ? "" : " ");
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