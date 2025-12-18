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

int64_t abs_int64(int64_t x) {
    if (x > 0)
        return x;
    else
        return -x;
}

void solve() {
    int64_t n = 0LL;
    std::cin >> n;

    std::vector<pair_t> sf(n, {0, 0});
    read_vecp(0, n, sf);

    std::multiset<pair_t> pp;
    for (int64_t i = 0; i < n; ++i) {
        pp.emplace(sf[i].first, i);
        pp.emplace(sf[i].second, i);
    }

    std::vector<bool> p(n, false);
    int64_t cpos = 1LL, tt = 0LL;
    while (!pp.empty()) {
        auto& [maxc, imaxc] = *pp.rbegin();
        auto& [minc, iminc] = *pp.begin();
        int64_t td1 = abs_int64(maxc - cpos);
        int64_t td2 = abs_int64(minc - cpos);
        int64_t ti = -1;

        if (td1 > td2) {
            ti = imaxc;
        } else if (td2 > td1) {
            ti = iminc;
        } else {
            int64_t len1 = abs_int64(sf[imaxc].first - sf[imaxc].second);
            int64_t len2 = abs_int64(sf[iminc].first - sf[iminc].second);

            if (len1 > len2)
                ti = imaxc;
            else
                ti = iminc;
        }

        int64_t nf = 0LL;
        if (!p[ti]) {
            p[ti] = true;
            nf = sf[ti].first;
        } else {
            nf = sf[ti].second;
        }
        pp.erase({nf, ti});
        tt += abs_int64(nf - cpos);
        cpos = nf;
    }

    std::cout << tt << "\n";
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