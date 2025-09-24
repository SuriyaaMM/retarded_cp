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

    std::vector<int64_t> a(n, 0);
    read_vec(0, n, a);

    std::unordered_map<int64_t, int64_t> fvm;
    std::map<int64_t, int64_t> ffm;
    for (int64_t i = 0; i < n; ++i) {
        fvm[a[i]]++;
    }
    for (const auto& [v, f] : fvm) {
        ffm[f]++;
    }

    auto print_ans = [](const int64_t& i) { std::cout << i + 1 << std::endl; };

    for (int64_t i = n - 1; i >= 0; --i) {
        if (ffm.size() == 1) {
            auto const& [freq, count] = *ffm.begin();
            if (freq == 1 || count == 1) {
                print_ans(i);
                return;
            }
        } else if (ffm.size() == 2) {
            auto const& [f1, fv1] = *ffm.begin();
            auto const& [f2, fv2] = *ffm.rbegin();

            if (f2 - f1 == 1 && fv2 == 1) {
                print_ans(i);
                return;
            }
            if (f1 == 1 && fv1 == 1) {
                print_ans(i);
                return;
            }
        }

        --ffm[fvm[a[i]]];
        if (ffm[fvm[a[i]]] == 0) ffm.erase(fvm[a[i]]);
        fvm[a[i]]--;
        if (fvm[a[i]] != 0) ffm[fvm[a[i]]]++;
    }
    std::cout << 1 << std::endl;
}

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

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