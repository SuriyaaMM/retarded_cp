#include <algorithm>
#include <cmath>
#include <cstdint>
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
#define read_vec(begin, end, vec)         \
    for (int64_t i = begin; i < end; ++i) \
        std::cin >> vec[i];

// reads the vector pair
#define read_vecp(begin, end, vec)        \
    for (int64_t i = begin; i < end; ++i) \
        std::cin >> vec[i].first >> vec[i].second;

// prints the vector
#define print_vec(begin, end, vec)        \
    for (int64_t i = begin; i < end; ++i) \
        std::cout << vec[i] << " ";

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
        if (parent[x] != x)
            parent[x] = find_parent(parent[x]);
        return parent[x];
    }

    void unite(int64_t u, int64_t v) {
        u = find_parent(u);
        v = find_parent(v);

        if (v == u)
            return;

        if (rank[u] < rank[v])
            std::swap(u, v);

        parent[v] = u;
        if (rank[u] == rank[v])
            ++rank[u];
    }
};

void solve() {
    int n = 0L;
    long long k = 0L;
    std::cin >> n >> k;
    std::vector<int> a(n);
    read_vec(0, n, a);

    // freq
    std::vector<int> cnt(n + 2, 0);
    for (int x : a)
        cnt[x]++;

    int M = 0;
    while (cnt[M] > 0)
        M++;
    int M2 = M + 1;
    while (cnt[M2] > 0)
        M2++;

    std::vector<int> b(n);
    for (int i = 0; i < n; i++) {
        if (a[i] != M)
            b[i] = M;
        else if (cnt[M] > 1)
            b[i] = M;
        else
            b[i] = M2;
    }

    if (k == 1) {
        std::cout << std::accumulate(b.begin(), b.end(), 0L) << "\n";
    } else {
        // Determine state for k>=2
        bool allM = true;
        for (int x : b)
            if (x != M) {
                allM = false;
                break;
            }

        if (allM) {
            // oscillates between M and M+1
            long long val = (k % 2 == 1 ? M : M + 1);
            std::cout << 1LL * n * val << "\n";
        } else {
            // mixture of M and M2 -> always stable sum
            std::cout << accumulate(b.begin(), b.end(), 0LL) << "\n";
        }
    }
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