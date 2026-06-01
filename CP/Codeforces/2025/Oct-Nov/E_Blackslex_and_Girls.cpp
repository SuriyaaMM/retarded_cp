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
    int64_t n = 0LL, x = 0LL, y = 0LL;
    std::cin >> n >> x >> y;

    std::string s;
    std::cin >> s;

    std::vector<int64_t> p(n);
    int64_t sp = 0;

    for (int64_t i = 0; i < n; ++i) {
        std::cin >> p[i];
        p[i] = std::max(p[i], 1L);
        sp += p[i];
    }

    int64_t tv = x + y;
    int64_t e = tv - sp;

    if (e < 0) {
        std::cout << "NO\n";
        return;
    }

    int64_t bma = 0;
    bool hpd = false;
    int64_t epo = 0;

    for (int i = 0; i < n; ++i) {
        if (s[i] == '1') {
            bma += (p[i] / 2) + 1;
            if (p[i] % 2 == 0) epo++;
        } else {
            hpd = true;
        }
    }

    int64_t man = bma;
    if (!hpd) {
        int64_t te = e;
        int64_t cheap = std::min(te, epo);
        te -= cheap;

        if (te > 0) {
            man += (te + 1) / 2;
        }
    }

    int64_t bmaa = 0;
    bool hod = false;
    int64_t epz = 0;

    for (int64_t i = 0; i < n; ++i) {
        if (s[i] == '1') {
            bmaa += p[i];
            hod = true;
        } else {
            bmaa += (p[i] - 1) / 2;
            if (p[i] % 2 == 0) epz++;
        }
    }

    int64_t map = bmaa;

    if (hod) {
        map += e;
    } else {
        int64_t te = e;
        int64_t profit = std::min(te, epz);
        map += profit;
        te -= profit;
        if (te > 0) {
            map += te / 2;
        }
    }

    if (x >= man && x <= map) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
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