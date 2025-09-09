#include <algorithm>
#include <cstdint>
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

// disjoint set union by  & path compression
struct dsur_t {

    std::vector<int64_t> parent, rank;

    dsur_t(int64_t n) {
        // O(n)
        parent.resize(n + 1);
        // O(n)
        rank.resize(n + 1, 0);

        for (int64_t i = 1; i <= n; ++i) {
            parent[i] = i;
        }
    }
    // O(1)
    int64_t find_parent(int64_t x) {
        if (parent[x] != x)
            parent[x] = find_parent(parent[x]);
        return parent[x];
    }

    void unite(int64_t u, int64_t v) {
        u = find_parent(u);
        v = find_parent(v);

        if (v == u)
            return;

        if (rank[u] < rank[v])
            std::swap(u, v);

        parent[v] = u;
        if (rank[u] == rank[v])
            ++rank[u];
    }
};

/*
we can choose any slime of same size then merge it
so if we choose slime of size X, then it becomes slime of size 2X
slime size is 1e9 at most, so at most we can do 30 merges log2(1e9) is 30
immediate greedy step will not be optimal minimum over time
dp[i] = min number of slimes that we can have at the end of sequence
for calculating dp[i] -> a[i] -> 2a[i] -> .......... 
we can sort a[i] in nlogn time, then do binary search to find this in logn time?
    say we have 3 slimes of size 3, 1 slime of size 5, 1 slime of size 6
    for 3 we can start merging we will have 1 remaining in 3, 2 of size 6 and 1 of size 5
    then we can merge that 6 to form 1 slime of size 3, 1 slime of size 5.

    say we started with 1 slime of size 5, we cannot merge
    say we started with 1 slime of size 6, we cannot merge, so answer will be 1.
    answer for any step will be (a[i].first - a[i].first % 2)/2

*/

void solve() {

    int64_t n = 0L;
    std::cin >> n;

    std::map<int64_t, int64_t> fmap;
    for (int64_t i = 0; i < n; ++i) {
        int64_t s, c;
        std::cin >> s >> c;
        fmap[s] += c;
    }

    for (auto it = fmap.begin(); it != fmap.end(); ++it) {
        int64_t size = it->first;
        int64_t count = it->second;

        if (count >= 2) {
            fmap[2 * size] += count / 2;
            it->second = count % 2;
        }
    }

    int64_t total_slimes = 0L;
    for (const auto& pair : fmap) {
        total_slimes += pair.second;
    }

    std::cout << total_slimes << std::endl;

    // int64_t n = 0L;
    // std::cin >> n;

    // std::vector<pair_t> slimes(n, {0, 0});
    // read_vecp(0, n, slimes);

    // std::map<int64_t, int64_t> fmap;
    // for (const auto& [slime_size, slime_count] : slimes) {
    //     fmap[slime_size] = slime_count;
    // }

    // // std::sort(slimes.begin(), slimes.end());

    // int64_t sum = 0L;
    // for (int64_t i = 0; i < n; ++i) {
    //     sum += slimes[i].second;
    // }

    // int64_t answer = inf;

    // for (int64_t i = 0; i < n; ++i) {
    //     std::map<int64_t, int64_t> fmapc = fmap;
    //     int64_t merged = 0L, current_size = slimes[i].first;
    //     while (fmapc[current_size] >= 2) {
    //         int64_t this_merged =
    //             (fmapc[current_size] - fmapc[current_size] % 2) / 2;
    //         fmapc[current_size] %= 2;
    //         fmapc[current_size * 2] += this_merged;
    //         merged += this_merged;
    //         current_size *= 2;
    //     }

    //     answer = std::min(answer, sum - merged);
    // }

    // std::cout << answer << std::endl;

    // std::vector<int64_t> dp(n + 1, inf);
    // for (int64_t i = 0; i < n; ++i) {
    //     // we need at least 2 slimes for merging
    //     if (slimes[i].second < 2) {
    //         dp[i] = sum;
    //     }
    // }

    // for (int64_t i = 0; i < n; ++i) {
    //     int64_t& slime_to_merge = slimes[i].first;
    //     int64_t slimes_merged = 0L;
    //     // logn operation
    //     while (true) {
    //         auto it = std::lower_bound(
    //             slimes.begin(), slimes.end(), 2 * slime_to_merge,
    //             [](const pair_t& elem, const int64_t value) {
    //                 return elem.first < value;
    //             });
    //         if (it == slimes.end()) {
    //             break;
    //         } else {
    //             slimes_merged += slime_to_merge - (slime_to_merge % 2);
    //             it->first += slimes_merged / 2;
    //             slime_to_merge = it->first;
    //         }
    //     }
    //     dp[i] = sum - slimes_merged;
    // }

    // std::cout << *std::min_element(dp.begin(), dp.end()) << std::endl;
}

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    solve();

    return 0;
}