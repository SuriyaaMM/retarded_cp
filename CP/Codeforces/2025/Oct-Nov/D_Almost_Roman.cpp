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

    std::string s = "";
    std::cin >> s;

    // int64_t nq = 0LL, nt = 0LL, bs = 0LL;
    // for (int64_t i = 0; i < n; ++i) {
    //     if (s[i] == '?') {
    //         ++nq;
    //     } else {
    //         if (s[i] == 'V') {
    //             bs += 5;
    //         }
    //         if (s[i] == 'X') {
    //             bs += 10;
    //         }
    //         if (s[i] == 'I') {
    //             if (i + 1 < n) {
    //                 if (s[i + 1] != 'I') {
    //                     bs--;
    //                 }
    //             } else {
    //                 bs++;
    //             }
    //         }
    //     }
    //     if (i + 1 < n) {
    //         if (s[i] == 'I' && s[i + 1] != 'I') {
    //             ++nt;
    //         }
    //     }
    // }

    // for (int64_t i = 0; i < q; ++i) {
    //     int64_t nx = 0LL, nv = 0LL, ni = 0LL;
    //     std::cin >> nx >> nv >> ni;

    //     int64_t nh = nx + nv;
    //     int64_t nl = ni;

    //     if (nq <= nl) {
    //         std::cout << bs + nq << "\n";
    //     } else {
    //         int64_t nil = nq - ni;
    //         int64_t nvl = nq - ni - nv;
    //         int64_t nxl = nq - ni - nv - nx;

    //         std::cout << bs + std::max(0L, nil * i) + std::max(0L, nvl * 5) +
    //                          std::max(0L, nxl * 10)
    //                   << "\n";
    //     }
    // }

    // 1. Calculate Base Score
    // Assume ALL '?' are 'I'.
    // This is the starting point (0 Heavies used).
    int64_t base_score = 0;
    for (int i = 0; i < n; ++i) {
        char c = (s[i] == '?') ? 'I' : s[i];
        if (c == 'X')
            base_score += 10;
        else if (c == 'V')
            base_score += 5;
        else {
            // It is I (or ? acting as I).
            // Value is -1 if the NEXT FIXED character is Heavy.
            // (Note: adjacent ? acts as I, so it doesn't trigger the -1)
            if (i + 1 < n && (s[i + 1] == 'X' || s[i + 1] == 'V')) {
                base_score += -1;
            } else {
                base_score += 1;
            }
        }
    }

    // 2. Count Marginal Costs per Block
    int64_t total_count2 = 0;
    int64_t total_count4 = 0;
    int64_t total_count6 = 0;
    int64_t total_q = 0;

    for (int i = 0; i < n;) {
        if (s[i] != '?') {
            i++;
            continue;
        }

        // Identify block range [i, j)
        int j = i;
        while (j < n && s[j] == '?') j++;
        int64_t len = j - i;
        total_q += len;

        // Check Neighbors
        // Left neighbor is Heavy if it exists and is X/V. Otherwise Light.
        bool left_H = (i > 0 && (s[i - 1] == 'X' || s[i - 1] == 'V'));
        // Right neighbor is Heavy if it exists and is X/V. Otherwise Light.
        bool right_H = (j < n && (s[j] == 'X' || s[j] == 'V'));

        int64_t c2 = 0, c4 = 0, c6 = 0;

        if (!left_H && !right_H) {
            // L...L
            c2 = (len + 1) / 2;
            c4 = (len % 2 == 0);
        } else if (left_H && right_H) {
            // H...H
            if (len > 0) c2 = (len - 1) / 2;
            if (len > 1) c4 = 1;
        } else {
            // L...H or H...L
            c2 = len / 2;
            c4 = (len % 2 != 0);
        }

        c6 = len - c2 - c4;

        total_count2 += c2;
        total_count4 += c4;
        total_count6 += c6;

        i = j;
    }

    // 3. Answer Queries
    while (q--) {
        int64_t nx, nv, ni;
        std::cin >> nx >> nv >> ni;

        // We are forced to use at least this many Heavies
        int64_t k = std::max(0L, total_q - ni);

        int64_t ans = base_score;

        // Apply marginal costs (Cheapest first: 2, then 4, then 6)
        int64_t take = std::min(k, total_count2);
        ans += take * 2;
        k -= take;

        take = std::min(k, total_count4);
        ans += take * 4;
        k -= take;

        take = std::min(k, total_count6);
        ans += take * 6;
        k -= take;

        // X Adjustment: The marginal costs assume we used V (value 5).
        // If we were forced to use X, we add the difference (+5).
        // Heavies used = (total_q - ni). V available = nv.
        int64_t used_heavies = std::max(0L, total_q - ni);
        if (used_heavies > nv) {
            ans += (used_heavies - nv) * 5;
        }

        std::cout << ans << "\n";
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