#include <algorithm>
#include <cstdint>
#include <iostream>
#include <iterator>
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

    int64_t n = 0LL, k = 0LL;
    std::cin >> n >> k;
    --k;

    std::vector<int64_t> a(n, 0);
    read_vec(0, n, a);

    int64_t start = a[k], start_index = 0LL;

    std::sort(a.begin(), a.end());

    auto start_iterator = std::ranges::find(a, start);
    start_index = std::ranges::distance(a.begin(), start_iterator);

    int64_t maximum_jumpable_level = 0LL, current_level = start_index,
            water_level = 0LL;
    while (current_level < n) {
        maximum_jumpable_level = a[current_level] - water_level;

        auto next_valid_itp1 = std::upper_bound(
            start_iterator, a.end(), a[maximum_jumpable_level + start_index]);

        int64_t next_jumpable_level =
            std::ranges::distance(start_iterator, next_valid_itp1);
        --next_jumpable_level;
        if (next_jumpable_level == current_level) {
            std::cout << "No\n";
            return;
        }
        if (next_jumpable_level == n - 1) {
            std::cout << "Yes\n";
            return;
        }

        water_level += (next_jumpable_level - current_level);
        current_level = next_jumpable_level;
    }

    std::cout << "Yes\n";
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