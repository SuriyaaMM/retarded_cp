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

bool move_is_valid(int64_t i, int64_t j, int64_t n, int64_t m) {
    return ((i < n) && (i >= 0) && (j < m) && (j >= 0));
}

void solve() {
    int64_t n = 0LL, m = 0LL;
    std::cin >> n >> m;

    std::vector<std::vector<int64_t>> grid(n, std::vector<int64_t>(m, 0));
    for (int64_t i = 0; i < n; ++i) {
        for (int64_t j = 0; j < m; ++j) {
            std::cin >> grid[i][j];
        }
    }

    for (int64_t i = 0; i < n; ++i) {
        for (int64_t j = 0; j < m; ++j) {
            bool is_peak = true;
            bool has_neighbor = false;
            if (move_is_valid(i + 1, j, n, m)) {
                has_neighbor = true;
                if (grid[i][j] <= grid[i + 1][j]) is_peak = false;
            }

            if (move_is_valid(i - 1, j, n, m)) {
                has_neighbor = true;
                if (grid[i][j] <= grid[i - 1][j]) is_peak = false;
            }

            if (move_is_valid(i, j + 1, n, m)) {
                has_neighbor = true;
                if (grid[i][j] <= grid[i][j + 1]) is_peak = false;
            }

            if (move_is_valid(i, j - 1, n, m)) {
                has_neighbor = true;
                if (grid[i][j] <= grid[i][j - 1]) is_peak = false;
            }

            if (is_peak && has_neighbor) {
                grid[i][j] = ninf;
                if (move_is_valid(i + 1, j, n, m))
                    grid[i][j] = std::max(grid[i][j], grid[i + 1][j]);
                if (move_is_valid(i - 1, j, n, m))
                    grid[i][j] = std::max(grid[i][j], grid[i - 1][j]);
                if (move_is_valid(i, j + 1, n, m))
                    grid[i][j] = std::max(grid[i][j], grid[i][j + 1]);
                if (move_is_valid(i, j - 1, n, m))
                    grid[i][j] = std::max(grid[i][j], grid[i][j - 1]);
            }
        }
    }

    for (int64_t i = 0; i < n; ++i) {
        for (int64_t j = 0; j < m; ++j) {
            std::cout << grid[i][j] << " ";
        }
        std::cout << "\n";
    }
}

int main(int, char **) {
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