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
    int64_t n = 0LL, q = 0LL;
    std::cin >> n >> q;

    std::vector<int64_t> a(n, 0);
    read_vec(0, n, a);
    std::map<int64_t, std::pair<int64_t, int64_t>> st;
    for (int64_t i = 0; i < n; ++i) {
        if (!st.count(a[i])) st[a[i]].first = i;
        st[a[i]].second = i;
    }

    for (int64_t i = 0; i < q; ++i) {
        int64_t ai = 0LL, bi = 0LL;
        std::cin >> ai >> bi;

        if (!st.count(ai) || !st.count(bi)) {
            std::cout << "NO\n";
            continue;
        }

        auto& [amini, amaxi] = st[ai];
        auto& [bmini, bmaxi] = st[bi];
        if (bmaxi > amini) {
            std::cout << "YES\n";
        } else {
            std::cout << "NO\n";
        }
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