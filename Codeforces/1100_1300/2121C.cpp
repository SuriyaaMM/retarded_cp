#include <algorithm>
#include <cstdint>
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
    int64_t n = 0LL, m = 0LL;
    std::cin >> n >> m;

    std::vector<std::vector<int64_t>> grid(n, std::vector<int64_t>(m, 0));
    std::priority_queue<pair_t> row_heap, column_heap;

    int64_t global_sum = 0LL;

    for (int64_t i = 0; i < n; ++i) {
        int64_t row_sum = 0LL;
        for (int64_t j = 0; j < m; ++j) {
            std::cin >> grid[i][j];
            row_sum += grid[i][j];
            global_sum += grid[i][j];
        }
        row_heap.push(std::make_pair(row_sum, i));
    }

    for (int64_t j = 0; j < m; ++j) {
        int64_t column_sum = 0LL;
        for (int64_t i = 0; i < n; ++i) {
            column_sum += grid[i][j];
        }
        column_heap.push(std::make_pair(column_sum, j));
    }

    const auto [row_sum, row] = row_heap.top();
    const auto [column_sum, column] = column_heap.top();

    int64_t answer = global_sum + grid[row][column] - n - m;
    std::cout << answer << std::endl;

    //O(2*n*m) + O(nlogn + mlogm)
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