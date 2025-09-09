#include <algorithm>
#include <cstdint>
#include <functional>
#include <iostream>
#include <limits>
#include <numeric>
#include <ostream>
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

    int64_t n = 0LL, m = 0LL;
    std::cin >> n >> m;

    std::vector<int64_t> a(n, 0);
    read_vec(0, n, a);

    std::sort(a.begin(), a.end());
    std::vector<int64_t> d(n, 0);

    for (int64_t i = 0; i < n - 1; ++i) {
        d[i] = a[i + 1] - a[i];
    }

    std::sort(d.begin(), d.end(), std::greater<>());
    int64_t sum = a[n - 1] - a[0];
    for (int64_t i = 0; i < m - 1; ++i) {
        sum -= d[i];
    }

    std::cout << sum << std::endl;
}

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    solve();

    return 0;
}