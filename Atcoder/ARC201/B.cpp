#include <algorithm>
#include <cstdint>
#include <functional>
#include <iostream>
#include <limits>
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
    int64_t n = 0LL, w = 0LL;
    std::cin >> n >> w;
    std::vector<pair_t> a(n, {0, 0}), ar(n, {0, 0});

    for (int64_t i = 0; i < n; ++i) {
        std::cin >> a[i].first >> a[i].second;
        a[i].first = 1LL << a[i].first;
        ar[i] = {a[i].second, a[i].first};
    }

    std::ranges::sort(a);
    std::ranges::sort(ar, std::greater<>());

    int64_t search_index = 0LL, current_sum = 0LL, current_value = 0LL,
            max_value = 0LL;

    for (int64_t i = 0; i < n; ++i) {
        // immediatly we can return if this sum is > w
        if (ar[i].second > w) {
            continue;
        }
        // we will binary search in the possible space
        search_index = i;
        while (search_index < n) {
            current_sum += ar[search_index].second;
            std::ranges::lower_bound(ar,
                                     [](const auto& first, const auto& second) {

                                     })
        }
    }
}

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int64_t t = 0LL;
    std::cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}