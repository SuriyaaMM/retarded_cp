#include <algorithm>
#include <cstdint>
#include <iostream>
#include <limits>
#include <map>
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

void solve() {

    int64_t w = 0LL, h = 0LL, n = 0LL, a = 0LL, b = 0LL;
    std::cin >> w >> h >> n;

    std::vector<pair_t> strawberries(n, {0, 0});
    read_vecp(0, n, strawberries);

    std::cin >> a;
    std::vector<int64_t> acuts(a + 2, 0);
    read_vec(1, a + 1, acuts);
    acuts[a + 1] = w;

    std::ranges::sort(acuts);

    std::cin >> b;
    std::vector<int64_t> bcuts(b + 2, 0);
    read_vec(1, b + 1, bcuts);
    bcuts[b + 1] = h;

    std::ranges::sort(bcuts);

    std::map<pair_t, int64_t> cake_map;

    for (const auto& [sx, sy] : strawberries) {

        int64_t x_interval_index =
            std::ranges::lower_bound(acuts, sx) - acuts.begin() - 1;
        int64_t y_interval_index =
            std::ranges::lower_bound(bcuts, sy) - bcuts.begin() - 1;

        ++cake_map[std::make_pair(x_interval_index, y_interval_index)];
    }

    int64_t min_berries = inf, max_berries = 0;
    for (const auto& [grid, berries] : cake_map) {
        min_berries = std::min(min_berries, berries);
        max_berries = std::max(max_berries, berries);
    }

    int64_t total_pieces = (a + 1) * (b + 1);
    if (cake_map.size() < total_pieces)
        min_berries = 0;

    std::cout << min_berries << " " << max_berries << std::endl;
}

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    solve();

    return 0;
}