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

void solve() {
    int64_t na = 0LL, nb = 0LL;
    std::cin >> na >> nb;

    std::multiset<int64_t> a, b;
    for (int64_t i = 0; i < na; ++i) {
        int64_t ai = 0LL;
        std::cin >> ai;
        a.emplace(ai);
    }
    for (int64_t i = 0; i < nb; ++i) {
        int64_t bi = 0LL;
        std::cin >> bi;
        b.emplace(bi);
    }

    bool aturn = true;

    while (!a.empty() && !b.empty()) {
        int64_t amax = *a.rbegin();
        int64_t bmax = *b.rbegin();
        if (aturn) {
            b.erase(std::prev(b.end()));
            if (bmax > amax) b.emplace(bmax - amax);

        } else {
            a.erase(std::prev(a.end()));
            if (amax > bmax) a.emplace(amax - bmax);
        }
        aturn = !aturn;
    }

    if (a.empty()) {
        std::cout << "Bob\n";
    } else {
        std::cout << "Alice\n";
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