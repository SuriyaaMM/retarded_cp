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
    int64_t n = 0LL, m = 0LL, d = 0LL;
    std::cin >> n >> m >> d;

    std::vector<int64_t> a(n, 0), b(m, 0);
    read_vec(0, n, a);
    read_vec(0, m, b);

    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());

    int64_t max_sum = ninf;

    int64_t pa = n - 1, pb = m - 1, diff = 0LL;
    while (pa >= 0 && pb >= 0) {
        diff = std::abs(a[pa] - b[pb]);

        if (diff <= d) {
            std::cout << a[pa] + b[pb] << std::endl;
            return;
        }

        if (a[pa] > b[pb])
            --pa;
        else
            --pb;
    }

    if (max_sum != ninf) {
        std::cout << max_sum << std::endl;
    } else {
        std::cout << -1 << std::endl;
    }
}

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    solve();

    return 0;
}