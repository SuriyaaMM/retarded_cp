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
    int64_t n = 0LL, k = 0LL;
    std::cin >> n >> k;

    if (n == 0) {
        for (int64_t i = 0; i < k; ++i) std::cout << 0 << " ";
        std::cout << "\n";
        return;
    }

    if (k % 2 != 0) {
        for (int64_t i = 0; i < k; ++i) std::cout << n << " ";
        std::cout << "\n";
    } else {
        std::vector<int64_t> a(k, 0);
        std::set<int64_t> si;
        int64_t msb = 64 - __builtin_clzll(n);
        for (int64_t j = msb - 1; j >= 0; --j) {
            int64_t mask = (1ULL << j);
            if (n & mask) {
                for (int64_t i = 0; i < k; ++i) {
                    a[i] |= mask;
                }
                bool c = false;
                for (int64_t i = 0; i < k; ++i) {
                    auto it = si.find(i);
                    if (it == si.end()) {
                        a[i] &= ~mask;
                        si.emplace(i);
                        c = true;
                        break;
                    }
                }
                if (!c) a[0] &= ~mask;

            } else {
                int64_t ts = si.size();
                if (ts % 2 == 1) ts--;
                int64_t u = 0LL;
                for (int64_t i = 0; i < k; ++i) {
                    if (si.find(i) != si.end() && u < ts) {
                        a[i] |= mask;
                        ++u;
                    } else {
                        a[i] &= ~mask;
                    }
                }
            }
        }

        for (const auto& ai : a) std::cout << ai << " ";
        std::cout << "\n";
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